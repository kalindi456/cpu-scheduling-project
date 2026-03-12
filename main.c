#include<stdio.h>
#include<stdlib.h>
#include "scheduler.h"
int main(){
	int n,choice; float tq;
printf("Enter Number of processes: ");
scanf("%d",&n);
struct Process p[n];
FILE *fp = fopen("data/schedule_log.csv","w");
fprintf(fp,"pid,start,end\n");
fclose(fp);

for(int i=0;i<n;i++){
	p[i].pid=i+1;
	printf("\nProcess P%d\n",i+1);

	printf("Arrival Time: ");
	scanf("%f",&p[i].at);
	printf("Burst Time: ");
        scanf("%f",&p[i].bt);
	p[i].finished=0;

      	

}	/*printf("First Come first Serve FCFS\n");
        fcfs(p,n);
        print_process_table(p,n);
        reset_results(p,n);
        printf("\n");*/



	printf("Shortest Job First\n");
	sjfnp(p,n);
	print_process_table(p,n);
	reset_results(p,n);
	printf("\n");
<<<<<<< HEAD
=======
	
	printf("Shortest Job First Preemptive SRTF\n");
        srtf(p,n);
        print_process_table(p,n);
        reset_results(p,n);
        printf("\n");

	printf("\nPriority Preemptive\n");
	int hm[1000];
	int pr;
	int i=0;
	while(i<n){
	printf("Enter Priority of PID:%d ",i+1);
	scanf("%d",&pr);
	if(hm[pr]==1){printf("Priority already assigned.Try again!");}
	
	else{p[i].priority=pr;
	hm[pr]=1;
	i++;}
}	/*Priority based*/
>>>>>>> 60b96bd (Changed format)
	printf("\nPriority Preemptive\n");

	priority_p(p,n);
	print_process_table(p,n);
	reset_results(p,n);

<<<<<<< HEAD
	printf("\n Priority Non Preemptive \n");
    	priority_np(p,n);
    	print_process_table(p,n);
    	reset_results(p,n);
    	printf("\n FCFS \n");
    	fcfs(p,n);
    	print_process_table(p,n);
        reset_results(p,n);
    	printf("\n Round Robin\n");
    	printf("Enter Time Quantum: ");
    	scanf("%f",&tq);
	rr(p,n,tq);
    	print_process_table(p,n);
    	reset_results(p,n);
=======
/*	printf("\nPriority Non- Preemptive\n");
	priority_np(p,n);
	print_process_table(p,n);
	reset_results(p,n);		
	
	printf("\nRound Robin\n");
	float tq;
	printf("Enter time quantum TQ: ");
	scanf("%f",&tq);
        rr(p,n,tq);
        print_process_table(p,n);
        reset_results(p,n); */    
>>>>>>> 60b96bd (Changed format)
return 0;






}
