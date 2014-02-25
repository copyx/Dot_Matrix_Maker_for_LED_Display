#ifndef __COMM_H_
#define __COMM_H_

#include "rx_queue.h"
#include "display.h"

#define INNER_DISPLAY_ID	'I'	//아이
#define OUTER_DISPLAY_ID	'O'	//오

#define THIS_ID		INNER_DISPLAY_ID

enum COMMAND
{
	DISPLAY_ON_CMD = 'N',
	DISPLAY_OFF_CMD = 'F',
	
	ROTATION_CW_START_CMD = 'C',
	ROTATION_CCW_START_CMD = 'W',
	ROTATION_STOP_CMD = 'T',

	MUSIC_START_CMD = 'M',
	MUSIC_PAUSE_CMD = 'P',
	MUSIC_STOP_CMD = 'Q',
	
	STRING_RECEIVE_CMD = 'S',
	IMG_RECEIVE_CMD = 'I',
};

void init_Comm(void);
void receive_String(RX_CQ*);
void receive_IMG(RX_CQ*);

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

		case IMG_RECEIVE_CMD:
			receive_IMG(&RX_Queue);
			break;

		case DISPLAY_ON_CMD:
			turn_Power_INNER_Display(ON);
			break;

		case DISPLAY_OFF_CMD:
			turn_Power_INNER_Display(OFF);
			break;

		case ROTATION_CW_START_CMD:
			INNER_Status.content.rotation = CW;
			break;

		case ROTATION_CCW_START_CMD:
			INNER_Status.content.rotation = CCW;
			break;

		case ROTATION_STOP_CMD:
			INNER_Status.content.rotation = STOP;
			break;
		}
	}
}

#endif