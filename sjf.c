#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int cpu_time;
    int resource_time;
} Process;


void sjfScheduling(Process *processes, int n, FILE *cpu_output, FILE *resource_output){
    int current_time = 0;
    int completed = 0;
    int is_completed[100] = {0};

    while(completed != n){
        int idx = -1;
        int min_burst = 1e9;
        for(int i = 0; i < n; i++){
            if(processes[i].arrival_time <= current_time && is_completed[i] == 0){
                if(processes[i].cpu_time < min_burst){
                    min_burst = processes[i].cpu_time;
                    idx = i;
                }
                if(processes[i].cpu_time == min_burst){
                    if(processes[i].arrival_time < processes[idx].arrival_time){
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1){
            // execute process
            for(int t = 0; t < processes[idx].cpu_time; t++){
                fprintf(cpu_output, "%d", processes[idx].process_id);
                current_time++;
            }
            
            // resource executiton
        }
    }
}