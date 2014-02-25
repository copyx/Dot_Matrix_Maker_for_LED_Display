#include "display_queue.h"
#include "display.h"
#include <stdio.h>

IMG_CQ IMG_Queue;
MUSIC_CQ MUSIC_Queue;

void init_IMG_CQ(IMG_CQ* queue)
{
	queue->current_img = queue->current_line = queue->total_img = 0;
}

void init_MUSIC_CQ(MUSIC_CQ* queue)
{
	queue->current_img = queue->current_line = 0;
	queue->total_img = MAXIMUM_NUMBER_OF_DEFAULT_IMG;

	queue->
}