/*
 * fifo_queue.h
 *
 * 	Created on: Jan 7, 2016
 * 		Authors: Jonah Howard
 *                       Mehgan Cook
 *                       Anthony Zullo
 *                       Quinn Cox
 */

#include <stdio.h>
#include <stdlib.h>
#include "PCB1.h"

#ifndef FIFO_QUEUE_H_
#define FIFO_QUEUE_H_

//typedef struct NODE {
//	void *next;
//	void *data;
//} Node;
//
//typedef struct fifo_queue {
//	int size;
//	Node front;
//	Node back;
//	void *data;
//} fifo_queue, FIFO_QUEUE, QUEUE, Q;


struct node {
	PCB_p pcb;
	struct node *next;
        struct node *back;
};

typedef struct node Node;

typedef struct fifo_queue {
	Node *head;
        int size;
} fifo_queue;

// Defines the fifo_queue_p which is a pointer to a fifo_queue
typedef fifo_queue *fifo_queue_p;



fifo_queue_p create_queue();
void enqueue(fifo_queue_p queue, PCB_p block);
PCB_p dequeue(fifo_queue_p queue);
PCB_p peek(fifo_queue_p queue);
int isEmpty(fifo_queue_p queue);
void to_string_enqueue(fifo_queue_p queue);
void to_string_dequeue(fifo_queue_p queue, PCB_p p);
void to_file_enqueue(FILE *outfile, fifo_queue_p queue);
void to_file_dequeue(FILE *outfile, fifo_queue_p queue, PCB_p p);

#endif /* fifo_queue.h */