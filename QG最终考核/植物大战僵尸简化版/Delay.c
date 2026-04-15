#include "public.h"


void Delay_10us(unsigned int ten_us)
{
	while(ten_us--);	
}


void Delay_ms(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}
