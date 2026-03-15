#include<stdio.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"


void srtf(struct Process p[], int n)
{
    int completed = 0;
    float current_time = 0;

    float total_wt = 0, total_tat = 0;
    float remaining_bt[n];

    // For Gantt slice merging
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
        float min_bt = 9999;

        // Find process with shortest remaining time
        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= current_time &&
               remaining_bt[i] > 0 &&
               remaining_bt[i] < min_bt)
            {
                min_bt = remaining_bt[i];
                idx = i;
            }
        }

        // CPU Idle
        if(idx == -1)
        {
            current_time++;
            continue;
        }

        // Process switch detected
        if(last_pid != p[idx].pid)
        {
            if(last_pid != -1)
            {
                log_gantt_slice(last_pid, slice_start, current_time);
            }

            slice_start = current_time;
            last_pid = p[idx].pid;
        }

        // Execute process for 1 unit
        remaining_bt[idx]--;
        current_time++;

        // Process finished
        if(remaining_bt[idx] == 0)
        {
            log_gantt_slice(p[idx].pid, slice_start, current_time);

            last_pid = -1;

            p[idx].ct = current_time;
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

    // Save performance to CSV
    save_performance("SRTF", avg_wt, avg_tat);
}
