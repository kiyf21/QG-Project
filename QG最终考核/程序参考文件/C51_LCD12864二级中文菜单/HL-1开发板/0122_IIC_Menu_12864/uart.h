/*
					*** 串口通信_头文件 ***
| 适配硬件:| HL-1开发板
===========================================================*/

#ifndef __UART_H__
#define __UART_H__

/******* 宏定义 *******/


/****** 变量声明 ******/
extern bit flagUartRx;
//extern u8 rxSbuf;

/****** 函数声明 ******/
void uart_init(u16);			//uart/定时器1初始化
//void uart_txByte(u8);			//串口发送一个字节数据
void pro_uartRx();				//处理串口接收数据
	
#endif