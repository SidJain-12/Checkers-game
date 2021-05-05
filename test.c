#include "future_moves.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
    GameState G = initEmptyBoard();
    setBoard(G);
    // addPiece(G,2,5,RED,PAWN);
    // addPiece(G,6,1,BLACK,PAWN);

    // displayBoard(G);

    // movePiece(G,2,5,3,4);
    // movePiece(G,6,1,5,2);

    displayBoard(G);
    // FNode FN = _initFNode(0, G);
    // FTree F = _nextChildren(FN);
    // _nextChildren(F);
    // displayBoard(F->child->child->G);

    FTree F = createFTree(2,G);
    
    displayFTree(0, F);
    printf("---------------------------------------------------------------\n");
    displayFTree(1, F);
    printf("---------------------------------------------------------------\n");
    displayFTree(2, F);

    free(G);
    freeFTree(F);
    // freeFTree(FN);
}