#include <stdio.h>
#include "comm.h"
#include "display_queue.h"

//���� ȸ��ü
void init_UART_0(void)
{
	//UART0 �ʱ�ȭ �κ�	
	//cli();
	
	//UCSR0A=(1<<UDRE0);      //�۽ŵ����͸� ���� �غ� �� ����.
	//UCSR0B=(1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02);   //�������ͷ�ƮȰ��ȭ.����.�۽ź� Ȱ��ȭ
	//UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);      //���� �����ͱ��� 8bit.
	//UBRR0L=51;      //BaudRate=19200. UBRR=(F/16*BaudRate)-1

	//sei();   
}

//�������
void init_UART_1(void)
{
	//UART1 �ʱ�ȭ �κ�	
	//cli();

	//UCSR1A=(1<<UDRE1);      //�۽ŵ����͸� ���� �غ� �� ����.
	//UCSR1B=(1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1)|(0<<UCSZ12);   //�������ͷ�ƮȰ��ȭ.����.�۽ź� Ȱ��ȭ
	//UCSR1C=(1<<UCSZ11)|(1<<UCSZ10);      //���� �����ͱ��� 8bit.
	//UBRR1L=51;      //BaudRate=19200. UBRR=(F/16*BaudRate)-1

	//sei();   
}

void init_Comm(void)
{
	init_RX_Queue();
	init_UART_0();
	init_UART_1();
}

void receive_IMG(RX_CQ* queue)
{
	short i, j;

	turn_Power_OUTER_Display(OFF);

	init_IMG_CQ(&IMG_Queue);

	IMG_Queue.total_img = *dequeue_RX(queue);

	for(j = 0; j < IMG_Queue.total_img; j++)
	{		
		for(i = 0; i < OUTER_DISPLAY_COLOR_BYTE_LENGTH; i++)
		{		
			while(IS_EMPTY(queue)) ;
			IMG_Queue.item[j].line_color_info[i] = *dequeue_RX(queue);
		}

		for(i = 0; i < OUTER_DISPLAY_TOTAL_DOT_BYTE; i++)
		{
			while(IS_EMPTY(queue)) ;
			IMG_Queue.item[j].dots[i / OUTER_DISPLAY_HEIGHT_IN_BYTE][i % OUTER_DISPLAY_HEIGHT_IN_BYTE] = *dequeue_RX(queue);
		}
	}

	OUTER_Status.content.mode = IMG;
	
	turn_Power_OUTER_Display(ON);
}

void receive_MUSIC(RX_CQ* queue)
{
	short i;
	unsigned char length[2];

	for(i = 0; i < 2; i++)
	{
		while(IS_EMPTY(queue)) ;
		length[i] = *dequeue_RX(queue);
	}

	OUTER_Music.length = *(short*)length;

	for(i = 0; i < OUTER_Music.length; i++)
	{
		while(IS_EMPTY(queue)) ;
		OUTER_Music.LEVEL_Data[i] = *dequeue_RX(queue);
	}
}

void deliver_String(RX_CQ* queue)
{
	unsigned short i, length;

	while(IS_EMPTY(queue)) ;
	length = *dequeue_RX(queue);

	for(i = 0; i < length; i++)
	{		
		while(IS_EMPTY(queue)) ;
		//���� = *dequeue_RX(queue);
	}
}

//UART ���ͷ�Ʈ
//SIGNAL(SIG_UART1_RECV)
//{
//	unsigned char data;
//	data = UDR1;
//	enqueue_RX(&RX_Queue, data);
//}