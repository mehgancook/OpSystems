/*
 * fifo_queue.h
 *
 * 	Created on: Jan 7, 2016
 * 		Author: Jonah Howard
 */

#include <stdio.h>
#include <stdlib.h>
#include "PCB.h"

#ifndef FIFO_QUEUE_H_
#define FIFO_QUEUE_H_

typedef struct fifo_queue {
	int size;
	PCB_p front;
	PCB_p back;
} fifo_queue, FIFO_QUEUE, QUEUE, Q;

fifo_queue *create_queue();
void enqueue(fifo_queue *queue, PCB_p block);
PCB_p dequeue(fifo_queue *queue);
PCB_p peek(fifo_queue *queue);
int is_empty(fifo_queue *queue); // Return 1 if empty
int get_size(fifo_queue *queue);
void to_string_enqueue(fifo_queue *queue);
void to_string_dequeue(fifo_queue *queue, PCB_p p);

#endif /* fifo_queue.h */