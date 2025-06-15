typedef char ItemType;

typedef struct StackNodeTag {
    ItemType Item;
    struct StackNodeTag *Link;
} StackNode;

typedef struct {
    StackNode *ItemList;
} Stack;

