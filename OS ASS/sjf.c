#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int completed;
};

void sjf(struct Process *processes, int n) {
    int currenttime = 0;
    int countComplete = 0;
    struct Process *currentproc = NULL;
    int min_burst;
    while (countComplete < n) {
        min_burst = INT32_MAX;
        for (int j = 0; j < n; j++) {
            if (processes[j].arrival <= currenttime && min_burst > processes[j].burst && !processes[j].completed) {
                min_burst = processes[j].burst;
                currentproc = &processes[j];
            }
        }

        if (currentproc == NULL) {
            currenttime++;
        } else {
            if (currenttime < currentproc->arrival)
                currenttime = currentproc->arrival;

            currenttime += currentproc->burst;
            currentproc->completion = currenttime;
            currentproc->turnaround = currenttime - currentproc->arrival;
            currentproc->waiting = currentproc->turnaround - currentproc->burst;
            currentproc->completed = 1;
            countComplete++;
        }
    }

    printf("Id\tAT\tBT\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        struct Process *p = &processes[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p->id, p->arrival, p->burst, p->completion, p->turnaround, p->waiting);
    }
}

int main() {
    int n;
    printf("Enter num of processes: ");
    scanf("%d", &n);

    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));

    int arr, burst;
    for (int i = 0; i < n; i++) {
        printf("Enter process %d arrival time: ", i);
        scanf("%d", &arr);
        printf("Enter process %d burst time: ", i);
        scanf("%d", &burst);

        processes[i].arrival = arr;
        processes[i].burst = burst;
        processes[i].id = i;
        processes[i].completed = 0;
    }

    sjf(processes, n);

    free(processes);
    return 0;
}
