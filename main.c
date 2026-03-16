#include<stdio.h>
#include<stdlib.h>
#include "scheduler.h"
#include "gantt.h"
void print_border(){
    printf("\n====================================================\n");
}


void print_menu(){
    print_border();
    printf("              CPU SCHEDULING SIMULATOR\n");
    print_border();
    printf("1. First Come First Serve (FCFS)\n");
    printf("2. Shortest Job First (SJF - Non Preemptive)\n");
    printf("3. Shortest Remaining Time First (SRTF)\n");
    printf("4. Priority Scheduling (Preemptive)\n");
    printf("5. Priority Scheduling (Non Preemptive)\n");
    printf("6. Round Robin\n");
    printf("7. Run All Algorithms\n");
    printf("0. Exit\n");
    print_border();
    printf("Enter your choice: ");
}

void generate_chart(){
    printf("\nGenerating Gantt Chart...\n");
    system("python3 visualization/gantt_chart.py data/schedule_log.csv");
}
int negative_error(int time){
	if(time<0)
{return -1;} else{return 0;}}
int main(){

    int n,choice;
    float tq;

    print_border();
    printf("Enter Number of Processes: ");
    scanf("%d",&n);

    struct Process p[n];

    FILE *fp = fopen("data/schedule_log.csv","w");
    fprintf(fp,"pid,start,end\n");
    fclose(fp);

    for(int i=0;i<n;i++){
        p[i].pid=i+1;

        print_border();
        printf("Process P%d\n",i+1);

        printf("Arrival Time: ");
        scanf("%f",&p[i].at);
	while(negative_error(p[i].at)==-1){
	printf("Time cannot be negative!Try Again!\n");
	printf("Arrival Time: ");
        scanf("%f",&p[i].at);
}
        printf("Burst Time: ");
        scanf("%f",&p[i].bt);
	while(negative_error(p[i].bt)==-1){
        printf("Time cannot be negative!Try Again!\n");
        printf("Burst Time: ");
        scanf("%f",&p[i].bt);
}

        p[i].finished=0;
    }

   /* int hm[1000]={0};

    for(int i=0;i<n;i++){
        int pr;
        printf("Enter Priority for PID P%d: ",i+1);
        scanf("%d",&pr);

        while(hm[pr]==1){
            printf("Priority already used! Enter again: ");
            scanf("%d",&pr);
        }

        p[i].priority=pr;
        hm[pr]=1;
    }*/

    while(1){

        print_menu();
        scanf("%d",&choice);

        if(choice==0){
            printf("\nExiting Scheduler...\n");
            break;
        }

        switch(choice){

            case 1:
                print_border();
                printf("Running FCFS Scheduling\n");
                print_border();
		reset_gantt_log();
                fcfs(p,n);
                print_process_table(p,n);
                generate_chart();
                reset_results(p,n);
                break;

            case 2:
                print_border();
                printf("Running Shortest Job First (SJF)\n");
                print_border();
		reset_gantt_log();

                sjfnp(p,n);
                print_process_table(p,n);
                generate_chart();
                reset_results(p,n);
                break;

            case 3:
                print_border();
                printf("Running Shortest Remaining Time First (SRTF)\n");
                print_border();
		reset_gantt_log();
                srtf(p,n);
                print_process_table(p,n);
                generate_chart();
                reset_results(p,n);
                break;

            case 4:
		int hm[1000]={0};

    for(int i=0;i<n;i++){
        int pr;
        printf("Enter Priority for PID P%d: ",i+1);
        scanf("%d",&pr);

        while(hm[pr]==1){
            printf("Priority already used! Enter again: ");
            scanf("%d",&pr);
        }

        p[i].priority=pr;
        hm[pr]=1;
    }


                print_border();
                printf("Running Priority Scheduling (Preemptive)\n");
                print_border();
		reset_gantt_log();

                priority_p(p,n);
                print_process_table_priority(p,n);
                generate_chart();
                reset_results(p,n);
                break;

            case 5:
               int hm2[1000]={0};

    for(int i=0;i<n;i++){
        int pr;
        printf("Enter Priority for PID P%d: ",i+1);
        scanf("%d",&pr);

        while(hm2[pr]==1){
            printf("Priority already used! Enter again: ");
            scanf("%d",&pr);
        }

        p[i].priority=pr;
        hm2[pr]=1;
    }


		 print_border();
                printf("Running Priority Scheduling (Non Preemptive)\n");
                print_border();
		reset_gantt_log();

                priority_np(p,n);
                print_process_table_priority(p,n);
                generate_chart();
                reset_results(p,n);
                break;

            case 6:
                print_border();
                printf("Round Robin Scheduling\n");
                print_border();

                printf("Enter Time Quantum: ");
                scanf("%f",&tq);
		reset_gantt_log();

                rr(p,n,tq);
                print_process_table(p,n);
                generate_chart();
                reset_results(p,n);
                break;

            case 7:
                print_border();
                printf("Running ALL Scheduling Algorithms\n");
                print_border();

                printf("\n--- SJF ---\n");
		reset_gantt_log();

                sjfnp(p,n);
                print_process_table(p,n);
                generate_chart();
                reset_results(p,n);

                printf("\n--- SRTF ---\n");
		reset_gantt_log();

                srtf(p,n);
                print_process_table(p,n);
                generate_chart();
                reset_results(p,n);

                printf("\n--- Priority Preemptive ---\n");
		reset_gantt_log();

                priority_p(p,n);
                print_process_table_priority(p,n);
                generate_chart();
                reset_results(p,n);

                printf("\n--- Priority Non Preemptive ---\n");
		reset_gantt_log();

                priority_np(p,n);
                print_process_table_priority(p,n);
                generate_chart();
                reset_results(p,n);

                printf("\n--- FCFS ---\n");
		reset_gantt_log();

                fcfs(p,n);
                print_process_table(p,n);
                generate_chart();
                reset_results(p,n);

                printf("\n--- Round Robin ---\n");
                printf("Enter Time Quantum: ");
                scanf("%f",&tq);
		reset_gantt_log();

                rr(p,n,tq);
                print_process_table(p,n);
                generate_chart();
                reset_results(p,n);

                break;

            default:
                printf("\nInvalid Choice! Try again.\n");
        }
    }

    return 0;
}
