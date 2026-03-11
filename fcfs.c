#include <stdio.h>
#include <stdlib.h>

struct Process {
    int  pid;
    float at;
    float bt;
    float tat;
    float wt;
    float ct;
};

int  main() {
   int  n, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];


    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d\n", p[i].pid);
        printf("Arrival Time: ");
        scanf("%f", &p[i].at);
        printf("Burst Time: ");
        scanf("%f", &p[i].bt);
    }


    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }


    p[0].ct = p[0].at + p[0].bt;
    for(i = 1; i < n; i++) {
        if(p[i-1].ct < p[i].at)
            p[i].ct = p[i].at + p[i].bt;
        else
            p[i].ct = p[i-1].ct + p[i].bt;
    }


    double  total_tat = 0, total_wt = 0;

    for(i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    double  avg_tat = total_tat / n;
    double  avg_wt = total_wt / n;


    FILE *fp = fopen("fcfs_output.csv", "w");
    if(fp != NULL) {
        fprintf(fp, "PID,Arrival Time,Burst Time,Completion Time,Turnaround Time,Waiting Time\n");
    }


    printf("| PID | AT | BT | CT | TAT | WT |\n");


    for(i = 0; i < n; i++) {
        printf("| %3d | %2f | %2f | %2f | %3f | %2f |\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        if(fp != NULL) {
            fprintf(fp, "%d,%f,%f,%f,%f,%f\n",
                    p[i].pid, p[i].at, p[i].bt,
                    p[i].ct, p[i].tat, p[i].wt);
        }
    }


    printf("\nAverage Turnaround Time = %lf\n", avg_tat);
    printf("Average Waiting Time    = %lf\n", avg_wt);

    if(fp != NULL) {
        fprintf(fp, "\nAverage Turnaround Time,%lf\n", avg_tat);
        fprintf(fp, "Average Waiting Time,%lf\n", avg_wt);
        fclose(fp);
    }


    return 0;
}
