#ifndef __COMM_H_
#define __COMM_H_

#include "rx_queue.h"
#include "display.h"

#define INNER_DISPLAY_ID	0
#define OUTER_DISPLAY_ID	1

#define THIS_ID		OUTER_DISPLAY_ID

enum COMMAND
{
	INNER_DISPLAY_ON_CMD = 2,
	INNER_DISPLAY_OFF_CMD,
	OUTER_DISPLAY_ON_CMD,
	OUTER_DISPLAY_OFF_CMD,

	OUTER_ROTATION_CW_START_CMD,
	OUTER_ROTATION_CCW_START_CMD,
	OUTER_ROTATION_STOP_CMD,

	MUSIC_START_CMD,
	MUSIC_STOP_CMD,
	
	STRING_RECEIVE_CMD,
	IMG_RECEIVE_CMD,
	MUSIC_RECEIVE_CMD,
};

void init_Comm(void);
void receive_IMG(RX_CQ*);
void deliver_String(RX_CQ*);
void receive_MUSIC(RX_CQ*);

//ID를 비교해서 자기 것이면 수신, 남의 것이면 전달함.
__inline void detect_RX_Data(void)
{
	unsigned char id, command;
	
	if(!IS_EMPTY(&RX_Queue))
	{
		id = *dequeue_RX(&RX_Queue);
		command = *dequeue_RX(&RX_Queue);
		
		if(id == THIS_ID)
		{
			switch(command)
			{
			case IMG_RECEIVE_CMD:
				receive_IMG(&RX_Queue);
				break;
			case MUSIC_RECEIVE_CMD:
				receive_MUSIC(&RX_Queue);
				break;
			case OUTER_DISPLAY_ON_CMD:
				turn_Power_OUTER_Display(ON);
				break;
			case OUTER_DISPLAY_OFF_CMD:
				turn_Power_OUTER_Display(OFF);
				break;
			case OUTER_ROTATION_CW_START_CMD:
				OUTER_Status.content.rotation = CW;
				break;
			case OUTER_ROTATION_CCW_START_CMD:
				OUTER_Status.content.rotation = CCW;
				break;
			case OUTER_ROTATION_STOP_CMD:
				OUTER_Status.content.rotation = STOP;
				break;
			case MUSIC_START_CMD:
				OUTER_Status.content.music = ON;
				break;
			case MUSIC_STOP_CMD:
				OUTER_Status.content.music = OFF;
				break;
			}
		}
		else
		{
			switch(command)
			{
			case STRING_RECEIVE_CMD:
				deliver_String(&RX_Queue);
				break;
			case INNER_DISPLAY_ON_CMD:
			case INNER_DISPLAY_OFF_CMD:
				//UART로 바로 전달
				break;
			}
		}
	}
}

#endif