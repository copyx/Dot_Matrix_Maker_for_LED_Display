#include <stdio.h>
#include "display.h"
#include "comm.h"

int main(void)
{
	//프로그램 초기화
	init_Comm();
	init_Display();

	//명령 수신
	detect_RX_Data();

	return 0;
}