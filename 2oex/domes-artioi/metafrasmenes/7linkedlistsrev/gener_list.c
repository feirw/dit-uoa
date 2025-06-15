typedef struct GenListTag {
    GenListTag *Link;
    int Atom;
    union SubNodeTag {
        ItemType Item;
        struct GenListTag *Sublist;
    } SubNode;
} GenListNode;

void PrintList(GenListNode *L){   
    GenListNode *G;
    printf("(");
    G=L;
    while (G != NULL){
        if (G->Atom){
            printf("%d", G->SubNode.Item);
        } else {
            printList(G->SubNode.SubList);
        }
        if (G->Link != NULL)printf(",");
            G=G->Link;
    }
    printf("");
}