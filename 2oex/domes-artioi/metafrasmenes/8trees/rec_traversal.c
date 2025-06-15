#include <stdio.h>
#include <stdlib.h>

// Define a structure for a binary tree node
typedef struct NodeTag {
    char Symbol;             // Data for the node (character symbol)
    struct NodeTag *LLink;  // Pointer to the left child
    struct NodeTag *RLink;  // Pointer to the right child
} TreeNode;

// Enum to specify the type of traversal
typedef enum { PreOrder, InOrder, PostOrder } OrderOfTraversal;

// Function to visit a node and print its symbol
void Visit(TreeNode *T) {
    printf("%c\n", T->Symbol);  // Print the symbol of the node
}

// Function to traverse the tree
void Traverse(TreeNode *T, OrderOfTraversal TraversalOrder) {
    if (T != NULL) {
        // PreOrder Traversal
        if (TraversalOrder == PreOrder) {
            Visit(T);                           // Visit the node first
            Traverse(T->LLink, PreOrder);       // Traverse the left subtree
            Traverse(T->RLink, PreOrder);       // Traverse the right subtree
        }
        // InOrder Traversal
        else if (TraversalOrder == InOrder) {
            Traverse(T->LLink, InOrder);        // Traverse the left subtree
            Visit(T);                           // Visit the node
            Traverse(T->RLink, InOrder);        // Traverse the right subtree
        }
        // PostOrder Traversal
        else if (TraversalOrder == PostOrder) {
            Traverse(T->LLink, PostOrder);      // Traverse the left subtree
            Traverse(T->RLink, PostOrder);      // Traverse the right subtree
            Visit(T);                           // Visit the node last
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

    // Test the different traversals
    printf("PreOrder Traversal:\n");
    Traverse(T, PreOrder);

    printf("\nInOrder Traversal:\n");
    Traverse(T, InOrder);

    printf("\nPostOrder Traversal:\n");
    Traverse(T, PostOrder);

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
