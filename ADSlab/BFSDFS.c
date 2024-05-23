#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure to represent a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent a graph
struct Graph {
    int numVertices;
    struct Node* adjacencyList[MAX_VERTICES];
    bool visited[MAX_VERTICES];
};

// Create a new node with given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Initialize a graph with given number of vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

// Add an edge between two vertices
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    // For undirected graph, add edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

// Breadth-First Search (BFS) traversal of the graph
void BFS(struct Graph* graph, int startVertex) {
    // Queue for BFS traversal
    int queue[MAX_VERTICES];
    int front = 0, rear = -1;

    // Enqueue the start vertex and mark it as visited
    queue[++rear] = startVertex;
    graph->visited[startVertex] = true;

    printf("BFS Traversal: ");

    while (front <= rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Visit all adjacent vertices of the current vertex
        struct Node* temp = graph->adjacencyList[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->data;
            if (!graph->visited[adjVertex]) {
                queue[++rear] = adjVertex;
                graph->visited[adjVertex] = true;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// Depth-First Search (DFS) traversal of the graph
void DFSUtil(struct Graph* graph, int currentVertex) {
    printf("%d ", currentVertex);
    graph->visited[currentVertex] = true;

    // Visit all adjacent vertices of the current vertex recursively
    struct Node* temp = graph->adjacencyList[currentVertex];
    while (temp != NULL) {
        int adjVertex = temp->data;
        if (!graph->visited[adjVertex]) {
            DFSUtil(graph, adjVertex);
        }
        temp = temp->next;
    }
}

void DFS(struct Graph* graph, int startVertex) {
    printf("DFS Traversal: ");
    DFSUtil(graph, startVertex);
    printf("\n");
}

int main() {
    int numVertices, choice, src, dest;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &numVertices);

    struct Graph* graph = createGraph(numVertices);

    while (true) {
        printf("\nGraph Operations:\n");
        printf("1. Add Edge\n");
        printf("2. Breadth-First Search (BFS)\n");
        printf("3. Depth-First Search (DFS)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter source and destination vertices of the edge: ");
                scanf("%d %d", &src, &dest);
                if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
                    printf("Invalid vertices.\n");
                    break;
                }
                addEdge(graph, src, dest);
                break;
            case 2:
                printf("Enter the starting vertex for BFS: ");
                scanf("%d", &src);
                if (src < 0 || src >= numVertices) {
                    printf("Invalid starting vertex.\n");
                    break;
                }
                BFS(graph, src);
                break;
            case 3:
                printf("Enter the starting vertex for DFS: ");
                scanf("%d", &src);
                if (src < 0 || src >= numVertices) {
                    printf("Invalid starting vertex.\n");
                    break;
                }
                // Reset visited array before DFS traversal
                for (int i = 0; i < numVertices; i++) {
                    graph->visited[i] = false;
                }
                DFS(graph, src);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
