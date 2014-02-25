#include <stdio.h>
#include "comm.h"

//���ŵ� Data�� UART ���ͷ�Ʈ�� ���� Queue�� ����

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
	init_UART_1();
}

void receive_String(RX_CQ* queue)
{
	unsigned short i;
	unsigned char unusing_STR = ~INNER_Status.content.using_str;

	turn_Power_INNER_Display(OFF);

	while(IS_EMPTY(queue)) ;
	STR_Buffer[unusing_STR].length = *dequeue_RX(queue);

	for(i = 0; i < STR_Buffer[unusing_STR].length; i++)
	{		
		while(IS_EMPTY(queue)) ;
		STR_Buffer[unusing_STR].data[i] = *dequeue_RX(queue);
	}

	INNER_Status.content.new_str = 1;
	INNER_Status.content.mode = STR;
	
	turn_Power_INNER_Display(ON);
}

void receive_IMG(RX_CQ* queue)
{
	short i, j;

	turn_Power_INNER_Display(OFF);

	init_IMG_CQ(&IMG_Queue);

	IMG_Queue.total_img = *dequeue_RX(queue);

	for(j = 0; j < IMG_Queue.total_img; j++)
	{		
		for(i = 0; i < INNER_DISPLAY_COLOR_BYTE_LENGTH; i++)
		{		
			while(IS_EMPTY(queue)) ;
			IMG_Queue.item[j].line_color_info[i] = *dequeue_RX(queue);
		}

		for(i = 0; i < INNER_DISPLAY_TOTAL_DOT_BYTE; i++)
		{
			while(IS_EMPTY(queue)) ;
			IMG_Queue.item[j].dots[i / INNER_DISPLAY_HEIGHT_IN_BYTE][i % INNER_DISPLAY_HEIGHT_IN_BYTE] = *dequeue_RX(queue);
		}
	}

	INNER_Status.content.mode = IMG;
	
	turn_Power_INNER_Display(ON);
}

//UART ���ͷ�Ʈ
//SIGNAL(SIG_UART1_RECV)
//{
//	unsigned char data;
//	data = UDR1;
//	enqueue_RX(&RX_Queue, data);
//}