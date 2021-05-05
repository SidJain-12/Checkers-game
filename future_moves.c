#include "future_moves.h"

#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

FNode _initFNode(int depth, GameState G){
    FNode node = (FNode) malloc(sizeof(struct FutureTreeNode));
    node->child = NULL;
    node->next = NULL;
    node->G = initEmptyBoard();
    copyBoard(G, node->G);
    node->depth = depth;
    return node;
}

FNode _addChild(FNode parent, GameState G){
    parent->child = _initFNode(parent->depth + 1, G);
    return  parent->child;
}

FNode _addSibling(FNode parent, GameState G){
    FNode temp = parent;
    while(temp->next != NULL)
        temp = temp->next;
    
    temp->next = _initFNode(parent->depth, G);

    return temp->next;
}

//displays each possible gamestate after 'depth' moves
void displayFTree(int depth, FTree F){
    
    if(F == NULL || F->depth > depth){
        return;
    }
    
    FTree temp = F;
    if(temp->depth == depth){
        while(temp != NULL){
            printf("Depth: %d\n", temp->depth);
            displayBoard(temp->G);
            printf("\n");
            temp = temp->next;
        }
        // printf("--------------------\n");
        return;
    }

    while(temp != NULL){
        displayFTree(depth, temp->child);
        temp = temp->next;
    }
}

void freeFTree(FTree F){
    if(F == NULL)
        return;

    FNode temp = F;

    while(temp != NULL){
        FNode nexttemp = temp->next;
        
        freeFTree(temp->child);
        free(temp->G);
        free(temp);

        temp = nexttemp;
    }
}

//adds the next layer of moves to an FNode
FTree _nextChildren(FNode F){
    GameState G = F->G;

    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++){
            if((G->board[i][j] >> 1) == G->currPlayer && !isEmpty(G, i, j) && validMove(G, i, j))
            {
                short int tempPiece = G->board[i][j];
                if(tempPiece == BLACK_KING || tempPiece == RED_KING){
                    for(int k = -1; k < 2; k +=2)
                        for(int l = -1; l < 2; l +=2)
                            if(validMove(G, i + k, j + l) && isEmpty(G, i + k, j + l)){
                                GameState tempBoard = initEmptyBoard();
                                copyBoard(G, tempBoard);

                                movePiece(tempBoard, i, j, i + k, j + l);
                                //assuming F has a child
                                if(F->child == NULL)
                                    _addChild(F, tempBoard);
                                else
                                    _addSibling(F->child, tempBoard);
                                
                                free(tempBoard);
                            }
                }
                else{
                    short int tempPieceColour = tempPiece >> 1;
                    int direction = ((tempPieceColour == RED) ? -1 : 1);
                    printf("piece (%d,%d)\n", i+1, j+1);
                    for(int k = -1; k < 2; k +=2)
                        if(validMove(G, i + k, j + direction) && isEmpty(G, i + k, j + direction)){
                            GameState tempBoard = initEmptyBoard();
                            copyBoard(G, tempBoard);

                            int status = movePiece(tempBoard, i, j, i + k, j + direction);

                            if(status == 1)
                                printf("succesful normal move of (%d,%d) to (%d,%d)\n", i+1,j+1,i+1 + k, j+1 +direction);
                            else if(status == 0)
                                printf("invalid move for piece (%d,%d)\n",i+1,j+1);

                            //assuming F has a child
                            if(F->child == NULL)
                                _addChild(F, tempBoard);
                            else
                                _addSibling(F->child, tempBoard);
                            
                            free(tempBoard);        
                        }
                        else printf("no piece/non empty move (%d,%d)\n", i+1, j+1);
                }
            }
        }

    return F->child;
}

void _createFTreeStep(int k, FNode F){
    
    if(F == NULL || F->depth == k)
        return;
        
    FNode temp = _nextChildren(F); //child of F
    while(temp != NULL){
        _createFTreeStep(k, temp);

        temp = temp->next;
    }    
}

FTree createFTree(int k, GameState G){
    FTree tree = _initFNode(0, G);
    _createFTreeStep(k, tree);
    return tree;
}