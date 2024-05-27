#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

int calculateHeight(struct TreeNode *node) {
    if (node == NULL)
        return 0;

    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

struct TreeNode *rightRotate(struct TreeNode *y) {
    struct TreeNode *x = y->left;
    struct TreeNode *T2 = x->right;

   
    x->right = y;
    y->left = T2;

    return x;
}


struct TreeNode *leftRotate(struct TreeNode *x) {
    struct TreeNode *y = x->right;
    struct TreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}


struct TreeNode *createNode(int data) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


int getBalanceFactor(struct TreeNode *node) {
    if (node == NULL)
        return 0;

    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);

    return leftHeight - rightHeight;
}


struct TreeNode *insertNode(struct TreeNode *node, int data) {

    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else 
        return node;

    int balance = getBalanceFactor(node);



    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Right Left Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Left right Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


void inorder(struct TreeNode *root) {
    if (root == NULL)
        return;

    inorder(root->left);        
    printf("%d ", root->data);  
    inorder(root->right);       
}


void levelOrderTraversal(struct TreeNode *root) {
    if (root == NULL)
        return;

    struct TreeNode *queue[1000]; 
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        int currentLevelSize = rear - front;
        while (currentLevelSize-- > 0) {
            struct TreeNode *current = queue[front++];
            printf("%d ", current->data);

            if (current->left != NULL)
                queue[rear++] = current->left;
            if (current->right != NULL)
                queue[rear++] = current->right;
        }
        printf("\n");
    }
}


void freeTree(struct TreeNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct TreeNode *root = NULL;
    int data;
    char choice;

    do {
        printf("Enter a number to insert into the AVL tree (enter 0 to stop): ");
        scanf("%d", &data);
        if (data != 0) {
            root = insertNode(root, data);
        }
    } while (data != 0);

    printf("Inorder Traversal (Sorted Order) of the AVL Tree:\n");
    inorder(root);
    printf("\n");

    printf("Level Order Traversal of the AVL Tree (each level on a new line):\n");
    levelOrderTraversal(root);

    freeTree(root);

    return 0;
}