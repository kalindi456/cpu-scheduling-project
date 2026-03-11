#include <stdio.h>
#include "scheduler.h"

void priority_p(struct Process p[], int n)
{
   float time = 0;
    int completed = 0;

    float remaining_bt[n];

   
    for(int i = 0; i < n; i++)
    {
        remaining_bt[i] = p[i].bt;
    }

    while(completed < n)
    {
        int idx = -1;
        int highest_priority = 9999;

       
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

        if(idx != -1)
        {
            /* ---------------- GANTT LOG ---------------- */

            remaining_bt[idx]--;
            time++;

            if(remaining_bt[idx] == 0)
            {
                completed++;

                p[idx].ct = time;

                p[idx].tat=
                    p[idx].ct - p[idx].at;

                p[idx].wt =
                    p[idx].tat - p[idx].bt;
            }
        }
        else
        {
            
            time++;
        }
    }

    /* ---------------- OUTPUT / CSV ---------------- */
 
}
