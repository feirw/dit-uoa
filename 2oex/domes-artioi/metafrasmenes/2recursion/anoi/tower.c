#include <stdio.h>
//χρονικη πολυπλοκοτητα Ο(2^ν)

// Συνάρτηση που επιλύει το πρόβλημα του Πύργου του Χόανι
void MoveTowers(int n, int start, int finish, int spare) {
    if (n == 1) {
        // Αν έχουμε μόνο έναν δίσκο, απλά τον μεταφέρουμε
        printf("Move a disk from peg %1d to peg %1d\n", start, finish);
    } else {
        // Μετακινούμε τους n-1 δίσκους από τον start στον spare
        MoveTowers(n-1, start, spare, finish);
        // Μετακινούμε τον τελευταίο δίσκο από τον start στον finish
        printf("Move a disk from peg %1d to peg %1d\n", start, finish);
        // Μετακινούμε τους n-1 δίσκους από τον spare στον finish
        MoveTowers(n-1, spare, finish, start);
    }
}

int main() {
    int n;

    // Ζητάμε από τον χρήστη τον αριθμό των δίσκων
    printf("Enter the number of disks: ");
    scanf("%d", &n);

    // Καλούμε τη συνάρτηση MoveTowers για να λύσουμε το πρόβλημα
    // Τα 1, 2, 3 είναι οι τρεις στύλοι (1: Αρχικός, 2: Ενδιάμεσος, 3: Τελικός)
    MoveTowers(n, 1, 3, 2);

    return 0;
}
