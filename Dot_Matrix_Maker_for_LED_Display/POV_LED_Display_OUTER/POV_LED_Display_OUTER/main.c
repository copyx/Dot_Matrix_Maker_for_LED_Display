#include <stdio.h>
#include "display.h"
#include "comm.h"

int main(void)
{
	//���α׷� �ʱ�ȭ
	init_Comm();
	init_Display();

	//��� ����
	detect_RX_Data();

	while(1)
		GPIO_Interrupt();

	return 0;
}