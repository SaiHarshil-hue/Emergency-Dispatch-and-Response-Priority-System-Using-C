#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "emergency.h"

static int next_case_id = 101;
int read_int(const char *prompt, int min_value, int max_value, int *out_value) {
    char buffer[128], extra;
    long value;
    char *end;
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof buffer, stdin)) return 0;
        value = strtol(buffer, &end, 10);
        while (isspace((unsigned char)*end)) end++;
        if (end == buffer || *end != '\0' || value < min_value || value > max_value) {
            (void)extra;
            printf("Invalid input. Enter a whole number from %d to %d.\n", min_value, max_value);
            continue;
        }
        *out_value = (int)value;
        return 1;
    }
}

int read_double(const char *prompt, double min_value, double max_value, double *out_value) {
    char buffer[128], *end;
    double value;
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof buffer, stdin)) return 0;
        value = strtod(buffer, &end);
        while (isspace((unsigned char)*end)) end++;
        if (end == buffer || *end != '\0' || value < min_value || value > max_value) {
            printf("Invalid input. Enter a number from %.2f to %.2f.\n", min_value, max_value);
            continue;
        }
        *out_value = value;
        return 1;
    }
}

const char *emergency_type_name(EmergencyType type) {
    switch (type) {
        case TYPE_MEDICAL: return "Medical";
        case TYPE_FIRE: return "Fire";
        case TYPE_POLICE: return "Police";
        default: return "Unknown";
    }
}
const char *case_status_name(CaseStatus status) {
    switch (status) {
        case STATUS_PENDING: return "PENDING";
        case STATUS_DISPATCHED: return "DISPATCHED";
        case STATUS_RESOLVED: return "RESOLVED";
        default: return "UNKNOWN";
    }
}
const char *unit_type_name(UnitType type) {
    switch (type) {
        case UNIT_AMBULANCE: return "Ambulance";
        case UNIT_FIRE: return "Fire Unit";
        case UNIT_POLICE: return "Police Unit";
        default: return "Unknown";
    }
}
const char *unit_status_name(UnitStatus status) {
    return status == UNIT_AVAILABLE ? "AVAILABLE" : "BUSY";
}

void register_emergency(Emergency cases[], int *case_count) {
    int id, type, severity;
    double distance;
    char prompt[100];
    if (*case_count >= MAX_CASES) {
        printf("Case storage is full. Cannot register more emergencies.\n");
        return;
    }
    id = next_case_id++;
    printf("Assigned Case ID: %d\n", id);
    printf("Emergency type: 1. Medical  2. Fire  3. Police\n");
    if (!read_int("Choose type: ", 1, 3, &type)) return;
    if (!read_int("Severity (1 = low, 5 = critical): ", 1, 5, &severity)) return;
    (void)snprintf(prompt, sizeof prompt, "Distance from control point in km (0 to 1000): ");
    if (!read_double(prompt, 0.0, 1000.0, &distance)) return;

    cases[*case_count].id = id;
    cases[*case_count].type = (EmergencyType)type;
    cases[*case_count].severity = severity;
    cases[*case_count].distance = distance;
    cases[*case_count].priority = severity * 10.0 + (type == TYPE_MEDICAL ? 10.0 : type == TYPE_FIRE ? 8.0 : 6.0) - (distance / 2.0);
    cases[*case_count].status = STATUS_PENDING;
    cases[*case_count].assigned_unit_id = 0;
    (*case_count)++;
    printf("Emergency registered successfully. Priority score: %.2f\n", cases[*case_count - 1].priority);
}
