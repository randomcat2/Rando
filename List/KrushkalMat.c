#include <stdio.h>
#include <stdlib.h>

#define INF 99999

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Function to create a graph with V vertices and E edges
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Function to create a graph
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// A utility function to find set of an element i (uses path compression technique)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// A function that does union of two sets of x and y (uses union by rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
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

// Function to print the constructed MST
void printMST(struct Edge result[], int E) {
    printf("Following are the edges in the constructed MST\n");
    for (int i = 0; i < E; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    }
}

// The main function to construct MST using Kruskal's algorithm
void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0; // Index for result[]
    int i = 0; // Index for sorted edges

    // Step 1: Sort all the edges in non-decreasing order of their weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    // Allocate memory for creating V subsets
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    // Create V subsets with single elements
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is V-1
    while (e < V - 1 && i < graph->E) {
        // Step 2: Pick the smallest edge. Check if it forms a cycle with the spanning-tree formed so far.
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does not cause a cycle, include it in result and increment the index of result
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the constructed MST
    printMST(result, e);

    // Free allocated memory
    free(subsets);
}

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V, E);

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        graph->edge[i].src = src;
        graph->edge[i].dest = dest;
        graph->edge[i].weight = weight;
    }

    KruskalMST(graph);

    // Free allocated memory
    free(graph->edge);
    free(graph);

    return 0;
}




// Graph Structure: The graph is represented using an edge list, where each edge has a source, destination, and weight.
// Union-Find Data Structure: This helps in detecting cycles. It includes two functions: find (with path compression) and Union (with union by rank).
// Kruskal's Algorithm:
// Step 1: Sort all edges in non-decreasing order of their weight.
// Step 2: Pick the smallest edge and check if it forms a cycle with the spanning-tree formed so far using the union-find data structure. If it doesn't form a cycle, include it in the result.
// Repeat until we have V-1 edges in the result.
// Main Function: This initializes the graph, reads user input for the edges, and calls the function to compute and print the MST.
