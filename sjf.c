#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int cpu_time;
    int resource_time;
} Process;

void sjfScheduling(Process *processes, int n) {
    int current_time = 0;
    int completed = 0;
    int is_completed[100] = {0};

    printf("CPU Output: ");
    while (completed != n) {
        int idx = -1;
        int min_burst = 1e9;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && is_completed[i] == 0) {
                if (processes[i].cpu_time < min_burst) {
                    min_burst = processes[i].cpu_time;
                    idx = i;
                }
                if (processes[i].cpu_time == min_burst) {
                    if (processes[i].arrival_time < processes[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1) {
            // Execute process
            for (int t = 0; t < processes[idx].cpu_time; t++) {
                printf("%d", processes[idx].process_id);
                current_time++;
            }

            // Resource execution
            printf(" ");
            for (int t = 0; t < processes[idx].resource_time; t++) {
                printf("%d", processes[idx].process_id);
            }
            is_completed[idx] = 1;
            completed++;
        } else {
            // CPU idle
            printf("_ ");
            current_time++;
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = (Process *)malloc(n * sizeof(Process));

    printf("Enter process details (process_id arrival_time cpu_time resource_time):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &processes[i].process_id, &processes[i].arrival_time, 
              &processes[i].cpu_time, &processes[i].resource_time);
    }

    sjfScheduling(processes, n);

    free(processes);
    return 0;
}
