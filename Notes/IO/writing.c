#include <stdio.h>

int main(){

	FILE *pfile = fopen("output.txt", "w");
	if(pfile == NULL){
		printf("Error while openning file!");
		return 1;
	}

	char contentToWrite[50] = "Halo Gan Teck Ann!\n";
	fprintf(pfile, "%s", contentToWrite);
	
	fclose(pfile);
	return 0;
}
