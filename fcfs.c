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
        for(int t = 0; t < p->cpu_time; t++){
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

int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Dynamically allocate memory for processes
    Process* processes = (Process*) malloc(n * sizeof(Process));

    // Input process details
    printf("Enter the arrival time, CPU time, and resource time for each process:\n");
    for(int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;  // Assign process ID starting from 1
        printf("Process %d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("CPU time: ");
        scanf("%d", &processes[i].cpu_time);
        printf("Resource time: ");
        scanf("%d", &processes[i].resource_time);
    }

    // Show input
    printf("\nInput processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process ID: %d, Arrival time: %d, CPU time: %d, Resource time: %d\n",
               processes[i].process_id, processes[i].arrival_time, processes[i].cpu_time, processes[i].resource_time);
    }

    // Open output files
    FILE* cpu_output = fopen("cpu_output.txt", "w");
    FILE* resource_output = fopen("resource_output.txt", "w");

    // Execute FCFS scheduling
    fcfsScheduling(processes, n, cpu_output, resource_output);

    // Close files
    fclose(cpu_output);
    fclose(resource_output);

    // Free memory
    free(processes);

    return 0;
}
