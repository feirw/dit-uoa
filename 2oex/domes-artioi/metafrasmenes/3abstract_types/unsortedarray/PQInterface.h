#include "PQTypes.h"
void Initialize(PriorityQueue *PQ);
int Empty(PriorityQueue *PQ);
int Full(PriorityQueue *PQ);
void Insert(PQItem Item, PriorityQueue *PQ);
PQItem Remove(PriorityQueue *PQ);

// Νέα συνάρτηση για την απόκρυψη του Count
int GetCount(PriorityQueue *PQ);  // Επιστρέφει τον αριθμό των στοιχείων στην ουρά

