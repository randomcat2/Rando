#include <stdio.h>
#include <stdlib.h>

struct student {
    int roll;
    char name[20];
    float CGPA;
};

int swapCountQuickSort = 0;
int swapCountHeapSort = 0;

void swap(int *a, int *b, int *swapCount) {
    int temp = *a;
    *a = *b;
    *b = temp;
    (*swapCount)++;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high;
    while (i < j) {
        while (arr[i] <= pivot && i <= high) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j], &swapCountQuickSort);
        }
    }
    swap(&arr[low], &arr[j], &swapCountQuickSort);
    return j;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int index = partition(arr, low, high);
        quickSort(arr, low, index - 1);
        quickSort(arr, index + 1, high);
    }
}

void createHeap(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest], &swapCountHeapSort);
        createHeap(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        createHeap(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i], &swapCountHeapSort);
        createHeap(arr, i, 0);
    }
}

void displaySortedStudents(struct student s[], int arr[], int n) {
    printf("Sorted Student Details:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[j].roll == arr[i]) {
                printf("Roll No: %d, Name: %s, CGPA: %.2f\n", s[j].roll, s[j].name, s[j].CGPA);
                break;
            }
        }
    }
}

int main() {
    struct student s[3];
    int arr[3];

    for (int i = 0; i < 3; i++) {
        printf("Enter roll: ");
        scanf("%d", &s[i].roll);
        printf("Enter name: ");
        scanf("%s", s[i].name);
        printf("Enter CGPA: ");
        scanf("%f", &s[i].CGPA);
        arr[i] = s[i].roll;
    }

    quickSort(arr, 0, 2);
    printf("\nSorted using QuickSort:\n");
    displaySortedStudents(s, arr, 3);
    printf("Number of swaps in QuickSort: %d\n", swapCountQuickSort);

    // Reset the array to the original state
    for (int i = 0; i < 3; i++) {
        arr[i] = s[i].roll;
    }

    heapSort(arr, 3);
    printf("\nSorted using HeapSort:\n");
    displaySortedStudents(s, arr, 3);
    printf("Number of swaps in HeapSort: %d\n", swapCountHeapSort);

    return 0;
}
