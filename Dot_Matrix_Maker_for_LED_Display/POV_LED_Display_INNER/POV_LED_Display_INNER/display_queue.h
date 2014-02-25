#ifndef __DISPLAY_QUEUE_H_
#define __DISPLAY_QUEUE_H_

//47이 1cm 간격으로 계산했을 때 라인 수. 타이밍 계산의 용이함을 위해 48로 변경
#define INNER_DISPLAY_WIDTH				48
#define INNER_DISPLAY_HEIGHT_IN_BYTE	2 
#define INNER_DISPLAY_TOTAL_DOT_BYTE	(INNER_DISPLAY_WIDTH * INNER_DISPLAY_HEIGHT_IN_BYTE)
#define INNER_DISPLAY_COLOR_BYTE_LENGTH	12
#define LED_CHAR_WIDTH		12

#define MAXIMUM_NUMBER_OF_USER_IMG	10

typedef struct String_Display_Circular_Queue
{
	unsigned char front;
	unsigned char rear;
	unsigned char* item[INNER_DISPLAY_WIDTH];
	
	unsigned char reference_line;
	unsigned char current_line;
	unsigned char char_index;
	unsigned char char_line;
}STR_DISP_CQ;

typedef struct INNER_Dot_Matrix
{
	unsigned char line_color_info[INNER_DISPLAY_COLOR_BYTE_LENGTH];
	unsigned char dots[INNER_DISPLAY_WIDTH][INNER_DISPLAY_HEIGHT_IN_BYTE];
}INNER_Matrix;

typedef struct Image_Circular_Queue
{
	unsigned char current_img;
	unsigned char current_line;
	unsigned char total_img;
	INNER_Matrix item[MAXIMUM_NUMBER_OF_USER_IMG];	
}IMG_CQ;

void init_IMG_CQ(IMG_CQ*);
void init_STR_DISP_CQ(STR_DISP_CQ*);
void enqueue_STR_DISP_Line(STR_DISP_CQ*);

extern STR_DISP_CQ STR_DISP_Queue;
extern IMG_CQ IMG_Queue;

#endif