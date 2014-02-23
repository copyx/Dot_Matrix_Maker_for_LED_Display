#include <stdio.h>
#include "display.h"
#include "comm.h"

#define LED_CHAR_WIDTH		16
#define NUMBER_OF_LED_CHAR	26

//47이 1cm 간격으로 계산했을 때 라인 수. 타이밍 계산의 용이함을 위해 48로 변경
#define INNER_DISPLAY_WIDTH	48
#define OUTER_DISPLAY_WIDTH	64

#define MAXIMUM_NUMBER_OF_USER_IMG		10
#define MAXIMUM_NUMBER_OF_DEFAULT_IMG	3

#define NUMBER_OF_MUSIC_LEVEL	16
#define MAXIMUM_LENGTH_OF_LEVEL	256	


typedef union Inner_Display_Line
{
	unsigned char bytes[2];
	unsigned short total_bits;
}LED_Char;

typedef struct Outer_Display_Line
{
	unsigned char byte[4];
	unsigned int total_bits;
}OUTER_Line;

typedef struct Outer_Dot_Matrix
{
	unsigned char line_color_info[8];
	OUTER_Line dots[OUTER_DISPLAY_WIDTH];
}OUTER_Matrix;

LED_Char base_characters[LED_CHAR_WIDTH][NUMBER_OF_LED_CHAR];

OUTER_Matrix IMG_Buffer[MAXIMUM_NUMBER_OF_USER_IMG];
OUTER_Matrix default_music_image[MAXIMUM_NUMBER_OF_DEFAULT_IMG][NUMBER_OF_MUSIC_LEVEL];

unsigned char LEVEL_Data_Buffer[2][MAXIMUM_LENGTH_OF_LEVEL];

int main(void)
{
	//프로그램 초기화
	init_Display();

	//명령 수신
	detect_RX_Data();

	return 0;
}