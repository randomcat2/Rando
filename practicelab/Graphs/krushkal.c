#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int src, dest, weight;
} Edge;

typedef struct Node {
    int dest, weight;
    struct Node* next;
} Node;

typedef struct Graph {
    int V;
    Node** adjList;
    Edge* edges;
    int numEdges; // New member to keep track of the number of edges
} Graph;

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adjList = (Node**)malloc(V * sizeof(Node*));
    graph->edges = (Edge*)malloc(V * V * sizeof(Edge)); // Maximum possible edges
    graph->numEdges = 0; // Initialize the number of edges to 0

    for (int i = 0; i < V; ++i)
        graph->adjList[i] = NULL;

    return graph;
}

Node* createNode(int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;

    // Add the edge to the edges array
    graph->edges[graph->numEdges].src = src;
    graph->edges[graph->numEdges].dest = dest;
    graph->edges[graph->numEdges].weight = weight;
    graph->numEdges++; // Increment the number of edges
}

void swap(Edge* a, Edge* b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Edge edges[], int low, int high) {
    int pivot = edges[high].weight;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (edges[j].weight < pivot) {
            i++;
            swap(&edges[i], &edges[j]);
        }
    }
    swap(&edges[i + 1], &edges[high]);
    return (i + 1);
}

void quickSort(Edge edges[], int low, int high) {
    if (low < high) {
        int pi = partition(edges, low, high);
        quickSort(edges, low, pi - 1);
        quickSort(edges, pi + 1, high);
    }
}

int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void unionSets(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

void kruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V];
    int e = 0;
    int i = 0;
    quickSort(graph->edges, 0, graph->numEdges - 1); // Use numEdges instead of E
    
    int *parent = (int*)malloc(V * sizeof(int));
    for (int v = 0; v < V; ++v)
        parent[v] = -1;

    while (e < V - 1 && i < graph->numEdges) { // Use numEdges instead of E
        Edge next_edge = graph->edges[i++];
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            unionSets(parent, x, y);
        }
    }

    printf("Edges in the MST:\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
}

int main() {
    int V = 4; // Change as needed
    Graph* graph = createGraph(V);

    // Add edges
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 6);
    addEdge(graph, 0, 3, 5);
    addEdge(graph, 1, 3, 15);
    addEdge(graph, 2, 3, 4);

    kruskalMST(graph);

    return 0;
}
