#ifndef __DISPLAY_QUEUE_H_
#define __DISPLAY_QUEUE_H_

//47�� 1cm �������� ������� �� ���� ��. Ÿ�̹� ����� �������� ���� 48�� ����
#define INNER_DISPLAY_WIDTH	48

#define IS_FULL(x)	((((x)->rear + 1) % INNER_DISPLAY_WIDTH) == (x)->front)
#define IS_EMPTY(x)	((x)->front == (x)->rear)

typedef struct Display_Circular_Queue
{
	unsigned char front;
	unsigned char rear;
	unsigned char item[INNER_DISPLAY_WIDTH];
	
	unsigned char reference_line;
	unsigned char current_line;
	unsigned char char_index;
	unsigned char next_line;
}DISP_CQ;

void init_DISP_CQ(DISP_CQ*);
unsigned char enqueue(DISP_CQ*, unsigned char);
unsigned char* dequeue(DISP_CQ*);

extern DISP_CQ DISP_Queue;

#endif