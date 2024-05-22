#include <stdio.h>
#define MAX 100

int q[MAX];
int front =-1,rear=-1;

void enqueue(int data)
{
    rear++;
    q[rear]= data;
}

int dequeue()
{
    front++;
    int x = q[front];
    return x;
}

void bfs(int A[7][7], int visited[],int i)
{
    printf("%d", i);
    enqueue(i);
    visited[i]=1;
    while (front!= rear)
    {
        i =dequeue();
        for(int j=0;j<7;j++)
        {
            if(A[i][j]==1 && visited[j]==0)
            {
                enqueue(j);
                printf("%d",j);
                visited[j]=1;

            }
        }
    }
    


}

int main()
{
    int visited[7];
    for (int i = 0; i < 7; i++)
    {
        visited[i]=0;
    }

    int A[7][7]={{0,0,0,0,0,0,0},{0,0,1,1,0,0,0},{0,1,0,0,1,0,0},{0,1,0,0,1,0,0},{0,0,1,1,0,1,1},{0,0,0,0,1,0,0},{0,0,0,0,1,0,0}};

  bfs(A,visited,1);
    
}