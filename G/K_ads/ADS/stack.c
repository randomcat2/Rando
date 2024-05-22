#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Structure to represent a stack
struct Stack {
    int top;
    char *items[MAX_SIZE];
};

// Function to initialize stack
void initialize(struct Stack *s) {
    s->top = -1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *s) {
    return s->top == -1;
}

// Function to check if the stack is full
int isFull(struct Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Function to push an element onto the stack
void push(struct Stack *s, char *c) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = c;
}

// Function to pop an element from the stack
char *pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

// Function to return the precedence of an operator
int precedence(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return -1;
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to convert infix expression to prefix expression
void infixToPrefix(char *infix, char *prefix) {
    struct Stack stack;
    initialize(&stack);

    int i, j = 0;
    int len = strlen(infix);

    // Reverse the infix expression
    for (i = len - 1; i >= 0; i--) {
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
        prefix[j++] = infix[i];
    }
    prefix[j] = '\0';

    // Infix to postfix conversion
    for (i = 0; prefix[i] != '\0'; i++) {
        if (prefix[i] == '(')
            prefix[i] = ')';
        else if (prefix[i] == ')')
            prefix[i] = '(';
    }

    j = 0;
    for (i = 0; prefix[i] != '\0'; i++) {
        if (isalnum(prefix[i]))
            prefix[j++] = prefix[i];
        else if (prefix[i] == '(')
            push(&stack, &prefix[i]);
        else if (prefix[i] == ')') {
            while (!isEmpty(&stack) && *stack.items[stack.top] != '(')
                prefix[j++] = *pop(&stack);
            if (!isEmpty(&stack) && *stack.items[stack.top] != '(')
                printf("Invalid Expression\n");
            else
                pop(&stack);
        } else {
            while (!isEmpty(&stack) && precedence(prefix[i]) <= precedence(*stack.items[stack.top]))
                prefix[j++] = *pop(&stack);
            push(&stack, &prefix[i]);
        }
    }

    while (!isEmpty(&stack))
        prefix[j++] = *pop(&stack);
    prefix[j] = '\0';

    // Reverse the prefix expression
    len = strlen(prefix);
    for (i = 0; i < len / 2; i++) {
        char temp = prefix[i];
        prefix[i] = prefix[len - i - 1];
        prefix[len - i - 1] = temp;
    }
}

int main() {
    char infix[MAX_SIZE], prefix[MAX_SIZE];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPrefix(infix, prefix);

    printf("Prefix expression: %s\n", prefix);

    return 0;
}
