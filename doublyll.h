#ifndef __DOUBLYLL_H
#define __DOUBLYLL_H
typedef struct Node node;
struct Node {
    int data;
    struct Node* next; // Pointer to next node in DLL
    struct Node* prev; // Pointer to previous node in DLL
};
void push(struct Node** head_ref, int new_data);
void append(struct Node** head_ref, int new_data);
#endif
