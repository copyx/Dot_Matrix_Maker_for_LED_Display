#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#define MAXIMUM_LENGTH_OF_STRING	100

#define LED_CHAR_WIDTH		16
#define NUMBER_OF_LED_CHAR	26

#define COLOR_RED		0
#define COLOR_YELLOW	1
#define COLOR_BLUE		2

#define COLOR_MASK_0	0xC0
#define COLOR_MASK_1	0x30
#define COLOR_MASK_2	0x0C
#define COLOR_MASK_3	0x03

const unsigned char COLOR_MASK[4] = {COLOR_MASK_0, COLOR_MASK_1, COLOR_MASK_2, COLOR_MASK_3};



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
	unsigned char nothing : 4;
	unsigned char power : 1;
	unsigned char rotation : 1;
	unsigned char new_str : 1;
	unsigned char using_str : 1;
}INNER_STAT_CONTENT;

typedef union INNER_Display_Status
{
	INNER_STAT_CONTENT content;
	unsigned char total_bits;
}INNER_DISP_STAT;

//typedef union Inner_Display_Line
//{
//	unsigned char bytes[2];
//	unsigned short total_bits;
//}LED_Char;

typedef struct INNER_Display_Index
{	
	unsigned short char_index;
	unsigned char current_str_line;
}INNER_DISP_IDX;


void init_Display(void);
void turn_Power_INNER_Display(unsigned char);
void rotate_INNER_Display(unsigned char);

extern INNER_String STR_Buffer[2];
extern INNER_DISP_STAT STR_Status;



#endif