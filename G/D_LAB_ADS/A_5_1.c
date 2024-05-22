#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct {
    int id;
    char name[50];
    char department[50];
} Faculty;

Faculty faculty_database[TABLE_SIZE];

int hash_function(int id) {
    return id % TABLE_SIZE;
}

void insert_faculty(Faculty f) {
    int index = hash_function(f.id);
    while (faculty_database[index].id!= -1) {
        index = (index + 1) % TABLE_SIZE;
    }
    faculty_database[index] = f;
}

Faculty* search_faculty(int id) {
    int index = hash_function(id);
    while (faculty_database[index].id!= -1) {
        if (faculty_database[index].id == id) {
            return &faculty_database[index];
        }
        index = (index + 1) % TABLE_SIZE;
    }
    return NULL;
}

int main() {
    Faculty f1 = {1, "John Doe", "Computer Science"};
    Faculty f2 = {2, "Jane Doe", "Mathematics"};
    Faculty f3 = {3, "Jim Smith", "Physics"};

    insert_faculty(f1);
    insert_faculty(f2);
    insert_faculty(f3);

    Faculty* result = search_faculty(2);

    if (result!= NULL) {
        printf("Faculty found: ID=%d, Name=%s, Department=%s\n", result->id, result->name, result->department);
    } else {
        printf("Faculty not found\n");
    }

    return 0;
}