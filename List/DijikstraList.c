#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a node in adjacency list
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

// Structure to represent a graph
struct Graph {
    int numVertices;
    struct Node** adjList;
};

// Function to create a new node
struct Node* createNode(int v, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = V;
    graph->adjList = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; ++i)
        graph->adjList[i] = NULL;
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int visited[], int V) {
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
void printSolution(int dist[], int parent[], int V, int src) {
    printf("Vertex\t Distance\tPath");
    for (int i = 0; i < V; i++) {
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        printPath(parent, i);
    }
}

// Function to perform Dijkstra's algorithm
void dijkstra(struct Graph* graph, int src) {
    int V = graph->numVertices;
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
        int u = minDistance(dist, visited, V);

        // Mark the picked vertex as visited
        visited[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        struct Node* pCrawl = graph->adjList[u];
        while (pCrawl) {
            int v = pCrawl->vertex;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + pCrawl->weight < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + pCrawl->weight;
            }
            pCrawl = pCrawl->next;
        }
    }

    // Print the constructed distance array
    printSolution(dist, parent, V, src);
}

int main() {
    int V, E, src;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    struct Graph* graph = createGraph(V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        printf("Enter edge (source destination weight): ");
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    printf("Enter the source vertex: ");
    scanf("%d", &src);

    printf("Shortest paths from vertex %d:\n", src);
    dijkstra(graph, src);

    return 0;
}
