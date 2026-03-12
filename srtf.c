#include<stdio.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"


void srtf(struct Process p[],int n){
	int completed=0;float current_time=0;
	float total_wt=0,total_tat=0;
	float remaining_bt[n];
	for(int i=0;i<n;i++){
	remaining_bt[i]=p[i].bt;
	p[i].finished=0;
}
	while(completed<n){
	int idx=-1;
	int min_bt=9999;
	for(int i=0;i<n;i++){
	if(p[i].at<=current_time && remaining_bt[i]>0 && remaining_bt[i])
		{min_bt=remaining_bt[i];
		idx=i;
		}
}
	if( idx==-1){
	current_time++;
}
	else{remaining_bt[idx]--;
	current_time++;}

	if(remaining_bt[idx]==0){
	p[idx].ct=current_time;
	p[idx].tat=p[idx].ct-p[idx].at;
	p[idx].wt=p[idx].tat-p[idx].bt;
	total_tat+=p[idx].tat;
	total_wt+=p[idx].wt;
// Gantt chart logging
log_gantt_slice(p[i].pid, start, end);
	p[idx].finished=1;
	completed++;
	
	printf("\nAverage Waiting Time=%.2f",total_wt/n);
        printf("\nAverage Turnaround Time=%.2f",total_tat/n);

// Save performance to CSV
save_performance("SRTF", avg_wt, avg_tat);
}
}

}




