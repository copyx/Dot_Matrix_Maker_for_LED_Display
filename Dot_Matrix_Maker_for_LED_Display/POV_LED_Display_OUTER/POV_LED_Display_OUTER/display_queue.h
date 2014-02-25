#ifndef __DISPLAY_QUEUE_H_
#define __DISPLAY_QUEUE_H_

#define OUTER_DISPLAY_WIDTH	64
#define OUTER_DISPLAY_HEIGHT_IN_BYTE	4 
#define OUTER_DISPLAY_TOTAL_DOT_BYTE	(OUTER_DISPLAY_WIDTH * OUTER_DISPLAY_HEIGHT_IN_BYTE)
#define OUTER_DISPLAY_COLOR_BYTE_LENGTH	16

#define NUMBER_OF_MUSIC_LEVEL	16

#define MAXIMUM_NUMBER_OF_DEFAULT_IMG	3	
#define MAXIMUM_NUMBER_OF_USER_IMG		10

typedef struct OUTER_Dot_Matrix
{
	unsigned char line_color_info[16];
	unsigned char dots[OUTER_DISPLAY_WIDTH][OUTER_DISPLAY_HEIGHT_IN_BYTE];
}OUTER_Matrix;

typedef struct Image_Circular_Queue
{
	unsigned char current_img;
	unsigned char current_line;
	unsigned char total_img;
	OUTER_Matrix item[MAXIMUM_NUMBER_OF_USER_IMG];
}IMG_CQ;

typedef struct Music_Image_Circular_Queue
{
	unsigned char current_img;
	unsigned char current_line;
	unsigned char total_img;
	OUTER_Matrix item[MAXIMUM_NUMBER_OF_DEFAULT_IMG][NUMBER_OF_MUSIC_LEVEL];
}MUSIC_CQ;

void init_IMG_CQ(IMG_CQ*);
void init_MUSIC_CQ(MUSIC_CQ*);

extern IMG_CQ IMG_Queue;
extern MUSIC_CQ MUSIC_Queue;

#endif