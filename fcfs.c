#include <stdio.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"

void fcfs(struct Process p[], int n)
{
float time = 0;
float total_wt = 0, total_tat = 0;


for(int i = 0; i < n - 1; i++)
{
    for(int j = i + 1; j < n; j++)
    {
        if(p[i].at > p[j].at)
        {
            struct Process temp = p[i];
            p[i] = p[j];
            p[j] = temp;
        }
    }
}

for(int i = 0; i < n; i++)
{
    if(time < p[i].at)
    {
        log_gantt_slice(0, time, p[i].at);  // log idle
        time = p[i].at;
    }

    float start = time;
    time += p[i].bt;
    float end = time;

    p[i].ct = end;
    p[i].tat = p[i].ct - p[i].at;
    p[i].wt = p[i].tat - p[i].bt;

    total_wt += p[i].wt;
    total_tat += p[i].tat;

    log_gantt_slice(p[i].pid, start, end);
}

float avg_wt = total_wt / n;
float avg_tat = total_tat / n;

save_performance("FCFS", avg_wt, avg_tat);

printf("\nFCFS Completed: Avg WT = %.2f, Avg TAT = %.2f\n", avg_wt, avg_tat);


}
