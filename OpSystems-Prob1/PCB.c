/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h> 
#include "PCB.h"

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
    printf("Address Space: %d\n\n  ", pcb_p->address_space);
}