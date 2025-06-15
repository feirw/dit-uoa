#include <stdio.h>
#include "interface.h"

int main(){
    Queue q;
    InitializeQueue(&q);
    Empty(&q);
    Full(&q);
    Insert(10,&q);
    Insert(11,&q);
    Insert(12,&q);
    Insert(13,&q);
    return 0;

}