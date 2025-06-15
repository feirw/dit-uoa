#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

int main(int argc, char *argv[]) {
    int i, N;
    Item *items;

    if (argc != 3) {
        printf("Usage: %s <N> <mode>\n", argv[0]);
        printf("mode = 0 for manual input, 1 for random\n");
        return 1;
    }

    N = atoi(argv[1]);
    int mode = atoi(argv[2]);

    items = malloc(N * sizeof(Item));

    for (i = 0; i < N; i++) {
        if (mode == 1) {
            items[i] = ITEMrand();
        } else {
            Key v;
            printf("Enter key for item %d: ", i + 1);
            if (ITEMscan(&v) == EOF) break;
            items[i].key = v;
        }
    }

    printf("Items:\n");
    for (i = 0; i < N; i++) {
        ITEMshow(items[i]);
    }
    printf("\n");

    free(items);
    return 0;
}
