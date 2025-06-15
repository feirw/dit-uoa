#include <stdio.h>
#include <stdlib.h>
#include "STnode.h"

// === Υλοποίηση απλών τύπων και συναρτήσεων ===

typedef struct {
    int key;
    char value[50];
} Record;

Item NEWitem(int k, const char* val) {
    Record* r = malloc(sizeof(Record));
    r->key = k;
    snprintf(r->value, sizeof(r->value), "%s", val);
    return (Item)r;
}

Key key(Item item) {
    return ((Record*)item)->key;
}

int eq(Key a, Key b) {
    return a == b;
}

int less(Key a, Key b) {
    return a < b;
}

Item NULLitem = NULL;

// === Κύρια συνάρτηση ===

int main() {
    STinit(100);  // Αρχικοποίηση του B+-Tree

    // Εισαγωγή στοιχείων
    STinsert(NEWitem(10, "Alice"));
    STinsert(NEWitem(20, "Bob"));
    STinsert(NEWitem(5, "Charlie"));
    STinsert(NEWitem(15, "Diana"));
    STinsert(NEWitem(25, "Eve"));

    // Αναζήτηση
    Key searchKey = 15;
    Item found = STsearch(searchKey);
    if (found != NULLitem) {
        printf("Βρέθηκε: %s (Key: %d)\n", ((Record*)found)->value, ((Record*)found)->key);
    } else {
        printf("Το στοιχείο με κλειδί %d δεν βρέθηκε.\n", searchKey);
    }

    // Διαγραφή
    Key deleteKey = 20;
    printf("Διαγράφεται το στοιχείο με κλειδί %d...\n", deleteKey);
    STdelete(deleteKey);

    // Επιβεβαίωση διαγραφής
    Item check = STsearch(deleteKey);
    if (check == NULLitem) {
        printf("Το στοιχείο με κλειδί %d διαγράφηκε επιτυχώς.\n", deleteKey);
    } else {
        printf("Η διαγραφή απέτυχε για το κλειδί %d.\n", deleteKey);
    }

    return 0;
}
