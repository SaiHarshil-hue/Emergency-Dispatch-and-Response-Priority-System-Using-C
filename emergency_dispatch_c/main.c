#include <stdio.h>
#include "emergency.h"

static void print_menu(void) {
    printf("\n==============================================\n");
    printf("     EMERGENCY DISPATCH & RESPONSE SYSTEM\n");
    printf("==============================================\n");
    printf("1. Register Emergency\n");
    printf("2. View Pending Emergencies\n");
    printf("3. Dispatch Emergency Unit\n");
    printf("4. View Available Units\n");
    printf("5. Mark Case as Resolved\n");
    printf("6. View Emergency History\n");
    printf("7. Exit\n");
}

void view_history(const Emergency cases[], int case_count) {
    int i;
    if (case_count == 0) { printf("No emergency records yet.\n"); return; }
    printf("\n--- EMERGENCY HISTORY ---\n");
    printf("%-8s %-10s %-8s %-10s %-10s %-12s %-10s\n", "Case ID", "Type", "Severity", "Distance", "Priority", "Status", "Unit ID");
    for (i = 0; i < case_count; i++) {
        printf("%-8d %-10s %-8d %-10.2f %-10.2f %-12s ", cases[i].id, emergency_type_name(cases[i].type), cases[i].severity, cases[i].distance, cases[i].priority, case_status_name(cases[i].status));
        if (cases[i].assigned_unit_id == 0) printf("-\n"); else printf("%d\n", cases[i].assigned_unit_id);
    }
}

int main(void) {
    Emergency cases[MAX_CASES];
    ResponseUnit units[MAX_UNITS];
    int case_count = 0, unit_count = 0, choice;
    initialize_units(units, &unit_count);
    printf("Welcome to Emergency Dispatch & Response Priority Simulator\n");
    for (;;) {
        print_menu();
        if (!read_int("Enter your choice (1-7): ", 1, 7, &choice)) {
            printf("Input ended. Exiting program.\n");
            break;
        }
        switch (choice) {
            case 1: register_emergency(cases, &case_count); break;
            case 2: view_pending_emergencies(cases, case_count); break;
            case 3: dispatch_emergency(cases, case_count, units, unit_count); break;
            case 4: view_units(units, unit_count); break;
            case 5: resolve_emergency(cases, case_count, units, unit_count); break;
            case 6: view_history(cases, case_count); break;
            case 7: printf("Thank you for using the simulator. Goodbye!\n"); return 0;
        }
    }
    return 0;
}
