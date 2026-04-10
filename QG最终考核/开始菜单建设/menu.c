#include "public.h"


unsigned char mLayer = 1;
unsigned char option = 1;
unsigned char i;

void show_menu();
void menu1();
void arrow_position(unsigned char arrowPos);
unsigned char pagenum();
void clear_arrow();

/**********************************************************|
| 描述	:| 菜单显示
| 参数	:| 无
| 返回值	:| 无
/***********************************************************/
void show_menu()
{
	if (mLayer == 1)								//当菜单层变量为1时
	{
		menu1();			//刷新显示一级菜单
		
	}
}	


void menu1()
{

	LCD12864_Show_String(1,0,"植物大战僵尸");
	LCD12864_Show_String(2,2, "游戏简介");				//显示第二行内容
	LCD12864_Show_String(2,3, "开始游戏");				//显示第三行内容
	arrow_position(1);
}

/***********************************************************|
| 名称	:| 显示箭头位置
| 参数	:| u8 arrowPos	-要显示页面指向箭头位置
| 返回值	:| 无
/***********************************************************/
void arrow_position(unsigned char arrowPos)
{			
	if (arrowPos==1)	
	{
		clear_arrow();
		LCD12864_Set_Location(1, 2);										//设置地址在第二行第一个字符处
	}
	else if (arrowPos==2)	
	{
		clear_arrow();
		LCD12864_Set_Location(1, 3);										//设置地址在第三行第一个字符处
	}
	LCD12864_Write_Data(' ');											//左半角英文字符位显示空格
	LCD12864_Write_Data(0x10);											//右半角英文字符位显示左箭头
}

/***********************************************************|
| 名称	:| 清除箭头显示
| 参数	:| 无
| 返回值	:| 无
/***********************************************************/
void clear_arrow()
{
	LCD12864_Show_String(1, 2, "  ");					//清除屏幕第二行最左边箭头显示区域
	LCD12864_Show_String(1, 3, "  ");					//清除屏幕第三行最左边箭头显示区域
}


