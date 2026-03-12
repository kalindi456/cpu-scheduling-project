#include <stdio.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"

void priority_np( struct Process p[], int n)
{
    int completed = 0;
    float time = 0;
    int visited[100] = {0}; // track completed processes

    float total_tat = 0;
    float total_wt = 0;

    while(completed < n)
    {
        int idx = -1;

        // Find the next process with highest priority (lowest number) that has arrived
        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= time && visited[i] == 0)
            {
                if(idx == -1 || p[i].priority < p[idx].priority)
                {
                    idx = i;
                }
            }
        }

        if(idx == -1)
        {
            time += 1; // CPU idle
            continue;
        }

        float start = time;         // Start time of this process
        float end = time + p[idx].bt; // End time after full burst

        time = end; // move current time

        // Completion, TAT, WT
        p[idx].ct = end;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        // Log Gantt slice
        log_gantt_slice(p[idx].pid, start, end);

        total_tat += p[idx].tat;
        total_wt += p[idx].wt;

        visited[idx] = 1;
        completed++;
    }

    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;

    // Save performance to CSV
    save_performance("Priority_NP", avg_wt, avg_tat);

    printf("\nPriority Non-Preemptive Completed: Avg WT = %.2f, Avg TAT = %.2f\n", avg_wt, avg_tat);
}
