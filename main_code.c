#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int arrival_time;
    int estimated_run_time;
    int waiting_time;
} Process;

int main() {
    int n, i, j, time = 0, total_waiting_time = 0;
    float average_waiting_time;
    Process *processes, temp;

    // Step 1: Read the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Step 2: Allocate memory for the processes array
    processes = (Process*) malloc(n * sizeof(Process));

    // Step 3: Read the arrival time and estimated run time for each process
    for (i = 0; i < n; i++) {
        printf("Enter the arrival time for process %d: ", i+1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the estimated run time for process %d: ", i+1);
        scanf("%d", &processes[i].estimated_run_time);
        processes[i].id = i+1;
        processes[i].waiting_time = 0;
    }

    // Step 4: Sort the processes by arrival time
    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Step 5: Run the processes using the priority scheduling algorithm
    int *gantt_chart = (int*) malloc(n * 100 * sizeof(int));
    int gantt_index = 0;
    int *remaining_time = (int*) malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        remaining_time[i] = processes[i].estimated_run_time;
    }
    int *completed = (int*) malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        completed[i] = 0;
    }
    int completed_count = 0;
    while (completed_count < n) {
        int highest_priority = -1;
        int highest_priority_index = -1;
        for (i = 0; i < n; i++) {
            if (!completed[i] && processes[i].arrival_time <= time) {
                int priority = 1 + processes[i].waiting_time / processes[i].estimated_run_time;
                if (highest_priority == -1 || priority < highest_priority) {
                    highest_priority = priority;
                    highest_priority_index = i;
                }
            }
        }
        if (highest_priority_index == -1) {
            time++;
            continue;
        }
        gantt_chart[gantt_index++] = highest_priority_index + 1;
        remaining_time[highest_priority_index]--;
        time++;
        for (i = 0; i < n; i++) {
            if (i != highest_priority_index && !completed[i] && processes[i].arrival_time <= time) {
                processes[i].waiting_time++;
            }
        }
        if (remaining_time[highest_priority_index] == 0) {
            completed[highest_priority_index] = 1;
            completed_count++;
            processes[highest_priority_index].waiting_time = time - processes[highest_priority_index].arrival_time - processes[highest_priority_index].estimated_run_time;
            total_waiting_time += processes[highest_priority_index].waiting_time;
        }
    }

    // Step 6: Print the gantt chart
    printf("\nGantt chart:\n");
    for (i = 0; i < gantt_index; i++) {
        printf("%d ", gantt_chart[i]);
    }
    printf("\n");

    // Step 7: Print the waiting time for each process
    printf("\nWaiting time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: %d\n", processes[i].id, processes[i].waiting_time);
    }

    // Step 8: Calculate and print the average waiting time
    average_waiting_time = (float) total_waiting_time / n;
    printf("\nAverage waiting time: %.2f\n", average_waiting_time);

    // Step 9: Free the memory allocated for the arrays
    free(processes);
    free(gantt_chart);
    free(remaining_time);
    free(completed);

    return 0;
}