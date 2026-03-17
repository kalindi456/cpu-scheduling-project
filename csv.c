#include <stdio.h>
#include "csv.h"



void save_performance(char algo[], float avg_wt, float avg_tat)
{
    FILE *fp;

    fp = fopen("data/performance.csv", "a");

    if(fp == NULL)
    {
        printf("Error opening performance.csv\n");
        return;
    }

    fprintf(fp, "%s,%.2f,%.2f\n", algo, avg_wt, avg_tat);

    fclose(fp);
}
void reset_performance_log()
{
    FILE *fp = fopen("data/performance.csv", "w");
    if(fp == NULL)
    {
        printf("Error opening performance.csv\n");
        return;
    }

    fprintf(fp,"algorithm,avg_wt,avg_tat\n");
    fclose(fp);
}
