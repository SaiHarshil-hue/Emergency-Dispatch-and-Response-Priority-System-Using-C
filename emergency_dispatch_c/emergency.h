#ifndef EMERGENCY_H
#define EMERGENCY_H

#define MAX_CASES 100
#define MAX_UNITS 9
#define ID_LENGTH 20

typedef enum { TYPE_MEDICAL = 1, TYPE_FIRE, TYPE_POLICE } EmergencyType;
typedef enum { STATUS_PENDING = 1, STATUS_DISPATCHED, STATUS_RESOLVED } CaseStatus;
typedef enum { UNIT_AMBULANCE = 1, UNIT_FIRE, UNIT_POLICE } UnitType;
typedef enum { UNIT_AVAILABLE = 1, UNIT_BUSY } UnitStatus;

typedef struct {
    int id;
    EmergencyType type;
    int severity;
    double distance;
    double priority;
    CaseStatus status;
    int assigned_unit_id; /* 0 means no unit assigned */
} Emergency;

typedef struct {
    int id;
    UnitType type;
    double distance;
    UnitStatus status;
    int assigned_case_id; /* 0 means no case assigned */
} ResponseUnit;

const char *emergency_type_name(EmergencyType type);
const char *case_status_name(CaseStatus status);
const char *unit_type_name(UnitType type);
const char *unit_status_name(UnitStatus status);
int read_int(const char *prompt, int min_value, int max_value, int *out_value);
int read_double(const char *prompt, double min_value, double max_value, double *out_value);
void register_emergency(Emergency cases[], int *case_count);
void view_pending_emergencies(Emergency cases[], int case_count);
void sort_pending_by_priority(Emergency cases[], int case_count);
void dispatch_emergency(Emergency cases[], int case_count, ResponseUnit units[], int unit_count);
void view_units(const ResponseUnit units[], int unit_count);
void resolve_emergency(Emergency cases[], int case_count, ResponseUnit units[], int unit_count);
void view_history(const Emergency cases[], int case_count);
void initialize_units(ResponseUnit units[], int *unit_count);

#endif
