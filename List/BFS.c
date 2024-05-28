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

    // Uncomment the following lines for an undirected graph
    // Add edge from dest to src
    // newNode = createNode(src);
    // newNode->next = graph->adjLists[dest];
    // graph->adjLists[dest] = newNode;
}

// Queue structure for BFS
struct Queue {
    int items[100];
    int front;
    int rear;
};

// Function to create a queue
struct Queue* createQueue() {
    struct Queue* queue = malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    if (queue->rear == -1)
        return 1;
    else
        return 0;
}

// Function to add an element to the queue
void enqueue(struct Queue* queue, int value) {
    if (queue->rear == 99)
        printf("\nQueue is full");
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

// Function to remove an element from the queue
int dequeue(struct Queue* queue) {
    int item;
    if (isEmpty(queue)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}

// BFS algorithm
void bfs(struct Graph* graph, int startVertex) {
    struct Queue* queue = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        struct Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->data;

            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
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

    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &startVertex);

    printf("BFS Traversal starting from vertex %d:\n", startVertex);
    bfs(graph, startVertex);

    return 0;
}
