#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

int main(int argc, char *argv[]) {
    int N, maxN = atoi(argv[1]), sw = atoi(argv[2]);
    Key v;
    Item item;

    STinit(maxN);

    for (N = 0; N < maxN; N++) {
        if (sw)
            item = ITEMrand();
        else if (ITEMscan(&v) == EOF)
            break;
        else
            item.key = v;

        if (STsearch(key(item)).key != -1) continue;

        printf("Inserting item %d\n", item.key);
        STinsert(item);
    }

    printf("Sorted items:\n");
    STsort(ITEMshow);
    printf("\n");

    printf("%d keys total\n", N);
    printf("%d distinct keys\n", STcount());

    return 0;
}
