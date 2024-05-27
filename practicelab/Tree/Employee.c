#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct Stack{
    struct TreeNode *node;
    struct Stack *next;
};

struct TreeNode *createNode(int data)
{
    struct TreeNode *newNode =(struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data=data;
    newNode->left=newNode->right=NULL;
    return newNode;
}

struct Stack *createStack(struct TreeNode *node)
{
    struct Stack *stackNode=(struct Stack*)malloc(sizeof(struct Stack));
    stackNode->node=node;
    stackNode->next=NULL;
}

void push(struct Stack **top,struct TreeNode *root)
{
    struct Stack *stackNode = createStack(root);
    stackNode->next=*top;
    *top=stackNode;
}

struct TreeNode *pop(struct Stack **top)
{
    if(*top==NULL)
    {
        return NULL;
    }
    struct TreeNode *popped = (*top)->node;
    struct Stack *temp=*top;
    *top=(*top)->next;
    free(temp);
    return popped;
}

struct TreeNode *insert(struct TreeNode *root,int key)
{
    struct TreeNode *temp=createNode(key);
    if(root==NULL)
       return temp;
    struct TreeNode *p=root;
    struct TreeNode *parent=NULL;
    while(p!=NULL)
    {
        parent=p;
        if(key < p->data)
        p=p->left;
        else
        p=p->right;
    }
    if(key < parent->data)
    parent->left=temp;
    else
    parent->right=temp;

    return root;
}

bool find(struct TreeNode *root,int key)
{
    while(root != NULL)
    {
        if(root->data == key)
        return true;
        else if(key < root->data)
        root=root->left;
        else
        root=root->right;
    }
    return false;
}

void Inorder(struct TreeNode *root)
{
    struct Stack *top=NULL;
    struct TreeNode *temp=root;
    while(temp != NULL || top !=NULL)
    {
        while(temp != NULL)
        {
            push(&top,temp);
            temp=temp->left;
        }
        temp=pop(&top);
        printf("%d ",temp->data);
        temp=temp->right;
    }
}

int main()
{
    int n, id, search;
    struct TreeNode *root = NULL;
    char name[50];

    printf("Enter the number of employees: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter emp id: ");
        scanf("%d", &id);
        printf("Enter emp name: ");
        scanf("%s", name);
        root = insert(root, id);
    }

    printf("Enter the id to search: ");
    scanf("%d", &search);

    if (find(root, search))
        printf("Employee found.\n");
    else
        printf("Employee not found.\n");

    printf("Sorted order  is :");
    Inorder(root);    

    return 0;
}    