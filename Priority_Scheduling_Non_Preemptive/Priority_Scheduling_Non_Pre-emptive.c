#include <stdio.h>
#include <stdbool.h>

struct Process {
    char id[10];
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool completed;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++) {
        // Automatically generate Process ID (P1, P2, etc.)
        sprintf(p[i].id, "P%d", i + 1);

        printf("\n--- Details for %s ---\n", p[i].id);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst_time);
        printf("Priority: ");
        scanf("%d", &p[i].priority);
        p[i].completed = false;
    }

    int current_time = 0;
    int completed_count = 0;

    // Execution logic
    while(completed_count < n) {
        int highest_priority = 9999;
        int selected_index = -1;

        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && !p[i].completed) {
                if(p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    selected_index = i;
                }
            }
        }

        if(selected_index == -1) {
            current_time++;
        } else {
            p[selected_index].completion_time = current_time + p[selected_index].burst_time;
            p[selected_index].turnaround_time = p[selected_index].completion_time - p[selected_index].arrival_time;
            p[selected_index].waiting_time = p[selected_index].turnaround_time - p[selected_index].burst_time;

            current_time = p[selected_index].completion_time;
            p[selected_index].completed = true;
            completed_count++;
        }
    }

    // Results table
    printf("\n%-10s %-10s %-10s %-10s %-10s %-10s\n", "ID", "Arrival", "Burst", "Priority", "Wait", "Turnaround");
    for(int i = 0; i < n; i++) {
        printf("%-10s %-10d %-10d %-10d %-10d %-10d\n", p[i].id, p[i].arrival_time,
               p[i].burst_time, p[i].priority, p[i].waiting_time, p[i].turnaround_time);
    }

    return 0;
}
