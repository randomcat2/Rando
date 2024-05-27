#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *prev;
    int data;
    struct Node *next;
} *first = NULL, *second = NULL, *third = NULL;

void create(int A[], int n) {
    struct Node *t, *last;
    int i;

    first = (struct Node*)malloc(sizeof(struct Node));
    first->data = A[0];
    first->prev = first->next = NULL;
    last = first;

    for (i = 1; i < n; i++) {
        t = (struct Node*)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = last->next;
        t->prev = last;
        last->next = t;
        last = t;
    }
}

void create2(int B[], int n) {
    struct Node *t, *last;
    int i;

    second = (struct Node*)malloc(sizeof(struct Node));
    second->data = B[0];
    second->prev = second->next = NULL;
    last = second;

    for (i = 1; i < n; i++) {
        t = (struct Node*)malloc(sizeof(struct Node));
        t->data = B[i];
        t->next = last->next;
        t->prev = last;
        last->next = t;
        last = t;
    }
}

void Display(struct Node *p) {
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int Length(struct Node *p) {
    int len = 0;

    while (p) {
        len++;
        p = p->next;
    }
    return len;
}

void Insert(struct Node *p, int index, int x) {
    struct Node *t;
    int i;
    if (index < 0 || index > Length(p)) {
        return;
    }
    if (index == 0) {
        t = (struct Node*)malloc(sizeof(struct Node));
        t->data = x;
        t->prev = NULL;
        t->next = first;
        if (first) first->prev = t;
        first = t;
    } else {
        for (i = 0; i < index - 1; i++) {
            p = p->next;
        }
        t = (struct Node*)malloc(sizeof(struct Node));
        t->data = x;
        t->prev = p;
        t->next = p->next;
        if (p->next) {
            p->next->prev = t;
        }
        p->next = t;
    }
}

int Delete(struct Node *p, int index) {
    int x = -1, i;

    if (index < 1 || index > Length(p)) {
        return -1;
    }
    if (index == 1) {
        first = first->next;
        if (first) {
            first->prev = NULL;
        }
        x = p->data;
        free(p);
    } else {
        for (i = 0; i < index - 1; i++) {
            p = p->next;
        }
        p->prev->next = p->next;
        if (p->next) {
            p->next->prev = p->prev;
        }
        x = p->data;
        free(p);
    }
    return x;
}

void Merge(struct Node *p, struct Node *q) {
    struct Node *last;
    if (p->data < q->data) {
        third = last = p;
        p = p->next;
        third->next = NULL;
    } else {
        third = last = q;
        q = q->next;
        third->next = NULL;
    }
    while (p && q) {
        if (p->data < q->data) {
            last->next = p;
            p->prev = last;
            last = p;
            p = p->next;
            last->next = NULL;
        } else {
            last->next = q;
            q->prev = last;
            last = q;
            q = q->next;
            last->next = NULL;
        }
    }
    if (p) {
        last->next = p;
        p->prev = last;
    }
    if (q) {
        last->next = q;
        q->prev = last;
    }
}

int main() {
    int A[] = {10, 20, 30, 40, 50};
    int B[] = {5, 15, 25, 35, 45};

    create(A, 5);
    create2(B, 5);

    printf("First linked list: ");
    Display(first);
    
    printf("Second linked list: ");
    Display(second);

    Merge(first, second);

    printf("Merged linked list: ");
    Display(third);

    return 0;
}
