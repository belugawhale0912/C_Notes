#include <stdio.h>
#include <stdlib.h> // Required for malloc() and free()

int main(void) {
    // --- WHAT IS A NULL POINTER? ---
    // A null pointer is a pointer deliberately assigned a reserved address 
    // to indicate that it references no valid memory object.
    //
    // NOTE: An uninitialized pointer (wild pointer) is NOT a null pointer;
    // it holds whatever garbage bits were left in that stack location.
    // Dereferencing an uninitialized pointer points to an arbitrary, invalid address.
    //
    // - In C, the null pointer constant is defined as NULL.
    // - It typically maps to ((void *)0) or an integer constant 0.
    // - The C standard guarantees that no valid object or function will ever reside at address 0.

    // --- USE CASE 1: SAFE INITIALIZATION ---
    // Assigning NULL ensures the pointer does not hold an indeterminate garbage address.
    int *ptr = NULL; // Safe: cleanly denotes "not pointing to anything yet"

    // Guarding against segmentation faults:
    if (ptr != NULL) {
        *ptr = 10;
    }

    // --- USE CASE 2: ELIMINATING DANGLING POINTERS ---
    char *s = malloc(20);
    free(s); // Marks allocated heap memory as free to be reused

    // However, the variable 's' still holds that previous memory address,
    // making 's' a dangling pointer.
    // If subsequent code does: *s = 'A'; it causes a Use-After-Free condition.

    // Resetting 's' to NULL eliminates the dangling pointer:
    s = NULL;

    // Additional benefit: free(NULL) is guaranteed safe and does nothing.
    free(s); 

    return 0;
}
