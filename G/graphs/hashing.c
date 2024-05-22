#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct Node {
    int key;
    char value[100];
    struct Node* next;
} Node;

typedef struct {
    Node* h[SIZE];
} HashTable;

int hashing(int key) {
    return (3 * key + 5) % SIZE;
}

void initHashTable(HashTable* ht) {
    for (int i = 0; i < SIZE; i++) {
        ht->h[i] = NULL;
    }
}

void insert(HashTable* ht, int key, const char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    strcpy(newNode->value, value);
    newNode->next = NULL;

    int index = hashing(key);
    newNode->next = ht->h[index];
    ht->h[index] = newNode;
}

void search(HashTable* ht, int key) {
    int index = hashing(key);
    Node* temp = ht->h[index];
    while (temp != NULL) {
        if (temp->key == key) {
            printf("Found: %s\n", temp->value);
            return;
        }
        temp = temp->next;
    }
    printf("Not found\n");
}

void del(HashTable* ht, int key) {
    int index = hashing(key);
    Node* temp = ht->h[index];
    Node* prev = NULL;
    
    while (temp != NULL && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Key not found\n");
        return;
    }
    
    if (prev == NULL) {
        ht->h[index] = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    free(temp);
    printf("Key deleted\n");
}

void display(HashTable* ht) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d -> ", i);
        Node* temp = ht->h[i];
        if (temp == NULL) {
            printf("Empty");
        } else {
            while (temp != NULL) {
                printf("%s ", temp->value);
                temp = temp->next;
            }
        }
        printf("\n");
    }
}

int main() {
    HashTable ht;
    initHashTable(&ht);
    int choice;
    do {
        printf("\n1) Insert 2) Search 3) Delete 4) Display 5) Exit\n");
        printf("Enter: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                char str[100];
                int key;
                printf("Enter key and value: ");
                scanf("%d %s", &key, str);
                insert(&ht, key, str);
                break;
            }
            case 2: {
                int key;
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(&ht, key);
                break;
            }
            case 3: {
                int key;
                printf("Enter key to delete: ");
                scanf("%d", &key);
                del(&ht, key);
                break;
            }
            case 4: {
                display(&ht);
                break;
            }
            case 5: {
                printf("Exiting...\n");
                break;
            }
            default: {
                printf("Invalid choice. Try again.\n");
                break;
            }
        }
    } while (choice != 5);

    return 0;
}
