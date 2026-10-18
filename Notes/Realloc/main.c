#include <stdio.h>
#include <stdlib.h>

typedef char names[20];

int main(){

    int count = 0;
    int newcount = 0;

    printf("Please enter amount of items: ");
    scanf("%d", &count);
    getchar();

    names *item_names = malloc(count * sizeof(names));
    if(item_names == NULL){
	    printf("Memory Allocation Failed");    
	    return 1;
    }

    for(int i = 0; i < count; i++){
	    printf("Enter name of item#%d: ", i + 1);
	    fgets(item_names[i], sizeof(names), stdin);
    }

    printf("Enter new amount of items: ");
    scanf("%d", &newcount);
    getchar();
    
    names *temp = realloc(item_names, newcount * sizeof(names));
    if(temp == NULL){
	    printf("Memory Reallocation Failed");
	    free(item_names);
	    return 1;
    }else{
	    item_names = temp;
	    temp = NULL;

	    for(int i = count; i < newcount; i++){
		    printf("Enter name of item#%d: ", i + 1);
		    fgets(item_names[i], sizeof(names), stdin);
	    }
    }

    for(int i = 0; i < newcount; i++){
	    printf("Item#%d: %s", i + 1, item_names[i]);
    }

    free(item_names);
    item_names = NULL;
    return 0;
}
