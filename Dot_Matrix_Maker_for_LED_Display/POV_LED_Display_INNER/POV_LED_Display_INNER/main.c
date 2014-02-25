#include <stdio.h>
#include "display.h"
#include "comm.h"

int main(void)
{
	//프로그램 초기화
	init_Comm();
	init_Display();
	
	STR_Buffer[0].data[0] = 'A';
	STR_Buffer[0].data[1] = 'B';
	STR_Buffer[0].data[2] = 'C';
	STR_Buffer[0].data[3] = 'D';
	STR_Buffer[0].length = 4;

	
	STR_Buffer[1].data[0] = 'D';
	STR_Buffer[1].data[1] = 'C';
	STR_Buffer[1].data[2] = 'B';
	STR_Buffer[1].data[3] = 'A';
	STR_Buffer[1].length = 4;

	INNER_Status.content.new_str = 1;

	while(1)
	{
		//명령 수신
		detect_RX_Data();
		TIMER_Interrupt();
	}

	return 0;
}