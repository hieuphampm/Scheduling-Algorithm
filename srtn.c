#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int cpu_time;
    int resource_time;
} Process;

void srtnScheduling(Process *processes, int n, FILE *cpu_output, FILE *resource_output){
    int current_time = 0;
    int completed = 0;
    int is_completed[100] = {0};
    int remaining_time[100];
    for(int i = 0; i < n; i++){
        remaining_time[i] = processes[i].cpu_time;
    }

    while(completed != n){
        int idx = -1;
        int min_remaining = 1e9;
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
            // execute process for one time unit
            fprintf(cpu_output, "%d", processes[idx].process_id);
            remaining_time[idx]--;
            current_time++;
            if(remaining_time[idx] == 0){
                is_completed[idx] = 1;
                completed++;
                // resource execution
                for(int t = 0; t < processes[idx].resource_time; t++){
                    fprintf(resource_output, "%d", processes[idx].process_id);
                }
            }
        } else{
            // cpu idle
            fprintf(cpu_output, "_");
            current_time;
        }
    }
    fprintf(cpu_output, "\n");
    fprintf(resource_output, "\n");
}