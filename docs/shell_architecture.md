# Shell Architecture: How a Shell Processes a Command Line

> When you type a command into a shell and press Enter, the shell doesn't just "run" it. It processes that line of text through four distinct stages — each one transforming the input into a form the next stage can use — before anything actually executes. These notes explain what each stage does, why it exists, what data structure it produces, and how the four stages interact. By the end you will understand the full journey from raw text to running process.

## Prerequisites

- Basic C programming (pointers, structs, linked lists).
- A rough idea of what a Unix process is (a running program with its own memory space).
- Familiarity with using a shell (typing commands, using pipes, redirecting output to a file). You don't need to know *how* any of that works internally — that's what these notes teach.

## TL;DR

- A shell processes a command line in four stages, always in this order: **lexer → parser → expander → executor**.
- The **lexer** is a state machine that walks the raw input character by character, tracking quote context, and produces a flat list of tokens.
- The **parser** takes that flat token list and builds a **tree** (an AST) where operator precedence is encoded by depth. Each leaf is a simple command; each internal node is an operator (`|`, `&&`, `||`, `;`).
- The **expander** walks the tree's leaves and transforms each word — replacing `$VAR` with its value, expanding `~`, running `$(cmd)` — while respecting the quote context the lexer recorded. One input word can become zero or many output words.
- The **executor** recursively walks the tree and makes things happen: `fork()`, `execve()`, `pipe()`, `dup2()`, `waitpid()`.
- **Expansion happens after parsing, never before.** This is a security property: expanded text is data, not code. A `|` that comes out of a variable is just the character `|` — it never becomes a pipe operator.

---

<table_of_contents/>

---

## 1. The Big Picture: Why Four Stages, and Why This Order?

### Intuition

Imagine a hypothetical shell that expands variables *before* it figures out the structure of the command. A user sets:

```plain text
USER="; rm -rf ~"
```

The quotes around `; rm -rf ~` are **syntax** — the shell consumes them while parsing the assignment. They tell the shell "everything between these quotes is one value." The quotes themselves are **not** stored in the variable. After the assignment, `USER` contains exactly 12 characters: `;`, space, `r`, `m`, space, `-`, `r`, `f`, space, `~` — no quote characters anywhere.

Now the user types:

```plain text
echo $USER
```

In the hypothetical expand-first shell, the expander runs before the lexer. It replaces `$USER` with its stored value, and the lexer then receives:

```plain text
echo ; rm -rf ~
```

The lexer sees `;` as a command separator. It tokenizes this as **two commands**: `echo` (with no arguments) and `rm -rf ~`. The result: the user's home directory is deleted.

In a real shell, the lexer and parser run **first**, on the raw input `echo $USER`. They see one command (`echo`) with one argument (`$USER`). The structure is locked in. Only then does the expander replace `$USER` with its value — but that value is treated as **data**, not re-parsed as shell syntax. The `;` inside the variable is just a character. Nothing is deleted. `echo` prints `; rm -rf ~`.

<callout icon="🔑" color="green_bg">
The ordering rule: **tokenization and parsing happen on the raw input. Expansion happens later, on individual tokens. The results of expansion are never re-lexed as shell syntax.** Expanded text is data, not code.
</callout>

This is the fundamental security property of shells. It is also why `eval` is dangerous — `eval` explicitly re-lexes its argument as shell syntax, which is exactly the expand-first disaster described above, done on purpose.

### The four stages and their data flow

```plain text
  "ls -l | grep foo > out"        ← raw input (a string)
              |
              v
         +--------+
         | LEXER  |                ← stateful character-by-character walk
         +--------+
              |
              v
  [WORD(ls), WORD(-l), PIPE,       ← flat list of tokens
   WORD(grep), WORD(foo),
   REDIR_OUT, WORD(out)]
              |
              v
         +--------+
         | PARSER |                ← recursive descent
         +--------+
              |
              v
           PIPE                    ← tree (AST)
          /    \
     [ls -l]  [grep foo >out]      ← leaves = simple commands
              |
              v
        +----------+
        | EXPANDER |               ← walks leaves, replaces $VAR, ~, $(cmd)
        +----------+
              |
              v
           PIPE                    ← same tree, expanded words
          /    \
     [ls -l]  [grep foo >out]
              |
              v
        +----------+
        | EXECUTOR |               ← recursive tree walk: fork, exec, pipe, wait
        +----------+
              |
              v
         exit code                 ← integer (0 = success)
```

Each stage has a clear input and a clear output. The stages are cleanly separated: the lexer doesn't know about variables, the parser doesn't know about file descriptors, the expander doesn't create processes, and the executor doesn't tokenize anything.

---

## 2. The Lexer

### Intuition

The lexer's job is to walk a raw line of text — just a sequence of characters — and chop it into meaningful chunks called **tokens**. A token is the smallest piece of the input that has a meaning to the shell: a word, an operator like `|` or `>`, etc.

This sounds simple, but shell lexers are fundamentally harder than lexers for languages like C or Java. In those languages, a character like `+` means the same thing everywhere. In a shell, the meaning of a character **depends on its context**. The character `<` is a redirection operator in one context, plain text in another, and part of a heredoc operator `<<` in a third:

| Input | What `<` means | Why |
|---|---|---|
| `cat < file.txt` | Input redirection operator | Unquoted, between words |
| `echo "a < b"` | Literal character | Inside double quotes |
| `echo a\<b` | Literal character | Preceded by backslash (escaped) |
| `cat << EOF` | Part of the heredoc operator `<<` | Two `<` characters in a row form a different operator |

The lexer can't just look at each character in isolation. It needs to **remember what came before** — specifically, whether it's currently inside a quoted region, and whether the previous character was a backslash. This piece of memory is called **state**, and a lexer that carries state forward as it walks the input is called a **state machine**.

### Mechanics

At any point while walking the input, the lexer is in one of several states:

- **DEFAULT** — between words, or starting a new word. Metacharacters (` `, `|`, `>`, `<`, `&`, `;`) have their special meaning.
- **IN_WORD (unquoted)** — building up a word. Whitespace or a metacharacter ends the word.
- **IN_SINGLE_QUOTES** — everything is literal until the next `'`. Nothing is special inside single quotes. Not `$`, not `\`, not `"`. Nothing. Only the closing `'` ends it.
- **IN_DOUBLE_QUOTES** — most things are literal, but a few characters are still special (see below). The closing `"` ends it.
- **ESCAPED** — the previous character was `\` (outside single quotes). The current character is treated as a literal, regardless of what it is.

The lexer processes one character at a time. For each character, the rule is: **given my current state and this character, what do I do?** The answer is always one of three things:

1. **Append** the character to the current word as a literal.
2. **Change state** (e.g., enter or leave a quoted region).
3. **Emit** the current word as a completed token, and possibly also emit an operator token.

### What's special inside double quotes?

Inside `"..."`, most characters lose their special meaning — `*`, `?`, `|`, `;`, `'`, `<`, `>` are all just literal text. But a small set of characters remain special:

| Character | Behavior inside `"..."` |
|---|---|
| `$` | Still triggers variable expansion and command substitution |
| `` ` `` | Still triggers command substitution (old-style backtick syntax) |
| `"` | Ends the double-quoted region |
| `\` | Escapes the next character, but **only** if the next character is itself special inside double quotes (`$`, `` ` ``, `"`, `\`, or newline). Otherwise the `\` is kept as a literal backslash. |

<callout icon="⚠️" color="yellow_bg">
Inside double quotes, `\n` (backslash followed by `n`) does **not** become a newline. It stays as the two literal characters `\` and `n`, because `n` is not in the set of characters that `\` escapes inside double quotes. This is different from the unquoted case, where `\` escapes everything.
</callout>

Compare with single quotes: inside `'...'`, **nothing** is special. Not even `\`. The string `'\n'` is two literal characters. The string `'$USER'` is literally the six characters `$`, `U`, `S`, `E`, `R`. Single quotes are the "take this literally, no exceptions" quoting mechanism.

### Word boundaries — when does a token end?

The lexer ends the current word and emits it as a token when it encounters (while not inside any quotes):

- **Whitespace** — spaces or tabs between words.
- **A shell operator** — any metacharacter that has structural meaning: `|`, `<`, `>`, `&`, `;`, `(`, `)`. These end the current word **and** are emitted as their own tokens.

So the input `hello>out` (no spaces) produces **three** tokens: `hello`, `>`, `out`. A naive "split on whitespace" approach would see it as one token and completely miss the redirection.

Similarly, the lexer needs **one character of lookahead** for multi-character operators: `<<` vs `<`, `>>` vs `>`, `&&` vs `&`, `||` vs `|`. When the lexer sees `<`, it peeks at the next character. If it's also `<`, the operator is `<<` (heredoc). Otherwise it's `<` (input redirection).

### The gluing rule — adjacent quoted segments form one word

This is the subtlest part of the lexer and the source of most minishell bugs. Consider:

```plain text
echo "hello"world'foo'bar
```

The lexer walks this left to right:

1. `e`, `c`, `h`, `o` → builds the word `echo`.
2. Space → emits `echo`, switches to DEFAULT state.
3. `"` → enters IN_DOUBLE_QUOTES. Starts a new word.
4. `h`, `e`, `l`, `l`, `o` → appends to current word.
5. `"` → exits double quotes. **Does not emit the word.** Returns to IN_WORD (unquoted).
6. `w`, `o`, `r`, `l`, `d` → appends to the **same** word. Still building.
7. `'` → enters IN_SINGLE_QUOTES. Still the same word.
8. `f`, `o`, `o` → appends to the same word.
9. `'` → exits single quotes. Still the same word.
10. `b`, `a`, `r` → appends to the same word.
11. End of input → emits the word.

The result: two tokens — `echo` and `helloworldfoobar`. The second token is **one word**, formed by gluing together a double-quoted segment, an unquoted segment, a single-quoted segment, and another unquoted segment. The quote characters themselves are consumed as syntax; they don't appear in the output.

<callout icon="🔑" color="green_bg">
The lexer doesn't emit a new token every time the quoting style changes. It stays inside the same word, toggling its quote-state, and only emits when it hits actual whitespace or an operator (while unquoted). Adjacent quoted and unquoted pieces are **glued** into one word.
</callout>

### Preserving quote context for the expander

The lexer throws away the quote characters — they're syntax, not data. But later, the expander needs to know **which parts of a word were quoted and how**, because quoted and unquoted expansions behave differently:

- `$USER` (unquoted) → expands, then word-splits on whitespace.
- `"$USER"` (double-quoted) → expands, but no word-splitting.
- `'$USER'` (single-quoted) → no expansion at all. Literal text.

If the lexer stores a word as just a `char *`, this information is lost. The expander would see `$USERworld` and try to expand a variable named `USERworld`.

The solution: a word is not a plain string. It's a **list of segments**, where each segment carries a type tag:

```plain text
Word for: "$USER"world

  Segment 1: { type: DOUBLE_QUOTED, text: "$USER" }
  Segment 2: { type: UNQUOTED,      text: "world" }
```

The expander processes each segment according to its type. The lexer's job is to produce these tagged segments, not just raw strings.

### Heredocs — collected by the lexer, used by the executor

When the lexer encounters `<<DELIMITER`, it switches into a special mode: it reads subsequent lines of input verbatim (not as shell syntax) until it sees a line containing only `DELIMITER`. This block of text — the heredoc body — is attached to the redirection token, stored alongside the parse tree, and later delivered to the command's stdin by the executor.

Key points:

- The heredoc body is collected **before** the command runs. The shell grabs the text at lex time, not at execution time. The child process never reads from the script file.
- If the delimiter is **quoted** in any way (`'EOF'`, `"EOF"`, or `\EOF`), the heredoc body is treated as literal — no variable expansion. If the delimiter is **unquoted** (`EOF`), variables in the body are expanded at execution time.
- The lexer must remember whether the delimiter was quoted and attach that flag to the heredoc, so the expander (much later) knows whether to process the body.

For delivery, the shell typically creates a **pipe**: writes the heredoc body into the write end, connects the read end to the child's stdin via `dup2()`, and closes the write end. (Historically, some shells used temporary files instead. For small heredocs, a pipe is simpler — no cleanup needed.)

---

## 3. The Parser

### Intuition

The lexer produces a flat list of tokens — words and operators, one after another. The parser's job is to add **structure**: which words form a command, which commands are connected by pipes, which side of `&&` something is on. The flat list `[ls, -l, |, grep, foo, >, out]` doesn't tell you that `> out` belongs to `grep`, not to the whole pipeline. The parser makes that explicit.

The parser's output is a **tree** — specifically, an Abstract Syntax Tree (AST). A tree is the right data structure because shell commands **nest**: a pipeline can be the left operand of `&&`, which can be the left operand of `||`, and so on. A flat table can't express "this whole pipeline is one operand of `&&`." A tree can.

### Mechanics: the tree structure

Every node in the tree is one of two kinds:

**Leaves — simple commands.** A leaf is the smallest unit that can stand alone and actually execute. It's a struct containing:
- **argv**: the command name and its arguments (a list of words).
- **redirections**: a list of redirections that apply to this command (e.g., `> out`, `< in`, `>> append`, `<< heredoc`).

Example: `grep foo > out` becomes one leaf: `{ argv: [grep, foo], redirs: [(OUT, out)] }`. The redirection lives **inside** the leaf, not as its own tree node, because it belongs to this specific command.

**Internal nodes — operators.** An internal node represents a shell operator that combines two sub-expressions. Each internal node has:
- **type**: the operator (`|`, `&&`, `||`, `;`).
- **left child**: the left operand (a subtree or a leaf).
- **right child**: the right operand (a subtree or a leaf).

### Operator precedence

Not all operators bind with the same strength. In the expression `ls -l | grep foo && echo done`, the `|` binds `ls -l` and `grep foo` together more tightly than `&&` binds the pipeline to `echo done`. This is **operator precedence**, the same concept as `*` binding tighter than `+` in arithmetic.

The shell operators, ranked from tightest to loosest:

| Precedence | Operator | Meaning |
|---|---|---|
| Tightest | `\|` | Pipe — connect stdout to stdin |
| Middle | `&&`, `\|\|` | Logical AND / OR — conditional execution |
| Loosest | `;` | Sequential — run one after the other |

In the tree, **tighter operators sit deeper** (closer to the leaves) and **looser operators sit higher** (closer to the root). The root is the operator that gets evaluated **last**, because it wraps everything else.

When operators have the same precedence (like `&&` and `||`), they group **left-to-right**: `A && B || C` is read as `(A && B) || C`, not `A && (B || C)`.

### Worked example

The command: `ls -l | grep foo > out && echo done || echo fail`

**Step 1 — identify the operators and their precedence:**
- One `|` (tightest)
- One `&&` (middle)
- One `||` (middle, same as `&&`, grouped left-to-right)

**Step 2 — build the tree bottom-up, tightest first:**

Layer 1 — the `|` operator:

```plain text
          |
         / \
      ls -l  grep foo >out
```

(The `> out` is inside the `grep foo` leaf, not a separate node.)

Call this subtree **P**.

Layer 2 — the `&&` operator (its left operand is P, its right operand is `echo done`):

```plain text
           &&
          /  \
         P    echo done
```

Call this subtree **Q**.

Layer 3 — the `||` operator (loosest, so it's at the root; its left operand is Q):

```plain text
              ||
             /  \
            Q    echo fail
```

Fully expanded:

```plain text
              ||              <- root (evaluated last)
             /  \
            &&   echo fail
           /  \
          |    echo done
         / \
      ls -l  grep foo >out   <- leaves (simple commands)
```

Notice the tree leans left — that's a consequence of left-to-right grouping. The right side of the root is just one tiny leaf.

**Why this shape is correct — verified by execution:**

Running `false && echo done || echo fail` in bash prints `fail`. Trace the tree:

1. Evaluate `&&`: run `false`, it fails. Skip `echo done`. The `&&` subtree's result is "failed."
2. Evaluate `||`: its left child (the `&&` subtree) failed. So run `echo fail`.

If `||` were *underneath* `&&` instead of above it, then when `false` failed, `&&` would skip its entire right side (including `||` and `echo fail`), and nothing would print. The fact that `fail` does print proves `||` must sit above `&&` in the tree.

### Mechanics: recursive descent parsing

The standard technique for building the tree is **recursive descent** — one function per precedence level, from loosest to tightest:

```plain text
parse_list()             <- handles ;
  calls parse_andor()    <- handles && and ||
    calls parse_pipeline()   <- handles |
      calls parse_simple_command()   <- collects words + redirections
```

Each function:
- Calls the **next-tighter** function to get its operands (not itself — each layer delegates downward).
- Iterates on its **own** operator: if the next token is the operator this function handles, consume it and call the tighter function again for the right operand.
- **Stops and returns** when it sees an operator from a *looser* level (or end of input), leaving that token for the caller to handle.

This is the key insight: **each layer is willfully ignorant of operators outside its precedence level.** When `parse_pipeline()` sees `&&`, it doesn't know what `&&` means — it just stops and returns whatever it has built so far. The caller (`parse_andor()`) takes over and handles the `&&`.

**Trace: `A | B && C`**

1. `parse_andor()` is called. It needs a left operand, so it calls `parse_pipeline()`.
2. `parse_pipeline()` is called. It calls `parse_simple_command()`, which reads `A` and stops at `|`.
3. `parse_pipeline()` sees `|` — that's its operator. It consumes it and calls `parse_simple_command()` again, which reads `B` and stops at `&&`.
4. `parse_pipeline()` looks at the next token: `&&`. That's **not** `|`, so `parse_pipeline()` stops and returns the subtree `(A | B)`.
5. Back in `parse_andor()`: left operand is `(A | B)`. Next token is `&&` — that's what `parse_andor()` handles. It consumes `&&` and calls `parse_pipeline()` for the right operand.
6. `parse_pipeline()` calls `parse_simple_command()`, which reads `C` and stops at end of input. `parse_pipeline()` returns the leaf `C`.
7. `parse_andor()` builds the node `(A | B) && C` and returns.

Result:

```plain text
           &&
          /  \
         |    C
        / \
       A   B
```

`|` is deeper than `&&` — not because anyone checked precedence explicitly, but because `parse_pipeline()` was called *recursively from inside* `parse_andor()`'s operand fetch. The call stack structure enforces precedence automatically.

**Trace: `A && B | C`**

1. `parse_andor()` calls `parse_pipeline()`.
2. `parse_pipeline()` calls `parse_simple_command()`, reads `A`, stops at `&&`.
3. `parse_pipeline()` sees `&&` — not `|`. Stops. Returns just the leaf `A`.
4. `parse_andor()` has left operand `A`. Sees `&&`, consumes it, calls `parse_pipeline()` for right operand.
5. `parse_pipeline()` calls `parse_simple_command()`, reads `B`, stops at `|`.
6. `parse_pipeline()` sees `|` — its own operator. Consumes it, calls `parse_simple_command()`, reads `C`.
7. `parse_pipeline()` returns the subtree `(B | C)`.
8. `parse_andor()` builds `A && (B | C)` and returns.

Result:

```plain text
           &&
          /  \
         A    |
             / \
            B   C
```

`|` is again deeper than `&&`, even though `|` appeared *after* `&&` in the input. The precedence is correct regardless of the order operators appear in.

<callout icon="🔑" color="green_bg">
In recursive descent, **the tree shape is a physical reflection of the call stack during parsing.** Tighter operators are parsed inside deeper function calls, so they automatically end up deeper in the tree. Nobody ever compares precedence numbers — the layered function structure does it for free.
</callout>

For a minishell without bonus features (`&&`, `||`, `;`), the parser only needs **two layers**: `parse_pipeline()` and `parse_simple_command()`. If you later add the bonus operators, you add `parse_andor()` on top and `parse_list()` on top of that. Each new layer is a small function, and the existing layers don't change.

---

## 4. The Expander

### Intuition

After parsing, the tree's leaves contain words like `$USER`, `~/docs`, `*.c`, and `$(date)`. These are not yet the final strings that will be passed to `execve()`. The expander's job is to walk each leaf of the tree and transform every word into its final form — replacing variables with their values, tildes with home directories, command substitutions with their output, and glob patterns with matching filenames.

The critical property of the expander: **it cannot change the shape of the tree.** The structure (which commands, which pipes, which operators) was decided by the parser and is frozen. The expander can only modify the contents of leaves — the words inside simple commands.

### Mechanics: what the expander does to each word

For each word in a simple command's argv, the expander performs these operations in order:

1. **Tilde expansion** — a leading `~` becomes the user's home directory path (e.g., `/home/alice`).
2. **Variable expansion** — `$VAR` and `${VAR}` are replaced with the variable's value. `$?` is replaced with the exit code of the last command.
3. **Command substitution** — `$(command)` runs the command in a subshell and is replaced by its stdout output.
4. **Word splitting** — (unquoted expansions only) if the expanded value contains whitespace, it is split into multiple words.
5. **Globbing / pathname expansion** — (unquoted only) patterns like `*.c` are replaced with the list of matching filenames.

The order matters. Variable expansion happens **before** globbing so that a variable containing a glob pattern (e.g., `PATTERN="*.c"`) can be expanded and then matched against files. Globbing happens **after** word splitting because each split word might itself be a glob pattern.

### The shocking consequence: one word can become many (or zero)

This is the most surprising thing about expansion. Consider:

```plain text
FILES="a.c b.c c.c"
echo $FILES
```

The parser sees one command (`echo`) with one argument (`$FILES`). After expansion, `$FILES` is replaced by `a.c b.c c.c`, and then **word splitting** breaks that into three separate words. `echo` ends up receiving three arguments, not one.

Compare with the double-quoted version:

```plain text
echo "$FILES"
```

Here, the expander replaces `$FILES` with `a.c b.c c.c` but **does not word-split** because the expansion was inside double quotes. `echo` receives one argument: the single string `a.c b.c c.c` (with spaces inside it).

The same asymmetry applies to empty values:

```plain text
unset EMPTY
echo $EMPTY       # $EMPTY expands to nothing, the word is REMOVED. echo gets 0 arguments.
echo "$EMPTY"     # $EMPTY expands to nothing, but quotes PRESERVE the empty string. echo gets 1 argument (an empty string).
```

<callout icon="🔑" color="green_bg">
Unquoted expansions undergo word splitting and empty removal. Double-quoted expansions do not. This is the entire reason the advice "always quote your variables" exists in shell scripting.
</callout>

So the expander's input is a list of words, and its output is a **new** list of words — potentially longer or shorter than the input. It can't just modify words in place; it has to build a new argv.

### How the expander knows about quoting — the segment list

The expander needs to treat `$USER`, `"$USER"`, and `'$USER'` differently:

| Form | What happens |
|---|---|
| `$USER` (unquoted) | Expand, then word-split, then glob |
| `"$USER"` (double-quoted) | Expand, but no word-splitting, no globbing |
| `'$USER'` (single-quoted) | No expansion at all. Literal text. |

But the lexer already threw away the quote characters — they were syntax. So how does the expander know?

The answer is that the lexer **records the quote context** alongside each piece of text. A word is stored not as a plain `char *`, but as a list of **segments**, each tagged with its quote type:

```plain text
Input:  "$USER"world'!'

Stored as:
  Segment 1: { type: DOUBLE_QUOTED, text: "$USER" }
  Segment 2: { type: UNQUOTED,      text: "world" }
  Segment 3: { type: SINGLE_QUOTED, text: "!" }
```

The expander processes each segment according to its type:
- `SINGLE_QUOTED` → no expansion. Literal text.
- `DOUBLE_QUOTED` → expand `$VAR` and `$(cmd)`, but no word splitting, no globbing.
- `UNQUOTED` → expand `$VAR` and `$(cmd)`, then word split, then glob.

After processing all segments, the results are **concatenated** back into the final word (or words, if word splitting occurred in an unquoted segment).

### Edge cases & gotchas

- **Nested command substitution**: `$(echo $(date))` — the inner `$(date)` runs first, its output becomes part of the argument to the outer `echo`, whose output becomes the final substitution. The expander handles this recursively.
- **Variables inside command substitutions**: `$(echo $USER)` — the subshell that runs `echo $USER` has its own lexer/parser/expander cycle. The inner `$USER` is expanded inside the subshell, not by the outer expander.
- **Globbing that matches nothing**: if `*.xyz` matches no files, bash (by default) leaves the pattern as the literal string `*.xyz`. It does not remove the word or produce an error.
- **`$?` — the exit code variable**: `$?` expands to the exit code of the most recently completed foreground command. This is the primary way scripts check whether a command succeeded.

---

## 5. The Executor

### Intuition

The executor is where the tree meets the operating system. It takes the fully expanded parse tree and **makes things happen**: processes are forked, programs are loaded, pipes are connected, files are opened for redirection, and exit codes are collected. Structurally, the executor is the simplest stage — it's a recursive walk over the tree, with one rule per node type.

### Prerequisites: the three system calls

Before understanding the executor, you need three Unix system calls:

**`fork()`** — creates a new process. After a successful `fork()`, two processes exist: the **parent** (original) and the **child** (copy). They are running the same code, but `fork()` returns different values to each:
- Returns `0` to the child.
- Returns the child's PID (a positive number) to the parent.

The child's *actual* PID is a positive number (every process has a unique positive PID). The `0` return value is just how the child knows "I'm the child." It can find its real PID by calling `getpid()`.

**`execve(path, argv, envp)`** — replaces the current process's program with a new one. Same PID, same file descriptors — but the code, stack, and heap are completely swapped out. After a successful `execve()`, the calling function's next line of code **never executes**, because the code containing that line no longer exists in memory. It was overwritten by the new program.

<callout icon="⚠️" color="yellow_bg">
`execve()` does **not** create a new process. `fork()` creates the process; `execve()` replaces its program. This is why you need both: `fork()` to create a child, `execve()` (inside the child) to load the target program. If you called `execve()` without forking, it would replace your shell with `ls` — your shell would cease to exist.
</callout>

**`waitpid(pid, &status, flags)`** — the parent calls this to wait for a child process to finish. It blocks until the specified child exits, then stores the child's exit status in `status`. If the parent doesn't call `waitpid()`, the finished child becomes a **zombie process** — it's dead but its entry lingers in the process table, leaking system resources.

### Executing a simple command (a leaf)

The simplest case: a single command like `ls -l > out`.

```plain text
1. Shell (parent) calls fork().
   Two processes now exist: parent and child.

2. Child process:
   a. Set up redirections:
      - Open "out" for writing (O_WRONLY | O_CREAT | O_TRUNC).
      - dup2(fd_of_out, STDOUT_FILENO) — redirect stdout to the file.
      - close(fd_of_out) — no longer needed; stdout IS the file now.
   b. Call execve("/bin/ls", ["ls", "-l"], env).
      The child's code is replaced by ls. ls runs.

3. Parent process:
   Calls waitpid(child_pid, &status, 0).
   Blocks until the child finishes.

4. Child (ls) finishes and exits with a status code.
   waitpid() returns. Parent extracts the exit code.

5. Shell continues — displays the next prompt.
```

<callout icon="📌" color="blue_bg">
Redirections are set up **between `fork()` and `execve()`**. This is the only window where the child can manipulate its file descriptors before the new program takes over. Once `execve()` fires, it's too late.
</callout>

### Executing a pipeline

For `ls | grep foo`, the shell needs to connect the stdout of `ls` to the stdin of `grep`. This uses the `pipe()` system call.

**`pipe(fd[2])`** creates a unidirectional data channel: `fd[0]` is the read end, `fd[1]` is the write end. Bytes written to `fd[1]` can be read from `fd[0]`.

The full recipe for `A | B`:

```plain text
1. Parent calls pipe(fd).
   Now fd[0] = read end, fd[1] = write end.
   Three processes will have copies of both ends: parent, left child, right child.

2. Parent calls fork() -> LEFT CHILD.
   Left child:
     - close(fd[0])            Close the read end (doesn't need it)
     - dup2(fd[1], STDOUT)     Redirect stdout to pipe's write end
     - close(fd[1])            No longer needed; stdout IS the pipe now
     - execve(A)

3. Parent calls fork() -> RIGHT CHILD.
   Right child:
     - close(fd[1])            Close the write end (doesn't need it)
     - dup2(fd[0], STDIN)      Redirect stdin to pipe's read end
     - close(fd[0])            No longer needed; stdin IS the pipe now
     - execve(B)

4. Parent:
     - close(fd[0])            Must close BOTH ends
     - close(fd[1])            Otherwise the pipe never closes
     - waitpid() for both children
     - Return the RIGHT child's exit code (pipeline's result = last command's result)
```

<callout icon="🚨" color="red_bg">
**The most common pipe bug:** if the parent forgets to close its copies of the pipe file descriptors, the read end of the pipe will never see EOF (because the write end is still open in the parent). The right child will hang forever, waiting for input that never comes. **Every process must close every pipe fd it doesn't use.**
</callout>

Both children **must run concurrently**. If the parent waited for the left child to finish before forking the right child, commands like `yes | head -5` would hang forever: `yes` produces infinite output and only stops when `head` closes the read end of the pipe (which causes a SIGPIPE). But if `head` hasn't been started yet, `yes` never stops.

### Executing the full tree — the recursive walk

The executor is a single recursive function. For each node type, the rule is:

```plain text
execute(node):
  if node is a SIMPLE COMMAND (leaf):
      fork, set up redirections, execve, waitpid
      return exit code

  if node is a PIPE:
      create pipe
      fork left child  -> execute(node.left) with stdout redirected to pipe
      fork right child -> execute(node.right) with stdin redirected from pipe
      close pipe fds in parent
      waitpid both children
      return right child's exit code

  if node is AND (&&):
      code = execute(node.left)
      if code == 0:        # left succeeded
          return execute(node.right)
      return code          # left failed; skip right

  if node is OR (||):
      code = execute(node.left)
      if code != 0:        # left failed
          return execute(node.right)
      return code          # left succeeded; skip right

  if node is SEMICOLON (;):
      execute(node.left)   # run left, ignore its exit code
      return execute(node.right)
```

That's the entire executor. Five rules, one recursive walk. **The tree structure is what makes precedence and short-circuiting "just work."** The executor doesn't contain any precedence logic — all of that was baked into the tree shape by the parser. The executor just follows the tree.

---

## How the Pieces Fit Together

```plain text
                     raw input string
                           |
                     +-----v------+
                     |   LEXER    |  State machine. Walks chars.
                     |            |  Tracks quoting. Produces tokens
                     |            |  with quote-context segments.
                     +-----+------+
                           |
                     flat token list
                           |
                     +-----v------+
                     |   PARSER   |  Recursive descent.
                     |            |  One function per precedence level.
                     |            |  Produces a tree (AST).
                     +-----+------+
                           |
                      AST (tree)
                           |
                     +-----v------+
                     |  EXPANDER  |  Walks leaves of the tree.
                     |            |  Processes segments by quote type.
                     |            |  $VAR, ~, $(), globbing.
                     |            |  One word -> zero or many words.
                     +-----+------+
                           |
                   expanded AST (tree)
                           |
                     +-----v------+
                     |  EXECUTOR  |  Recursive tree walk.
                     |            |  fork, execve, pipe, dup2, waitpid.
                     |            |  Returns exit code.
                     +-----+------+
                           |
                       exit code
```

The stages are **strictly sequential**: each one completes before the next begins. And they are **cleanly separated**: each stage transforms one data structure into another, and doesn't need to know the internals of any other stage.

The single most important architectural decision is that **parsing happens before expansion**. This means the structure of a command is determined by what the user typed, not by the contents of variables. Expanded text is data, not code. This is both a security property and a simplification: the parser never needs to worry about variable values, and the expander never needs to worry about tree structure.

---

## Common Confusions

| Confusion | Clarification |
|---|---|
| "The lexer splits on whitespace" | No. The lexer splits on whitespace **and** shell operators, only when not inside quotes. `hello>out` is three tokens, not one. |
| "`execve()` creates a new process" | No. `fork()` creates the process. `execve()` replaces its program image. Same PID, same fds. |
| "Quotes are stored in the variable" | No. Quotes are syntax consumed by the lexer. `USER="hello"` stores 5 characters, not 7. |
| "Expansion can create new pipes or redirections" | No. Expansion happens after parsing. It can only change the contents of words, not the tree structure. |
| "`\|` inside a variable becomes a pipe" | No. Expanded text is data, not code. Metacharacters from expansion are never re-interpreted as shell syntax. |
| "The parent should wait for the left pipe child before forking the right" | No. Both sides of a pipe must run concurrently. Otherwise `yes \| head` hangs forever. |

---

## Self-Check

Test your understanding. Try answering each question before revealing the answer.

**1.** What does `echo $USER` do if `USER="hello world"` (two words in the value)? How many arguments does `echo` receive? What if it's `echo "$USER"` instead?

<details>
<summary>Answer 1</summary>
	Without quotes: `$USER` expands to `hello world`, then word splitting produces two separate words. `echo` receives **two** arguments: `hello` and `world`. Output: `hello world` (looks the same, but they're separate args).

	With double quotes: `"$USER"` expands to `hello world` as a single string (no word splitting). `echo` receives **one** argument. Output: `hello world`.

	The difference matters when the value contains special characters or when the argument count matters (e.g., `test -z $VAR` breaks if `VAR` has spaces; `test -z "$VAR"` always works).
</details>

**2.** Draw the parse tree for `A | B | C && D`. Which operator is at the root? Which is deepest?

<details>
<summary>Answer 2</summary>
	Precedence: `|` is tighter than `&&`. Multiple `|` at the same level group left-to-right.

	Tree:

```plain text
              &&
             /  \
            |    D
           / \
          |    C
         / \
        A   B
```

	`&&` is at the root (loosest, evaluated last). The deeper `|` node is deepest (tightest, evaluated first). The left-to-right grouping of `|` produces a left-leaning chain.
</details>

**3.** In the command `cat << 'EOF'` followed by lines containing `$HOME`, does `$HOME` get expanded? Why or why not?

<details>
<summary>Answer 3</summary>
	No, `$HOME` is **not** expanded. The delimiter `EOF` is enclosed in single quotes (`'EOF'`), which tells the shell to treat the entire heredoc body as literal text. Any form of quoting on the delimiter (`'EOF'`, `"EOF"`, `\EOF`) suppresses expansion in the body. Only an unquoted delimiter allows variable expansion.
</details>

**4.** What goes wrong if you call `execve()` without calling `fork()` first?

<details>
<summary>Answer 4</summary>
	`execve()` **replaces** the current process's program. If the current process is your shell, `execve()` replaces the shell with the target program (e.g., `ls`). Your shell ceases to exist. When `ls` finishes, there's no shell to return to — the terminal session ends. This is exactly what the shell built-in `exec ls` does intentionally.
</details>

**5.** A student's minishell hangs on `ls | cat`. The student's pipe code forks both children correctly and sets up `dup2()` in each child. What's the most likely bug?

<details>
<summary>Answer 5</summary>
	The parent didn't close its copies of the pipe file descriptors. After forking both children, the parent still holds `fd[0]` (read end) and `fd[1]` (write end). `cat` reads from stdin (the pipe's read end) until it sees EOF. EOF on a pipe only happens when **all** write ends are closed. Since the parent still has `fd[1]` open, `cat` never sees EOF and hangs forever. Fix: the parent must `close(fd[0])` and `close(fd[1])` after forking both children.
</details>

---

## Further Reading

- **Bash Reference Manual** — [gnu.org/software/bash/manual/](https://www.gnu.org/software/bash/manual/) — the authoritative spec for bash behavior. Sections 3.5 (Shell Expansions) and 3.7 (Executing Commands) are particularly relevant.
- `man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, `man 2 waitpid` — the system call man pages. Read these before writing executor code.
- `man 3 readline` — if your minishell uses readline for line editing and history.
- **The Open Group Base Specifications (POSIX Shell)** — [pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — the POSIX shell spec. Denser than the bash manual, but more precise. Good for settling "what should the shell do in this edge case?" debates.
- **"Advanced Programming in the UNIX Environment" by W. Richard Stevens** — chapters 8 (Process Control) and 15 (Interprocess Communication) cover fork, exec, pipe, and dup2 in depth with excellent diagrams.
