#include "game.h"
#include <stdio.h>
#include <stdlib.h>

#define rp RED,PAWN
#define rk RED,KING
#define bp BLACK,PAWN
#define bk BLACK,KING

int main(void){
    GameState G = initEmptyBoard();
    setBoard(G);

    //loop to add arbitrary no of pieces to the test board
    // int t[][4] = {{0,2,rp},{5,1,rk}};
    // for(int i = 0; i < sizeof(t)/(sizeof(int)*4); i++)
    // {
    //     addPiece(G, t[i][0], t[i][1], t[i][2], t[i][3]);
    // }

    displayBoard(G);

    movePiece(G,2,5,3,4);

    displayBoard(G);

    movePiece(G,3,2,4,3);

    displayBoard(G);

    movePiece(G,3,6,2,5);

    displayBoard(G);

    movePiece(G,5,2,6,3);

    displayBoard(G);

    movePiece(G,3,4,5,2);

    displayBoard(G);

    free(G);
}