#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

#include "structs.h" // structs definitions + methods
#include "linkedLists.h" // linked list def. & methods
#include "queueStack.h" // queue and stack def. & methods


int main(){
    FILE *inputFilePtr = fopen("tema1.in", "rt");
    
    // Reading units from input file & init. unit
    Queue *queue_available_units = initQueue();
    int numOfUnits;
    fscanf(inputFilePtr, "%d", &numOfUnits);
    Unit *units = (Unit *)malloc(numOfUnits * sizeof(Unit));
    for(int i = 0; i < numOfUnits; i++){
        // creating unit
        fscanf(inputFilePtr, "%d %c", &units[i].id, &units[i].type);
        units[i].availability = 1;
        // adding to queue
        enqueue(queue_available_units, units+i);
    }
    // Declaring & init. incidents list
    Incident *dummyIncident = initIncident(0, "low", "test incident", "solved");
    DoubleLinkedList *incidentList = initList(dummyIncident);

    // Declaring & init. intervention list
    Intervention *dummyIntervention = initIntervention(NULL, NULL);
    DoubleLinkedList *interventionList = initList(dummyIntervention);

    // Declaring & init. queues/stacks
    Queue *queue_high = initQueue();
    Queue *queue_medium = initQueue();
    Queue *queue_low = initQueue();
    Stack *interventions_history = NULL;

    // Operations
    FILE *outputFilePtr = fopen("tema1.out", "wt");
    int numOfOperations;
    char option[25];
    fscanf(inputFilePtr, "%d", &numOfOperations);
    for(int i = 0; i < numOfOperations; i++){
        fscanf(inputFilePtr,"%s", option);
        if(strcmp(option, "ADD_INCIDENT") == 0){
            int id;
            char priority[7], buff[1000];
            fscanf(inputFilePtr, "%d %s", &id, priority);
            fgets(buff, 999, inputFilePtr);
            // delete \n & " from the end of buff
            buff[strlen(buff)-2] = '\0';
            // passing buff+2 as description to get rid of leading space and "
            Incident *newIncident = initIncident(id, priority, buff+2, "queued");
            addToList(incidentList, newIncident);
            // adding incident to its priority queue
            if(strcmp(priority, "high") == 0){
                enqueue(queue_high, newIncident);
            }else if(strcmp(priority, "medium") == 0){
                enqueue(queue_medium, newIncident);
            }else{
                enqueue(queue_low, newIncident);
            }
        }else if(strcmp(option, "CHECK_UNITS_AVAILABILITY") == 0){
            fprintf(outputFilePtr, "Number of available units: %d\n", queue_available_units->len);
        }else if(strcmp(option, "DISPATCH")){
            int valid = 0;
            Queue *qList[3] = {queue_high, queue_low, queue_medium};
            for(int i = 0; i <= 2; i++){
                if(isEmptyQueue(qList[i]) == 0 && isEmptyQueue(queue_available_units) == 0){
                    valid = 1;
                    // creating intervention and adding it to list
                    Incident *inc = (Incident *)qList[i]->front->data;
                    Unit *unit = (Unit *)queue_available_units->front->data;
                    Intervention *newIntervention = initIntervention(inc, unit);
                    addToList(interventionList, newIntervention);
                    // getting id for incident and unit in order to modify status
                    int idInc = inc->id;
                    int idUnit = unit->id;
                    modifyIncident(incidentList, idInc, "intervened");
                    modifyUnit(units, numOfUnits, idUnit, 0);
                    // adding to stack
                    interventions_history = push(interventions_history, newIntervention);
                }
            }
            // error - no unit or intervention available
            if(valid == 0){
                fprintf(outputFilePtr, "INVALID OPERATION! ERROR 404\n");
            }

        }
    }
}