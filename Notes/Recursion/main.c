#include <stdio.h>

// Demonstration of recursion
// Factorial function expected output: 5! = 5*4*3*2*1 = 120

int factorial(int num);

int main(){
	int input = 0;
	printf("Enter a number: ");
	scanf("%d", &input);
	printf("%d! is: %d\n", input,factorial(input));
}

int factorial(int num){

	if (num == 1){ // Terminating Case
		return num;
	}
	else if(num > 1){
		return num * factorial(num - 1);
	
		// e.g. : input = 3
		// calls factorial(3)
		
		// call 1: return 3 * factorial(3-1)
		// Hold on! The computer can't finish this addition yet 
		// because it doesn't know what factorial(3-1) equals
		
		// call 2: return 2 * factorial(2-1)
		// Same, the computer does not know factorial(2-1)

		// call 3: return 1 (Terminating case hit! No more function call)
		
		// Start unwinding the stack
		// call 2 now knows factorial(2-1) = 1
		// calculate 2 * 1 = 2
		// call 1 now knows factorial(3-1) = 2
		// calculate 3 * 2 = 6
	
		// Final output = 6
		// 3! is indeed 6
	}
	else{ 
		return 1;
	}
}
