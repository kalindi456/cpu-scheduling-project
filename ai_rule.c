#include <stdio.h>
#include <string.h>
#include <math.h>

#include "ai_rule.h"
#include "gantt.h"

// Declare function from main.c
void generate_chart(char *algorithm);

// ------------------------------
// STORE TRAINING DATA (FIXED)
// ------------------------------
void store_training_data(struct Process p[], int n, char *best_algo)
{
    FILE *fp = fopen("data/training_data.csv", "a");

    if(fp == NULL){
        printf("Error opening training_data.csv\n");
        return;
    }

    float sum = 0;
    for(int i = 0; i < n; i++){
        sum += p[i].bt;
    }

    float avg_bt = sum / n;

    float variance = 0;
    for(int i = 0; i < n; i++){
        variance += (p[i].bt - avg_bt) * (p[i].bt - avg_bt);
    }
    variance /= n;

    float std_bt = sqrt(variance);

    // ✅ Store TRUE best algorithm (NOT from ai_choice.txt)
    fprintf(fp, "%d,%.2f,%.2f,%s\n", n, avg_bt, std_bt, best_algo);

    fclose(fp);
}

// ------------------------------
// SELECT BEST ALGORITHM (UNCHANGED)
// ------------------------------
void select_best_algorithm(char *best_algo)
{
    FILE *fp = fopen("data/performance.csv", "r");

    if (fp == NULL) {
        printf("Error opening performance.csv\n");
        return;
    }

    char algo[30];
    float wt, tat, best_wt;
    int cs, best_cs;

    // Skip header
    fscanf(fp, "%*[^\n]\n");

    // Read first row
    if (fscanf(fp, "%[^,],%f,%f,%d\n", best_algo, &best_wt, &tat, &best_cs) != 4) {
        fclose(fp);
        return;
    }

    // Compare remaining rows
    while (fscanf(fp, "%[^,],%f,%f,%d\n", algo, &wt, &tat, &cs) == 4)
    {
        if (wt < best_wt)
        {
            best_wt = wt;
            best_cs = cs;
            strcpy(best_algo, algo);
        }
        else if (fabs(wt - best_wt) < 0.01)
        {
            if (cs < best_cs)
            {
                best_cs = cs;
                strcpy(best_algo, algo);
            }
            else if (cs == best_cs)
            {
                if (strcmp(algo, "SJF-NP") == 0 ||
                    strcmp(algo, "FCFS") == 0 ||
                    strcmp(algo, "Priority_NP") == 0)
                {
                    strcpy(best_algo, algo);
                }
            }
        }
    }

    printf("\n🔥 Best Algorithm: %s\n", best_algo);

    fclose(fp);
}

// ------------------------------
// RUN BEST ALGORITHM (HYBRID)
// ------------------------------
void run_best_algorithm(struct Process p[], int n, float tq,int pa,int tqa)
{
    FILE *fp = fopen("data/ai_choice.txt", "r");

    if (fp == NULL) {
        printf("Error reading ai_choice.txt\n");
        return;
    }

    char algo[30];
    float confidence;

    fscanf(fp, "%s %f", algo, &confidence);
    fclose(fp);

    printf("\nML Suggestion: %s (Confidence: %.2f)\n", algo, confidence);

    // ---------------- HYBRID LOGIC ----------------
    if (confidence <= 0.7) {
        printf("⚠️ Low confidence → Running all algorithms to find best\n");

        run_all_algorithms_silent(p, n, tq,pa,tqa);

        char best_algo[30];
        select_best_algorithm(best_algo);

        strcpy(algo, best_algo);

        printf("🔥 Fallback Selected: %s\n", algo);
    } 
    else {
        printf("✅ Using ML Decision\n");
    }

    // ---------------- EXECUTION ----------------
    reset_gantt_log();

    if (strcmp(algo, "FCFS") == 0) {
        fcfs(p, n,0);
        print_process_table(p, n);
        generate_chart("FCFS");
    }
    else if (strcmp(algo, "SJF-NP") == 0) {
        sjfnp(p, n,0);
        print_process_table(p, n);
        generate_chart("SJF Non-Preemptive");
    }
    else if (strcmp(algo, "SRTF") == 0) {
        srtf(p, n,0);
        print_process_table(p, n);
        generate_chart("SJF Preemptive");
    }
    else if (strcmp(algo, "RR") == 0) {
        rr(p, n, tq,0);
        print_process_table(p, n);
        generate_chart("Round Robin");
    }
    else if (strcmp(algo, "Priority_NP") == 0) {
        priority_np(p, n,0);
        print_process_table_priority(p, n);
        generate_chart("Priority Non-Preemptive");
    }
    else if (strcmp(algo, "Priority_P") == 0) {
        priority_p(p, n,0);
        print_process_table_priority(p, n);
        generate_chart("Priority Preemptive");
    }
    else {
        printf("Unknown algorithm: %s\n", algo);
        return;
    }

    reset_results(p, n);
}

// ------------------------------
// RUN ALL (UNCHANGED)
// ------------------------------
void run_all_algorithms_silent(struct Process p[], int n, float tq,int pa,int tqa)
{
    reset_gantt_log();
    sjfnp(p,n,1);
    reset_results(p,n);

    reset_gantt_log();
    srtf(p,n,1);
    reset_results(p,n);
    if(pa==1){
    reset_gantt_log();
    priority_p(p,n,1);
    reset_results(p,n);

    reset_gantt_log();
    priority_np(p,n,1);
    reset_results(p,n);
    }
    
    reset_gantt_log();
    fcfs(p,n,1);
    reset_results(p,n);

    if(tqa==1){

    reset_gantt_log();
    rr(p,n,tq,1);
    reset_results(p,n);}
}
