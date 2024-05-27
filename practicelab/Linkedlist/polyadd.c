#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int coeff;
    int exp;
    struct Node *next;
}*poly=NULL;

struct Node *create()
{
    struct Node *t,*last=NULL,*poly=NULL;
    int num;
    int i;

    printf("Enter the no. of terms: ");
    scanf("%d",&num);
    printf("Enter each term with coeff and exp\n");

    for(i=0;i<num;i++)
    {
        t=(struct Node*)malloc(sizeof(struct Node));
        scanf("%d%d",&t->coeff,&t->exp);
        t->next=NULL;
        if(poly==NULL)
        {
            poly=last=t;
        }
        else
        {
            last->next=t;
            last=t;
        }
    }
    return poly;
}

void Display(struct Node *p)
{
    while(p)
    {
        printf("%dx%d +",p->coeff,p->exp);
        if(p->next)
           printf(" + ");
        p=p->next;   
    }
    printf("\n");
}

struct Node *add(struct Node *p1,struct Node *p2)
{
    struct Node *poly3=NULL,*p3=NULL;
    while(p1!=NULL && p2!=NULL)
    {
        struct Node *t=(struct Node*)malloc(sizeof(struct Node));
        t->next=NULL;
        if(p1->exp==p2->exp)
        {
            t->coeff=p1->coeff+p2->coeff;
            t->exp=p1->exp;
            p1=p1->next;
            p2=p2->next;
        }
        else if(p1->exp > p2->exp)
        {
            t->exp=p1->exp;
            t->coeff=p1->coeff;
            p1=p1->next;
        }
        else
        {
            t->exp=p2->exp;
            t->coeff=p2->coeff;
            p2=p2->next;
        }

        if(poly3==NULL)
           poly3=p3=t;
        else
        {
            p3->next=t;
            p3=t;
        }   
    }
    while (p1 != NULL)
    {
        struct Node *t = (struct Node *)malloc(sizeof(struct Node));
        t->coeff = p1->coeff;
        t->exp = p1->exp;
        t->next = NULL;

        p3->next = t;
        p3 = t;
        p1 = p1->next;
    }

    while (p2 != NULL)
    {
        struct Node *t = (struct Node *)malloc(sizeof(struct Node));
        t->coeff = p2->coeff;
        t->exp = p2->exp;
        t->next = NULL;

        p3->next = t;
        p3 = t;
        p2 = p2->next;
    }

    return poly3;
}

int main()
{
    struct Node *poly1, *poly2, *poly3;

    printf("Enter first polynomial:\n");
    poly1 = create();
    Display(poly1);

    printf("Enter second polynomial:\n");
    poly2 = create();
    Display(poly2);

    poly3 = add(poly1, poly2);
    printf("Resultant polynomial after addition:\n");
    Display(poly3);

    return 0;
}