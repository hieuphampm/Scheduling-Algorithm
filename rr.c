#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Process structure
typedef struct {
    int process_id;
    int arrival_time;
    int cpu_time;
    int resource_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

// First-Come, First-Served (FCFS)
void fcfsScheduling(Process* processes, int n) {
    int current_time = 0;
    printf("\nCPU Execution (FCFS): ");
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time > current_time) {
            current_time = processes[i].arrival_time;
        }
        for (int t = 0; t < processes[i].cpu_time; t++) {
            printf("%d", processes[i].process_id);
            current_time++;
        }
        printf(" ");
        printf("\nResource Usage (FCFS): ");
        for (int t = 0; t < processes[i].resource_time; t++) {
            printf("%d", processes[i].process_id);
        }
        printf("\n");
    }
}

// Round Robin (RR)
void rrScheduling(Process* processes, int n, int quantum) {
    int current_time = 0;
    int remaining_processes = n;
    int queue[100];
    int front = 0, rear = 0;

    // Initialize queue with process IDs
    for (int i = 0; i < n; i++) {
        queue[rear++] = i;
    }

    printf("\nCPU Execution (Round Robin): ");
    while (remaining_processes > 0) {
        int idx = queue[front++];
        if (front == rear) {
            front = rear = 0;
        }
        if (processes[idx].remaining_time <= quantum) {
            for (int t = 0; t < processes[idx].remaining_time; t++) {
                printf("%d", processes[idx].process_id);
                current_time++;
            }
            processes[idx].remaining_time = 0;
            remaining_processes--;
        } else {
            for (int t = 0; t < quantum; t++) {
                printf("%d", processes[idx].process_id);
                current_time++;
            }
            processes[idx].remaining_time -= quantum;
            queue[rear++] = idx;
        }
        printf(" ");
    }
    printf("\nResource Usage (Round Robin):\n");
}

// Shortest Job First (SJF)
void sjfScheduling(Process *processes, int n) {
    int current_time = 0;
    int completed = 0;
    int is_completed[100] = {0};

    printf("\nCPU Execution (SJF): ");
    while (completed != n) {
        int idx = -1;
        int min_burst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && is_completed[i] == 0) {
                if (processes[i].cpu_time < min_burst) {
                    min_burst = processes[i].cpu_time;
                    idx = i;
                }
                if (processes[i].cpu_time == min_burst) {
                    if (processes[i].arrival_time < processes[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1) {
            for (int t = 0; t < processes[idx].cpu_time; t++) {
                printf("%d", processes[idx].process_id);
                current_time++;
            }
            printf(" ");
            printf("\nResource Usage (SJF): ");
            for (int t = 0; t < processes[idx].resource_time; t++) {
                printf("%d", processes[idx].process_id);
            }
            printf("\n");
            is_completed[idx] = 1;
            completed++;
        } else {
            printf("_ ");
            current_time++;
        }
    }
}

// Shortest Remaining Time Next (SRTN)
void srtnScheduling(Process *processes, int n) {
    int current_time = 0;
    int completed = 0;
    int is_completed[100] = {0};
    int remaining_time[100];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].cpu_time;
    }

    printf("\nCPU Execution (SRTN): ");
    while (completed != n) {
        int idx = -1;
        int min_remaining_time = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && is_completed[i] == 0) {
                if (remaining_time[i] < min_remaining_time) {
                    min_remaining_time = remaining_time[i];
                    idx = i;
                }
                if (remaining_time[i] == min_remaining_time) {
                    if (processes[i].arrival_time < processes[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1) {
            for (int t = 0; t < remaining_time[idx]; t++) {
                printf("%d", processes[idx].process_id);
                current_time++;
            }
            printf(" ");
            printf("\nResource Usage (SRTN): ");
            for (int t = 0; t < processes[idx].resource_time; t++) {
                printf("%d", processes[idx].process_id);
            }
            printf("\n");
            is_completed[idx] = 1;
            completed++;
        } else {
            printf("_ ");
            current_time++;
        }
    }
}

// Input function for processes
void inputProcesses(Process* processes, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for process %d:\n", i + 1);
        processes[i].process_id = i + 1;
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("CPU time: ");
        scanf("%d", &processes[i].cpu_time);
        printf("Resource time: ");
        scanf("%d", &processes[i].resource_time);
        processes[i].remaining_time = processes[i].cpu_time;
    }
}

// Main function
int main() {
    int n, quantum, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    inputProcesses(processes, n);

    printf("\nChoose the scheduling algorithm:\n");
    printf("1. FCFS\n");
    printf("2. Round Robin\n");
    printf("3. Shortest Job First (SJF)\n");
    printf("4. Shortest Remaining Time Next (SRTN)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfsScheduling(processes, n);
            break;
        case 2:
            printf("Enter the time quantum: ");
            scanf("%d", &quantum);
            rrScheduling(processes, n, quantum);
            break;
        case 3:
            sjfScheduling(processes, n);
            break;
        case 4:
            srtnScheduling(processes, n);
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
