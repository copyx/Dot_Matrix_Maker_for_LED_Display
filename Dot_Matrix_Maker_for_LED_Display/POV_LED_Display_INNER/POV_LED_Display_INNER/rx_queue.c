#include <stdio.h>
#include "rx_queue.h"

RX_CQ RX_Queue;

void init_RX_Queue(void)
{
	RX_Queue.front = RX_Queue.rear = 0;
}

unsigned char enqueue_RX(RX_CQ* queue, unsigned char item)
{
	if(IS_FULL(queue))
		return 0;
	else
	{
		queue->rear = (queue->rear + 1) % MAXIMUM_LENGTH_OF_RX_BUFFER;
		queue->item[queue->rear] = item;
		return 1;
	}
}

unsigned char* dequeue_RX(RX_CQ* queue)
{
	if(IS_EMPTY(queue))
		return NULL;
	else
	{
		queue->front = (queue->front + 1) % MAXIMUM_LENGTH_OF_RX_BUFFER;
		return &(queue->item[queue->front]);
	}
}