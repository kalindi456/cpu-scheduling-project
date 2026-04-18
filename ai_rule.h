#ifndef AI_RULE_H
#define AI_RULE_H
#include "scheduler.h"
void select_best_algorithm();
void run_best_algorithm(struct Process p[], int n, float tq);
void store_training_data(struct Process p[], int n);
#endif
