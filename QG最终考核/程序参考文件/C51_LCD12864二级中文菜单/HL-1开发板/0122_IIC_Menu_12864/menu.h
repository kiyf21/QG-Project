/*
					*** 设置菜单_头文件 ***
| 适配硬件:| HL-1开发板
===========================================================*/

#ifndef __MENU_H__
#define __MENU_H__

/******* 宏定义 *******/

/****** 变量声明 ******/
extern bit flag_keyAc;
extern u8 page;
extern u8 mLayer;
extern u8 arrowPos1;
extern u8 arrowPos11;				//一级菜单项目1下的二级菜单箭头位置索引
extern u8 arrowPos12;				//一级菜单项目2下的二级菜单箭头位置索引
extern u8 arrowPos13;				//一级菜单项目3下的二级菜单箭头位置索引
extern u8 arrowPos14;				//一级菜单项目4下的二级菜单箭头位置索引
extern u8 arrowPos15;				//一级菜单项目5下的二级菜单箭头位置索引
extern u8 arrowPos16;				//一级菜单项目6下的二级菜单箭头位置索引
extern u8 arrowPos17;				//一级菜单项目7下的二级菜单箭头位置索引
extern u8 arrowPos18;				//一级菜单项目8下的二级菜单箭头位置索引

extern u8 page11;					//一级菜单项目1下的二级菜单页索引
extern u8 page12;					//一级菜单项目2下的二级菜单页索引
extern u8 arrowPos11;				//一级菜单项目1下的二级菜单箭头位置索引
extern u8 arrowPos12;				//一级菜单项目2下的二级菜单箭头位置索引


/****** 函数声明 ******/
//主菜单
void enter_set();					//进入设置
void exit_set();					//退出设置				
void down_key();					//下按键程序
void down_keyHold();				//下按键持续按下程序
void up_key();						//上按键程序
void up_keyHold();					//上按键持续按下程序
void enter_menu2();					//ENTER键单击进入二级菜单或设置项界面
void return_menu();					//ESC键单击返回上级菜单
void arrow_position(u8);			//显示箭头位置
void clear_arrow();					//清除显示的箭头

//二级菜单
void clear_areaStr();				//清除显示屏上面三行字符
void menu2();						//二级菜单
void menu11();						//一级菜单项目1下的二级菜单页显示
void menu12();						//一级菜单项目2下的二级菜单页显示
void menu13();						//一级菜单项目3下的二级菜单页显示
void menu14();						//一级菜单项目4下的二级菜单页显示
void menu15();						//一级菜单项目5下的二级菜单页显示
void menu16();						//一级菜单项目6下的二级菜单页显示
void menu17();						//一级菜单项目7下的二级菜单页显示
void menu18();						//一级菜单项目8下的二级菜单页显示

//子菜单设置项（三级）
void enter_setItem();				//进入项目设置界面
void leftKey();						//左按键程序
void rightKey();					//右按键程序
void add_dat();						//递增数据
void sub_dat();						//递减数据
void save_dat();					//保存数据

	
#endif