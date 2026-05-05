#include <stdio.h>
#include <limits.h>

int main() {
    int n;

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

    int complete = 0, time = 0;
    int waiting[n], turnaround[n];

    int order[1000], index = 0;

    while (complete != n) {
        int min = INT_MAX;
        int shortest = -1;

        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0 && remaining[i] < min) {
                min = remaining[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        // track Gantt
        order[index++] = shortest;

        remaining[shortest]--;
        time++;

        if (remaining[shortest] == 0) {
            complete++;

            int finish = time;
            waiting[shortest] = finish - burst[shortest] - arrival[shortest];
            if (waiting[shortest] < 0)
                waiting[shortest] = 0;

            turnaround[shortest] = finish - arrival[shortest];
        }
    }

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

    // Gantt Chart
    printf("\nGantt Chart:\n|");

    for (int i = 0; i < index; i++) {
        printf(" P%d |", order[i] + 1);
    }

    printf("\n0");

    for (int i = 1; i <= index; i++) {
        printf("   %d", i);
    }

    printf("\n");

    return 0;
}