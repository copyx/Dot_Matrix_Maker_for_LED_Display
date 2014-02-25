#include "display_queue.h"
#include "display.h"
#include <stdio.h>

STR_DISP_CQ STR_DISP_Queue;
IMG_CQ IMG_Queue;

void init_STR_DISP_CQ(STR_DISP_CQ* queue)
{
	int i;

	queue->char_index = queue->char_line = queue->front = queue->rear = 0;
	queue->reference_line = queue->current_line = queue->rear + 1;

	for(i = 0; i < INNER_DISPLAY_WIDTH; i++)
		queue->item[i] = NULL;
}

void init_IMG_CQ(IMG_CQ* queue)
{
	queue->current_img = queue->current_line = queue->total_img = 0;
}

void enqueue_STR_DISP_Line(STR_DISP_CQ* queue)
{
	unsigned char* item;
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
		item = DEFAULT_Characters[STR_Buffer[INNER_Status.content.using_str].data[queue->char_index] - 'A'][queue->char_line];

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