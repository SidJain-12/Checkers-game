#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int _abs(int a)
{
    return (a>0) ? a : -a;
}

GameState initEmptyBoard(){
    GameState G = (GameState) malloc(sizeof(struct GameStateS));

    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            G->board[i][j] = EMPTY;

    //This idiom makes sure turn and currPlayer correspond. Used instead of manually updating
    //Red always goes on odd turns, black always goes on even turns
    //Red starts
    G->turn = 1;
    G->currPlayer = RED; //initialises to RED

    return G;
}

void copyBoard(GameState src, GameState dest)
{
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            dest->board[i][j] = src->board[i][j];

    dest->turn = src->turn;
    dest->currPlayer = src->turn;   
}


//fills a board with empty positions
void setBoard(GameState G){
    for(int i = 0; i < SIZE; i++)
        switch(i){
            case 1:
                for(int j = 0; j < SIZE; j++){
                    if(!(j%2))
                        addPiece(G,j,i,BLACK,PAWN);
                    else
                        removePiece(G,j,i);
                }
                break;

            case 0: case 2:
                for(int j = 0; j < SIZE; j++){
                    if(j%2)
                        addPiece(G,j,i,BLACK,PAWN);
                    else
                        removePiece(G,j,i);
                }
                break;
            
            case 5: case 7:
                for(int j = 0; j < SIZE; j++){
                    if(!(j%2))
                        addPiece(G,j,i,RED,PAWN);
                    else
                        removePiece(G,j,i);
                }
                break;
            
            case 6:
                for(int j = 0; j < SIZE; j++){
                    if(j%2)
                        addPiece(G,j,i,RED,PAWN);
                    else
                        removePiece(G,j,i);
                }
                break;
            default: 
                for(int j = 0; j < SIZE; j++)
                    removePiece(G,j,i);
                    break;
        }
    return;
}

void displayBoard(GameState G)
{   
    printf("Turn: %d\nCurrent player: ", G->turn);
    if(G->currPlayer == RED)
        printf("Red\n\n");
    else
        printf("Black\n\n");

    printf("  1 2 3 4 5 6 7 8\n");
    for(int i = 0; i < SIZE; i++){
        printf("%d", i+1);
        for(int j = 0; j < SIZE; j++){
            switch(G->board[j][i]){
                case 4:
                    if(!((i+j)%2)) printf(" □");
                    else printf(" ■");
                    break;
                case 0: 
                    printf(" P");
                    break;
                case 1: 
                    printf(" K");
                    break;
                case 2: 
                    printf(" \x1b[31mP");
                    printf("\x1b[0m");
                    break;
                case 3: 
                    printf(" \x1b[31mK");
                    printf("\x1b[0m");
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
    
    return;
}

void displayBoardClear(GameState G){
    system("clear");
    displayBoard(G);
}

void addPiece(GameState G, int x, int y, int colour, int type){
    if(G->board[x][y] == EMPTY){
        //converts colour and type to a piece code
        short int piece = type + colour * 2;
        G->board[x][y] = piece;
        
        return;
    }
    else return;
}

void removePiece(GameState G, int x, int y){
    G->board[x][y] = EMPTY;
}

//checks to see if a given piece can make a capture on its next move
//includes different cases for pawns and kings
int isEmpty(GameState G, int x, int y)
{
    return(G->board[x][y] == EMPTY);
}

//returns 0 if the move is out of bounds or on the wrong tile colour, else 1
//check for empty left separate to check for captures being in/out of bounds
int validMove(GameState G, int x, int y)
{
    if( (x > 7) || (x < 0) || (y > 7) || (y < 0) ) //checks bounds
        return 0;
    else if( (x+y)%2 == 0 )     //checks for white squares
        return 0;
    else return 1;
}

//returns a +ve integer if a piece can legally capture another
//Check if a capture is made separately
int captureAvailable(GameState G, int x, int y)
{
    short int piece = G->board[x][y];

    //KINGS
    if(piece == RED_KING || piece == BLACK_KING){                    
        short int pieceColour = piece >> 1;          //right shifts the piece code to get colour
        
        //this loop checks each if each possible move is valid
        //then it checks if there is an enemy piece and whether there is space to jump over it
        for(int i = -1; i < 2; i +=2)
            for(int j = -1; j < 2; j +=2){
                if(validMove(G, x + i, y + j)){
                    short int targetSquareColour = G->board[x+i][y+j]>>1;
                    if(targetSquareColour == !pieceColour){
                        if(isEmpty(G,x+2*i,y+2*j) && validMove(G,x+2*i,y+2*j)) 
                            return 1;
                    }
                }
            }
        return 0;
    }

    //PAWNS
    else{
        short int pieceColour = piece >> 1;          //right shifts the piece code to get colour
        int direction = (pieceColour == RED) ? -1 : 1;   //uses colour to determine whether up or down is checked

        //this loop is an adjusted version of the one for KINGS
        for(int i = -1; i < 2; i +=2){
            if(validMove(G, x + i, y + direction)){          
                short int targetSquareColour = G->board[x+i][y+direction]>>1;
                if(targetSquareColour == !pieceColour){
                    if(isEmpty(G,x+2*i,y+2*direction) && validMove(G,x+2*i,y+2*direction)) 
                        return 1;
                }
            }
        }
        return 0;
    }
    assert(0);
}

//returns an integer corresponding to whether a move can be made (NOT A CAPTURE)
int moveAvailable(GameState G, int x, int y, int targetX, int targetY)
{
    if( !validMove(G, targetX, targetY))
        return 0;
    else{
        short int piece = G->board[x][y];
        if(piece == BLACK_KING || piece == RED_KING){
            for(int i = -1; i < 2; i +=2)
                for(int j = -1; j < 2; j +=2)
                    if(validMove(G, x + i, y + j) && isEmpty(G, x + i, y + j))
                        return 1;
            
            //all possibilities exhausted
            return 0;
        }
        else{
            short int pieceColour = piece >> 1;
            int direction = (pieceColour == RED) ? -1 : 1;

            for(int i = -1; i < 2; i +=2)
                if(validMove(G, x + i, y + direction) && isEmpty(G, x + i, y + direction))
                        return 1;
            
            return 0;
        }
    }
}

void _updateBoard(GameState G)
{
    G->turn++;
    if(G->currPlayer == RED) G->currPlayer = BLACK;
    else G->currPlayer = RED;
    return;
}

//returns 0 for an invalid move (out of bounds/onto another piece/no possible moves)
//returns -1 if a capture is available but not made
//returns 1 if regular move
//returns 2 if captured a piece
//returns 3 if a piece was promoted
int movePiece(GameState G, int x, int y, int targetX, int targetY)
{
    short int piece = G->board[x][y];
    short int pieceColour = piece >> 1;
    short int isKing = piece%2;
    short int direction = (pieceColour) ? -1 : 1;

    if(!validMove(G, targetX, targetY) || !validMove(G, x, y))
        return 0;

    if(pieceColour == G->currPlayer){

    }    

    short int xDist = _abs(x-targetX);
    short int yDist = _abs(y-targetY);

    if(xDist == 2 && yDist == 2){
        if(!captureAvailable(G, x, y))
            return 0;
        else{
            if(!isEmpty(G, targetX, targetY) || (!isKing && (targetY-y)/2 != direction))
                return 0;
            else{
                removePiece(G,x,y);
                removePiece(G, (x+targetX)/2, (y+targetY)/2);
                addPiece(G, targetX, targetY, pieceColour, isKing);
                
                //promotion
                if((targetY == (pieceColour == RED) ? 0 : 7) && !isKing ){
                    removePiece(G, targetX, targetY);
                    addPiece(G, targetX, targetY, pieceColour, KING);

                    //no double jumps after promotion
                    return 3;
                }

                //multi-jumps dont change the turn count or player
                if(!captureAvailable(G, targetX, targetY))
                    _updateBoard(G);
                else
                    G->turn++;

                return 2;
            }
        }   
    }

    else if(xDist == 1 && yDist == 1){
        //this state is reached if a non capture move is made when one is available
        if(captureAvailable(G, x, y))
            return -1;

        //this state checks for illegal moves that are on the board
        else{
            if(!isEmpty(G, targetX, targetY) || (!isKing && (targetY-y) != direction))
                return 0;
            else{
                removePiece(G,x,y);
                addPiece(G, targetX, targetY, pieceColour, isKing);
                _updateBoard(G);

                if((targetY == (pieceColour == RED) ? 0 : 7) && !isKing){
                    removePiece(G, targetX, targetY);
                    addPiece(G, targetX, targetY, pieceColour, KING);

                    return 3;
                }

                return 1;
            }
        }
    }
    else
        return 0;
}