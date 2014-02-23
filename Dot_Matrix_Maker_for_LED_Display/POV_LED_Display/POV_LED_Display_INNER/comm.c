#include <stdio.h>
#include "comm.h"
#include "rx_queue.h"
#include "display.h"

//수신된 Data는 UART 인터럽트를 통해 Queue에 저장

void init_Comm(void)
{
	//UART 초기화 부분
}

void receive_String(RX_CQ* queue)
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
	unsigned char command;
	
	if(!IS_EMPTY(&RX_Queue))
	{
		command = *dequeue(&RX_Queue);
		
		switch(command)
		{
		case STRING_RECEIVE_CMD:
			receive_String(&RX_Queue);
			break;
		case INNER_DISPLAY_ON_CMD:
			turn_Power_INNER_Display(ON);
			break;
		case INNER_DISPLAY_OFF_CMD:
			turn_Power_INNER_Display(OFF);
			break;
		case INNER_ROTATION_CW_START_CMD:
			rotate_INNER_Display(CW);
			break;
		case INNER_ROTATION_STOP_CMD:
			rotate_INNER_Display(STOP);
			break;
		}
	}
}