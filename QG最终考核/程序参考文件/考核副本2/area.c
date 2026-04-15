#include "area.h"

extern code unsigned char IMG_DATA_Empty[32];
extern code unsigned char IMG_DATA_Position[32];



// 定义一块地的状态
u8 Plot_State[PLOT_NUM];  //用数组来存地块状态


// 初始化：所有地块都是空的//扩展到24地块用于处理僵尸和子弹的地块占用问题
void Plot_Init(void)
{
    u8 i;
    for(i=0; i<PLOT_NUM; i++)
    {
        Plot_State[i] = EMPTY;
    }
}

//定义地块标号为数组标号
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
		case 13: return 6;
        case 23: return 7;
        case 33: return 8;
        case 14: return 9;
        case 24: return 10;
        case 34: return 11;
		case 15: return 12;
        case 25: return 13;
        case 35: return 14;
        case 16: return 15;
        case 26: return 16;
        case 36: return 17;
		case 17: return 18;
        case 27: return 19;
        case 37: return 20;
        case 18: return 21;
        case 28: return 22;
        case 38: return 23;
        default: return 0xFF;
    }
}

// ===================== 查询状态 =====================
// 功能：输入地块编号(0~23)，返回它的状态
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
    //if(sta > POTATO) return; // 只允许 0 1 2
    
    Plot_State[index] = sta;
}



