#include <stdio.h>
#include "emergency.h"

void sort_pending_by_priority(Emergency cases[], int case_count) {
    int i, j;
    Emergency temp;
    for (i = 0; i < case_count - 1; i++) {
        for (j = 0; j < case_count - i - 1; j++) {
            int swap = 0;
            if (cases[j].status == STATUS_PENDING && cases[j + 1].status == STATUS_PENDING && cases[j].priority < cases[j + 1].priority) swap = 1;
            if (cases[j].status != STATUS_PENDING && cases[j + 1].status == STATUS_PENDING) swap = 1;
            if (swap) { temp = cases[j]; cases[j] = cases[j + 1]; cases[j + 1] = temp; }
        }
    }
}

void view_pending_emergencies(Emergency cases[], int case_count) {
    int i, found = 0;
    sort_pending_by_priority(cases, case_count);
    printf("\n--- PENDING EMERGENCIES (highest priority first) ---\n");
    printf("%-8s %-10s %-9s %-10s %-10s\n", "Case ID", "Type", "Severity", "Distance", "Priority");
    for (i = 0; i < case_count; i++) {
        if (cases[i].status == STATUS_PENDING) {
            printf("%-8d %-10s %-9d %-10.2f %-10.2f\n", cases[i].id, emergency_type_name(cases[i].type), cases[i].severity, cases[i].distance, cases[i].priority);
            found = 1;
        }
    }
    if (!found) printf("No pending emergencies.\n");
}
