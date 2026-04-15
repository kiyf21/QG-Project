#include "blood.h"

//定义一个血量数组
idata u8 Plot_Blood[PLOT_NUM_BLOOD];



// 初始化：所有地块都是空的//扩展到24地块用于处理僵尸和子弹的地块占用问题
void Plot_BLOOD_Init(void)
{
    u8 i;
    for(i=0; i<PLOT_NUM_BLOOD; i++)
    {
        Plot_Blood[i] = NOBLOOD;
    }
}


//定义地块标号为数组标号
static unsigned char Redefine_Plot_Num(unsigned char plot_id)
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


//读取地块的血量状态
u8 Get_Plot_Blood_State(u8 plot_id)
{
    unsigned char index = Redefine_Plot_Num(plot_id);
    if(index >= PLOT_NUM_BLOOD) return 0xFF;
    return Plot_Blood[index];
}


//改变地块的血量状态
void Set_Plot_Blood_State(u8 plot_id, u8 sta)
{
	unsigned char index = Redefine_Plot_Num(plot_id);
    if(index >= PLOT_NUM_BLOOD) return;
	if(sta<=0)
	{
		sta=0;
	}
    Plot_Blood[index] = sta;
}	


























