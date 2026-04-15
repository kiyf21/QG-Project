/*
					*** IIC_头文件 ***
| 适配硬件:| HL-1开发板
===========================================================*/

#ifndef __IIC_H__
#define __IIC_H__

/******* 宏定义 *******/
#define iic_delay5us() {_nop_(); _nop_(); _nop_(); _nop_();}

/****** 引脚定义 ******/
sbit SDA = P2^0;
sbit SCL = P2^1;

/****** 变量声明 ******/

/****** 函数声明 ******/	
void iic_start();					//向IIC总线发送起始信号
void iic_stop();					//向IIC总线发送停止信号
bit iic_write_byte(u8);				//向IIC总线发送一个字节的数据并等待从机应答
u8 iic_read_byte();					//从IIC总线读取一个字节的数据
//bit iic_slave_ack();				//主机处理从机应答
void iic_master_ackOrNack(bit);		//主机发送应答或非应答信号
	
#endif