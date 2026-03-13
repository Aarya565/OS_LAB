#include <stdio.h>
#include <stdbool.h>

struct Process {
    char id[10];
    int at, bt, priority, ct, tat, wt, rt;
    bool completed;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        sprintf(p[i].id, "P%d", i + 1);
        printf("\nDetails for %s:\n", p[i].id);
        printf("Arrival Time: "); scanf("%d", &p[i].at);
        printf("Burst Time:   "); scanf("%d", &p[i].bt);
        printf("Priority:     "); scanf("%d", &p[i].priority);
        p[i].completed = false;
    }

    int current_time = 0, completed_count = 0;

    while (completed_count < n) {
        int highest_priority = 9999;
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !p[i].completed) {
                if (p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
        } else {
            p[idx].ct = current_time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].wt;

            current_time = p[idx].ct;
            p[idx].completed = true;
            completed_count++;
        }
    }

    printf("\n%-5s %-6s %-4s %-4s %-4s %-4s %-4s %-4s\n",
           "PID", "Prior", "AT", "BT", "CT", "TAT", "WT", "RT");

    float total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        printf("%-5s %-6d %-4d %-4d %-4d %-4d %-4d %-4d\n",
               p[i].id, p[i].priority, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    printf("\nAverage Turnaround time: %.6f", total_tat / n);
    printf("\nAverage Waiting time: %.6f\n", total_wt / n);

    return 0;
}
