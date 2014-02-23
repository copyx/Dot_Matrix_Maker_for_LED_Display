#include "display_queue.h"
#include <stdio.h>

DISP_CQ DISP_Queue;

void init_DISP_CQ(DISP_CQ* queue)
{
	queue->front = queue->rear = INNER_DISPLAY_WIDTH - 2;
	queue->reference_line = queue->current_line = queue->char_index = queue->next_line = 0;
}

unsigned char enqueue(DISP_CQ* queue, unsigned char item)
{
	if(IS_FULL(queue))
		return 0;
	else
	{
		queue->rear = (queue->rear + 1) % INNER_DISPLAY_WIDTH;
		queue->item[queue->rear] = item;
		return 1;
	}
}

unsigned char* dequeue(DISP_CQ* queue)
{
	if(IS_EMPTY(queue))
		return NULL;
	else
	{
		queue->front = (queue->front + 1) % INNER_DISPLAY_WIDTH;
		return &(queue->item[queue->front]);
	}
}