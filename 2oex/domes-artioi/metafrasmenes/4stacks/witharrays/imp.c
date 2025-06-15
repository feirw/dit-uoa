#include <stdio.h>
#include "prot.h"


void InitializeStack(Stack *s) {
    s->top = -1;  // Initialize the stack as empty
}

int Empty(Stack *s) {
    return s->top == -1;  // Stack is empty if top is -1
}

int Full(Stack *s) {
    return s->top == MAX - 1;  // Stack is full if top reaches MAX-1
}

void Push(ItemType item, Stack *s) {
    if (Full(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = item;  // Increment top and push item
}

void Pop(Stack *s, ItemType *item) {
    if (Empty(s)) {
        printf("Stack Underflow\n");
        return;
    }
    *item = s->items[(s->top)--];  // Pop item and decrement top
}
