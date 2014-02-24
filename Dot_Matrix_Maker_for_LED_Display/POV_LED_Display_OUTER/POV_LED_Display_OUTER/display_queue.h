#ifndef __DISPLAY_QUEUE_H_
#define __DISPLAY_QUEUE_H_

#include "display.h"

#define MAXIMUM_NUMBER_OF_USER_IMG		10

typedef struct Image_Circular_Queue
{
	unsigned char front;
	unsigned char rear;
	OUTER_Matrix item[MAXIMUM_NUMBER_OF_USER_IMG];
	
	unsigned char current_IMG;
	unsigned char current_line;
}IMG_CQ;

//typedef struct Display_Circular_Queue
//{
//	unsigned char front;
//	unsigned char rear;
//	char* item[INNER_DISPLAY_WIDTH];
//	
//	unsigned char reference_line;
//	unsigned char current_line;
//	unsigned char char_index;
//	unsigned char char_line;
//}DISP_CQ;

void init_IMG_CQ(IMG_CQ*);
//void init_DISP_CQ(DISP_CQ*);
//void enqueue_DISP(DISP_CQ*);

extern IMG_CQ IMG_Queue;

#endif