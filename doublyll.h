#ifndef __DOUBLYLL_H
#define __DOUBLYLL_H
#include "game.h"

struct Node
{
    GameState G;
    struct Node *next; // Pointer to next node in DLL
    struct Node *prev; // Pointer to previous node in DLL
};

struct Node* GetNewNode(GameState G);
void push(GameState G);

#endif
