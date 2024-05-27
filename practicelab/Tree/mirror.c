#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node in the BST
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// Function to create a new node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
TreeNode* insertNode(TreeNode* root, int data) {
    TreeNode* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }
    TreeNode* current = root;
    TreeNode* parent = NULL;
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            return root; // Duplicate values are not allowed
        }
    }
    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    return root;
}

// Function to display the BST in-order iteratively
void inOrder(TreeNode* root) {
    if (root == NULL) return;
    
    TreeNode* stack[100];
    int top = -1;
    TreeNode* current = root;
    
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

// Function to create a mirror image of the BST without modifying the original using a queue
TreeNode* mirror(TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    // Create a new root for the mirrored tree
    TreeNode* mirroredRoot = createNode(root->data);

    // Use queues to perform level-order traversal
    TreeNode* originalQueue[100];
    TreeNode* mirroredQueue[100];
    int front = 0, rear = 0;

    originalQueue[rear] = root;
    mirroredQueue[rear++] = mirroredRoot;

    while (front < rear) {
        TreeNode* originalNode = originalQueue[front];
        TreeNode* mirroredNode = mirroredQueue[front++];

        // If the left child exists in the original tree, create the right child in the mirrored tree
        if (originalNode->left != NULL) {
            mirroredNode->right = createNode(originalNode->left->data);
            originalQueue[rear] = originalNode->left;
            mirroredQueue[rear++] = mirroredNode->right;
        }

        // If the right child exists in the original tree, create the left child in the mirrored tree
        if (originalNode->right != NULL) {
            mirroredNode->left = createNode(originalNode->right->data);
            originalQueue[rear] = originalNode->right;
            mirroredQueue[rear++] = mirroredNode->left;
        }
    }

    return mirroredRoot;
}

// Function to mirror the BST in place iteratively using a queue
void mirrorInPlace(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode* current = queue[front++];

        // Swap left and right children
        TreeNode* temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->left) {
            queue[rear++] = current->left;
        }
        if (current->right) {
            queue[rear++] = current->right;
        }
    }
}

// Function to calculate the height of the tree using level-order traversal
int height(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int height = 0;
    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        int nodeCount = rear - front;
        height++;
        while (nodeCount > 0) {
            TreeNode* node = queue[front++];
            if (node->left != NULL) {
                queue[rear++] = node->left;
            }
            if (node->right != NULL) {
                queue[rear++] = node->right;
            }
            nodeCount--;
        }
    }
    return height;
}

int main() {
    TreeNode* root = NULL;
    // Inserting nodes into the BST
    root = insertNode(root, 50);
    root = insertNode(root, 30);
    root = insertNode(root, 70);
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    root = insertNode(root, 60);
    root = insertNode(root, 80);

    printf("In-order traversal of the original BST:\n");
    inOrder(root);
    printf("\n");

    // Create a mirror image without modifying the original tree
    TreeNode* mirroredRoot = mirror(root);

    printf("In-order traversal of the mirrored BST (without modifying original):\n");
    inOrder(mirroredRoot);
    printf("\n");

    printf("Height of the original tree: %d\n", height(root));

    // Mirror the original tree in place
    mirrorInPlace(root);

    printf("In-order traversal of the mirrored BST (modifying original):\n");
    inOrder(root);
    printf("\n");

    printf("Height of the modified (mirrored) tree: %d\n", height(root));

    return 0;
}
