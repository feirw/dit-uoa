/* This is the file QueueTypes.h */
#define MAXQUEUESIZE 100
typedef int ItemType;
/* the item type can be arbitrary */

typedef struct {
    int Count;
    int Front;
    int Rear;
    ItemType Items[MAXQUEUESIZE];
} Queue;