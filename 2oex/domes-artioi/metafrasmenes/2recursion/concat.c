#include <stdio.h>
#include <stdlib.h>

// Ορισμός του τύπου NodeType για τα στοιχεία της συνδεδεμένης λίστας
typedef struct NodeType {
    int data;            // Αποθήκευση δεδομένων
    struct NodeType *Link; // Σύνδεση με τον επόμενο κόμβο
} NodeType;

// Συνάρτηση για την εκτύπωση μιας συνδεδεμένης λίστας
void PrintList(NodeType *head) {
    NodeType *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->Link;
    }
    printf("NULL\n");
}

// Συνάρτηση για την προσθήκη ενός κόμβου στην αρχή της λίστας
NodeType* InsertAtHead(NodeType *head, int value) {
    NodeType *newNode = (NodeType *)malloc(sizeof(NodeType));
    newNode->data = value;
    newNode->Link = head;
    return newNode;
}

// Συνάρτηση για την συγχώνευση (σύνδεση) δύο συνδεδεμένων λιστών
NodeType* Concat(NodeType *L1, NodeType *L2) {
    NodeType *N;
    if (L1 == NULL) {
        return L2;
    } else {
        N = L1;
        while (N->Link != NULL) {
            N = N->Link; // Προχωράμε στον επόμενο κόμβο μέχρι να φτάσουμε στον τελευταίο
        }
        N->Link = L2; // Συνδέουμε τον τελευταίο κόμβο του L1 με την αρχή του L2
        return L1;
    }
}

int main() {
    NodeType *L1 = NULL, *L2 = NULL;
    
    // Δημιουργία και εισαγωγή στοιχείων στη λίστα L1
    L1 = InsertAtHead(L1, 3);
    L1 = InsertAtHead(L1, 2);
    L1 = InsertAtHead(L1, 1);
    
    // Δημιουργία και εισαγωγή στοιχείων στη λίστα L2
    L2 = InsertAtHead(L2, 6);
    L2 = InsertAtHead(L2, 5);
    L2 = InsertAtHead(L2, 4);

    printf("Λίστα 1 (L1): ");
    PrintList(L1);

    printf("Λίστα 2 (L2): ");
    PrintList(L2);

    // Σύνδεση των δύο λιστών L1 και L2
    L1 = Concat(L1, L2);

    printf("Συγχωνευμένη Λίστα (L1 + L2): ");
    PrintList(L1);

    // Ελευθέρωση της μνήμης (δεν είναι υποχρεωτική για το συγκεκριμένο παράδειγμα, αλλά καλό είναι να γίνεται στην πράξη)
    while (L1 != NULL) {
        NodeType *temp = L1;
        L1 = L1->Link;
        free(temp);
    }

    return 0;
}
