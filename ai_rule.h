#ifndef AI_RULE_H
#define AI_RULE_H
#include "scheduler.h"
void select_best_algorithm(char *best_algo);
void run_best_algorithm(struct Process p[], int n, float tq);
void store_training_data(struct Process p[], int n,char *best_algo);
void run_all_algorithms_silent(struct Process p[], int n, float tq);
#endif
