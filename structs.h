#include "linkedLists.h"

#ifndef STRUCTS_H
#define STRUCTS_H
// General use definitions

typedef struct Unit {
    int id;
    char type;
    int availability;
} Unit;

typedef struct Incident {
    int id;
    char priority[7];
    char *description;
    char status[11];
} Incident;

typedef struct Intervention {
    struct Incident *incident;
    struct Unit *unit;
} Intervention;

// methods
Incident *initIncident(int id, char *priority, char *description, char *status);
Intervention *initIntervention(Incident *incident, Unit *unit);
void modifyIncident(DoubleLinkedList *list, int id, char *status);
void modifyUnit(Unit *units, int numUnits, int idUnit, int availability);
void freeIncident(void *data);

#endif