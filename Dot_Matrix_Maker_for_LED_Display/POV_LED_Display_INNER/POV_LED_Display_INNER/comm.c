#include <stdio.h>
#include "comm.h"

//���ŵ� Data�� UART ���ͷ�Ʈ�� ���� Queue�� ����

void init_Comm(void)
{
	init_RX_Queue();
	//UART �ʱ�ȭ �κ�
}

void receive_String(RX_CQ* queue)
{
	unsigned short i;
	unsigned char unusing_STR = ~INNER_Status.content.using_str;

	while(IS_EMPTY(queue)) ;
	STR_Buffer[unusing_STR].length = *dequeue_RX(queue);

	for(i = 0; i < STR_Buffer[unusing_STR].length; i++)
	{		
		while(IS_EMPTY(queue)) ;
		STR_Buffer[unusing_STR].data[i] = *dequeue_RX(queue);
	}

	INNER_Status.content.new_str = 1;
}
