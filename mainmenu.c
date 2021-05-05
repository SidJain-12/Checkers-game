#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "doublyll.h"

int main(void)
{
    int status = 0;
    GameState G = initEmptyBoard();
    setBoard(G);
    displayBoardClear(G);
    struct Node *head = GetNewNode(G);

    int x = 0, y = 0, tX = 0, tY = 0;

    //need to include a provision to restrict moves if a capture is available
    while (1)
    {
        printf("What do you wanna do: Undo,Review,Move or Exit?");
        char str[100];
        scanf("%s", str);
        if (strcmp(str, "UNDO") == 0)
        {
            G = Undo(head);
            displayBoardClear(G);
            continue;
        }
        if (strcmp(str, "REVIEW") == 0)
        {
            Review(head);
            continue;
        }
        if (strcmp(str, "MOVE") == 0)
        {
            printf("Enter x and y coordinates of the piece you want to move and the target square\n");
        }
        if (strcmp(str, "Show_Possible_moves") == 0)
        {
            //func
            continue;
        }

        if (strcmp(str, "EXIT") == 0)
        {
            return 0;
        }

        if (!scanf(" %d %d %d %d", &x, &y, &tX, &tY))
            break;

        x--;
        y--;
        tX--;
        tY--;

        if (x == -1 && y == -1 && tX == -1 && tY == -1)
        {
            free(head);
            break;
        }

        status = movePiece(G, x, y, tX, tY);
        insert(G, head);
        displayBoardClear(G);
        switch (status)
        {
        default:
        case 0:
            printf("Invalid move\n");
            break;
        case -1:
            printf("You must make a capture\n");
            break;
        case 1:
            printf("You made a regular move\n");
            break;
        case 2:
            printf("You captured a piece, you must make another capture if possible\n");
            break;
        case 3:
            printf("You promoted a pawn\n");
            break;
        }
    }
}
