#include <stdio.h>

int main(void) {
    /*
     * FORMAT SPECIFIERS REFERENCE IN C:
     * Syntax: %[flags][width][.precision][length]type
     * 
     * Flags:
     *   - : Left-justify within the given field width.
     *   + : Forces a sign (+ or -) to precede positive/negative numbers.
     *   0 : Pads the field with leading zeroes instead of spaces.
     *   (space) : Leaves a leading space if no sign is printed.
     *   # : Alternate form (e.g., adds 0x for %x, forces decimal point for floats).
     *
     * Width:
     *   Minimum number of characters to be printed.
     *
     * Precision:
     *   .n for integers: minimum number of digits to display.
     *   .n for floats: number of decimal digits after the dot.
     *   .n for strings: maximum number of characters to display.
     */

    // Sample data variables
    char letter = 'A';
    char name[] = "Beluga";
    int age = 20;
    int negative_val = -42;
    float price = 67.90f;
    double pi = 3.1415926535;
    unsigned int hex_val = 255;
    void *ptr = &age;

    // === CHARACTERS & STRINGS ===
    printf("=== CHARACTERS & STRINGS (%%c, %%s) ===\n");
    printf("%%c (single char)       : %c\n", letter);
    printf("%%s (basic string)      : %s\n", name);
    printf("%%10s (width 10, right) : [%10s]\n", name);
    printf("%%-10s (width 10, left) : [%-10s]\n", name);
    printf("%%.3s (truncate to 3)   : %.3s\n\n", name);

    // === INTEGERS ===
    printf("=== INTEGERS (%%d, %%i, %%u) ===\n");
    printf("%%d (standard signed)   : %d\n", age);
    printf("%%+d (force sign)       : %+d\n", age);
    printf("%% d (leading space)    : % d\n", age);
    printf("%%5d (width 5, right)   : [%5d]\n", age);
    printf("%%-5d (width 5, left)   : [%-5d]\n", age);
    printf("%%05d (zero-padding)    : %05d\n", age);
    printf("%%.5d (min 5 digits)    : %.5d\n", age);
    printf("%%u (unsigned int)      : %u\n\n", 3000000000U);

    // === FLOATS & DOUBLES ===
    printf("=== FLOATING-POINT (%%f, %%lf, %%e, %%g) ===\n");
    printf("%%f (default precision) : %f\n", price);
    printf("%%.2f (2 decimals)      : %.2f\n", price);
    printf("%%+2.2f (sign + 2 dec)  : %+2.2f\n", price);
    printf("%%+2.2f (negative val)  : %+2.2f\n", -price);
    printf("%%8.2f (width 8, 2 dec) : [%8.2f]\n", price);
    printf("%%08.2f (zero-padded)   : [%08.2f]\n", price);
    printf("%%.4lf (double, 4 dec)  : %.4lf\n", pi);
    printf("%%e (scientific)        : %e\n", pi);
    printf("%%g (compact float)     : %g\n\n", 0.000042);

    // === NUMBER BASES & SPECIALS ===
    printf("=== BASES & SPECIALS (%%o, %%x, %%p, %%%%) ===\n");
    printf("%%o (octal)             : %o\n", hex_val);
    printf("%%x (hex lowercase)     : %x\n", hex_val);
    printf("%%X (hex uppercase)     : %X\n", hex_val);
    printf("%%#x (hex with prefix)  : %#x\n", hex_val);
    printf("%%p (pointer address)   : %p\n", ptr);
    printf("%%%% (literal percent)   : 100%%\n");

    return 0;
}
