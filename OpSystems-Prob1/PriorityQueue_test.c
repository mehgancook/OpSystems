///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
#include <stdio.h>
#include <stdlib.h>
#include "PCB1.h"
#include "fifo_queue.h"
#include "PriorityQueue.h"
//
////void dequeue1(fifo_queue *thePQ) {
////    int random1 = rand();
////    int value1 = (random1 % 6) + 4;
////    int i = 0;
////    while (i < value1) {
////      
////    PCB_p p = GetNext(&thePQ);
////    i++;
////    }
////    PriorityQueuetoString(&thePQ);
////    
////}
//
//
//
void testPriorityQueue() {
    priority_queue_p queue = create_priority_queue();
    int i;
    for(i = 0; i < 30; i++) {
        int random = rand();
        int value = (random % 15) + 1;
        PCB_p pcb = create_pcb(i, value, 0);
        
        enqueue_priority(queue, pcb);
      //  enqueue_priority(queue, pcb);
    }
    priority_queue_to_string(queue);
}


//void testPriorityQueue() {
//    fifo_queue *thePQ = createPriorityQueue();
//    int j = 1;
//    int random = rand();
//    int value = (random % 15) + 1;
//    PCB pcb1 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb1, thePQ);
//    j++;
//    
//
//    
//    
//    random = rand();
//    value = (random % 15) + 1;
//    PCB pcb2 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb2, thePQ);
//    j++;
//    
//
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb3 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb3, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb4 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb4, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb5 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb5, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb6 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb6, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb7 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb7, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb8 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb8, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb9 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb9, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb10 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb10, thePQ);
//    j++;
//    
//    PriorityQueuetoString(thePQ);
//    printf("\n");
//    
//    int r = rand();
//    int va = (r % 5) + 4;
//  //  va = 4;
//    int i = 0;
//    while (i < va) {
//      
//    PCB_p a = GetNext(thePQ);
//    toString(a);
//    i++;
//    }
////    PriorityQueuetoString(thePQ);
// //      printf("\n");
//    
//    
//    
//    
//    
//    
//    PCB pcb11 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb11, thePQ);
//    j++;
//    
//    random = rand();
//    value = (random % 15) + 1;
//    PCB pcb12 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb12, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb13 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb13, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb14 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb14, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb15 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb15, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb16 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb16, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb17 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb17, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb18 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb18, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb19 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb19, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb20 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb20, thePQ);
//    j++;
//    
//    PriorityQueuetoString(thePQ);
//    printf("\n");
//    
//    int r1 = rand();
//    int va1 = (r1 % 5) + 4;
//  //  va = 4;
//    i = 0;
//    while (i < va1) {
//      
//    PCB_p a = GetNext(thePQ);
//    toString(a);
//    i++;
//    }
////    PriorityQueuetoString(thePQ);
////       printf("\n");
//       
//       
//   PCB pcb21 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb21, thePQ);
//    j++;
//    
//    random = rand();
//    value = (random % 15) + 1;
//    PCB pcb22 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb22, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb23 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb23, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb24 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb24, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb25 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb25, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb26 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb26, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb27 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb27, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb28 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb28, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb29 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb29, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb30 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb30, thePQ);
//    j++;
//    
//    PriorityQueuetoString(thePQ);
//    printf("\n");
//    
//    int r2 = rand();
//    int va2 = (r2 % 5) + 4;
//  //  va = 4;
//    i = 0;
//    while (i < va2) {
//      
//    PCB_p a = GetNext(thePQ);
//    toString(a);
//    i++;
//    }
// //   PriorityQueuetoString(thePQ);
// //      printf("\n");
//    
//    
//    
//    
//    
//    
//    PCB pcb31 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb31, thePQ);
//    j++;
//    
//    random = rand();
//    value = (random % 15) + 1;
//    PCB pcb32 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb32, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb33 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb33, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb34 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb34, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb35 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb35, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb36 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb36, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb37 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb37, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb38 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb38, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb39 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb39, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb40 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb40, thePQ);
//    j++;
//    
//    PriorityQueuetoString(thePQ);
//    printf("\n");
//    
//    int r3 = rand();
//    int va3 = (r3 % 5) + 4;
//  //  va = 4;
//    i = 0;
//    while (i < va3) {
//      
//    PCB_p a = GetNext(thePQ);
//    toString(a);
//    i++;
//    }
// //   PriorityQueuetoString(thePQ);
// //      printf("\n");
// 
//           PCB pcb41 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb41, thePQ);
//    j++;
//    
//    
//    random = rand();
//    value = (random % 15) + 1;
//    PCB pcb42 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb42, thePQ);
//    j++;
//    
//
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb43 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb43, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb44 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb44, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb45 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb45, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb46 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb46, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb47 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb47, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb48 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb48, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb49 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb49, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb50 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb50, thePQ);
//    j++;
//    
//    PriorityQueuetoString(thePQ);
//    printf("\n");
//    
//    int r5 = rand();
//    int va5 = (r5 % 6) + 4;
//  //  va = 4;
//    i = 0;
//    while (i < va5) {
//      
//    PCB_p a = GetNext(thePQ);
//    toString(a);
//    i++;
//    }
////    PriorityQueuetoString(thePQ);
// //      printf("\n");
//    
//    
//    
//    
//    
//    
//    PCB pcb51 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb51, thePQ);
//    j++;
//    
//    random = rand();
//    value = (random % 15) + 1;
//    PCB pcb52 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb52, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb53 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb53, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb54 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb54, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb55 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb55, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb56 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb56, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb57 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb57, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb58 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb58, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb59 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb59, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb60 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb60, thePQ);
//    j++;
//    
//    PriorityQueuetoString(thePQ);
//    printf("\n");
//    
//    int r6 = rand();
//    int va6 = (r6 % 6) + 4;
//  //  va = 4;
//    i = 0;
//    while (i < va6) {
//      
//    PCB_p a = GetNext(thePQ);
//    toString(a);
//    i++;
//    }
// //   PriorityQueuetoString(thePQ);
// //      printf("\n");
//       
//       
//   PCB pcb61 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb61, thePQ);
//    j++;
//    
//    random = rand();
//    value = (random % 15) + 1;
//    PCB pcb62 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb62, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb63 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb63, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb64 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb64, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb65 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb65, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb66 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb66, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb67 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb67, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb68 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb68, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb69 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb69, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb70 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb70, thePQ);
//    j++;
//    
//    PriorityQueuetoString(thePQ);
//    printf("\n");
//    
//    int r7 = rand();
//    int va7 = (r7 % 6) + 4;
//  //  va = 4;
//    i = 0;
//    while (i < va7) {
//      
//    PCB_p a = GetNext(thePQ);
//    toString(a);
//    i++;
//    }
// //   PriorityQueuetoString(thePQ);
// //      printf("\n");
//    
//    
//    
//    
//    
//    
//    PCB pcb71 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb71, thePQ);
//    j++;
//    
//    random = rand();
//    value = (random % 15) + 1;
//    PCB pcb72 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb72, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb73 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb73, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb74 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb74, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb75 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb75, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb76 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb76, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb77 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb77, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb78 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb78, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb79 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb79, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb80 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb80, thePQ);
//    j++;
//    
//    PriorityQueuetoString(thePQ);
//    printf("\n");
//    
//    int r8 = rand();
//    int va8 = (r8 % 6) + 4;
//  //  va = 4;
//    i = 0;
//    while (i < va8) {
//      
//    PCB_p a = GetNext(thePQ);
//    toString(a);
//    i++;
//    }
////    PriorityQueuetoString(thePQ);
// //      printf("\n");
// 
//          PCB pcb81 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb81, thePQ);
//    j++;
//    
//    random = rand();
//    value = (random % 15) + 1;
//    PCB pcb82 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb82, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb83 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb83, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb84 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb84, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb85 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb85, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb86 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb86, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb87 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb87, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb88 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb88, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb89 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb89, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb90 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb90, thePQ);
//    j++;
//    
//    PriorityQueuetoString(thePQ);
//    printf("\n");
//    
//    int r9 = rand();
//    int va9 = (r9 % 6) + 4;
//  //  va = 4;
//    i = 0;
//    while (i < va9) {
//      
//    PCB_p a = GetNext(thePQ);
//    toString(a);
//    i++;
//    }
////    PriorityQueuetoString(thePQ);
// //      printf("\n");
//    
//    
//    
//    
//    
//    
//    PCB pcb91 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb91, thePQ);
//    j++;
//    
//    random = rand();
//    value = (random % 15) + 1;
//    PCB pcb92 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb92, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb93 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb93, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb94 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb94, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb95 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb95, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb96 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb96, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb97 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb97, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb98 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb98, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb99 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb99, thePQ);
//    j++;
//    
//        random = rand();
//    value = (random % 15) + 1;
//    PCB pcb100 = {new,j, 0, NULL, value, j, 0};
//    addPCB(&pcb100, thePQ);
//    j++;
//    
//    PriorityQueuetoString(thePQ);
//    printf("\n");
//    
//    int r81 = rand();
//    int va81 = (r81 % 6) + 4;
//  //  va = 4;
//    i = 0;
//    while (i < va81) {
//      
//    PCB_p a = GetNext(thePQ);
//    toString(a);
//    i++;
//    }
//    PriorityQueuetoString(thePQ);
//       printf("\n");
//       
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
// //   dequeue1(&thePQ);
//}
//    
//    
//    
// 