/* 
 * File:   PriorityQueue.h
 * Author: Cox Family
 *
 * Created on January 8, 2016, 1:56 PM
 */

#include "fifo_queue.h"

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#define NumberOfPriorities 4    
    
typedef struct priority_queue {
        fifo_queue_p MainArray[NumberOfPriorities];
} priority_queue;

typedef priority_queue *priority_queue_p;


       
priority_queue_p create_priority_queue();
void enqueue_priority(priority_queue_p queue, PCB_p block);
PCB_p dequeue_priority(priority_queue_p queue);
void priority_queue_to_string(priority_queue_p queue);


//fifo_queue *createPriorityQueue();
//int addPCB(PCB *thePCB, fifo_queue *thePQ);
//PCB_p GetNext(fifo_queue *thePQ);
//void PriorityQueuetoString(fifo_queue *thePQ);

#ifdef __cplusplus
}
#endif

#endif /* PRIORITYQUEUE_H */