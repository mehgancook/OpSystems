/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "fifo_queue.h"
#include "fifo_queue_test.h"
#include "PCB.h"

void testFIFO() {
    fifo_queue_p q = create_queue();
    int j = 0;
    int i = 0;
    while (i < 5) {
        PCB_p pcb = create_pcb(i, 0);
        enqueue(q, pcb);
        i++; j++;
          to_string_enqueue(q);
    }
    //   to_string_enqueue(q);
//    PCB pcb1 ={ new, 10, 0, 0, 3, 1, 0};
//    PCB_p one = &pcb1;
//    PCB pcb2 = {new, 1, 0, 0, 15, 75, 0};
//    PCB_p two = &pcb2;
//    PCB pcb3 = {new, 2, 0, 0, 14, 3, 0};
//    PCB_p three = &pcb3;
//    enqueue(q, one);
//    to_string_enqueue(q);
//    enqueue(q, two);
//    to_string_enqueue(q);
//    enqueue(q, three);
//    to_string_enqueue(q);
//      
//   
//   PCB pcb4 = {new, 3, 0, 0, 13, 65, 0};
//     PCB_p four = &pcb4;
//     enqueue(q, four);
//         to_string_enqueue(q);
//
//    PCB pcb5 = {new, 12, 0, 0, 12, 55, 0};
//     PCB_p five = &pcb5;
//     enqueue(q, five);
//         to_string_enqueue(q);
//     
//    PCB pcb6 = {new, 5, 0, 0, 11, 45, 0};
//         PCB_p six = &pcb6;
//     enqueue(q, six);
//         to_string_enqueue(q);
//
//    PCB pcb7 = {new, 6, 0, 0, 10, 6, 0};
//         PCB_p seven = &pcb7;
//     enqueue(q, seven);
//         to_string_enqueue(q);
//
//    PCB pcb8 = {new, 7, 0, 0, 9, 15, 0};
//         PCB_p eight = &pcb8;
//     enqueue(q, eight);
//         to_string_enqueue(q);
//
//    PCB pcb9 = {new, 8, 0, 0, 1, 25, 0};
//         PCB_p nine = &pcb9;
//     enqueue(q, nine);
//         to_string_enqueue(q);
//
//   PCB pcb10 = {new,9, 0, 0, 5, 35, 0};
//   PCB_p ten = &pcb10;
//   enqueue(q, ten);
//   to_string_enqueue(q);
//   
//   PCB_p p = peek(q); 
//   
//   printf("TESTING THE PEEK FUNCTION, The dequeue testing tests the size functions and the is empty functions\n");
//   toString(p);
// //  printf("\n%d", q->size);
//   
//   
//   int i = q->size;
//   while (i > 0) {
//   PCB_p removed = dequeue(q);
//   to_string_dequeue(q, removed);
//   i--;
////     printf("%d", q->size);
//   }    
//   // at this point element 9 should still be in the queue, but it is not or wont print once it is removed.
//   // when i enqueue it shows as if 9 is not in there.
//  // toString(q->head->pcb);
//   enqueue(q, four);
//   to_string_enqueue(q);
//   enqueue(q, five);
//   to_string_enqueue(q);
//   PCB_p removed = dequeue(q);
//   to_string_dequeue(q, removed);
//   removed = dequeue(q); //does the same thing here, it should be removing element five at this point and it shows as if its not there.
//   to_string_dequeue(q, removed);
//   PCB_p pq = peek(q); // peek is also showing that there is no more elements in the queue.
//   toString(pq);
}