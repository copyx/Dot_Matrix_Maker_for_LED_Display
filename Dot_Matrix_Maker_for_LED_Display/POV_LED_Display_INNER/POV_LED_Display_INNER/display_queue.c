#include "display_queue.h"
#include "display.h"
#include <stdio.h>

DISP_CQ DISP_Queue;

void init_DISP_CQ(DISP_CQ* queue)
{
	int i;

	queue->char_index = queue->char_line = queue->front = queue->rear = 0;
	queue->reference_line = queue->current_line = queue->rear + 1;

	for(i = 0; i < INNER_DISPLAY_WIDTH; i++)
		queue->item[i] = NULL;
}

void enqueue_DISP(DISP_CQ* queue)
{
	char* item;
	static char empty = 0;

	if(empty >= 48)
	{
		empty = 0;
		if(INNER_Status.content.new_str)
		{
			INNER_Status.content.using_str = ~INNER_Status.content.using_str;
			INNER_Status.content.new_str = 0;
		}

		queue->char_index = 0;		
	}

	if(queue->char_index < STR_Buffer[INNER_Status.content.using_str].length)
	{
		item = (char*)DEFAULT_Characters[STR_Buffer[INNER_Status.content.using_str].data[queue->char_index] - 'A'][queue->char_line];

		//문자 인덱스들 증가
		queue->char_line = (queue->char_line + 1) % LED_CHAR_WIDTH;
		if(queue->char_line == 0)
			queue->char_index++;
	}
	else
	{
		item = NULL;
		empty++;
	}
	
	queue->rear = (queue->rear + 1) % INNER_DISPLAY_WIDTH;
	queue->item[queue->rear] = item;

	queue->current_line = queue->reference_line = (queue->reference_line + 1) % INNER_DISPLAY_WIDTH;
}