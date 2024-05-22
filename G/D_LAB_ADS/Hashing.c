#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct {
    int h[SIZE];
    int comp1;
} HashTable;

void initHashTable(HashTable* ht) {
    ht->comp1 = 0;
    for (int i = 0; i < SIZE; i++) {
        ht->h[i] = 0;
    }
}

int hashing(int key) {
    return key % SIZE;
}

int probing(HashTable* ht, int key) {
    int index = hashing(key);
    int i = 0;
    while (ht->h[(index + i) % SIZE] != 0) {
        i++;
    }
    return (index + i) % SIZE;
}

void insertforwithout(HashTable* ht, int key) {
    int index = hashing(key);
    if (ht->h[index] != 0) {
        index = probing(ht, key);
    }
    ht->h[index] = key;
}

void insertforwith(HashTable* ht, int key) {
    int index = hashing(key);
    if (ht->h[index] != 0) {
        if (ht->h[index] % SIZE == index) {
            int newIndex = probing(ht, key);
            ht->h[newIndex] = key;
        } else {
            int x = ht->h[index];
            ht->h[index] = key;
            int i = probing(ht, x);
            ht->h[i] = x;
        }
    } else {
        ht->h[index] = key;
    }
}

void display(HashTable* ht) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d -> %d\n", i, ht->h[i]);
    }
}

void search(HashTable* ht, int key) {
    int index = hashing(key);
    int i = 0;
    int flag = 0;
    while (ht->h[(index + i) % SIZE] != 0) {
        ht->comp1++;
        if (ht->h[(index + i) % SIZE] == key) {
            flag = 1;
            break;
        }
        i++;
    }
    if (flag == 1) {
        printf("\n\nComp: %d\n", ht->comp1);
    } else {
        printf("\nNot found\n");
    }
}

int main() {
    HashTable ht;
    initHashTable(&ht);
    int choice;
    do {
        printf("\n1) Insert 2) Search 3) Display\n");
        printf("Enter: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                int key;
                printf("\n\nEnter key: ");
                scanf("%d", &key);
                insertforwith(&ht, key);
                break;
            }
            case 2: {
                int key;
                printf("\n\nEnter key to search: ");
                scanf("%d", &key);
                search(&ht, key);
                break;
            }
            case 3: {
                display(&ht);
                break;
            }
            default: {
                printf("Invalid choice. Try again.\n");
                break;
            }
        }
    } while (choice >= 1 && choice <= 3);

    return 0;
}