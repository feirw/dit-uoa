#ifndef ITEM_H
#define ITEM_H

typedef int Key;

typedef struct {
    Key key;
} Item;

#define NULLitem (Item){-1}

// Βοηθητικές συναρτήσεις για το Item
Key key(Item item);
int less(Key a, Key b);
int eq(Key a, Key b);

// Χρήσιμες για το main
Item ITEMrand(void);
int ITEMscan(Key *v);
void ITEMshow(Item item);

#endif
