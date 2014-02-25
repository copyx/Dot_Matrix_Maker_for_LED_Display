#include "display.h"
//#include <avr/io.h>
//#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

INNER_String STR_Buffer[2];
INNER_DISP_STAT INNER_Status;

const unsigned char LED_COLOR_MASK[4] = {0xC0, 0x30, 0x0C, 0x03};

/*
 * Default Character
 */
unsigned char DEFAULT_Characters[NUMBER_OF_LED_CHAR][LED_CHAR_WIDTH][2] = {
	{0, 0, -96, 127, -112, 127, 24, 3, 12, 3, 6, 3, 6, 3, 12, 3, 24, 3, -112, 127, -96, 127, 0, 0},
	{0, 0, -126, 127, -126, 127, -6, 97, -6, 97, -6, 97, -6, 97, -6, 97, -78, 115, -124, 63, 120, 30, 0, 0},
	{0, 0, -96, 7, -120, 31, 28, 56, 14, 112, 6, 96, 6, 96, 6, 96, 14, 112, 28, 56, 24, 24, 0, 0},
	{0, 0, -126, 127, -126, 127, 6, 96, 6, 96, 6, 96, 6, 96, 12, 48, 28, 56, -120, 31, -96, 7, 0, 0},
};

void init_GPIO(void)
{
   /*DDRA=0xff;
   DDRB=0xff;
   DDRC=0xff;
   DDRD=0b11110011;
   DDRE=0xff;
   DDRF=0xff;
   DDRG=0xff;*/
}

void init_INNER_Status(void)
{
	INNER_Status.total_bits = 0;
}

void init_INNER_Timer(void)
{
	//Timer 초기화 부분
	//TCCR1A = (0b00000000);
	//TCCR1B = (0b00001010);       // Timer1 prescale 1

	//OCR1A = F_CPU / START_PPS;   // Start Pulse Per Second

	////Bit 4 - OCIE1A: Timer/Counter1, Output Compare a Match Interrupt Enable
	//TIMSK = (1 << OCIE1A);
}

void init_Display(void)
{
	init_GPIO();
	init_INNER_Status();
	init_INNER_Timer();
	init_STR_DISP_CQ(&STR_DISP_Queue);
}

void turn_Power_INNER_Display(unsigned char status)
{
	if(status == OFF)
	{
		//글로벌 인터럽트 Disable
		//cli();

		//LED off
		//PORTA = 0b00000000;
		//PORTB = 0b00000000;

		//Status Bit 변경
		INNER_Status.content.power = OFF;
	}
	else if(status == ON)
	{
		//Status Bit 변경
		INNER_Status.content.power = ON;
		//글로벌 인터럽트 Enable
		//sei();
	}
}

//GPIO 출력 함수
void LED_Print(unsigned char* line)
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
	
	/*PORTA = *(line + 0);
	PORTB = *(line + 1);*/
}

void change_Color()
{
	//색상 변경 코드
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
		if(INNER_Status.content.mode == STR)
		{
			//STR 모드
			LED_Print(STR_DISP_Queue.item[STR_DISP_Queue.current_line]);
		
			//출력 라인 이동
			STR_DISP_Queue.current_line = (STR_DISP_Queue.current_line + 1) % INNER_DISPLAY_WIDTH;
			
			//한 화면 출력하면 새 라인 추가
			if(STR_DISP_Queue.current_line == STR_DISP_Queue.reference_line)
			{
				enqueue_STR_DISP_Line(&STR_DISP_Queue);
				Sleep(10);
				system("cls");
			}
		}
		else
		{
			//IMG 모드
			LED_Print(IMG_Queue.item[IMG_Queue.current_img].dots[IMG_Queue.current_line]);
		
			//출력 라인 이동
			IMG_Queue.current_line = (IMG_Queue.current_line + 1) % INNER_DISPLAY_WIDTH;

			if(IMG_Queue.current_line == 0)
			{
				if(INNER_Status.content.rotation = CW)
					IMG_Queue.current_line = (IMG_Queue.current_line == 0) ? INNER_DISPLAY_WIDTH - 1 : IMG_Queue.current_line - 1;					
				else if(INNER_Status.content.rotation = CCW)
					IMG_Queue.current_line = (IMG_Queue.current_line + 1) % INNER_DISPLAY_WIDTH;
			}

			if(img_change_timer > 10000)
			{
				IMG_Queue.current_img = (IMG_Queue.current_img + 1) % IMG_Queue.total_img;
				Sleep(10);
				system("cls");
			}
			img_change_timer++;
		}
	}
	else
	{	//LED off
		//PORTA = 0b00000000;
		//PORTB = 0b00000000;
	}
}

//ISR(TIMER1_COMPA_vect)
//{
//}