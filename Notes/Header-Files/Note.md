# C Header Files: Calculator Example

## 1. What is a header file?

A C header file (`.h`) contains declarations that can be shared by multiple source files.

For example, `calculator.h` tells other files which calculator functions are available, without containing their implementations.

A typical project:

```text
Calculator/
├── main.c
├── calculator.c
└── calculator.h
```

## 2. The three files

### `calculator.h` — declarations

```c
#ifndef CALCULATOR_H
#define CALCULATOR_H

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);

#endif
```

The function prototypes declare each function's name, return type, and parameters.

The `#ifndef`, `#define`, and `#endif` lines are **header guards**. They prevent the header from being processed more than once within the same translation unit.

### `calculator.c` — implementations

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

This file contains the actual function definitions.

### `main.c` — using the functions

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

`main.c` includes the header so the compiler knows the declarations of the functions it calls.

## 3. Compile and run

Compile both `.c` files together:

```bash
gcc main.c calculator.c -o calculator
```

Run on Linux or macOS:

```bash
./calculator
```

Expected output:

```text
15
5
50
```

If you omit `-o`, GCC normally names the executable `a.out`:

```bash
gcc main.c calculator.c
./a.out
```

`-o calculator` specifies the output filename. On Linux and macOS, executables commonly have no extension; on Windows, they commonly use `.exe`.

## 4. What happens behind the scenes?

When you run:

```bash
gcc main.c calculator.c -o calculator
```

GCC performs several stages:

1. **Preprocessing:** Each `.c` file is processed separately. Its `#include "calculator.h"` directive is expanded with the header's contents.
2. **Compilation:** Each source file is compiled into an object file. Conceptually, this produces `main.o` and `calculator.o`.
3. **Linking:** The linker combines the object files. It resolves the call to `add()` in `main.o` using the definition provided by `calculator.o`.
4. **Output:** The result is one executable named `calculator`.

Conceptually:

```text
main.c  ── preprocess + compile ──> main.o
                                      \
                                       ├── linker ──> calculator
                                      /
calculator.c ─ preprocess + compile ─> calculator.o
```

### Important: `#include` is not the linker

`#include` is handled by the **preprocessor**. It makes declarations from the header visible to a source file by inserting the header's contents during preprocessing.

The **linker** is a later stage. It connects references to functions and variables with their definitions in object files or libraries.

## 5. Why can multiple `.c` files include the same header?

Both `main.c` and `calculator.c` can include `calculator.h`. Each source file is preprocessed independently, so each gets the declarations it needs.

Header guards do not stop the header from being included in different `.c` files. They prevent repeated inclusion within one translation unit.

It is normal for many `.c` files to include the same header.

## 6. What if a function has no implementation?

Suppose `calculator.h` declares:

```c
int add(int a, int b);
```

But no compiled source file defines `add()`.

`main.c` may compile because it has seen the declaration. The **linker** will then report an error such as:

```text
undefined reference to `add'
```

A declaration tells the compiler that a function exists; it does not provide the function's implementation.

## 7. What if two `.c` files implement the same function?

For example, if both `main.c` and `calculator.c` define an externally linked function named `add()`, linking them together will normally produce a multiple-definition error.

For an ordinary externally linked function, provide one definition across the program.

## 8. Can an implementation go in a header file?

Yes, but be careful.

If a header defines a normal externally linked function and that header is included by multiple `.c` files, each translation unit can produce a definition. Linking them can cause a multiple-definition error.

For small functions defined in headers, a common pattern is:

```c
static inline int add(int a, int b) {
    return a + b;
}
```

`static` gives each translation unit its own internal-linkage function. `inline` permits inline substitution as an optimization, but does not guarantee it.

For larger projects, the usual convention is:

- `.h`: declarations (the module's interface)
- `.c`: implementations (the module's implementation)

## 9. Compile in separate steps

You can compile each source file into an object file:

```bash
gcc -c main.c -o main.o
gcc -c calculator.c -o calculator.o
```

Then link the object files:

```bash
gcc main.o calculator.o -o calculator
```

The `-c` option compiles without performing the final linking step.

You normally do **not** pass header files as separate source files to GCC. Include them from the `.c` files that need them.

## 10. Key terms to remember

| Term | Meaning |
|---|---|
| Header file (`.h`) | Shared declarations, types, macros, and sometimes inline definitions |
| Source file (`.c`) | C code containing function definitions and other implementation details |
| Function declaration | Describes a function's name, return type, and parameters |
| Function definition | Provides the function's implementation |
| Preprocessor | Handles directives such as `#include` and `#define` |
| Object file (`.o`) | Compiled code that has not yet been linked into the final executable |
| Linker | Resolves references and combines object files and libraries |
| Executable | The resulting runnable program |
| `-o` | GCC option used to specify the output filename |
| `-c` | GCC option used to compile without linking |

## Main takeaway

A header file is an **interface or contract**: it tells other source files what functions and types are available.

A source file usually provides the actual implementation. The compiler checks each source file, and the linker connects function calls to their definitions when building the final executable.
