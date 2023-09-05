#include<stdio.h>
struct process{
    int id,at,bt,tt,wt,completed;
};

int main(){
    int n;
    printf("enter the total number of process:");
    scanf("%d",&n);
    struct process p[n];
    struct process temp[n];
    for (int i = 0; i < n; i++) {
        printf("\nEnter the arrival time of process :%d ", i + 1);
        scanf("%d", &p[i].at);
        printf("\nEnter the burst time of process :%d ", i + 1);
        scanf("%d", &p[i].bt);
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(p[j].bt>p[j+1].bt)
            {
                temp[j]=p[j];
                p[j]=p[j+1];
                p[j+1]=temp[j];
            }
        }
    }
        int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at)
            current_time = p[i].at;
        int completion = current_time + p[i].bt;
        p[i].tt = completion - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
        current_time = completion;
    }
    float avg_tt = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        printf("\nprocess: %d\tarrival time: %d\tburst time: %d\ttt: %d\twaiting time:%d", i + 1, p[i].at,
               p[i].bt, p[i].tt, p[i].wt);
        avg_tt += p[i].tt;
        avg_wt += p[i].wt;
    }
    avg_wt /= n;
    avg_tt /= n;

    printf("\nAverage waiting time =%f\nAverage TT = %f", avg_wt, avg_tt);


}