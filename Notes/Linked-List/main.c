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
void remove_by_index(node_t **head, int index); // remove item by index
void remove_by_value(node_t **head, int val); // remove item by value

int main(){

	node_t *head = malloc(sizeof(node_t));
	if (head == NULL){
		return 1;
	}
	head->val = 2;
	head->next = NULL;
	node_t **pHead = &head; // create reference to head pointer 

	append(head, 3);
	push(pHead, 1);

	remove_by_value(pHead, 3);

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

void remove_by_index(node_t **pHead, int index){
	if(*pHead == NULL || index < 0){
		return;
	}

	if(index == 0){
		node_t *temp = *pHead;
		*pHead = (*pHead)->next;
		free(temp);
		temp = NULL;
		return;
	}

	node_t *current = *pHead;
	node_t *temp_node = NULL;

	for(int i = 0; i < index - 1; i++){
		if(current->next == NULL){
			return;
		}
		current = current->next; // the node before the node we want to delete
	}

	temp_node = current->next; // the node to be delete

	current->next = temp_node->next;
	free(temp_node);
	temp_node = NULL;

}

void remove_by_value(node_t **pHead, int val){
	if(*pHead == NULL || pHead == NULL){
		return;
	}

	node_t *current = *pHead;
	node_t *prev = NULL;

	while(current != NULL){
		if(current->val == val){
			if(prev == NULL){
				*pHead = current->next;
				free(current);
				return;
			}
			else{
				prev->next = current->next;
				free(current);
				return;
			}
		}
		else{
			prev = current;
			current = current->next;
		}
	}

	printf("Item with value %d not found!\n", val);
	return;
}
