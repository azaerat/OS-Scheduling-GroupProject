#include <stdio.h>

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n], remaining[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for P%d: ", i+1);
        scanf("%d", &arrival[i]);

        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &burst[i]);

        remaining[i] = burst[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int time = 0, done;
    int waiting[n], turnaround[n];

    // ✅ Gantt tracking
    int order[100], index = 0;

    do {
        done = 1;

        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                done = 0;

                if (remaining[i] > tq) {
                    order[index++] = i;   // track process
                    time += tq;
                    remaining[i] -= tq;
                } else {
                    order[index++] = i;   // track process
                    time += remaining[i];
                    waiting[i] = time - burst[i];
                    turnaround[i] = time - arrival[i];
                    remaining[i] = 0;
                }
            }
        }

    } while (!done);

    printf("\nP\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               i+1, arrival[i], burst[i], waiting[i], turnaround[i]);
    }

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        totalWT += waiting[i];
        totalTAT += turnaround[i];
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    // ✅ GANTT CHART
    printf("\nGantt Chart:\n|");

    for (int i = 0; i < index; i++) {
        printf(" P%d |", order[i] + 1);
    }

    printf("\n0");

    int currentTime = 0;
    int tempRemaining[n];

    for (int i = 0; i < n; i++) {
        tempRemaining[i] = burst[i];
    }

    for (int i = 0; i < index; i++) {
        int p = order[i];

        if (tempRemaining[p] > tq) {
            currentTime += tq;
            tempRemaining[p] -= tq;
        } else {
            currentTime += tempRemaining[p];
            tempRemaining[p] = 0;
        }

        printf("   %d", currentTime);
    }

    printf("\n");

    return 0;
}