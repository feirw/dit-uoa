#ifndef STNODE_H
#define STNODE_H

#define M 4  // Τάξη δέντρου

typedef int Key;
typedef void* Item;

typedef struct STnode* link;

typedef struct {
    Key key;
    union {
        link next;
        Item item;
    } ref;
} entry;

struct STnode {
    entry b[M];
    int m;
};

// Global variables
extern link head;
extern int H, N;
extern Item NULLitem;

// Function declarations
link NEW();
void STinit(int maxN);
void STinsert(Item item);
Item STsearch(Key v);
void STdelete(Key v);
link insertR(link h, Item item, int H);
link split(link h);
link deleteR(link h, Key v, int H);
int eq(Key a, Key b);
int less(Key a, Key b);
Key key(Item item);

#endif
