#include "display.h"
#include "display_queue.h"

INNER_String STR_Buffer[2];
INNER_DISP_STAT INNER_Status;
INNER_DISP_IDX INNER_Index;

unsigned char DEFAULT_Characters[NUMBER_OF_LED_CHAR][LED_CHAR_WIDTH][2];

void init_Default_Character(void)
{
}

void init_Buffer(void)
{
	INNER_Status.total_bits = 0;
}

void init_INNER_Index(void)
{
	INNER_Index.char_index = 0;
	INNER_Index.current_str_line = 0;
}

void init_INNER_Timer(void)
{
	//GPIO �ʱ�ȭ �κ�
}

void init_Display(void)
{
	init_Default_Character();
	init_Buffer();
	init_INNER_Index();
	init_INNER_Timer();
}

void turn_Power_INNER_Display(unsigned char status)
{
	if(status == OFF)
	{
		//�۷ι� ���ͷ�Ʈ Disable
		//Status Bit ����
		INNER_Status.content.power = OFF;
	}
	else if(status == ON)
	{
		//Status Bit ����
		INNER_Status.content.power = ON;
		//�۷ι� ���ͷ�Ʈ Enable
	}
}

void rotate_INNER_Display(unsigned char status)
{
	if(status == STOP)
	{
		//Status Bit ����
		INNER_Status.content.rotation = STOP;
	}
	else if(status == CW)
	{
		//Status Bit ����
		INNER_Status.content.rotation = CW;
	}
}

void GPIO_Interrupt(void)
{	
	
}