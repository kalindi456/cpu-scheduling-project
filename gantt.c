#include <stdio.h>
#include "gantt.h"

void log_gantt_slice(int pid, float  start, float end)
{
    FILE *fp;

    /* Try opening file in append mode */
    fp = fopen("data/schedule_log.csv", "a");

    /* If file cannot be opened */
    if(fp == NULL)
    {
        printf("Error: Could not open schedule_log.csv\n");
        printf("Make sure the 'data' folder exists.\n");
        return;
    }

    /* Write gantt slice */
    fprintf(fp, "%d,%f,%f\n", pid, start, end);

    fclose(fp);
}
