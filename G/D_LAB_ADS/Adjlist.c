#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists; 
    int* visited;
} Graph;

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;


    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void BFS(Graph* graph, int startVertex) {
    int queue[100], front = 0, rear = 0;
    graph->visited[startVertex] = 1;
    queue[rear++] = startVertex;

    printf("BFS Traversal: ");

    while (front != rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;

            if (!graph->visited[adjVertex]) {
                queue[rear++] = adjVertex;
                graph->visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
    printf("\n");

    // Reset visited array for future use
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

void DFS(Graph* graph, int startVertex) {
    int stack[100];
    int top = -1;

    stack[++top] = startVertex;

    printf("DFS Traversal: ");
    while (top != -1) {
        int currentVertex = stack[top--];

        if (!graph->visited[currentVertex]) {
            printf("%d ", currentVertex);
            graph->visited[currentVertex] = 1;
        }

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex]) {
                stack[++top] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");

    // Reset visited array for future use
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

int main() {
    int vertices, edges, src, dest, startVertex;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("\n");

    Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    printf("\n");

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (source and destination): ");
        scanf("%d %d", &src, &dest);
        printf("\n");
        addEdge(graph, src, dest);
    }

    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &startVertex);
    printf("\n");
    BFS(graph, startVertex);

    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &startVertex);
    printf("\n");
    DFS(graph, startVertex);

    return 0;
}