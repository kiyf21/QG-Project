/*
					*** 定时器_头文件 ***
| 适配硬件:| HL-1开发板
===========================================================*/

#ifndef __TIMER_H__
#define __TIMER_H__

/******* 宏定义 *******/

/****** 变量声明 ******/
extern bit flag200ms;
extern u8 cntS;				//秒计数变量
extern u8 cntM;				//分计数变量
extern u8 cntH;				//时计数变量

/****** 函数声明 ******/
void timer0_init(u16);			//定时器0初始化
	
#endif