#include<stdio.h>
#include<stdlib.h>
#define size 20

typedef struct {
    int arr[size];
    int front1,rear1;
    int front2,rear2;
}DualQueue;

void init(DualQueue *dq)
{
    dq->front1=dq->rear1=-1;
    dq->front2=dq->rear2=size;
}

int isEmpty1(DualQueue *dq)
{
    return dq->front1==-1;
}

int isEmpty2(DualQueue *dq)
{
    return dq->front2==size;
}

int isFull1(DualQueue *dq)
{
    return dq->rear1+1==dq->front2;
}

int isFull2(DualQueue *dq)
{
    return dq->rear2-1==dq->rear1;
}

void addq1(DualQueue *dq,int value)
{
    if(isFull1(dq))
    {
        printf("Queue 1 is full\n");
        return;
    }
    if(dq->front1==-1)
    {
        dq->front1=dq->rear1=0;
    }
    else
    {
        dq->rear1++;
    }
    dq->arr[dq->rear1]=value;   
}

void addq2(DualQueue *dq,int value)
{
    if(isFull2(dq))
    {
        printf("Queue 2 is full\n");
        return;
    }
    if(dq->front2==size)
    {
        dq->front2=dq->rear2=size-1;
    }
    else
    {
        dq->rear2--;
    }
    dq->arr[dq->rear2]=value;   
}

int delq1(DualQueue *dq)
{
    if(isEmpty1(dq))
    {
        printf("Queue is Empty");
        return -1;
    }
    int value=dq->arr[dq->front1];
    if(dq->front1==dq->rear1)
    {
        dq->front1=dq->rear1=-1;
    }
    else
    {
        dq->front1++;
    }
    return value;
}

int delq2(DualQueue *dq)
{
    if(isEmpty2(dq))
    {
        printf("Queue 2 is Empty");
        return -1;
    }
    int value=dq->arr[dq->front2];
    if(dq->front2==dq->rear2)
    {
        dq->front2=dq->rear2=size;
    }
    else
    {
        dq->front2++;
    }
    return value;
}

void displayQueue1(DualQueue *dq) {
    if (isEmpty1(dq)) {
        printf("Queue 1 is empty\n");
        return;
    }
    printf("Queue 1: ");
    for (int i = dq->front1; i <= dq->rear1; i++) {
        printf("%d ", dq->arr[i]);
    }
    printf("\n");
}

void displayQueue2(DualQueue *dq) {
    if (isEmpty2(dq)) {
        printf("Queue 2 is empty\n");
        return;
    }
    printf("Queue 2: ");
    for (int i = dq->front2; i >= dq->rear2; i--) {
        printf("%d ", dq->arr[i]);
    }
    printf("\n");
}

int main()
{
    DualQueue dq;
    init(&dq);

    addq1(&dq, 10);
    addq1(&dq, 20);
    addq1(&dq, 30);
    displayQueue1(&dq);
    printf("Deleted from Queue 1: %d\n", delq1(&dq));
    displayQueue1(&dq);

    addq2(&dq, 40);
    addq2(&dq, 50);
    addq2(&dq, 60);
    displayQueue2(&dq);
    printf("Deleted from Queue 2: %d\n", delq2(&dq));
    displayQueue2(&dq);
    return 0;
}
