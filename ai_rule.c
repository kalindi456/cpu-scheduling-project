#include <stdio.h>
#include <string.h>

#include "ai_rule.h"

#include "gantt.h"

// 🔴 Declare function from main.c
void generate_chart(char *algorithm);

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
        if (wt < best_wt || (wt == best_wt && cs < best_cs))
        {
            best_wt = wt;
            best_cs = cs;
            strcpy(best_algo, algo);
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

    // Reset gantt log before running
    reset_gantt_log();

    if (strcmp(algo, "FCFS") == 0) {
        fcfs(p, n);
        print_process_table(p, n);
        generate_chart("FCFS");
    }
    else if (strcmp(algo, "SJF") == 0) {
        sjfnp(p, n);
        print_process_table(p, n);
        generate_chart("SJF Non-Preemptive");
    }
    else if (strcmp(algo, "SRTF") == 0) {
        srtf(p, n);
        print_process_table(p, n);
        generate_chart("SJF Preemptive");
    }
    else if (strcmp(algo, "RR") == 0) {
        rr(p, n, tq);
        print_process_table(p, n);
        generate_chart("Round Robin");
    }
    else if (strcmp(algo, "Priority_NP") == 0) {
        priority_np(p, n);
        print_process_table_priority(p, n);
        generate_chart("Priority Non-Preemptive");
    }
    else if (strcmp(algo, "Priority_P") == 0) {
        priority_p(p, n);
        print_process_table_priority(p, n);
        generate_chart("Priority Preemptive");
    }
    else {
        printf("Unknown algorithm: %s\n", algo);
        return;
    }

    // Reset results for reuse
    reset_results(p, n);
}
