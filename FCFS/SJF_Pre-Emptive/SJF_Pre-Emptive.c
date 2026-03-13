#include <stdio.h>
#include <limits.h>

int main() {
    int n, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rt[n];
    int ct[n], tat[n], wt[n];

    for(i = 0; i < n; i++) {
        pid[i] = i + 1;
    }

    for(i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i]; // Remaining time
    }

    int completed = 0, current_time = 0;
    int shortest, min_rt;
    int found = 0;

    while(completed != n) {
        shortest = -1;
        min_rt = INT_MAX;

        for(i = 0; i < n; i++) {
            if(at[i] <= current_time && rt[i] > 0 && rt[i] < min_rt) {
                min_rt = rt[i];
                shortest = i;
                found = 1;
            }
        }

        if(found == 0) {
            current_time++;
            continue;
        }

        rt[shortest]--;

        if(rt[shortest] == 0) {
            completed++;
            ct[shortest] = current_time + 1;

            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
        }

        current_time++;
        found = 0;
    }

    float total_wt = 0, total_tat = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);

        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
