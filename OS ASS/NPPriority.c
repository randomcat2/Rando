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
//bubble sort for priority 
void non_preemptive_priority(Process processes[], int n, float *avg_turnaround_time, float *avg_waiting_time) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
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

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].pid = i + 1; 
    }

    non_preemptive_priority(processes, n, &avg_turnaround_time, &avg_waiting_time);

    printf("PID\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority, processes[i].turnaround_time, processes[i].waiting_time);
    }

    printf("Non-Preemptive Priority Algorithm - Average Turnaround Time: %.2f, Average Waiting Time: %.2f\n", avg_turnaround_time, avg_waiting_time);

    return 0;
}
