#include<stdio.h>
#include<stdlib.h>

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int priority;
};

void print_gantt_chart(struct process proc[], int n);

int main() {
    int n, i, j, time=0, total_waiting_time=0;
    float avg_waiting_time;
    struct process temp;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process proc[n];
    for(i=0; i<n; i++) {
        printf("Enter details for process %d:\n", i+1);
        printf("Arrival time: ");
        scanf("%d", &proc[i].arrival_time);
        printf("Burst time: ");
        scanf("%d", &proc[i].burst_time);
        proc[i].pid = i+1;
        proc[i].priority = 1 + proc[i].waiting_time/proc[i].burst_time;
    }
    for(i=0; i<n-1; i++) {
        for(j=0; j<n-i-1; j++) {
            if(proc[j].priority > proc[j+1].priority) {
                temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
    printf("Gantt chart:\n");
    print_gantt_chart(proc, n);
    printf("\nPID\tArrival Time\tBurst Time\tWaiting Time\n");
    for(i=0; i<n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, proc[i].waiting_time);
        total_waiting_time += proc[i].waiting_time;
    }
    avg_waiting_time = (float)total_waiting_time/n;
    printf("Average waiting time: %.2f\n", avg_waiting_time);
    return 0;
}

void print_gantt_chart(struct process proc[], int n) {
    int i, j, current_time=0, completion_time;
    printf(" ");
    for(i=0; i<n; i++) {
        for(j=0; j<proc[i].burst_time; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n|");
    for(i=0; i<n; i++) {
        completion_time = current_time + proc[i].burst_time;
        for(j=0; j<proc[i].burst_time-1; j++) {
            printf(" ");
        }
        printf("P%d", proc[i].pid);
        for(j=0; j<proc[i].burst_time-1; j++) {
            printf(" ");
        }
        printf("|");
        proc[i].waiting_time = current_time - proc[i].arrival_time;
        if(proc[i].waiting_time < 0) {
            proc[i].waiting_time = 0;
        }
        current_time = completion_time;
    }
    printf("\n ");
    for(i=0; i<n; i++) {
        for(j=0; j<proc[i].burst_time; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");
}
