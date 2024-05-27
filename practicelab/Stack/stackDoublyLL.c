#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};
struct Node *top = NULL;

void push(int x) {
    struct Node *newnode;
    newnode = (struct Node*)malloc(sizeof(struct Node));
    if (newnode == NULL) {
        printf("Stack overflow\n");
        return;
    }
    newnode->data = x;
    newnode->next = top;
    newnode->prev = NULL;
    if (top != NULL) {
        top->prev = newnode;
    }
    top = newnode;
}

void pop() {
    struct Node *temp;
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    } else {
        temp = top;
        printf("Popped value is %d\n", top->data);
        top = top->next;
        if (top != NULL) {
            top->prev = NULL;
        }
        free(temp);
    }
}

void display() {
    struct Node *temp;
    temp = top;
    if (top == NULL) {
        printf("Stack is empty\n");
    } else {
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    push(5);
    push(2);
    push(3);
    display();
    pop();
    display();
    return 0;
}
