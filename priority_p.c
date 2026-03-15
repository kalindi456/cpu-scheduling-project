#include <stdio.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"

void priority_p(struct Process p[], int n)
{
    float time = 0;
    int completed = 0;

    float total_wt = 0, total_tat = 0;

    float remaining_bt[n];

    int last_pid = -1;
    float slice_start = 0;

    for(int i = 0; i < n; i++)
    {
        remaining_bt[i] = p[i].bt;
        p[i].finished = 0;
    }

    while(completed < n)
    {
        int idx = -1;
        int highest_priority = 9999;

        // Find highest priority process (lower number = higher priority)
        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= time && remaining_bt[i] > 0)
            {
                if(p[i].priority < highest_priority)
                {
                    highest_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        // CPU idle
        if(idx == -1)
        {
            time++;
            continue;
        }

        // Process switch detection for Gantt chart
        if(last_pid != p[idx].pid)
        {
            if(last_pid != -1)
            {
                log_gantt_slice(last_pid, slice_start, time);
            }

            slice_start = time;
            last_pid = p[idx].pid;
        }

        // Execute process for 1 time unit
        remaining_bt[idx]--;
        time++;

        // Process finished
        if(remaining_bt[idx] == 0)
        {
            log_gantt_slice(p[idx].pid, slice_start, time);

            last_pid = -1;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_tat += p[idx].tat;
            total_wt += p[idx].wt;

            p[idx].finished = 1;
            completed++;
        }
    }

    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f", avg_tat);

    // Save results to CSV
    save_performance("Priority-P", avg_wt, avg_tat);
}
