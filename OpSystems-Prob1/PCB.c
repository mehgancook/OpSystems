/*
 * PCB.c
 *
 *  Created on: Jan 7, 2016
 *    Author: Jonah Howard
 *                      Mehgan Cook
 *                      Anthony Zullo
 *                      Quinn Cox
 *                      
 */
#include <stdio.h> 
#include "PCB.h"


/**
 * creates the pcb
 */
PCB_p create_pcb(int thePid, int thePriority) {
    PCB_p pcb_p = malloc(sizeof(PCB));
    pcb_p->state = new; /* current state  of the pcb */
    pcb_p->pid = thePid; /** id of the pid */
    pcb_p->PC = 0; /* where to resume */
//    struct PCB *next_pcb; /* list ptr */
    pcb_p->Priority = thePriority; /* extrinsic property */
    pcb_p->address_space = 0; /* where in memory */
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

    // prints the register files associated with this PCB
    printf("Reg Files:  ");
    if (pcb_p->reg_file) {
        int i;
        for (i = 0; i < NUMREGS; i++) {
            printf("REG%d: %d  ", i, pcb_p->reg_file[i]);
        }
        printf("  ");
    } else {
        printf("\t\tNONE\n\n");
    }

    // // if there exists a following pcb, print out the next address
    // if (pcb_p->next_pcb) {
    //     PCB_p next = pcb_p->next_pcb;
    //     printf("Next Struct Address: %d  ", next->address_space);
    // } else {
    // // otherwise print nothing
    //     printf("Next Struct Address: NULL  ");
    // }

    printf("Priority: %d  ", pcb_p->Priority);
    printf("Address Space: %u\n\n  ", pcb_p->address_space);
}
/*
 * Prints contents of the passed queue to the passed file.  
 */
void print_to_file(FILE *outfile, fifo_queue_p queue) {
    struct Node current = queue->head;
    while (current) {
        fwrite("contents: ", 1, 1, outfile);
        fprintf(outfile, "State: %s  ", getStateName(current->pcb->state));
        fprintf(outfile, "PID: %d  ", current->pcb->pid);
        fprintf(outfile, "PC: %d  ", current->pcb->PC);
            // prints the register files associated with this PCB
        fwrite("Reg Files:  ", 1, 1, outfile);
        if (current->pcb->reg_file) {
            int i;
            for (i = 0; i < NUMREGS; i++) {
                fprintf(outfile, "REG%d: %d  ", i, current->pcb->reg_file[i]);
            }
            fwrite("  ", 1, 1, outfile);
        } else {
            fwrite("\t\tNONE\n\n"1, 1, outfile);
        }
        fprintf(outfile, "Priority: %d  ", current->pcb->Priority);
        fprintf(outfile, "Address Space: %u\n\n  ", current->pcb->address_space);
        current = current->next;
    }
}