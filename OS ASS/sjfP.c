#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int completion;
    int remaining;
    int waiting;
    int turnaround;
    bool completed;
};

void sjf_preemptive(struct Process *processes, int n) {
    int currentTime = 0;
    float AverageWT = 0;
    float AverageTAT = 0;
    int completedProcesses = 0;

    printf("Id\tAT\tBT\tCT\tTAT\tWT\n");
    while (completedProcesses < n) {
        int minBurst = INT_MAX;
        int selectedProcess = -1;

        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival <= currentTime && processes[i].burst < minBurst) {
                minBurst = processes[i].burst;
                selectedProcess = i;
            }
        }

        if (selectedProcess == -1) {
            currentTime++;
            continue;
        }

        struct Process *currentProcess = &processes[selectedProcess];
        currentProcess->remaining--;

        if (currentProcess->remaining == 0) {
            currentTime++;
            currentProcess->completion = currentTime;
            currentProcess->turnaround = currentProcess->completion - currentProcess->arrival;
            currentProcess->waiting = currentProcess->turnaround - currentProcess->burst;
            AverageWT += currentProcess->waiting;
            AverageTAT += currentProcess->turnaround;
            printf("%d\t%d\t%d\t%d\t%d\t%d\n", currentProcess->id, currentProcess->arrival, currentProcess->burst,
                   currentProcess->completion, currentProcess->turnaround, currentProcess->waiting);
            currentProcess->completed = true;
            completedProcesses++;
        } else {
            currentTime++;
        }
    }

    printf("\nAverage Waiting Time: %.2f\n", AverageWT / n);
    printf("Average Turnaround Time: %.2f\n", AverageTAT / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));

    printf("Enter arrival times and burst times for each process:\n");
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &processes[i].arrival);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &processes[i].burst);
        processes[i].remaining = processes[i].burst;
        processes[i].completed = false;
    }

    sjf_preemptive(processes, n);

    free(processes);
    return 0;
}
