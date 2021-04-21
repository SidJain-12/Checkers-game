#ifndef __QUEUE_H
#define __QUEUE_H

#include "Elem_Type.h"

typedef struct que Que;
typedef struct que* PtrToQue;


//Crearting a struct for cells of 
//queue with doubly linked list implementation.
struct que
{
    elem_type X1; // Initial position of the coin
    elem_type X2; // Final position of the coin
    PtrToQue Link_To_Next;
    PtrToQue Link_To_Previous;
};

PtrToQue MakeNode(elem_type X1, elem_type X2);

void Push(elem_type X1, elem_type X2);
void Pop();

#endif
