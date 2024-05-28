#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a node in adjacency list
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
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

    newNode = createNode(src, weight);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// A utility function to find set of an element i (uses path compression technique)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// A function that does union of two sets of x and y (uses union by rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare two edges according to their weights
int compareEdges(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

// Function to construct MST using Kruskal's algorithm
void KruskalMST(struct Graph* graph) {
    int V = graph->numVertices;
    struct Edge result[V];
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges

    // Step 1: Sort all the edges in non-decreasing order of their weight
    qsort(graph->edges, graph->numEdges, sizeof(graph->edges[0]), compareEdges);

    // Allocate memory for creating V subsets
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    // Create V subsets with single elements
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is V-1
    while (e < V - 1 && i < graph->numEdges) {
        // Step 2: Pick the smallest edge. Check if it forms a cycle with the spanning-tree formed so far.
        struct Edge next_edge = graph->edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does not cause a cycle, include it in the result and increment the index of result
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the constructed MST
    printf("Following are the edges in the constructed MST:\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);

    free(subsets);
}

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V);

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    KruskalMST(graph);

    return 0;
}
