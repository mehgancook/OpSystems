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
#define max_sys_timer 300000


// Transfer the next PCB from the ready queue to currently running
void ReadyQueueToIsRunning(CPU_p cpu) {
    if (!isEmpty(cpu->readyQueue)) {
        fprintf(cpu->outfile, "PID %d put into waiting queue, PID %d dispatched\n", cpu->isRunning->pid, cpu->readyQueue->head->pcb->pid);
        cpu->isRunning = dequeue(cpu->readyQueue);
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
        if (!isEmpty(cpu->readyQueue)) {
          //  fprintf(cpu->outfile, "This pcb has been enqueued to the ready queue\n");
           // printToFile(cpu->outfile, pcb);
        } else {
            cpu->isRunning = cpu->idle;
        }
        enqueue(cpu->readyQueue, cpu->isRunning);
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
    int i = rand();
    i = (i % 5) + 1;
   // for (;i > 0 && pidCounter < num_pcbs; i--) {
    while (cpu->pidCounter < num_pcbs) {
        PCB_p pcb = create_pcb(cpu->pidCounter++, 0, 0);
        fprintf(cpu->outfile,"Process created: PID %d at %d\n", pcb->pid, cpu->computerTime);
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
        fprintf(cpu->outfile,"Timer interrupt: PID %d was running, PID %d dispatched\n", temp->pid, temp2->pid);
       // fprintf(cpu->outfile, "\nRunning PCB:\n");
        temp->state = running;
       // printToFile(cpu->outfile, temp);
       // fprintf(cpu->outfile, "Switching to:\n");
       // printToFile(cpu->outfile, temp2);
    }
    cpu->isRunning = temp2;
    cpu->systack_pc = cpu->isRunning->PC;
    cpu->isRunning->state = running;
    temp->state = ready;
    if (bool) {
     //   fprintf(cpu->outfile, "New content of PCBs\n");
     //   printToFile(cpu->outfile, temp);
     //   printToFile(cpu->outfile, cpu->isRunning);
     //   to_file_enqueue(cpu->outfile, cpu->readyQueue);
     //   fprintf(cpu->outfile, "\n");
    }
    cpu->fourth_context_switching++;
    return;
}

// Simulates a timer interrupt. Returns 1 if a timer interrupt has occurred,
// 0 otherwise.
int timerInterrupt(CPU_p cpu) {
    cpu->currentTimerTime--;
 //   cpu->currentTimerTime--;
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
    if (cpu->ioTimerTime1 <= 0 && !isEmpty(cpu->ioWaitingQueue1)) {
        cpu->ioTimerTime1 = cpu->initialioTimerTime1;
        fprintf(cpu->outfile,"I/O completion interrupt1: PID %d is running, PID %d put in ready queue\n", cpu->isRunning->pid, cpu->ioWaitingQueue1->head->pcb->pid);
        enqueue(cpu->readyQueue, dequeue(cpu->ioWaitingQueue1));
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
        enqueue(cpu->readyQueue, dequeue(cpu->ioWaitingQueue2));
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
      //  fprintf(cpu->outfile, "This pcb has been enqueued to the ready queue\n");
      //  printToFile(cpu->outfile, pcb);
        enqueue(cpu->readyQueue, pcb);
    }
    if (interruption == timer) {
        cpu->isRunning->state = ready;
        if (cpu->isRunning != cpu->idle) {
            PCB_p pcb = cpu->isRunning;
         //   fprintf(cpu->outfile, "This pcb has been enqueued to the ready queue\n");
         //   printToFile(cpu->outfile, pcb);
            enqueue(cpu->readyQueue, cpu->isRunning);
        }
    }
    dispatcher(cpu);
    return;
}

// Simulates an isr timer and calls the scheduler.
void pseudo_isr_timer(CPU_p cpu) {
    cpu->isRunning->state = interrupted;
    //cpu->isRunning->PC = cpu->systack_pc;
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
    cpu->pidCounter= 0;
    cpu->computerTime = 0;
    cpu->currentTimerTime = timerInitTime;
    cpu->systack_pc = 0;
    cpu->cpu_pc = 0;
    cpu->fourth_context_switching = 1;
    cpu->terminateQueue = create_queue();
    cpu->ioWaitingQueue1 = create_queue();
    cpu->ioWaitingQueue2 = create_queue();
    cpu->ioTimerTime1 = ((rand() % 3) + 3) * timerInitTime;
    cpu->ioTimerTime2 = ((rand() % 3) + 3) * timerInitTime;
    cpu->initialioTimerTime1 = cpu->ioTimerTime1;
    cpu->initialioTimerTime2 = cpu->ioTimerTime2;
    
    cpu->outfile = fopen("discontinuities.txt", "w");
    fprintf(cpu->outfile, "GROUP 9:\nTony Zullo\nJonah Howard\nQuinn Cox\nMehgan Cook\n\n\n");

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
    cpu->pidCounter = 1;
    // Each iteration represents one timer quantum
    //computerTime < max_sys_timer
    //cpu->computerTime < max_sys_timer
    while (1) {
        cpu->computerTime++;
        cpu->isRunning->PC++;

      //printf("MAX: %d PC: %d\n", cpu->isRunning->MAX_PC, cpu->isRunning->PC);
        //          fprintf(cpu->outfile, "\n\n\n\PC %d MAX PC %d TERMINATE %d TERM COUNT %d",cpu->isRunning->PC, cpu->isRunning->MAX_PC, cpu->isRunning->TERMINATE, cpu->isRunning->TERM_COUNT);
        // Determine if the currently running process needs to be terminated
        if (cpu->isRunning->PC >= cpu->isRunning->MAX_PC) {
            fprintf(cpu->outfile, "DO I MAKE IT HERE\n");
            cpu->isRunning->PC = 0;
            cpu->isRunning->TERM_COUNT++;
            if (cpu->isRunning->TERMINATE != 0  && cpu->isRunning->TERM_COUNT >= cpu->isRunning->TERMINATE) {
                fprintf(cpu->outfile, "WILL I MAKE IT HERE\n");
                printf("Process terminated: PID %d at %d\n",cpu->isRunning->pid, cpu->computerTime);
                cpu->isRunning->TERMINATION = cpu->computerTime;
                fprintf(cpu->outfile,"Process terminated: PID %d at %d\n",cpu->isRunning->pid, cpu->computerTime); 
                enqueue(cpu->terminateQueue, cpu->isRunning);
                ReadyQueueToIsRunning(cpu);
                cpu->computerTime = timerInitTime;
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
