#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Recursive Count Nodes
int countNodesRecursive(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodesRecursive(root->left) + countNodesRecursive(root->right);
}

// Iterative Count Nodes (Level Order Traversal)
int countNodesIterative(struct Node* root) {
    if (root == NULL) {
        return 0;
    }

    struct Node* queue[100];  // Adjust queue size based on expected tree size
    int front = 0, rear = -1;
    int count = 0;

    queue[++rear] = root;  // Enqueue root

    while (front <= rear) {
        struct Node* current = queue[front++];

        if (current->left != NULL) {
            queue[++rear] = current->left;
        }
        if (current->right != NULL) {
            queue[++rear] = current->right;
        }
        count++;
    }

    return count;
}

// Recursive Find Height
int findHeightRecursive(struct Node* root) {
    if (root == NULL) {
        return -1; // Consider -1 as height of empty tree for clarity
    }
    int leftHeight = findHeightRecursive(root->left);
    int rightHeight = findHeightRecursive(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Iterative Find Height (Level Order Traversal)
int findHeightIterative(struct Node* root) {
    if (root == NULL) {
        return -1;
    }

    struct Node* queue[100];  // Adjust queue size based on expected tree size
    int front = 0, rear = -1;
    int level = -1, height = 0;

    queue[++rear] = root;  // Enqueue root
    level++;

    while (front <= rear) {
        int size = rear - front + 1; // Number of nodes in current level

        // Process all nodes of current level
        for (int i = 0; i < size; i++) {
            struct Node* current = queue[front++];

            if (current->left != NULL) {
                queue[++rear] = current->left;
            }
            if (current->right != NULL) {
                queue[++rear] = current->right;
            }
        }

        level++;  // Move to next level
    }

    return level-1;
}

// Function to create the mirror image of a tree
void createMirrorImage(struct Node* root) {
    if (root == NULL) {
        return;
    }
    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    createMirrorImage(root->left);
    createMirrorImage(root->right);
}

// Function to insert a node into the tree (assuming BST insertion logic)
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return newNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
} 

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to display the menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Insert Node\n");
    printf("2. Count Nodes (Recursive)\n");
    printf("3. Count Nodes (Iterative)\n");
    printf("4. Find Height (Recursive)\n");
    printf("5. Find Height (Iterative)\n");
    printf("6. Create Mirror Image\n"); 
     printf("7. Inorder Traversal\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}

// Main function to handle user interactions
int main() {
    struct Node* root = NULL;
    int choice, data;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Total nodes (recursive): %d\n", countNodesRecursive(root));
                break;
            case 3:
                printf("Total nodes (iterative): %d\n", countNodesIterative(root));
                break;
            case 4:
                printf("Tree height (recursive): %d\n", findHeightRecursive(root));
                break;
            case 5:
                printf("Tree height (iterative): %d\n", findHeightIterative(root));
                break;
            case 6:
                createMirrorImage(root);
                printf("Mirror image created.\n");
                break;
            case 7:
                inorder(root);
                printf("This is the Inorder Traversal.\n");
                break;
            
            case 8:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
