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

GameState Undo(struct Node *head)
{
    if (head->next == NULL)
    {
        GameState F = initEmptyBoard();
        setBoard(F);
        return F;
        // displayBoardClear(G);
    }
    struct Node *temp = head->next;
    while (temp->next != NULL)
        temp = temp->next;
    GameState H = temp->prev->G;
    // displayBoardClear(H);
    temp->prev->next = NULL;
    free(temp);
    return H;
}

void Review(struct Node *head)
{
    struct Node *temp = head;
    if (head == NULL)
    {
        printf("No moves lol");
        return;
    }
    while (temp != NULL)
    {
        GameState H = temp->G;
        displayBoard(H);
        temp = temp->next;
    }
}
