#include <REGX52.H>
#include "LCD12864.h"
#include "Delay.h"
void main()
{

	lcd12864_init();
	lcd12864_show_string(0,0,"AAAAAAAA");
	lcd12864_show_string(1,0,"AAAAAAA");
	lcd12864_show_string(2,0,"AAAA");
	lcd12864_show_string(3,0,"AAA");
	while(1)
	{
		lcd12864_clear();
		Delay(1000);
	}
}
