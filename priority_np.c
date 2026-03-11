#include <stdio.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"
#include "io.h"

void priority_np(struct process p[], int n)
{
    int completed = 0;
    float time = 0;
    int visited[100] = {0};

    float total_tat = 0;
    float total_wt = 0;

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
            time++;
            continue;
        }

        time += p[idx].bt;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        total_tat += p[idx].tat;
        total_wt += p[idx].wt;

        visited[idx] = 1;
        completed++;
    }

    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;
}
