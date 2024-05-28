#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Node structure to represent an adjacency list node
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

// Structure to represent an adjacency list
struct AdjList {
    struct Node* head;
};

// Structure to represent a graph
struct Graph {
    int numVertices;
    struct AdjList* array;
};

// Function to create a new adjacency list node
struct Node* newAdjListNode(int vertex, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = V;

    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int visited[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (visited[v] == 0 && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the constructed MST
void printMST(int parent[], int n, struct Graph* graph) {
    printf("Edge   Weight\n");
    for (int i = 1; i < n; i++) {
        struct Node* pCrawl = graph->array[i].head;
        while (pCrawl) {
            if (pCrawl->vertex == parent[i]) {
                printf("%d - %d    %d \n", parent[i], i, pCrawl->weight);
                break;
            }
            pCrawl = pCrawl->next;
        }
    }
}

// Function to construct and print MST for a graph
void PrimMST(struct Graph* graph) {
    int V = graph->numVertices;
    int parent[V];
    int dist[V];
    int visited[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = 1;

        struct Node* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->vertex;
            if (visited[v] == 0 && pCrawl->weight < dist[v]) {
                parent[v] = u;
                dist[v] = pCrawl->weight;
            }
            pCrawl = pCrawl->next;
        }
    }

    printMST(parent, V, graph);
}

int main() {
    int vertices, edges, src, dest, weight;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (src dest weight): ");
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    printf("Minimum Spanning Tree:\n");
    PrimMST(graph);

    return 0;
}
