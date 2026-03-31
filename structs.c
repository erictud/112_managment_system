#include "structs.h"
#include "linkedLists.h"
#include <stdlib.h>
#include <string.h>

Incident *initIncident(int id, char *priority, char *description, char *status){
    Incident *inc = malloc(sizeof(Incident));
    inc->id = id;
    inc->description = description;
    strcpy(inc->priority, priority);
    strcpy(inc->status, status);
    return inc;
}

Intervention *initIntervention(Incident *incident, Unit *unit){
    Intervention *inv = malloc(sizeof(Intervention));
    inv->incident = incident;
    inv->unit = unit;
    return inv;
}