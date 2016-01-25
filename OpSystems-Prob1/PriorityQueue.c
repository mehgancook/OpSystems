//#include <stdio.h>
//#include <stdlib.h>
//
///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
//#include "PriorityQueue.h"
//
//#define NumberOfPriorities 16
//
//static fifo_queue MainArray[NumberOfPriorities];
//
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
//
//
////used for testing:
////static int IntArray[NumberOfPriorities];
////int *createIntArray() {
////    int i;
////    for (i = 0; i < NumberOfPriorities; i++ ) {
////      //MainArray[i] = (fifo_queue*)malloc(sizeof(fifo_queue));
////      IntArray[i] = i;
////      //MainArray[i] = malloc(sizeof(FifoQueue));
////    }
////    //fifo_queue *theAnswer = (fifo_queue *)MainArray;
////    //theAnswer->startOfArray = (fifo_queue *)MainArray;
////    return IntArray;
////}
//
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
//
////returns the next PCB pointer in the priority queue or null if none in all the queues
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
//
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