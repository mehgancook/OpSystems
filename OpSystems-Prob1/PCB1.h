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
 
 typedef enum {ready_to_read, ready_to_write, enum_counter} condition_type ;
 
 enum pcb_type_enum {normal, prodcon, nondeadlock, deadlock};
 
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
     int origPriority;
     int isCIP; // Compute Intensive Processes
     int isProdCon;
     enum pcb_type_enum pcb_type;
     int isProducer;
     int prodcon_num;
     int MRU_num;
     int isMRUA;
     char name[LENGTH_OF_NAME];

     int IO_1_TRAPS[4];
     int IO_2_TRAPS[4];
     int MUTEX_1_TRAPS[2];
     int MUTEX_2_TRAPS[2];
     int mutex_lock[2];
     int reg_file[NUMREGS]; /* contents of GPRs */
 } PCB;
 
 // Defines the PCB_p which is a pointer to a PCB
 typedef PCB *PCB_p;
 
 typedef struct pcb_producer {
          enum state_type state; /* current state  of the pcb */
     int pid; /** id of the pid */
     address PC; /* where to resume */
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
     int origPriority;
     int isCIP; // Compute Intensive Processes

     char name[LENGTH_OF_NAME];
     
     int IO_1_TRAPS[4];
     int IO_2_TRAPS[4];
     int MUTEX_1_TRAPS[4];
     int MUTEX_2_TRAPS[4];
     int mutex_lock[2];
     
     int reg_file[NUMREGS]; /* contents of GPRs */

 } PCB_producer, producer;
 
 typedef PCB_producer *PCB_p_producer;
 
 typedef struct pcb_consumer {
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
     int origPriority;
     int isCIP; // Compute Intensive Processes

     char name[LENGTH_OF_NAME];

     int IO_1_TRAPS[4];
     int IO_2_TRAPS[4];
     int MUTEX_1_TRAPS[4];
     int MUTEX_2_TRAPS[4];
     int mutex_lock[2];
     int reg_file[NUMREGS]; /* contents of GPRs */
     
 } PCB_consumer, consumer;
 
 typedef PCB_consumer *PCB_p_consumer;
 
 PCB_p create_pcb(int thePid, int thePriority, int theCreationTime);
 
 PCB_p create_producer(int thePid, int thePriority, int theCreationTime, char *theName, int theProdConNum);
 
 PCB_p create_consumer(int thePid, int thePriority, int theCreationTime, char *theName, int theProdConNum);
 
 PCB_p create_MRU(int thePid, int thePriority, int theCreationTime, char *theName, int theMRUNum);
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
 
// void PCB_Action(PCB_p_producer thePCB, int *theData);
// 
int PCB_Action(PCB_p thePCB, int *theData);
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif /* PCB_H */ 