#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct StackNode {
    struct TreeNode* data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

StackNode* createStackNode(TreeNode* treeNode) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = treeNode;
    newNode->next = NULL;
    return newNode;
}

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

int isEmpty(Stack* stack) {
    if (stack->top == NULL) {
        return 1; 
    } else {
        return 0; 
    }
}

void push(Stack* stack, TreeNode* treeNode) {
    StackNode* newNode = createStackNode(treeNode);
    newNode->next = stack->top;
    stack->top = newNode;
}

TreeNode* pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    StackNode* temp = stack->top;
    TreeNode* poppedNode = temp->data;
    stack->top = temp->next;
    free(temp);
    return poppedNode;
}

void destroyStack(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}

void insert(TreeNode** root, int data) {
    if (*root == NULL) {
        *root = createNode(data);
        return;
    }

    if (data < (*root)->data) {
        insert(&((*root)->left), data);
    } else {
        insert(&((*root)->right), data);
    }
}

void inorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* current = root;
    Stack* stack = createStack();
    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        printf("%d ", current->data);
        current = current->right;
    }
    destroyStack(stack);
}

void preorderTraversal(TreeNode* current) {
    Stack* stack = createStack();
    while (current != NULL || !isEmpty(stack)) {
        if (current != NULL) {
            printf("%d ", current->data);
            push(stack, current);
            current = current->left;
        } else {
            current = pop(stack);
            current = current->right;
        }
    }
    destroyStack(stack);
}

int countLeafNodes(TreeNode* root) {
    if (root == NULL) return 0;
    int count = 0;
    Stack* stack = createStack();
    push(stack, root);
    while (!isEmpty(stack)) {
        TreeNode* current = pop(stack);
        if (current->left == NULL && current->right == NULL) {
            count++;
        }
        if (current->right != NULL) {
            push(stack, current->right);
        }
        if (current->left != NULL) {
            push(stack, current->left);
        }
    }
    destroyStack(stack);
    return count;
}

void mirror(TreeNode* root) {
    if (root == NULL) return;
    Stack* stack = createStack();
    push(stack, root);
    while (!isEmpty(stack)) {
        TreeNode* current = pop(stack);
        TreeNode* temp = current->left;
        current->left = current->right;
        current->right = temp;
        if (current->right != NULL) {
            push(stack, current->right);
        }
        if (current->left != NULL) {
            push(stack, current->left);
        }
    }
    destroyStack(stack);
}

int main() {
    TreeNode* root = NULL;
   
    int value;
    do {
        printf("Enter a value for the node (enter -1 to stop): ");
        scanf("%d", &value);
        if (value != -1) {
            insert(&root, value);
        }
    } while (value != -1);

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));

    printf("Mirroring the tree...\n");
    mirror(root);

    printf("Inorder Traversal of Mirror Tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
