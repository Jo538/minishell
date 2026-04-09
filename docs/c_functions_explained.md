# C Functions Explained From Zero

This document explains a set of C functions commonly used when building a Unix shell (like `minishell`). It assumes **zero** prior knowledge: every term is introduced from scratch, with ASCII diagrams and concrete examples.

---

## Table of Contents

1. [Background concepts you need first](#background)
2. [Readline library](#readline)
3. [Standard I/O and memory](#stdio-mem)
4. [Low-level I/O](#lowio)
5. [Processes](#processes)
6. [Signals](#signals)
7. [Filesystem](#filesystem)
8. [Directories](#directories)
9. [Errors](#errors)
10. [Terminals](#terminals)
11. [Environment](#environment)
12. [Termcap](#termcap)

---

<a name="background"></a>
## 1. Background concepts you need first

Before any function makes sense, you need a few ideas.

### 1.1 A program is a process
When you run a program, the operating system (OS) creates a **process**: a running instance of that program with its own memory, its own open files, and its own ID number called a **PID** (process ID).

```
    +---------------------------+
    |        PROCESS            |
    |                           |
    |   code + variables        |
    |   open files (fd table)   |
    |   PID = 4321              |
    +---------------------------+
```

### 1.2 File descriptors
A **file descriptor** (fd) is just a small integer the OS gives you to refer to an open file (or pipe, socket, terminal, etc.). Three are open by default for every process:

```
    fd 0  -> stdin  (keyboard input)
    fd 1  -> stdout (screen output)
    fd 2  -> stderr (screen error output)
```

### 1.3 The kernel and system calls
The **kernel** is the core of the OS. A **system call** is a request from your program asking the kernel to do something privileged (read a file, create a process, etc.). Functions like `read`, `write`, `fork` are system calls. Functions like `printf`, `malloc` are normal library functions built on top.

### 1.4 Return values and errno
Most C library/system functions return a number. By convention:
- `0` or a positive number = success
- `-1` (or `NULL` for pointers) = failure, and a global variable `errno` is set to a code describing what went wrong.

You include `<errno.h>` to use `errno`.

---

<a name="readline"></a>
## 2. Readline library

The **readline** library lets your program read a line of input from the user with editing (arrow keys, backspace, history with up/down). You compile with `-lreadline`. Include `<readline/readline.h>` and `<readline/history.h>`.

---

### `readline`

```c
char *readline(const char *prompt);
```

#### What it does
Prints `prompt` to the screen, then waits for the user to type a line and press Enter. Returns the typed line as a heap-allocated string (without the newline). Returns `NULL` if the user pressed Ctrl-D on an empty line (end of input).

#### How it works internally
1. Switches the terminal to **raw mode** so it can intercept every keypress (arrows, backspace).
2. Each keypress runs an editor function (move cursor, delete char, etc.).
3. When Enter is pressed, it restores the terminal and returns a `malloc`'d copy of the line.

You **must** `free()` the returned string yourself.

#### Example
```c
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main(void) {
    char *line = readline("myshell$ ");
    if (line == NULL) {            // Ctrl-D
        printf("bye\n");
        return 0;
    }
    printf("you typed: %s\n", line);
    free(line);
    return 0;
}
```

```
    myshell$ hello world      <- user types this, presses Enter
    you typed: hello world
```

#### Bonus: readline tracks an undo history

While the user is editing a line, readline silently records every change they make — each character inserted, each deletion, each kill (cut), each paste. That recorded list of reversible edits is the **undo history** for the current line.

The user can then press `Ctrl-_` (or `Ctrl-/`) to undo the most recent change, then again to undo the one before, and so on — exactly like the undo in a text editor.

```
    User types:        line buffer:    undo stack (most recent on top):
    h                  "h"             [insert 'h' at 0]
    e                  "he"            [insert 'e' at 1] [insert 'h' at 0]
    l                  "hel"           [insert 'l' at 2] ...
    l                  "hell"          [insert 'l' at 3] ...
    Backspace          "hel"           [delete 'l' at 3] ...
```

If they now press `Ctrl-_`, readline pops the top of the stack and reverses it: the deleted `l` comes back and the buffer is `"hell"` again.

The undo history is **per line** — once the user presses Enter and `readline()` returns, that history is gone and a fresh one starts for the next line. This matters because some functions (like `rl_replace_line`, see below) take a parameter that lets you decide whether to also wipe the undo history when you mess with the buffer programmatically.

---

### `add_history`

```c
void add_history(const char *line);
```

#### What it does
Adds a line to the readline **history list** so that pressing the Up arrow next time recalls it.

#### How it works internally
History is stored as a dynamic array of strings inside the readline library. `add_history` copies the string and appends it.

#### Example
```c
char *line;
while ((line = readline("$ ")) != NULL) {
    if (*line)                 // skip empty lines
        add_history(line);
    printf("got: %s\n", line);
    free(line);
}
```

```
    $ ls
    got: ls
    $ pwd
    got: pwd
    $ <UP arrow>   -> shows "pwd"
    $ <UP arrow>   -> shows "ls"
```

---

### `rl_clear_history`

```c
void rl_clear_history(void);
```

#### What it does
Wipes the entire history list and frees all the memory it used.

#### How it works internally
Walks the internal history array, frees each entry, and resets the count to zero.

#### Example
```c
add_history("ls");
add_history("pwd");
rl_clear_history();   // history is now empty
```

Use this before exiting to avoid memory-leak warnings from tools like `valgrind`.

---

### `rl_on_new_line`

```c
int rl_on_new_line(void);
```

#### What it does
Tells readline: "the cursor is now on a fresh new line, please update your idea of where it is." Used after you printed something yourself (often from a signal handler).

#### How it works internally
Resets readline's internal cursor-position counters to column 0 of a new line.

#### Why you need it
Readline tracks where the cursor is so it can redraw correctly. If your code (or a signal handler) writes a newline, readline doesn't know — `rl_on_new_line` informs it.

#### The mental model: readline keeps a map of the screen

When `readline()` is running, the library maintains its own internal model of what's on the terminal:

- where the prompt was printed
- which column the cursor is at
- what's currently in the line buffer

It needs this model so that arrow keys, backspace, and redraws all work correctly. As long as **only readline** writes to the terminal, its model stays in sync with reality.

```
    What's actually on screen:        What readline THINKS is on screen:
    +----------------------+          prompt_col = 0
    | $ hello#             |          cursor_col = 7
    +----------------------+          line_buffer = "hello"
              ^
              cursor here
```

#### The desync problem

Now suppose the user presses **Ctrl-C** while typing `hello`. Your `SIGINT` handler runs and does:

```c
    write(1, "\n", 1);   // move to a fresh line
```

The real screen is now:

```
    +----------------------+
    | $ hello              |   <- old line, stale
    | #                    |   <- real cursor is HERE
    +----------------------+
```

But readline still believes:

```
    prompt_col = 0
    cursor_col = 7              <- WRONG: cursor is now at col 0 of a new line
    line_buffer = "hello"       <- also stale
```

If you call `rl_redisplay()` now, readline will emit movement and drawing commands **relative to where it thinks the cursor is** — but the terminal will execute those commands relative to where the cursor **actually** is. The result is garbled output: text landing at the wrong column, partial rewrites, misplaced cursors.

#### What `rl_on_new_line` actually does

It is a tiny function with one job: tell readline *"forget what you thought about cursor position — assume the cursor is now at column 0 of a brand-new empty line."* It just resets the internal position counters. It does **not**:
- touch the line buffer (that's `rl_replace_line`'s job)
- draw anything on the screen (that's `rl_redisplay`'s job)

```
    rl_on_new_line()  ->  updates the MAP
    rl_redisplay()    ->  redraws the TERRITORY using the corrected map
```

So `rl_on_new_line` by itself produces no visible change. The fix becomes visible only when `rl_redisplay` runs afterward and now computes positions from the correct starting point.

#### The three-step dance

After your code prints something behind readline's back, you typically need all three calls together — each fixes one piece of the desync:

```c
    write(1, "\n", 1);      // 1. you wrote a newline yourself
    rl_replace_line("", 0); // 2. fix the BUFFER  (throw away current input)
    rl_on_new_line();       // 3. fix the MAP     (cursor is at col 0 of new line)
    rl_redisplay();         // 4. fix the SCREEN  (redraw cleanly)
```

---

### `rl_replace_line`

```c
void rl_replace_line(const char *text, int clear_undo);
```

#### What it does
Replaces the text currently being edited with `text`. If `clear_undo` is non-zero, also wipes the undo history for that line.

#### How it works internally
Frees readline's internal line buffer and copies `text` into it. The cursor is moved to the end.

#### Example: Ctrl-C in a shell
When the user presses Ctrl-C, you want to throw away whatever they were typing and show a fresh prompt:
```c
void handle_sigint(int sig) {
    (void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 1);    // clear current input
    rl_on_new_line();          // we are now on a new line
    rl_redisplay();            // redraw the prompt
}
```

---

### `rl_redisplay`

```c
void rl_redisplay(void);
```

#### What it does
Forces readline to redraw the prompt and the current input line on the terminal.

#### How it works internally
Writes the prompt string followed by the current line buffer to stdout, then positions the cursor.

Used together with `rl_on_new_line` and `rl_replace_line` (see Ctrl-C example above).

---

<a name="stdio-mem"></a>
## 3. Standard I/O and memory

---

### `printf`

```c
int printf(const char *format, ...);
```

#### What it does
Prints formatted text to stdout (fd 1). Returns the number of characters printed, or a negative value on error.

#### Format specifiers
| Spec | Meaning            | Example          |
|------|--------------------|------------------|
| `%d` | int                | `42`             |
| `%s` | string (char*)     | `hello`          |
| `%c` | single character   | `A`              |
| `%x` | hex integer        | `2a`             |
| `%p` | pointer            | `0x7ffe...`      |
| `%%` | literal `%`        | `%`              |

#### How it works internally
1. Parses the format string left to right.
2. For each `%X`, pulls the next argument from the variable-argument list (`stdarg.h`).
3. Converts it to characters and writes them into an internal buffer.
4. The buffer is flushed to fd 1 (immediately if it's a terminal, otherwise on newline or when full).

#### Example
```c
int age = 7;
char *name = "Sam";
printf("Hello %s, you are %d years old.\n", name, age);
```
Output:
```
    Hello Sam, you are 7 years old.
```

---

### `malloc`

```c
void *malloc(size_t size);
```

#### What it does
Asks the OS for a chunk of `size` bytes from the **heap** (a region of memory for dynamic allocation). Returns a pointer to the first byte, or `NULL` on failure.

The memory is **uninitialized** — it contains garbage until you write to it.

#### How it works internally
The C library keeps a pool of memory it got from the kernel (via `brk` or `mmap`). It tracks free blocks in a linked list. `malloc` finds a block big enough, splits it if needed, marks it used, and returns a pointer.

```
    HEAP layout (simplified):

    [used 32B][free 100B][used 16B][free ...]
                 ^
                 malloc(50) returns this
                 (and shrinks the free block)
```

#### Example
```c
int *arr = malloc(5 * sizeof(int));   // room for 5 ints
if (!arr) { perror("malloc"); exit(1); }
for (int i = 0; i < 5; i++) arr[i] = i * i;
// arr is now {0, 1, 4, 9, 16}
free(arr);
```

---

### `free`

```c
void free(void *ptr);
```

#### What it does
Returns memory previously allocated by `malloc` (or `calloc`/`realloc`) back to the heap so it can be reused.

#### Rules
- Passing `NULL` is safe; it does nothing.
- **Never** free the same pointer twice (double-free → crash).
- **Never** use a pointer after freeing it (use-after-free → bug).

#### How it works internally
Looks up the block's bookkeeping (usually stored just before the returned pointer), marks it free, and tries to merge it with neighboring free blocks (**coalescing**) to reduce fragmentation.

```
    Before free:  [used 50B][used 30B][free 20B]
                       ^
                       free(this)
    After free:   [free 50B][used 30B][free 20B]
```

---

<a name="lowio"></a>
## 4. Low-level I/O

These are direct system calls. Include `<unistd.h>` and `<fcntl.h>`.

---

### `write`

```c
ssize_t write(int fd, const void *buf, size_t count);
```

#### What it does
Writes up to `count` bytes from `buf` to file descriptor `fd`. Returns the number of bytes actually written, or `-1` on error.

#### How it works internally
The kernel copies the bytes from your process's memory into the kernel buffer for that fd, then schedules them to be sent to the underlying device (disk, terminal, pipe...).

#### Example
```c
write(1, "hello\n", 6);     // prints "hello" to stdout
```

#### ⚠️ Unlike `printf`, `write` does no formatting — it sends raw bytes.

---

### `access`

```c
int access(const char *pathname, int mode);
```

#### What it does
Checks if the calling process can access the file `pathname` according to `mode`. Returns `0` if yes, `-1` if no.

#### Modes (bitwise OR)
| Constant | Meaning            |
|----------|--------------------|
| `F_OK`   | file exists        |
| `R_OK`   | readable           |
| `W_OK`   | writable           |
| `X_OK`   | executable         |

#### Example: searching PATH for a command
```c
if (access("/bin/ls", X_OK) == 0)
    printf("/bin/ls is executable\n");
```

---

### `open`

```c
int open(const char *pathname, int flags, ... /* mode_t mode */);
```

#### What it does
Opens a file and returns a new file descriptor (a small int), or `-1` on error.

#### Common flags (bitwise OR)
| Flag         | Meaning                       |
|--------------|-------------------------------|
| `O_RDONLY`   | read only                     |
| `O_WRONLY`   | write only                    |
| `O_RDWR`     | read and write                |
| `O_CREAT`    | create the file if missing    |
| `O_TRUNC`    | truncate to size 0 if exists  |
| `O_APPEND`   | every write goes to the end   |

If `O_CREAT` is used you must pass a third argument `mode` giving permission bits, e.g. `0644`.

#### How it works internally
The kernel:
1. Looks up the file path on disk.
2. Checks permissions.
3. Allocates an entry in the process's fd table pointing at the file.
4. Returns the smallest unused fd number.

```
    fd table (before):  0 1 2  -  -  -
    fd table (after open returns 3):
                        0 1 2 [file] - -
```

#### Example
```c
int fd = open("notes.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (fd < 0) { perror("open"); exit(1); }
write(fd, "hello\n", 6);
close(fd);
```

---

### `read`

```c
ssize_t read(int fd, void *buf, size_t count);
```

#### What it does
Reads up to `count` bytes from `fd` into `buf`. Returns:
- `> 0` : number of bytes actually read
- `0`   : end of file
- `-1`  : error

#### Example
```c
char buf[128];
ssize_t n = read(0, buf, sizeof(buf) - 1);   // read from stdin
if (n > 0) {
    buf[n] = '\0';
    printf("got: %s", buf);
}
```

---

### `close`

```c
int close(int fd);
```

#### What it does
Releases a file descriptor. After `close`, that fd number can be reused for another open. Returns `0` on success, `-1` on error.

#### ⚠️ Always close fds you no longer need; otherwise you leak them and may run out. ⚠️

---

<a name="processes"></a>
## 5. Processes

---

### `fork`

```c
pid_t fork(void);
```

#### What it does
Creates a new process by **duplicating** the current one. After `fork`, there are *two* processes running the same code from the same point.

#### Return value (this is the tricky bit!)
- In the **parent**: returns the child's PID (positive number).
- In the **child**: returns `0`.
- On error: returns `-1`, no child created.

```
    Before fork:           After fork:
    [Parent PID=100]       [Parent PID=100]   [Child PID=101]
          |                       |                 |
       fork()                  pid=101           pid=0
```

#### How it works internally
The kernel makes a copy of the parent's memory pages (using **copy-on-write**: pages are shared until one process writes to them) and the file descriptor table.
Each process, the parent and the child, have separated memories and fd tables. When fork is called, the child gets an exact copy of the memory + fd table of the parent. 
Then, if the child changes its memory + fd table, it will become different to the parent's.

#### Example
```c
pid_t pid = fork();
if (pid < 0)        perror("fork");
else if (pid == 0)  printf("I am the child\n");
else                printf("I am the parent, child=%d\n", pid);
```

---

### `wait`

```c
pid_t wait(int *status);
```

#### What it does
Suspends the parent until **any** child process terminates. Returns the PID of the child that exited, or `-1` if there are no children. If `status` is non-NULL, it gets info about how the child ended.

#### Example
```c
pid_t pid = fork();
if (pid == 0) { printf("child\n"); exit(0); }
int status;
wait(&status);
printf("child finished\n");
```

---

### `waitpid`

```c
pid_t waitpid(pid_t pid, int *status, int options);
```

#### What it does
Like `wait`, but lets you specify *which* child to wait for and how to wait.

- `pid > 0`  : wait for that specific child
- `pid == -1`: wait for any child (same as `wait`)
- `options`  : `0` to block, `WNOHANG` to return immediately if no child has exited

#### Deep dive: the `options` parameter (blocking vs non-blocking)

This little parameter hides a huge concept. When your program calls a function like `waitpid`, two very different things can happen:

- **Blocking** = the function does **not** return until the awaited event has happened. Your program is frozen at that line. The CPU isn't spinning — the kernel actually puts your process to **sleep** and lets other programs run. When the event occurs, the kernel wakes you up and the function finally returns. A blocked process consumes **zero CPU**.
- **Non-blocking** = the function returns **immediately**, no matter what. If the thing you wanted hasn't happened yet, the function tells you "nope, not yet" and your program keeps running.

Same function, two modes — chosen by `options`.

##### Mode 1: `options = 0` (blocking)

```
    Time ->

    parent: ...running... waitpid(pid,&s,0)  zzzzzzzz...  (woken up) ...continues...
                                  |                ^
                                  v                |
    child:  ...working...      ...still working... exit(0)
```

You call `waitpid(pid, &status, 0)`. If the child is still running, the kernel puts the parent to sleep. The parent does literally nothing — it consumes no CPU. Eventually the child exits, the kernel wakes the parent, and `waitpid` returns with the child's status filled in.

This is what you usually want in a basic shell:

```c
pid_t pid = fork();
if (pid == 0) execve(...);     // child runs the command
waitpid(pid, &status, 0);      // parent sleeps until command finishes
// now show the next prompt
```

The shell has nothing useful to do while `ls` runs, so sleeping is the right call.

##### Mode 2: `options = WNOHANG` (non-blocking)

`WNOHANG` literally means **W**ait — but do **NO** **HANG**ing. It tells `waitpid`: *"check if a child has finished, but if none has, don't sleep — return right away."*

The return value tells you which case you're in:

| Return value | Meaning                                              |
|--------------|------------------------------------------------------|
| `> 0`        | the child finished; `status` is filled in            |
| `0`          | child is still running; come back later              |
| `< 0`        | error (e.g., no such child)                          |

##### Why would you ever want non-blocking?

Imagine your shell launches a background job:

```
    minishell$ sleep 60 &       <- the & means "run in background"
    minishell$ ls               <- I want to keep using the shell
```

If you used blocking `waitpid`, your shell would freeze for 60 seconds and the user couldn't type `ls`. So instead, the shell loops back to the prompt and **occasionally** checks "did any background child finish?" using `waitpid(-1, &status, WNOHANG)`. If the answer is "not yet," the shell shrugs and keeps doing its thing. If the answer is "yes, pid 4321 finished," the shell can print `[1]+ Done sleep 60` and reap the zombie.

##### Pizza-oven analogy

- **Blocking** = you sit on the kitchen floor staring at the oven door. You do nothing else until the pizza is ready. Boring, but you can't miss it.
- **Non-blocking** = every few minutes you walk over and check ("ready yet? — nope") then go back to watching TV. You stay productive, at the cost of having to remember to keep checking.

##### Common misconception

Beginners sometimes think "blocking = bad, non-blocking = efficient." That's backwards. A **blocked process consumes zero CPU**. A naive non-blocking polling loop, by contrast, can burn CPU spinning if you're not careful. Blocking is the *efficient* default; reach for `WNOHANG` only when you have a real reason — like needing to do other work in the meantime.

#### Useful macros to inspect `status`
| Macro                 | Meaning                          |
|-----------------------|----------------------------------|
| `WIFEXITED(s)`        | child called `exit()` normally   |
| `WEXITSTATUS(s)`      | the exit code (if normal exit)   |
| `WIFSIGNALED(s)`      | child was killed by a signal     |
| `WTERMSIG(s)`         | which signal killed it           |

#### Deep dive: what `status` actually is

Look at the type: `int status;`. It's just an `int`. But a child's "death story" actually carries several distinct facts:

- Did the child exit normally (calling `exit(n)`) or was it killed by a signal?
- If it exited normally, **what number** did it pass to `exit()`?
- If it was killed by a signal, **which signal**?

The kernel has to cram all of that into a single `int`. How? **Bit-packing**: different *bits* of the integer store different pieces of information.

```
    status (conceptually):

     31                        16 15        8 7 6 5 4 3 2 1 0
    +----------------------------+-----------+-----------------+
    |        (unused / flags)    | exit code | signal number   |
    +----------------------------+-----------+-----------------+
                                  ^           ^
                                  used if     used if killed
                                  exited      by signal
                                  normally
```

So `status` is **not** "the exit code." It's a packed struct pretending to be an `int`, where some bits mean one thing and other bits mean something else, depending on which kind of death happened.

If you naively did `printf("%d\n", status)` after a child called `exit(2)`, you would *not* see `2`. You'd see `512` — because the `2` is sitting up in the high byte, not the low byte. (Shifting a number left by 8 bits is the same as multiplying by 256, and `2 * 256 = 512`.) This confuses every beginner exactly once.

#### Why the macros exist

You could in principle write the bit-fiddling yourself: `(status >> 8) & 0xff` to pull out the exit code. But:

1. The exact bit layout is **not portable** — Linux, macOS, BSD may differ.
2. It's error-prone and unreadable.

So POSIX gives you macros that do the bit-fiddling for you, with names that document intent:

- The **`WIF...`** macros are *yes/no questions* (predicates).
- The other macros are *getters* that only make sense if the matching `WIF...` question was true.

Calling `WEXITSTATUS(status)` when `WIFEXITED(status)` is **false** is meaningless — you'd be reading bits that don't represent an exit code in that scenario. The macros don't crash, they just return garbage.

#### The decision tree

Because `status` describes one of several mutually-exclusive scenarios, the correct pattern is **ask first, then extract**:

```
    waitpid(pid, &status, 0);

         is WIFEXITED(status) true?
                    |
            yes ----+---- no
             |              |
    child called         is WIFSIGNALED(status) true?
    exit(n) normally              |
             |             yes ---+--- no
             |              |             |
    WEXITSTATUS(status)  child was    something else
    gives you n          killed by    (stopped, etc.)
                         a signal
                              |
                    WTERMSIG(status)
                    gives you the signal number
```

#### Worked example: child calls `exit(7)`

```
    status raw   = 1792      (7 * 256 — the 7 lives in the high byte)
    WIFEXITED    = 1         (yes, exited normally)
    WEXITSTATUS  = 7         (macro shifts the high byte back down)
    WIFSIGNALED  = 0         (no, it wasn't killed by a signal)
```

Roughly, `WEXITSTATUS` does the inverse of what the kernel did:

```
    kernel:        status = (exit_code << 8) | ...other stuff...
    WEXITSTATUS:   exit_code = (status >> 8) & 0xff
```

#### Why this matters for a shell

In bash, `$?` holds the exit status of the last command. Try this:

```
    $ ls /nonexistent
    ls: cannot access '/nonexistent': No such file or directory
    $ echo $?
    2
    $ sleep 100
    ^C                  <- you press Ctrl-C
    $ echo $?
    130
```

Notice the second case: `130`. That's not from `WEXITSTATUS` — `sleep` never called `exit()`, it was killed by `SIGINT`. Bash uses the convention `128 + signal_number`, and `SIGINT` is signal `2`, so `128 + 2 = 130`.

So when **your** minishell needs to set its own `$?`, you'll need to:

1. Inspect `status` from `waitpid`.
2. Decide which "kind of death" it was using `WIFEXITED` / `WIFSIGNALED`.
3. Extract the right number with `WEXITSTATUS` or `WTERMSIG`.
4. Combine them appropriately (`128 + sig` for the signal case).

#### Vocabulary trap: "wait" vs "reap"

In Unix-speak, **"to wait" for a process means specifically "to call `wait`/`waitpid` and collect its exit status,"** not just "to pause." A **zombie** is not a child whose parent forgot to pause — it's a child whose parent forgot to **reap** (i.e., never successfully called `wait`/`waitpid` on it). Even a parent that pauses for an hour with `sleep(3600)` will create a zombie if it never calls `waitpid`.

#### Example
```c
int status;
waitpid(pid, &status, 0);
if (WIFEXITED(status)) {
    printf("child exited normally with code %d\n", WEXITSTATUS(status));
} else if (WIFSIGNALED(status)) {
    printf("child was killed by signal %d\n", WTERMSIG(status));
}
```

---

### `wait3` and `wait4`

```c
pid_t wait3(int *status, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```

#### What they do
Same as `wait`/`waitpid`, but additionally fill in a `struct rusage` with **resource usage** statistics for the child: CPU time used, memory peak, page faults, etc.

`wait3` waits for any child; `wait4` lets you pick.

#### Example
```c
struct rusage ru;
int status;
wait4(pid, &status, 0, &ru);
printf("user CPU time: %ld.%06ld s\n",
       ru.ru_utime.tv_sec, ru.ru_utime.tv_usec);
```

---

### `execve`

```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

#### What it does
Replaces the current process's memory with a new program loaded from `pathname`. If it succeeds, your old code is gone — execution starts at the new program's `main`. It only returns on **failure** (returns `-1`).

- `argv` is the argument array (`argv[0]` is conventionally the program name; the array must end with `NULL`).
- `envp` is the environment array (`KEY=VALUE` strings, ending with `NULL`).

#### How it works internally
The kernel:
1. Reads the executable file.
2. Wipes the process's memory.
3. Loads the new code/data.
4. Sets up the stack with `argv` and `envp`.
5. Jumps to the new program's entry point.

```
    Before execve:          After execve:
    [shell process]         [ls process]
    PID=200                 PID=200   <- same PID!
    code: shell             code: ls
```

#### Example: fork + execve = run a command
```c
pid_t pid = fork();
if (pid == 0) {
    char *args[] = {"/bin/ls", "-l", NULL};
    char *env[]  = {NULL};
    execve("/bin/ls", args, env);
    perror("execve");          // only reached on error
    exit(1);
}
wait(NULL);
```

---

### `dup`

```c
int dup(int oldfd);
```

#### What it does
Creates a copy of `oldfd`. The new fd is the lowest unused number. Both fds refer to the **same** open file.

#### Example
```c
int fd = open("out.txt", O_WRONLY | O_CREAT, 0644);
int copy = dup(fd);
write(copy, "hi\n", 3);   // writes to out.txt
```

---

### `dup2`

```c
int dup2(int oldfd, int newfd);
```

#### What it does
Like `dup`, but you choose the new fd number. If `newfd` was already open, it's closed first. Used for **redirection**.

#### Example: redirect stdout to a file
```c
int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
dup2(fd, 1);          // fd 1 (stdout) now points to out.txt
close(fd);
printf("this goes into out.txt\n");
```

```
    Before dup2:               After dup2(fd, 1):
    fd 1 -> terminal           fd 1 -> out.txt
    fd 3 -> out.txt            fd 3 -> out.txt
```

---

### `pipe`

```c
int pipe(int pipefd[2]);
```

#### What it does
Creates a **pipe**: a one-way data channel inside the kernel. Fills `pipefd[0]` with the read end and `pipefd[1]` with the write end.

```
    pipefd[1]   ===bytes==>   pipefd[0]
    (write)                    (read)
```

Used together with `fork` + `dup2` to connect commands like `ls | wc`.

#### Example
```c
int p[2];
pipe(p);
if (fork() == 0) {            // child = writer
    dup2(p[1], 1);
    close(p[0]); close(p[1]);
    execlp("ls", "ls", NULL);
}
if (fork() == 0) {            // child = reader
    dup2(p[0], 0);
    close(p[0]); close(p[1]);
    execlp("wc", "wc", "-l", NULL);
}
close(p[0]); close(p[1]);
wait(NULL); wait(NULL);
```

---

### `exit`

```c
void exit(int status);
```

#### What it does
Ends the current process. `status` is returned to the parent (visible via `WEXITSTATUS`). Conventionally, `0` = success, non-zero = failure.

Before terminating, it flushes stdio buffers and runs any functions registered with `atexit`.

---

<a name="signals"></a>
## 6. Signals

A **signal** is a small notification the kernel sends to a process — like an interrupt. Examples: `SIGINT` (Ctrl-C), `SIGTERM` (polite kill), `SIGKILL` (forced kill, can't be caught), `SIGCHLD` (a child exited).

---

### `signal`

```c
void (*signal(int signum, void (*handler)(int)))(int);
```

#### What it does
Installs `handler` as the function to call when the process receives `signum`. Special values:
- `SIG_DFL` : restore default behavior
- `SIG_IGN` : ignore the signal

#### Example
```c
void on_sigint(int sig) { (void)sig; write(1, "ouch\n", 5); }

int main(void) {
    signal(SIGINT, on_sigint);
    while (1) pause();
}
```
Press Ctrl-C: prints `ouch` instead of killing the program.

> Note: `signal` has historically inconsistent behavior across systems. `sigaction` is preferred for new code.

---

### `sigaction`

```c
int sigaction(int signum, const struct sigaction *act,
              struct sigaction *oldact);
```

#### What it does
A more powerful, portable replacement for `signal`. Lets you set the handler, a signal mask (signals to block while the handler runs), and flags (e.g., `SA_RESTART` to auto-restart interrupted system calls).

#### Example
```c
struct sigaction sa;
sa.sa_handler = on_sigint;
sigemptyset(&sa.sa_mask);
sa.sa_flags = SA_RESTART;
sigaction(SIGINT, &sa, NULL);
```

---

### `sigemptyset`

```c
int sigemptyset(sigset_t *set);
```

Initializes `set` to contain **no** signals. A `sigset_t` is a bitmask saying "these signals are in the set."

---

### `sigaddset`

```c
int sigaddset(sigset_t *set, int signum);
```

Adds `signum` to `set`.

#### Example: block SIGINT and SIGQUIT inside a handler
```c
sigset_t mask;
sigemptyset(&mask);
sigaddset(&mask, SIGINT);
sigaddset(&mask, SIGQUIT);
sa.sa_mask = mask;
```

---

### `kill`

```c
int kill(pid_t pid, int sig);
```

#### What it does
Sends signal `sig` to process `pid`. Despite the name, it doesn't necessarily kill — `sig` could be `SIGSTOP`, `SIGCONT`, `0` (just check existence), etc.

#### Example
```c
kill(child_pid, SIGTERM);     // ask the child to terminate
```

---

<a name="filesystem"></a>
## 7. Filesystem

---

### `getcwd`

```c
char *getcwd(char *buf, size_t size);
```

#### What it does
Writes the absolute path of the current working directory into `buf`. Returns `buf` on success, `NULL` on error.

#### Example
```c
char buf[4096];
if (getcwd(buf, sizeof(buf)))
    printf("cwd = %s\n", buf);
```

---

### `chdir`

```c
int chdir(const char *path);
```

#### What it does
Changes the current working directory of the process. Returns `0` on success.

#### Example: implementing `cd`
```c
if (chdir("/tmp") < 0) perror("cd");
```

---

### `stat`, `lstat`, `fstat`

```c
int stat (const char *path, struct stat *st);
int lstat(const char *path, struct stat *st);
int fstat(int fd,           struct stat *st);
```

#### What they do
All three fill in a `struct stat` with metadata about a file: size, permissions, owner, modification time, type (regular file, directory, symlink, ...).

| Function | Takes  | Symlink behavior              |
|----------|--------|-------------------------------|
| `stat`   | path   | follows symlinks              |
| `lstat`  | path   | does **not** follow symlinks  |
| `fstat`  | fd     | (already have the file open)  |

#### Useful fields and macros
```c
struct stat st;
stat("file.txt", &st);
st.st_size;            // size in bytes
st.st_mode;            // permission bits + type
S_ISREG(st.st_mode);   // is regular file?
S_ISDIR(st.st_mode);   // is directory?
S_ISLNK(st.st_mode);   // is symlink?  (use with lstat)
```

#### Example
```c
struct stat st;
if (stat("file.txt", &st) == 0)
    printf("size = %lld bytes\n", (long long)st.st_size);
```

---

### `unlink`

```c
int unlink(const char *path);
```

#### What it does
Removes a name from the filesystem. If that was the last name pointing at the file's data, the data is freed (when the last open fd to it also closes).

#### Example
```c
unlink("temp.txt");   // delete the file
```

---

<a name="directories"></a>
## 8. Directories

Include `<dirent.h>`.

---

### `opendir`

```c
DIR *opendir(const char *name);
```

#### What it does
Opens a directory for reading its contents. Returns a `DIR *` handle, or `NULL` on error.

---

### `readdir`

```c
struct dirent *readdir(DIR *dirp);
```

#### What it does
Returns the next entry in the directory, or `NULL` at end / on error. The most useful field is `d_name` (the filename).

---

### `closedir`

```c
int closedir(DIR *dirp);
```

Frees the resources used by `opendir`.

#### Example: list a directory
```c
DIR *d = opendir(".");
struct dirent *entry;
while ((entry = readdir(d)) != NULL)
    printf("%s\n", entry->d_name);
closedir(d);
```

---

<a name="errors"></a>
## 9. Errors

---

### `strerror`

```c
char *strerror(int errnum);
```

Converts an errno code (e.g., `ENOENT`) into a human-readable string (e.g., `"No such file or directory"`).

```c
int fd = open("nope", O_RDONLY);
if (fd < 0) printf("error: %s\n", strerror(errno));
```

---

### `perror`

```c
void perror(const char *s);
```

Prints `s`, then `": "`, then the message for the current `errno`, then a newline — to stderr.

```c
if (open("nope", O_RDONLY) < 0) perror("open");
// prints:  open: No such file or directory
```

---

<a name="terminals"></a>
## 10. Terminals

---

### `isatty`

```c
int isatty(int fd);
```

Returns `1` if `fd` refers to a terminal, `0` otherwise. Useful to decide whether to print colored prompts, etc.

```c
if (isatty(0)) printf("input is a terminal\n");
```

---

### `ttyname`

```c
char *ttyname(int fd);
```

Returns the path of the terminal device for `fd` (e.g., `/dev/ttys001`), or `NULL` if `fd` isn't a terminal.

---

### `ttyslot`

```c
int ttyslot(void);
```

Returns the index of the current terminal in the system's tty file (legacy). Rarely used in modern code.

---

### `ioctl`

```c
int ioctl(int fd, unsigned long request, ...);
```

#### What it does
The "everything else" system call for devices: lets you send special commands to a file descriptor that don't fit `read`/`write`. Examples: get terminal window size, set serial port speed.

#### Example: get terminal width and height
```c
#include <sys/ioctl.h>
struct winsize ws;
ioctl(1, TIOCGWINSZ, &ws);
printf("rows=%d cols=%d\n", ws.ws_row, ws.ws_col);
```

---

<a name="environment"></a>
## 11. Environment

---

### `getenv`

```c
char *getenv(const char *name);
```

Returns the value of environment variable `name`, or `NULL` if not set. Don't modify or free the returned string.

```c
char *home = getenv("HOME");
if (home) printf("home = %s\n", home);
```

---

### `tcgetattr`

```c
int tcgetattr(int fd, struct termios *termios_p);
```

Reads the current settings of a terminal (canonical/raw mode, echo on/off, special characters, etc.) into `termios_p`.

---

### `tcsetattr`

```c
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
```

Applies new terminal settings. `optional_actions` is usually `TCSANOW` (apply immediately).

#### Example: turn off echo (for password input)
```c
struct termios old, new;
tcgetattr(0, &old);
new = old;
new.c_lflag &= ~ECHO;          // clear echo bit
tcsetattr(0, TCSANOW, &new);
// ... read password ...
tcsetattr(0, TCSANOW, &old);   // restore
```

---

<a name="termcap"></a>
## 12. Termcap

The **termcap** library provides portable access to terminal capabilities (clear screen, move cursor, etc.) without hardcoding escape sequences. Different terminals (xterm, vt100, ...) use different sequences; termcap looks them up in a database keyed by the `TERM` environment variable.

Link with `-ltermcap` (or `-lncurses`). Include `<termcap.h>`.

---

### `tgetent`

```c
int tgetent(char *bp, const char *name);
```

Loads the termcap entry for terminal `name` (usually `getenv("TERM")`) into buffer `bp`. Returns `1` on success. Must be called before any other tg* function.

```c
char buf[2048];
tgetent(buf, getenv("TERM"));
```

---

### `tgetflag`

```c
int tgetflag(char *id);
```

Returns `1` if the terminal has the boolean capability `id`, else `0`. Example: `"am"` = automatic margins.

---

### `tgetnum`

```c
int tgetnum(char *id);
```

Returns the numeric capability `id`, or `-1` if absent. Examples: `"co"` (columns), `"li"` (lines).

```c
int cols = tgetnum("co");
```

---

### `tgetstr`

```c
char *tgetstr(char *id, char **area);
```

Returns the string capability `id` (an escape sequence), or `NULL`. `area` points into a scratch buffer the function uses for storage.

Common ids:
| id   | meaning           |
|------|-------------------|
| `cl` | clear screen      |
| `cm` | move cursor       |
| `ce` | clear to EOL      |
| `so` | start standout    |
| `se` | end standout      |

---

### `tgoto`

```c
char *tgoto(const char *cap, int col, int row);
```

Takes a cursor-movement capability (like the one returned for `"cm"`) and fills in the column/row to produce the actual escape sequence to send.

---

### `tputs`

```c
int tputs(const char *str, int affcnt, int (*putc)(int));
```

Sends a termcap string to the terminal, handling any padding delays it requires. `affcnt` is the number of lines affected (used for delay calculation). `putc` is a function that writes one char (often `putchar`).

#### Example: clear the screen portably
```c
char buf[2048], area[2048];
char *area_p = area;
tgetent(buf, getenv("TERM"));
char *cl = tgetstr("cl", &area_p);
tputs(cl, 1, putchar);
```

#### Example: move cursor to column 10, row 5
```c
char *cm = tgetstr("cm", &area_p);
tputs(tgoto(cm, 10, 5), 1, putchar);
```

---

## Putting it all together: a tiny shell loop

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void) {
    char *line;
    while ((line = readline("minishell$ ")) != NULL) {
        if (*line) add_history(line);
        pid_t pid = fork();
        if (pid == 0) {
            char *argv[] = { line, NULL };
            char *envp[] = { NULL };
            execve(line, argv, envp);
            perror("execve");
            exit(1);
        }
        waitpid(pid, NULL, 0);
        free(line);
    }
    rl_clear_history();
    return 0;
}
```

This is the skeleton: read a line, fork, execve in the child, wait in the parent, repeat. Every function in this document fits somewhere into expanding this skeleton into a real shell.
