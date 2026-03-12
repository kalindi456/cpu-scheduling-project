#include <stdio.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"

// FCFS Scheduling
void fcfs( struct Process p[], int n)
{
    float time = 0;
    float total_wt = 0, total_tat = 0;

    // Sort processes by Arrival Time
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(p[i].at > p[j].at)
            {
              struct  Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // FCFS Execution
    for(int i = 0; i < n; i++)
    {
        if(time < p[i].at)
            time = p[i].at;  // CPU idle if process not arrived

        float start = time;
        time += p[i].bt;
        float end = time;

        p[i].ct = end;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_wt += p[i].wt;
        total_tat += p[i].tat;

        // Log Gantt chart slice
        log_gantt_slice(p[i].pid, start, end);
    }

    // Calculate average metrics
    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;

    // Save performance
    save_performance("FCFS", avg_wt, avg_tat);

    printf("\nFCFS Completed: Avg WT = %.2f, Avg TAT = %.2f\n", avg_wt, avg_tat);
}
