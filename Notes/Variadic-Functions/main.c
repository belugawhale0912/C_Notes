#include <stdio.h>
#include <stdarg.h>

// Variadic functions are functions that can accept a variable number of arguments
// The most famouse example in the C standard library is printf which can take a format string
// Followed by any number of additional arguments

// Key requirements for Variadic Functions
// - At least one fixed parameter: A variadic function must have at least one named,
//   fixed parameter before the ellipsis (...). The compiler uses this fixed parameter
//   to locate where the variable arguments begin on the stack
// - The ellpsis (...): Denotes that zero or more additional arguments may follow.

// Example: Custom Summation Function

// 'count' is the mandatory fixed parameter
int sum(int count, ...) {
    int total = 0;
    va_list args; // Declare the argument pointer

    // Initialize args to start after 'count'
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        // Retrieve the next argument as an 'int'
        total += va_arg(args, int);
    }

    // Clean up the argument list
    va_end(args);

    return total;
}

int main(void) {
    // Calling the variadic function with different numbers of arguments
    printf("Sum (2, 10, 20) = %d\n", sum(2, 10, 20)); 
    printf("Sum (4, 1, 2, 3, 4) = %d\n", sum(4, 1, 2, 3, 4));
    
    return 0;
}
