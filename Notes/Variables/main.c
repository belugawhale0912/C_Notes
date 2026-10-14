#include <stdio.h>
#include <stdbool.h>

int main(){
	
	// variable = reusable container for a value

	// int = whole numbers  (4 bytes)
	// float = single-precision decimal number (4 bytes)
	// double = double-precision decimal number (8 bytes)
	// char = single character (1 byte)
	// char[] = array of characters / string (size varies) 
	// bool = true or false value (1 byte)

	// NOTE: bool requires <stdbool.h> header file
	
	int age = 20;
	float accuracy = 99.9;
	double pi = 3.1415926;
	char gender = 'M';
	char name[] = "BelugaWhale";
	bool isAlive = true;

	printf("Hi, I am %d years old\n", age);
	printf("The accuracy of my aim is %f\n",accuracy);
	printf("The value of PI is: %.2f\n", pi);
	printf("Gender: %c\n",gender);
	printf("My name is: %s\n", name);
	
	if(isAlive){
		printf("Alive and breating\n");
	}
	else{
		printf("DEAD\n");
	}
}
