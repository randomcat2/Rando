#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
    int data;
    int height;
} Node;

typedef struct Tree {
    Node *root;
} Tree;

Node* createNode(int data);
void inorder(Node *root);
int uph(Node *c);
int bf(Node *c);
Node* balance(Node *c);
Node* insert(Node *c, int data);
Node* ll(Node *c);
Node* rr(Node *c);
Node* lr(Node *c);
Node* rl(Node *c);
void initializeTree(Tree *t);

int main() {
    Tree t;
    initializeTree(&t);
    int ch;
    do {
        printf("\n1) Insert \n2) Inorder\n");
        printf("Enter: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: {
                int data;
                printf("\nEnter data: ");
                scanf("%d", &data);
                t.root = insert(t.root, data);
                break;
            }
            case 2: {
                inorder(t.root);
                break;
            }
        }
    } while (ch <= 2);
    return 0;
}

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = data;
    newNode->height = 1;
    return newNode;
}

void initializeTree(Tree *t) {
    t->root = NULL;
}

int uph(Node *c) {
    if (c == NULL) {
        return 0;
    }
    int leftHeight = uph(c->left);
    int rightHeight = uph(c->right);
    c->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    return c->height;
}

int bf(Node *c) {
    if (c == NULL) {
        return 0;
    }
    return uph(c->left) - uph(c->right);
}

Node* ll(Node *c) {
    Node *newRoot = c->left;
    c->left = newRoot->right;
    newRoot->right = c;
    uph(newRoot);
    uph(c);
    return newRoot;
}

Node* rr(Node *c) {
    Node *newRoot = c->right;
    c->right = newRoot->left;
    newRoot->left = c;
    uph(newRoot);
    uph(c);
    return newRoot;
}

Node* lr(Node *c) {
    c->left = rr(c->left);
    return ll(c);
}

Node* rl(Node *c) {
    c->right = ll(c->right);
    return rr(c);
}

Node* balance(Node *c) {
    if (bf(c) == 2) {
        if (bf(c->left) < 0) {
            c = lr(c);
        } else {
            c = ll(c);
        }
    } else if (bf(c) == -2) {
        if (bf(c->right) > 0) {
            c = rl(c);
        } else {
            c = rr(c);
        }
    }
    uph(c);
    return c;
}

Node* insert(Node *c, int data) {
    if (c == NULL) {
        return createNode(data);
    }
    if (data < c->data) {
        c->left = insert(c->left, data);
    } else if (data > c->data) {
        c->right = insert(c->right, data);
    }
    return balance(c);
}

void inorder(Node *c) {
    if (c == NULL) {
        return;
    }
    inorder(c->left);
    printf("%d ", c->data);
    inorder(c->right);
}
