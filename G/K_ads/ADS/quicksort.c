// Online C compiler to run C program online
#include <stdio.h>
#include<stdlib.h>
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int h;
}
int getHeight(struct Node *n)
{
    if(n==NULL)
    {
        return 0;
    }
    else
    {
        return n->h;
    }
}
struct Node *createNode(int key)
{
    struct Node* node=(struct Node *)malloc(sizeof(struct Node));
    node->key=key;
    node->left=NULL;
    node->right=NULL;
    node->h=1;
    return node;
}

int getBalanceFactor(struct Node *n)
{
    if(n==NULL)
    {
        return 0;
    }
    else{
        return getHeight(n->left->height)-getHeight(n->right->height)
        
    }
}

struct Node* leftRotate(struct Node* y)
{
    struct Node* x = y->left;
    struct Node* T2=x->right;
    
    x->rigth=y;
    y->left=T2;
    
    x->height=
}
int main() {
    // Write C code here
    printf("Try programiz.pro");

    return 0;
}