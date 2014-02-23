#include "display.h"

INNER_String STR_Buffer[2];
STR_BUFF_STAT STR_Status;

void init_STR_Buffer(void)
{
	STR_Status.total_bits = 0;
}

//둘 중 하나만 사용
void init_INNER_Timer(void)
{
}

//void init_OUTER_Timer(void)
//{
//}

void init_Display(void)
{
	init_STR_Buffer();
	init_INNER_Timer();
	//init_OUTER_Timer();
}
