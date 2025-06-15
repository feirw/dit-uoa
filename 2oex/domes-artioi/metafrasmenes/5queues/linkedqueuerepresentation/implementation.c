/* This is the file QueueImplementation.c */
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void InitializeQueue(Queue *Q){
    Q->Front=NULL;
    Q->Rear=NULL;
}
int Empty(Queue *Q) {
    return(Q->Front==NULL);
}
int Full(Queue *Q){
    return(0);
}
/* We assume an already constructed queue */
/* is not full since it can potentially grow */
/* as a linked structure. */

void Insert(ItemType R, Queue *Q){
    QueueNode *Temp;
    Temp=(QueueNode *)malloc(sizeof(QueueNode));
    if (Temp==NULL){
        printf("System storage is exhausted");
    } else {
        Temp->Item=R;
        Temp->Link=NULL;
    }
    
    if (Q->Rear==NULL){ /* this is the case when the queue is empty */
        Q->Front=Temp;
        Q->Rear=Temp;
    } else { /* this is the case when the queue is not empty */
        Q->Rear->Link=Temp;
        Q->Rear=Temp;
    }
}

void Remove(Queue *Q, ItemType *F) {
    QueueNode *Temp;
    if (Q->Front==NULL){
        printf("attempt to remove item from an empty queue");
    } else {
        *F=Q->Front->Item;
        Temp=Q->Front;
        Q->Front=Temp->Link;
        free(Temp);
        if (Q->Front==NULL){
            Q->Rear=NULL;
        }  
    }
}
