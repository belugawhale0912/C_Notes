# C Makefiles: Automating Compilation with GCC

## 1. What is a Makefile?

A **Makefile** is a file containing build rules used by the `make` build tool.

Instead of repeatedly typing long GCC commands, you can write the build instructions once and run:

```bash
make
```

Make reads the Makefile, checks dependencies, and runs the commands needed to build the target.

A Makefile is especially useful when a project contains many `.c` files.

## 2. A simple calculator project

Start with this project structure:

```text
Calculator/
├── main.c
├── calculator.c
├── calculator.h
└── Makefile
```

Example `calculator.h`:

```c
#ifndef CALCULATOR_H
#define CALCULATOR_H

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);

#endif
```

Example `calculator.c`:

```c
#include "calculator.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}
```

Example `main.c`:

```c
#include <stdio.h>
#include "calculator.h"

int main(void) {
    printf("%d\n", add(10, 5));
    printf("%d\n", subtract(10, 5));
    printf("%d\n", multiply(10, 5));

    return 0;
}
```

## 3. Your first Makefile

Create a file named exactly `Makefile` (usually with no file extension):

```makefile
calculator: main.c calculator.c
	gcc main.c calculator.c -o calculator
```

Run it from the project directory:

```bash
make
```

Then run the executable on Linux or macOS:

```bash
./calculator
```

Expected output:

```text
15
5
50
```

**Important:** The command under a Makefile rule must begin with a TAB character, not spaces. This is a common beginner mistake.

## 4. Understanding Makefile syntax

The basic rule format is:

```makefile
target: dependencies
	command
```

| Part | Meaning |
|---|---|
| Target | The file or task you want Make to build |
| Dependencies | Files required to build the target |
| Command | The shell command Make executes |

For example:

```makefile
calculator: main.c calculator.c
	gcc main.c calculator.c -o calculator
```

- `calculator` is the target.
- `main.c` and `calculator.c` are dependencies.
- The GCC command builds the executable.

Make normally considers a target out of date if it does not exist or if one of its dependencies is newer.

## 5. A more structured Makefile: compile and link separately

For a larger project, it is useful to compile each `.c` file into an object file (`.o`) and then link the object files.

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g

calculator: main.o calculator.o
	$(CC) main.o calculator.o -o calculator

main.o: main.c calculator.h
	$(CC) $(CFLAGS) -c main.c -o main.o

calculator.o: calculator.c calculator.h
	$(CC) $(CFLAGS) -c calculator.c -o calculator.o

.PHONY: clean
clean:
	rm -f *.o calculator
```

Now run:

```bash
make
```

Make builds the required object files and links them into `calculator`.

### Makefile variables

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g
```

- `CC` stores the compiler command.
- `CFLAGS` stores common C compiler options.

Use `$(...)` to refer to a Make variable:

```makefile
$(CC) $(CFLAGS) -c main.c -o main.o
```

Common GCC options:

| Option | Meaning |
|---|---|
| `-Wall` | Enables many common warnings |
| `-Wextra` | Enables additional warnings |
| `-g` | Includes debugging information |
| `-c` | Compiles without linking |
| `-o filename` | Sets the output filename |

## 6. Understanding dependencies

Consider this rule:

```makefile
main.o: main.c calculator.h
	gcc -Wall -Wextra -c main.c -o main.o
```

It means:

To build `main.o`, Make needs both `main.c` and `calculator.h`.

If either file changes, Make knows that `main.o` may need to be rebuilt.

The header is listed because `main.c` includes it and its declarations can affect compilation.

**Important:** Make does not automatically discover every header dependency in this basic example. You must list dependencies yourself, or use compiler-generated dependency files in larger projects.

## 7. Incremental compilation

One of Make's most useful features is **incremental compilation**.

Suppose the project contains:

```text
main.c
calculator.c
statistics.c
```

You build the project once. Later, you change only `calculator.c`.

With suitable dependency rules, Make can:

1. Recompile `calculator.c` into `calculator.o`.
2. Reuse the existing `main.o` and `statistics.o`.
3. Link the object files again to create an updated executable.

It does not need to recompile every unchanged source file.

Make generally uses file modification timestamps to decide whether a target needs rebuilding.

## 8. The `clean` target and `.PHONY`

A common Makefile rule is:

```makefile
.PHONY: clean

clean:
	rm -f *.o calculator
```

Run it with:

```bash
make clean
```

This removes generated object files and the executable. It does not remove your `.c` or `.h` source files.

`.PHONY` tells Make that `clean` is a task name, not a file that needs to be created.

Without `.PHONY`, a real file named `clean` could interfere with the rule.

## 9. The overall build process

When you run `make`, the workflow is conceptually:

```text
You edit .c or .h files
          |
          v
      Run `make`
          |
          v
 Make checks targets and dependencies
          |
          v
 Rebuild outdated object files
          |
          v
 Link object files with GCC
          |
          v
     Executable created
```

The stages involved in building C programs are:

1. **Preprocessing:** Handles directives such as `#include` and `#define`.
2. **Compilation:** Compiles each source file into object code.
3. **Linking:** Combines object files and libraries, resolving references between them.

Make coordinates the commands for these stages; it is not itself the C compiler or linker.

## 10. Compile manually versus using Make

Without a Makefile, you might run:

```bash
gcc -c main.c -o main.o
gcc -c calculator.c -o calculator.o
gcc main.o calculator.o -o calculator
```

With a Makefile, you can simply run:

```bash
make
```

To remove generated files:

```bash
make clean
```

## Main takeaway

A Makefile is a set of build instructions for the `make` tool.

- **Target:** What Make should build.
- **Dependencies:** What the target relies on.
- **Command:** How to build it.
- **Incremental build:** Make rebuilds outdated targets instead of blindly rebuilding everything.

For a small project, a simple Makefile can save repetitive typing. For a larger project, well-defined dependencies and reusable rules make builds easier to maintain.
