#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#define M 10

int main(int argc, char *argv[]) {
    int i, j;
    if(argc < 2){
        return 1;

    }
    int N = atoi(argv[1]);
    QPointer queues[M];
    
    // Δημιουργία των M ουρών
    for (i = 0; i < M; i++) {
        queues[i] = QUEUEinit(N);
    }

    // Τοποθέτηση N στοιχείων στις ουρές
    for (i = 0; i < N; i++) {
        QUEUEput(queues[rand() % M], i);
    }

    // Εκτύπωση και αφαίρεση των στοιχείων από τις ουρές
    for (i = 0; i < M; i++, printf("\n")) {
        printf("Queue %d: ", i);
        while (!QUEUEempty(queues[i])) {
            printf("%3d ", QUEUEget(queues[i]));
        }
    }

    return 0;
}
