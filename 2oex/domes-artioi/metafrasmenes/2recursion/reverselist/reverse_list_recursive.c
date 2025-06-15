#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char AirportCode[4]; // Ο κωδικός του αεροδρομίου (3 χαρακτήρες + 1 για το '\0')

typedef struct NodeTag {
    AirportCode Airport;  // Κωδικός αεροδρομίου
    struct NodeTag *Next; // Δείκτης στον επόμενο κόμβο της λίστας
} NodeType;

// **Αναδρομική Συνάρτηση Αντιστροφής Λίστας**
NodeType* ReverseRecursive(NodeType *CurrentNode, NodeType *PreviousNode) {
    if (CurrentNode == NULL) {
        return PreviousNode;  // Αν φτάσουμε στο τέλος, επιστρέφουμε τη νέα κορυφή
    }
    NodeType *NextNode = CurrentNode->Next;  // Αποθηκεύουμε τον επόμενο κόμβο
    CurrentNode->Next = PreviousNode;        // Αντιστροφή συνδέσμου
    return ReverseRecursive(NextNode, CurrentNode); // Αναδρομή με τον επόμενο κόμβο
}

// **Βοηθητική Συνάρτηση για να Καλέσουμε την Αναδρομική**
void Reverse(NodeType **Head) {
    *Head = ReverseRecursive(*Head, NULL);
}

// **Συνάρτηση για Εισαγωγή Νέου Κόμβου στην Αρχή της Λίστας**
void Insert(NodeType **Head, char *code) {
    NodeType *NewNode = (NodeType*)malloc(sizeof(NodeType));
    strcpy(NewNode->Airport, code);
    NewNode->Next = *Head;
    *Head = NewNode;
}

// **Συνάρτηση Εκτύπωσης Λίστας**
void PrintList(NodeType *Head) {
    while (Head != NULL) {
        printf("%s -> ", Head->Airport);
        Head = Head->Next;
    }
    printf("NULL\n");
}

// **Δοκιμή**
int main() {
    NodeType *Head = NULL;

    Insert(&Head, "JFK");  // Προσθήκη κόμβων
    Insert(&Head, "LAX");
    Insert(&Head, "ORD");
    Insert(&Head, "ATL");

    printf("Αρχική λίστα:\n");
    PrintList(Head);

    Reverse(&Head);
    
    printf("Αντιστροφή λίστας:\n");
    PrintList(Head);

    return 0;
}
