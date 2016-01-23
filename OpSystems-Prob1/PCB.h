/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PCB.h
 * Author: Cox Family
 *
 * Created on January 8, 2016, 1:56 PM
 */

#ifndef PCB_H
#define PCB_H

#ifdef __cplusplus
extern "C" {
#endif
// number of registers
#define NUMREGS 16

enum state_type {new, ready, running, waiting, interrupted, halted};

typedef int address;

// Defines the PCB struct type
typedef struct pcb {
    enum state_type state; /* current state  of the pcb */
    int pid; /** id of the pid */
    address PC; /* where to resume */
//    struct PCB *next_pcb; /* list ptr */
    int Priority; /* extrinsic property */
    address address_space; /* where in memory */
    int reg_file[NUMREGS]; /* contents of GPRs */
} PCB;

// Defines the PCB_p which is a pointer to a PCB
typedef PCB *PCB_p;

/**
 * Takes a PCB pointer and prints out the contents of the PCB
 * @param PCB_p pointer referencing the PCB to print
 */
void toString(PCB_p pcb);

char* getState(PCB_p pcb_p);

int getPid(PCB_p pcb_p);

address getAddress(PCB_p pcb_p);

address getPC(PCB_p pcb_p);

int getPriority(PCB_p pcb_p);

#ifdef __cplusplus
}
#endif

#endif /* PCB_H */