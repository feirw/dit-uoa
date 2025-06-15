
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char AirportCode[4]; // Ορισμός τύπου AirportCode για την αποθήκευση 3-χαρακτηρη αεροδρομίου
typedef struct NodeTag {
    AirportCode Airport;       // Αποθηκεύει τον κωδικό του αεροδρομίου
    struct NodeTag *Link;      // Δείκτης στον επόμενο κόμβο της λίστας
} NodeType;

typedef NodeType *NodePointer; // Δείκτης σε NodeType


void PrintList(NodeType *L)
{
    NodeType *N;
    printf("(");
    N = L;
    while (N != NULL) {
        printf("%s", N->Airport);
        N = N->Link;
        if (N != NULL) printf(",");
    }
    printf(")\n");
}
void InsertNewLastNode(char *A, NodeType **L)
{
    NodeType *N, *P;
    
    // Δημιουργία νέου κόμβου
    N = (NodeType *)malloc(sizeof(NodeType));
    strcpy(N->Airport, A);
    N->Link = NULL;  // Ο τελευταίος κόμβος δείχνει σε NULL
    
    // Εάν η λίστα είναι κενή, το νέο στοιχείο γίνεται η αρχή της λίστας
    if (*L == NULL) {
        *L = N;
    } else {
        // Διατρέχουμε τη λίστα μέχρι να βρούμε τον τελευταίο κόμβο
        P = *L;
        while (P->Link != NULL) {
            P = P->Link;
        }
        
        // Εισάγουμε το νέο κόμβο στο τέλος της λίστας
        P->Link = N;
    }
}
void DeleteLastNode(NodeType **L)
{
    NodeType *PreviousNode, *CurrentNode;
    
    // Ελέγχουμε αν η λίστα δεν είναι κενή
    if (*L != NULL) {
        
        // Εάν η λίστα έχει μόνο έναν κόμβο
        if ((*L)->Link == NULL){
            free(*L);   // Απελευθερώνουμε τον κόμβο
            *L = NULL;  // Ορίζουμε τη λίστα σε NULL
        } else {
            // Εάν η λίστα έχει περισσότερους από έναν κόμβους
            PreviousNode = *L;
            CurrentNode = (*L)->Link;
            
            // Διατρέχουμε τη λίστα για να φτάσουμε στον τελευταίο κόμβο
            while (CurrentNode->Link != NULL){
                PreviousNode = CurrentNode;
                CurrentNode = CurrentNode->Link;
            }
            
            // Αφαιρούμε το τελευταίο κόμβο
            PreviousNode->Link = NULL;
            free(CurrentNode);  // Απελευθερώνουμε τη μνήμη του τελευταίου κόμβου
        }
    }
}
NodeType *ListSearch(char *A, NodeType *L)
{
    NodeType *N;
    N = L;
    while (N != NULL) {
        if (strcmp(N->Airport, A) == 0) {
            return N;
        } else {
            N = N->Link;
        }
    }
    return NULL;
}
void InsertNewSecondNode(void){
    NodeType *N;
    NodeType *L;
    N=(NodeType *)malloc(sizeof(NodeType));
    strcpy(N->Airport,"BRU");
    N->Link=L->Link;
    L->Link=N;
}

int main(void)
{
    NodeType *L; // Δείκτης στη λίστα των αεροδρομίων
    L = NULL;     // Αρχικοποιούμε τη λίστα ως κενή

    PrintList(L); // Εκτυπώνουμε την κενή λίστα

    /* Εισαγωγή νέων κόμβων στη λίστα */
    InsertNewLastNode("DUS", &L);
    InsertNewLastNode("ORD", &L);
    InsertNewLastNode("SAN", &L);

    PrintList(L); // Εκτυπώνουμε τη λίστα μετά τις εισαγωγές

    /* Διαγραφή του τελευταίου κόμβου */
    DeleteLastNode(&L);

    PrintList(L); // Εκτυπώνουμε τη λίστα μετά τη διαγραφή του τελευταίου κόμβου

    /* Έλεγχος αν ο κόμβος "DUS" υπάρχει στη λίστα */
    if (ListSearch("DUS", L) != NULL) {
        printf("DUS is an element of the list\n");
    }
}

/* Ο κώδικας για τις συναρτήσεις InsertNewLastNode, PrintList, */
/* ListSearch και DeleteLastNode παρατίθεται παρακάτω. */
