#include <stdio.h>
#include "PQInterface.h"

int main() {
    PriorityQueue PQ;
    Initialize(&PQ);

    PQItem inputItems[] = {15, 3, 22, 7, 9};
    int n = sizeof(inputItems) / sizeof(PQItem);

    printf("Εισαγωγή στοιχείων:\n");
    for (int i = 0; i < n; ++i) {
        printf("  ➤ Εισάγεται το: %d\n", inputItems[i]);
        Insert(inputItems[i], &PQ);
    }

    printf("\n Αφαίρεση στοιχείων κατά προτεραιότητα:\n");
    while (!Empty(&PQ)) {
        PQItem item = Remove(&PQ);
        printf("  ➤ Αφαιρέθηκε το: %d\n", item);
    }

    return 0;
}
