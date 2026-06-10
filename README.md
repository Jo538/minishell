*This project has been created as part of the 42 curriculum by bribot, jchartie.*

# Minishell

## Description

Minishell is a simple Unix shell written in C, inspired by `bash`. The goal of
the project is to gain a deep, hands-on understanding of how a shell works
internally — how a line of text typed at a prompt is turned into running
processes connected by pipes and redirections.

The shell reads a command line, splits it into tokens, expands variables and
quotes, builds an abstract representation of the pipeline, and then forks the
necessary child processes to execute it while respecting input/output
redirections and the standard exit-status conventions.

Implemented features (mandatory part):

- Interactive prompt with command history (via `readline`).
- Command execution using `PATH` lookup, or via relative/absolute paths.
- Single quotes `'...'` (no interpretation) and double quotes `"..."`
  (interpretation except for `$`).
- Environment variable expansion (`$VAR`) and the special `$?` (exit status of
  the last foreground pipeline).
- Redirections: `<`, `>`, `>>`, and heredoc `<<`.
- Pipes `|` with an arbitrary number of stages.
- Signal handling matching `bash` in interactive mode:
  - `Ctrl-C` displays a fresh prompt on a new line.
  - `Ctrl-D` exits the shell.
  - `Ctrl-\` is ignored.
- Built-in commands: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`,
  `exit`.

## Instructions

### Requirements

- A C compiler (`cc` / `gcc` / `clang`).
- `make`.
- The GNU `readline` library, including its development headers.
  - On macOS (Homebrew): `brew install readline` — the Makefile already points
    to `/opt/homebrew/opt/readline` for both the headers and the library.
  - On Linux (Debian/Ubuntu): `sudo apt install libreadline-dev`.

### Build

From the project root:

```sh
make           # builds the `minishell` binary
make clean     # removes object files
make fclean    # removes object files, libft archive, and the binary
make re        # fclean + make
```

The Makefile first builds `libft` (in `libft/`) and then links it together with
the project objects into the final `minishell` executable. Compilation uses
`-Wall -Wextra -Werror`.

### Run

```sh
./minishell
```

You will land on an interactive prompt. Type commands as you would in `bash`.
Use `exit` or `Ctrl-D` to leave the shell.

### Project layout

```
includes/        public header (minishell.h)
libft/           the 42 libft, used by the project
src/
  main.c          entry point and main read/eval/print loop
  signals.c       signal handlers
  lexer/          tokenization of the input line
  parsing/        quote / variable expansion and AST construction
  check_if_good/  syntactic validation of the parsed command line
  executor/       process creation, redirections, pipes, heredocs
  env/            environment / built-ins (cd, pwd, env, export, unset, echo, exit)
Makefile
```

## Resources

### Documentation and references

- `man bash` — the reference behavior we tried to mimic.
- `man 3 readline` — prompt, line editing, and history.
- `man 2 fork`, `man 2 execve`, `man 2 wait`, `man 2 waitpid`, `man 2 pipe`,
  `man 2 dup2`, `man 2 open` — the system calls at the heart of the executor.
- `man 7 signal`, `man 2 sigaction` — for the signal-handling layer.
- POSIX shell command language specification —
  <https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html>
- *Advanced Programming in the UNIX Environment* (Stevens & Rago) — chapters on
  processes, signals, and terminal I/O.

### Use of AI

AI assistance was used during this project for the
following, non-code-generating tasks:

- Clarifying concepts before writing code (process groups, controlling
  terminals, the exact semantics of `readline` signal handling, the difference
  between interactive and non-interactive shells).
- Reading and explaining sections of the `bash` and POSIX documentation.
- Drafting and proofreading this README.

