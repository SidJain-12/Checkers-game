#include "game.h"

#ifndef __FUTURE_MOVES_H
#define __FUTURE_MOVES_H


//linked list containing each possible next move
//each node points to another linked list containing all subsequent moves
struct FutureTreeNode{
    int depth;
    GameState G;
    struct FutureTreeNode* next;
    struct FutureTreeNode* child;
};

typedef struct FutureTreeNode* FNode;
typedef FNode FTree;

FNode _initFNode(int depth, GameState G);
//adds a node to a linked list
void _addFNode(FNode F ,GameState G);

FTree _createFTree(int k, GameState G);

//recursively frees each linked list in the FTree
void clearFTree(FTree F);

#endif