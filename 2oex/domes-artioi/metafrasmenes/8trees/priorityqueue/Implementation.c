/* This is the file “PQImplementation.c” */
#include "PQInterface.h"

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
    int ChildLoc;
    int ParentLoc;
    (PQ->Count)++;
    ChildLoc = PQ->Count;
    ParentLoc = ChildLoc / 2;

    while (ParentLoc != 0) {
        if (Item <= PQ->ItemArray[ParentLoc]) {
            PQ->ItemArray[ChildLoc] = Item;
            return;
        } else {
            PQ->ItemArray[ChildLoc] = PQ->ItemArray[ParentLoc];
            ChildLoc = ParentLoc;
            ParentLoc = ParentLoc / 2;
        }
    }
    PQ->ItemArray[ChildLoc] = Item;
}

PQItem Remove(PriorityQueue *PQ)
{
    int CurrentLoc;
    int ChildLoc;
    PQItem ItemToPlace;
    PQItem ItemToReturn;

    if (Empty(PQ)) {
        return;  // Here you should probably return a default or error value, but for now we just return.
    }

    ItemToReturn = PQ->ItemArray[1];
    ItemToPlace = PQ->ItemArray[PQ->Count];
    (PQ->Count)--;

    CurrentLoc = 1;
    ChildLoc = 2 * CurrentLoc;

    while (ChildLoc <= PQ->Count) {
        if (ChildLoc < PQ->Count) {
            if (PQ->ItemArray[ChildLoc + 1] > PQ->ItemArray[ChildLoc]) {
                ChildLoc++;
            }
        }

        if (PQ->ItemArray[ChildLoc] <= ItemToPlace) {
            PQ->ItemArray[CurrentLoc] = ItemToPlace;
            return ItemToReturn;
        } else {
            PQ->ItemArray[CurrentLoc] = PQ->ItemArray[ChildLoc];
            CurrentLoc = ChildLoc;
            ChildLoc = 2 * CurrentLoc;
        }
    }

    PQ->ItemArray[CurrentLoc] = ItemToPlace;
    return ItemToReturn;
}
