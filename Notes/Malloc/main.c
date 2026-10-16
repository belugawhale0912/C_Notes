#include <stdio.h>
#include <stdlib.h>

int main() {
    int count = 0;
    printf("Input number of prices: ");
    if (scanf("%d", &count) != 1 || count <= 0) {
        printf("Invalid input count.\n");
        return 1;
    }

    // Allocate memory for 'count' number of floats
    float *price = malloc(count * sizeof(float));
    if (price == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("Enter price #%d: RM", i + 1);
        scanf("%f", &price[i]);
    }

    float total = 0;
    for (int i = 0; i < count; i++) {
        total += price[i];
    }

    printf("Total: RM%.2f\n", total);

    // Free the allocated heap memory
    free(price);
    //prevent dangling pointer
    price = NULL; 

    return 0;
}
