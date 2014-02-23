#include <stdio.h>
#include "comm.h"
#include "queue.h"
#include "display.h"

void receive_String(CQ* queue)
{
	unsigned short i;
	unsigned char unusing_STR = (STR_Status.content.using_str + 1) % 2;

	while(IS_EMPTY(queue)) ;
	STR_Buffer[unusing_STR].length = *dequeue(queue);

	for(i = 0; i < STR_Buffer[unusing_STR].length; i++)
	{		
		while(IS_EMPTY(queue)) ;
		STR_Buffer[unusing_STR].data[i] = *dequeue(queue);
	}

	STR_Status.content.new_str = 1;
}

//ID를 비교해서 자기 것이면 수신, 남의 것이면 전달함.

__inline void detect_RX_Data(void)
{
	unsigned char id, command;
	
	if(!IS_EMPTY(&RX_Queue))
	{
		id = *dequeue(&RX_Queue);
		command = *dequeue(&RX_Queue);
		
		if(id == THIS_ID)
		{
			switch(command)
			{
			case STRING_RECEIVE_CMD:
				receive_String(&RX_Queue);
				break;
			case INNER_DISPLAY_ON_CMD:
				break;
			case INNER_DISPLAY_OFF_CMD:
				break;
			case INNER_ROTATION_CW_START_CMD:
				break;
			case INNER_ROTATION_CCW_START_CMD:
				break;
			case INNER_ROTATION_STOP_CMD:
				break;
			}
		}
		else
		{
			switch(command)
			{
			case IMG_RECEIVE_CMD:
				break;
			case OUTER_DISPLAY_ON_CMD:
				break;
			case OUTER_DISPLAY_OFF_CMD:
				break;
			case OUTER_ROTATION_CW_START_CMD:
				break;
			case OUTER_ROTATION_CCW_START_CMD:
				break;
			case OUTER_ROTATION_STOP_CMD:
				break;
			case MUSIC_START_CMD:
				break;
			case MUSIC_STOP_CMD:
				break;
			}
		}
	}
}