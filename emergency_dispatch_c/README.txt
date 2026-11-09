EMERGENCY DISPATCH & RESPONSE PRIORITY SIMULATOR (C)

Files:
  main.c          Menu and program entry point
  emergency.h     Structures, constants, enums and function declarations
  registration.c  Input validation, registration and shared name helpers
  priority.c      Pending-case sorting and display
  dispatch.c      Unit setup, dispatch/allocation, unit display and resolution

Compile (GCC):
  gcc -std=c11 -Wall -Wextra -Wpedantic main.c registration.c priority.c dispatch.c -o emergency_dispatch

Run:
  ./emergency_dispatch
  On Windows, run: emergency_dispatch.exe

Priority formula used:
  Priority = Severity * 10 + Type Weight - Distance Penalty
  Medical weight = 10, Fire weight = 8, Police weight = 6
  Distance penalty = distance in km / 2


Notes:
- This is an educational console simulator, not a real emergency service.
- Nine sample units are initialized (three per category); their distances are fixed example values.
- Data is stored in memory and resets when the program exits.
- Case IDs are automatically generated, starting from 101.
- Severity must be between 1 and 5.
- Distance must be between 0 and 1000 km.
- Invalid inputs are rejected through input validation.

