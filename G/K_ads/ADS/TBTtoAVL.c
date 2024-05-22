#include <stdio.h>
#include <stdlib.h>

// Node structure for threaded binary tree
struct ThreadedNode {
    int data;
    struct ThreadedNode* left;
    struct ThreadedNode* right;
    int isThreaded; // Flag to indicate whether the right pointer is a thread or not
};

// Node structure for AVL tree
struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

// Function to create a new threaded node
struct ThreadedNode* createThreadedNode(int data) {
    struct ThreadedNode* newNode = (struct ThreadedNode*)malloc(sizeof(struct ThreadedNode));
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

// Function to create a new AVL node
struct AVLNode* createAVLNode(int data) {
    struct AVLNode* newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to perform in-order traversal of threaded binary tree
void inOrder(struct ThreadedNode* root, int arr[], int* index) {
    if (root == NULL)
        return;
    inOrder(root->left, arr, index);
    arr[(*index)++] = root->data;
    if (root->isThreaded)
        return;
    inOrder(root->right, arr, index);
}

// Function to construct a balanced AVL tree from a sorted array
struct AVLNode* sortedArrayToAVL(int arr[], int start, int end) {
    if (start > end)
        return NULL;
    int mid = (start + end) / 2;
    struct AVLNode* root = createAVLNode(arr[mid]);
    root->left = sortedArrayToAVL(arr, start, mid - 1);
    root->right = sortedArrayToAVL(arr, mid + 1, end);
    return root;
}

// Function to convert a threaded binary tree to AVL tree
struct AVLNode* threadedBSTtoAVL(struct ThreadedNode* root) {
    // Step 1: Perform in-order traversal of threaded binary tree to get sorted elements
    int size = 0;
    inOrder(root, NULL, &size);
    int* sortedArray = (int*)malloc(size * sizeof(int));
    int index = 0;
    inOrder(root, sortedArray, &index);

    // Step 2: Construct AVL tree from sorted array
    struct AVLNode* avlRoot = sortedArrayToAVL(sortedArray, 0, size - 1);

    free(sortedArray);

    return avlRoot;
}

// Function to perform in-order traversal of AVL tree
void inOrderAVL(struct AVLNode* root) {
    if (root == NULL)
        return;
    inOrderAVL(root->left);
    printf("%d ", root->data);
    inOrderAVL(root->right);
}

int main() {
    // Sample threaded binary tree
    struct ThreadedNode* root = createThreadedNode(10);
    root->left = createThreadedNode(5);
    root->right = createThreadedNode(20);
    root->left->left = createThreadedNode(3);
    root->left->right = createThreadedNode(7);
    root->left->right->right = root;

    // Convert threaded binary tree to AVL tree
    struct AVLNode* avlRoot = threadedBSTtoAVL(root);

    // Print the AVL tree in-order
    printf("In-order traversal of AVL tree: ");
    inOrderAVL(avlRoot);
    printf("\n");

    return 0;
}
