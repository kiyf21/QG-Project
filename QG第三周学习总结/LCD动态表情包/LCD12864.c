#include <REGX52.H>
#include "Delay.h"

//管脚定义
sbit LCD12864_RS  = P2^6;//数据命令选择
sbit LCD12864_WR  = P2^5;//读写选择
sbit LCD12864_E   = P2^7;//使能信号
sbit LCD12864_PSB = P3^2;//8位或4并口/串口选择

#define LCD12864_DATAPORT	P0	//LCD12864数据端口定义
#define Busy               0x80 //用于检测LCD状态字中的Busy标识

unsigned char ReadStatusLCD(void);//检测是否繁忙
void lcd12864_write_data(unsigned char dat);
void lcd12864_write_cmd(unsigned char cmd,BuysC);
void lcd12864_init(void);
void lcd12864_clear(void);
void DisplayImage (unsigned char code *DData);

//写数据
void lcd12864_write_data(unsigned char dat)
{
	ReadStatusLCD(); //检测忙
	LCD12864_RS=1;//选择数据
	LCD12864_WR=0;//选择写
	LCD12864_DATAPORT=dat;//准备数据
	delay_10us(1);
	LCD12864_E=1;
	LCD12864_E=1;
	LCD12864_E=1;//使能脚E先上升沿写入
	LCD12864_E=0;//使能脚E后负跳变完成写入
}

//写指令
void lcd12864_write_cmd(unsigned char cmd,BuysC)
{
	if (BuysC) ReadStatusLCD(); //根据需要检测忙 
	LCD12864_RS=0;//选择命令
	LCD12864_WR=0;//选择写
	LCD12864_DATAPORT=cmd;//准备命令
	delay_10us(1);
	LCD12864_E=1;
	LCD12864_E=1;
	LCD12864_E=1;//使能脚E先上升沿写入
	LCD12864_E=0;//使能脚E后负跳变完成写入
}

//读状态
unsigned char ReadStatusLCD(void)
{
	 LCD12864_DATAPORT = 0xFF; 
	 LCD12864_RS = 0;
	 LCD12864_WR = 1; 
	 LCD12864_E = 1;
	 while (LCD12864_DATAPORT & Busy); //检测忙信号
	 LCD12864_E = 0;
	 return(LCD12864_DATAPORT);
}

void lcd12864_init(void)
{
	//LCD12864_PSB=1;//选择8位或4位并口方式
	lcd12864_write_cmd(0x30,1);//数据总线8位，基本指令操作
	lcd12864_write_cmd(0x01,1);
	lcd12864_write_cmd(0x06,1);//写入新数据后光标右移，显示屏不移动
	lcd12864_write_cmd(0x0c,1);
}

void lcd12864_clear(void)
{
	lcd12864_write_cmd(0x01,1);	
	lcd12864_write_cmd(0x34,1);	
	lcd12864_write_cmd(0x30,1);	
} 


//图形显示122*32
void DisplayImage (unsigned char code *DData)
{
	unsigned char x,y,i;
	unsigned int tmp=0;
	
	lcd12864_write_cmd(0x34,1);  // 关闭绘图显示，进入指令模式
    lcd12864_write_cmd(0x36,1);  // 打开绘图模式
	
	for(i=0;i<9;){		//分两屏，上半屏和下半屏，因为起始地址不同，需要分开
	for(x=0;x<32;x++)
	{				//32行
		//lcd12864_write_cmd(0x34,1);
		lcd12864_write_cmd((0x80+x),1);//列地址
		lcd12864_write_cmd((0x80+i),1);	//行地址，下半屏，即第三行地址0X88
		//lcd12864_write_cmd(0x30,1);		
		for(y=0;y<16;y++)
		{
			lcd12864_write_data(DData[tmp+y]);//读取数据写入LCD
			//delay_10us(1);
		}
		tmp+=16;		
	}
	i+=8;
	}
	lcd12864_write_cmd(0x36,1);	//扩充功能设定
	lcd12864_write_cmd(0x30,1);
}

