/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Mutex.h"
#include "cpu.h"

#define LENGTH_OF_NAME 20


//void dead_lock_detect(Mutex_p *R1MutexArray, Mutex_p *R2MutexArray, CPU_p cpu) {
//    int flag = 1;
//    for (int i = 0; i < cpu->num_MRUs; i++, R1MutexArray++, R2MutexArray++) {
//        if (*R1MutexArray->locked && *R2MutexArray->locked && (*R1MutexArray->owner != *R2MutexArray->owner)) {
//            fprintf(cpu->outfile, "Deadlock detected for processes PID%d and PID%d\n", *R1MutexArray->owner, *R2MutexArray->owner);
//            *R1MutexArray->locked = 0;
//            unLock(*R1MutexArray, *R1MutexArray->owner, cpu->readyQueue);
//            flag = 0;
//        }
//    }
//    if (flag) {
//        fprintf(cpu->outfile, "No deadlock detected");
//    }
//}

Mutex_p create_Mutex(int *theData, char *theName){
    Mutex_p newMutex = malloc(sizeof (Mutex));       
    strcpy(newMutex->name,theName);
    //printf(newMutex->name);
    //printf(" create_Mutex;\n");
    newMutex->theData = theData;
    newMutex->locked = 0;
    newMutex->owner = NULL;
    newMutex->waitingQueue = create_queue();     
    return newMutex;
}

PCB_p get_Owner(Mutex_p theMutex){
    return theMutex->owner;    
}

int Lock(Mutex_p theMutex, PCB_p theLocker, FILE *theFile){
    int answer = 0; //0 is didn't get lock
    char string[80];
    //printf("\n theFile %p\n",theFile);
    if (theMutex->owner == NULL) {
        theMutex->owner = theLocker;
        answer = 1;
        sprintf(string, "PID %d: requested lock on mutex %s - succeeded\n", theLocker->pid, theMutex->name);
        fprintf(theFile, string);
        printf("%s", string);
        theMutex->locked = 1;
    } else if (theMutex->owner == theLocker) {
        answer = 1;
    } else {
        enqueue(theMutex->waitingQueue, theLocker);
        sprintf(string, "PID %d: requested lock on mutex %s - blocked by PID %d\n", theLocker->pid, theMutex->name, theMutex->owner->pid);
        fprintf(theFile, string);
        printf("%s", string);
    }

    return answer;
}

void unLock(Mutex_p theMutex, PCB_p theLocker, priority_queue_p theReadyQueue){
    if (theMutex->owner = theLocker) {
        if (isEmpty(theMutex->waitingQueue)) {
            theMutex->owner = NULL;
            theMutex->locked = 0;
        } else {
            theMutex->owner = dequeue(theMutex->waitingQueue); 
            enqueue_priority(theReadyQueue, theMutex->owner);
        }                   
    }
}

