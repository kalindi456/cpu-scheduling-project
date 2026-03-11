#include<stdio.h>
#include<stdlib.h>
#include "scheduler.h"
int main(){
	int n,choice; float tq;
printf("Enter Number of processes: ");
scanf("%d",&n);
struct Process p[n];
for(int i=0;i<n;i++){
	p[i].pid=i+1;
	printf("\nProcess P%d\n",i+1);
	printf("Arrival Time: ");
	scanf("%f",&p[i].at);
	printf("Burst Time: ");
        scanf("%f",&p[i].bt);
	p[i].finished=0;	

}	printf("Shortest Job First\n");
	sjfnp(p,n);
	print_process_table(p,n);
	reset_results(p,n);
	printf("\n");
	printf("\nPriority Preemptive\n");

	priority_p(p,n);
	print_process_table(p,n);
	reset_results(p,n);
return 0;






}
