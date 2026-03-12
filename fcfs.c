#include <stdio.h>
#include "scheduler.h"
#include  "gantt.h"
#include "csv.h"

void fcfs(struct Process p[], int n)
{
    float time = 0;
    float total_tat = 0;
    float total_wt = 0;

    for(int i = 0; i < n; i++)
    {
        if(time < p[i].at)
        {
            time = p[i].at;
        }

        time += p[i].bt;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;
}
