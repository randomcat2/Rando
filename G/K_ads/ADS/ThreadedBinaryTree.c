#include <stdio.h>
#include <stdlib.h>

// Node structure for threaded binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int isThreaded; // Flag to indicate whether the right pointer is a thread or not
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
    newNode->isThreaded = 0;
    return newNode;
}

// Function to perform in-order traversal of threaded binary tree
void inOrder(struct Node* root) {
    struct Node* current = leftMost(root);
    while (current != NULL) {
        printf("%d ", current->data);

        if (current->isThreaded)
            current = current->right;
        else
            current = leftMost(current->right);
    }
}

// Function to find the leftmost node in a subtree
struct Node* leftMost(struct Node* node) {
    if (node == NULL)
        return NULL;
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Function to insert a new node into threaded binary tree
struct Node* insert(struct Node* root, int data) {
    // If the tree is empty, create a new node and make it root
    if (root == NULL)
        return createNode(data);

    // Otherwise, recur down the tree
    if (data < root->data) {
        // Insert into the left subtree
        root->left = insert(root->left, data);

        // Make the current node as a thread to its inorder predecessor
        if (root->left->right == NULL) {
            root->left->right = root;
            root->left->isThreaded = 1;
        }
    } else if (data > root->data) {
        // Insert into the right subtree
        if (root->isThreaded || root->right == NULL) {
            // If the current node is threaded or has no right child, create a new node
            struct Node* newNode = createNode(data);
            newNode->left = root;
            newNode->isThreaded = 1;
            newNode->right = root->right;
            root->right = newNode;
            root->isThreaded = 0;
        } else {
            // Insert into the right subtree
            root->right = insert(root->right, data);
        }
    }
    return root;
}

int main() {
    struct Node* root = NULL;
    root = insert(root, 10);
    insert(root, 5);
    insert(root, 20);
    insert(root, 3);
    insert(root, 7);

    printf("Inorder traversal of threaded binary tree: ");
    inOrder(root);
    printf("\n");

    return 0;
}
