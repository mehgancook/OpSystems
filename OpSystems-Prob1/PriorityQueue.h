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
    
fifo_queue *createPriorityQueue();
int addPCB(PCB *thePCB, fifo_queue *thePQ);
PCB_p GetNext(fifo_queue *thePQ);
void PriorityQueuetoString(fifo_queue *thePQ);

#ifdef __cplusplus
}
#endif

#endif /* PRIORITYQUEUE_H */