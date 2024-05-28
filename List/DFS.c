#include <stdio.h>
#include <stdlib.h>

// Node structure to represent an adjacency list node
struct Node {
    int data;
    struct Node* next;
};

// Graph structure to represent an adjacency list
struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

// Function to create a node
struct Node* createNode(int data) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // For an undirected graph, uncomment the following lines
    // Add edge from dest to src
    // newNode = createNode(src);
    // newNode->next = graph->adjLists[dest];
    // graph->adjLists[dest] = newNode;
}

// DFS algorithm
void DFS(struct Graph* graph, int vertex) {
    struct Node* adjList = graph->adjLists[vertex];
    struct Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->data;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

int main() {
    int vertices, edges, src, dest, startVertex;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (src dest): ");
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &startVertex);

    printf("DFS Traversal starting from vertex %d:\n", startVertex);
    DFS(graph, startVertex);

    return 0;
}
