/*
 * PCB.c
 *
 *  Created on: Jan 7, 2016
 *    Author: Jonah Howard
*             Mehgan Cook
*             Anthony Zullo
*             Quinn Cox
 *                      
 */
#include <stdio.h> 
#include <stdlib.h>
#include "PCB1.h"
#include <string.h>


/**
 * creates the pcb
 */
PCB_p create_pcb(int thePid, int thePriority, int theCreationTime) {
    PCB_p pcb_p = malloc(sizeof(PCB));
    pcb_p->state = new; /* current state  of the pcb */
    pcb_p->pid = thePid; /** id of the pid */
    pcb_p->PC = 0; /* where to resume */
//    struct PCB *next_pcb; /* list ptr */
    pcb_p->Priority = thePriority; /* extrinsic property */
    pcb_p->address_space = 0; /* where in memory */
    pcb_p->origPriority = thePriority;
    pcb_p->isCIP = 0;
    pcb_p->isProdCon = 0;
    pcb_p->priorityBoost = 0;
    pcb_p->MAX_PC = 2345;
    pcb_p->CREATION = theCreationTime;
    pcb_p->TERMINATION = 0;
    pcb_p->TERMINATE = 0;
    pcb_p->TERM_COUNT = 0;
    pcb_p->pcb_type = normal;
    return pcb_p;
}

PCB_p create_consumer(int thePid, int thePriority, int theCreationTime, char *theName, int theProdConNum) {
    PCB_p pcb_p_consumer = malloc(sizeof(PCB));
    pcb_p_consumer->state = new; /* current state  of the pcb */
    pcb_p_consumer->pid = thePid; /** id of the pid */
    pcb_p_consumer->PC = 0; /* where to resume */
    pcb_p_consumer->Priority = thePriority; /* extrinsic property */
    pcb_p_consumer->address_space = 0; /* where in memory */
    pcb_p_consumer->origPriority = thePriority;
    pcb_p_consumer->isCIP = 0;
    pcb_p_consumer->priorityBoost = 0;
    strcpy(pcb_p_consumer->name, theName);
    pcb_p_consumer->isProducer = 0;
    pcb_p_consumer->isProdCon = 1;
    pcb_p_consumer->pcb_type = prodcon;
    pcb_p_consumer->prodcon_num = theProdConNum;
    pcb_p_consumer->MAX_PC = 2000;
    pcb_p_consumer->CREATION = theCreationTime;
    pcb_p_consumer->TERMINATION = 0;
    pcb_p_consumer->TERMINATE = 0;
    pcb_p_consumer->TERM_COUNT = 0;
    return pcb_p_consumer; 
}

PCB_p create_MRU(int thePid, int thePriority, int theCreationTime, char *theName, int theMRUNum) {
    PCB_p pcb = malloc(sizeof(PCB));
    pcb->state = new; /* current state  of the pcb */
    pcb->pid = thePid; /** id of the pid */
    pcb->PC = 0; /* where to resume */
    pcb->Priority = thePriority; /* extrinsic property */
    pcb->address_space = 0; /* where in memory */
    pcb->origPriority = thePriority;
    pcb->isCIP = 0;
    pcb->priorityBoost = 0;
    strcpy(pcb->name, theName);
    pcb->isProdCon = 0;
    pcb->pcb_type = nondeadlock;
    pcb->MRU_num = theMRUNum;
    pcb->MAX_PC = 2000;
    pcb->CREATION = theCreationTime;
    pcb->TERMINATION = 0;
    pcb->TERMINATE = 0;
    pcb->TERM_COUNT = 0;
    return pcb; 
};

PCB_p create_producer(int thePid, int thePriority, int theCreationTime, char *theName, int theProdConNum) {
    PCB_p pcb_p_producer = malloc(sizeof(PCB));
    pcb_p_producer->state = new; /* current state  of the pcb */
    pcb_p_producer->pid = thePid; /** id of the pid */
    pcb_p_producer->PC = 0; /* where to resume */
    pcb_p_producer->Priority = thePriority; /* extrinsic property */
    pcb_p_producer->address_space = 0; /* where in memory */
    pcb_p_producer->origPriority = thePriority;
    pcb_p_producer->isCIP = 0;
    pcb_p_producer->priorityBoost = 0;
    strcpy(pcb_p_producer->name, theName);
    pcb_p_producer->isProducer = 1;
    pcb_p_producer->isProdCon = 1;
    pcb_p_producer->pcb_type = prodcon;
    pcb_p_producer->prodcon_num = theProdConNum;
    pcb_p_producer->MAX_PC = 2000;
    pcb_p_producer->CREATION = theCreationTime;
    pcb_p_producer->TERMINATION = 0;
    pcb_p_producer->TERMINATE = 0;
    pcb_p_producer->TERM_COUNT = 0;
    return pcb_p_producer; 
}

/**
 * Gets the state name and returns the state name in a String.
 * @param enum state_type representing the current state
 * @return char* representing the state name
 */
const char* getStateName(enum state_type state) 
{
   switch (state) 
   {
      case new: return "NEW";
      case ready: return "READY";
      case running: return "RUNNING";
      case waiting: return "WAITING";
      case halted: return "HALTED";
   }
}

char* getState(PCB_p pcb_p) {
    return getStateName(pcb_p->state);
}

int getPid(PCB_p pcb_p) {
    return pcb_p->pid; 
}

address getAddress(PCB_p pcb_p) {
    return pcb_p->address_space;
} 

address getPC(PCB_p pcb_p) {
    return pcb_p->PC;
}

int getPriority(PCB_p pcb_p) {
    return pcb_p->Priority;
}



/**
 * Takes a PCB pointer and prints out the contents of the PCB
 * @param PCB_p pointer referencing the PCB to print
 */
void toString(PCB_p pcb_p) {   
    printf("contents: ");
    printf("State: %s  ", getStateName(pcb_p->state));
    printf("PID: %d  ", pcb_p->pid);
    printf("PC: %d  ", pcb_p->PC);
    printf("Priority: %d  ", pcb_p->Priority);
    printf("Address Space: %u\n\n", pcb_p->address_space);
}
/*
 * Prints contents of the passed PCB to the passed file.  
 */
void printToFile(FILE *outfile, PCB_p pcb_p) {
    fprintf(outfile, "contents: ");
    fprintf(outfile, "State: %s  ", getStateName(pcb_p->state));
    fprintf(outfile, "PID: %d  ", pcb_p->pid);
    fprintf(outfile, "PC: %u  ", pcb_p->PC);
    fprintf(outfile, "Priority: %d  ", pcb_p->Priority);
    fprintf(outfile, "Address Space: %u\n\n", pcb_p->address_space);
}

 int PCB_Action(PCB_p thePCB, int *theData) {
     int answer = -1;
     if (thePCB->isProducer) {
         theData++;
     } else {
         answer = *theData;
     }
     return answer;
 }
    
