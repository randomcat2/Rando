#include<stdio.h>
#include<stdlib.h>
#define MAX 100

struct Node 
{
    int data;
    struct Node *next;
}*front=NULL,*rear=NULL;

void enqueue(int x)
{
    struct Node *t;
    t=(struct Node*)malloc(sizeof(struct Node));
    if(t==NULL)
    printf("Queue is Full");
    else
    {
        t->data=x;
        t->next=NULL;
        if(front==NULL)
            front=rear=t;
        else
        {
            rear->next=t;
            rear=t;
        }    
    }
}

int dequeue()
{
    int x=-1;
    struct Node *t;

    if(front==NULL)
        printf("Queue is Empty");
    else
    {
        x=front->data;
        t=front;
        front=front->next;
        free(t);
    }  
    return x;  
}

void createGraph(int adjMatrix[MAX][MAX],int vertices)
{
    int edges,start,end;

    printf("Enter the no. of edges");
    scanf("%d",&edges);

    for(int i=0;i<edges;i++)
    {
        printf("Enter the edges:");
        scanf("%d %d",&start,&end);
        if(start >= vertices || end >= vertices || start < 0 || end < 0)
        {
            printf("Invalid edge");
            i--;
        }
        else
        {
            adjMatrix[start][end]=1;
            adjMatrix[end][start]=1;
        }
    }
}

void display(int adjMatrix[MAX][MAX],int vertices)
{
    printf("Adjacency Matrix is :\n");
    for(int i=0;i<vertices;i++)
    {
        for(int j=0;j<vertices;j++)
        {
            printf("%d ",adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void BFS(int adjMatrix[MAX][MAX],int vertices,int startvertex)
{
    int visited[MAX]={0};
    visited[startvertex] = 1;
    enqueue(startvertex);
    printf("BFS Traversal");

    while(front != NULL)
    {
        int current = dequeue();
        printf("%d ",current);

        for(int i=0;i<vertices;i++)
        {
            if(adjMatrix[current][i]==1 && !visited[i])
            {
                enqueue(i);
                visited[i]=1;
            }
        }
    }
    printf("\n");
}

int main()
{
    int vertices;
    int adjMatrix[MAX][MAX]={0};

    printf("Enter the no. of vertices:");
    scanf("%d",&vertices);

    createGraph(adjMatrix,vertices);
    display(adjMatrix,vertices);

    int startvertex;
    printf("Enter the starting vertex for BFS:");
    scanf("%d",&startvertex);

    if(startvertex >= vertices || startvertex < 0)
    {
        printf("Invalid starting vertex\n");
    }
    else
    {
        BFS(adjMatrix,vertices,startvertex);
    }
    return 0;
}