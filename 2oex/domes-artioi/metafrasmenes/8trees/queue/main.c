#include <stdio.h>
#include <stdlib.h>

#define MAXQUEUESIZE 100

// Define the structure of the tree node
typedef struct NodeTag {
    char Symbol;            // Data for the node (character symbol)
    struct NodeTag *LLink; // Pointer to the left child
    struct NodeTag *RLink; // Pointer to the right child
} TreeNode;

// Define a Queue for storing TreeNode pointers
typedef TreeNode *ItemType;
typedef struct {
    int Count;             // Number of elements in the queue
    int Front;             // Index of the front element
    int Rear;              // Index of the rear element
    ItemType Items[MAXQUEUESIZE]; // Array to hold the items (TreeNode pointers)
} Queue;

// Queue functions

// Initialize the queue
void InitializeQueue(Queue *Q) {
    Q->Count = 0;
    Q->Front = 0;
    Q->Rear = -1;
}

// Check if the queue is empty
int IsEmpty(Queue *Q) {
    return Q->Count == 0;
}

// Check if the queue is full
int IsFull(Queue *Q) {
    return Q->Count == MAXQUEUESIZE;
}

// Add an item to the queue (enqueue operation)
void Enqueue(Queue *Q, ItemType item) {
    if (IsFull(Q)) {
        printf("Queue is full. Cannot enqueue item.\n");
        return;
    }
    Q->Rear = (Q->Rear + 1) % MAXQUEUESIZE;
    Q->Items[Q->Rear] = item;
    Q->Count++;
}

// Remove an item from the queue (dequeue operation)
void Dequeue(Queue *Q, ItemType *item) {
    if (IsEmpty(Q)) {
        printf("Queue is empty. Cannot dequeue item.\n");
        return;
    }
    *item = Q->Items[Q->Front];
    Q->Front = (Q->Front + 1) % MAXQUEUESIZE;
    Q->Count--;
}

// Function to create a new tree node
TreeNode* CreateNode(char symbol) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->Symbol = symbol;
    newNode->LLink = NULL;
    newNode->RLink = NULL;
    return newNode;
}

int main(void) {
    // Initialize the queue
    Queue q;
    InitializeQueue(&q);

    // Create tree nodes and enqueue them into the queue
    TreeNode *nodeA = CreateNode('A');
    TreeNode *nodeB = CreateNode('B');
    TreeNode *nodeC = CreateNode('C');
    
    Enqueue(&q, nodeA);
    Enqueue(&q, nodeB);
    Enqueue(&q, nodeC);

    // Dequeue and print the items
    TreeNode *item;
    while (!IsEmpty(&q)) {
        Dequeue(&q, &item);
        printf("Dequeued node with symbol: %c\n", item->Symbol);
    }

    return 0;
}
