#include <stdio.h>
#include <stdlib.h>
#include "doublyll.h"
#include "game.h"

// struct Node *head;

struct Node *GetNewNode(GameState G)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->G = G;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insert(GameState G, struct Node *head)
{
    struct Node *temp = head;
    struct Node *newNode = GetNewNode(G);
    if (head == NULL)
    {
        head = newNode;
        return;
    }
    while (temp->next != NULL)
        temp = temp->next; // Go To last Node
    temp->next = newNode;
    newNode->prev = temp;
}
