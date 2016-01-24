/*
 * fifo_queue.c
 *
 * 	Created on: Jan 7, 2016
 * 		Author: Jonah Howard
 */

#include "fifo_queue.h"

// Global Variables
//static Node queue->front;
//static Node queue->back;
//static int size = 0;
//static struct fifo_queue *queue = NULL;

// Initializes a new FIFOQueue
fifo_queue * create_queue() {
	fifo_queue *queue;
	queue = malloc(sizeof(queue));
	queue->front = NULL;
	queue->back = NULL;
	queue->size = 0;
	return queue;
}

// Add PCB block to this queue with the same priority as the others in this queue
void enqueue(fifo_queue *queue, Node block) {
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
Node dequeue(fifo_queue *queue) {
	Node temp = queue->front;
	if (!temp) {	// If this queue is empty
		printf("\nError, there are no more PCB's in this queue!");
	} else {
		queue->front = queue->front->next_pcb;
		queue->size--;
	}
	return temp;
}

// Return a pointer referencing the first PCB block of this queue
Node peek(fifo_queue *queue) {
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

// Returns the size of the passed queue
int get_size(fifo_queue *queue) {
	return queue->size;
}

// Prints the contents of the passed queue.
void to_string_enqueue(fifo_queue *queue) {
	int i = 1;
	Node current = queue->front;
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

// Prints the contents of the passed queue. p is the most 
// recently dequeued Node.
void to_string_dequeue(fifo_queue *queue, Node p) {
	int i = 1, j = 2;
	Node current = queue->front;
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