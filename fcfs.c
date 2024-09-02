#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int cpu_time;
    int resource_time;
} Process;

void fcfsScheduling(Process* processes, int n, FILE *cpu_output, FILE *resource_output){
    int current_time = 0;
    for(int i = 0; i < n; i++){
        Process *p = &processes[i];
        if(current_time < p->arrival_time){
            // cpu idle
            for(int t = current_time; t < p->arrival_time; t++){
                fprintf(cpu_output, "_ ");
            }
            current_time = p->arrival_time;
        }
        // cpu execution
        for(int t = 0; t< p->cpu_time; t++){
            fprintf(cpu_output, "%d ", p->process_id);
            current_time++;
        }
        // resource execution
        for(int t = 0; t < p->resource_time; t++){
            fprintf(resource_output, "%d ", p->process_id);
        }
    }
    fprintf(cpu_output, "\n");
    fprintf(resource_output, "\n");
}