#include <stdio.h>

typedef struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
} Process;

void non_preemptive_sjf(Process processes[], int n, float *avg_turnaround_time, float *avg_waiting_time) {
    // Sort processes based on burst time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int time = 0;
    float total_turnaround_time = 0, total_waiting_time = 0;

    for (int i = 0; i < n; i++) {
        time += processes[i].burst_time;
        processes[i].turnaround_time = time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }

    *avg_turnaround_time = total_turnaround_time / n;
    *avg_waiting_time = total_waiting_time / n;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    float avg_turnaround_time, avg_waiting_time;

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i + 1; // Assign PID sequentially
    }

    non_preemptive_sjf(processes, n, &avg_turnaround_time, &avg_waiting_time);

    printf("PID\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    printf("Non-Preemptive SJF Algorithm - Average Turnaround Time: %.2f, Average Waiting Time: %.2f\n", avg_turnaround_time, avg_waiting_time);

    return 0;
}
