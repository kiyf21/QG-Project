#include <REGX52.H>

#define LCD12864_DATA P0

sbit LCD12864_RS  = P2^6;
sbit LCD12864_RW  = P2^5;
sbit LCD12864_EN  = P2^7;
sbit LCD12864_PSB = P3^2;

void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void lcd12864_write_cmd(unsigned char cmd)
{
	LCD12864_RS = 0;
	LCD12864_RW = 0;
	LCD12864_EN = 0;
	Delay1ms();
	LCD12864_DATA = cmd;
	Delay1ms();
	LCD12864_EN = 1;
	Delay1ms();
	LCD12864_EN = 0;
}


void lcd12864_write_data(unsigned char dat)
{
	LCD12864_RS = 1;
	LCD12864_RW = 0;
	LCD12864_EN = 0;
	Delay1ms();
	LCD12864_DATA = dat;
	Delay1ms();
	LCD12864_EN = 1;
	Delay1ms();
	LCD12864_EN = 0;
}

void lcd12864_clear(void)
{
	lcd12864_write_cmd(0x01);
	Delay1ms();
}


void lcd12864_init(void)
{
	LCD12864_PSB=1;
	Delay1ms();
	lcd12864_write_cmd(0x30);
	Delay1ms();
	lcd12864_write_cmd(0x0C);
	Delay1ms();
	lcd12864_write_cmd(0x06);
	Delay1ms();
	lcd12864_write_cmd(0x01);
	Delay1ms();
}


void lcd12864_show_string(unsigned char x,unsigned char y,unsigned char *str)
{
	if(y<=0)y=0;
	if(y>3)y=3;
	x&=0x0f;
	
	switch(y)
	{
		case 0: x|=0x80;break;
		case 1: x|=0x90;break;
		case 2: x|=0x88;break;
		case 3: x|=0x98;break;
	}
	Delay1ms();
	lcd12864_write_cmd(x);
	Delay1ms();
	while(*str!='\0')
	{	
		lcd12864_write_data(*str);
		Delay1ms();
		str++;
		
	}
}














