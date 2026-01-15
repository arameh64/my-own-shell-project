# Ashell

Ashell is a custom Unix-like shell written entirely in **C**, developed as a low-level programming exercise to better understand how traditional shells work internally.  
The project focuses on manual memory management, process control, parsing, and execution flow — similar in style to older, minimal shells.

This project is not intended to be a full Bash replacement. It is built purely for learning and training purposes.

---

## Overview

Ashell implements a basic command-line interpreter with support for:

- Tokenization and parsing
- Built-in commands
- External command execution
- Configuration loading
- Command history
- Arrow key navigation
- Proper memory cleanup

All logic is written manually in C without using high-level abstractions.

---

## Build & Compilation

The project includes a build script to compile everything automatically.

### Using `build.sh`

```bash
chmod +x build.sh
./build.sh

What the script does:

    Cleans old object files

    Compiles all source files

    Links everything into the final ashell binary

After successful compilation, you can run the shell with:

./ashell

Project Structure

Below is a brief description of each core file in the project.
main.c

Entry point of the program.
Initializes the shell, loads configuration, and starts the main input loop.
reader.c

Handles reading input from the user.
Manages raw input, buffering, and passing lines to the tokenizer.
tokenizer.c

Splits raw input into tokens.
Responsible for recognizing words, pipes, redirections, and special characters.
parser.c

Converts tokens into command structures.
Builds the internal representation used by the executor.
executor.c

Executes parsed commands.
Handles pipelines, redirections, background execution, and process control.
externals.c

Handles execution of external programs using fork, execve, and related system calls.
built_ins.c

Contains all built-in shell commands such as cd, exit, and others.
These commands are executed without spawning new processes.
history.c

Manages command history.
Stores previous commands and allows navigation through them.
arrow_browsing.c

Implements arrow key navigation.
Handles moving through command history using keyboard input.
config.c

Loads and processes the shell configuration file (similar to .bashrc).
Executes startup commands before entering the main loop.
free.c

Centralized memory cleanup logic.
Ensures all allocated structures are properly freed to avoid leaks.
includes.h

Main header file.
Contains all struct definitions, function prototypes, and shared includes.
versionlog.md

Tracks version changes and updates to the project.