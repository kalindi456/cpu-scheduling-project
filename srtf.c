#include <stdio.h>
#include <float.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"

void srtf(struct Process p[], int n)
{
int completed = 0;
float current_time = 0;


float total_wt = 0, total_tat = 0;
float remaining_bt[n];

int last_idx = -1;      // last running process index
float slice_start = 0;

for(int i = 0; i < n; i++)
{
    remaining_bt[i] = p[i].bt;
    p[i].finished = 0;
}

while(completed < n)
{
    int idx = -1;
    float min_bt = FLT_MAX;

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

    // CPU Idle case
    if(idx == -1)
    {
        if(last_idx != -2)
        {
            if(last_idx >= 0)
                log_gantt_slice(p[last_idx].pid, slice_start, current_time);

            slice_start = current_time;
            last_idx = -2; // idle indicator
        }

        current_time++;
        continue;
    }

    // Process switch
    if(last_idx != idx)
    {
        if(last_idx >= 0)
            log_gantt_slice(p[last_idx].pid, slice_start, current_time);
        else if(last_idx == -2)
            log_gantt_slice(0, slice_start, current_time); // idle logged as PID 0

        slice_start = current_time;
        last_idx = idx;
    }

    // Execute process for 1 time unit
    remaining_bt[idx]--;
    current_time++;

    // Process finished
    if(remaining_bt[idx] == 0)
    {
        log_gantt_slice(p[idx].pid, slice_start, current_time);

        p[idx].ct = current_time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        total_tat += p[idx].tat;
        total_wt += p[idx].wt;

        p[idx].finished = 1;
        completed++;

        last_idx = -1;
    }
}

float avg_wt = total_wt / n;
float avg_tat = total_tat / n;

printf("\nAverage Waiting Time = %.2f", avg_wt);
printf("\nAverage Turnaround Time = %.2f", avg_tat);

save_performance("SRTF", avg_wt, avg_tat);


}
