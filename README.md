*This project has been created as part of the 42 curriculum by thhtun & pytun.*

## Description

**minishell** is a minimal shell implementation in C, created as part of the 42 School curriculum. It mimics core bash functionality, including:

- Interactive shell prompt with command history
- Command execution with PATH resolution and relative/absolute paths
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Environment variable expansion (`$VAR` and `$?`)
- Input/output redirections: `<`, `>`, `>>`
- Heredoc syntax: `<<DELIMITER`
- Pipe operator: `|`
- Quote handling: single quotes (`'`) and double quotes (`"`)
- Signal handling: Ctrl+C, Ctrl+D, Ctrl+\

## Instructions

### Compilation

```bash
make           # Build minishell
make clean     # Remove object files
make fclean    # Remove all build artifacts
make re        # Full rebuild
```

### Running

```bash
./minishell
```

Once inside, use standard shell commands. Type `exit` or press Ctrl+D to quit.

### Testing

```bash
sh tests/minishell_tests.sh
```

This runs a suite of automated tests covering builtins, expansions, redirections, heredocs, pipes, and signal handling.

## Resources

- **POSIX Shell Standard**: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/sh.html
- **GNU Bash Manual**: https://www.gnu.org/software/bash/manual/
- **readline(3)**: `man readline` (interactive input library)
- **Process Management**: `man 2 fork`, `man 2 execve`, `man 2 wait`
- **File Descriptors & I/O**: `man 2 dup2`, `man 2 pipe`
- **Environment Variables**: `man 3 getenv`, `man environ`

### AI Usage

AI was used to assist with:
- Code structure review and cleanup of redundant implementations
- Debugging and testing of edge cases in variable expansion and quoting
- Documentation and README generation
- Refactoring signal handling to meet strict requirements

All core shell logic (lexing, parsing, execution, builtin commands, redirections, pipes, and heredoc handling) was written from scratch following the subject specification.

