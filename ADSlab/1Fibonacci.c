#include <stdio.h>

// Function prototypes
void fibonacciNonRecursive(int n);
void fibonacciRecursive(int n);
int fibonacciHelper(int n);

int main() {
    int n, choice;

    // Taking input from the user
    printf("Enter the number of Fibonacci numbers you want in the series: ");
    scanf("%d", &n);

    // Menu for choosing method
    printf("Choose method:\n");
    printf("1. Non-recursive\n");
    printf("2. Recursive\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    // Using switch case to handle the choice
    switch (choice) {
        case 1:
            fibonacciNonRecursive(n);
            break;
        case 2:
            fibonacciRecursive(n);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

// Function to generate Fibonacci series non-recursively
void fibonacciNonRecursive(int n) {
    int a = 0, b = 1, next;
    printf("Non-recursive Fibonacci series:\n");
    for (int i = 0; i < n; i++) {
        if (i <= 1)
            next = i;
        else {
            next = a + b;
            a = b;
            b = next;
        }
        printf("%d ", next);
    }
    printf("\n");
}

// Function to generate Fibonacci series recursively
void fibonacciRecursive(int n) {
    printf("Recursive Fibonacci series:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacciHelper(i));
    }
    printf("\n");
}

// Helper function to calculate Fibonacci number recursively
int fibonacciHelper(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacciHelper(n - 1) + fibonacciHelper(n - 2);
}
