#include<stdio.h>
#include<stdlib.h>
#define MAX 100

struct Stack{
    int data;
    struct Stack *next;
};
struct Stack *top=NULL;

void push(int x)
{
    struct Stack *t;
    t=(struct Stack*)malloc(sizeof(struct Stack));
    if(t==NULL)
    printf("Stack is full\n");
    else
    {
        t->data=x;
        t->next=top;
        top=t;
    }
}

int pop()
{
    struct Stack *t;
    int x=-1;;
    if(top==NULL)
    {
        printf("Stack is empty");
    }
    else
    {
        t=top;
        top=top->next;
        x=t->data;
        free(t);
    }
    return x;
}

void createGraph(int adjMatrix[MAX][MAX],int vertices)
{
    int edges,start,end;

    printf("Enter the no. of edges:");
    scanf("%d",&edges);

    for(int i=0;i<edges;i++)
    {
        printf("Enter the edge");
        scanf("%d %d",&start,&end);
        if(start >= vertices || end >= vertices || start <0 || end<0)
        {
            printf("Invalid edge\n");
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

void DFS(int adjMatrix[MAX][MAX],int vertices,int startvertex)
{
    int visited[MAX]={0};
    push(startvertex);
    printf("DFS Traversal: ");
    while(top != NULL)
    {
        int current= pop();
        if(visited[current] != 1)
        {
            printf("%d ",current);
            visited[current]=1;
        }
        for(int i=vertices-1;i>=0;i--)
        {
            if(adjMatrix[current][i]==1 && visited[i]!=1)
            {
                push(i);
            }
        }
    }
    printf("\n");
}

int main()
{
    int vertices;
    int adjMatrix[MAX][MAX] = {0};

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    createGraph(adjMatrix, vertices);
    display(adjMatrix, vertices);

    int startVertex;
    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &startVertex);

    if (startVertex >= vertices || startVertex < 0) {
        printf("Invalid starting vertex!\n");
    } else {
        DFS(adjMatrix, vertices, startVertex);
    }
    return 0;
}