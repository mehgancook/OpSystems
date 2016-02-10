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
#include "PCB.h"
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

    pcb_p->MAX_PC = 2345;
    pcb_p->CREATION = theCreationTime;
    pcb_p->TERMINATION_TIME = 0;
    pcb_p->TERMINATE = 0;
    pcb_p->TERM_COUNT = 0;
    return pcb_p;
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
    
