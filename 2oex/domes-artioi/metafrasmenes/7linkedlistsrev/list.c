typedef char AirportCode[4];

typedef struct NodeTag {
    AirportCode Airport;
    struct NodeTag *Link;
} NodeType;
 
typedef NodeType *NodePointer;

void PrintItem(int i, NodeType *L){
    while ((i > 1) && (L != NULL)){
        L=L->Link;
        i--;
    }
    if ((i == 1) && (L != NULL)){
        printf(“%s”, L->Item);
    } else {
        printf("Error – attempt to print an item that is not on the list.\n");
    }
}