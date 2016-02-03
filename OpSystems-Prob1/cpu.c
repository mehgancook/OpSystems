/**
 *  File:   cpu.c
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
#include "cpu.h"


/*
 * Simulates an operating system dispatcher. Pulls next available PCB from the 
 * ready queue and changes its state to running.
 */
void dispatcher(CPU_p cpu) {
    int bool = 0;
    if (cpu->isRunning != cpu->idle && cpu->fourth_context_switching % 4 == 0) {
        bool = 1;
    }
    PCB_p temp = cpu->isRunning;
    PCB_p temp2;
    if (isEmpty(cpu->readyQueue)) {
        temp2 = cpu->idle;
    } else {
        temp2 = dequeue(cpu->readyQueue);
    }
    if (bool) {
        fprintf(cpu->outfile, "\nRunning PCB:\n");
        temp->state = running;
        printToFile(cpu->outfile, temp);
        fprintf(cpu->outfile, "Switching to:\n");
        printToFile(cpu->outfile, temp2);
    }
    cpu->isRunning = temp2;
    cpu->systack_pc = cpu->isRunning->PC;
    cpu->isRunning->state = running;
    temp->state = ready;
    if (bool) {
        fprintf(cpu->outfile, "New content of PCBs\n");
        printToFile(cpu->outfile, temp);
        printToFile(cpu->outfile, cpu->isRunning);
        to_file_enqueue(cpu->outfile, cpu->readyQueue);
        fprintf(cpu->outfile, "\n");
    }
    cpu->fourth_context_switching++;
    return;
}

/* 
 * Places all PCB's from the new process queue to the ready queue. It then 
 * will change the state of the currently running PCB to ready if the passed 
 * interrupt is the timer. It then calls the dispatcher.
 */
void scheduler(CPU_p cpu, enum interrupt interruption) {
    while (!isEmpty(cpu->newQueue)) {
        PCB_p pcb = dequeue(cpu->newQueue);
        pcb->state = ready;
        fprintf(cpu->outfile, "This pcb has been enqueued to the ready queue\n");
        printToFile(cpu->outfile, pcb);
        enqueue(cpu->readyQueue, pcb);
    }
    if (interruption == timer) {
        cpu->isRunning->state = ready;
        if (cpu->isRunning != cpu->idle) {
            PCB_p pcb = cpu->isRunning;
            fprintf(cpu->outfile, "This pcb has been enqueued to the ready queue\n");
            printToFile(cpu->outfile, pcb);
            enqueue(cpu->readyQueue, cpu->isRunning);
        }
    }
    dispatcher(cpu);
    return;
}

// Simulates an isr timer and calls the scheduler.
void pseudo_isr_timer(CPU_p cpu) {
    cpu->isRunning->state = interrupted;
    cpu->isRunning->PC = cpu->systack_pc;
    scheduler(cpu, timer);
    return;
}

/*
 * Runs the program and simulates the CPU 
 */
void run(CPU_p cpu) {
    cpu->systack_pc = 0;
    cpu->cpu_pc = 0;
    cpu->fourth_context_switching = 1;

    cpu->outfile = fopen("scheduleTrace.txt", "w");
    fprintf(cpu->outfile, "GROUP 10:\nTony Zullo\nJonah Howard\nQuinn Cox\nMehgan Cook\n\n\n");

    cpu->idle = create_pcb(0, 16);
    cpu->newQueue = create_queue();
    cpu->readyQueue = create_queue();

    int bool = 1;
    int pidCounter = 1;
    // Each iteration represents one timer quantum
    while (bool) {
        if (pidCounter > 30) {
            bool = 0;
        }
        int i = rand();
        i = (i % 5) + 1;
        for (;i > 0 && pidCounter < 31; i--) {
            enqueue(cpu->newQueue, create_pcb(pidCounter++, 0));
        }
        if (isEmpty(cpu->readyQueue)) {
            cpu->isRunning = cpu->idle;
        }
        unsigned int random = (rand() % 1001) + 3000;
        cpu->cpu_pc += random;
        cpu->systack_pc = cpu->cpu_pc;
        pseudo_isr_timer(cpu);
        cpu->cpu_pc = cpu->systack_pc;
    }
    fclose(cpu->outfile);
}

