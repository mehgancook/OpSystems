/**
 *  File:   main.c
 *  Created on: Jan 7, 2016
 *  Author: Mehgan Cook
 *          Jonah Howard
 *          Tony Zullo
 *          Quinn Cox
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
static int fourth_context_switching = 1;
enum interrupt {timer, io};

//#include "pcb_test.h"
//#include "PriorityQueue_test.h"

// void testFIFO() {
//     fifo_queue_p q = create_queue();
//     int j = 0;
//     int i = 0;
//     while (i < 5) {
//         PCB_p pcb = create_pcb(i, j);
//         enqueue(q, pcb);
//         i++; j++;
//           to_string_enqueue(q);
//     }
// }

void dispatcher() {
    printf("made it to dispatcher.");
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
        toString(temp);
        printf("Switching to ");
        toString(temp2);
    }
    isRunning = temp2;
    systack_pc = isRunning->PC;
    isRunning->state = running;
    if (bool) {
        toString(isRunning);
        toString(temp);
        fourth_context_switching++;
    }
    return;
}

void scheduler(enum interrupt interruption) {
    while (!isEmpty(newQueue)) {
        PCB_p pcb = dequeue(newQueue);
        printf("This pcb has been enqueued from new list:\n");
        toString(pcb);
        enqueue(readyQueue, pcb);
    }
    if (interruption == timer) {
        isRunning->state = ready;
        if (isRunning != idle) {
            PCB_p pcb = isRunning;
            printf("This pcb has been enqueued from is running:\n");
            toString(pcb);
            enqueue(readyQueue, isRunning);
        }
    }
    dispatcher();
    return;
}

void pseudo_isr_timer() {
    isRunning->state = interrupted;
    isRunning->PC = systack_pc;
    scheduler(timer);
    return;
}

int main(int argc, char** argv) {

    idle = create_pcb(0, 16);
    int bool = 1;
    newQueue = create_queue();
    readyQueue = create_queue();

    int pidCounter = 1;
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
 
    return (EXIT_SUCCESS);
}

