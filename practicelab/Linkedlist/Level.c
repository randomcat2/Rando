// C program to demonstrate searching operation
// in binary search tree without recursion
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Function to check the given key exist or not
int iterativeSearch(struct Node* root, int key)
{
    // Traverse until root reaches to dead end
    while (root != NULL) {
        // pass right subtree as new tree
        if (key > root->data)
            root = root->right;

        // pass left subtree as new tree
        else if (key < root->data)
            root = root->left;
        else
            return 1; // if the key is found return 1
    }
    return 0;
}

// A utility function to create a new BST Node
struct Node* newNode(int item)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

/* A utility function to insert a new Node with
given key in BST */
struct Node* insert(struct Node* node, int data)
{
    /* If the tree is empty, return a new Node */
    if (node == NULL)
        return newNode(data);

    /* Otherwise, recur down the tree */
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    /* return the (unchanged) Node pointer */
    return node;
}

// Driver Program to test above functions
int main()
{
    /* Let us create following BST
            50
           /  \
         30    70
        / \   / \
      20  40 60  80 */
    struct Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    if (iterativeSearch(root, 20))
        printf("Yes");
    else
        printf("No");
    return 0;
}


