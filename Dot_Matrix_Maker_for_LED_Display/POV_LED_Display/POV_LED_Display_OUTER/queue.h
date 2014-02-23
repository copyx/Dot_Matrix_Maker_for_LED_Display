#ifndef __QUEUE_H_
#define __QUEUE_H_

#define MAXIMUM_LENGTH_OF_RX_BUFFER	200

typedef struct Circular_Queue
{
	unsigned char front;
	unsigned char rear;
	unsigned char item[MAXIMUM_LENGTH_OF_RX_BUFFER];
}CQ;

#define IS_FULL(x)	((((x)->rear + 1) % MAXIMUM_LENGTH_OF_RX_BUFFER) == (x)->front)
#define IS_EMPTY(x)	((x)->front == (x)->rear)

unsigned char enqueue(CQ*, unsigned char);
unsigned char* dequeue(CQ*);

extern CQ RX_Queue;

#endif