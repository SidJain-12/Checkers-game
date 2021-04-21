#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
    GameState G = initEmptyBoard();

    //loop to add arbitrary no of pieces to the test board
    int t[][4] = {{0,1,RED,PAWN},{5,1,RED,PAWN}};
    for(int i = 0; i < sizeof(t)/(sizeof(int)*4); i++)
    {
        addPiece(G, t[i][0], t[i][1], t[i][2], t[i][3]);
    }

    displayBoardClear(G);
    free(G);
}