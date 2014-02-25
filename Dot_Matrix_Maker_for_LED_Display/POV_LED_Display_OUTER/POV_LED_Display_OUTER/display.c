#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

OUTER_DISP_STAT OUTER_Status;
OUTER_Music_Data OUTER_Music;

const unsigned char LED_COLOR_MASK[4] = {0xC0, 0x30, 0x0C, 0x03};

void init_OUTER_Status(void)
{
	OUTER_Status.total_bits = 0;
}

void init_OUTER_Timer(void)
{
	//타이머 설정 코드
}

void init_Display(void)
{
	init_IMG_CQ(&IMG_Queue);
	init_MUSIC_CQ(&MUSIC_Queue);
	init_OUTER_Status();
	init_OUTER_Timer();
}

void turn_Power_OUTER_Display(unsigned char status)
{
	if(status == OFF)
	{
		//글로벌 인터럽트 Disable
		//Status Bit 변경
		OUTER_Status.content.power = OFF;
	}
	else if(status == ON)
	{
		//Status Bit 변경
		OUTER_Status.content.power = ON;
		//글로벌 인터럽트 Enable
	}
}
void change_Color(void)
{
	//색상 변경 코드
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

void TIMER_Interrupt(void)
{	
	static unsigned short color_change_timer = 0, img_change_timer = 0;

	if(color_change_timer++ > 100)
	{
		color_change_timer = 0;
		change_Color();
	}

	if(color_change_timer % 2)
	{
		if(OUTER_Status.content.mode == IMG)
		{
			//IMG 모드
			LED_Print(IMG_Queue.item[IMG_Queue.current_img].dots[IMG_Queue.current_line]);
		
			//출력 라인 이동
			IMG_Queue.current_line = (IMG_Queue.current_line + 1) % OUTER_DISPLAY_WIDTH;

			if(IMG_Queue.current_line == 0)
			{
				if(OUTER_Status.content.rotation = CW)
					IMG_Queue.current_line = (IMG_Queue.current_line == 0) ? OUTER_DISPLAY_WIDTH - 1 : IMG_Queue.current_line - 1;					
				else if(OUTER_Status.content.rotation = CCW)
					IMG_Queue.current_line = (IMG_Queue.current_line + 1) % OUTER_DISPLAY_WIDTH;
			}

			if(img_change_timer > 10000)
			{
				IMG_Queue.current_img = (IMG_Queue.current_img + 1) % IMG_Queue.total_img;
				Sleep(10);
				system("cls");
			}
			img_change_timer++;
		}
		else
		{
			//MUSIC 모드
		}
	}
	else
	{	//LED off
		//PORTA = 0b00000000;
		//PORTB = 0b00000000;
	}
}