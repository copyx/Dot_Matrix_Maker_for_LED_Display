#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#define COLOR_RED		0
#define COLOR_YELLOW	1
#define COLOR_BLUE		2

#define OUTER_DISPLAY_WIDTH	64
#define MAXIMUM_NUMBER_OF_DEFAULT_IMG	3

#define NUMBER_OF_MUSIC_LEVEL	16
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
	NORMAL = 0,
	MUSIC,
};



typedef struct OUTER_Display_Status_Content
{
	unsigned char mode : 1;
	unsigned char using_music : 1;
	unsigned char new_music : 1;
	unsigned char using_str : 1;
	unsigned char power : 1;
	unsigned char rotation : 2;
	unsigned char music : 1;
}OUTER_STAT_CONTENT;

typedef union OUTER_Display_Status
{
	OUTER_STAT_CONTENT content;
	unsigned char total_bits;
}OUTER_DISP_STAT;

typedef struct OUTER_Dot_Matrix
{
	unsigned char line_color_info[16];
	unsigned char dots[OUTER_DISPLAY_WIDTH][4];
}OUTER_Matrix;

typedef struct OUTER_Music_Level_Data
{
	short length;
	unsigned char LEVEL_Data[MAXIMUM_LENGTH_OF_MUSIC];
}OUTER_Music_Data;



void init_Display(void);
void turn_Power_OUTER_Display(unsigned char);
void GPIO_Interrupt(void);

extern OUTER_DISP_STAT OUTER_Status;
extern OUTER_Matrix DEFAULT_Music_Img[MAXIMUM_NUMBER_OF_DEFAULT_IMG][NUMBER_OF_MUSIC_LEVEL];
extern OUTER_Music_Data OUTER_Music;

#endif