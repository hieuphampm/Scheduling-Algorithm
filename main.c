#include <stdio.h>
#include <stdlib.h>

// Process structure
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

// Function to read processes from user input
Process* readProcessesFromUser(int *n){
    printf("Enter the number of processes: ");
    scanf("%d", n);

    Process *processes = (Process *) malloc((*n) * sizeof(Process));
    for (int i = 0; i < *n; i++){
        printf("Enter details for Process %d\n", i + 1);
        processes[i].process_id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("CPU Time: ");
        scanf("%d", &processes[i].cpu_time);
        printf("Resource Time: ");
        scanf("%d", &processes[i].resource_time);
        processes[i].remaining_time = processes[i].cpu_time;
    }

    return processes;
}

// First-Come, First-Served (FCFS)
void fcfsScheduling(Process* processes, int n){
    int current_time = 0;
    printf("\nCPU Execution Timeline (FCFS):\n");
    for(int i = 0; i < n; i++){
        Process *p = &processes[i];
        if(current_time < p->arrival_time){
            for(int t = current_time; t < p->arrival_time; t++){
                printf("_ ");  // CPU idle
            }
            current_time = p->arrival_time;
        }
        for(int t = 0; t < p->cpu_time; t++){
            printf("%d ", p->process_id);  // CPU execution
            current_time++;
        }
    }
    printf("\n");

    printf("\nResource Execution Timeline (FCFS):\n");
    for(int i = 0; i < n; i++){
        Process *p = &processes[i];
        for(int t = 0; t < p->resource_time; t++){
            printf("%d ", p->process_id);  // Resource execution
        }
    }
    printf("\n");
}

// Round Robin (RR)
void rrScheduling(Process* processes, int n, int quantum){
    int current_time = 0, done = 0;
    printf("\nCPU Execution Timeline (RR, quantum = %d):\n", quantum);

    while(done < n){
        done = 0;
        for(int i = 0; i < n; i++){
            if(processes[i].remaining_time > 0){
                if(processes[i].arrival_time <= current_time){
                    int exec_time = (processes[i].remaining_time < quantum) ? processes[i].remaining_time : quantum;
                    for(int t = 0; t < exec_time; t++){
                        printf("%d ", processes[i].process_id);  // CPU execution
                        current_time++;
                    }
                    processes[i].remaining_time -= exec_time;
                } else {
                    printf("_ ");  // CPU idle
                    current_time++;
                }
            } else {
                done++;
            }
        }
    }
    printf("\n");
}

// Shortest Job First (SJF) Scheduling
void sjfScheduling(Process *processes, int n){
    // Implement SJF logic here
    printf("SJF scheduling logic goes here\n");
}

// Shortest Remaining Time Next (SRTN) Scheduling
void srtnScheduling(Process *processes, int n){
    // Implement SRTN logic here
    printf("SRTN scheduling logic goes here\n");
}

// Main function
int main(){
    int n, algorithm, quantum = 2;

    // Read processes from user
    Process *processes = readProcessesFromUser(&n);

    // Select algorithm
    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. First-Come, First-Served (FCFS)\n");
    printf("2. Round Robin (RR)\n");
    printf("3. Shortest Job First (SJF)\n");
    printf("4. Shortest Remaining Time Next (SRTN)\n");
    printf("Enter choice: ");
    scanf("%d", &algorithm);

    // If Round Robin is chosen, ask for quantum
    if(algorithm == 2){
        printf("Enter time quantum for Round Robin: ");
        scanf("%d", &quantum);
    }

    // Perform the selected scheduling algorithm
    switch(algorithm){
        case 1:
            fcfsScheduling(processes, n);
            break;
        case 2:
            rrScheduling(processes, n, quantum);
            break;
        case 3:
            sjfScheduling(processes, n);
            break;
        case 4:
            srtnScheduling(processes, n);
            break;
        default:
            printf("Invalid algorithm choice.\n");
            return 1;
    }

    // Free allocated memory
    free(processes);

    return 0;
}
