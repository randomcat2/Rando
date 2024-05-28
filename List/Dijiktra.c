#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 6 // Number of vertices in the graph

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the shortest path from source to v
void printPath(int parent[], int v) {
    if (parent[v] == -1)
        return;

    printPath(parent, parent[v]);
    printf("%d ", v);
}

// Function to print the constructed distance array
void printSolution(int dist[], int parent[], int src) {
    printf("Vertex\t Distance\tPath");
    for (int i = 0; i < V; i++) {
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        printPath(parent, i);
    }
}

// Function to perform Dijkstra's algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];     // Array to store the shortest distance from src to i
    int parent[V];   // Array to store the parent node of each vertex in the shortest path
    int visited[V];  // Array to mark visited vertices

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, visited);

        // Mark the picked vertex as visited
        visited[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the constructed distance array
    printSolution(dist, parent, src);
}

int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    int src;
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    printf("Shortest paths from vertex %d:\n", src);
    dijkstra(graph, src);

    return 0;
}
