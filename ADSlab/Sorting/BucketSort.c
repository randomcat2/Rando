#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void inputArray(int arr[], int n);
void displayArray(int arr[], int n);
void bucketSort(int arr[], int n);
void insertionSort(int arr[], int n);

int main() {
    int choice;
    int n;
    int arr[100];

    do {
        printf("\nMenu:\n");
        printf("1. Input Array\n");
        printf("2. Sort Array using Bucket Sort\n");
        printf("3. Display Array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of elements in the array: ");
                scanf("%d", &n);
                if (n > 100) {
                    printf("Array size exceeds the maximum limit of 100.\n");
                } else {
                    inputArray(arr, n);
                }
                break;
            case 2:
                bucketSort(arr, n);
                printf("Array sorted successfully.\n");
                break;
            case 3:
                displayArray(arr, n);
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

// Function to input array elements
void inputArray(int arr[], int n) {
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
}

// Function to display array elements
void displayArray(int arr[], int n) {
    printf("Array elements are:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to perform bucket sort
void bucketSort(int arr[], int n) {
    if (n <= 0) {
        return;
    }

    // Find the maximum element to determine the range of buckets
    int maxValue = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }

    // Create n empty buckets
    int bucketCount = n;
    int** buckets = (int**)malloc(bucketCount * sizeof(int*));
    int* bucketSizes = (int*)malloc(bucketCount * sizeof(int));
    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = (int*)malloc(n * sizeof(int));
        bucketSizes[i] = 0;
    }

    // Distribute array elements into buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = (arr[i] * bucketCount) / (maxValue + 1);
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }

    // Sort each bucket using insertion sort
    for (int i = 0; i < bucketCount; i++) {
        insertionSort(buckets[i], bucketSizes[i]);
    }

    // Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[index++] = buckets[i][j];
        }
    }

    // Free memory
    for (int i = 0; i < bucketCount; i++) {
        free(buckets[i]);
    }
    free(buckets);
    free(bucketSizes);
}

// Function to perform insertion sort on an array
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
