#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Queue {
    int items[MAX];
    int front;
    int rear;
} Queue;

Queue* createQueue();
void enqueue(Queue* q, int);
int dequeue(Queue* q);
void printQueue(Queue* q);
int isEmpty(Queue* q);

void bfs(int adjacencyMatrix[][MAX], int startVertex, int n);
void DFS(int adjacencyMatrix[][MAX], int start, int n);

int main() {
    int adjacencyMatrix[MAX][MAX];
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }

    printf("Enter the starting vertex: ");
    int startVertex;
    scanf("%d", &startVertex);

    printf("BFS traversal: ");
    bfs(adjacencyMatrix, startVertex, n);

    printf("\nDFS traversal: ");
    DFS(adjacencyMatrix, startVertex, n);

    return 0;
}

Queue* createQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX - 1)
        printf("\nQueue is Full!!");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

int isEmpty(Queue* q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

void bfs(int adjacencyMatrix[][MAX], int startVertex, int n) {
    Queue* q = createQueue();

    int visited[MAX];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    visited[startVertex] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%c ", currentVertex + 65);

        for (int i = 0; i < n; i++) {
            if (adjacencyMatrix[currentVertex][i] == 1 && visited[i] == 0) {
                enqueue(q, i);
                visited[i] = 1;
            }
        }
    }
}

void DFS(int adjacencyMatrix[][MAX], int start, int n) {
    int stack[MAX];
    int top = -1;
    int visited[MAX] = {0};
    int i, j;

    stack[++top] = start; // push start vertex into the stack
    visited[start] = 1;

    while(top != -1) {
        j = stack[top--]; // pop a vertex from the stack
        printf("%c ", j + 65);

        // push all unvisited and adjacent vertices of j into the stack
        for(i = 0; i < n; i++) {
            if(adjacencyMatrix[j][i] == 1 && visited[i] == 0) {
                stack[++top] = i;
                visited[i] = 1;
            }
        }
    }
}
