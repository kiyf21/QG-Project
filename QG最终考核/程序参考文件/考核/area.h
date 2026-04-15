#ifndef __AREA_H__
#define __AREA_H__

#include "pubilc.h"
// 地块状态定义
#define EMPTY    0   // 空
#define PEA      1   // 豌豆
#define POTATO   2   // 土豆
#define BULLET   3   // 子弹
#define ZOMBIE   4   // 僵尸

// 一共有多少块地
#define PLOT_NUM    24 

extern xdata unsigned char Plot_State[PLOT_NUM]; //将数组定义为全局，用于子弹，扣血，僵尸攻击调用

void Plot_Init(void);
unsigned char Get_Plot_State(unsigned char plot_id);
void Set_Plot_State(unsigned char plot_id, unsigned char sta);

#endif
