#include <REGX52.H>
#include "AT24C02.h"
#include "Delay.h"
#include "Key.h"
#include "LCD1602.h"
#include "UART.h"

unsigned char Read;//用于开机读取存储值的变量
unsigned char KeyNum;//按键变量
unsigned char ReadNum;//赋值上一次写入了多少个数值，用于开机串口数值的发送
unsigned char UART_Num=0;//用于串口写入数值的计数
unsigned char MaxNum;//记录本次写入了多少个数，并存在不属于数组的地址里，用于ReadNum读取
unsigned char Num[64];//创建一个数组使串口能够发送多个数据

void main()
{
	LCD_Init();
	UART_Init();
	ReadNum=AT24C02_ReadByte(65);//读取上一次写入了多少个数据
	if(ReadNum!=255)//检查ReadNum是否未被赋值，若从未被赋值，即未被写入数值，则不进行读取
	{
		for(MaxNum=0;MaxNum<ReadNum;MaxNum++)
		{
			Read=AT24C02_ReadByte(MaxNum);//开机读值
			Delay(5);
			UART_SendByte(Read);
		}
	}
	UART_Num=0;//用于清除串口读取造成的UART_Num变化
	while(1)
	{
		//LCD调试用代码
		LCD_ShowString(1,1,"ReadNum");
		LCD_ShowString(1,6,"UART_Num");
		LCD_ShowString(2,1,"MaxNum:");
		
		LCD_ShowNum(1,3,ReadNum,2);
		LCD_ShowNum(2,8,MaxNum,2);
		LCD_ShowNum(1,8,UART_Num,2);

		//按下按键3是串口发送的数值存入eeprom里
		KeyNum=Key();
		if(KeyNum)
		{
			if(KeyNum==3)
			{
				//决定写入数据后，将存于串口数组里的数据依次写入
				for(MaxNum=0;MaxNum<UART_Num;MaxNum++)
				{
					AT24C02_WriteByte(MaxNum,Num[MaxNum]);//写入串口值
					Delay(5);
				}
				AT24C02_WriteByte(65,MaxNum);
				
			}
		}
	}
}

void UART_Routine() interrupt 4
{
	//产生发送
	if(RI==1)
	{		
		Num[UART_Num]=SBUF;
		UART_SendByte(Num[UART_Num]);//发送回数值
		RI=0;
	}
	UART_Num++;
	if(UART_Num>64)UART_Num=0;
}

