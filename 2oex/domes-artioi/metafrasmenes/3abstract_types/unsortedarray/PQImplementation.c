#include <stdio.h>
#include "PQInterface.h"

/* Παρακάτω δίνονται όλες οι λεπτομέρειες των συναρτήσεων */
/* που δηλώθηκαν στο αρχείο διεπαφής, μαζί με */
/* τοπικές ιδιωτικές συναρτήσεις. */

void Initialize(PriorityQueue *PQ)
{
    PQ->Count = 0;
}
int Empty(PriorityQueue *PQ)
{
    return (PQ->Count == 0);
}
int Full(PriorityQueue *PQ)
{
    return (PQ->Count == MAXCOUNT);
}
void Insert(PQItem Item, PriorityQueue *PQ)
{
    if (!Full(PQ)) {
        PQ->ItemArray[PQ->Count] = Item;
        PQ->Count++;
    }
}
PQItem Remove(PriorityQueue *PQ)
{
    int i;
    int MaxIndex;
    PQItem MaxItem;

    if (!Empty(PQ)) {
        MaxItem = PQ->ItemArray[0];
        MaxIndex = 0;

        for (i = 1; i < PQ->Count; ++i) {
            if (PQ->ItemArray[i] > MaxItem) {
                MaxItem = PQ->ItemArray[i];
                MaxIndex = i;
            }
        }

        PQ->Count--;
        PQ->ItemArray[MaxIndex] = PQ->ItemArray[PQ->Count];
        return MaxItem;
    }
}
int GetCount(PriorityQueue *PQ) {
    return PQ->Count;
}