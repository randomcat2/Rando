#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 3 // Number of frames in memory

// Function to find the index of the page that will not be used for the longest time
int findOptimalIndex(int pages[], int frames[], int n, int current) {
    int index = -1, farthest = current;
    for (int i = 0; i < FRAME_SIZE; ++i) {
        int j;
        for (j = current; j < n; ++j) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (index == -1) ? 0 : index;
}

// Function to implement Optimal page replacement algorithm
void optimal(int pages[], int n) {
    int frames[FRAME_SIZE], page_faults = 0;
    for (int i = 0; i < FRAME_SIZE; ++i)
        frames[i] = -1;

    for (int i = 0; i < n; ++i) {
        int j, hit = 0;
        for (j = 0; j < FRAME_SIZE; ++j) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (!hit) {
            int index = findOptimalIndex(pages, frames, n, i + 1);
            frames[index] = pages[i];
            ++page_faults;
        }
    }

    printf("Optimal Page Replacement Algorithm:\nTotal Page Faults: %d\n", page_faults);
}

// Function to implement FIFO page replacement algorithm
void fifo(int pages[], int n) {
    int frames[FRAME_SIZE], page_faults = 0, rear = 0;
    for (int i = 0; i < FRAME_SIZE; ++i)
        frames[i] = -1;

    for (int i = 0; i < n; ++i) {
        int j, hit = 0;
        for (j = 0; j < FRAME_SIZE; ++j) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (!hit) {
            frames[rear] = pages[i];
            rear = (rear + 1) % FRAME_SIZE;
            ++page_faults;
        }
    }

    printf("FIFO Page Replacement Algorithm:\nTotal Page Faults: %d\n", page_faults);
}

// Function to implement LRU page replacement algorithm
void lru(int pages[], int n) {
    int frames[FRAME_SIZE], page_faults = 0, recent = 0;
    for (int i = 0; i < FRAME_SIZE; ++i)
        frames[i] = -1;

    int counter[FRAME_SIZE];
    for (int i = 0; i < FRAME_SIZE; ++i)
        counter[i] = 0;

    for (int i = 0; i < n; ++i) {
        int j, hit = 0;
        for (j = 0; j < FRAME_SIZE; ++j) {
            if (frames[j] == pages[i]) {
                hit = 1;
                counter[j] = ++recent;
                break;
            }
        }
        if (!hit) {
            int index = 0, oldest = counter[0];
            for (int k = 1; k < FRAME_SIZE; ++k) {
                if (counter[k] < oldest) {
                    index = k;
                    oldest = counter[k];
                }
            }
            frames[index] = pages[i];
            counter[index] = ++recent;
            ++page_faults;
        }
    }

    printf("LRU Page Replacement Algorithm:\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);

    fifo(pages, n);
    lru(pages, n);
    optimal(pages, n);

    return 0;
}
