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

// First-Come, First-Served (FCFS)
void fcfsScheduling(Process* processes, int n, FILE *cpu_output, FILE *resource_output);
// Round Robin (RR)
void rrScheduling(Process* processes, int n, int quantum, FILE *cpu_output, FILE *resource_output);
//Shortest Job First (SJF)
void sjfScheduling(Process *processes, int n, FILE *cpu_output, FILE *resource_output);
// Shortest Remaining Time Next (SRTN)
void srtnScheduling(Process *processes, int n, FILE *cpu_output, FILE *resource_output);

// main
int main(int argc, char *argv[]){
    if(argc < 4){
        printf("Use: %s <input_file> <output_file> <algorithm> [quantum]\n", argv[0]);
        return 1;
    }
    
    char *input_file = argv[1];
    char *output_file = argv[3];
    int algorithm = atoi(argv[3]);
    int quantum = 2; // default for rr

    if(algorithm == 2 && argc == 5){
        quantum = atoi(argv[4]);
    }

    int n;
    Process *processes = readProcesses(input_file, &n);
    if(processes == NULL){
        printf("Error reading input file\n");
        return 1;
    }

    FILE *cpu_output = fopen(output_file, "w");
    FILE *resource_output = fopen("resource_output.txt", "w"); // divide file resource output

    switch(algorithm){
        case 1: 
            fcfsScheduling(processes, n, cpu_output, resource_output);
            break;
        case 2: 
            rrScheduling(processes, n, quantum, cpu_output, resource_output);
            break;    
        case 3: 
            sjfScheduling(processes, n, cpu_output, resource_output);
            break;
        case 4: 
            srtnScheduling(processes, n, cpu_output, resource_output);
            break;    
        default:
            printf("Invalid algorithm choice");
            return 1;
    }
    fclose(cpu_output);
    fclose(resource_output);
    free(processes);
    return 0;
}