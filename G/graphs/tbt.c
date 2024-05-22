#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
    int l; // Left flag
    int r; // Right flag
};

struct node* create(struct node* root, struct node* t, int key) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = key;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->l = 0;
    newnode->r = 0;

    if (root == NULL) {
        root = newnode;
        root->left = t;
        root->right = t;
    } else {
        if (key < root->data) {
            if (root->l == 0) {
                newnode->left = root->left;
                newnode->right = root;
                root->left = newnode;
                root->l = 1;
            } else {
                create(root->left, t, key);
            }
        }
        if (key > root->data) {
            if (root->r == 0) {
                newnode->right = root->right;
                newnode->left = root;
                root->right = newnode;
                root->r = 1;
            } else {
                create(root->right, t, key);
            }
        }
    }
    return root;
}

void inorder(struct node* root, struct node* t) {
    while (root != t) {
        while (root->l == 1) {
            root = root->left;
        }
        printf("%d ", root->data);
        while (root->r == 0) {
            root = root->right;
            if (root == t) {
                return;
            }
            printf("%d ", root->data);
        }
        root = root->right;
    }
}

struct node* case1(struct node* root, struct node* parent, struct node* current) {
    if (parent == NULL) {
        root = NULL;
    } else if (current == parent->left) {
        parent->l = 0;
        parent->left = current->left;
    } else {
        parent->r = 0;
        parent->right = current->right;
    }
    free(current);
    return root;
}

struct node* case2(struct node* root, struct node* parent, struct node* current) {
    struct node* child;
    if (current->l == 1) {
        child = current->left;
    } else {
        child = current->right;
    }

    if (parent == NULL) {
        root = child;
    } else if (current == parent->left) {
        parent->left = child;
    } else {
        parent->right = child;
    }

    if (current->l == 1) {
        struct node* temp = current->right;
        while (temp->l == 1) {
            temp = temp->left;
        }
        temp->left = child;
    } else {
        if (current->r == 1) {
            struct node* temp = current->left;
            while (temp->r == 1) {
                temp = temp->right;
            }
            temp->right = child;
        }
    }

    free(current);
    return root;
}

struct node* case3(struct node* root, struct node* parent, struct node* current) {
    struct node* parsucc = current;
    struct node* succ = current->right;

    while (succ->l == 1) {
        parsucc = succ;
        succ = succ->left;
    }

    current->data = succ->data;

    if (succ->l == 0 && succ->r == 0) {
        root = case1(root, parsucc, succ);
    } else {
        root = case2(root, parsucc, succ);
    }

    return root;
}

struct node* dThreadedBST(struct node* root, int value) {
    struct node *parent = NULL, *current = root;
    int found = 0;

    while (current != NULL) {
        if (value == current->data) {
            found = 1;
            break;
        }
        parent = current;
        if (value < current->data) {
            if (current->l == 1) {
                current = current->left;
            } else {
                break;
            }
        } else {
            if (current->r == 1) {
                current = current->right;
            } else {
                break;
            }
        }
    }

    if (found == 0) {
        printf("The value not present in tree\n");
    } else if (current->l == 1 && current->r == 1) {
        root = case3(root, parent, current);
    } else if (current->l == 1) {
        root = case2(root, parent, current);
    } else if (current->r == 1) {
        root = case2(root, parent, current);
    } else {
        root = case1(root, parent, current);
    }

    return root;
}

int main() {
    struct node* root = NULL;
    struct node* t = (struct node*)malloc(sizeof(struct node));
    t->data = -999;
    t->left = root;
    t->right = NULL;

    root = create(root, t, 12);
    create(root, t, 21);
    create(root, t, 17);
    create(root, t, 2);
    create(root, t, 16);
    create(root, t, 22);
    create(root, t, 18);

    inorder(root, t);
    printf("\n");

    root = dThreadedBST(root, 17);
    inorder(root, t);
    printf("\n");

    free(t);

    return 0;
}
