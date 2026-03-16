#include <stdio.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"

void priority_np(struct Process p[], int n)
{
int completed = 0;
float time = 0;
int visited[100] = {0};


float total_tat = 0;
float total_wt = 0;

float idle_start = -1;

while(completed < n)
{
    int idx = -1;

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
        if(idle_start == -1)
            idle_start = time;

        time += 1;
        continue;
    }

    if(idle_start != -1)
    {
        log_gantt_slice(0, idle_start, time);
        idle_start = -1;
    }

    float start = time;
    float end = time + p[idx].bt;

    log_gantt_slice(p[idx].pid, start, end);

    time = end;

    p[idx].ct = end;
    p[idx].tat = p[idx].ct - p[idx].at;
    p[idx].wt = p[idx].tat - p[idx].bt;

    total_tat += p[idx].tat;
    total_wt += p[idx].wt;

    visited[idx] = 1;
    completed++;
}

if(idle_start != -1)
{
    log_gantt_slice(0, idle_start, time);
}

float avg_tat = total_tat / n;
float avg_wt = total_wt / n;

save_performance("Priority_NP", avg_wt, avg_tat);

printf("\nPriority Non-Preemptive Completed: Avg WT = %.2f, Avg TAT = %.2f\n", avg_wt, avg_tat);


}
