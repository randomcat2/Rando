#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

typedef struct {
    struct Node *front;
    struct Node *rear;
}CircularDeque;

void initdeque(CircularDeque *deque)
{
    deque->front=deque->rear=NULL;
}

struct Node *createNode(int data)
{
    struct Node* newNode =(struct Node*)malloc(sizeof(struct Node));
    newNode->data=data;
    newNode->prev=newNode->next=NULL;
    return newNode;
}

void insertFront(CircularDeque *deque,int data)
{
    struct Node *newNode =createNode(data);
    if(deque->front==NULL)
    {
        deque->front=deque->rear=newNode;
        newNode->next=newNode->prev=newNode;
    }
    else
    {
        newNode->next=deque->front;
        newNode->prev=deque->rear;
        deque->rear->next=newNode;
        deque->front->prev=newNode;
        deque->front=newNode;
    }
}

void insertRear(CircularDeque *deque,int data)
{
    struct Node *newNode = createNode(data);
    if(deque->rear==NULL)
    {
        deque->front=deque->rear=newNode;
        newNode->next=newNode->prev=newNode;
    }
    else
    {
        newNode->next=deque->front;
        newNode->prev=deque->rear;
        deque->rear->next=newNode;
        deque->front->prev=newNode;
        deque->rear=newNode;
    }
}

void deleteFront(CircularDeque *deque)
{
    if(deque->front==NULL)
    {
        printf("Deque is Empty");
        return;
    }
    struct Node *temp=deque->front;
    if(deque->front==deque->rear)
    {
        deque->front=deque->rear=NULL;
    }
    else
    {
        deque->front=deque->front->next;
        deque->front->prev=deque->rear;
        deque->rear->next=deque->front;
    }
    free(temp);
}

void deleteRear(CircularDeque *deque)
{
    if(deque->rear==NULL)
    {
        printf("Deque is Empty");
        return;
    }
    struct Node *temp=deque->rear;
    if(deque->front==deque->rear)
    {
        deque->front=deque->rear=NULL;
    }
    else
    {
        deque->rear=deque->rear->prev;
        deque->rear->next=deque->front;
        deque->front->prev=deque->rear;
    }
    free(temp);
}

void displayDeque(CircularDeque *deque)
{
    if(deque->front==NULL)
    {
        printf("Deque is empty");
        return;
    }
    struct Node *temp = deque->front;
    printf("Deque: ");
    do{
        printf("%d ",temp->data);
        temp=temp->next;
    }
    while(temp!= deque->front);
    printf("\n");
}

int main()
{
    CircularDeque deque;
    initdeque(&deque);

    insertRear(&deque, 10);
    insertRear(&deque, 20);
    insertFront(&deque, 5);
    insertFront(&deque, 2);

    printf("Deque contents: ");
    displayDeque(&deque);

    deleteFront(&deque);
    printf("Deque contents after deleting front: ");
    displayDeque(&deque);

    deleteRear(&deque);
    printf("Deque contents after deleting rear: ");
    displayDeque(&deque);

    insertRear(&deque, 40);
    printf("Deque contents after inserting 40 at rear: ");
    displayDeque(&deque);
    return 0;
}