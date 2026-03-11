#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d\n", p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;
    int visited[n];

    for(int i = 0; i < n; i++)
        visited[i] = 0;

   for(int i = 0; i < n; i++) {
        if(p[i].at == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while(completed < n) {

        if(front == rear) {
            time++;
            for(int i = 0; i < n; i++) {
                if(p[i].at <= time && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int i = queue[front++];


        if(p[i].rt > tq) {
            time += tq;
            p[i].rt -= tq;
        } else {
            time += p[i].rt;
            p[i].rt = 0;
            p[i].ct = time;
            completed++;
        }

       for(int j = 0; j < n; j++) {
            if(p[j].at <= time && !visited[j]) {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

      if(p[i].rt > 0)
            queue[rear++] = i;
    }

    float total_tat = 0, total_wt = 0;

    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;

    FILE *fp = fopen("rr_output.csv", "w");
    if(fp != NULL)
        fprintf(fp, "PID,Arrival Time,Burst Time,Completion Time,Turnaround Time,Waiting Time\n");

   printf("| PID | AT | BT | CT | TAT | WT |\n");

    for(int i = 0; i < n; i++) {
        printf("| %3d | %2d | %2d | %3d | %3d | %3d |\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        if(fp != NULL)
            fprintf(fp, "%d,%d,%d,%d,%d,%d\n",
                    p[i].pid, p[i].at, p[i].bt,
                    p[i].ct, p[i].tat, p[i].wt);
    }


    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time    = %.2f\n", avg_wt);

    if(fp != NULL) {
        fprintf(fp, "\nAverage Turnaround Time,%.2f\n", avg_tat);
        fprintf(fp, "Average Waiting Time,%.2f\n", avg_wt);
        fclose(fp);
    }

   return 0;
}
