#include <stdio.h>
#include "emergency.h"

void initialize_units(ResponseUnit units[], int *unit_count) {
    int i = 0, id;
    const UnitType types[] = {UNIT_AMBULANCE, UNIT_AMBULANCE, UNIT_AMBULANCE, UNIT_FIRE, UNIT_FIRE, UNIT_FIRE, UNIT_POLICE, UNIT_POLICE, UNIT_POLICE};
    const double distances[] = {2.0, 5.0, 8.0, 1.5, 4.0, 7.0, 2.5, 6.0, 9.0};
    for (id = 1; id <= MAX_UNITS; id++, i++) {
        units[i].id = id;
        units[i].type = types[i];
        units[i].distance = distances[i];
        units[i].status = UNIT_AVAILABLE;
        units[i].assigned_case_id = 0;
    }
    *unit_count = i;
}

void view_units(const ResponseUnit units[], int unit_count) {
    int i;
    printf("\n--- RESPONSE UNITS ---\n");
    printf("%-8s %-14s %-12s %-12s %-10s\n", "Unit ID", "Type", "Distance(km)", "Status", "Case ID");
    for (i = 0; i < unit_count; i++) {
        printf("%-8d %-14s %-12.2f %-12s ", units[i].id, unit_type_name(units[i].type), units[i].distance, unit_status_name(units[i].status));
        if (units[i].assigned_case_id == 0) printf("-\n"); else printf("%d\n", units[i].assigned_case_id);
    }
}

void dispatch_emergency(Emergency cases[], int case_count, ResponseUnit units[], int unit_count) {
    int i, j, best_case = -1, best_unit = -1;
    sort_pending_by_priority(cases, case_count);
    for (i = 0; i < case_count; i++) {
        if (cases[i].status != STATUS_PENDING) continue;
        UnitType needed = cases[i].type == TYPE_MEDICAL ? UNIT_AMBULANCE : cases[i].type == TYPE_FIRE ? UNIT_FIRE : UNIT_POLICE;
        for (j = 0; j < unit_count; j++) {
            if (units[j].status == UNIT_AVAILABLE && units[j].type == needed) {
                best_case = i;
                best_unit = j;
                break;
            }
        }
        if (best_case >= 0) break;
    }
    if (best_case < 0) {
        printf("No pending case with a compatible available unit can be dispatched.\n");
        return;
    }
    /* Select the nearest available compatible unit for the highest-priority dispatchable case. */
    {
        UnitType needed = cases[best_case].type == TYPE_MEDICAL ? UNIT_AMBULANCE : cases[best_case].type == TYPE_FIRE ? UNIT_FIRE : UNIT_POLICE;
        for (j = 0; j < unit_count; j++) {
            if (units[j].status == UNIT_AVAILABLE && units[j].type == needed && units[j].distance < units[best_unit].distance) best_unit = j;
        }
    }
    cases[best_case].status = STATUS_DISPATCHED;
    cases[best_case].assigned_unit_id = units[best_unit].id;
    units[best_unit].status = UNIT_BUSY;
    units[best_unit].assigned_case_id = cases[best_case].id;
    printf("Dispatched %s unit %d to case %d (%s).\n", unit_type_name(units[best_unit].type), units[best_unit].id, cases[best_case].id, emergency_type_name(cases[best_case].type));
    printf("Case status: DISPATCHED | Unit status: BUSY\n");
}

void resolve_emergency(Emergency cases[], int case_count, ResponseUnit units[], int unit_count) {
    int id, i, j;
    if (!read_int("Enter case ID to resolve: ", 1, 2147483647, &id)) return;
    for (i = 0; i < case_count; i++) {
        if (cases[i].id == id) break;
    }
    if (i == case_count) { printf("Case ID not found.\n"); return; }
    if (cases[i].status != STATUS_DISPATCHED) {
        printf("Only a DISPATCHED case can be marked as resolved. Current status: %s\n", case_status_name(cases[i].status));
        return;
    }
    cases[i].status = STATUS_RESOLVED;
    for (j = 0; j < unit_count; j++) {
        if (units[j].id == cases[i].assigned_unit_id) {
            units[j].status = UNIT_AVAILABLE;
            units[j].assigned_case_id = 0;
            break;
        }
    }
    cases[i].assigned_unit_id = 0;
    printf("Case %d marked RESOLVED. Assigned unit has been released.\n", id);
}
