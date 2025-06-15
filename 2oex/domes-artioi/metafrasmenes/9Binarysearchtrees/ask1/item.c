#include <stdlib.h>
#include <stdio.h>
#include "Item.h"

Key key(Item item) {
    return item.key;
}

int less(Key a, Key b) {
    return a < b;
}

int eq(Key a, Key b) {
    return a == b;
}

Item ITEMrand(void) {
    Item x;
    x.key = rand() % 1000;
    return x;
}

int ITEMscan(Key *v) {
    return scanf("%d", v);
}

void ITEMshow(Item item) {
    printf("%d ", item.key);
}
