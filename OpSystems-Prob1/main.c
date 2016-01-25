/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: mehga_000
 *
 * Created on January 13, 2016, 1:40 AM
 */


#include <stdio.h>
#include <stdlib.h>
#include "PCB.h"
#include "fifo_queue.h"
//#include "pcb_test.h"
#include "fifo_queue_test.h"
//#include "PriorityQueue_test.h"

void testFIFO() {
    fifo_queue_p q = create_queue();
    int j = 0;
    int i = 0;
    while (i < 5) {
        PCB_p pcb = create_pcb(i, j);
        enqueue(q, pcb);
        i++; j++;
          to_string_enqueue(q);
    }
}
/*
 * 
 */
int main(int argc, char** argv) {

  //  testPCB();
    testFIFO();
 //    testPriorityQueue();
 
    return (EXIT_SUCCESS);
}

