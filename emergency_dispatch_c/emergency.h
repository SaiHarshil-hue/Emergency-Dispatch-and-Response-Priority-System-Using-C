
#ifndef EMERGENCY_H
#define EMERGENCY_H

#define MAX_CASES 100
#define MAX_UNITS 9
#define ID_LENGTH 20

typedef enum {
    MEDICAL,
    FIRE,
    POLICE
} EmergencyType;

typedef enum {
    STATUS_PENDING,
    STATUS_DISPATCHED,
    STATUS_RESOLVED
} CaseStatus;

typedef enum {
    UNIT_AMBULANCE,
    UNIT_FIRE,
    UNIT_POLICE
} UnitType;

typedef enum {
    UNIT_AVAILABLE,
    UNIT_BUSY
} UnitStatus;

typedef struct {
    int id;
    EmergencyType type;
    int severity;
    double distance;
    double priority;
    CaseStatus status;
    int assigned_unit_id;
} Emergency;

typedef struct {
    int id;
    UnitType type;
    double distance;
    UnitStatus status;
    int assigned_case_id;
} ResponseUnit;

void register_emergency(Emergency cases[], int *case_count);

void sort_pending_by_priority(const Emergency cases[], int case_count,
                              Emergency sorted_cases[]);
void view_pending_emergencies(const Emergency cases[], int case_count);

void initialize_units(ResponseUnit units[], int *unit_count);
void dispatch_emergency(Emergency cases[], int case_count,
                        ResponseUnit units[], int unit_count);
void resolve_emergency(Emergency cases[], int case_count,
                       ResponseUnit units[], int unit_count);

void view_units(const ResponseUnit units[], int unit_count);
void view_history(const Emergency cases[], int case_count);

const char *emergency_type_name(EmergencyType type);
const char *unit_type_name(UnitType type);

int read_int(const char *prompt, int min_value, int max_value,
             int *out_value);
const char *case_status_name(CaseStatus status);
const char *unit_status_name(UnitStatus status);

#endif
