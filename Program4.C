#include <stdio.h>
#include <limits.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n], priority[n], remaining[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for P%d: ", i+1);
        scanf("%d", &arrival[i]);

        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &burst[i]);

        printf("Enter priority for P%d (1-99): ", i+1);
        scanf("%d", &priority[i]);

        remaining[i] = burst[i];
    }

    int complete = 0, time = 0;
    int waiting[n], turnaround[n];

    int order[1000], index = 0;

    while (complete != n) {
        int highestPriority = INT_MAX;
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0 && priority[i] < highestPriority) {
                highestPriority = priority[i];
                selected = i;
            }
        }

        if (selected == -1) {
            time++;
            continue;
        }

        // track execution
        order[index++] = selected;

        remaining[selected]--;
        time++;

        if (remaining[selected] == 0) {
            complete++;

            int finish = time;
            waiting[selected] = finish - burst[selected] - arrival[selected];
            if (waiting[selected] < 0)
                waiting[selected] = 0;

            turnaround[selected] = finish - arrival[selected];
        }
    }

    printf("\nP\tAT\tBT\tPR\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, arrival[i], burst[i], priority[i], waiting[i], turnaround[i]);
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