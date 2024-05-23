#include <stdio.h>
#include <stdlib.h>

// Definition of the BST node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the BST
struct Node* insert(struct Node* node, int data) {
    if (node == NULL) return createNode(data); // If bst is empty 

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    return node;
}

// Function to find the minimum value node in the tree
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Inorder traversal with recursion
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder traversal with recursion
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal with recursion
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Inorder traversal without recursion
void inorderNonRecursive(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    struct Node* curr = root;

    while (curr != NULL || top >= 0) {
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }
        curr = stack[top--];
        printf("%d ", curr->data);
        curr = curr->right;
    }
}

// Preorder traversal without recursion
void preorderNonRecursive(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        struct Node* node = stack[top--];
        printf("%d ", node->data);

        if (node->right) stack[++top] = node->right;
        if (node->left) stack[++top] = node->left;
    }
}

// Postorder traversal without recursion
void postorderNonRecursive(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack1[100];
    struct Node* stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;
    while (top1 >= 0) {
        struct Node* node = stack1[top1--];
        stack2[++top2] = node;

        if (node->left) stack1[++top1] = node->left;
        if (node->right) stack1[++top1] = node->right;
    }

    while (top2 >= 0) {
        struct Node* node = stack2[top2--];
        printf("%d ", node->data);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Inorder Traversal (Recursive)\n");
        printf("4. Preorder Traversal (Recursive)\n");
        printf("5. Postorder Traversal (Recursive)\n");
        printf("6. Inorder Traversal (Non-Recursive)\n");
        printf("7. Preorder Traversal (Non-Recursive)\n");
        printf("8. Postorder Traversal (Non-Recursive)\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;
            case 3:
                printf("Inorder Traversal (Recursive): ");
                inorder(root);
                printf("\n");
                break;
            case 4:
                printf("Preorder Traversal (Recursive): ");
                preorder(root);
                printf("\n");
                break;
            case 5:
                printf("Postorder Traversal (Recursive): ");
                postorder(root);
                printf("\n");
                break;
            case 6:
                printf("Inorder Traversal (Non-Recursive): ");
                inorderNonRecursive(root);
                printf("\n");
                break;
            case 7:
                printf("Preorder Traversal (Non-Recursive): ");
                preorderNonRecursive(root);
                printf("\n");
                break;
            case 8:
                printf("Postorder Traversal (Non-Recursive): ");
                postorderNonRecursive(root);
                printf("\n");
                break;
            case 9:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
