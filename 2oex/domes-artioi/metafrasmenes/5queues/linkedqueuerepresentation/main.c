#include <stdio.h>
#include <stdlib.h>
#include "types.h"

int main(void){
    int i,j;
    Queue Q;
    InitializeQueue(&Q);
    for(i=1; i<10; ++i){
        Insert(i, &Q);
    }
    while (!Empty(&Q)){
        Remove(&Q, &j);
        printf("Item %d has been removed.\n", j);
    }
return 0;
}