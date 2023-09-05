#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

struct process {
    int arrival_time, burst_time, turnaround_time, waiting_time, completed_time, remaining_time;
};

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, time_quantum, remaining;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
    }

    remaining = n;
    
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);
    
    int current_time = 0;

    while (remaining) {
        int completed = 0;  // Flag to check if any process completed in the current time slice

        for (int i = 0; i < n; ++i) {
            if (p[i].remaining_time <= 0 || p[i].arrival_time > current_time) {
                continue;
            }

            int time_slice = min(p[i].remaining_time, time_quantum);
            
            current_time += time_slice;
            p[i].remaining_time -= time_slice;

            if (p[i].remaining_time == 0) {
                printf("Process %d completed at time %d\n", i + 1, current_time);
                remaining--;
                p[i].completed_time = current_time;
                completed = 1;
            }
        }

        // If no process completed in the current time slice, move time forward
        if (!completed) {
            current_time++;
        }
    }

    float avg_tt = 0, avg_wt = 0;
    
    printf("\nSi No:\tArrival time\tBurst Time\tWaiting time\tTurnAround Time\tCOMPLETED TIME\n");
    
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].completed_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time, p[i].completed_time);
        
        avg_tt += p[i].turnaround_time;
        avg_wt += p[i].waiting_time;
    }
    
    printf("\nAverage waiting time = %f\nAverage Turnaround Time = %f\n", avg_wt / n, avg_tt / n);
    
    return 0;
}
