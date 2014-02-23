#include <stdio.h>
#include "queue.h"

CQ RX_Queue;

unsigned char enqueue(CQ* queue, unsigned char item)
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

unsigned char* dequeue(CQ* queue)
{
	if(IS_EMPTY(queue))
		return NULL;
	else
	{
		queue->front = (queue->front + 1) % MAXIMUM_LENGTH_OF_RX_BUFFER;
		return &(queue->item[queue->front]);
	}
}