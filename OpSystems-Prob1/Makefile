main: main.c PCB.o fifo_queue.o PriorityQueue.o testPriorityQueue.o
		gcc -o main main.c PCB.c fifo_queue.c PriorityQueue.c testPriorityQueue.c

PriorityQueue.o: PriorityQueue.c PriorityQueue.h
		gcc -c PriorityQueue.c

fifo_queue.o: fifo_queue.c fifo_queue.h
		gcc -c fifo_queue.c

PCB.o: PCB.c PCB.h 
		gcc -c PCB.c
	
testPriorityQueue.o: testPriorityQueue.c testPriorityQueue.h
		gcc -c testPriorityQueue.c