#include <stdio.h>
#include <stdbool.h>

#define TABLE_SIZE 10
#define NUM_TABLES 2

int hashTables[NUM_TABLES][TABLE_SIZE];

// Hash function 1
int hashFunction1(int value) {
    return value % TABLE_SIZE;
}

// Hash function 2
int hashFunction2(int value) {
    return (value / TABLE_SIZE) % TABLE_SIZE;
}

// Function to insert value into hash tables using cuckoo hashing
bool insert(int value) {
    int tableIndex = 0; // Start with table 0
    int currentValue = value;
    int numIterations = 0;

    while (numIterations < TABLE_SIZE) {
        int hash = (tableIndex == 0) ? hashFunction1(currentValue) : hashFunction2(currentValue);

        // Check if slot is empty
        if (hashTables[tableIndex][hash] == 0) {
            hashTables[tableIndex][hash] = currentValue;
            printf("Inserted %d into Table %d at index %d\n", currentValue, tableIndex, hash);
            return true;
        } else {
            // Swap values
            int temp = hashTables[tableIndex][hash];
            hashTables[tableIndex][hash] = currentValue;
            currentValue = temp;
        }

        // Switch table
        tableIndex = (tableIndex + 1) % NUM_TABLES;
        numIterations++;
    }

    // Unable to insert
    return false;
}

// Function to print hash tables
void printHashTables() {
    printf("\nHash Tables:\n");
    for (int i = 0; i < NUM_TABLES; i++) {
        printf("Table %d: ", i);
        for (int j = 0; j < TABLE_SIZE; j++) {
            printf("%d ", hashTables[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Initialize hash tables
    for (int i = 0; i < NUM_TABLES; i++) {
        for (int j = 0; j < TABLE_SIZE; j++) {
            hashTables[i][j] = 0;
        }
    }

    int choice, value;
    while (true) {
        printf("\nCuckoo Hashing Operations:\n");
        printf("1. Insert\n");
        printf("2. Print Hash Tables\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                if (!insert(value))
                    printf("Unable to insert %d. Hash tables are full or insertion failed.\n", value);
                break;
            case 2:
                printHashTables();
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
