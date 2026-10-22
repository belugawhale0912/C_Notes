#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int val;
	struct node *next;
} node_t;

void print_list(node_t *head); // output all items in the linked list
void append(node_t *head, int val); // add item at the end of the linked list
void push(node_t **head, int val); // add item at the beginning of the linked list
void pop(node_t **head); // remove the first item
void remove_last(node_t **pHead); // remove the last item

int main(){

	node_t *head = malloc(sizeof(node_t));
	if (head == NULL){
		return 1;
	}
	head->val = 6;
	head->next = NULL;
	node_t **pHead = &head; // create reference to head pointer 

	printf("append 7 and push 67:\n");
	append(head, 7);
	push(pHead, 67);

	print_list(head);

	printf("After pop and remove_last:\n");
	pop(pHead);
	remove_last(pHead);
	print_list(head);
} 


void print_list(node_t *head){
	node_t *current = head;

	while (current != NULL){
		printf("%d\n", current->val);
		current = current->next;
	}
}


void append(node_t *head, int val){
	node_t *lastnode = head;

	while(lastnode->next != NULL){
		lastnode = lastnode->next;
	}
	
	lastnode->next = (node_t *) malloc(sizeof(node_t));
	lastnode->next->val = val;
	lastnode->next->next = NULL;
}


void push(node_t **pHead, int val){ // get the head variable by reference (node_t **)
	node_t *newnode = malloc(sizeof(node_t)); // create the new node
	newnode->val = val;

	// set the next field in newnode = *pHead(the head pointer)
	// this makes the newnode points to the same addess as the head pointer
	// which is the initial first node
	newnode->next = *pHead; 

	// then we let the head pointer point to our new node
	*pHead = newnode;
}

void pop(node_t **pHead){
	if(*pHead == NULL){
		return;
	}
	
	node_t *temp = (*pHead)->next;
	free(*pHead);
	*pHead = temp;	
}

void remove_last(node_t **pHead){
	if(*pHead == NULL){
		return;
	}

	if((*pHead)->next == NULL){
		free(*pHead);
		*pHead = NULL;
		return;
	}

	node_t *current = *pHead;
	node_t *previous = NULL;
	
	while(current->next != NULL){
		previous = current;
		current = current->next;
	}

	free(current);
	previous->next = NULL;
}

