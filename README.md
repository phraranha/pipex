# Pipex

## Overview

**Pipex** is a C program that replicates a shell pipe functionality, allowing the user to execute two commands in sequence, using the output of the first command as the input for the second command. The program uses Unix system calls to handle processes, pipes, and file descriptors.

---

## Usage

```bash
./pipex infile "cmd1" "cmd2" outfile
```

### Parameters
- **infile**: The input file to be read.
- **cmd1**: The first command to execute.
- **cmd2**: The second command to execute, which takes the output of `cmd1` as input.
- **outfile**: The output file where the result of `cmd2` will be written.

### Example

```bash
./pipex input.txt "grep keyword" "wc -l" output.txt
```

This command searches for the word "keyword" in `input.txt` and counts the lines containing the keyword, saving the result in `output.txt`.

---

## Features

1. **Error Handling**:
   - Provides descriptive error messages when a file or command fails to execute.
   - Handles memory leaks by freeing allocated memory before exiting.
   - Closes file descriptors to avoid resource exhaustion.

2. **Quoted Arguments**:
   - Supports commands with quoted arguments (e.g., `"echo 'hello world'"`).

3. **Environment Variable Parsing**:
   - Parses the `PATH` environment variable to locate executable commands.

4. **Custom Split Functionality**:
   - Includes a robust `ft_split_quoted` function to handle commands with spaces or quotes.

---

## Implementation Details

### Key Functions

1. **`main`**:
   - Validates input arguments.
   - Creates a pipe and forks processes to execute commands.

2. **`execute_command`**:
   - Parses the command and finds its executable path using `find_command_path`.
   - Executes the command using `execve`.

3. **`parse_command`**:
   - Splits the command string into arguments, respecting quoted segments.

4. **`find_command_path`**:
   - Searches for the executable in directories specified in the `PATH` environment variable.

5. **`ft_split_quoted`**:
   - Splits strings into words, handling quoted segments correctly.

6. **`open_input_file`** and **`open_output_file`**:
   - Safely open files for reading or writing, handling errors appropriately.

### System Calls Used
- `pipe()`: Creates a pipe for inter-process communication.
- `fork()`: Creates child processes.
- `dup2()`: Redirects file descriptors.
- `execve()`: Executes a command.
- `open()`, `close()`: Manages file descriptors.

---

## Error Handling

The program ensures robust error handling:
- Missing or invalid arguments: Displays usage instructions.
- File errors (e.g., not found, no permissions): Displays a descriptive error message.
- Command errors (e.g., not found, execution failure): Informs the user and exits gracefully.

---

## Compilation

Compile the program using the provided Makefile:

```bash
make
```

This generates the `pipex` executable.

