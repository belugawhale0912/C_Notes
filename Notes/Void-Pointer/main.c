#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // --- WHAT IS A VOID POINTER (void *)? ---
    // A void pointer is a generic, raw pointer that holds a memory address
    // without binding it to a concrete data type.
    //
    // - It stores an address, but the compiler does not know:
    //   1. The byte width of the target data (1 byte for char, 4 for int, etc.)
    //   2. How to interpret the underlying bits (integer, float, struct, etc.)

    int num = 42;
    void *vptr = &num; // Safe: any object pointer implicitly converts to void*

    // --- RULE 1: CANNOT DEREFERENCE DIRECTLY ---
    // *vptr = 100; // COMPILE ERROR: dereferencing 'void *' pointer
    //
    // FIX: Cast to the concrete pointer type before dereferencing:
    *(int *)vptr = 100;
    printf("Updated num: %d\n", num); // 100

    // --- RULE 2: NO STANDARD POINTER ARITHMETIC ---
    // vptr = vptr + 1; // NON-STANDARD: size of 'void' is unknown
    //
    // FIX: Cast to a type with a known byte size (like char*) to step:
    char *byte_step = (char *)vptr + 1; // Moves forward by exactly 1 byte
    (void)byte_step; // Silences unused variable warning

    // --- WHY USE void*? (GENERIC PROGRAMMING) ---
    // 1. Dynamic allocators return void* so any pointer type can accept them
    //    without explicit typecasting in C:
    double *values = malloc(5 * sizeof(double));

    // 2. Used in raw memory utilities (memcpy, memset) and generic callbacks
    //    (like qsort comparator functions) to handle any arbitrary data type.

    free(values);
    values = NULL;

    return 0;
} 
