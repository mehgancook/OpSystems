/*
 * fifo_queue.c
 *
 * 	Created on: Jan 7, 2016
 * 		Author: Jonah Howard
 */

#include "fifo_queue.h"


// Initializes a new FIFOQueue

fifo_queue_p create_queue() {
    Node *newNode = malloc(sizeof (Node));
    newNode->back = NULL;
    newNode->next = NULL;
    newNode->pcb = NULL;
    fifo_queue_p fifo = newNode;
    fifo->size = 0;
    return fifo;
}

// Add PCB block to this queue with the same priority as the others in this queue

void enqueue(fifo_queue_p queue, PCB_p pcb) {
    if (queue->head == NULL) {
        Node *newNode = malloc(sizeof (Node));
        newNode->pcb = pcb;
        newNode->next = NULL;
        newNode->back = NULL;
        queue->head = newNode;
    } else {
        Node *curr = queue->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        Node *newNode = malloc(sizeof (Node));
        newNode->pcb = pcb;
        newNode->next = NULL;
        newNode->back = curr;
        curr->next = newNode;
    }
    queue->size++;
}

// Remove and return the first PCB block in this queue.

PCB_p dequeue(fifo_queue_p queue) {
    Node *first = queue->head;
    PCB_p ret = NULL;
    if (queue->head == NULL) {
        printf("\nError, there are no more PCB's in this queue!");
    } else if (first->next == NULL) {
        ret = queue->head->pcb;
        queue->head = NULL;
        queue->size--;
    } else {
        ret = queue->head->pcb;
        queue->head = first->next;
        queue->size--;
    }
    return ret;
}

// Return a pointer referencing the first PCB block of this queue

PCB_p peek(fifo_queue_p queue) {
    if (isEmpty(queue)) { // Check if queue is empty
        printf("\nError, there are no more PCB's in this queue!");
        return NULL;
    } else {
        return queue->head->pcb;
    }
}

int isEmpty(fifo_queue_p queue) {
    if (queue->head == NULL) {
        return 1;
    } else {
        return 0;
    }
}

// Prints the contents of the passed queue.

void to_string_enqueue(fifo_queue_p queue) {
    Node *current = queue->head;
    if (current == NULL) {
        printf("FIFO Queue is empty!");
    } else {
        while (current->next != NULL) {
            printf("P%d->", current->pcb->pid);
            current = current->next;
        }
        printf("P%d->", current->pcb->pid);
        printf("*\n");
        toString(current->pcb);
    }
}

// Prints the contents of the passed queue. p is the most 
// recently dequeued Node.

void to_string_dequeue(fifo_queue_p queue, PCB_p p) {
	Node *current = queue->head;
        if (current == NULL && p != NULL) {
             printf("P%d->*\n", p->pid);
	    printf("*\n");
            toString(p);
        } else if (!isEmpty(queue) || p) {	// If queue is not empty
		if (current->next == NULL) {	// Only one element
			printf("P%d->P%d->*\n", p->pid, queue->head->pcb->pid);
			printf("P%d->", queue->head->pcb->pid);
		} else {
			printf("P%d->", p->pid);
			while (current) {
				printf("P%d->", current->pcb->pid);
				current = current->next;
			}
			printf("*\n");
			current = queue->head;
			while (current) {
				printf("P%d->", current->pcb->pid);
				current = current->next;
			}
		}
			printf("*\n");
			toString(p);
        } else {
		printf("This queue is empty!");
	}
}






