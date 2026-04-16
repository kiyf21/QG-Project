#ifndef __MENU_H__
#define __MENU_H__


typedef enum {
    MENU_MAIN,      // 主菜单
    MENU_GAME_INFO, // 游戏简介
    MENU_LEVEL_SEL, // 难度选择
    GAME_PLAYING,    // 进入游戏
	GAME_SETTLEMENT,  //游戏结算
	SAVE_CHECK
} MenuState;

//// ====================== 菜单状态定义 ======================
//typedef enum {
//    MENU_MAIN,      // 主菜单
//    MENU_GAME_INFO, // 游戏简介
//    MENU_LEVEL_SEL, // 难度选择
//    GAME_PLAYING    // 进入游戏
//} MenuState;
extern MenuState now_state;
//// ====================== 全局变量 ======================
//MenuState now_state = MENU_MAIN;  // 当前状态
//u8 main_sel = 0;                  // 主菜单选择 0=简介 1=开始
//u8 level_sel = 0;                 // 难度选择 0=简单 1=普通 2=困难
//u8 game_difficulty = 0;          // 最终难度

// ====================== 函数声明 ======================
void Menu_Main(void);
void Menu_Run(void);
void Show_MainMenu(void);

#endif
