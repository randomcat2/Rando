#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack definition
typedef struct {
    int top;
    char items[MAX];
} Stack;

// Function prototypes
void push(Stack *s, char c);
char pop(Stack *s);
char peek(Stack *s);
int isEmpty(Stack *s);
int precedence(char op);
void infixToPostfix(char *infix, char *postfix);

int main() {
    char infix[MAX], postfix[MAX];

    // Taking input from the user
    printf("Enter an infix expression: ");
    gets(infix);

    // Converting infix to postfix
    infixToPostfix(infix, postfix);

    // Output the postfix expression
    printf("Postfix expression: %s\n", postfix);

    return 0;
}

// Push an element onto the stack
void push(Stack *s, char c) {
    if (s->top == MAX - 1) {
        printf("Stack overflow\n");
        exit(1);
    } else {
        s->items[++(s->top)] = c;
    }
}

// Pop an element from the stack
char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        exit(1);
    } else {
        return s->items[(s->top)--];
    }
}

// Peek the top element of the stack
char peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        exit(1);
    } else {
        return s->items[s->top];
    }
}

// Check if the stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Return the precedence of the operator
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Convert infix expression to postfix expression
void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    s.top = -1;
    int i = 0, j = 0;
    char c;

    while ((c = infix[i++]) != '\0') {
        if (isalnum(c)) {
            postfix[j++] = c; // Add operands directly to the postfix expression
        } else if (c == '(') {
            push(&s, c); // Push '(' to stack
        } else if (c == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s); // Pop until '(' is found
            }
            if (!isEmpty(&s) && peek(&s) != '(') {
                printf("Invalid expression\n");
                exit(1); // Invalid expression
            } else {
                pop(&s); // Pop '(' from stack
            }
        } else { // Operator encountered
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(c)) {
                postfix[j++] = pop(&s); // Pop operators with higher or equal precedence
            }
            push(&s, c); // Push current operator to stack
        }
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s); // Pop all remaining operators in stack
    }

    postfix[j] = '\0'; // Null-terminate the postfix expression
}
