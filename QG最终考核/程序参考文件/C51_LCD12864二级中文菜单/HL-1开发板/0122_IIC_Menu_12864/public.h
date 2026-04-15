/*
				*** 公共部分_头文件 ***
| 适配硬件:| HL-1开发板
===========================================================*/

#ifndef __PUBLIC_H__
#define __PUBLIC_H__

/****** 包含头文件 ******/
#include <reg52.h>
#include <intrins.h>
#include "timer.h"
#include "lcd12864.h"
#include "uart.h"
#include "menu.h"

/****** 变量声明 ******/
extern bit flag_autoExit;				//自动退出设置标志位
extern u8 year;
extern u8 month;
extern u8 day;
extern u8 week;

/******* 函数声明 *******/
void delay100us();						//延时100us
void delay5ms();						//延时5ms
void show_byte(u8 dat, u8 type);		//将一个字节的数据以指定进制方式在Lcd屏显示
	
#endif