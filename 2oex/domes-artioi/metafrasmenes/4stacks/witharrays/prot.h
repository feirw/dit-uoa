typedef char ItemType;
#define MAX 100

typedef struct {
    ItemType items[100];
    int top;
} Stack;

void InitializeStack(Stack *);
int Empty(Stack *);
int Full(Stack *);
void Push(ItemType, Stack *);
void Pop(Stack *, ItemType *);