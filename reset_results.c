#include<stdio.h>
#include "scheduler.h"
void reset_results(struct Process p[], int n)
{
    for(int i = 0; i < n; i++)
    {
        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
	p[i].finished=0;
    }
}
