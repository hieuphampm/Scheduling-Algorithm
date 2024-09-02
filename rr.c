#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int cpu_time;
    int resource_time;
} Process;

void rrScheduling(Process* processes, int n, int quantum, FILE *cpu_output, FILE *resource_output){
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

    while (completed < n){
        if(front == rear){
            // cpu idle
            fprintf(cpu_output,"_");
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
        for(int t = 0; t< exec_time; t++){
            fprintf(cpu_output, "%d", processes[idx].process_id);
            current_time++;
            remaining_time[idx]--;

            // check new arrived processes
            for(int i = 0; i < n; i++){
                if(arrival_time[i] == current_time){
                    queue[rear++] = 1;
                }
            }
        }

        if(remaining_time[idx] > 0){
            queue[rear++] = idx;
        } else{
            completed++;
            // process resource time after cpu completion
            for(int t = 0; t< resource_time[idx]; t++){
                fprintf(resource_output, "%d", processes[idx].process_id);
            }
        }
    }
    fprintf(cpu_output, "\n");
    fprintf(resource_output, "\n");
    free(remaining_time);
    free(resource_time);
    free(arrival_time);
}