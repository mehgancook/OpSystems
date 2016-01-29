/**
 *  File:   main.c
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
#include "PCB.h"
#include "fifo_queue.h"

static PCB_p idle;
static unsigned int systack_pc = 0;
static unsigned int cpu_pc = 0;
static PCB_p isRunning;
static fifo_queue_p newQueue;
static fifo_queue_p readyQueue;
FILE *outfile;
static int fourth_context_switching = 1;
enum interrupt {timer, io};


/*
 * Simulates an operating system dispatcher. Pulls next available PCB from the 
 * ready queue and changes its state to running.
 */
void dispatcher() {
    int bool = 0;
    if (isRunning != idle && fourth_context_switching % 4 == 0) {
        bool = 1;
    }
    PCB_p temp = isRunning;
    PCB_p temp2;
    if (isEmpty(readyQueue)) {
        temp2 = idle;
    } else {
        temp2 = dequeue(readyQueue);
    }
    if (bool) {
        fprintf(outfile, "\nRunning PCB:\n");
        printToFile(outfile, temp);
        fprintf(outfile, "Switching to:\n");
        printToFile(outfile, temp2);
    }
    isRunning = temp2;
    systack_pc = isRunning->PC;
    isRunning->state = running;
    if (bool) {
        fprintf(outfile, "New content of PCBs\n");
        printToFile(outfile, isRunning);
        printToFile(outfile, temp);
        to_file_enqueue(outfile, readyQueue);
        fprintf(outfile, "\n");
    }
    fourth_context_switching++;
    return;
}

/* 
 * Places all PCB's from the new process queue to the ready queue. It then 
 * will change the state of the currently running PCB to ready if the passed 
 * interrupt is the timer. It then calls the dispatcher.
 */
void scheduler(enum interrupt interruption) {
    while (!isEmpty(newQueue)) {
        PCB_p pcb = dequeue(newQueue);
        fprintf(outfile, "This pcb has been enqueued to the ready queue\n");
        printToFile(outfile, pcb);
        enqueue(readyQueue, pcb);
    }
    if (interruption == timer) {
        isRunning->state = ready;
        if (isRunning != idle) {
            PCB_p pcb = isRunning;
            fprintf(outfile, "This pcb has been enqueued to the ready queue\n");
            printToFile(outfile, pcb);
            enqueue(readyQueue, isRunning);
        }
    }
    dispatcher();
    return;
}

// Simulates an isr timer and calls the scheduler.
void pseudo_isr_timer() {
    isRunning->state = interrupted;
    isRunning->PC = systack_pc;
    scheduler(timer);
    return;
}

/*
 * Main driver for this program. Creates a random number of new processes and 
 * simulates the running of the current process. Command line parameters are 
 * ignored. Returns the exit status of the program.
 */
int main(int argc, char** argv) {
    outfile = fopen("scheduleTrace.txt", "w");
    fprintf(outfile, "GROUP 10:\nTony Zullo\nJonah Howard\nQuinn Cox\nMehgan Cook\n\n\n");
    idle = create_pcb(0, 16);
    int bool = 1;
    newQueue = create_queue();
    readyQueue = create_queue();

    int pidCounter = 1;
    // Each iteration represents one timer quantum
    while (bool) {
        if (pidCounter > 30) {
            bool = 0;
        }
        int i = rand();
        i = (i % 5) + 1;
        for (;i > 0; i--) {
            enqueue(newQueue, create_pcb(pidCounter++, 0));
        }
        if (isEmpty(readyQueue)) {
            isRunning = idle;
        }
        unsigned int random = (rand() % 1001) + 3000;
        cpu_pc += random;
        systack_pc = cpu_pc;
        pseudo_isr_timer();
        cpu_pc = systack_pc;
    }
    fclose(outfile);
    return (EXIT_SUCCESS);
}

