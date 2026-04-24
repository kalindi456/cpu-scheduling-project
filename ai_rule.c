#include <stdio.h>
#include <string.h>
#include <math.h>

#include "ai_rule.h"
#include "gantt.h"

// Declare function from main.c
void generate_chart(char *algorithm);

// ------------------------------
// STORE TRAINING DATA
// ------------------------------
void store_training_data(struct Process p[], int n)
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

    FILE *fp2 = fopen("data/ai_choice.txt", "r");
    char algo[30];

    if(fp2 == NULL){
        printf("Error reading ai_choice.txt\n");
        fclose(fp);
        return;
    }

    fscanf(fp2, "%s", algo);
    fclose(fp2);

    fprintf(fp, "%d,%.2f,%.2f,%s\n", n, avg_bt, std_bt, algo);

    fclose(fp);
}

// ------------------------------
// SELECT BEST ALGORITHM
// ------------------------------
void select_best_algorithm()
{
    FILE *fp = fopen("data/performance.csv", "r");
    FILE *out = fopen("data/ai_choice.txt", "w");

    if (fp == NULL || out == NULL) {
        printf("Error opening files for AI\n");
        return;
    }

    char algo[30], best_algo[30];
    float wt, tat, best_wt;
    int cs, best_cs;

    // Skip header
    fscanf(fp, "%*[^\n]\n");

    // Read first row
    if (fscanf(fp, "%[^,],%f,%f,%d\n", best_algo, &best_wt, &tat, &best_cs) != 4) {
        fclose(fp);
        fclose(out);
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
                // Prefer non-preemptive algorithms
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
    fprintf(out, "%s", best_algo);

    fclose(fp);
    fclose(out);
}

// ------------------------------
// RUN BEST ALGORITHM
// ------------------------------
void run_best_algorithm(struct Process p[], int n, float tq)
{
    FILE *fp = fopen("data/ai_choice.txt", "r");

    if (fp == NULL) {
        printf("Error reading best algorithm\n");
        return;
    }

    char algo[30];
    fscanf(fp, "%s", algo);
    fclose(fp);

    printf("\n🚀 Running Best Algorithm: %s\n", algo);

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
