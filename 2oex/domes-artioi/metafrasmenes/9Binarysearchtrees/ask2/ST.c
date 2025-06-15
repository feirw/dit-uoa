#include <stdlib.h>
#include "ST.h"

link z = NULL;
link head = NULL;

static link NEW(Item item, link l, link r, int N) {
    link x = malloc(sizeof(*x));
    x->item = item;
    x->l = l;
    x->r = r;
    x->N = N;
    return x;
}

void STinit(int maxN) {
    z = NEW(NULLitem, NULL, NULL, 0);
    head = z;
}

static int count(link h) {
    if (h == z) return 0;
    return h->N;
}

int STcount(void) {
    return count(head);
}

static link rotR(link h) {
    link x = h->l;
    h->l = x->r;
    x->r = h;
    h->N = count(h->l) + count(h->r) + 1;
    x->N = count(x->l) + count(x->r) + 1;
    return x;
}

static link rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l = h;
    h->N = count(h->l) + count(h->r) + 1;
    x->N = count(x->l) + count(x->r) + 1;
    return x;
}

static link insertT(link h, Item item) {
    Key v = key(item);
    if (h == z) return NEW(item, z, z, 1);
    if (less(v, key(h->item))) {
        h->l = insertT(h->l, item);
        h = rotR(h);
    } else {
        h->r = insertT(h->r, item);
        h = rotL(h);
    }
    h->N = count(h->l) + count(h->r) + 1;
    return h;
}

void STinsert(Item item) {
    head = insertT(head, item);
}

Item STsearch(Key v) {
    link x = head;
    while (x != z) {
        if (eq(v, key(x->item))) return x->item;
        else if (less(v, key(x->item))) x = x->l;
        else x = x->r;
    }
    return NULLitem;
}

static void sortR(link h, void (*visit)(Item)) {
    if (h == z) return;
    sortR(h->l, visit);
    visit(h->item);
    sortR(h->r, visit);
}

void STsort(void (*visit)(Item)) {
    sortR(head, visit);
}

static Item selectR(link h, int k) {
    int t = count(h->l);
    if (h == z) return NULLitem;
    if (t > k) return selectR(h->l, k);
    if (t < k) return selectR(h->r, k - t - 1);
    return h->item;
}

Item STselect(int k) {
    return selectR(head, k);
}

link STjoin(link a, link b) {
    if (a == z) return b;
    if (b == z) return a;
    b = insertT(b, a->item);
    b->l = STjoin(a->l, b->l);
    b->r = STjoin(a->r, b->r);
    free(a);
    b->N = count(b->l) + count(b->r) + 1;
    return b;
}

// link STjoin(link a, link b) {
//     return STjoin(a, b);
// }

static link deleteR(link h, Key v) {
    if (h == z) return z;
    if (less(v, key(h->item))) h->l = deleteR(h->l, v);
    else if (less(key(h->item), v)) h->r = deleteR(h->r, v);
    else {
        link x = h;
        h = STjoin(h->l, h->r);
        free(x);
    }
    if (h != z)
        h->N = count(h->l) + count(h->r) + 1;
    return h;
}

void STdelete(Key v) {
    head = deleteR(head, v);
}
