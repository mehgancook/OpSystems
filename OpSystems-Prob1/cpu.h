/**
 *  File:   cpu.h
 *  Created on: Jan 7, 2016
 *  Author: Mehgan Cook
 *          Jonah Howard
 *          Tony Zullo
 *          Quinn Cox
 * 
 * This program simulates a scheduler implementing the round robin algorithm.
 */
 #include <stdio.h>
#include <stdlib.h>
#include "PCB1.h"
#include "fifo_queue.h"

#ifndef CPU_H
#define CPU_H

#ifdef __cplusplus
extern "C" {
#endif

enum interrupt {timer, io};


typedef struct cpu {
    PCB_p idle;
    unsigned int systack_pc;
    unsigned int cpu_pc;
    PCB_p isRunning;
    fifo_queue_p newQueue;
    fifo_queue_p readyQueue;
    FILE *outfile;
    int fourth_context_switching;
    int pidCounter;
    int computerTime;
    int currentTimerTime;
    int ioTimerTime1;
    int ioTimerTime2;
    int initialioTimerTime1;
    int initialioTimerTime2;
    fifo_queue_p terminateQueue;
    fifo_queue_p ioWaitingQueue1;
    fifo_queue_p ioWaitingQueue2;
} CPU;

typedef CPU *CPU_p;

/*
 * Simulates an operating system dispatcher. Pulls next available PCB from the 
 * ready queue and changes its state to running.
 */
void dispatcher(CPU_p cpu);

/* 
 * Places all PCB's from the new process queue to the ready queue. It then 
 * will change the state of the currently running PCB to ready if the passed 
 * interrupt is the timer. It then calls the dispatcher.
 */
void scheduler(CPU_p cpu, enum interrupt interruption);

// Simulates an isr timer and calls the scheduler.
void pseudo_isr_timer(CPU_p cpu);

/*
 * Runs the program
 */
void run(CPU_p cpu);

#ifdef __cplusplus
}
#endif

#endif /* PCB_TEST_H */

