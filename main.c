#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "scheduler.h"
#include "gantt.h"
#include "csv.h"
#include "ai_rule.h"

#define MAX_PROCESS 100

/* ---------------- UI ---------------- */

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
    printf("9. Change Process Details\n");
    printf("0. Exit\n");
    print_border();
    printf("Enter your choice: ");
}

/* ---------------- SAFE INPUT ---------------- */

int get_valid_integer(const char *prompt) {
    int value;
    char extra;

    while (1) {
        printf("%s", prompt);
        if (scanf("%d%c", &value, &extra) == 2 && extra == '\n') {
            return value;
        }
        printf("Invalid input! Enter integer only.\n");
        while (getchar() != '\n');
    }
}

float get_valid_float(const char *prompt) {
    float value;
    char extra;

    while (1) {
        printf("%s", prompt);
        if (scanf("%f%c", &value, &extra) == 2 && extra == '\n') {
            return value;
        }
        printf("Invalid input! Enter numeric value.\n");
        while (getchar() != '\n');
    }
}

/* ---------------- VALIDATORS ---------------- */

int negative_error(float time){
    return (time < 0);
}

int invalid_bt(float time){
    return (time <= 0);
}

/* ---------------- PRIORITY INPUT ---------------- */

int get_valid_priority(int used[], int pid) {
    int pr;

    while (1) {
        printf("Enter Priority for PID P%d: ", pid);

        pr = get_valid_integer("");

        if (pr > 0 && pr < 1000) {
            if (used[pr] == 0) return pr;
            else printf("Priority already used!\n");
        } else {
            printf("Priority must be 1–999.\n");
        }
    }
}

/* ---------------- GANTT ---------------- */

void generate_chart(const char *algorithm){
    char command[256];

    printf("\nGenerating Gantt Chart...\n");

    snprintf(command, sizeof(command),
        "python3 visualization/gantt_chart.py \"%s\" data/schedule_log.csv",
        algorithm);

    if(system(command) != 0){
        printf("Error generating chart!\n");
    }
}

/* ---------------- INIT PROCESSES ---------------- */

void input_processes(struct Process *p, int n){
    for(int i=0;i<n;i++){
        p[i].pid = i+1;

        print_border();
        printf("Process P%d\n", i+1);

        do{
            p[i].at = get_valid_float("Arrival Time: ");
        }while(negative_error(p[i].at));

        do{
            p[i].bt = get_valid_float("Burst Time: ");
        }while(invalid_bt(p[i].bt));

        p[i].finished = 0;
    }
}

/* ---------------- MAIN ---------------- */

int main(){

    int n, choice;
    float tq = 0;

    print_border();

    /* initial process count */
    while(1){
        n = get_valid_integer("Enter number of processes (1-100): ");
        if(n > 0 && n <= MAX_PROCESS) break;
        printf("Invalid range!\n");
    }

    /* dynamic allocation */
    struct Process *p = malloc(n * sizeof(struct Process));
    if(!p){
        printf("Memory allocation failed!\n");
        return 1;
    }

    /* init file */
    FILE *fp = fopen("data/schedule_log.csv","w");
    if(!fp){
        printf("File error!\n");
        free(p);
        return 1;
    }
    fprintf(fp,"pid,start,end\n");
    fclose(fp);

    input_processes(p, n);

    /* ---------------- LOOP ---------------- */

    while(1){

        print_menu();
        choice = get_valid_integer("");

        if(choice == 0){
            printf("\nExiting...\n");
            break;
        }

        switch(choice){

            case 1:
                reset_gantt_log();
                fcfs(p,n,0);
                print_process_table(p,n);
                generate_chart("FCFS");
                reset_results(p,n);
                break;

            case 2:
                reset_gantt_log();
                sjfnp(p,n,0);
                print_process_table(p,n);
                generate_chart("SJF");
                reset_results(p,n);
                break;

            case 3:
                reset_gantt_log();
                srtf(p,n,0);
                print_process_table(p,n);
                generate_chart("SRTF");
                reset_results(p,n);
                break;

            case 4:
            {
                int used[1000]={0};

                for(int i=0;i<n;i++){
                    int pr = get_valid_priority(used,i+1);
                    p[i].priority = pr;
                    used[pr]=1;
                }

                reset_gantt_log();
                priority_p(p,n,0);
                print_process_table_priority(p,n);
                generate_chart("Priority Preemptive");
                reset_results(p,n);
                break;
            }

            case 5:
            {
                int used[1000]={0};

                for(int i=0;i<n;i++){
                    int pr = get_valid_priority(used,i+1);
                    p[i].priority = pr;
                    used[pr]=1;
                }

                reset_gantt_log();
                priority_np(p,n,0);
                print_process_table_priority(p,n);
                generate_chart("Priority Non-Preemptive");
                reset_results(p,n);
                break;
            }

            case 6:
                do{
                    tq = get_valid_float("Enter Time Quantum: ");
                    if(tq < 1) printf("Must be >= 1\n");
                }while(tq < 1);

                reset_gantt_log();
                rr(p,n,tq,0);
                print_process_table(p,n);
                generate_chart("Round Robin");
                reset_results(p,n);
                break;
            case 7: {
    print_border();
    printf("Running ALL Scheduling Algorithms\n");
    print_border();

    reset_performance_log();

    /* -------- SJF -------- */
    printf("\n--- SJF (Non-Preemptive) ---\n");
    reset_gantt_log();
    sjfnp(p, n, 0);
    print_process_table(p, n);
    generate_chart("SJF Non-Preemptive");
    reset_results(p, n);

    /* -------- SRTF -------- */
    printf("\n--- SRTF ---\n");
    reset_gantt_log();
    srtf(p, n, 0);
    print_process_table(p, n);
    generate_chart("SRTF");
    reset_results(p, n);

    /* -------- PRIORITY INPUT (ONCE) -------- */
    int used[1000] = {0};
    for (int i = 0; i < n; i++) {
        int pr = get_valid_priority(used, i + 1);
        p[i].priority = pr;
        used[pr] = 1;
    }

    /* -------- PRIORITY PREEMPTIVE -------- */
    printf("\n--- Priority (Preemptive) ---\n");
    reset_gantt_log();
    priority_p(p, n, 0);
    print_process_table_priority(p, n);
    generate_chart("Priority Preemptive");
    reset_results(p, n);

    /* -------- PRIORITY NON-PREEMPTIVE -------- */
    printf("\n--- Priority (Non-Preemptive) ---\n");
    reset_gantt_log();
    priority_np(p, n, 0);
    print_process_table_priority(p, n);
    generate_chart("Priority Non-Preemptive");
    reset_results(p, n);

    /* -------- FCFS -------- */
    printf("\n--- FCFS ---\n");
    reset_gantt_log();
    fcfs(p, n, 0);
    print_process_table(p, n);
    generate_chart("FCFS");
    reset_results(p, n);

    /* -------- ROUND ROBIN -------- */
    float tq;
    do {
        tq = get_valid_float("Enter Time Quantum: ");
        if (tq < 1) printf("Time Quantum must be >= 1\n");
    } while (tq < 1);

    printf("\n--- Round Robin ---\n");
    reset_gantt_log();
    rr(p, n, tq, 0);
    print_process_table(p, n);
    generate_chart("Round Robin");
    reset_results(p, n);

    /* -------- PERFORMANCE GRAPH -------- */
    if (system("python3 visualization/performance_plot.py") != 0) {
        printf("Error generating performance plot!\n");
    }

    break;
}
            

            case 8:
            {
                printf("\nAI MODE\n");

                int used[1000]={0};

                tq = get_valid_float("Enter Time Quantum: ");

                for(int i=0;i<n;i++){
                    int pr = get_valid_priority(used,i+1);
                    p[i].priority = pr;
                    used[pr]=1;
                }

                run_all_algorithms_silent(p,n,tq);
                select_best_algorithm();

                FILE *fp = fopen("data/ai_choice.txt","r");
                if(!fp){
                    printf("AI file error!\n");
                    break;
                }

                char best[50];
                fscanf(fp,"%s",best);
                fclose(fp);

                printf("Selected Algorithm: %s\n",best);

                run_best_algorithm(p,n,tq);
                break;
            }
            case 9:   /* 🔥 FIXED VERSION */
            {
                int new_n;

                new_n = get_valid_integer("Enter new number of processes: ");

                if(new_n <= 0 || new_n > MAX_PROCESS){
                    printf("Invalid number!\n");
                    break;
                }

                struct Process *temp = realloc(p, new_n * sizeof(struct Process));
                if(!temp){
                    printf("Memory reallocation failed!\n");
                    break;
                }

                p = temp;
                n = new_n;

                input_processes(p,n);

                reset_results(p,n);
                reset_gantt_log();
                reset_performance_log();

                printf("Processes updated successfully!\n");
                break;
            }

            default:
                printf("Invalid choice!\n");
        }
    }

    free(p);
    return 0;
}

