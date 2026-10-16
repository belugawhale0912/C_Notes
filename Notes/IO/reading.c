#include <stdio.h>

int main(){
	
	FILE *pFile = fopen("output.txt", "r");
	char readbuffer[1024] = {0};

	while(fgets(readbuffer, sizeof(readbuffer), pFile) != NULL){
		printf("%s", readbuffer);
	}
	fclose(pFile);
	return 0;
}
