#include <stdio.h>

int dfs(int A[7][7], int start,int visited[], int n)
{
    
    if(visited[start]==0)
    {
        printf("%d",start);
        visited[start]=1;

        for(int j=0;j<7;j++)
    {
        if(A[start][j]==1 && visited[j]==0)
        {
            dfs(A,j,visited,n);
        }
    }
    }

    
}

int main()
{
    int visited[7] = {0};
    
    int A[7][7]={{0,0,0,0,0,0,0},{0,0,1,1,0,0,0},{0,1,0,0,1,0,0},{0,1,0,0,1,0,0},{0,0,1,1,0,1,1},{0,0,0,0,1,0,0},{0,0,0,0,1,0,0}};

    dfs(A,1,visited,7);
    return 0;
}