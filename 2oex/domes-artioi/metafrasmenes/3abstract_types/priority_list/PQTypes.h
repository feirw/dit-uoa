#define MAXCOUNT 10
typedef int PQItem;

typedef struct PQNodeTag {
    PQItem NodeItem;
    struct PQNodeTag *Link;
} PQListNode;

typedef struct {
    int Count;
    PQListNode *ItemList;
} PriorityQueue;
