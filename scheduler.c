#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// process structure
typedef struct 
{
    int process_id;
    int arrival_time;
    int cpu_time;
    int resource_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

// function read process from the input file
Process* readProcesses(char *filename, int *n){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Error %s\n", filename);
        return NULL;
    };
    fscanf(file, "%d", n);
    Process *processes = (Process *) malloc((*n) * sizeof(Process));

    for (int i = 0; i < *n; i++){
        processes[i].process_id = i + 1; // start from 1
        fscanf(file, "%d %d %d", &processes[i].arrival_time, &processes[i].cpu_time, &processes[i].resource_time);
        processes[i].remaining_time = processes[i].cpu_time;
    }

    fclose(file);
    return processes;
};

// fcfs
void fcfsScheduling(Process* processes, int n, FILE *cpu_output, FILE *resource_output);
// rr
void rrScheduling(Process* processes, int n, int quantum, FILE *cpu_output, FILE *resource_output);