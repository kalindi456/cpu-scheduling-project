#include <stdio.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"

void rr(struct Process p[], int n, float  tq)
{
float time = 0;
int completed = 0;
float rem_bt[50];
float total_wt = 0, total_tat = 0;


int idle_start = -1;
for(int i = 0; i < n; i++)
{
    rem_bt[i] = p[i].bt;
}

while(completed < n)
{
    int executed = 0;

    for(int i = 0; i < n; i++)
    {
        if(rem_bt[i] > 0 && p[i].at <= time)
        {
            executed = 1;

            if(idle_start != -1)
            {
                log_gantt_slice(0, idle_start, time);
                idle_start = -1;
            }

            float start = time;

            if(rem_bt[i] > tq)
            {
                time += tq;
                rem_bt[i] -= tq;
            }
            else
            {
                time += rem_bt[i];
                rem_bt[i] = 0;
                p[i].ct = time;
                completed++;
            }

            log_gantt_slice(p[i].pid, start, time);
        }
    }

    if(!executed)
    {
        if(idle_start == -1)
            idle_start = time;

        time++;
    }
}

if(idle_start != -1)
{
    log_gantt_slice(0, idle_start, time);
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

printf("\nAverage Waiting Time = %.2f", avg_wt);
printf("\nAverage Turnaround Time = %.2f", avg_tat);
int cs = calculate_context_switch();
save_performance("RR", avg_wt, avg_tat, cs);


}
