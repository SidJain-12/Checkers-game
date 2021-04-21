#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

PtrToQue Front = NULL;
PtrToQue Rear = NULL;

PtrToQue MakeNode(elem_type X1, elem_type X2)
{
    PtrToQue P = (PtrToQue)malloc(sizeof(Que));
    
    P->X1 = X1;
    P->X2 = X2;
    
    P->Link_To_Next = NULL;
    P->Link_To_Previous = NULL;

    return P;
}

void Push(elem_type X1, elem_type X2)
{
    PtrToQue P = MakeNode(X1, X2);

    if((Front == NULL) && (Rear == NULL))
    {
        Front = P;
        Rear = P;
        return;
    }
    
    Front->Link_To_Previous = P;
    P->Link_To_Next = Front;

    Front = P;
}
void Pop()
{
    if(Front == Rear)
    {
        Front = NULL;
        Rear = NULL;
        return;
    }
    PtrToQue temp = Front;

    Front = Front->Link_To_Next;
    Front->Link_To_Previous = NULL;

    free(temp);
}




