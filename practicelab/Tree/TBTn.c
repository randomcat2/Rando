#include<stdio.h>
#include<stdlib.h>

struct TBT{
    int data;
    int lbit,rbit;
    struct TBT *left;
    struct TBT *right;
};

struct TBT *create(struct TBT *head,int key)
{
    struct TBT *temp;
    struct TBT *p;
    temp=(struct TBT*)malloc(sizeof(struct TBT));
    temp->data=key;
    temp->lbit=temp->rbit=0;
    if(head->lbit==0)
    {
        head->left=temp;
        head->lbit=1;
        temp->left=temp->right=head;
        return head;
    }
    p=head->left;
    while(1)
    {
        if(key < p->data && p->lbit==1)
        p=p->left;
        else if(key > p->data && p->rbit==1)
        p=p->right;
        else
        break;
    }
    if(key < p->data)
    {
        temp->right=p;
        temp->left=p->left;
        p->lbit=1;
        p->left=temp;
    }
    if(key > p->data)
    {
        temp->left=p;
        temp->right=p->right;
        p->rbit=1;
        p->right=temp;
    }
    return head;
}

void Preorder(struct TBT *head)
{
    struct TBT *p;
    p=head->left;
    while(p!= head)
    {
        printf("%d ",p->data);
        if(p->lbit==1)
        p=p->left;
        else if(p->rbit==1)
        p=p->right;
        else if(p->rbit==0)
        {
            while (p->rbit==0)
            {
                p=p->right;
            }
            p=p->right;
        }
    }
}

void Inorder(struct TBT *head)
{
    struct TBT *p;
    p=head->left;
    while(p->lbit==1)
    {
        p=p->left;
    }
    while (p!=head)
    {
        printf("%d ",p->data);
        if(p->rbit==1)
        {
            p=p->right;
            while(p->lbit==1)
            p=p->left;
        }
        else if(p->rbit==0)
        {
            p=p->right;
        }
    }
    
}

int main()
{
    int n;
    int key;
    struct TBT *head = NULL;
    head=(struct TBT*)malloc(sizeof(struct TBT));
    head->rbit=1;
    head->lbit=0;
    head->left=head->right=head;
    printf("Enter no. of Nodes:");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        printf("Enter value:");
        scanf("%d",&key);
        head=create(head,key);
    }
    printf("Preorder Traversal: ");
    Preorder(head);
    printf("\n");
    
    printf("Inorder Traversal: ");
    Inorder(head);
    printf("\n");
    return 0;
}