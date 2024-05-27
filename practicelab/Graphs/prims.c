#include <stdio.h>

void DisplayMST(int parent[], int G[][10], int v) {
    int i, j;
    for (i = 1; i < v; i++) {
        printf("%d - %d: %d\n", parent[i], i, G[i][parent[i]]);
    }
}

int Findmin(int dist[], int visit[], int v) {
    int min = 999;
    int minIndex = -1;
    for (int i = 0; i < v; i++) {
        if (visit[i] == 0 && dist[i] < min) {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void prims(int G[][10], int v) {
    int visit[10], parent[10], dist[10];
    int u;

    for (int i = 0; i < v; i++) {
        parent[i] = -1;
        visit[i] = 0;
        dist[i] = 999;
    }
    dist[0] = 0;

    for (int i = 0; i < v - 1; i++) {
        u = Findmin(dist, visit, v);
        visit[u] = 1;
        for (int j = 0; j < v; j++) {
            if (visit[j] == 0 && G[u][j] < dist[j]) {
                dist[j] = G[u][j];
                parent[j] = u;
            }
        }
    }
    DisplayMST(parent, G, v);
}

int main() {
    int G[10][10];
    int v;
    printf("Enter the number of vertices: ");
    scanf("%d", &v);
    printf("Enter the Matrix: ");
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            scanf("%d", &G[i][j]);
        }
    }
    prims(G, v);
    return 0;
}
