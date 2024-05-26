#include <stdio.h>

typedef struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int priority;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
} Process;

void round_robin(Process processes[], int n, int tq, float *avg_turnaround_time, float *avg_waiting_time) {
    int time = 0;
    int completed = 0;
    float total_turnaround_time = 0, total_waiting_time = 0;

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > tq) {
                    time += tq;
                    processes[i].remaining_time -= tq;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    completed++;
                    processes[i].turnaround_time = time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    total_turnaround_time += processes[i].turnaround_time;
                    total_waiting_time += processes[i].waiting_time;
                }
            }
        }
    }

    *avg_turnaround_time = total_turnaround_time / n;
    *avg_waiting_time = total_waiting_time / n;
}

int main() {
    int n, tq;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    float avg_turnaround_time, avg_waiting_time;

    // Input arrival time, burst time, and priority for each process
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time
        processes[i].pid = i + 1; // Assign PID sequentially
    }

    printf("Enter the time quantum (TQ): ");
    scanf("%d", &tq);

    round_robin(processes, n, tq, &avg_turnaround_time, &avg_waiting_time);

    printf("PID\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority, processes[i].turnaround_time, processes[i].waiting_time);
    }

    printf("Round Robin Algorithm (TQ=%d) - Average Turnaround Time: %.2f, Average Waiting Time: %.2f\n", tq, avg_turnaround_time, avg_waiting_time);

    return 0;
}
