#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

struct process {
    int arrival_time, burst_time, turnaround_time, waiting_time, completed_time, priority;
};

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, remaining;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        printf("Enter the priority of process %d: ", i + 1);
        scanf("%d", &p[i].priority);
    }

    // Sort the processes by priority (non-preemptive)
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].priority < p[j+1].priority) {
                // Swap processes based on priority
                struct process temp = p[j+1];
                p[j+1] = p[j];
                p[j] = temp;
            }
        }
    }

    remaining = n;
    
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time > current_time) {
            current_time = p[i].arrival_time;
        }

        p[i].waiting_time = current_time - p[i].arrival_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
        p[i].completed_time = current_time + p[i].burst_time;

        current_time = p[i].completed_time;
    }

    float avg_tt = 0, avg_wt = 0;
    
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, p[i].arrival_time, p[i].burst_time, p[i].priority, p[i].waiting_time, p[i].turnaround_time, p[i].completed_time);
        
        avg_tt += p[i].turnaround_time;
        avg_wt += p[i].waiting_time;
    }
    
    printf("\nAverage Waiting Time = %.2f\nAverage Turnaround Time = %.2f\n", avg_wt / n, avg_tt / n);
    
    return 0;
}
