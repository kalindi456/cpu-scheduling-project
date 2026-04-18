#include <stdio.h>
#include "gantt.h"
#include <string.h>
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
int calculate_context_switch() {
    FILE *fp = fopen("data/schedule_log.csv", "r");
    if (!fp) return 0;

    int prev_pid, curr_pid;
    float start, end;
    int count = 0;

    // Skip header line
    fscanf(fp, "%*[^\n]\n");

    // Read first row
    if (fscanf(fp, "%d,%f,%f\n", &prev_pid, &start, &end) != 3) {
        fclose(fp);
        return 0;
    }

    // Read remaining rows
    while (fscanf(fp, "%d,%f,%f\n", &curr_pid, &start, &end) == 3) {
        if (prev_pid != curr_pid) {
            count++;
        }
        prev_pid = curr_pid;
    }

    fclose(fp);
    return count;
}
void reset_gantt_log(){FILE *fp=fopen("data/schedule_log.csv","w");
		if(fp!=NULL){
		fprintf(fp,"pid,start,end\n");
fclose(fp);}}
