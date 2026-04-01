#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "structs.h"     // structs definitions + methods
#include "linkedLists.h" // linked list def. & methods
#include "queueStack.h"  // queue and stack def. & methods

// comparing function that matches a intervention
// pointer to a specific id
int cmpInterventionToIndex(void *data, int id)
{
    Intervention *inv = (Intervention *)data;
    int idCmp = inv->incident->id;
    return id == idCmp;
}

int main()
{
    FILE *inputFilePtr = fopen("tema1.in", "rt");
    FILE *outputFilePtr = fopen("tema1.out", "wt");

    // Reading units from input file & init. unit
    Queue *queue_available_units = initQueue();
    int numOfUnits;
    fscanf(inputFilePtr, "%d", &numOfUnits);
    Unit *units = (Unit *)malloc(numOfUnits * sizeof(Unit));
    for (int i = 0; i < numOfUnits; i++)
    {
        // creating unit
        fscanf(inputFilePtr, "%d %c", &units[i].id, &units[i].type);
        units[i].availability = 1;
        // adding to queue
        enqueue(queue_available_units, units + i);
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
    int numOfOperations;
    char option[25];
    fscanf(inputFilePtr, "%d", &numOfOperations);
    for (int i = 0; i < numOfOperations; i++)
    {
        fscanf(inputFilePtr, "%s", option);
        if (strcmp(option, "ADD_INCIDENT") == 0)
        {
            //parsing incident details
            int id;
            char priority[7], buff[1000];
            fscanf(inputFilePtr, "%d %s", &id, priority);
            fgets(buff, 999, inputFilePtr);

            // delete \n & " from the end of buff
            buff[strlen(buff) - 2] = '\0';

            // passing buff+2 as description to get rid of leading space and "
            Incident *newIncident = initIncident(id, priority, buff + 2, "queued");
            addToList(incidentList, newIncident);

            // adding incident to its priority queue
            if (strcmp(priority, "high") == 0)
            {
                enqueue(queue_high, newIncident);
            }
            else if (strcmp(priority, "medium") == 0)
            {
                enqueue(queue_medium, newIncident);
            }
            else
            {
                enqueue(queue_low, newIncident);
            }
        }
        else if (strcmp(option, "CHECK_UNITS_AVAILABILITY") == 0)
        {
            fprintf(outputFilePtr, "Number of available units: %d\n", queue_available_units->len);
        }
        else if (strcmp(option, "DISPATCH") == 0)
        {
            int valid = 0;
            Queue *qList[3] = {queue_high, queue_medium, queue_low};
            for (int i = 0; i <= 2; i++)
            {
                // iterating queues in priority order to det. which incident to solve 
                if (isEmptyQueue(qList[i]) == 0 && isEmptyQueue(queue_available_units) == 0)
                {
                    valid = 1;
                    // creating intervention and adding it to list
                    Incident *inc = (Incident *)qList[i]->front->data;
                    Unit *unit = (Unit *)queue_available_units->front->data;
                    Intervention *newIntervention = initIntervention(inc, unit);
                    addToList(interventionList, newIntervention);

                    // making unit unavailable by popping queue
                    dequeue(qList[i]);
                    dequeue(queue_available_units);

                    // getting id for incident and unit in order to modify status
                    int idInc = inc->id;
                    int idUnit = unit->id;
                    modifyIncident(incidentList, idInc, "intervened");
                    modifyUnit(units, numOfUnits, idUnit, 0);

                    // adding intervetion to history stack
                    interventions_history = push(interventions_history, newIntervention);
                    break;
                }
            }
            // error - no unit or intervention available
            if (valid == 0)
            {
                fprintf(outputFilePtr, "INVALID OPERATION! ERROR 404\n");
            }
        }
        else if (strcmp(option, "UNDO_LAST_DISPATCH") == 0)
        {
            int valid = 0;
            while (isEmptyStack(interventions_history) == 0)
            {
                // determining last intervention dispatched
                Stack *s = top(interventions_history);
                interventions_history = pop(interventions_history);
                Intervention *interv = (Intervention *)s->data;
                if (strcmp(interv->incident->status, "intervened") == 0)
                {
                    valid = 1;
                    // getting id for incident and unit in order to modify status
                    int idInc = interv->incident->id;
                    int idUnit = interv->unit->id;

                    // deleting intervention from list
                    delFromList(interventionList, idInc, cmpInterventionToIndex);
                    modifyIncident(incidentList, idInc, "queued");
                    modifyUnit(units, numOfUnits, idUnit, 1);

                    // making unit & incident again available by queueing them
                    enqueue(queue_available_units, interv->unit);

                    if (strcmp(interv->incident->priority, "high") == 0)
                    {
                        enqueueFirst(queue_high, interv->incident);
                    }
                    else if (strcmp(interv->incident->priority, "medium") == 0)
                    {
                        enqueueFirst(queue_medium, interv->incident);
                    }
                    else
                        enqueueFirst(queue_low, interv->incident);
                    free(s);
                    free(interv);
                    break;
                }
                free(s);
            }

            // error - no active dispatch found
            if (valid == 0)
                fprintf(outputFilePtr, "INVALID OPERATION! ERROR 404\n");
        }
        else if (strcmp(option, "SOLVED_INCIDENT") == 0)
        {
            int valid = 0, idIncFind;
            fscanf(inputFilePtr, "%d", &idIncFind);

            // trying to find the intervention with the specific incident id
            Node *p = interventionList->head->next;
            while (p != interventionList->head)
            {
                Intervention *interv = (Intervention *)p->data;
                int intervIncId = interv->incident->id;
                // making sure the incident has status intervened
                if (intervIncId == idIncFind && strcmp(interv->incident->status, "intervened") == 0)
                {
                    valid = 1;
                    modifyIncident(incidentList, intervIncId, "solved");
                    modifyUnit(units, numOfUnits, interv->unit->id, 1);
                    enqueue(queue_available_units, interv->unit);
                }
                p = p->next;
            }

            // error - invalid id or incident not in the right state
            if (valid == 0)
                fprintf(outputFilePtr, "INVALID OPERATION! ERROR 404\n");
        }
        else if (strcmp(option, "SHOW_UNIT") == 0)
        {
            int idUnit, valid = 0;
            fscanf(inputFilePtr, "%d", &idUnit);
            for (int i = 0; i < numOfUnits; i++)
                if (units[i].id == idUnit)
                {
                    valid = 1;
                    fprintf(outputFilePtr, "Unit %d is type %c and is %s\n", units[i].id, units[i].type, (units[i].availability == 1 ? "available" : "unavailable"));
                }
            
            // error - invalid unit id
            if (valid == 0)
                fprintf(outputFilePtr, "INVALID OPERATION! ERROR 404\n");
        }
        else if (strcmp(option, "SHOW_INCIDENT") == 0)
        {
            int idIncident, valid = 0;
            fscanf(inputFilePtr, "%d", &idIncident);
            Node *p = incidentList->head->next;
            // trying to find incident by id
            while (p != incidentList->head)
            {
                Incident *inc = (Incident *)p->data;
                if (inc->id == idIncident)
                {
                    valid = 1;
                    fprintf(outputFilePtr, "Incident %d has %s priority, the following description: \"%s\" and is %s\n",
                            idIncident, inc->priority, inc->description, inc->status);
                }
                p = p->next;
            }

            // error - incorect id
            if (valid == 0)
                fprintf(outputFilePtr, "INVALID OPERATION! ERROR 404\n");
        }
        else // SHOW_INTERVENTIONS case
        {
            Node *p = interventionList->head->next;
            // error - intervention list is void
            if (p->next == p)
                fprintf(outputFilePtr, "No intervention has been initiated\n");
            else
            {
                while (p != interventionList->head)
                {
                    Intervention *interv = (Intervention *)p->data;
                    fprintf(outputFilePtr, "Incident %d was assigned to unit %d, and has the following status: \"%s\"\n",
                            interv->incident->id, interv->unit->id, interv->incident->status);
                    p = p->next;
                }
            }
        }
    }

    // freeing dynamic memory
    fclose(inputFilePtr);
    fclose(outputFilePtr);
    freeList(&incidentList, freeIncident);
    free(units);
    freeList(&interventionList, NULL);
    freeQueue(&queue_available_units);
    freeQueue(&queue_high);
    freeQueue(&queue_low);
    freeQueue(&queue_medium);
    freeStack(interventions_history);
}