#ifndef GANTT_H
#define GANTT_H

void log_gantt_slice(int pid, float  start, float end);
int calculate_context_switch();
void reset_gantt_log();
#endif
