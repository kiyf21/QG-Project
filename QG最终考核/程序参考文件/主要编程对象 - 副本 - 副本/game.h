#ifndef __GAME_H__
#define __GAME_H__

#include "pubilc.h"
// 状态枚举
typedef enum {
    KEY_CHOOSE,
    KEY_PLANT,
    KEY_REMOVE
} GameState;

// 声明外部变量 → 让所有文件都能看到
extern GameState now_state_1;

void Game_Main(void);


#endif