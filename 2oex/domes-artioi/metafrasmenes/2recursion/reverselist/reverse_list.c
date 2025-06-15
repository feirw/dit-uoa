#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char AirportCode[4]; // 3 χαρακτήρες + 1 για το '\0'

typedef struct NodeTag {
    AirportCode Airport;  // Κωδικός αεροδρομίου (π.χ. "JFK")
    struct NodeTag *Link; // Δείκτης στον επόμενο κόμβο
} NodeType;

// **Συνάρτηση Αντιστροφής Συνδεδεμένης Λίστας (Επαναληπτική)**
void Reverse(NodeType **Head) {
    NodeType *ReversedList = NULL;   // Η νέα αντιστραμμένη λίστα
    NodeType *CurrentNode = *Head;   // Ο τρέχων κόμβος της αρχικής λίστας
    NodeType *NextNode = NULL;       // Ο επόμενος κόμβος

    while (CurrentNode != NULL) {
        NextNode = CurrentNode->Link; // Αποθήκευση επόμενου κόμβου
        CurrentNode->Link = ReversedList; // Αντιστροφή συνδέσμου
        ReversedList = CurrentNode; // Μετακίνηση της αντιστραμμένης λίστας
        CurrentNode = NextNode; // Προχωράμε στον επόμενο κόμβο
    }
    
    *Head = ReversedList; // Ενημερώνουμε τον δείκτη της λίστας
}

// **Συνάρτηση Εισαγωγής Κόμβου στην Αρχή της Λίστας**
void Insert(NodeType **Head, char *code) {
    NodeType *NewNode = (NodeType*)malloc(sizeof(NodeType));
    if (NewNode == NULL) {
        printf("Σφάλμα κατανομής μνήμης!\n");
        exit(1);
    }
    strcpy(NewNode->Airport, code);
    NewNode->Link = *Head;
    *Head = NewNode;
}

// **Συνάρτηση Εκτύπωσης Λίστας**
void PrintList(NodeType *Head) {
    while (Head != NULL) {
        printf("%s -> ", Head->Airport);
        Head = Head->Link;
    }
    printf("NULL\n");
}

// **Κύριο Πρόγραμμα (main)**
int main() {
    NodeType *Head = NULL;

    // Προσθήκη κόμβων στη λίστα
    Insert(&Head, "JFK");  // Νέα Υόρκη
    Insert(&Head, "LAX");  // Λος Άντζελες
    Insert(&Head, "ORD");  // Σικάγο
    Insert(&Head, "ATL");  // Ατλάντα

    // Εκτύπωση αρχικής λίστας
    printf("Αρχική λίστα:\n");
    PrintList(Head);

    // Αντιστροφή λίστας
    Reverse(&Head);

    // Εκτύπωση αντιστραμμένης λίστας
    printf("Αντιστροφή λίστας:\n");
    PrintList(Head);

    return 0;
}
