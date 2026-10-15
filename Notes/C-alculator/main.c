#include <stdio.h>

// The name is not a typo, its "C" alculator, get it? LoL

int main(){

	float numberA = 0.0;
	float numberB = 0.0;
	char operator = '\0';
	float result = 0.0;

	printf("Enter first number: ");
	scanf("%f", &numberA);

	printf("Enter second number: ");
	scanf("%f", &numberB);

	printf("Choose operator ( + |  - | * | / ): ");
	scanf(" %c", &operator);

	switch(operator){
		case '+':
			result = numberA + numberB;
			break;
		case '-':
			result = numberA - numberB;
			break;
		case '*':
			result = numberA * numberB;
			break;
		case '/':
			result = numberA / numberB;
			break;
		default:
			printf("Please choose a valid operator!");
			return 0;
	}

	printf("The result for %.2f %c %.2f is %.2f\n", numberA, operator, numberB, result);

	return 0;
}
