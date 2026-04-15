/*
			*** lcd12864中文液晶_头文件 ***
| 适配硬件:| HL-1开发板
===========================================================*/

#ifndef __LCD12864_H__
#define __LCD12864_H__

/******* 宏定义 *******/
#define DB P0

/****** 引脚定义 ******/
sbit RS = P1^0;
sbit RW = P1^1;
sbit E  = P2^5;

/******* 函数声明 *******/
void lcd12864_write_cmd(u8);							//往液晶写入一个字节的指令
void lcd12864_write_dat(u8);							//往液晶写入一个字节的数据
void lcd12864_set_cursor(u8, u8);						//设置光标在液晶屏幕的位置
void lcd12864_show_str(u8, u8, u8 *);					//在屏幕指定位置显示字符串
void lcd12864_clear_str(u8, u8, u8);					//在屏幕指定位置清除字符串
void lcd12864_show_img(u8, u8, u8, u8, u8 *);			//在屏幕指定位置显示一幅图像
void lcd12864_clear_area(u8, u8, u8, u8, bit);			//清除屏幕上的一块图形显示区域
//void lcd12864_clear_char(u8, u8, bit);					//反白屏幕指定位置的半角字符位
void lcd12864_init();									//lcd12864液晶初始化
void showDec_byte(u8, u8, u8);							//将一个字节的数据在液晶指定位置以十进制显示
//void long_str(u8, u8, signed long *);					//将一个长整型数转字符串在屏幕指定位置显示
	
#endif