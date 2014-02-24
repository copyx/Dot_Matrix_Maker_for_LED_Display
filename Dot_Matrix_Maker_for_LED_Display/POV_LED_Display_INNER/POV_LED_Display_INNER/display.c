#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

INNER_String STR_Buffer[2];
INNER_DISP_STAT INNER_Status;

const unsigned char LED_COLOR_MASK[4] = {0xC0, 0x30, 0x0C, 0x03};

/*
 * Default Character
 * A B C D
 */
char DEFAULT_Characters[NUMBER_OF_LED_CHAR][LED_CHAR_WIDTH][2] = {
	{0, 0, -96, 127, -112, 127, 24, 3, 12, 3, 6, 3, 6, 3, 12, 3, 24, 3, -112, 127, -96, 127, 0, 0},
	{0, 0, -126, 127, -126, 127, -6, 97, -6, 97, -6, 97, -6, 97, -6, 97, -78, 115, -124, 63, 120, 30, 0, 0},
	{0, 0, -96, 7, -120, 31, 28, 56, 14, 112, 6, 96, 6, 96, 6, 96, 14, 112, 28, 56, 24, 24, 0, 0},
	{0, 0, -126, 127, -126, 127, 6, 96, 6, 96, 6, 96, 6, 96, 12, 48, 28, 56, -120, 31, -96, 7, 0, 0},
};

void init_INNER_Status(void)
{
	INNER_Status.total_bits = 0;
}

void init_INNER_Timer(void)
{
	//GPIO 초기화 부분
}

void init_Display(void)
{
	init_INNER_Status();
	init_INNER_Timer();
	init_DISP_CQ(&DISP_Queue);
}

void turn_Power_INNER_Display(unsigned char status)
{
	if(status == OFF)
	{
		//글로벌 인터럽트 Disable
		//Status Bit 변경
		INNER_Status.content.power = OFF;
	}
	else if(status == ON)
	{
		//Status Bit 변경
		INNER_Status.content.power = ON;
		//글로벌 인터럽트 Enable
	}
}

void LED_Print(char* line)
{
	if(line != NULL)
	{
		char i, j;

		for(i = 1; i >= 0; i--)
			for(j = 7; j >= 0; j--)
				if((*(line + i) & (1 << j)) != 0)
					printf(" 1");
				else
					printf(" 0");
		printf("\n");
	}
	else
		printf(" 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n");
}

void change_Color(void)
{
	//색상 변경 코드
}

void GPIO_Interrupt(void)
{	
	static unsigned int color_change_timer = 0;
	/*
	 * GPIO 출력 bit 입력 부분
	 */
	LED_Print(DISP_Queue.item[DISP_Queue.current_line]);
		
	DISP_Queue.current_line = (DISP_Queue.current_line + 1) % INNER_DISPLAY_WIDTH;

	if(DISP_Queue.current_line == DISP_Queue.reference_line)
	{
		enqueue_DISP(&DISP_Queue);
		Sleep(10);
		system("cls");	//새 라인 추가
	}

	if(color_change_timer++ > 100)
		change_Color();
}