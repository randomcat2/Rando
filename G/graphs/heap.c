#include <stdio.h>

#define MAX_SIZE 10

typedef struct {
    int arr[MAX_SIZE];
    int cnt;
    int m;
} Heap;

void heap_init(Heap *h);
void insert(Heap *h);
void heapify(Heap *h, int n);
void heapsort(Heap *h);
void display(Heap *h);

void heap_init(Heap *h) {
    h->cnt = 0;
    printf("\nEnter number of nodes: ");
    scanf("%d", &h->m);
}

void insert(Heap *h) {
    for (int i = 0; i < h->m; i++) {
        printf("\nEnter: ");
        scanf("%d", &h->arr[i]);
        heapify(h, h->cnt);
        h->cnt++;
    }
}

void heapify(Heap *h, int n) {
    int i = n;
    while (i > 0) {
        int z = (i - 1) / 2;
        if (h->arr[z] < h->arr[i]) {
            int temp = h->arr[i];
            h->arr[i] = h->arr[z];
            h->arr[z] = temp;
        } else {
            break;
        }
        i = (i - 1) / 2;
    }
}

void heapsort(Heap *h) {
    int cnt1 = h->m - 1;
    while (cnt1 >= 0) {
        int temp = h->arr[cnt1];
        h->arr[cnt1] = h->arr[0];
        h->arr[0] = temp;
        cnt1--;
        for (int i = 0; i <= cnt1; i++) {
            heapify(h, i);
        }
    }
}

void display(Heap *h) {
    printf("\n");
    for (int i = 0; i < h->m; i++) {
        printf("%d ", h->arr[i]);
    }
    printf("\n");
}

int main() {
    Heap h;
    heap_init(&h);
    insert(&h);
    display(&h);
    heapsort(&h);
    display(&h);
    return 0;
}
