#include "pubilc.h"


// ====================== 菜单状态定义 ======================
typedef enum {
    MENU_MAIN,      // 主菜单
    MENU_GAME_INFO, // 游戏简介
    MENU_LEVEL_SEL, // 难度选择
    GAME_PLAYING    // 进入游戏
} MenuState;

// ====================== 全局变量 ======================
MenuState now_state = MENU_MAIN;  // 当前状态
u8 main_sel = 0;                  // 主菜单选择 0=简介 1=开始
u8 level_sel = 0;                 // 难度选择 0=简单 1=普通 2=困难
u8 game_difficulty = 0;          // 最终难度
// ====================== 菜单显示函数 ======================

// 显示主菜单
static void Show_MainMenu(void)
{
    LCD12864_Clear();
    LCD12864_Show_String(1, 0, "植物大战僵尸");

    if(main_sel == 0)
	{
		LCD12864_Set_Location(1,1);
		LCD12864_Write_Data(' ');											//左半角英文字符位显示空格
		LCD12864_Write_Data(0x10);
        LCD12864_Show_String(2, 1, "游戏简介");
	}
    else
	{
		LCD12864_Show_String(1, 1, "  ");		
        LCD12864_Show_String(2, 1, "游戏简介");
	}

    if(main_sel == 1)
	{
		LCD12864_Set_Location(1,2);
		LCD12864_Write_Data(' ');											//左半角英文字符位显示空格
		LCD12864_Write_Data(0x10);
        LCD12864_Show_String(2, 2, "开始游戏");
	}
    else
	{
		LCD12864_Show_String(1, 2, "  ");
        LCD12864_Show_String(2, 2, "开始游戏");
	}
}

// 显示游戏简介
static void Show_GameInfo(void)
{
    LCD12864_Clear();
    LCD12864_Show_String(2,0,"游戏介绍");
    LCD12864_Show_String(0,1,"种植植物防御僵尸");
    LCD12864_Show_String(1,2,"51+LCD制作");
    LCD12864_Show_String(1,3,"按任意键返回");
	//while(MatrixKey() == 0);
}

// 显示难度选择
static void Show_LevelSel(void)
{
    LCD12864_Clear();
    LCD12864_Show_String(2,4,"难度选择");

    if(level_sel == 0)
	{
		LCD12864_Set_Location(1,0);
		LCD12864_Write_Data(' ');											//左半角英文字符位显示空格
		LCD12864_Write_Data(0x10);
        LCD12864_Show_String(3,0,"简单");
	}
    else
	{
		LCD12864_Show_String(1, 0, "  ");
        LCD12864_Show_String(3,0,"简单");
	}

    if(level_sel == 1)
	{
		LCD12864_Set_Location(1,2);
		LCD12864_Write_Data(' ');											//左半角英文字符位显示空格
		LCD12864_Write_Data(0x10);
        LCD12864_Show_String(3,2,"困难");
	}
    else
	{
		LCD12864_Show_String(1, 2, "  ");
        LCD12864_Show_String(3,2,"困难");
	}
}

// 显示开始游戏提示
static void Show_GameStart(void)
{
    LCD12864_Clear();
    LCD12864_Show_String(0,0,"按任意键游戏开始");
    if(game_difficulty == 0) LCD12864_Show_String(3,3,"难度：简单");
    if(game_difficulty == 1) LCD12864_Show_String(3,3,"难度：困难");
}

// ====================== 菜单逻辑 ======================
//菜单按钮控制
static void MainMenu_Key(u8 key)
{
    if(key == 2) // 上
    {
        if(main_sel > 0) main_sel--;
    }
    if(key == 10) // 下
    {
        if(main_sel < 1) main_sel++;
    }
    if(key == 6) // 确定
    {
        if(main_sel == 0) now_state = MENU_GAME_INFO;//状态切换为游戏简介
        if(main_sel == 1) now_state = MENU_LEVEL_SEL;//状态切换为难度选择
    }
    Show_MainMenu();
}
//返回按钮控制
static void GameInfo_Key(u8 key)
{
	Show_GameInfo();
    if(key != 0) // 任意键返回
    {
        now_state = MENU_MAIN;//状态切换为菜单主页面
        Show_MainMenu();
    }
}
//难度按钮控制
static void LevelSel_Key(u8 key)
{
    if(key == 2)
    {
        if(level_sel > 0) level_sel--;
    }
    if(key == 10)
    {
        if(level_sel < 1) level_sel++;
    }
    if(key == 6)
    {
        game_difficulty = level_sel;
		Show_GameStart();
        now_state = GAME_PLAYING;
        
    }
    Show_LevelSel();
}



// ====================== 菜单总运行 ======================
void Menu_Run(void)
{
    u8 key;
	u8 last_state = 0xFF; // 记录上一状态，用于自动刷新
    Show_MainMenu();

    while(1)
    {
		if(now_state != last_state)
        {
            last_state = now_state;
            switch(now_state)
            {
                case MENU_MAIN:      Show_MainMenu();    break;
                case MENU_GAME_INFO: Show_GameInfo();    break;
                case MENU_LEVEL_SEL: Show_LevelSel();    break;
                case GAME_PLAYING:   Show_GameStart();   break;
            }
        }
        key = MatrixKey();
        if(key == 0) continue;
        switch(now_state)
        {
            case MENU_MAIN:      MainMenu_Key(key);    break;
            case MENU_GAME_INFO: GameInfo_Key(key);    break;
            case MENU_LEVEL_SEL: LevelSel_Key(key);    break;
            case GAME_PLAYING:   Game_Main();          break;
        }
    }
}