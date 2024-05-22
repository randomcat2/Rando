#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int result;
    char name[50];
    struct Student* left;
    struct Student* right;
} Student;

typedef struct StackNode {
    struct Student* data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;

Student* newStudent(int result, char name[]) {
    Student* student = (Student*)malloc(sizeof(Student));
    student->result = result;
    strcpy(student->name, name);
    student->left = NULL;
    student->right = NULL;
    return student;
}

Student* insert(Student* student, int result, char name[]) {
    if (student == NULL) return newStudent(result, name);

    if (result < student->result)
        student->left  = insert(student->left, result, name);
    else if (result > student->result)
        student->right = insert(student->right, result, name);

    return student;
}

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack* stack, Student* student) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = student;
    newNode->next = stack->top;
    stack->top = newNode;
}

Student* pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    StackNode* temp = stack->top;
    Student* poppedNode = temp->data;
    stack->top = temp->next;
    free(temp);
    return poppedNode;
}

int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

void assignRollNo(Student* root) {
    Stack* stack = createStack();
    Student* current = root;
    int rollNo = 1;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->right;
        }
        current = pop(stack);
        printf("Roll No: %d, Name: %s, Result: %d\n", rollNo++, current->name, current->result);
        current = current->left;
    }
}

int main() {
    Student* root = NULL;
    int result;
    char name[50];

    printf("Enter student data (enter -1 for the result to stop):\n");
    while (1) {
        printf("Enter result: ");
        scanf("%d", &result);
        if (result == -1) break;
        printf("Enter name: ");
        scanf("%s", name);
        root = insert(root, result, name);
    }

    printf("Assigning roll numbers...\n");
    assignRollNo(root);

    return 0;
}
