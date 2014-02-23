#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#define COLOR_RED		0
#define COLOR_YELLOW	1
#define COLOR_BLUE		2

#define COLOR_MASK_0	0xC0
#define COLOR_MASK_1	0x30
#define COLOR_MASK_2	0x0C
#define COLOR_MASK_3	0x03

const unsigned char COLOR_MASK[4] = {COLOR_MASK_0, COLOR_MASK_1, COLOR_MASK_2, COLOR_MASK_3};

#define MAXIMUM_LENGTH_OF_STRING	100

typedef struct Inner_String_Data
{
	unsigned short length;
	unsigned char data[MAXIMUM_LENGTH_OF_STRING];
}INNER_String;

typedef struct String_Buffer_Status_Content
{
	unsigned char nothing : 6;
	unsigned char new_str : 1;
	unsigned char using_str : 1;
}STR_STAT_CONTENT;

typedef union String_Buffer_Status
{
	STR_STAT_CONTENT content;
	unsigned char total_bits;
}STR_BUFF_STAT;

void init_Display(void);

extern INNER_String STR_Buffer[2];
extern STR_BUFF_STAT STR_Status;

#endif