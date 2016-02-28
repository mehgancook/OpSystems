/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 *  File:   Mutex.h
 *  Author: Mehgan Cook
 *          Jonah Howard
 *          Tony Zullo
 *          Quinn Cox
 * 
 * Created on February 24, 2016, 2:24 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "PCB1.h"
#include "PriorityQueue.h"


#ifndef MUTEX_H
#define MUTEX_H
#define LENGTH_OF_NAME 20

#ifdef __cplusplus
extern "C" {
#endif


    
typedef struct mutex {
    char name[LENGTH_OF_NAME];
    int *theData;
    int locked;
    PCB_p owner;
    fifo_queue_p waitingQueue;
} Mutex;

typedef Mutex *Mutex_p;

Mutex_p create_Mutex(int *theData, char *theName);

PCB_p get_Owner(Mutex_p theMutex);

int tryLock(Mutex_p theMutex, PCB_p theLocker);

void unLock(Mutex_p theMutex, PCB_p theLocker, priority_queue_p theReadyQueue);


#ifdef __cplusplus
}
#endif

#endif /* MUTEX_H */

