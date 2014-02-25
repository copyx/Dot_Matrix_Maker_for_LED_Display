#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include "display_queue.h"

#define COLOR_RED		0
#define COLOR_YELLOW	1
#define COLOR_BLUE		2

#define MAXIMUM_LENGTH_OF_MUSIC	6000



enum DISPLAY_POWER
{
	OFF = 0,
	ON,
};

enum ROTATION_STATUS
{
	STOP = 0,
	CW,
	CCW,
};

enum DISPLAY_MODE
{
	IMG = 0,
	MUSIC,
};



typedef struct OUTER_Display_Status_Content
{
	unsigned char nothing : 3;
	unsigned char mode : 1;
	unsigned char power : 1;
	unsigned char rotation : 2;
	unsigned char music : 1;
}OUTER_STAT_CONTENT;

typedef union OUTER_Display_Status
{
	OUTER_STAT_CONTENT content;
	unsigned char total_bits;
}OUTER_DISP_STAT;

typedef struct OUTER_Music_Level_Data
{
	short length;
	unsigned char LEVEL_Data[MAXIMUM_LENGTH_OF_MUSIC];
}OUTER_Music_Data;



void init_Display(void);
void turn_Power_OUTER_Display(unsigned char);
void TIMER_Interrupt(void);

extern OUTER_DISP_STAT OUTER_Status;
extern OUTER_Matrix DEFAULT_Music_Img[MAXIMUM_NUMBER_OF_DEFAULT_IMG][NUMBER_OF_MUSIC_LEVEL];
extern OUTER_Music_Data OUTER_Music;

#endif