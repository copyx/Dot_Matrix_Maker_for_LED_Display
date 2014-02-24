#ifndef __DISPLAY_QUEUE_H_
#define __DISPLAY_QUEUE_H_

//47�� 1cm �������� ������� �� ���� ��. Ÿ�̹� ����� �������� ���� 48�� ����
#define INNER_DISPLAY_WIDTH	48
#define LED_CHAR_WIDTH		12

typedef struct Display_Circular_Queue
{
	unsigned char front;
	unsigned char rear;
	char* item[INNER_DISPLAY_WIDTH];
	
	unsigned char reference_line;
	unsigned char current_line;
	unsigned char char_index;
	unsigned char char_line;
}DISP_CQ;

void init_DISP_CQ(DISP_CQ*);
void enqueue_DISP(DISP_CQ*);

extern DISP_CQ DISP_Queue;

#endif