#include <stdio.h>
#include "scheduler.h"

void print_process_table(struct Process p[], int n)
{
    printf("\n============================================================\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    printf("------------------------------------------------------------\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%.2f\t%.2f\t%d\t%.2f\t%.2f\t%.2f\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].priority,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("============================================================\n\n");
}
