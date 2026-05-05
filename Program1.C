#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for P%d: ", i+1);
        scanf("%d", &arrival[i]);

        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &burst[i]);
    }

    int waiting[n], turnaround[n];
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (time < arrival[i]) {
            time = arrival[i];
        }

        waiting[i] = time - arrival[i];
        time += burst[i];
        turnaround[i] = waiting[i] + burst[i];
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

    printf("\nGantt Chart:\n|");

for (int i = 0; i < n; i++) {
    printf(" P%d |", i+1);
}

printf("\n0");

int currentTime = 0;

for (int i = 0; i < n; i++) {
    if (currentTime < arrival[i]) {
        currentTime = arrival[i];
    }
    currentTime += burst[i];
    printf("   %d", currentTime);
}

printf("\n");

    return 0;
}