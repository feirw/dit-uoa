#include <stdlib.h>
#include <stdlib.h>
#include "interface.h"

typedef struct QUEUEnode* link;

struct QUEUEnode { 
    Item item; 
    link next; 
};
struct queue {
    link head;
    link tail;
};

link NEW(Item item, link next){
    link x = malloc(sizeof *x);
    x->item = item;
    x->next = next;
    return x;
}
QPointer QUEUEinit(int maxN){
    QPointer q = malloc(sizeof *q);
    q->head = NULL;
    q->tail = NULL;
    return q;
}

int QUEUEempty(QPointer q) {
    return q->head == NULL;
}

void QUEUEput(QPointer q, Item item){
    if (q->head == NULL){ 
    q->tail = NEW(item, q->head);
    q->head = q->tail;
    return;
    }
    q->tail->next = NEW(item, q->tail->next);
    q->tail = q->tail->next;
}

Item QUEUEget(QPointer q){
    Item item = q->head->item;
    link t = q->head->next;
    free(q->head);
    q->head = t;
    return item;
}
