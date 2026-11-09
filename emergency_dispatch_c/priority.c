
#include <stdio.h>
#include "emergency.h"

void sort_pending_by_priority(const Emergency cases[], int case_count,
                              Emergency sorted_cases[]) {
    int i, j;
    Emergency temp;

    for (i = 0; i < case_count; i++) {
        sorted_cases[i] = cases[i];
    }

    for (i = 0; i < case_count - 1; i++) {
        for (j = 0; j < case_count - i - 1; j++) {
            int swap = 0;

            if (sorted_cases[j].status == STATUS_PENDING &&
                sorted_cases[j + 1].status == STATUS_PENDING &&
                sorted_cases[j].priority < sorted_cases[j + 1].priority) {
                swap = 1;
            }

            if (sorted_cases[j].status != STATUS_PENDING &&
                sorted_cases[j + 1].status == STATUS_PENDING) {
                swap = 1;
            }

            if (swap) {
                temp = sorted_cases[j];
                sorted_cases[j] = sorted_cases[j + 1];
                sorted_cases[j + 1] = temp;
            }
        }
    }
}

void view_pending_emergencies(const Emergency cases[], int case_count) {
    int i, found = 0;
    Emergency sorted_cases[MAX_CASES];

    sort_pending_by_priority(cases, case_count, sorted_cases);

    printf("\n--- PENDING EMERGENCIES (highest priority first) ---\n");
    printf("%-8s %-10s %-9s %-10s %-10s\n",
           "Case ID", "Type", "Severity", "Distance", "Priority");

    for (i = 0; i < case_count; i++) {
        if (sorted_cases[i].status == STATUS_PENDING) {
            printf("%-8d %-10s %-9d %-10.2f %-10.2f\n",
                   sorted_cases[i].id,
                   emergency_type_name(sorted_cases[i].type),
                   sorted_cases[i].severity,
                   sorted_cases[i].distance,
                   sorted_cases[i].priority);
            found = 1;
        }
    }

    if (!found) {
        printf("No pending emergencies.\n");
    }
}
