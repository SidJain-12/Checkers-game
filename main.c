#include "game.h"
#include <stdio.h>
#include <stdlib.h>

#define rp RED,PAWN
#define rk RED,KING
#define bp BLACK,PAWN
#define bk BLACK,KING

int main(void){
    GameState G = initEmptyBoard();

    //loop to add arbitrary no of pieces to the test board
    // int t[][4] = {{0,2,rp},{5,1,rk}};
    // for(int i = 0; i < sizeof(t)/(sizeof(int)*4); i++)
    // {
    //     addPiece(G, t[i][0], t[i][1], t[i][2], t[i][3]);
    // }
    
    addPiece(G,2,1,RED,PAWN);

    displayBoard(G);

    movePiece(G, 2,1,3,0);

    displayBoard(G);
    
    
    free(G);
}