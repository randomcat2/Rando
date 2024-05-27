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

int fact(int n)
{
    int fac=1;
    int x;
    for(int i=1;i<=n;i++)
    {
        x=pop();
        fac=fac*x;
    }
    return fac;
}

int main()
{
    int n;
    printf("Enter the no:");
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        push(i);
    }
    printf("Factorial is: %d",fact(n));
    return 0;
}