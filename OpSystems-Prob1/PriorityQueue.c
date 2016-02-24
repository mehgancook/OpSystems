#include <stdio.h>
#include <stdlib.h>

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PriorityQueue.h"

//#define NumberOfPriorities 16

//static fifo_queue MainArray[NumberOfPriorities];

//priority_queue_p create_queue();

priority_queue_p create_priority_queue() {
    int i;
    priority_queue_p pq  = malloc(sizeof(fifo_queue_p) * NumberOfPriorities);
    for (i = 0; i < NumberOfPriorities; i++) {
        pq->MainArray[i] = create_queue();    
    }
    pq->size = 0;
    return pq;
}

//fifo_queue *createPriorityQueue() {
//    int i;
//    for (i = 0; i < NumberOfPriorities; i++ ) {
//      //MainArray[i] = (fifo_queue*)malloc(sizeof(fifo_queue));
//      MainArray[i] = *create_queue();
//      //MainArray[i] = malloc(sizeof(FifoQueue));
//    }
//    //fifo_queue *theAnswer = (fifo_queue *)MainArray;
//    //theAnswer->startOfArray = (fifo_queue *)MainArray;
//    return MainArray;
//}


//used for testing:
//static int IntArray[NumberOfPriorities];
//int *createIntArray() {
//    int i;
//    for (i = 0; i < NumberOfPriorities; i++ ) {
//      //MainArray[i] = (fifo_queue*)malloc(sizeof(fifo_queue));
//      IntArray[i] = i;
//      //MainArray[i] = malloc(sizeof(FifoQueue));
//    }
//    //fifo_queue *theAnswer = (fifo_queue *)MainArray;
//    //theAnswer->startOfArray = (fifo_queue *)MainArray;
//    return IntArray;
//}

//void enqueue(priority_queue_p queue, PCB_p block);
//PCB_p dequeue(priority_queue_p queue);void enqueue(priority_queue_p queue, PCB_p block);
//PCB_p dequeue(priority_queue_p queue);

void enqueue_priority(priority_queue_p queue, PCB_p block) {
    int answer = 0;
    
    if (block->Priority >= 0 && block->Priority < NumberOfPriorities) {
      //  printf("%d ", block->Priority);
      //    to_string_enqueue(queue->MainArray[block->Priority]);
        enqueue(queue->MainArray[block->Priority], block);
        queue->size += 1;
    }
}

PCB_p dequeue_priority(priority_queue_p queue) {
    int keepGoing = 1;
    int priorityCounter = 0;
    PCB_p answerPCB;
    while (keepGoing && priorityCounter < NumberOfPriorities) {
        if (!isEmpty(queue->MainArray[priorityCounter])) {
            answerPCB = dequeue(queue->MainArray[priorityCounter]);
            keepGoing = 0;
        }
        priorityCounter++;
    }
    
    if (keepGoing) {
        printf("priority Queue is Empty!");
    }
    queue->size -= 1;
    return answerPCB;
}

int isEmptyPriorityQueue(priority_queue_p queue) {
    int i = 0;
    int flag = 1;
    while (i < NumberOfPriorities) {
        if (!isEmpty(queue->MainArray[i])) {
            flag = 0;           
        }
        i++;
    }
    return flag;
}


//returns the next PCB pointer in the priority queue or null if none in all the queues
//PCB_p GetNext(fifo_queue *theArray) {
//    //fifo_queue *theArray = thePQ->startOfArray;
//    int keepGoing = 1;
//    int priorityCounter = 0;
//    PCB_p answerPCB;
//    
//    while (keepGoing && priorityCounter < NumberOfPriorities) {
//        if (!is_empty((theArray + priorityCounter))) {
//            answerPCB = dequeue((theArray + priorityCounter));
//            keepGoing = 0;
//        }        
//        priorityCounter++;
//    }
//    if (keepGoing) {
//        printf("Priority Queue is Empty\n");
//    }   
//    return answerPCB;
//}




//void enqueue(fifo_queue_p queue, PCB_p block);
//PCB_p dequeue(fifo_queue_p queue);
//PCB_p peek(fifo_queue_p queue);
//int isEmpty(fifo_queue_p queue);void enqueue(fifo_queue_p queue, PCB_p block);
//PCB_p dequeue(fifo_queue_p queue);
//PCB_p peek(fifo_queue_p queue);
//int isEmpty(fifo_queue_p queue);



//int addPCB(PCB *thePCB, fifo_queue *theArray) {
//    //fifo_queue *theArray = thePQ->startOfArray;
//    int answer = 0;
//    if (thePCB->Priority > 0 && thePCB->Priority < NumberOfPriorities) {
//        enqueue((theArray + thePCB->Priority), thePCB); 
//        answer = 1;
//    } else {
//        printf("Tried to add PCB with out of bounds priority.\n");
//    }
//    return answer;
//}

//returns the next PCB pointer in the priority queue or null if none in all the queues
//PCB_p GetNext(fifo_queue *theArray) {
//    //fifo_queue *theArray = thePQ->startOfArray;
//    int keepGoing = 1;
//    int priorityCounter = 0;
//    PCB_p answerPCB;
//    
//    while (keepGoing && priorityCounter < NumberOfPriorities) {
//        if (!is_empty((theArray + priorityCounter))) {
//            answerPCB = dequeue((theArray + priorityCounter));
//            keepGoing = 0;
//        }        
//        priorityCounter++;
//    }
//    if (keepGoing) {
//        printf("Priority Queue is Empty\n");
//    }   
//    return answerPCB;
//}

void priority_queue_to_string(priority_queue_p queue) {
    int i;
    for(i = 0; i < NumberOfPriorities; i++) {
        printf("Q%d", i);
        fifo_queue_p tempQueue = create_queue();
        fifo_queue_p cue = queue->MainArray[i];
        while (!isEmpty(cue)) {
            PCB_p temp = dequeue(cue);
            printf("P%d", temp->pid);
            enqueue(tempQueue, temp);
            if (!isEmpty(cue)) {
                printf("->");
            } else {
                printf("-");
            }
        }
        printf("*");
        while (!isEmpty(tempQueue)) {
            enqueue(cue, dequeue(tempQueue));
        }
        printf("\n");
    }
}

//void PriorityQueuetoString(fifo_queue *theArray) {
//    //fifo_queue *theArray = thePQ->startOfArray;
//    int i;
//    for (i = 0; i < NumberOfPriorities; i++ ) {
//        printf("Q%d:", i);
//        //FIFOQueuetoString((theArray + i));
//         fifo_queue *tempqueue = create_queue();
//         fifo_queue *queue = &theArray[i];
//    //printf("is_empty %d", is_empty(queue));
//    //printf("not is_empty %d", !is_empty(queue));
//    while (!is_empty(queue)) {
//        
//        //printf("size before dequeue %d", get_size(queue));
//        PCB_p temp = dequeue(queue);
//        //toStringShort(temp);
//        printf("P%d", temp->pid);
//        enqueue(tempqueue, temp);
//        if (!is_empty(queue)){
//            printf("->");
//        } else {
//            printf("-");    
//        }
//    }
//    printf("*");
//    //put the data back in the original queue
//    while (!is_empty(tempqueue)) {
//        enqueue(queue, dequeue(tempqueue));
//    }
//        printf("\n");
//    }
//}