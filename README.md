*This project was created as part of the 42 curriculum by paduarte.*

# get_next_line

## Description

The goal of this project is to implement a function capable of reading and returning a line from a file descriptor, one line at a time.

Function prototype:

```c
char	*get_next_line(int fd);
```

The function must:
- Read from a file descriptor using `read()`
- Return one line per function call
- Include the newline character (`\n`) when present
- Preserve unread content between calls using a static variable
- Return `NULL` on EOF or error

This project introduces one of the most important concepts in C programming:
- static variables

It also reinforces:
- dynamic memory allocation
- file descriptor handling
- string manipulation
- memory management
- buffer-based reading

---

# Instructions

## Compilation

Compile the project with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c
```

Example with another buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=3 *.c
```

The project must compile both with and without the `-D BUFFER_SIZE=n` flag.

---

# Usage Example

```c
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("README.md", O_RDONLY);

	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}

	close(fd);
	return (0);
}
```

---

# How the Algorithm Works

The implementation is divided into three main stages:

## 1. Reading and Storing

The function continuously reads chunks from the file descriptor using a temporary buffer of size `BUFFER_SIZE`.

These chunks are appended to a persistent static buffer until:
- a newline (`\n`) is found
- or EOF is reached

Example:

```txt
BUFFER_SIZE = 3

Read #1 -> "Wel"
Read #2 -> "com"
Read #3 -> "e!\n"
```

Accumulated static buffer:

```txt
"Welcome!\n"
```

---

## 2. Extracting the Line

Once a newline is found, the function extracts the current line from the accumulated buffer.

Example:

```txt
Static buffer:
"Welcome!\nThis is the next line"
```

Returned line:

```txt
"Welcome!\n"
```

---

## 3. Saving the Remaining Content

After extracting the line, the remaining content is stored back into the static buffer for the next function call.

Remaining buffer:

```txt
"This is the next line"
```

This allows the function to continue reading exactly where it stopped previously.

---

# Files

```txt
get_next_line.c
get_next_line_utils.c
get_next_line.h
```

---

# Authorized Functions

- `read`
- `malloc`
- `free`

---

# Important Notes

- The returned line must include the newline (`\n`) when present
- The implementation must work with files and standard input (`stdin`)
- The project must not leak memory
- Global variables are forbidden
- `lseek()` is forbidden

---

# Testing

Memory leaks were checked using:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./a.out
```

The function was tested with:
- very small buffer sizes (`1`)
- very large buffer sizes (`9999`)
- files with and without trailing newlines
- empty files
- multiple consecutive newlines

---

# Technical Decisions

## Why Use a Static Variable?

A static variable preserves its value between function calls.

This is essential because `get_next_line()` must remember:
- what has already been read
- what still remains unread after a newline

Without a static buffer, the function would lose the remaining content every time it returned a line.

---

# Memory Management

The implementation carefully:
- frees temporary buffers
- avoids memory leaks
- handles EOF correctly
- protects against invalid reads
- preserves leftovers safely between calls

---

# Resources

## Documentation

- https://man7.org/linux/man-pages/man2/read.2.html
- https://www.geeksforgeeks.org/static-variables-in-c/
- https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

## AI Usage

AI was used as a learning support tool to:
- concept clarification
- expanding the test suite
- formatting README

The implementation and debugging process were developed progressively through manual coding, testing, and iterative reasoning.