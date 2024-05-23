#include <stdio.h>
#include <stdbool.h>

#define ROWS 10
#define COLS 3

int hashTable[ROWS][COLS] = {0};

int hashFunction(int value) {
    return value % ROWS;
}

void insert(int value) {
    int index = hashFunction(value);
    for (int col = 0; col < COLS; col++) {
        if (hashTable[index][col] == -1) { // Check for -1 instead of 0
            hashTable[index][col] = value;
            printf("Inserted %d at address (%d, %d)\n", value, index, col);
            return;
        }
    }
    
    int col = 0;
    while (true) {
        int newIndex = (index + 1) % ROWS;
        if (hashTable[newIndex][col] == -1) { // Check for -1 instead of 0
            hashTable[newIndex][col] = value;
            printf("Inserted %d at address (%d, %d)\n", value, newIndex, col);
            return;
        }
        col = (col + 1) % COLS;
        if (col == 0) {
            printf("Hash Table is full. Unable to insert %d.\n", value);
            return;
        }
    }
}


void printHashTable() {
    printf("\nHash Table:\n");
    for (int i = 0; i < ROWS; i++) {
        printf("Index %d:", i);
        for (int j = 0; j < COLS; j++) {
            printf(" %d", hashTable[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int choice, value;
    for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
        hashTable[i][j] = -1;
    }
}
    while (true) {
        printf("\nLinear Probing Hashing Operations:\n");
        printf("1. Insert\n");
        printf("2. Print Hash Table\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(value);
                break;
            case 2:
                printHashTable();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}