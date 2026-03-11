#ifndef SHEDULER_H
#define SCHEDULER_H

struct Process{
	int pid;
	float at;
	float bt;
	float ct;
	float wt;
	float tat;
	float tq;
	int priority;
	int finished;

};
void srtf(struct Process p[],int n);
void sjfnp(struct Process p[],int n);
void priority_p(struct Process p[],int n);
void reset_results(struct Process p[],int n);
void print_process_table(struct Process p[],int n);
#endif
