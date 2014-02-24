#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "display_queue.h"

OUTER_DISP_STAT OUTER_Status;
OUTER_Matrix DEFAULT_Music_Img[MAXIMUM_NUMBER_OF_DEFAULT_IMG][NUMBER_OF_MUSIC_LEVEL];
OUTER_Music_Data OUTER_Music;

const unsigned char LED_COLOR_MASK[4] = {0xC0, 0x30, 0x0C, 0x03};

void init_OUTER_Status(void)
{
	OUTER_Status.total_bits = 0;
}

void init_OUTER_Timer(void)
{
	//Ÿ�̸� ���� �ڵ�
}

void init_Display(void)
{
	init_OUTER_Status();
	init_OUTER_Timer();
}

void turn_Power_OUTER_Display(unsigned char status)
{
	if(status == OFF)
	{
		//�۷ι� ���ͷ�Ʈ Disable
		//Status Bit ����
		OUTER_Status.content.power = OFF;
	}
	else if(status == ON)
	{
		//Status Bit ����
		OUTER_Status.content.power = ON;
		//�۷ι� ���ͷ�Ʈ Enable
	}
}
void change_Color(void)
{
	//���� ���� �ڵ�
}

void LED_Print(unsigned char* line)
{
	char i, j;

	for(i = 3; i >= 0; i--)
		for(j = 7; j >= 0; j--)
			if((*(line + i) & (1 << j)) != 0)
				printf(" 1");
			else
				printf(" 0");
	printf("\n");
}

void GPIO_Interrupt(void)
{	
	static unsigned int color_change_timer = 0;

	if(OUTER_Status.content.music)
	{
	}
	else
	{
	/*
	 * GPIO ��� bit �Է� �κ�
	 */
		LED_Print(IMG_Queue.item[IMG_Queue.current_IMG].dots[IMG_Queue.current_line]);
		
		IMG_Queue.current_line = (IMG_Queue.current_line + 1) % OUTER_DISPLAY_WIDTH;

	//if(DISP_Queue.current_line == DISP_Queue.reference_line)
	//{
	//	enqueue_DISP(&DISP_Queue);
	//	Sleep(10);
	//	system("cls");	//�� ���� �߰�
	//}
	}

	if(color_change_timer++ > 100)
		change_Color();
}