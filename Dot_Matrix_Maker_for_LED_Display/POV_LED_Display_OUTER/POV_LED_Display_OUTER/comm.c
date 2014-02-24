#include <stdio.h>
#include "comm.h"
#include "display_queue.h"

void init_Comm(void)
{
	init_RX_Queue();
	//UART 초기화 부분
}

void receive_IMG(RX_CQ* queue)
{
	short i;
	if(!IS_FULL(&IMG_Queue))
	{		
		IMG_Queue.rear = (IMG_Queue.rear + 1) % MAXIMUM_LENGTH_OF_RX_BUFFER;
		
		for(i = 0; i < 16; i++)
		{		
			while(IS_EMPTY(queue)) ;
			IMG_Queue.item[IMG_Queue.rear].line_color_info[i] = *dequeue_RX(queue);
		}

		for(i = 0; i < 256; i++)
		{
			while(IS_EMPTY(queue)) ;
			IMG_Queue.item[IMG_Queue.rear].dots[i / 4][i % 4] = *dequeue_RX(queue);
		}
	}
}

void receive_MUSIC(RX_CQ* queue)
{
	short i;
	unsigned char length[2];

	for(i = 0; i < 2; i++)
	{
		while(IS_EMPTY(queue)) ;
		length[i] = *dequeue_RX(queue);
	}

	OUTER_Music.length = *(short*)length;

	for(i = 0; i < OUTER_Music.length; i++)
	{
		while(IS_EMPTY(queue)) ;
		OUTER_Music.LEVEL_Data[i] = *dequeue_RX(queue);
	}
}

void deliver_String(RX_CQ* queue)
{
	unsigned short i, length;

	while(IS_EMPTY(queue)) ;
	length = *dequeue_RX(queue);

	for(i = 0; i < length; i++)
	{		
		while(IS_EMPTY(queue)) ;
		//전달 = *dequeue_RX(queue);
	}
}