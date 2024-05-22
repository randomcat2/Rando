#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct {
    int *elems;
    int length;
    int size;
} PriorityQueue;

PriorityQueue* createQueue(int size) {
    PriorityQueue* queue = (PriorityQueue*) malloc(sizeof(PriorityQueue));
    queue->elems = (int*) malloc(size * sizeof(int));
    queue->length = 0;
    queue->size = size;
    return queue;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void heapify(PriorityQueue* queue, int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < queue->length && queue->elems[left] > queue->elems[largest])
        largest = left;

    if (right < queue->length && queue->elems[right] > queue->elems[largest])
        largest = right;

    if (largest != idx) {
        swap(&queue->elems[largest], &queue->elems[idx]);
        heapify(queue, largest);
    }
}

void insert(PriorityQueue* queue, int elem) {
    if (queue->length == queue->size) {
        printf("\nOverflow - Could not insert Key\n");
        return;
    }

    queue->elems[queue->length] = elem;
    int i = queue->length;
    queue->length++;

    while (i != 0 && queue->elems[(i - 1) / 2] < queue->elems[i]) {
       swap(&queue->elems[i], &queue->elems[(i - 1) / 2]);
       i = (i - 1) / 2;
    }
}

int extractMax(PriorityQueue* queue) {
    if (queue->length <= 0)
        return INT_MIN;
    if (queue->length == 1) {
        queue->length--;
        return queue->elems[0];
    }

    int root = queue->elems[0];
    queue->elems[0] = queue->elems[queue->length - 1];
    queue->length--;
    heapify(queue, 0);

    return root;
}

int main() {
    int size, choice, elem;

    printf("Enter the maximum size of the priority queue: ");
    scanf("%d", &size);

    PriorityQueue* queue = createQueue(size);

    do {
        printf("\nPriority Queue Menu:\n");
        printf("1. Insert\n");
        printf("2. Extract Max\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &elem);
                insert(queue, elem);
                break;
            case 2:
                printf("Extracted max is %d\n", extractMax(queue));
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
