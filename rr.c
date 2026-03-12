#include <stdio.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"

void rr(struct Process p[], int n, int tq)
{
    int time = 0;
    int completed = 0;
    int rem_bt[50];
    float total_wt = 0, total_tat = 0;

    for(int i = 0; i < n; i++)
    {
        rem_bt[i] = p[i].bt;
    }

    while(completed < n)
    {
        int done = 1;

        for(int i = 0; i < n; i++)
        {
            if(rem_bt[i] > 0)
            {
                done = 0;

                int start = time;

                if(rem_bt[i] > tq)
                {
                    time += tq;
                    rem_bt[i] -= tq;

                    log_gantt_slice(p[i].pid, start, time);
                }
                else
                {
                    time += rem_bt[i];
                    log_gantt_slice(p[i].pid, start, time);

                    p[i].ct = time;
                    rem_bt[i] = 0;
                    completed++;
                }
            }
        }

        if(done == 1)
            break;
    }

    for(int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;

    save_performance("RR", avg_wt, avg_tat);
}
