#include <stdio.h>
#include "comm.h"

//수신된 Data는 UART 인터럽트를 통해 Queue에 저장

void init_Comm(void)
{
	init_RX_Queue();
	//UART 초기화 부분
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
