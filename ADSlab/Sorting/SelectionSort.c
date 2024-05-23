#include <stdio.h>

// Function prototypes
void inputArray(int arr[], int n);
void displayArray(int arr[], int n);
void selectionSort(int arr[], int n);

int main() {
    int choice;
    int n;
    int arr[100];

    do {
        printf("\nMenu:\n");
        printf("1. Input Array\n");
        printf("2. Sort Array using Selection Sort\n");
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
                selectionSort(arr, n);
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

// Function to perform selection sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Swap the found minimum element with the first element
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}
