#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head=NULL;

void push(int num)
{
    struct Node *newNode=(struct Node *)malloc(sizeof(struct Node));
    newNode->data=num;
    newNode->next=head;
    head=newNode;
}

void reverse()
{
    struct Node *p=head;
    struct Node *q=NULL;
    struct Node *r=NULL;

    while(p!=NULL)
    {
        r=q;
        q=p;
        p=p->next;
        q->next=r;
    }
    head=q;
}

void printList() {
    struct Node *node = head;
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}


int main()
{
    push(5);
    push(4);
    push(3);
    push(2);
    push(1);

    printf("Original list:\n");
    printList();

    reverse();

    printf("Reversed list:\n");
    printList();
    return 0;
}