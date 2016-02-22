/*
 - * PCB.h
 - *
 - *  Created on: Jan 7, 2016
 - *    Author: Jonah Howard
 -              Mehgan Cook
 - *            Anthony Zullo
 - *            Quinn Cox
 - *                      
 - */
 #ifndef PCB_H
 #define PCB_H
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 // number of registers
 #define NUMREGS 16
 // MT
 // Length of Name for PCB's
 #define LENGTH_OF_NAME 20
 
 enum state_type {new, ready, running, waiting, interrupted, halted};
 
 typedef unsigned int address;
 
 // Defines the PCB struct type
 typedef struct pcb {
     enum state_type state; /* current state  of the pcb */
     int pid; /** id of the pid */
     address PC; /* where to resume */
 //    struct PCB *next_pcb; /* list ptr */
     int Priority; /* extrinsic property */
     address address_space; /* where in memory */
 
     int MAX_PC;
     int CREATION;
     int TERMINATION;
     int TERMINATE;
     int TERM_COUNT;

     // MT
     // Priority boost is to determine whether or not we execute these jobs
     int priorityBoost;
     char name[LENGTH_OF_NAME];

     int IO_1_TRAPS[4];
     int IO_2_TRAPS[4];
     int reg_file[NUMREGS]; /* contents of GPRs */
 } PCB;
 
 // Defines the PCB_p which is a pointer to a PCB
 typedef PCB *PCB_p;
 
 
 PCB_p create_pcb(int thePid, int thePriority, int theCreationTime);
 /**
  * Takes a PCB pointer and prints out the contents of the PCB
  * @param PCB_p pointer referencing the PCB to print
  */
 void toString(PCB_p pcb);
 
 void printToFile(FILE *outfile, PCB_p pcb);
 
 char* getState(PCB_p pcb_p);
 
 int getPid(PCB_p pcb_p);
 
 address getAddress(PCB_p pcb_p);
 
 address getPC(PCB_p pcb_p);
 
 int getPriority(PCB_p pcb_p);
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif /* PCB_H */ 