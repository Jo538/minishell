*This project has been created as part of the 42 curriculum by <login1>, <login2>.*

## Description

`minishell` is a small Unix shell written in C, inspired by `bash`. The goal of
the project is to learn how a shell turns a line of text into running processes:
lexing the input, building an abstract syntax tree, expanding variables, and
finally orchestrating `fork`, `execve`, `pipe`, `dup2`, and `waitpid` to make
programs actually run.

Supported (mandatory):

- Interactive prompt with persistent history via `readline`
- Pipes (`|`) and redirections (`<`, `>`, `<<`, `>>`)
- Environment-variable expansion (`$VAR`) and the special `$?`
- Single (`'...'`) and double (`"..."`) quoting rules
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`) like bash
- Built-ins: `echo` (`-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Command lookup via `$PATH`, plus relative and absolute paths

## Instructions

Build the shell:

```
make
```

Run it:

```
./minishell
```

Clean rules:

```
make clean   # remove object files
make fclean  # remove object files, libft archive, and the binary
make re      # fclean + build
```

The project depends on GNU `readline`. On macOS it is picked up from
`/opt/homebrew/opt/readline`. On Linux it is linked from the system path.

## Resources

Reference material we relied on while building this:

- The Bash Reference Manual — sections 3.5 (Shell Expansions) and 3.7
  (Executing Commands).
- The POSIX Shell specification — for settling edge-case behaviour.
- `man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, `man 2 waitpid`,
  `man 3 readline` — the system-call and library references.
- Stevens, *Advanced Programming in the UNIX Environment* — chapters on
  process control and IPC.
- `docs/shell_architecture.md` and `docs/c_functions_explained.md` in this
  repository — our own notes that we wrote while learning.

### Use of AI

We used AI assistants to help:

- Audit the codebase for bugs and design issues, and propose fixes.
- Explain `readline` / signal interactions when the documentation was thin.
- Talk through edge cases in the lexer and the expander.
