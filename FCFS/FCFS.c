#include <stdio.h>

struct Process{
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main(){
    int n;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter total number of processes: ");
    scanf("%d",&n);

    struct Process p[n];

    for(int i=0; i<n; i++){
        p[i].id = i+1;
        printf("Process [%d]\n", p[i].id);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d",&p[i].burst_time);
    }

    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(p[j].arrival_time > p[j+1].arrival_time){
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int current_time = 0;

    for(int i=0; i<n; i++){
        if(current_time < p[i].arrival_time){
            current_time = p[i].arrival_time;
        }

        p[i].completion_time = current_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        current_time = p[i].completion_time;

        avg_tat += p[i].turnaround_time;
        avg_wt += p[i].waiting_time;
    }

    printf("\n%-8s %-12s %-12s %-15s %-15s %-12s\n",
           "Process", "Arrival Time", "Burst Time", "Completion Time", "Turnaround Time", "Waiting Time");

    for (int i = 0; i < n; i++) {
        printf("%-8d %-12d %-12d %-15d %-15d %-12d\n",
               p[i].id, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);

    return 0;
}
