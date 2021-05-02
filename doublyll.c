#include <stdio.h>
#include "doublyll.h"

struct Node* GetNewNode(GameState G) 
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->GameState = G;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void push(GameState G)
{
	struct Node* temp = head;
	struct Node* newNode = GetNewNode(G);
	if(head == NULL) {
		head = newNode;
		return;
	}
	while(temp->next != NULL) temp = temp->next; // Go To last Node
	temp->next = newNode;
	newNode->prev = temp;
}
