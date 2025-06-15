#include <stdio.h>
#include "PQInterface.h"

typedef PQItem SortingArray[MAXCOUNT];  // Ορίζουμε τον τύπο για τον πίνακα

void PriorityQueueSort(SortingArray A) {
    int i;
    PriorityQueue PQ;
    Initialize(&PQ);
    
    // Εισάγουμε τα στοιχεία στην ουρά προτεραιότητας
    for (i = 0; i < MAXCOUNT; ++i) {
        Insert(A[i], &PQ);
    }
    
    // Χρησιμοποιούμε την νέα συνάρτηση GetCount για να αποφεύγουμε την άμεση πρόσβαση στο Count
    printf(" Η ουρά περιέχει %d στοιχεία\n", GetCount(&PQ));
    
    // Αφαιρούμε τα στοιχεία από την ουρά και τα τοποθετούμε στον πίνακα
    for (i = MAXCOUNT - 1; i >= 0; --i) {
        A[i] = Remove(&PQ);
    }
}

int main(void) {
    int i;
    SortingArray A;

    // Γέμισμα του πίνακα με τιμές
    for (i = 0; i < 10; ++i) {
        A[i] = 3 * i - 13;
        printf("%d ", A[i]);
    }
    printf("\n");

    // Ταξινόμηση του πίνακα
    PriorityQueueSort(A);

    // Εμφάνιση των ταξινομημένων τιμών
    for (i = 0; i < 10; ++i) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
