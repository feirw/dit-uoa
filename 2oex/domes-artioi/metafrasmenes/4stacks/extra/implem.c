#include <stdlib.h>
#include "Item.h"
#include "STACK.h"

static Item *s;  // Δείκτης στον πίνακα που θα αποθηκεύει τα στοιχεία της στοίβας
static int N;    // Μετρητής για τον αριθμό των στοιχείων στην στοίβα

void STACKinit(int maxN)
{
    s = malloc(maxN * sizeof(Item));  // Κατανομή μνήμης για το μέγεθος του πίνακα
    N = 0;  // Αρχικοποίηση της στοίβας ως κενή
}

int STACKempty()
{
    return N == 0;  // Επιστρέφει 1 αν η στοίβα είναι κενή, αλλιώς 0
}

void STACKpush(Item item)
{
    s[N++] = item;  // Προσθήκη του στοιχείου στη στοίβα και αύξηση του μετρητή N
}

Item STACKpop()
{
    return s[--N];  // Αφαίρεση του τελευταίου στοιχείου από τη στοίβα και επιστροφή του
}
