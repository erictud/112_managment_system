#include "structs.h"
#include "linkedLists.h"
#include <stdlib.h>
#include <string.h>
#include <string.h>

Incident *initIncident(int id, char *priority, char *description, char *status){
    Incident *inc = malloc(sizeof(Incident));
    inc->id = id;
    inc->description = malloc(strlen(description)+1);
    strcpy(inc->description, description);
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

void modifyIncident(DoubleLinkedList *list, int id, char *status){
    Node *p = list->head->next;
    while(p != list->head){
        Incident *inc = (Incident *)p->data;
        int idInc = inc->id;
        if(idInc == id){
            strcpy(inc->status, status);
            return;
        }
        p = p->next;   
    }
}

void modifyUnit(Unit *units, int numUnits, int idUnit, int availability){
    for(int i = 0; i < numUnits; i++)
        if(units[i].id == idUnit){
            units[i].availability = availability;
            return;
        }
} 