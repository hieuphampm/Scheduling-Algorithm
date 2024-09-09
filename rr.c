#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int cpu_time;
    int resource_time;
} Process;

void rrScheduling(Process* processes, int n, int quantum){
    int current_time = 0;
    int completed = 0;
    int *remaining_time = (int *)malloc(n * sizeof(int));
    int *resource_time = (int *)malloc(n * sizeof(int));
    int *arrival_time = (int *)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        remaining_time[i] = processes[i].cpu_time;
        resource_time[i] = processes[i].resource_time;
        arrival_time[i] = processes[i].arrival_time;
    }

    int queue[100]; // max 100 processes in the queue
    int front = 0, rear = 0;

    // enqueue processes that have arrived at time = 0
    for(int i = 0; i < n; i++){
        if(arrival_time[i] <= current_time){
            queue[rear++] = i;
        }
    }

    printf("\nCPU Execution Timeline (RR, quantum = %d):\n", quantum);

    while (completed < n){
        if(front == rear){
            // cpu idle
            printf("_ ");
            current_time++;
            // check for newly arrived process
            for(int i = 0; i < n; i++){
                if(arrival_time[i] == current_time){
                    queue[rear++] = i;
                }
            }
            continue;
        }

        int idx = queue[front++];
        int exec_time = (remaining_time[idx] < quantum) ? remaining_time[idx] : quantum;
        for(int t = 0; t < exec_time; t++){
            printf("%d ", processes[idx].process_id); // CPU execution
            current_time++;
            remaining_time[idx]--;

            // check new arrived processes
            for(int i = 0; i < n; i++){
                if(arrival_time[i] == current_time){
                    queue[rear++] = i;
                }
            }
        }

        if(remaining_time[idx] > 0){
            queue[rear++] = idx; // re-enqueue the process if not finished
        } else{
            completed++;
        }
    }
    printf("\n");

    printf("\nResource Execution Timeline (RR):\n");
    for(int i = 0; i < n; i++){
        // After CPU completion, execute resource time
        for(int t = 0; t < resource_time[i]; t++){
            printf("%d ", processes[i].process_id); // Resource execution
        }
    }
    printf("\n");

    // Free allocated memory
    free(remaining_time);
    free(resource_time);
    free(arrival_time);
}

int main(){
    int n, quantum;

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

    // Get time quantum for Round Robin
    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    // Call RR scheduling function
    rrScheduling(processes, n, quantum);

    // Free dynamically allocated memory
    free(processes);

    return 0;
}
