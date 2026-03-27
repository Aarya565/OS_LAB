#include <stdio.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int execution_time;
    int period;
    int remaining_time;
    int next_arrival;
} Task;

int main() {
    int n, time, sim_time;

    Task tasks[MAX_TASKS];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Task %d execution time: ", i + 1);
        scanf("%d", &tasks[i].execution_time);
        printf("Task %d period: ", i + 1);
        scanf("%d", &tasks[i].period);

        tasks[i].remaining_time = 0;
        tasks[i].next_arrival = 0;
    }

    printf("Enter simulation time: ");
    scanf("%d", &sim_time);

    printf("\nTime\tRunning Task\n");

    for (time = 0; time < sim_time; time++) {

        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_arrival += tasks[i].period;
            }
        }

        int selected = -1;
        int min_period = 999999;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                if (tasks[i].period < min_period) {
                    min_period = tasks[i].period;
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            printf("%d\tT%d\n", time, tasks[selected].id);
            tasks[selected].remaining_time--;
        } else {
            printf("%d\tIdle\n", time);
        }
    }

    return 0;
}
