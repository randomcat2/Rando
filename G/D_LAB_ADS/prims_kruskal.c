#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 10
#define INF 9999

int minKey(int key[], bool mstSet[], int numVertices) {
    int min = INF;
    int minIndex = -1;

    for (int v = 0; v < numVertices; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < numVertices; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

void prim(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool mstSet[MAX_VERTICES];

    for (int i = 0; i < numVertices; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minKey(key, mstSet, numVertices);
        mstSet[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("Minimum Spanning Tree (Prim's Algorithm):\n");
    printMST(parent, graph, numVertices);
}

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

void unionVertices(int parent[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    parent[rootX] = rootY;
}

void kruskal(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    int parent[MAX_VERTICES];

    for (int i = 0; i < numVertices; i++) {
        parent[i] = i;
    }

    printf("Minimum Spanning Tree (Kruskal's Algorithm):\n");
    int edgeCount = 0;

    while (edgeCount < numVertices - 1) {
        int minWeight = INF;
        int u = -1, v = -1;

        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (find(parent, i) != find(parent, j) && graph[i][j] < minWeight) {
                    minWeight = graph[i][j];
                    u = i;
                    v = j;
                }
            }
        }

        if (u != -1 && v != -1) {
            unionVertices(parent, u, v);
            printf("Edge: %d - %d, Weight: %d\n", u, v, minWeight);
            edgeCount++;
        }
    }
}

int main() {
    int numVertices;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    int graph[MAX_VERTICES][MAX_VERTICES];

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int choice;
    do {
        printf("\nMinimum Spanning Tree (MST) Menu:\n");
        printf("1. Prim's Algorithm\n");
        printf("2. Kruskal's Algorithm\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                prim(graph, numVertices);
                break;
            case 2:
                kruskal(graph, numVertices);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}