#ifndef ST_H
#define ST_H

#include "Item.h"

typedef struct node* link;

typedef struct node {
    Item item;
    link l, r;
    int N;
} node;

extern link head;
extern link z;

void STinit(int maxN);
void STinsert(Item item);
Item STsearch(Key v);
void STsort(void (*visit)(Item));
Item STselect(int k);
void STdelete(Key v);
int STcount(void);
link STjoin(link a, link b);

#endif
