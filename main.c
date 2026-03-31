#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

#include "structs.h" // structs definitions + methods
#include "linkedLists.h" // linked list def. & methods
#include "queueStack.h" // queue and stack def. & methods


int main(){
    FILE *inputFilePtr = fopen("tema1.in", "rt");
    // Reading units from input file & init. unit
    int numOfUnits;
    fscanf(inputFilePtr, "%d", &numOfUnits);
    Unit *units = (Unit *)malloc(numOfUnits * sizeof(Unit));
    for(int i = 0; i < numOfUnits; i++){
        fscanf(inputFilePtr, "%d %c", &units[i].id, &units[i].type);
    }
    // Declaring & init. incidents list
    Incident *dummyIncident = initIncident(0, "low", "test incident", "solved");
    DoubleLinkedList *incidentList = initList(dummyIncident);

    // Declaring & init. intervention list
    Intervention *dummyIntervention = initIntervention(NULL, NULL);
    DoubleLinkedList *interventionList = initList(dummyIntervention);

    // Declaring & init. queues
    Queue *queue_high = initQueue();
    Queue *queue_medium = initQueue();
    Queue *queue_low = initQueue();
    Queue *queue_available_unit = initQueue();
}