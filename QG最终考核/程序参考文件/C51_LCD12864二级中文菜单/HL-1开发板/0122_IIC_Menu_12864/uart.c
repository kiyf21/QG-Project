/*
					*** 串口通信_c文件 ***
| 适配硬件:| HL-1开发板
===========================================================*/

#include "public.h"

bit flagUartRx = 0;			//串口接收标志位
u8 rxSbuf[2];				//串口接收数据缓冲区

/***********************************************************|
| 名称	:| uart/定时器1初始化
| 参数	:| u16 band	- 串口通信波特率
| 返回值	:| 无
/***********************************************************/
void uart_init(u16 band)
{
	TH1 = 256 - (11059200/12/32/band);		//计算band波特率下定时器1的重载值
	TL1 = TH1;								//定时器1装初值
	
	TMOD = TMOD & 0x0F | 0x20;				//保持定时器0设置不变，配置定时器1工作模式2(8位自动重载)
	SCON = 0x50;							//配置串口通信模式2，使能接收数据
	ET1 = 0;								//禁用定时器1中断
	ES = 1;									//打开uart中断
	TR1 = 1;								//启动定时器1
}


/***********************************************************|
| 名称	:| uart发送一个字节数据
| 参数	:| u8 dat	- 待发送一个字节的数据
| 返回值	:| 无
/***********************************************************/
//void uart_txByte(u8 dat)
//{
//	ES = 0;			//关闭串口中断，防止发送数据时被串口中断打断
//	SBUF = dat;		//将数据送到uart发送缓冲区，发送出去
//	while (~TI);	//等待一个字节数据发送完毕
//	TI = 0;			//清0串口中断发送标志位
//	ES = 1;			//打开串口中断
//}


/***********************************************************|
| 名称	:| 处理串口接收数据
| 参数	:| u8 dat	- 待发送一个字节的数据
| 返回值	:| 无
/***********************************************************/
void pro_uartRx()
{	
	switch (rxSbuf[0])
	{
		case 0x26: up_key(); 		flag_keyAc = 1;	break;		//单击【上】上翻菜单标题/递增设置数据
		case 0x56: up_keyHold(); 	flag_keyAc = 1;	break;		//持续按下【上】
		case 0x28: down_key();		flag_keyAc = 1;	break;		//单击【下】下翻菜单标题/递减设置数据
		case 0x58: down_keyHold(); 	flag_keyAc = 1;	break;		//持续按下【下】
		case 0x25: leftKey(); 		flag_keyAc = 1;	break;		//设置项左移
		case 0x27: rightKey(); 		flag_keyAc = 1;	break;		//设置项右移
		case 0x0D: enter_menu2(); 	flag_keyAc = 1;	break;		//单击【ENTER】进入二级菜单/确认并保存当前设置数据
		case 0x2D: enter_set(); 	flag_keyAc = 1;	break;		//长按【ENTER】进入设置
		case 0x1B: return_menu(); 	flag_keyAc = 1;	break;		//返回上级菜单
		case 0x3B: exit_set(); 		flag_keyAc = 1;	break;		//长按【ESC】退出设置
		
		case 0xA0:
			lcd12864_show_str(0,0, "写");						//在Lcd12864屏幕第3行输出提示信息
			lcd12864_show_str(7,0, "!!"); 			break;		//在Lcd12864屏幕第4行输出提示信息			
		case 0xA1:
			lcd12864_show_str(0,0, "读");						//在Lcd12864屏幕第3行输出提示信息
			lcd12864_show_str(7,0, "!!"); 			break;		//在Lcd12864屏幕第4行输出提示信息
		
		case 0xA2: year	 = rxSbuf[1]; 				break;		//处理年份数据
		case 0xA3: week  = rxSbuf[1]; 				break;		//处理星期数据
		case 0xA4: month = rxSbuf[1]; 				break;		//处理月份数据
		case 0xA5: day   = rxSbuf[1]; 				break;		//处理日数据
		case 0xAB: cntH  = rxSbuf[1]; 				break;		//处理小时数据
		case 0xAC: cntM  = rxSbuf[1]; 				break;		//处理分钟数据
		case 0xAD: cntS  = rxSbuf[1]; 				break;		//处理秒数据
				
		default: break;
	}
}


/***********************************************************|
| 名称	:| uart中断服务函数
| 参数	:| 无
| 返回值	:| 无
/***********************************************************/
void uart() interrupt 4
{
	static bit flagRxCnt = 0;			//接收次数
	
	if (RI)						
	{
		RI = 0;
		rxSbuf[flagRxCnt] = SBUF;		//将接收的数据放数组中
		if (flagRxCnt)					//接收次数达2
		{
			flagUartRx = 1;				//全部数据接收完成标志位置1		
		}
		flagRxCnt = ~flagRxCnt;			//接收次数标志位取反		
	}
	
	if (TI)
	{
		TI = 0;
	}
}