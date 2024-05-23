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

// Structure to represent a stack
struct Stack {
    int capacity;
    int top;
    int* array;
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

// Create a stack with given capacity
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Check if the stack is empty
bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Push an item onto the stack
void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

// Pop an item from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) return -1;
    return stack->array[stack->top--];
}

// Depth-First Search (DFS) traversal of the graph using a stack
void DFS(struct Graph* graph, int startVertex) {
    // Stack for DFS traversal
    struct Stack* stack = createStack(MAX_VERTICES);

    // Push the start vertex onto the stack and mark it as visited
    push(stack, startVertex);
    graph->visited[startVertex] = true;

    printf("DFS Traversal: ");

    while (!isEmpty(stack)) {
        int currentVertex = pop(stack);
        printf("%d ", currentVertex);

        // Visit all adjacent vertices of the current vertex
        struct Node* temp = graph->adjacencyList[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->data;
            if (!graph->visited[adjVertex]) {
                push(stack, adjVertex);
                graph->visited[adjVertex] = true;
            }
            temp = temp->next;
        }
    }

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
        printf("2. Depth-First Search (DFS)\n");
        printf("3. Exit\n");
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
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
