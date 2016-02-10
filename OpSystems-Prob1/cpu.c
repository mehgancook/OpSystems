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
#define timerInitTime 300
#define num_pcbs 6
#define max_sys_timer 10000

// Global variables
int pidCounter = 0;
int computerTime = 0;
int currentTimerTime = timerInitTime;
int ioTimerTime1;
int ioTimerTime2;
int initialioTimerTime1;
int initialioTimerTime2;
fifo_queue_p terminateQueue;
fifo_queue_p ioWaitingQueue1;
fifo_queue_p ioWaitingQueue2;

void ReadyQueueToIsRunning(CPU_p cpu) {
    if (!isEmpty(cpu->readyQueue)) {
        cpu->isRunning = dequeue(cpu->readyQueue);
    } else {
        cpu->isRunning = cpu->idle;
    }
}

void dequeueReadyQueue(CPU_p cpu) {
    cpu->isRunning->state = ready;
    if (cpu->isRunning != cpu->idle) {
        PCB_p pcb = cpu->isRunning;
        if (!isEmpty(cpu->readyQueue)) {
            fprintf(cpu->outfile, "This pcb has been enqueued to the ready queue\n");
            printToFile(cpu->outfile, pcb);
        } else {
            cpu->isRunning = cpu->idle;
        }
        enqueue(cpu->readyQueue, cpu->isRunning);
    }
}

void initialize_IO_trap_array(PCB_p pcb) {
    int io[8] = {0};
    int i, random;
    int unique = 1;
    for (i = 0; i < 8; i++) {
        int bool = 1;
        while (bool) {
            random = (rand() % (pcb->MAX_PC - 1)) + 1;
            int j = 0;
            for (; j < 8; j++) {
                if (io[j] == random) {
                    break;
                }
            }
            if (j == 8) {
                bool = 0;
            }
        }
        io[i] = random;
        if (i < 4) {
            pcb->IO_1_TRAPS[i] = random;
        } else {
            pcb->IO_2_TRAPS[i - 4] = random; 
        }
    } 
}

void initialize(CPU_p cpu) {
    int i = rand();
    i = (i % 5) + 1;
    for (;i > 0 && pidCounter < num_pcbs; i--) {
        PCB_p pcb = create_pcb(pidCounter++, 0, 0);
        pcb->MAX_PC = (rand() % 2001) + 2000;
        pcb->TERMINATE = (rand() % 31) + 30;
        initialize_IO_trap_array(pcb);
        enqueue(cpu->newQueue, pcb);
    }
      // assign MAX_PC with a random number between 2000 - 4000
      // assign Terminate value with a random number between 0 - 30
      // assign IO Trap Arrays 1 & 2 with initializeIOTrapArray();
}




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

int timerInterrupt() {
    currentTimerTime--;
    if (currentTimerTime <= 0) {
        currentTimerTime = timerInitTime; 
        return 1;
    } else {
        return 0;
    }
}

int iointerrupt1(CPU_p cpu) {
    ioTimerTime1--;
    if (ioTimerTime1 <= 0 && !isEmpty(ioWaitingQueue1)) {
        ioTimerTime1 = initialioTimerTime1;
        enqueue(cpu->readyQueue, dequeue(ioWaitingQueue1));
        return 1;
    } else {
        return 0;
    }
}

int iointerrupt2(CPU_p cpu) {
    ioTimerTime2--;
    if (ioTimerTime2 <= 0 && !isEmpty(ioWaitingQueue2)) {
        ioTimerTime2 = initialioTimerTime2;
        enqueue(cpu->readyQueue, dequeue(ioWaitingQueue2));
        return 1;
    } else {
        return 0;
    }
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

void trapHandler(CPU_p cpu, int io) {
    if (io == 1){
        enqueue(ioWaitingQueue1 ,cpu->isRunning);
        ReadyQueueToIsRunning(cpu);
    } else if (io == 2) {
        enqueue(ioWaitingQueue2 ,cpu->isRunning);
        ReadyQueueToIsRunning(cpu);
    }
}

void checkForTrapArrays(CPU_p cpu) {
    int i = 0;
    for (; i < 4; i++) {
        if(cpu->isRunning->IO_1_TRAPS[i] == cpu->isRunning->PC) {
            trapHandler(cpu, 1);
            break;
        } else if(cpu->isRunning->IO_2_TRAPS[i] == cpu->isRunning->PC){
            trapHandler(cpu, 2);
            break;
        }
    }
}
/*
 * Runs the program and simulates the CPU 
 */
void run(CPU_p cpu) {
    cpu->systack_pc = 0;
    cpu->cpu_pc = 0;
    cpu->fourth_context_switching = 1;
    terminateQueue = create_queue();
    ioWaitingQueue1 = create_queue();
    ioWaitingQueue2 = create_queue();
    ioTimerTime1 = ((rand() % 3) + 3) * timerInitTime;
    ioTimerTime2 = ((rand() % 3) + 3) * timerInitTime;
    initialioTimerTime1 = ioTimerTime1;
    initialioTimerTime2 = ioTimerTime2;

    cpu->outfile = fopen("scheduleTrace.txt", "w");
    fprintf(cpu->outfile, "GROUP 10:\nTony Zullo\nJonah Howard\nQuinn Cox\nMehgan Cook\n\n\n");

    cpu->idle = create_pcb(0, 16, 0);
    cpu->idle->MAX_PC = -1;
    cpu->idle->TERMINATE = 0;
    int i = 0;
    for (; i < 4; i++) {
        cpu->idle->IO_1_TRAPS[i] = -1;
        cpu->idle->IO_2_TRAPS[i] = -1;
    }
    
    cpu->newQueue = create_queue();
    cpu->readyQueue = create_queue();
    
    if (isEmpty(cpu->readyQueue)) {
        cpu->isRunning = cpu->idle;
    }
    
    initialize(cpu);
    int bool = 1;
    int pidCounter = 1;
    // Each iteration represents one timer quantum
    //computerTime < max_sys_timer
    while (1) {
        computerTime++;
        cpu->isRunning->PC ++;
  


        if (cpu->isRunning->PC >= cpu->isRunning->MAX_PC) {
            cpu->isRunning->PC = 0;
            if (!cpu->isRunning->TERMINATE && cpu->isRunning->TERM_COUNT >= cpu->isRunning->TERMINATE) {
                cpu->isRunning->TERMINATION_TIME = computerTime;
                enqueue(&terminateQueue, cpu->isRunning);
                cpu->isRunning = dequeue(cpu->readyQueue);
                computerTime = timerInitTime;
            }
        }
        int timerRun = timerInterrupt();
        if (timerRun) {
            pseudo_isr_timer(cpu);
        } else {
            iointerrupt1(cpu);
            iointerrupt2(cpu);        
            checkForTrapArrays(cpu);
        }
        printf("working\n");
        
//        unsigned int random = (rand() % 1001) + 3000;
//        cpu->cpu_pc += random;
//        cpu->systack_pc = cpu->cpu_pc;
//        pseudo_isr_timer(cpu);
//        cpu->cpu_pc = cpu->systack_pc;
    }
    fclose(cpu->outfile);
}
