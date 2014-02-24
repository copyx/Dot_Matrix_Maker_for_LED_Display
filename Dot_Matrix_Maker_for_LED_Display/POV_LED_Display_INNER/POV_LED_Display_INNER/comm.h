#ifndef __COMM_H_
#define __COMM_H_

#include "rx_queue.h"
#include "display.h"

#define INNER_DISPLAY_ID	0
#define OUTER_DISPLAY_ID	1

#define THIS_ID		INNER_DISPLAY_ID

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
};

void init_Comm(void);
void receive_String(RX_CQ*);

//LNK2019 발생: 인라인 함수는 헤더 파일에 정의와 구현을 함께 놓을 것!
__inline void detect_RX_Data(void)
{
	unsigned char command;
	
	if(!IS_EMPTY(&RX_Queue))
	{
		command = *dequeue_RX(&RX_Queue);
		
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
		}
	}
}

#endif