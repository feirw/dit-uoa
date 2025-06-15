#include <stdio.h>
#include <stdlib.h>
#include "PQInterface.h"

// Βοηθητική συνάρτηση για ταξινομημένη εισαγωγή
static PQListNode *SortedInsert(PQItem Item, PQListNode *P) {
    PQListNode *N;
    if ((P == NULL) || (Item >= P->NodeItem)) {
        N = (PQListNode *)malloc(sizeof(PQListNode));
        if (N == NULL) {
            printf("Σφάλμα: Αποτυχία δέσμευσης μνήμης.\n");
            exit(1);
        }
        N->NodeItem = Item;
        N->Link = P;
        return N;
    } else {
        P->Link = SortedInsert(Item, P->Link);
        return P;
    }
}

void Initialize(PriorityQueue *PQ) {
    PQ->Count = 0;
    PQ->ItemList = NULL;
}

int Empty(PriorityQueue *PQ) {
    return (PQ->Count == 0);
}

int Full(PriorityQueue *PQ) {
    return (PQ->Count == MAXCOUNT);
}

void Insert(PQItem Item, PriorityQueue *PQ) {
    if (!Full(PQ)) {
        PQ->ItemList = SortedInsert(Item, PQ->ItemList);
        PQ->Count++;
    } else {
        printf("Η ουρά είναι πλήρης! Δεν μπορεί να εισαχθεί το στοιχείο %d.\n", Item);
    }
}

PQItem Remove(PriorityQueue *PQ) {
    if (!Empty(PQ)) {
        PQItem temp = PQ->ItemList->NodeItem;
        PQListNode *oldNode = PQ->ItemList;
        PQ->ItemList = PQ->ItemList->Link;
        free(oldNode);
        PQ->Count--;
        return temp;
    } else {
        printf("Η ουρά είναι άδεια. Δεν μπορεί να γίνει αφαίρεση.\n");
        return -1; // Ή άλλη ένδειξη λάθους
    }
}
