#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node
{
    char data;
    struct Node *next;
} *top = NULL;

void push(char x)
{
    struct Node *t;
    t = (struct Node *)malloc(sizeof(struct Node));

    if (t == NULL)
        printf("stack is full\n");
    else
    {
        t->data = x;
        t->next = top;
        top = t;
    }
}

char pop()
{
    char x = -1;
    if (top == NULL)
        printf("Stack is Empty\n");
    else
    {
        struct Node *t = top;
        top = top->next;
        x = t->data;
        free(t);
    }
    return x;
}

int pre(char x)
{
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 2;
    return 0;
}

int isOperand(char x)
{
    return isalnum(x); // check if the character is alphanumeric (operand)
}

void reverse(char *exp)
{
    int length = strlen(exp);
    for (int i = 0; i < length / 2; i++)
    {
        char temp = exp[i];
        exp[i] = exp[length - i - 1];
        exp[length - i - 1] = temp;
    }
}

char *InfixToPostfix(char *infix)
{
    int i = 0, j = 0;
    int len = strlen(infix);
    char *postfix = (char *)malloc((len + 2) * sizeof(char));

    while (infix[i] != '\0')
    {
        if (isOperand(infix[i]))
            postfix[j++] = infix[i++];
        else if (infix[i] == '(')
            push(infix[i++]);
        else if (infix[i] == ')')
        {
            while (top != NULL && top->data != '(')
                postfix[j++] = pop();
            pop(); // pop '('
            i++;
        }
        else
        {
            while (top != NULL && pre(infix[i]) <= pre(top->data))
                postfix[j++] = pop();
            push(infix[i++]);
        }
    }
    while (top != NULL)
        postfix[j++] = pop();
    postfix[j] = '\0';
    return postfix;
}

char *InfixToPrefix(char *infix)
{
    // Step 1: Reverse the infix expression
    reverse(infix);

    // Step 2: Replace '(' with ')' and vice versa
    for (int i = 0; infix[i] != '\0'; i++)
    {
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
    }

    // Step 3: Get the postfix expression of the modified infix expression
    char *postfix = InfixToPostfix(infix);

    // Step 4: Reverse the postfix expression to get the prefix expression
    reverse(postfix);

    return postfix;
}

int main()
{
    char infix[] = "((a+b)*c)-d^e^f";
    printf("Infix expression: %s\n", infix);

    char *prefix = InfixToPrefix(infix);
    printf("Prefix expression: %s\n", prefix);

    free(prefix); // Don't forget to free the allocated memory for prefix

    return 0;
}
