#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    char processname[10];
    int arrivaltime;
    int bursttime;
}Process;

void sjf(Process processes[], int n)
{
    int completiontime[n];
    int turnaroundtime[n];
    int waitingtime[n];
    
    completiontime[0]=processes[0].bursttime;
    for(int i=1; i<n; i++)
    {
        if(completiontime[i-1]>=processes[i].arrivaltime)
        {
            completiontime[i]=completiontime[i-1]+processes[i].bursttime;
        }
        else 
        {
            completiontime[i]=processes[i].arrivaltime+processes[i].bursttime;
        }
    }
    for(int i=0; i<n; i++)
    {
        turnaroundtime[i]=completiontime[i]-processes[i].arrivaltime;
        waitingtime[i]=turnaroundtime[i]-processes[i].bursttime;
    }
    printf("ProcessName\tArrivalTime\tBurstTime\tCompletionTime\tTurnaroundTime\tWaitingTime\n");
    for(int i=0; i<n; i++)
    {
        printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",processes[i].processname,processes[i].arrivaltime,processes[i].bursttime,completiontime[i],turnaroundtime[i],waitingtime[i]);
    }
    float avg_turnaroundtime=0;
    float avg_waitingtime=0;
    for(int i=0; i<n; i++)
    {
        avg_turnaroundtime+=turnaroundtime[i];
        avg_waitingtime+=waitingtime[i];
    }
    avg_turnaroundtime=avg_turnaroundtime/n;
    avg_waitingtime=avg_waitingtime/n;
    printf("Average Turnaround Time : %.2f",avg_turnaroundtime);
    printf("Average Waiting Time : %.2f",avg_waitingtime);
    
}
int main()
{
    int n; 
    printf("Enter the number of processes : ");
    scanf("%d",&n);
    Process processes[n];
    for(int i=0; i<n; i++)
    {
        printf("Process Name : ");
        scanf("%s",processes[i].processname);
        printf("Arrival Time : ");
        scanf("%d",&processes[i].arrivaltime);
        printf("Burst Time : ");
        scanf("%d",&processes[i].bursttime);
    }
    //sorting on the basis of burst time in sjf
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(processes[j].bursttime>processes[j+1].bursttime)
            {
                Process temp=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp;
            }
        }
    }
    sjf(processes,n);
    return 0;
}