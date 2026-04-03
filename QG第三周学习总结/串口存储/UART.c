#include <REGX52.H>
/**
  * @brief  串口初始化 4800bps@12.000MHz
  * @param 	无
  * @retval	无
  */
void UART_Init()//4800bps@12.000MHz
{
	SCON=0x50;
	PCON |= 0x80;
	//串口配置寄存器一
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF4;		//设定定时初值   	单片机不同从0xF3改到0xF4
	TH1 = 0xF4;		//设置定时初值		单片机不同从0xF3改到0xF4
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;
	ES=1;
}
/**
  * @brief 串口发送一个字节数据
  * @param	Byte 要发送的一个字节数据
  * @retval	无
  */

void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}