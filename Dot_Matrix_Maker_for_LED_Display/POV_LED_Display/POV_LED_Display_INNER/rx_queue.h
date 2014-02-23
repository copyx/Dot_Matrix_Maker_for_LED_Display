#ifndef __RX_QUEUE_H_
#define __RX_QUEUE_H_

#define MAXIMUM_LENGTH_OF_RX_BUFFER	200

typedef struct RX_Circular_Queue
{
	unsigned char front;
	unsigned char rear;
	unsigned char item[MAXIMUM_LENGTH_OF_RX_BUFFER];
}RX_CQ;

#define IS_FULL(x)	((((x)->rear + 1) % MAXIMUM_LENGTH_OF_RX_BUFFER) == (x)->front)
#define IS_EMPTY(x)	((x)->front == (x)->rear)

unsigned char enqueue(RX_CQ*, unsigned char);
unsigned char* dequeue(RX_CQ*);

extern RX_CQ RX_Queue;

#endif