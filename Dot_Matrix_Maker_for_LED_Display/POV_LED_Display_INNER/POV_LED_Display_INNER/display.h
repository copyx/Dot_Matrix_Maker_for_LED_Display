#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include "display_queue.h"

#define MAXIMUM_LENGTH_OF_STRING	100

#define NUMBER_OF_LED_CHAR	26

#define LED_COLOR_RED		0
#define LED_COLOR_YELLOW	1
#define LED_COLOR_BLUE		2



enum DISPLAY_POWER
{
	OFF = 0,
	ON,
};

enum ROTATION_STATUS
{
	STOP = 0,
	CW,
};


typedef struct Inner_String_Data
{
	unsigned short length;
	unsigned char data[MAXIMUM_LENGTH_OF_STRING];
}INNER_String;

typedef struct INNER_Display_Status_Content
{
	unsigned char nothing : 5;
	unsigned char power : 1;
	unsigned char new_str : 1;
	unsigned char using_str : 1;
}INNER_STAT_CONTENT;

typedef union INNER_Display_Status
{
	INNER_STAT_CONTENT content;
	unsigned char total_bits;
}INNER_DISP_STAT;



void init_Display(void);
void turn_Power_INNER_Display(unsigned char);
void GPIO_Interrupt(void);

extern INNER_String STR_Buffer[2];
extern INNER_DISP_STAT INNER_Status;
extern const unsigned char LED_COLOR_MASK[4];
extern char DEFAULT_Characters[NUMBER_OF_LED_CHAR][LED_CHAR_WIDTH][2];

#endif