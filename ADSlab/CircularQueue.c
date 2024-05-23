#include <stdio.h>
#include <stdlib.h>

#define MAX 5  // Define the maximum size of the circular queue

// Function prototypes
void enqueue(int queue[], int *front, int *rear, int value);
int dequeue(int queue[], int *front, int *rear);
void display(int queue[], int front, int rear);

int main() {
    int queue[MAX];
    int front = -1, rear = -1;
    int choice, value;

    do {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to enqueue: ");
                scanf("%d", &value);
                enqueue(queue, &front, &rear, value);
                break;
            case 2:
                value = dequeue(queue, &front, &rear);
                if (value != -1) {
                    printf("Dequeued value: %d\n", value);
                }
                break;
            case 3:
                display(queue, front, rear);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to enqueue an element into the circular queue
void enqueue(int queue[], int *front, int *rear, int value) {
    if ((*front == 0 && *rear == MAX - 1) || (*rear == (*front - 1) % (MAX - 1))) {
        printf("Queue is full!\n");
        return;
    } else if (*front == -1) {  // Insert the first element
        *front = *rear = 0;
    } else if (*rear == MAX - 1 && *front != 0) {
        *rear = 0;
    } else {
        (*rear)++;
    }
    queue[*rear] = value;
    printf("Enqueued %d\n", value);
}

// Function to dequeue an element from the circular queue
int dequeue(int queue[], int *front, int *rear) {
    if (*front == -1) {
        printf("Queue is empty!\n");
        return -1;
    }

    int data = queue[*front];
    queue[*front] = -1;
    if (*front == *rear) {  // Queue has only one element, so we reset the queue
        *front = *rear = -1;
    } else if (*front == MAX - 1) {
        *front = 0;
    } else {
        (*front)++;
    }
    return data;
}

// Function to display the elements of the circular queue
void display(int queue[], int front, int rear) {
    if (front == -1) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue elements are: ");
    if (rear >= front) {
        for (int i = front; i <= rear; i++) {
            printf("%d ", queue[i]);
        }
    } else {
        for (int i = front; i < MAX; i++) {
            printf("%d ", queue[i]);
        }
        for (int i = 0; i <= rear; i++) {
            printf("%d ", queue[i]);
        }
    }
    printf("\n");
}
