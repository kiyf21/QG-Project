#include "pubilc.h"




// 定义一块地的状态
u8 Plot_State[PLOT_NUM];  //用数组来存地块状态，例如{0，0，0，0，1，2}

static unsigned char PlotID_To_Index(unsigned char plot_id)
{
    switch(plot_id)
    {
        case 11: return 0;
        case 21: return 1;
        case 31: return 2;
        case 12: return 3;
        case 22: return 4;
        case 32: return 5;
        default: return 0xFF;
    }
}
// 初始化：所有地块都是空的
void Plot_Init(void)
{
    u8 i;
    for(i=0; i<PLOT_NUM; i++)
    {
        Plot_State[i] = EMPTY;
    }
}

// ===================== 查询状态 =====================
// 功能：输入地块编号(0~5)，返回它的状态
u8 Get_Plot_State(u8 plot_id)
{
    unsigned char index = PlotID_To_Index(plot_id);
    if(index >= PLOT_NUM) return 0xFF;
    return Plot_State[index];
}

// ===================== 改变状态 =====================
// 功能：输入地块编号 + 新状态，直接修改
void Set_Plot_State(u8 plot_id, u8 sta)
{
	unsigned char index = PlotID_To_Index(plot_id);
    if(index >= PLOT_NUM) return;
    if(sta > POTATO) return; // 只允许 0 1 2
    
    Plot_State[index] = sta;
}