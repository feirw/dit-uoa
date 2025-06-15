#include <stdio.h>
#include <stdlib.h>
#include "diepafi.h"

void InitializeStack(Stack *S)
{
    S->ItemList = NULL;
}

int Empty(Stack *S)
{
    return (S->ItemList == NULL);
}

int Full(Stack *S)
{
    return 0;  // Ορίζουμε το πλήθος στοιχείων ως 0 γιατί η στοίβα μπορεί να μεγαλώσει δυναμικά
}

void Push(ItemType X, Stack *S)
{
    StackNode *Temp;
    Temp = (StackNode *) malloc(sizeof(StackNode));
    
    if (Temp == NULL) {
        printf("System storage is exhausted\n");
    } else {
        Temp->Link = S->ItemList;  // Σύνδεση του νέου κόμβου με τον προηγούμενο
        Temp->Item = X;            // Αποθήκευση του στοιχείου
        S->ItemList = Temp;        // Ενημέρωση του δείκτη της κορυφής της στοίβας
    }
}

void Pop(Stack *S, ItemType *X)
{
    StackNode *Temp;
    
    if (S->ItemList == NULL) {
        printf("Attempt to pop from an empty stack\n");
    } else {
        Temp = S->ItemList;
        *X = Temp->Item;            // Αποθήκευση του στοιχείου σε *X
        S->ItemList = Temp->Link;   // Ενημέρωση της κορυφής της στοίβας
        free(Temp);                 // Απελευθέρωση μνήμης του παλιού κόμβου
    }
}
