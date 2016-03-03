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
#include <string.h>
#include "PCB1.h"
#include "fifo_queue.h"
#include "PriorityQueue.h"
#include "cpu.h"

#define timerInitTime 300 // Quantum
#define num_pcbs 100
#define quantum 300
#define max_sys_timer 30000

#define starvationTimer 3 // TODO Change to a higher number

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
    if (n < 6) {
        priority = 0;
    } else if (n > 5 && n < 11) {
        priority = 3;
    } else if (n > 10 && n < 21) {
        priority = 2;
    } else {
        priority = 1;
    }
    return priority;
}

PCB_p generatePCB(CPU_p cpu) {
    int prio = generatePriority();
    static int p = num_pcbs + 1;
    PCB_p new = create_pcb(p++, prio, 0);
    if (prio == 0) {
       new->isCIP = 1; 
    }
    new->MAX_PC = (rand() %2001) + 2000;
    new->TERMINATE = (rand() % 31);
    initialize_IO_trap_array(new);  
    enqueue(cpu->newQueue, new);
   // printf("\nPCB created%d!\n");
    cpu->randomGeneratingPcbNumber += (generateRandomNumber(1, 3000) + cpu->computerTime);
}

// Transfer the next PCB from the ready queue to currently running
void ReadyQueueToIsRunning(CPU_p cpu) {
    if (!isEmptyPriorityQueue(cpu->readyQueue)) {
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

//must be done before initialize_IO_trap_array
void initialize_Mutex_trap_array(PCB_p pcb) {
//        int M1[2] = {0};
//        int M2[2] = {0};
    int max = pcb->MAX_PC;
    int midpoint = max/2;
    switch (pcb->pcb_type) {
        case prodcon:
            pcb->MUTEX_1_TRAPS[0] = pcb->MAX_PC/2;  //lock mutex1
            pcb->MUTEX_1_TRAPS[1] = pcb->MAX_PC/2 + 1;  //unlock mutex1
            break;
        case normal:
            break;
        case nondeadlock:
            pcb->MUTEX_1_TRAPS[0] = midpoint;  //lock mutex1
            pcb->MUTEX_2_TRAPS[0] = midpoint + 5;  //lock mutex2      
            pcb->MUTEX_2_TRAPS[1] = midpoint + 10;  //unlock mutex2
            pcb->MUTEX_1_TRAPS[1] = midpoint + 15;  //unlock mutex1
            break;
        case deadlock:
            if (pcb->isMRUA) {
                pcb->MUTEX_1_TRAPS[0] = midpoint;  //lock mutex1
                pcb->MUTEX_2_TRAPS[0] = midpoint + 5;  //lock mutex2      
                pcb->MUTEX_2_TRAPS[1] = midpoint + 10;  //unlock mutex2
                pcb->MUTEX_1_TRAPS[1] = midpoint + 15;  //unlock mutex1
            } else {
                pcb->MUTEX_2_TRAPS[0] = midpoint;  //lock mutex2
                pcb->MUTEX_1_TRAPS[0] = midpoint + 5;  //lock mutex1      
                pcb->MUTEX_1_TRAPS[1] = midpoint + 10;  //unlock mutex1
                pcb->MUTEX_2_TRAPS[1] = midpoint + 15;  //unlock mutex2
            }

            break;
        default:
            break;
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
                //found a random number that is already in the array or in-between the mutex lock and unlock traps
                if (io[j] == random){
                    
                    if (pcb->pcb_type == normal) {
                        break;
                    } else if (pcb->pcb_type == prodcon && (io[j] >= pcb->MUTEX_1_TRAPS[0] && io[j] <= pcb->MUTEX_1_TRAPS[1])) {
                        break;
                    } else if ((pcb->pcb_type == deadlock || pcb->pcb_type == nondeadlock) && //must be deadlock or nondeadlock
                            ((io[j] >= pcb->MUTEX_1_TRAPS[0] && io[j] <= pcb->MUTEX_1_TRAPS[1]) ||
                            (io[j] >= pcb->MUTEX_2_TRAPS[0] && io[j] <= pcb->MUTEX_2_TRAPS[1]))){ 
                        break;
                    } else {
                        break;
                    }
                             
                    
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
            if (zeroCount >= 25) {
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

        fprintf(cpu->outfile, "Process created: PID %d at %d\n", pcb->pid, cpu->computerTime);
        // assign MAX_PC with a random number between 2000 - 4000
        pcb->MAX_PC = (rand() % 2001) + 2000;
        // assign Terminate value with a random number between 0 - 30
        pcb->TERMINATE = (rand() % 31);
        
        // assign IO Trap Arrays 1 & 2 with initializeIOTrapArray();
        initialize_IO_trap_array(pcb);
        enqueue(cpu->newQueue, pcb);
    }
    
    int runProducerConsumerPairs = 1;
    
    if (runProducerConsumerPairs) {
        //int num_prodcons_pairs = 10;
//        int data[num_prodcons_pairs];
//        int signal[num_prodcons_pairs];
        int i;
        for (i = 0; i < cpu->num_prodcons; i++) {
            cpu->data[i] = 0;
            cpu->signal[i] = 0;
        }
        //cpu->dataMutexArray = malloc(num_prodcons_pairs * sizeof(Mutex_p));
        // Mutex_p signalMutexArray[num_prodcons_pairs];
        //cpu->signalMutexArray  = malloc(num_prodcons_pairs * sizeof(Mutex_p));

        int prodcon_num = 0;
       // int total_pcbs = cpu->pidCounter + num_prodcons;
        while (prodcon_num < cpu->num_prodcons) {
            // MT
            // Generate intial priority
            int priority = generatePriority();
            // If priority is 0
            if (priority == 0) {
                // Increment 0 count
                zeroCount += 1;
                // If we have more than 25 PCB's with 0 as a priority
                if (zeroCount >= 25) {
                    // generate a new priority that is not 0
                    while (priority == 0) {
                        priority = generatePriority();
                    }
                }
            }

            //create the Mutexs
            char mutexData_string[20];
            sprintf(mutexData_string, "MutexData%d", prodcon_num);
            
            Mutex_p dataMutex = create_Mutex(&(cpu->data[prodcon_num]), mutexData_string);
            sprintf(mutexData_string, "MutexSig%d", prodcon_num);
            Mutex_p signalMutex = create_Mutex(&(cpu->signal[prodcon_num]), mutexData_string);
            cpu->dataMutexArray[prodcon_num] = dataMutex;
            cpu->signalMutexArray[prodcon_num] = signalMutex;
//            printf("building %d ", prodcon_num);
//            printf("the data from cpu->dataArray %d", cpu->data[prodcon_num]);
//            printf("the data from dataMutex %d", *dataMutex->theData);
            //printf("the data from dataMutexArray %d", (cpu->dataMutexArray[prodcon_num]));
            //printf("the data from dataMutexArray %d", *cpu->dataMutexArray[prodcon_num]->theData);
//            printf("the data from dataMutex %d", *(dataMutex->theData));
            //printf("the data from dataMutexArray %d\n", *(cpu->dataMutexArray[prodcon_num]));
            // create producer
            cpu->priorityCount[priority] += 1;
            char prod_string[10];// = strcat("Prod", prodcon_num);
            sprintf(prod_string, "Prod%d", prodcon_num);
            PCB_p pcb_producer = create_producer(cpu->pidCounter++, priority, 0, prod_string, prodcon_num);
            //printf("the pcb_producer prodcon_num %d ", pcb_producer->prodcon_num);
            // MT
            // If priority was set to 0
            if (priority == 0) {
                // Set isCIP to 1
                pcb_producer->isCIP = 1;
            }

            fprintf(cpu->outfile, "Producer process created: PID %d at %d\n", pcb_producer->pid, cpu->computerTime);
            // assign MAX_PC with a random number between 2000 - 4000
            pcb_producer->MAX_PC = (rand() % 2001) + 2000;
            // assign Terminate value with a random number between 0 - 30
            pcb_producer->TERMINATE = (rand() % 31);

            // assign IO Trap Arrays 1 & 2 with initializeIOTrapArray();
            initialize_IO_trap_array(pcb_producer);
            initialize_Mutex_trap_array(pcb_producer);
            enqueue(cpu->newQueue, pcb_producer);

            // create consumer
            cpu->priorityCount[priority] += 1;
            char con_string[10];// = strcat("Cons", prodcon_num);
            sprintf(con_string, "Cons%d", prodcon_num);
            PCB_p pcb_consumer = create_consumer(cpu->pidCounter++, priority, 0, con_string, prodcon_num);
            //printf("the pcb_consumer prodcon_num %d \n", pcb_consumer->prodcon_num);
            prodcon_num++;
            // MT
            // If priority was set to 0
            if (priority == 0) {
                // Set isCIP to 1
                pcb_consumer->isCIP = 1;
            }

            fprintf(cpu->outfile, "Consumer process created: PID %d at %d\n", pcb_consumer->pid, cpu->computerTime);
            // assign MAX_PC with a random number between 2000 - 4000
            pcb_consumer->MAX_PC = (rand() % 2001) + 2000;
            // assign Terminate value with a random number between 0 - 30
            pcb_consumer->TERMINATE = (rand() % 31);

            // assign IO Trap Arrays 1 & 2 with initializeIOTrapArray();
            initialize_IO_trap_array(pcb_consumer);
            initialize_Mutex_trap_array(pcb_consumer);
            enqueue(cpu->newQueue, pcb_consumer);
        }
    }   
    
       int runMutualResourceUsers = 1;
       int runDeadlock = 0;
    
    if (runMutualResourceUsers) { 
        int i;
        for (i = 0; i < cpu->num_MRUs; i++) {
            cpu->R1[i] = 0;
            cpu->R2[i] = 0;
        }
        int MRU_num = 0;
        while (MRU_num < cpu->num_MRUs) {
            // Generate intial priority
            int priority = generatePriority();
            // If priority is 0
            if (priority == 0) {
                // Increment 0 count
                zeroCount += 1;
                // If we have more than 25 PCB's with 0 as a priority
                if (zeroCount >= 25) {
                    // generate a new priority that is not 0
                    while (priority == 0) {
                        priority = generatePriority();
                    }
                }
            }

            //create the Mutexs
            char mutexR1_string[20];
            sprintf(mutexR1_string, "MutexR1%d", MRU_num);
            
            Mutex_p R1Mutex = create_Mutex(&(cpu->R1[MRU_num]), mutexR1_string);
            sprintf(mutexR1_string, "MutexR2%d", MRU_num);
            Mutex_p R2Mutex = create_Mutex(&(cpu->R2[MRU_num]), mutexR1_string);
            cpu->R1MutexArray[MRU_num] = R1Mutex;
            cpu->R2MutexArray[MRU_num] = R2Mutex;

            // create first of MRU pair "A"
            cpu->priorityCount[priority] += 1;
            char MRUA_string[10];// = strcat("Prod", prodcon_num);
            sprintf(MRUA_string, "MRU A-%d", MRU_num);
            PCB_p pcb_MRUA = create_MRU(cpu->pidCounter++, priority, 0, MRUA_string, MRU_num);
            pcb_MRUA->isMRUA = 1;
            if (runDeadlock) {
                pcb_MRUA->pcb_type = deadlock;
            } else {
                pcb_MRUA->pcb_type = nondeadlock;
            }
            // MT
            // If priority was set to 0
            if (priority == 0) {
                // Set isCIP to 1
                pcb_MRUA->isCIP = 1;
            }

            fprintf(cpu->outfile, "MRU-A process created: PID %d at %d\n", pcb_MRUA->pid, cpu->computerTime);
            // assign MAX_PC with a random number between 2000 - 4000
            pcb_MRUA->MAX_PC = (rand() % 2001) + 2000;
            // assign Terminate value with a random number between 0 - 30
            pcb_MRUA->TERMINATE = (rand() % 31);
            
            initialize_Mutex_trap_array(pcb_MRUA);
            // assign IO Trap Arrays 1 & 2 with initializeIOTrapArray();
            initialize_IO_trap_array(pcb_MRUA);
            enqueue(cpu->newQueue, pcb_MRUA);

            // create second of MRU pair "B"
            cpu->priorityCount[priority] += 1;
            char MRUB_string[10];
            sprintf(MRUB_string, "Cons%d", MRU_num);
            PCB_p pcb_MRUB = create_MRU(cpu->pidCounter++, priority, 0, MRUB_string, MRU_num);
            //printf("the pcb_consumer prodcon_num %d \n", pcb_consumer->prodcon_num);
            pcb_MRUB->isMRUA = 0;
            if (runDeadlock) {
                pcb_MRUB->pcb_type = deadlock;
            } else {
                pcb_MRUB->pcb_type = nondeadlock;
            }
            MRU_num++;
            // MT
            // If priority was set to 0
            if (priority == 0) {
                // Set isCIP to 1
                pcb_MRUB->isCIP = 1;
            }

            fprintf(cpu->outfile, "MRU-B process created: PID %d at %d\n", pcb_MRUB->pid, cpu->computerTime);
            // assign MAX_PC with a random number between 2000 - 4000
            pcb_MRUB->MAX_PC = (rand() % 2001) + 2000;
            // assign Terminate value with a random number between 0 - 30
            pcb_MRUB->TERMINATE = (rand() % 31);

            initialize_Mutex_trap_array(pcb_MRUB);
            // assign IO Trap Arrays 1 & 2 with initializeIOTrapArray();
            initialize_IO_trap_array(pcb_MRUB);
           
            enqueue(cpu->newQueue, pcb_MRUB);
        }
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
        fprintf(cpu->outfile, "Timer interrupt: PID %d was running, PID %d dispatched\n", temp->pid, temp2->pid);
        temp->state = running;
    }
   // printf("%d ", cpu->readyQueue->size);
    cpu->isRunning = temp2;
    // cpu->isRunning->priorityBoost = 1;
 //   toString(cpu->isRunning);
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
            !isEmpty(cpu->ioWaitingQueue1)) {
        cpu->ioTimerTime1 = cpu->initialioTimerTime1;
        fprintf(cpu->outfile, "I/O completion interrupt1: PID %d is running, PID %d put in ready queue\n", cpu->isRunning->pid, cpu->ioWaitingQueue1->head->pcb->pid);
        // MT
   //      printf("I/O completion interrupt1: PID %d is running, PID %d put in ready queue\n", cpu->isRunning->pid, cpu->ioWaitingQueue1->head->pcb->pid);
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
        fprintf(cpu->outfile, "I/O completion interrupt2: PID %d is running, PID %d put in ready queue\n", cpu->isRunning->pid, cpu->ioWaitingQueue2->head->pcb->pid);
     //    printf("I/O completion interrupt2: PID %d is running, PID %d put in ready queue\n", cpu->isRunning->pid, cpu->ioWaitingQueue2->head->pcb->pid);
        // MT
        enqueue_priority(cpu->readyQueue, dequeue(cpu->ioWaitingQueue2));
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
  //  printf("\n%d\n",cpu->newQueue->size);
    while (!isEmpty(cpu->newQueue)) {
        PCB_p pcb = dequeue(cpu->newQueue);
//        toString(pcb);
        //priority_queue_to_string(cpu->readyQueue);
        pcb->state = ready;
        
        enqueue_priority(cpu->readyQueue, pcb);
          //      priority_queue_to_string(cpu->readyQueue);

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

void trapHandler(CPU_p cpu, int trap) {
    if (trap == 1) {
        fprintf(cpu->outfile, "I/O trap request: I/O device 1,");
        enqueue(cpu->ioWaitingQueue1, cpu->isRunning);
     //   ReadyQueueToIsRunning(cpu);
    } else if (trap == 2) {
        fprintf(cpu->outfile, "I/O trap request: I/O device 2,");
        enqueue(cpu->ioWaitingQueue2, cpu->isRunning);
     //   ReadyQueueToIsRunning(cpu);
    } 
    ReadyQueueToIsRunning(cpu);
}

int mutexTrapHandler(CPU_p cpu, int trap) {
    int switched = 0;
    int gotLock = 1;
    if (trap == 1) {
        gotLock = Lock(cpu->R1MutexArray[cpu->isRunning->MRU_num], cpu->isRunning, cpu->outfile);
    } else if (trap == 2) {
        //fprintf(cpu->outfile, "Mutex trap request: UnLock R1,");
        unLock(cpu->R1MutexArray[cpu->isRunning->MRU_num], cpu->isRunning, cpu->readyQueue);
    } else if (trap == 3) {
        //fprintf(cpu->outfile, "Mutex trap request: Lock R2,");
        gotLock = Lock(cpu->R2MutexArray[cpu->isRunning->MRU_num], cpu->isRunning, cpu->outfile);
    } else if (trap == 4) {
        //fprintf(cpu->outfile, "Mutex trap request: UnLock R2,");
        unLock(cpu->R2MutexArray[cpu->isRunning->MRU_num], cpu->isRunning, cpu->readyQueue);
    } 
 
    if (!gotLock) {
        ReadyQueueToIsRunning(cpu);
        switched = 1;
    }
    return switched;
}

// Checks if an I/O interrupt has occurred 

void checkForTrapArrays(CPU_p cpu) {
    int i = 0;
    if (!cpu->isRunning->isCIP) {
        for (; i < 4; i++) {
            if (cpu->isRunning->IO_1_TRAPS[i] == cpu->isRunning->PC) {
                trapHandler(cpu, 1);
                break;
            } else if (cpu->isRunning->IO_2_TRAPS[i] == cpu->isRunning->PC) {
                trapHandler(cpu, 2);
                break;
            }
        }
    }
}

int checkForMRUMutexArrays(CPU_p cpu) {
    int switched = 0;
    int i = 0;
    if (cpu->isRunning->MUTEX_1_TRAPS[0] == cpu->isRunning->PC) {
        switched = mutexTrapHandler(cpu, 1);
    } else if (cpu->isRunning->MUTEX_1_TRAPS[1] == cpu->isRunning->PC) {
        switched = mutexTrapHandler(cpu, 2);
    } else if (cpu->isRunning->MUTEX_2_TRAPS[0] == cpu->isRunning->PC) {
        switched = mutexTrapHandler(cpu, 3);
    } else if (cpu->isRunning->MUTEX_2_TRAPS[1] == cpu->isRunning->PC) {
        switched = mutexTrapHandler(cpu, 4);
    }
    return switched;
}

int checkForProdConMutexArrays(CPU_p cpu) {
    
}

int threadConditionWait(PCB_p thePCB, CPU_p cpu, condition_type theCondition, Mutex_p theMutex) {
    int answer = 0;
    
    return answer;
}

int threadConditionSignal(CPU_p cpu, condition_type theCondition) {
    int answer = 0;
    
    return answer;
}


//this is the basic producer consumer
int processProdCon(PCB_p thePCB, CPU_p cpu) {
    int switchedToNewPCB = 0;
    //printf("processProdCon ");
    //printf("pid: %d PC: %d ", thePCB->pid, thePCB->PC);
    //printf(" the data %d ", *cpu->dataMutexArray[thePCB->prodcon_num]->theData);
    if(thePCB->isProducer) {
        //printf("isProducer %d ", thePCB->prodcon_num);
        //try to get a lock on the signal
        Mutex_p signalMutex = (cpu->signalMutexArray)[(thePCB->prodcon_num)];
        if (Lock(signalMutex, thePCB)) {
            //printf("gotLock on signal %d ", *cpu->signalMutexArray[thePCB->prodcon_num]->theData);
            //you have the lock on mutex signal check if it is 1 for write
            if (*cpu->signalMutexArray[thePCB->prodcon_num]->theData == 1) {
                //printf(" signal = 1 for producer ");
                //if so get lock on dataMutex
                if (Lock(cpu->dataMutexArray[thePCB->prodcon_num], thePCB)) {                    
                    //once locked on data add one to the data and change signal bit
                    //printf("before writting the data %d ", *cpu->dataMutexArray[thePCB->prodcon_num]->theData);
                    (*cpu->dataMutexArray[thePCB->prodcon_num]->theData) += 1;
                    //printf("wrote the data %d ", *cpu->dataMutexArray[thePCB->prodcon_num]->theData);
                    printf("producer %d wrote the data it is now %d \n", thePCB->prodcon_num, *cpu->dataMutexArray[thePCB->prodcon_num]->theData);
                    *cpu->signalMutexArray[thePCB->prodcon_num]->theData = 0;
                    //printf("wrote the signal %d ", *cpu->signalMutexArray[thePCB->prodcon_num]->theData);
                    //release data and signal mutex
                    unLock(cpu->dataMutexArray[thePCB->prodcon_num], thePCB, cpu->readyQueue);
                    unLock(cpu->signalMutexArray[thePCB->prodcon_num], thePCB, cpu->readyQueue);
                } else {
                    //you didn't get the lock so you are in the dataMutex waiting queue
                    //but you also have a lock on the signalMutex
                    ReadyQueueToIsRunning(cpu);
                    switchedToNewPCB = 1;
                }
            } else {
                //printf("signal = 0 for producer");
                //if the signal is 0, release the mutex for signal
                unLock(cpu->signalMutexArray[thePCB->prodcon_num], thePCB, cpu->readyQueue);
            }
        } else {
            //you didn't get the lock so you are in the signalMutex waiting queue
            ReadyQueueToIsRunning(cpu);
            switchedToNewPCB = 1;
        }
    } else { //you are consumer
        //printf("isConsumer %d ", thePCB->prodcon_num);
        //try to get a lock on the signal
        if (Lock(cpu->signalMutexArray[thePCB->prodcon_num], thePCB)) {
            //printf("gotLock on signal ");
            //you have the lock on mutex signal check if it is 0 for read
            if (*cpu->signalMutexArray[thePCB->prodcon_num]->theData == 0) {
                //printf("signal = 0 for consumer");
                //if so get lock on dataMutex
                if (Lock(cpu->dataMutexArray[thePCB->prodcon_num], thePCB)) {
                    //once locked on data read the data and change signal bit
                    int temp = *cpu->dataMutexArray[thePCB->prodcon_num]->theData;
                    //
                    //printf("read the data %d", temp);
                    printf("consumer %d read the data it is currently %d \n", thePCB->prodcon_num, *cpu->dataMutexArray[thePCB->prodcon_num]->theData);
                    
                    *cpu->signalMutexArray[thePCB->prodcon_num]->theData = 1;
                    //release data and signal mutex
                    unLock(cpu->dataMutexArray[thePCB->prodcon_num], thePCB, cpu->readyQueue);
                    unLock(cpu->signalMutexArray[thePCB->prodcon_num], thePCB, cpu->readyQueue);
                } else {
                    //you didn't get the lock so you are in the dataMutex waiting queue
                    //but you also have a lock on the signalMutex
                    ReadyQueueToIsRunning(cpu);
                    switchedToNewPCB = 1;
                }
            } else {
                //printf("signal = 1 for consumer");
                //if the signal is 1, release the mutex for signal
                unLock(cpu->signalMutexArray[thePCB->prodcon_num], thePCB, cpu->readyQueue);
            }
        } else {
            //you didn't get the lock so you are in the signalMutex waiting queue
            ReadyQueueToIsRunning(cpu);
            switchedToNewPCB = 1;
        }
    }
    //printf(" the data %d ", *cpu->dataMutexArray[thePCB->prodcon_num]->theData);
    //printf("end processProdCon\n");
    return switchedToNewPCB;
}

/*
 * Runs the program and simulates the CPU 
 */
void run(CPU_p cpu) {
    cpu->pidCounter = 0;
    cpu->computerTime = 0;
    cpu->currentTimerTime = timerInitTime;
    cpu->systack_pc = 0;
    cpu->cpu_pc = 0;
    cpu->fourth_context_switching = 1;
    cpu->randomGeneratingPcbNumber = generateRandomNumber(1,3000);

    // MT number of current quantums
    cpu->numberOfQuantums = 1;

    cpu->terminateQueue = create_queue();
    cpu->ioWaitingQueue1 = create_queue();
    cpu->ioWaitingQueue2 = create_queue();
    
    cpu->num_prodcons = 10;
    cpu->dataMutexArray = (Mutex_p *) malloc(cpu->num_prodcons * sizeof(Mutex_p));
    cpu->signalMutexArray =(Mutex_p *) malloc(cpu->num_prodcons * sizeof(Mutex_p));
    cpu->data = malloc(cpu->num_prodcons * sizeof(int));
    cpu->signal = malloc(cpu->num_prodcons * sizeof(int));
    
    cpu->num_MRUs = 10;
    cpu->R1MutexArray = (Mutex_p *) malloc(cpu->num_MRUs * sizeof(Mutex_p));
    cpu->R2MutexArray =(Mutex_p *) malloc(cpu->num_MRUs * sizeof(Mutex_p));
    cpu->R1 = malloc(cpu->num_MRUs * sizeof(int));
    cpu->R2 = malloc(cpu->num_MRUs * sizeof(int));

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
    int ijk = 0;
    //1504 run time is the last time this works.
    while (cpu->computerTime < max_sys_timer) {
        //     me++;
        ijk++;

        if (cpu->randomGeneratingPcbNumber == ijk) {
            generatePCB(cpu);
        }
      //  printf("%d ", ijk);
        if (cpu->computerTime % quantum == 0) {
            cpu->numberOfQuantums++;

            // Changed T.ZULLO             
            // fifo_queue_p tempQueue = create_queue();
            // while(!isEmptyPriorityQueue(cpu->readyQueue)) {
            //     PCB_p pcb = dequeue_priority(cpu->readyQueue);
            //   //  toString(pcb);
            //     if (pcb->Priority != pcb->origPriority) {
            //         pcb->Priority = pcb->origPriority;        
            //     }
            //     enqueue(tempQueue, pcb);
            // }
            // while (!isEmpty(tempQueue)) {
            //    enqueue_priority(cpu->readyQueue, dequeue(tempQueue));
            // }
        }
        
      //  cpu->numberOfQuantums++;
        cpu->computerTime++;
       // printf("%d ",cpu->computerTime);      

        // TODO: priorityBoost occurs after so many quantums
        // TODO: For loop in queue after every # of quantums,
        // we bump up all PCB's with priorityBoost false to true
        // and change priority of PCB to origPriority
        // and change priority of PCB to priority - 1
        // Enqueue and Dequeue to transfer PCB's into new Ready Queues
        // MT
        if (cpu->numberOfQuantums % starvationTimer == 0) {
//
            printf("Boosting for Starvation\n");

            fifo_queue_p tempQueue = create_queue();
           // printf("QUEUE BEFORE ADJUSTING PRIORITY LEVEL DUE TO STARVATION\n");
           // priority_queue_to_string(cpu->readyQueue);
            while(!isEmptyPriorityQueue(cpu->readyQueue)) {
                PCB_p pcb = dequeue_priority(cpu->readyQueue);
              //  toString(pcb);
                if (!pcb->priorityBoost) {
                    pcb->origPriority = pcb->Priority;
                    if (pcb->Priority != 0)
                        pcb->Priority = pcb->Priority - 1;        
                }
                pcb->priorityBoost = 0;
                enqueue(tempQueue, pcb);
            }
           // priority_queue_to_string(cpu->readyQueue);
        //    printf("\n%d\n",tempQueue->size );
            while (!isEmpty(tempQueue)) {
                PCB_p pcb2 = tempQueue->head->pcb;
               // toString(pcb2);
               enqueue_priority(cpu->readyQueue, dequeue(tempQueue));
            }
          //  printf("QUEUE AFTER ADJUSTING PRIORITY LEVEL DUE TO STARVATION\n");
          //  priority_queue_to_string(cpu->readyQueue);
            cpu->numberOfQuantums = 1;
        }

        // Determine if the currently running process needs to be terminated
        if (cpu->isRunning->PC >= cpu->isRunning->MAX_PC) {
            cpu->isRunning->PC = 0;                
           // printf("Process terminated: PID %d at %d\n", cpu->isRunning->pid, cpu->computerTime);

            cpu->isRunning->TERM_COUNT++;
            if (cpu->isRunning->TERMINATE != 0 && cpu->isRunning->TERM_COUNT >= cpu->isRunning->TERMINATE) {
                printf("Process terminated: PID %d at %d\n", cpu->isRunning->pid, cpu->computerTime);
                cpu->isRunning->TERMINATION = cpu->computerTime;
                fprintf(cpu->outfile, "Process terminated: PID %d at %d\n", cpu->isRunning->pid, cpu->computerTime);
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
        int switched = 0;
        if (cpu->isRunning->isProdCon) {
            switched = processProdCon(cpu->isRunning, cpu);
        } 
        
        if (!switched && (cpu->isRunning->pcb_type == deadlock || cpu->isRunning->pcb_type == nondeadlock)) {
            switched = checkForMRUMutexArrays(cpu);
        }
        
        if (!switched) {
            cpu->isRunning->PC++;
        }
//        fclose(cpu->outfile);
//        cpu->outfile = fopen("discontinuities.txt", "a");
//                if (cpu->numberOfQuantums % starvationTimer == 0) {
////
//            fifo_queue_p tempQueue = create_queue();
//            priority_queue_to_string(cpu->readyQueue);
//            while(!isEmptyPriorityQueue(cpu->readyQueue)) {
//                PCB_p pcb = dequeue_priority(cpu->readyQueue);
//              //  toString(pcb);
//                if (!pcb->priorityBoost) {
//                    pcb->origPriority = pcb->Priority;
//                    pcb->Priority = pcb->Priority - 1;        
//                }
//                pcb->priorityBoost = 0;
//                enqueue(tempQueue, pcb);
//            }
//            priority_queue_to_string(cpu->readyQueue);
//            printf("\n%d\n",tempQueue->size );
//            while (!isEmpty(tempQueue)) {
//                PCB_p pcb2 = tempQueue->head->pcb;
//               // toString(pcb2);
//               enqueue_priority(cpu->readyQueue, dequeue(tempQueue));
//            }
//            priority_queue_to_string(cpu->readyQueue);
//            cpu->numberOfQuantums = 1;
//        }
    }
    fclose(cpu->outfile);
}

