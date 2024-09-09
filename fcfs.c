#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int cpu_time;
    int resource_time;
} Process;

void fcfsScheduling(Process* processes, int n){
    int current_time = 0;

    printf("\nCPU Execution Timeline:\n");
    for(int i = 0; i < n; i++){
        Process *p = &processes[i];

        // If the CPU is idle until the process arrives
        if(current_time < p->arrival_time){
            for(int t = current_time; t < p->arrival_time; t++){
                printf("_ "); // Represents idle time
            }
            current_time = p->arrival_time;
        }

        // CPU execution of the current process
        for(int t = 0; t < p->cpu_time; t++){
            printf("%d ", p->process_id); // Print process ID during CPU execution
            current_time++;
        }
    }
    printf("\n");

    printf("\nResource Execution Timeline:\n");
    for(int i = 0; i < n; i++){
        Process *p = &processes[i];

        // Resource execution of the current process
        for(int t = 0; t < p->resource_time; t++){
            printf("%d ", p->process_id); // Print process ID during resource execution
        }
    }
    printf("\n");
}

int main(){
    int n;
    
    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Dynamically allocate memory for 'n' processes
    Process *processes = (Process*)malloc(n * sizeof(Process));

    // Input process details
    for(int i = 0; i < n; i++){
        printf("Enter details for Process %d:\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &processes[i].process_id);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("CPU Time: ");
        scanf("%d", &processes[i].cpu_time);
        printf("Resource Time: ");
        scanf("%d", &processes[i].resource_time);
    }

    // Call FCFS scheduling function
    fcfsScheduling(processes, n);

    // Free dynamically allocated memory
    free(processes);

    return 0;
}
