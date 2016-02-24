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
#include "PCB1.h"
#include "fifo_queue.h"
#include "PriorityQueue.h"
#include "cpu.h"

#define timerInitTime 300 // Quantum
#define num_pcbs 100
#define max_sys_timer 300000

#define starvationTimer 1 // TODO Change to a higher number

// TODO: Decrease number of quantums to termination
// TODO: Generate PCB's with different priorities based off %

// TODO: Generate PCB's every once in a while
// TODO: Keep running 


// MT
// Generates a random number
int generateRandomNumber(int lowest, int highest) {
    int i = rand();
    i = (i % (highest - lowest)) + lowest;
    return i;
}

// MT
// Generate priority for PCB's
int generatePriority() {
    int n = generateRandomNumber(1, 100);
    int priority;
    switch(n) {
        case 6 < n:
            priority = 0;
            break;
        case 11 < n:
            priority = 3;
            break;
        case 21 < n:
            priority = 2;
            break;
        default:
            priority = 1;
            break;
    }
    return priority;
}

// Transfer the next PCB from the ready queue to currently running
void ReadyQueueToIsRunning(CPU_p cpu) {
    if (!isEmpty(cpu->readyQueue)) {
        // MT
        PCB_p pcb = dequeue_priority(cpu->readyQueue);
        fprintf(cpu->outfile, "PID %d put into waiting queue, PID %d dispatched\n", cpu->isRunning->pid,
            // MT
            pcb->pid);

        // MT
        cpu->isRunning = pcb;
    } else {
        cpu->isRunning = cpu->idle;
    }
}

// Transfers currently running process to the ready queue so long as the 
// currently running process is not the idle process.
void dequeueReadyQueue(CPU_p cpu) {
    cpu->isRunning->state = ready;
    if (cpu->isRunning != cpu->idle) {
        PCB_p pcb = cpu->isRunning;
        // MT
        if (!isEmptyPriorityQueue(cpu->readyQueue)) {
        } else {
            cpu->isRunning = cpu->idle;
        }
        // MT
        enqueue_priority(cpu->readyQueue, cpu->isRunning);
    }
}

// Initializes both I/O trap arrays for the passed PCB.
void initialize_IO_trap_array(PCB_p pcb) {
    int io[8] = {0};
    int i, random;
    int bool;
    for (i = 0; i < 8; i++) {
        bool = 1;
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
        // Fill each trap array
        if (i < 4) {
            pcb->IO_1_TRAPS[i] = random;
        } else {
            pcb->IO_2_TRAPS[i - 4] = random; 
        }
    } 
}

// Initialize a random number of PCB's and places them into the new Queue.
void initialize(CPU_p cpu) {
    time_t t;
    srand((unsigned) time(&t));
    int i = rand();
    i = (i % 5) + 1;
    // MT
    int zeroCount = 0;
   // for (;i > 0 && pidCounter < num_pcbs; i--) {
    while (cpu->pidCounter < num_pcbs) {
        // MT
        // Generate intial priority
        int priority = generatePriority();
        // If priority is 0
        if (priority == 0) {
            // Increment 0 count
            zeroCount += 1;
            // If we have more than 25 PCB's with 0 as a priority
            if (zeroCount <= 25) {
                // generate a new priority that is not 0
                while (priority == 0) {
                    priority = generatePriority();
                }
            }
        }

        // MT
        cpu->priorityCount[priority] += 1;
        PCB_p pcb = create_pcb(cpu->pidCounter++, priority, 0);
        // MT
        // If priority was set to 0
        if (priority == 0) {
            // Set isCIP to 1
            pcb->isCIP = 1;
        }

        fprintf(cpu->outfile,"Process created: PID %d at %d\n", pcb->pid, cpu->computerTime);
        // assign MAX_PC with a random number between 2000 - 4000
        pcb->MAX_PC = (rand() % 2001) + 2000;
        // assign Terminate value with a random number between 0 - 30
        pcb->TERMINATE = (rand() % 31);
        // assign IO Trap Arrays 1 & 2 with initializeIOTrapArray();
        initialize_IO_trap_array(pcb);
        enqueue(cpu->newQueue, pcb);
    }  
}

/*
 * Simulates an operating system dispatcher. Pulls next available PCB from the 
 * ready queue and changes its state to running.
 */
void dispatcher(CPU_p cpu) {
    int bool = 0;
    
    if (cpu->isRunning != cpu->idle && cpu->fourth_context_switching % 4 == 0) {
        bool = 1;
    } else {
        bool = 1;
    }
    PCB_p temp = cpu->isRunning;
    PCB_p temp2;

    // MT
    if (isEmptyPriorityQueue(cpu->readyQueue)) {
        temp2 = cpu->idle;
    } else {
        // MT
        temp2 = dequeue_priority(cpu->readyQueue);
    }
    if (bool) {
        fprintf(cpu->outfile,"Timer interrupt: PID %d was running, PID %d dispatched\n", temp->pid, temp2->pid);
        temp->state = running;
    }
    cpu->isRunning = temp2;
    cpu->systack_pc = cpu->isRunning->PC;
    cpu->isRunning->state = running;

    // MT Resets priorityBoost and origPriority to defaults
    // In SWAP in the isRunning, change out the origPriority and the
    // priorityBoost flag
    cpu->isRunning->priorityBoost = 0;
    if (cpu->isRunning->origPriority >= 0) {
        cpu->isRunning->Priority = cpu->isRunning->origPriority;
    }
    cpu->isRunning->origPriority = -1;

    temp->state = ready;
    cpu->fourth_context_switching++;
    return;
}

// Simulates a timer interrupt. Returns 1 if a timer interrupt has occurred,
// 0 otherwise.
int timerInterrupt(CPU_p cpu) {
    cpu->currentTimerTime--;
    if (cpu->currentTimerTime <= 0) {
        cpu->currentTimerTime = timerInitTime; 
        return 1;
    } else {
        return 0;
    }
}

// Simulates I/O being processed. Returns 1 if I/O interrupt has occurred, 0
// otherwise.
int iointerrupt1(CPU_p cpu) {
    cpu->ioTimerTime1--;
    if (cpu->ioTimerTime1 <= 0 &&
        // MT
        !isEmptyPriorityQueue(cpu->ioWaitingQueue1)) {
        cpu->ioTimerTime1 = cpu->initialioTimerTime1;
        fprintf(cpu->outfile,"I/O completion interrupt1: PID %d is running, PID %d put in ready queue\n", cpu->isRunning->pid, cpu->ioWaitingQueue1->head->pcb->pid);
        // MT
        enqueue_priority(cpu->readyQueue, dequeue(cpu->ioWaitingQueue1));
        return 1;
    } else {
        return 0;
    }
}

int iointerrupt2(CPU_p cpu) {
    cpu->ioTimerTime2--;
    if (cpu->ioTimerTime2 <= 0 && !isEmpty(cpu->ioWaitingQueue2)) {
        cpu->ioTimerTime2 = cpu->initialioTimerTime2;
        fprintf(cpu->outfile,"I/O completion interrupt2: PID %d is running, PID %d put in ready queue\n", cpu->isRunning->pid, cpu->ioWaitingQueue2->head->pcb->pid);
        enqueue_queue(cpu->readyQueue, dequeue(cpu->ioWaitingQueue2));
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
        enqueue_priority(cpu->readyQueue, pcb);
    }
    if (interruption == timer) {
        cpu->isRunning->state = ready;
        if (cpu->isRunning != cpu->idle) {
            PCB_p pcb = cpu->isRunning;
            enqueue_priority(cpu->readyQueue, cpu->isRunning);
        }
    }
    dispatcher(cpu);
    return;
}

// Simulates an isr timer and calls the scheduler.
void pseudo_isr_timer(CPU_p cpu) {
    cpu->isRunning->state = interrupted;
    scheduler(cpu, timer);
    return;
}

// Transfers currently running PCB to respective I/O waiting queue
void trapHandler(CPU_p cpu, int io) {
    if (io == 1) {
        fprintf(cpu->outfile,"I/O trap request: I/O device 1,");
        enqueue(cpu->ioWaitingQueue1 ,cpu->isRunning);
        ReadyQueueToIsRunning(cpu);
    } else if (io == 2) {
        fprintf(cpu->outfile,"I/O trap request: I/O device 2,");
        enqueue(cpu->ioWaitingQueue2 ,cpu->isRunning);
        ReadyQueueToIsRunning(cpu);
    }
}

// Checks if an I/O interrupt has occurred 
void checkForTrapArrays(CPU_p cpu) {
    int i = 0;
    if (!cpu->isRunning->isCIP) {
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
}
/*
 * Runs the program and simulates the CPU 
 */
void run(CPU_p cpu) {
    cpu->pidCounter= 0;
    cpu->computerTime = 0;
    cpu->currentTimerTime = timerInitTime;
    cpu->systack_pc = 0;
    cpu->cpu_pc = 0;
    cpu->fourth_context_switching = 1;

    // MT number of current quantums
    cpu->numberOfQuantums = 0;

    cpu->terminateQueue = create_queue();
    cpu->ioWaitingQueue1 = create_queue();
    cpu->ioWaitingQueue2 = create_queue();
    cpu->ioTimerTime1 = ((rand() % 3) + 3) * timerInitTime;
    cpu->ioTimerTime2 = ((rand() % 3) + 3) * timerInitTime;
    cpu->initialioTimerTime1 = cpu->ioTimerTime1;
    cpu->initialioTimerTime2 = cpu->ioTimerTime2;
    
    cpu->outfile = fopen("discontinuities.txt", "w");
    fprintf(cpu->outfile, "GROUP 9:\nTony Zullo\nJonah Howard\nQuinn Cox\nMehgan Cook\n\n\n");

    cpu->idle = create_pcb(-1, 16, 0);
    cpu->idle->MAX_PC = -1;
    cpu->idle->TERMINATE = 0;
    int i = 0;
    for (; i < 4; i++) {
        cpu->idle->IO_1_TRAPS[i] = -1;
        cpu->idle->IO_2_TRAPS[i] = -1;
    }
    
    cpu->newQueue = create_queue();
    cpu->readyQueue = create_priority_queue();
    
    if (isEmptyPriorityQueue(cpu->readyQueue)) {
        cpu->isRunning = cpu->idle;
    }
    
    initialize(cpu);
    int bool = 1;
    cpu->pidCounter = 1;
    // Each iteration represents one timer quantum
    //if you want to terminate at a set time:
    //cpu->computerTime < max_sys_timer
 //   int me = 0;
    while (1) {
   //     me++;
        cpu->numberOfQuantums++;
        cpu->computerTime++;
        cpu->isRunning->PC++;

        // TODO: priorityBoost occurs after so many quantums
        // TODO: For loop in queue after every # of quantums,
        // we bump up all PCB's with priorityBoost false to true
        // and change priority of PCB to origPriority
        // and change priority of PCB to priority - 1
        // Enqueue and Dequeue to transfer PCB's into new Ready Queues
        // MT
        if (starvationTimer % cpu->numberOfQuantums == 0) {

            fifo_queue_p tempQueue = create_queue();
            int increment = 0;
            for (; increment < NumberOfPriorities; increment++) {
                fifo_queue_p fifo_queue = cpu->readyQueue[i];
                while (!isEmpty(fifo_queue)) {
                    PCB_p pcb = dequeue(cpu->fifo_queue);
                    if (pcb->priorityBoost) {
                        pcb->priorityBoost = 1;
                    } else {
                        pcb->origPriority = pcb->Priority;
                        pcb->Priority = pcb->Priority - 1;
                    }
                    enqueue(tempQueue, pcb);
                }
            }

            while (!isEmpty(tempQueue)){
                enqueue_priority(cpu->readyQueue, dequeue(tempQueue));
            }
        }

        // Determine if the currently running process needs to be terminated
        if (cpu->isRunning->PC >= cpu->isRunning->MAX_PC) {
            cpu->isRunning->PC = 0;
            cpu->isRunning->TERM_COUNT++;
            if (cpu->isRunning->TERMINATE != 0  && cpu->isRunning->TERM_COUNT >= cpu->isRunning->TERMINATE) {
                printf("Process terminated: PID %d at %d\n",cpu->isRunning->pid, cpu->computerTime);
                cpu->isRunning->TERMINATION = cpu->computerTime;
                fprintf(cpu->outfile,"Process terminated: PID %d at %d\n",cpu->isRunning->pid, cpu->computerTime); 
                enqueue(cpu->terminateQueue, cpu->isRunning);
                ReadyQueueToIsRunning(cpu);
                cpu->currentTimerTime = timerInitTime;
            }
        }
        // Check for timer interrupt
        if (timerInterrupt(cpu)) {
            pseudo_isr_timer(cpu);
        } else {
            // Check for IO interrupts
            iointerrupt1(cpu);
            iointerrupt2(cpu);        
            checkForTrapArrays(cpu);
        }
    }
    fclose(cpu->outfile);
}
