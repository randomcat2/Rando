#include <stdio.h>

void findSwappedElements(int arr[], int n) {
    int first = -1, second = -1;
    
    // Traverse the array to find the two elements that are out of order
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if (first == -1) {
                first = i;
            } else {
                second = i + 1;
                break;
            }
        }
    }

    // If second is still -1, it means the swapped elements are adjacent
    if (second == -1) {
        second = first + 1;
    }

    printf("Swapped elements are: %d and %d\n", arr[first], arr[second]);
    printf("Their positions are: %d and %d\n", first, second);
}

int main() {
    int arr[] = {1, 2,4,3,5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    findSwappedElements(arr, n);

    return 0;
}
