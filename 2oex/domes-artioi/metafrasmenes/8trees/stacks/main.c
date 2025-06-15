#include <stdio.h>
#include <stdlib.h>


// Define the structure of the tree node
typedef struct NodeTag {
    char Symbol;            // Data for the node (character symbol)
    struct NodeTag *LLink; // Pointer to the left child
    struct NodeTag *RLink; // Pointer to the right child
} TreeNode;

// Define a simple stack structure
typedef struct Stack {
    TreeNode *items[100]; // Stack to hold tree nodes
    int top;              // Index of the top element
} Stack;

// Stack functions (Initialize, Push, Pop, Empty)
void InitializeStack(Stack *S) {
    S->top = -1;
}

int Empty(Stack *S) {
    return S->top == -1;
}

void Push(TreeNode *N, Stack *S) {
    if (S->top < 99) {  // Check if there is space in the stack
        S->items[++(S->top)] = N;
    }
}

void Pop(Stack *S, TreeNode **N) {
    if (!Empty(S)) {
        *N = S->items[(S->top)--];
    }
}

// PreOrder traversal using a stack
void PreOrderTraversal(TreeNode *T) {
    Stack S;
    TreeNode *N;
    InitializeStack(&S);
    Push(T, &S);

    while (!Empty(&S)) {
        Pop(&S, &N);
        if (N != NULL) {
            printf("%c\n", N->Symbol);  // Visit the node
            Push(N->RLink, &S);         // Push right child
            Push(N->LLink, &S);         // Push left child
        }
    }
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
    // Create a simple binary tree for testing
    TreeNode *T = CreateNode('A');
    T->LLink = CreateNode('B');
    T->RLink = CreateNode('C');
    T->LLink->LLink = CreateNode('D');
    T->LLink->RLink = CreateNode('E');
    T->RLink->LLink = CreateNode('F');
    T->RLink->RLink = CreateNode('G');

    // Perform PreOrder traversal
    printf("PreOrder Traversal:\n");
    PreOrderTraversal(T);

    // Free the allocated memory for the tree nodes
    free(T->RLink->RLink);
    free(T->RLink->LLink);
    free(T->LLink->RLink);
    free(T->LLink->LLink);
    free(T->RLink);
    free(T->LLink);
    free(T);

    return 0;
}
