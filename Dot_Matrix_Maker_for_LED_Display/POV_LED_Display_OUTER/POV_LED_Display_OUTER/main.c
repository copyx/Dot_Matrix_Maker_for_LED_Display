#include <stdio.h>
#include "display.h"
#include "comm.h"

int main(void)
{
	//���α׷� �ʱ�ȭ
	init_Comm();
	init_Display();


	while(1)
	{
		//��� ����
		detect_RX_Data();
		GPIO_Interrupt();
	}

	return 0;
}