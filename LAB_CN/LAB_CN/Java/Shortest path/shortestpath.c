#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NODES 100
#define INF INT_MAX

struct Node {
    int id;
    bool visited;
    int distance;
    int next_hop;
};

struct Network {
    int adjacency_matrix[MAX_NODES][MAX_NODES];
    int num_nodes;
    struct Node nodes[MAX_NODES];
};

void init_network(struct Network *net, int num_nodes) {
    net->num_nodes = num_nodes;
    for (int i = 0; i < num_nodes; i++) {
        net->nodes[i].id = i;
        net->nodes[i].visited = false;
        net->nodes[i].distance = INF;
        net->nodes[i].next_hop = -1;
        for (int j = 0; j < num_nodes; j++) {
            net->adjacency_matrix[i][j] = (i == j) ? 0 : INF;
        }
    }
}

void add_link(struct Network *net, int node1, int node2, int cost) {
    net->adjacency_matrix[node1][node2] = cost;
    net->adjacency_matrix[node2][node1] = cost;
}

void aodv(struct Network *net, int source) {
    net->nodes[source].distance = 0;
    net->nodes[source].next_hop = source;

    for (int i = 0; i < net->num_nodes; i++) {
        int min_distance = INF;
        int current_node = -1;

        for (int j = 0; j < net->num_nodes; j++) {
            if (!net->nodes[j].visited && net->nodes[j].distance < min_distance) {
                min_distance = net->nodes[j].distance;
                current_node = j;
            }
        }

        if (current_node == -1) break;

        net->nodes[current_node].visited = true;

        for (int j = 0; j < net->num_nodes; j++) {
            if (!net->nodes[j].visited && net->adjacency_matrix[current_node][j] != INF) {
                int new_distance = net->nodes[current_node].distance + net->adjacency_matrix[current_node][j];
                if (new_distance < net->nodes[j].distance) {
                    net->nodes[j].distance = new_distance;
                    net->nodes[j].next_hop = current_node;
                }
            }
        }
    }
}

void print_routing_table(struct Network *net, int node) {
    printf("Routing table for Node %d:\n", node);
    printf("Destination\tNext Hop\tDistance\n");
    for (int i = 0; i < net->num_nodes; i++) {
        printf("%d\t\t\t\t%d\t\t \t\t%d \n", i, net->nodes[i].next_hop, net->nodes[i].distance);
    }
}

void print_shortest_path(struct Network *net, int source, int destination) {
    printf("Shortest path from Node %d to Node %d:\n", source, destination);
    printf("Node Sequence: ");

    int current_node = destination;
    while (current_node != source) {
        printf("%d <- ", current_node);
        current_node = net->nodes[current_node].next_hop;
    }
    printf("%d\n", source);
    printf("Total Distance: %d\n", net->nodes[destination].distance);
}

int main() {
    struct Network net;
    init_network(&net, 6);

    add_link(&net, 0, 1, 1);
    add_link(&net, 0, 2, 2);
    add_link(&net, 1, 3, 3);
    add_link(&net, 2, 3, 2);
    add_link(&net, 2, 4, 5);
    add_link(&net, 3, 5, 4);
    add_link(&net, 4, 5, 1);

    aodv(&net, 0);

    for (int i = 0; i < net.num_nodes; i++) {
        print_routing_table(&net, i);
    }

    int source = 0;
    int destination = 5;
    print_shortest_path(&net, source, destination);

    return 0;
}
