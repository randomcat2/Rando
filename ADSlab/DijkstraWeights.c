#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
};

struct Node* createNode(int vertex, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (struct Node*)malloc(numVertices * sizeof(struct Node));

    for (int i = 0; i < numVertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // For undirected graph, add an edge from dest to src also
    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void dijkstra(struct Graph* graph, int startVertex) {
    int numVertices = graph->numVertices;
    int* distances = (int*)malloc(numVertices * sizeof(int));
    int* visited = (int*)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
    }

    distances[startVertex] = 0;

    for (int i = 0; i < numVertices - 1; i++) {
        int minVertex = -1;
        for (int j = 0; j < numVertices; j++) {
            if (!visited[j] && (minVertex == -1 || distances[j] < distances[minVertex])) {
                minVertex = j;
            }
        }

        visited[minVertex] = 1;

        struct Node* temp = graph->adjLists[minVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            int weight = temp->weight;
            if (!visited[adjVertex] && distances[minVertex] != INT_MAX && distances[minVertex] + weight < distances[adjVertex]) {
                distances[adjVertex] = distances[minVertex] + weight;
            }
            temp = temp->next;
        }
    }

    printf("Shortest distances from vertex %d:\n", startVertex);
    for (int i = 0; i < numVertices; i++) {
        printf("Vertex %d: Distance = %d\n", i, distances[i]);
    }

    free(distances);
    free(visited);
}

int main() {
    int vertices, edges, src, dest, weight, startVertex;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    struct Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge %d (src dest weight): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    printf("Enter the starting vertex for Dijkstra's algorithm: ");
    scanf("%d", &startVertex);

    dijkstra(graph, startVertex);

    return 0;
}