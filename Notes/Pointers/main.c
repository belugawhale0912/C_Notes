#include <stdio.h>

// Function prototypes
void inc_age_value(int age);
void inc_age_reference(int *age);

int main(void) {
    // A pointer is a variable that stores the memory address of another variable.
    // They help avoid wasting memory and processing time by allowing us to pass the
    // memory address of large data structures (like structs or arrays) to functions,
    // rather than copying the entire data structure onto the call stack.

    // age is a standard variable that allocates memory on the stack for an integer with a value of 20.
    int age = 20;
    printf("The initial value of variable age: %d\n", age);

    // The & (address-of) operator retrieves the exact hexadecimal memory address where 'age' is stored.
    printf("The memory address of variable age is: %p\n", &age);

    // When creating a pointer, the '*' symbol is part of the type declaration (int*),
    // indicating that pAge is not an integer, but a pointer designed to hold the address of an integer.
    // Here, we assign the memory address of 'age' (&age) directly to the pointer variable pAge.
    int *pAge = &age;

    // Call Example 1: Pass by value
    // We pass the variable 'age' directly.
    inc_age_value(age);
    // 'age' in main remains 20 because the function only manipulated its own temporary copy.
    printf("Pass by value: %d\n", age);

    // Call Example 2: Pass by reference (simulated via pointer)
    // We pass the pointer 'pAge', which holds the memory address of 'age'.
    inc_age_reference(pAge);
    // 'age' in main is now 21 because the function reached directly into this memory address and updated it.
    printf("Pass by reference: %d\n", age);

    return 0;
}

// Example 1: Pass by value
// This function accepts an argument of type int.
void inc_age_value(int age) {
    // Because C passes arguments by value, the runtime copies the data from 'age' in main()
    // into a brand-new local variable, also named 'age', allocated on inc_age_value's stack frame.
    // Both variables have completely separate memory addresses.
    
    age++; // Increments only the locally scoped copy.

    // Once this function finishes execution, its stack frame is destroyed, and the local copy disappears.
    // The original 'age' variable in main() remains completely untouched and unchanged at 20.
}

// Example 2: Pass by reference (simulated in C by passing a pointer)
// This function accepts a pointer parameter (int *age), which stores the memory address of an integer.
void inc_age_reference(int *age) {
    // When calling inc_age_reference(pAge), the memory address stored in pAge is copied into the parameter 'age'.
    // Even though the pointer variable itself is a local copy, the address it holds still points directly
    // to the original 'age' variable located in main()'s stack frame.

    // To modify the value at that address, we use the '*' dereference operator:
    // 1. Parentheses (*age) are required because the postfix increment (++) has higher operator precedence than (*).
    //    Writing *age++ would mistakenly increment the pointer address itself instead of the integer value.
    // 2. (*age) dereferences the pointer: it follows the address back to the memory location of 'age' in main().
    // 3. ++ then directly increments the value stored at that target memory address by one.
    (*age)++;

    // Because we modified the actual memory location, the change persists after this function finishes.
}
