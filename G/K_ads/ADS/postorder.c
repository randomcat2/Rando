#include <stdio.h>
#include <stdlib.h>

// Node structure for binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Structure for stack
struct StackNode {
    struct Node* node;
    int visited;
    struct StackNode* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create a new stack node
struct StackNode* createStackNode(struct Node* node) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->node = node;
    newNode->visited = 0;
    newNode->next = NULL;
    return newNode;
}

// Function to push a node onto the stack
void push(struct StackNode** topRef, struct Node* node) {
    struct StackNode* newNode = createStackNode(node);
    newNode->next = *topRef;
    *topRef = newNode;
}

// Function to pop a node from the stack
struct Node* pop(struct StackNode** topRef) {
    if (*topRef == NULL) {
        printf("Stack is empty!\n");
        exit(1);
    }
    struct StackNode* temp = *topRef;
    *topRef = (*topRef)->next;
    struct Node* poppedNode = temp->node;
    free(temp);
    return poppedNode;
}

// Function to perform postorder traversal of BST using a stack
void postOrderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    struct StackNode* stack = NULL;
    struct Node* current = root;
    struct Node* lastVisited = NULL;

    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        current = stack->node;

        if (current->right == NULL || current->right == lastVisited) {
            printf("%d ", current->data);
            lastVisited = current;
            pop(&stack);
            current = NULL;
        } else {
            current = current->right;
        }
    }
}

int main() {
    struct Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(3);
    root->left->right = createNode(7);

    printf("Postorder traversal of the BST: ");
    postOrderTraversal(root);
    printf("\n");

    return 0;
}
