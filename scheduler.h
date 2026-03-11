#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct
{
    int pid;
    float at;
    float bt;
    float ct;
    float wt;
    float tat;
    float rt;

} Process;

void fcfs(Process p[], int n);
void rr(Process p[], int n, float tq);

#endif
