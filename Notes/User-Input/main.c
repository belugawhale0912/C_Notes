#include <stdio.h>
#include <string.h>

int main(){

	int age = 0;
	float price = 0.0f;
	char gender = '\0';
	char name[30] = "";

	// 1. %d reads an integer and automatically skips any leading whitespace.
	//    However, pressing Enter leaves a trailing newline ('\n') in the buffer.

	// 2. %f automatically ignores leading whitespace, so it discards the leftover '\n'
	//    from the age input before reading the float, but leaves its own '\n' behind.

	// 3. %c does NOT skip whitespace by default and would normally read that leftover '\n',
	//    causing it to skip. The leading space in " %c" tells scanf to discard all
	//    preceding whitespace/newlines so it waits for actual user input.

	printf("Enter You Age:");
	scanf("%d", &age);

	printf("Enter Price:");
	scanf("%f",&price);

	printf("Enter Gender:");
	scanf(" %c",&gender);

	getchar(); // strips the \n character in the input buffer when pressing enter
	printf("Enter Your Name:");
	fgets(name, sizeof(name), stdin); // fgets is used because scanf will end when whitespace is detected
					  //
	// the fgets line will record name as 'name-entered-by-user\n' which causes printf later to print an extra new line
	// with string.h, we can get the strlen() function which returns the length of the string
	// we change the last character,using index:length - 1 to replace the \n (new line character) with \0 (null terminator)
	name[strlen(name) - 1] = '\0'; 	

	printf("%s\n",name);
	printf("%d\n",age);
	printf("%.2f\n",price);	
	printf("%c\n",gender);	

}
