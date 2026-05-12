#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
};

int main() {

    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (int i = 0; i < n; i++) {

        p[i].pid = i + 1;

        printf("Enter arrival time for P%d: ", p[i].pid);
        scanf("%d", &p[i].arrival);

        printf("Enter burst time for P%d: ", p[i].pid);
        scanf("%d", &p[i].burst);
    }

    // Sort by arrival time (FCFS)
    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (p[j].arrival > p[j + 1].arrival) {

                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int time = 0;

    // Calculate WT and TAT
    for (int i = 0; i < n; i++) {

        // CPU idle case
        if (time < p[i].arrival) {
            time = p[i].arrival;
        }

        p[i].waiting = time - p[i].arrival;

        time += p[i].burst;

        p[i].turnaround = p[i].waiting + p[i].burst;
    }
