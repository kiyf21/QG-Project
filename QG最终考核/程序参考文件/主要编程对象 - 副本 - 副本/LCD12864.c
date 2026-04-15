#include "pubilc.h"

//管脚定义
sbit LCD12864_RS  = P2^6;//数据命令选择
sbit LCD12864_WR  = P2^5;//读写选择
sbit LCD12864_E   = P2^7;//使能信号
sbit LCD12864_PSB = P3^2;//8位或4并口/串口选择

#define LCD12864_DATAPORT	P0	//LCD12864数据端口定义
#define Busy               0x80 //用于检测LCD状态字中的Busy标识

void LCD12864_Write_Cmd(unsigned char cmd,BuysC);
void LCD12864_Write_Data(unsigned char dat);
unsigned char LCD12864_Check_Status(void);
void LCD12864_Init(void);
void LCD12864_Clear(void);
void LCD_Flash(void);
void LCD12864_Show_String(unsigned char x,unsigned char y,unsigned char *str);
void LCD12864_Show_Onechar(unsigned char x, unsigned char y, unsigned char DData);
void LCD12864_Show_Image (unsigned char code *DData);
void LCD12864_Set_Location(unsigned char x, unsigned char y);

//写指令
void LCD12864_Write_Cmd(unsigned char cmd,BuysC)
{
	if (BuysC) LCD12864_Check_Status(); //根据需要检测忙 
	LCD12864_RS=0;//选择命令
	LCD12864_WR=0;//选择写
	LCD12864_DATAPORT=cmd;//准备命令
	Delay_10us(1);
	LCD12864_E=1;
	LCD12864_E=1;
	LCD12864_E=1;//使能脚E先上升沿写入
	LCD12864_E=0;//使能脚E后负跳变完成写入
}

//写数据
void LCD12864_Write_Data(unsigned char dat)
{
	LCD12864_Check_Status(); //检测忙
	LCD12864_RS=1;//选择数据
	LCD12864_WR=0;//选择写
	LCD12864_DATAPORT=dat;//准备数据
	Delay_10us(1);
	LCD12864_E=1;
	LCD12864_E=1;
	LCD12864_E=1;//使能脚E先上升沿写入
	LCD12864_E=0;//使能脚E后负跳变完成写入
}

//读状态
unsigned char LCD12864_Check_Status(void)
{
	 LCD12864_DATAPORT = 0xFF; 
	 LCD12864_RS = 0;
	 LCD12864_WR = 1; 
	 LCD12864_E = 1;
	 while (LCD12864_DATAPORT & Busy); //检测忙信号
	 LCD12864_E = 0;
	 return(LCD12864_DATAPORT);
}

//LCD初始化
void LCD12864_Init(void)
{
	//LCD12864_PSB=1;//选择8位或4位并口方式
	LCD12864_Write_Cmd(0x30,1);//数据总线8位，基本指令操作
	LCD12864_Write_Cmd(0x01,1);
	LCD12864_Write_Cmd(0x06,1);//写入新数据后光标右移，显示屏不移动
	LCD12864_Write_Cmd(0x0c,1);
}
//LCD清屏
void LCD12864_Clear(void)
{
	LCD12864_Write_Cmd(0x01,1);	
	LCD12864_Write_Cmd(0x34,1);	
	LCD12864_Write_Cmd(0x30,1);	
} 
//LCD写入位置，用于显示位置变化的字符
void LCD12864_Set_Location(unsigned char x, unsigned char y)
{
	unsigned char addr;								//光标RAM地址
	
	switch (y)
	{
		case 0: addr = 0x80 + x; break;		//设置光标在屏幕第一行x位置汉字位
		case 1: addr = 0x90 + x; break;		//设置光标在屏幕第二行x位置汉字位
		case 2: addr = 0x88 + x; break;		//设置光标在屏幕第三行x位置汉字位
		case 3: addr = 0x98 + x; break;		//设置光标在屏幕第四行x位置汉字位
		default: break;
	}
	LCD12864_Write_Cmd(addr,1);				//将光标RAM地址作为指令写入液晶	
	Delay_10us(10);							//延时
}

//LCD闪烁
void LCD_Flash(void)	//闪烁效果
{
	 LCD12864_Write_Cmd(0x08,1); //显示清屏
	 Delay_ms(400);
	 LCD12864_Write_Cmd(0x0c,1); // 显示开及光标设置
	 Delay_ms(400);
	 LCD12864_Write_Cmd(0x08,1); //显示清屏
	 Delay_ms(400);
	 LCD12864_Write_Cmd(0x0c,1); // 显示开及光标设置
	 Delay_ms(400);
	 LCD12864_Write_Cmd(0x08,1); //显示清屏
	 Delay_ms(400);
}

//第一种
//lcd12864_clear();
//lcd12864_show_string(0,0,"Hello World!");//第1行字符串显示
//delay_ms(400);
//delay_ms(400);
//第二种
//unsigned char  uctech[] = {"大雄电子营业部"};
//lcd12864_clear();
//lcd12864_show_string(0,0,uctech);	//显示字库中的中文数字
//delay_ms(400);
//delay_ms(400);
void LCD12864_Show_String(unsigned char x,unsigned char y,unsigned char *str)
{
	if(y<=0)y=0;
	if(y>3)y=3;
	x&=0x0f;	//限制x,y不能大于显示范围

	switch(y)
	{
		case 0: x|=0x80;break;//第1行地址+x的偏移
		case 1: x|=0x90;break;//第2行地址+x的偏移
		case 2: x|=0x88;break;//第3行地址+x的偏移
		case 3: x|=0x98;break;//第4行地址+x的偏移
	}
	LCD12864_Write_Cmd(x,1);
	while(*str!='\0')
	{
		LCD12864_Write_Data(*str);
		str++;		
	}	
} 

//lcd12864_clear();
//lcd12864_show_onechar(0,0,0x41);
//delay_ms(400);
//delay_ms(400);
//按指定位置显示一个字符
void LCD12864_Show_Onechar(unsigned char x, unsigned char y, unsigned char DData)
{
	if(y<=0)y=0;
	if(y>3)y=3;
	x&=0x0f;	//限制x,y不能大于显示范围

	switch(y)
	{
		case 0: x|=0x80;break;//第1行地址+x的偏移
		case 1: x|=0x90;break;//第2行地址+x的偏移
		case 2: x|=0x88;break;//第3行地址+x的偏移
		case 3: x|=0x98;break;//第4行地址+x的偏移
	}
	LCD12864_Write_Cmd(x,0); //这里不检测忙信号，发送地址码
	LCD12864_Write_Data(DData);
}

//图形显示128*64
void LCD12864_Show_Image (unsigned char code *DData)
{
	unsigned char x,y,i;
	unsigned int tmp=0;
	
	LCD12864_Write_Cmd(0x34,1);  // 关闭绘图显示，进入指令模式
    LCD12864_Write_Cmd(0x36,1);  // 打开绘图模式
	
	for(i=0;i<9;){		//分两屏，上半屏和下半屏，因为起始地址不同，需要分开
		for(x=0;x<32;x++){				//32行
			LCD12864_Write_Cmd((0x80+x),1);//列地址
			LCD12864_Write_Cmd((0x80+i),1);	//行地址，下半屏，即第三行地址0X88	
			for(y=0;y<16;y++)
			{
				LCD12864_Write_Data(DData[tmp+y]);//读取数据写入LCD
			}
			tmp+=16;		
		}
		i+=8;
	}
	LCD12864_Write_Cmd(0x36,1);	//扩充功能设定
	LCD12864_Write_Cmd(0x30,1);
}





//轨道一的统一使用函数
void LCD12864_Show_ImageTrack1 (unsigned char code *DData,unsigned char i)
{
	unsigned char x,y;
	unsigned int tmp=0;
	
	LCD12864_Write_Cmd(0x34,1);  // 关闭绘图显示，进入指令模式
    LCD12864_Write_Cmd(0x36,1);  // 打开绘图模式
	
	//分两屏，上半屏和下半屏，因为起始地址不同，需要分开
	for(x=13;x<29;x++){				//32行
		LCD12864_Write_Cmd((0x80+x),1);//列地址
		LCD12864_Write_Cmd((0x80+i),1);	//行地址	
		for(y=0;y<2;y++)
		{
			LCD12864_Write_Data(DData[tmp+y]);//读取数据写入LCD
		}
		tmp+=2;		
	}
	LCD12864_Write_Cmd(0x36,1);	//扩充功能设定
	LCD12864_Write_Cmd(0x30,1);
}
//轨道二的统一使用函数
void LCD12864_Show_ImageTrack2 (unsigned char code *DData,unsigned char z)
{
	unsigned char x,y,i;
	unsigned int tmp=0;
	
	LCD12864_Write_Cmd(0x34,1);  // 关闭绘图显示，进入指令模式
    LCD12864_Write_Cmd(0x36,1);  // 打开绘图模式
	
	for(i=0;i<9;)//分两屏，上半屏和下半屏，因为起始地址不同，需要分开
	{		
		if(i==0)
		{
			for(x=30;x<32;x++)//32行
			{				
				LCD12864_Write_Cmd((0x80+x),1);//列地址
				LCD12864_Write_Cmd((0x80+i+z),1);	//行地址，下半屏，即第三行地址0X88	
				for(y=0;y<2;y++)
				{
					LCD12864_Write_Data(DData[tmp+y]);//读取数据写入LCD
				}
				tmp+=2;		
			}
		}
		else
		{
			for(x=0;x<14;x++)//32行
			{				
				LCD12864_Write_Cmd((0x80+x),1);//列地址
				LCD12864_Write_Cmd((0x80+i+z),1);	//行地址，下半屏，即第三行地址0X88	
				for(y=0;y<2;y++)
				{
					LCD12864_Write_Data(DData[tmp+y]);//读取数据写入LCD
				}
				tmp+=2;
			}
		}
		i+=8;
	}
	LCD12864_Write_Cmd(0x36,1);	//扩充功能设定
	LCD12864_Write_Cmd(0x30,1);
}
//轨道三的统一使用函数
void LCD12864_Show_ImageTrack3 (unsigned char code *DData,unsigned char i)
{
	unsigned char x,y;
	unsigned int tmp=0;
	
	LCD12864_Write_Cmd(0x34,1);  // 关闭绘图显示，进入指令模式
    LCD12864_Write_Cmd(0x36,1);  // 打开绘图模式
	
	//分两屏，上半屏和下半屏，因为起始地址不同，需要分开
	for(x=15;x<31;x++){				//32行
		LCD12864_Write_Cmd((0x80+x),1);//列地址
		LCD12864_Write_Cmd((0x80+8+i),1);	//行地址，下半屏，即第三行地址0X88	
		for(y=0;y<2;y++)
		{
			LCD12864_Write_Data(DData[tmp+y]);//读取数据写入LCD
		}
		tmp+=2;		
	}
	LCD12864_Write_Cmd(0x36,1);	//扩充功能设定
	LCD12864_Write_Cmd(0x30,1);
}










