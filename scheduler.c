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
} Process;

// function read process from the input file
int readProcesses(char* filename, Process** process){
    FILE* file = fopen(filename, "r");
    if(!file){
        perror("Error");
        return -1;
    };
    
    int num_process;
    fscanf(file, "%d", &num_process);
    *process = (Process*) malloc(num_process * sizeof(Process));

    for (int i = 0; i < num_process; i++){
        fscanf(file, "%d %d %d", &((*process)[i].arrival_time), &((*process)[i].cpu_time), &((*process)[i].resource_time));
        (*process)[i].process_id = i + 1; // start from1
    }

    fclose(file);
    return num_process;
};

// function to simulate fcfs scheduling and create output file
void fcfsScheduling(Process* processes, int num_process, char* output_filename){
    FILE* file = fopen(output_filename, "w");
    if(!file){
        perror("Error");
        return;
    };

    // output the gantt chart for cpu scheduling
    for(int i = 0; i < num_process; i++){
        for(int j = 0; j < processes[i].cpu_time; j++){
            fprintf(file, "%d", processes[i].process_id);
        }
    }
    fprintf(file, "\n");

    fclose(file);
}

int main(int argc, char* argv[]){
    if(argc < 4){
        printf("Usage: %s <input file> <output file> <algorithm>\n", argv[0]);
        return 1;
    }

    char* input_filename = argv[1];
    char* output_filename = argv[2];
    int algorithm = atoi(argv[3]);

    Process* processes = NULL;
    int num_processes = readProcesses(input_filename, &processes);

    if(num_processes < 0){
        return 1;
    }

    // only fcfs
    if (algorithm == 1){
        fcfsScheduling(processes, num_processes, output_filename);
    } else{
        printf("Algorithm not implemented.\n");
        free(processes);
        return 1;
    }
    free(processes);
    return 0;
}