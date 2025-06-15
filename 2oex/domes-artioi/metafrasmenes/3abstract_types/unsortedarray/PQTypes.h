#define MAXCOUNT 10
typedef int PQItem;
typedef PQItem PQArray[MAXCOUNT];

typedef struct {
    int Count;
    PQArray ItemArray;
} PriorityQueue;