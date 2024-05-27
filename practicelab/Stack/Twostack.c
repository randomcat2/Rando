#include<stdio.h>
#define size 20
int arr[size];
int top1=-1;
int top2=size;

void push1(int data)
{
    if(top1>=top2-1)
    {
        printf("Stack overflow");
    }
    else
    {
        top1++;
        arr[top1]=data;
    }
}

void push2(int data)
{
    if(top1>=top2-1)
    {
        printf("Stack Overflow");
    }
    else
    {
        top2--;
        arr[top2]=data;
    }
}

void pop1()
{
    if(top1<0)
    {

        printf("Stack Empty");
    }
    else
    {
        int x=arr[top1];
        top1--;
        printf("Popped element is: %d",x);
    }
}

void pop2()
{
    if(top2>=size)
    {

        printf("Stack Empty");
    }
    else
    {
        int x=arr[top2];
        top2++;
        printf("Popped element is: %d",x);
    }
}

void display1()
{
  if (top1 < 0)
    {
        printf("Stack1 is empty\n");
    }
    else
    {
        for (int i = top1; i >= 0; --i)
        {
            printf("Stack elements:%d ", arr[i]);
        }
        printf("\n");
    }  
} 

void display2()
{
  if (top2 < size) {
        printf("Stack2 elements: ");
        for (int i = top2; i < size; ++i) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("Stack2 is empty\n");
    }
}


int main()
{
    int choice;
    while (1) {
        printf("\nEnter a choice:\n");
        printf("1. To push in stack1\n");
        printf("2. To push in stack2\n");
        printf("3. To pop from stack1\n");
        printf("4. To pop from stack2\n");
        printf("5. To display stacks\n");
        printf("6. To exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int b;
                printf("Enter a number to push into stack1: ");
                scanf("%d", &b);
                push1(b);
                break;
            }
            case 2: {
                int c;
                printf("Enter a number to push into stack2: ");
                scanf("%d", &c);
                push2(c);
                break;
            }
            case 3: {
                pop1();
                break;
            }
            case 4: {
                pop2();
                break;
            }
            case 5: {
                display1();
                display2();
                break;
            }
            case 6: {
                return 0;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    }
    return 0;
}