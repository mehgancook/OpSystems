/**
 *  File:   main.c
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
#include "cpu.h"
#include "PCB1.h"
#include "fifo_queue.h"
#include "PriorityQueue.h"
#include "PriorityQueue_test.h"


/*
 * Main driver for this program. Creates a random number of new processes and 
 * simulates the running of the current process. Command line parameters are 
 * ignored. Returns the exit status of the program.
 */
int main(int argc, char** argv) {
//    CPU cpu;
//    run(&cpu);
    testPriorityQueue();
    return (EXIT_SUCCESS);
}

