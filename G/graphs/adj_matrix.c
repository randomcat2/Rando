#include <stdio.h>
# define MAX 100

void create_Adj_mat(int adj_mat[MAX][MAX], int vertices, int edges)
{
    int i,src,des;
    for(i = 0;i<edges;i++)
    {
        printf("Enter [source destination]: ");
        scanf("%d %d",&src,&des);
        adj_mat[src][des] = 1;
        adj_mat[des][src] = 1; // for undirected graph
    }

}

void print_Adj_mat(int adj_mat[MAX][MAX], int vertices)
{
    int i,j;
    for(i=0;i<vertices;i++)
    {
        for(j=0;j<vertices;j++)
        {
            printf("%d ",adj_mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int vertices,edges;
    int adj_mat[MAX][MAX];
    printf("Enter no. of vertices: ");
    scanf("%d",&vertices);

    printf("Enter no. of edges: ");
    scanf("%d",&edges);

    for(int i=0;i<vertices;i++)
    {
        for(int j=0;j<vertices;j++)
        {
            adj_mat[i][j] = 0;
        }
    }

    create_Adj_mat(adj_mat,vertices,edges);
    print_Adj_mat(adj_mat,vertices);
}

