/*
 * fifo_queue.c
 *
 * 	Created on: Jan 7, 2016
 * 		Author: Jonah Howard
 */

#include "fifo_queue.h"

// Global Variables
//static PCB_p queue->front;
//static PCB_p queue->back;
//static int size = 0;
//static struct fifo_queue *queue = NULL;

fifo_queue * create_queue() {
	fifo_queue *queue;
	queue = malloc(sizeof(queue));
	queue->front = NULL;
	queue->back = NULL;
	queue->size = 0;
	return queue;
}

// Add PCB block to this queue with the same priority as the others in this queue
void enqueue(fifo_queue *queue, PCB_p block) {
	// If the queue is empty
//	printf("%d", queue->size);
	if (!queue->size) {
		queue->front = block;
		queue->front->next_pcb = NULL;
		queue->back = block;
	} else {	// Add to end of queue
		queue->back->next_pcb = block;
		block->next_pcb = NULL;
		queue->back = queue->back->next_pcb;
	}
	queue->size++;
}

// Remove and return the first PCB block in this queue.
PCB_p dequeue(fifo_queue *queue) {
	PCB_p temp = queue->front;
	if (!temp) {	// If this queue is empty
		printf("\nError, there are no more PCB's in this queue!");
	} else {
		queue->front = queue->front->next_pcb;
		queue->size--;
	}
	return temp;
}

// Return a pointer referencing the first PCB block of this queue
PCB_p peek(fifo_queue *queue) {
	if (!queue->front) {	// Check if queue is empty
		printf("\nError, there are no more PCB's in this queue!");
	}
	return queue->front;
}

// Returns 1 if this queue is empty, 0 otherwise
int is_empty(fifo_queue *queue) {
	int result;
	if (!queue->size)
		result = 1;
	else
		result = 0;
	return result;
}

int get_size(fifo_queue *queue) {
	return queue->size;
}

void to_string_enqueue(fifo_queue *queue) {
	int i = 1;
	PCB_p current = queue->front;
	if (!is_empty(queue)) {	// If queue is not empty
		if (queue->front == queue->back) {	// Only one element
			printf("P%d->", current->pid);
		} else {
			while (current) {
				printf("P%d->", current->pid);
				current = current->next_pcb;
				i++;
			}
		}
			printf("*\n");
			toString(queue->back);
	} else {
		printf("This queue is empty!");
	}
}

void to_string_dequeue(fifo_queue *queue, PCB_p p) {
	int i = 1, j = 2;
	PCB_p current = queue->front;
	if (!is_empty(queue) || p) {	// If queue is not empty
		if (queue->front == queue->back) {	// Only one element
			printf("P%d->P%d->*\n", p->pid, queue->front->pid);
			printf("P%d->", queue->front->pid);
		} else {
			printf("P%d->", p->pid);
			while (current) {
				printf("P%d->", current->pid);
				current = current->next_pcb;
			}
			printf("*\n");
			current = queue->front;
			while (current) {
				printf("P%d->", current->pid);
				current = current->next_pcb;
			}
		}
			printf("*\n");
			toString(p);
	} else {
		printf("This queue is empty!");
	}
}