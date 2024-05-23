#include <stdio.h>

// Function prototypes
void inputArray(int arr[], int n);
void displayArray(int arr[], int n);
void quicksort(int arr[], int low, int high);
int partition(int arr[], int low, int high);

int main() {
    int choice;
    int n;
    int arr[100];

    do {
        printf("\nMenu:\n");
        printf("1. Input Array\n");
        printf("2. Sort Array using Quicksort\n");
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
                quicksort(arr, 0, n - 1);
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

// Function to perform quicksort
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Function to partition the array
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}
 