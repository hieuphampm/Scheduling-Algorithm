#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int cpu_time;
    int resource_time;
} Process;

void srtnScheduling(Process *processes, int n){
    int current_time = 0;
    int completed = 0;
    int is_completed[100] = {0};
    int remaining_time[100];

    for(int i = 0; i < n; i++){
        remaining_time[i] = processes[i].cpu_time;
    }

    printf("\nCPU Execution Timeline (SRTN):\n");

    while(completed != n){
        int idx = -1;
        int min_remaining = 1e9;  // A large value to represent infinity

        for(int i = 0; i < n; i++){
            if(processes[i].arrival_time <= current_time && is_completed[i] == 0){
                if(remaining_time[i] < min_remaining && remaining_time[i] > 0){
                    min_remaining = remaining_time[i];
                    idx = i;
                }

                if(remaining_time[i] == min_remaining){
                    if(processes[i].arrival_time < processes[idx].arrival_time){
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1){
            // Execute process for one time unit
            printf("%d ", processes[idx].process_id);  // CPU execution
            remaining_time[idx]--;
            current_time++;

            if(remaining_time[idx] == 0){
                is_completed[idx] = 1;
                completed++;

                // Resource execution
                printf("\nResource Execution for Process %d:\n", processes[idx].process_id);
                for(int t = 0; t < processes[idx].resource_time; t++){
                    printf("%d ", processes[idx].process_id);  // Resource execution
                }
                printf("\n");
            }
        } else {
            // CPU idle
            printf("_ ");
            current_time++;
        }
    }

    printf("\n");
}

int main(){
    int n;

    // Get number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Dynamically allocate memory for 'n' processes
    Process *processes = (Process*)malloc(n * sizeof(Process));

    // Input process details
    for(int i = 0; i < n; i++){
        printf("Enter details for Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("CPU Time: ");
        scanf("%d", &processes[i].cpu_time);
        printf("Resource Time: ");
        scanf("%d", &processes[i].resource_time);
        processes[i].process_id = i + 1;
    }

    // Call SRTN scheduling function
    srtnScheduling(processes, n);

    // Free dynamically allocated memory
    free(processes);

    return 0;
}
