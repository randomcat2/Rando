#include<stdio.h>
#define size 10
int arr[size];
int top=-1;

void push(int data)
{
    if(top==size-1)
    {
        printf("Stack overflow");
    }
    else
    {
        top++;
        arr[top]=data;
    }
}

int pop()
{
    int x;
    if(top==-1)
    {
        printf("Stack empty");
        return -1;
    }
    else
    {
        x=arr[top];
        top--;
       return x;
    }
}

int fibonacci(int n)
{
    push(0); 
    if (n == 1) return 1;

    push(1); 
    for (int i = 2; i < n; i++) {
        int fib1 = pop(); 
        int fib2 = pop();
        int fib = fib1 + fib2;
        push(fib2);
        push(fib1);
        push(fib);
    }

}

void displayStack() {
    printf("Fibonacci series: ");
    for (int i = 0; i <= top; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);

    fibonacci(n);
    displayStack();
}