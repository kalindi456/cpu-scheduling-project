#include <stdio.h>
#include "gantt.h"

void log_gantt_slice(int pid, int start, int end)
{
    FILE *fp;

    fp = fopen("data/schedule_log.csv", "a");

    if(fp == NULL)
    {
        printf("Error opening Gantt log file\n");
        return;
    }

    fprintf(fp, "%d,%d,%d\n", pid, start, end);

    fclose(fp);
}
