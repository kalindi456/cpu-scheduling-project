#include<stdio.h>
#include<stdlib.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"
#include "ai_rule.h"
#define MAX_PROCESS 100
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
    printf("8. AI based selection\n");
    printf("0. Exit\n");
    print_border();
    printf("Enter your choice: ");
}

void generate_chart(char *algorithm){
	char command[200];
    printf("\nGenerating Gantt Chart...\n");
    snprintf(command,sizeof(command),"python3 visualization/gantt_chart.py \"%s\" data/schedule_log.csv",algorithm);
	system(command);
}
int get_valid_priority(int hm[], int pid) {
int pr;

while (1) {
printf("Enter Priority for PID P%d: ", pid);

if (scanf("%d", &pr) == 1) {

// 🔥 CLEAR BUFFER HERE (important)
while (getchar() != '\n');

if (pr > 0 && pr < 1000) {

if (hm[pr] == 0) {
return pr;
} else {
printf("Priority already used! Try again.\n");
}

} else {
printf("Priority must be between 1–999.\n");
}

} else {
printf("Invalid input! Enter a natural number (1–999).\n");

// clear invalid input
while (getchar() != '\n');
}}}
int negative_error(int time){
	if(time<0)
{return -1;} else{return 0;}}
int invalid_bt(int time){
if (time<=0)
{return -1;} else{return 0;}}
void run_all_algorithms_silent(struct Process p[], int n, float tq)
{

    // SJF
    reset_gantt_log();
    sjfnp(p,n,1);
    reset_results(p,n);

    // SRTF
    reset_gantt_log();
    srtf(p,n,1);
    reset_results(p,n);

    //priority
    reset_gantt_log();
    priority_p(p,n,1);
    reset_results(p,n);

    reset_gantt_log();
    priority_np(p,n,1);
    reset_results(p,n);

    // FCFS
    reset_gantt_log();
    fcfs(p,n,1);
    reset_results(p,n);

    // RR
    reset_gantt_log();
    rr(p,n,tq,1);
    reset_results(p,n);
}
int main(){
    int n,choice;
    float tq;
    char extra;
int result;
    print_border();
do
{
    printf("Enter number of processes (1-%d): ", MAX_PROCESS);
 	result=   scanf("%d%c",&n,&extra);

    if(n <= 0 || n > MAX_PROCESS)
        printf("Invalid number of processes.\n");
    if(result!=2|| extra!= '\n'){
	printf("Invalid number of processes.Only Integer allowed.\n");
	while(getchar()!='\n');
	n=-1;
        continue;
}
} while(n <= 0 || n > MAX_PROCESS);
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
	while(invalid_bt(p[i].bt)==-1){
        printf("Time cannot be negative or zero !Try Again!\n");
        printf("Burst Time: ");
        scanf("%f",&p[i].bt);
}

        p[i].finished=0;
    }

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
                fcfs(p,n,0);
                print_process_table(p,n);
                generate_chart("FCFS");
                reset_results(p,n);
                break;

            case 2:
                print_border();
                printf("Running Shortest Job First (SJF)\n");
                print_border();
		reset_gantt_log();

                sjfnp(p,n,0);
                print_process_table(p,n);
                generate_chart("SJF Non-Preemptive");
                reset_results(p,n);
                break;

            case 3:
                print_border();
                printf("Running Shortest Remaining Time First (SRTF)\n");
                print_border();
		reset_gantt_log();
                srtf(p,n,0);
                print_process_table(p,n);
                generate_chart("SJF Preemptive");
                reset_results(p,n);
                break;

            case 4:
		int hm[1000]={0};
	

    for(int i=0;i<n;i++){
        int pr=get_valid_priority(hm,i+1);       
        p[i].priority=pr;
        hm[pr]=1;
    }


                print_border();
                printf("Running Priority Scheduling (Preemptive)\n");
                print_border();
		reset_gantt_log();

                priority_p(p,n,0);
                print_process_table_priority(p,n);
                generate_chart("Priority Preemmptive");
                reset_results(p,n);
                break;

            case 5:
               int hm2[1000]={0};        

    for(int i=0;i<n;i++){
        int pr=get_valid_priority(hm2,i+1);       
        p[i].priority=pr;
        hm2[pr]=1;
    }

		 print_border();
                printf("Running Priority Scheduling (Non Preemptive)\n");
                print_border();
		reset_gantt_log();

                priority_np(p,n,0);
                print_process_table_priority(p,n);
                generate_chart("Priority Non-Preemptive");
                reset_results(p,n);
                break;

            case 6:
                print_border();
                printf("Round Robin Scheduling\n");
                print_border();
		do{
    		printf("Enter Time Quantum: ");
    		scanf("%f",&tq);

    		if(tq < 1){
       		 printf("Invalid Time Quantum!Time quantum should at least be 1.\n");

		}} while(tq < 1);
		reset_gantt_log();

                rr(p,n,tq,0);
                print_process_table(p,n);
                generate_chart("Round Robin");
                reset_results(p,n);
                break;

            case 7:
                print_border();
                printf("Running ALL Scheduling Algorithms\n");
                print_border();
		//to reset the  performance log
		reset_performance_log();
                printf("\n--- SJF ---\n");
		reset_gantt_log();

                sjfnp(p,n,0);
                print_process_table(p,n);
                generate_chart("SJF Non-Preemptive");
                reset_results(p,n);

                printf("\n--- SRTF ---\n");
		reset_gantt_log();

                srtf(p,n,0);
                print_process_table(p,n);
                generate_chart("SJF Preemptive");
                reset_results(p,n);
		
		printf("\n---Running priority based algorithms...--\n");
		int hma[1000]={0};

for(int i=0;i<n;i++){
        int pr=get_valid_priority(hma,i+1);       
        p[i].priority=pr;
        hma[pr]=1;
    }


                printf("\n--- Priority Preemptive ---\n");
		reset_gantt_log();

                priority_p(p,n,0);
                print_process_table_priority(p,n);
                generate_chart("Priority Preemptive");
                reset_results(p,n);

                printf("\n--- Priority Non Preemptive ---\n");
		reset_gantt_log();

                priority_np(p,n,0);
                print_process_table_priority(p,n);
                generate_chart("Priority Non-Preemptive");
                reset_results(p,n);

                printf("\n--- FCFS ---\n");
		reset_gantt_log();

                fcfs(p,n,0);
                print_process_table(p,n);
                generate_chart("FCFS");
                reset_results(p,n);

                printf("\n--- Round Robin ---\n");
                printf("Enter Time Quantum: ");
                scanf("%f",&tq);
		reset_gantt_log();

                rr(p,n,tq,0);
                print_process_table(p,n);
                generate_chart("Round Robin");
                reset_results(p,n);
		 // Generate comparison graph automatically
    		system("python3 performance_plot.py");
                break;
		case 8:
   		 printf("\n===== AI BASED SELECTION =====\n");

   		 reset_performance_log();
   		 reset_gantt_log();

   		 float tq;
   		 printf("Enter Time Quantum: ");
   		 scanf("%f", &tq);
		
   		 // ✅ TAKE PRIORITY INPUT ONCE
    		 int hm_ai[1000] = {0};   // now safe (new scope)
		for(int i = 0; i < n; i++) {
        	int pr = get_valid_priority(hm_ai, i+1);
        	p[i].priority = pr;
        	hm_ai[pr] = 1;
   		 }
   		 run_all_algorithms_silent(p, n, tq);  // 👈 silent version
   		 select_best_algorithm();
		 store_training_data(p, n);
		FILE *fp=fopen("data/ai_choice.txt","r");
		char best_algo[50];
		if(fp==NULL){printf("Error in opening file ai_choice\n");break;}
		fscanf(fp,"%s",best_algo);
		fclose(fp);
		printf("Selected Algorithm: %s\n",best_algo); 
   		 run_best_algorithm(p, n, tq);  // 👈 THIS prints final output

   		 break;
           default:
                printf("\nInvalid Choice! Try again.\n");
        }
    }

    return 0;
}
