#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STnode.h"

link head;  // Δείκτης στην κορυφή του δέντρου
int H, N;   // Υψος και αριθμός στοιχείων του δέντρου

// Dummy για να μην κρασάρει
link adjustNode(link h, int j, link u) {
    return NULL;
}


// Δημιουργία νέου κόμβου
link NEW() {
    link x = malloc(sizeof *x);
    x->m = 0;
    return x;
}

// Αρχικοποίηση του B+-Tree
void STinit(int maxN) {
    head = NEW();
    H = 0;
    N = 0;
}

// Αναδρομική αναζήτηση
Item searchR(link h, Key v, int H) {
    int j;
    if (H == 0) {
        for (j = 0; j < h->m; j++) {
            if (eq(v, h->b[j].key)) {
                return h->b[j].ref.item;
            }
        }
    } else {
        for (j = 0; j < h->m; j++) {
            if ((j + 1 == h->m) || less(v, h->b[j + 1].key)) {
                return searchR(h->b[j].ref.next, v, H - 1);
            }
        }
    }
    return NULLitem;
}

// Δημόσια συνάρτηση αναζήτησης
Item STsearch(Key v) {
    return searchR(head, v, H);
}

// Εισαγωγή νέου στοιχείου στον B+-Tree
void STinsert(Item item) {
    link t, u = insertR(head, item, H);
    if (u == NULL) return;
    t = NEW();
    t->m = 2;
    t->b[0].key = head->b[0].key;
    t->b[0].ref.next = head;
    t->b[1].key = u->b[0].key;
    t->b[1].ref.next = u;
    head = t;
    H++;
}

// Αναδρομική εισαγωγή
link insertR(link h, Item item, int H) {
    int i, j;
    Key v = key(item);
    entry x;
    link u;
    x.key = v;
    x.ref.item = item;

    if (H == 0) {
        for (j = 0; j < h->m; j++) {
            if (less(v, h->b[j].key)) break;
        }
    }

    if (H != 0) {
        for (j = 0; j < h->m; j++) {
            if ((j + 1 == h->m) || less(v, h->b[j + 1].key)) {
                u = insertR(h->b[j++].ref.next, item, H - 1);
                if (u == NULL) return NULL;
                x.key = u->b[0].key;
                x.ref.next = u;
                break;
            }
        }
    }

    for (i = ++(h->m); (i > j) && (i != M); i--)
        h->b[i] = h->b[i - 1];
    h->b[j] = x;

    if (h->m < M) return NULL;
    else return split(h);
}

// Διαχωρισμός κόμβου
link split(link h) {
    int j;
    link t = NEW();
    for (j = 0; j < M / 2; j++) {
        t->b[j] = h->b[M / 2 + j];
    }
    h->m = M / 2;
    t->m = M / 2;
    return t;
}

// Αναδρομική διαγραφή
link deleteR(link h, Key v, int H) {
    int j;
    if (H == 0) {
        for (j = 0; j < h->m; j++) {
            if (eq(v, h->b[j].key)) {
                for (; j < h->m - 1; j++) {
                    h->b[j] = h->b[j + 1];
                }
                h->m--;
                return NULL;
            }
        }
    }

    if (H != 0) {
        for (j = 0; j < h->m; j++) {
            if ((j + 1 == h->m) || less(v, h->b[j + 1].key)) {
                link u = deleteR(h->b[j].ref.next, v, H - 1);
                if (u == NULL) return NULL;

                if (h->b[j].ref.next->m < M / 2) {
                    return adjustNode(h, j, u);
                }
                break;
            }
        }
    }
    return NULL;
}

// Κύρια συνάρτηση διαγραφής
void STdelete(Key v) {
    link u = deleteR(head, v, H);
    if (u != NULL) {
        if (head->m == 0) {
            head = head->b[0].ref.next;
            H--;
        }
    }
}
