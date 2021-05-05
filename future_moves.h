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

// FNode _initFNode(int depth, GameState G);
FNode _initFNode(int depth, GameState G);
FNode _addChild(FNode parent, GameState G);
FNode _addSibling(FNode parent, GameState G);

//creates an FTree for G for k layers
FTree createFTree(int k, GameState G);
void displayFTree(int depth, FTree F);

//recursively frees each linked list in the FTree
void freeFTree(FTree F);

FTree _nextChildren(FNode F);

#endif