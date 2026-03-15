#include<stdio.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"

void sjfnp(struct Process p[], int n)
{
    int completed = 0;
    float current_time = 0;

    float total_wt = 0, total_tat = 0;

    while(completed < n)
    {
        int idx = -1;
        float min_bt = 9999;

        // Find shortest job among arrived processes
        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= current_time && p[i].finished == 0 && p[i].bt < min_bt)
            {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        // CPU idle
        if(idx == -1)
        {
            current_time++;
        }
        else
        {
            float start = current_time;
            float end = current_time + p[idx].bt;

            // Gantt chart logging
            log_gantt_slice(p[idx].pid, start, end);

            p[idx].ct = end;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;

            current_time = end;

            p[idx].finished = 1;
            completed++;
        }
    }

    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f", avg_tat);

    // Save performance to CSV
    save_performance("SJF-NP", avg_wt, avg_tat);
}
