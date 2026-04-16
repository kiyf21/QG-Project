#include "bullet.h"

extern u8 score;

extern code unsigned char IMG_DATA_Empty[32];
code u8 One_Bullet[] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x03,0xC0,0x03,0xC0,0x01,0x80,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*' ',0*/
};
code u8 Two_Bullet[] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x3C,0x3C,0x3C,0x3C,0x18,0x18,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*' ',0*/
};

typedef enum {
	OEPL,
	PLPL,
	NOPL,
} PlantState;


u8 Position_Item;

// 轨道1
PlantState Plant_state1 = NOPL;
PlantState last_state1  = NOPL;
static u8 bullet_pos1   = 2;
u8 addr_track1=13;

// 轨道2
PlantState Plant_state2 = NOPL;
PlantState last_state2  = NOPL;
static u8 bullet_pos2   = 2;
u8 addr_track2=23;
// 轨道3
PlantState Plant_state3 = NOPL;
PlantState last_state3  = NOPL;
static u8 bullet_pos3   = 2;
u8 addr_track3=33;

void Bullet_Normal(u8 track);
void Change_Plant_state_All(void);


void Bullet_Main(void)
{
	Change_Plant_state_All();
	Bullet_Normal(0);
	Bullet_Normal(1);
	Bullet_Normal(2);
}


// ====================== 检测3个轨道的植物状态 ======================
void Change_Plant_state_All(void)
{
    // 所有变量必须定义在函数最顶部！
    unsigned char left1, right1, pot1;
    unsigned char left2, right2, pot2;
    unsigned char left3, right3, pot3;

    // ========== 轨道1 ==========
    left1  = (Plot_State[0] == 1);
    right1 = (Plot_State[3] == 1);
    pot1   = (Plot_State[3] == 2);
    if(left1 && right1)      Plant_state1 = PLPL;
    else if(left1 || right1 || (left1 && pot1)) Plant_state1 = OEPL;
    else                    Plant_state1 = NOPL;

    // ========== 轨道2 ==========
    left2  = (Plot_State[1] == 1);
    right2 = (Plot_State[4] == 1);
    pot2   = (Plot_State[4] == 2);
    if(left2 && right2)      Plant_state2 = PLPL;
    else if(left2 || right2 || (left2 && pot2)) Plant_state2 = OEPL;
    else                    Plant_state2 = NOPL;

    // ========== 轨道3 ==========
    left3  = (Plot_State[2] == 1);
    right3 = (Plot_State[5] == 1);
    pot3   = (Plot_State[5] == 2);
    if(left3 && right3)      Plant_state3 = PLPL;
    else if(left3 || right3 || (left3 && pot3)) Plant_state3 = OEPL;
    else                    Plant_state3 = NOPL;
}

void Bullet_Normal(u8 track)
{
	// 1. 定义所有需要的指针
    PlantState *Plant_state;  // 状态指针
    PlantState *last_state;    // 上一次状态指针
	u8 *addr_track;
    u8 *a;                     // 子弹位置指针
    void (*p)(unsigned char code *DData,unsigned char i); // 函数指针
	Position_Item=11+10*track;
	
	switch(track)
	{
		case 0:
			Plant_state=&Plant_state1;
			last_state=&last_state1;
			addr_track=&addr_track1;
			p=LCD12864_Show_ImageTrack1;
			a=&bullet_pos1;
			break;
		case 1:
			Plant_state=&Plant_state2;
			last_state=&last_state2;
			addr_track=&addr_track2;
			p=LCD12864_Show_ImageTrack2;
			a=&bullet_pos2;
			break;
		case 2:
			Plant_state=&Plant_state3;
			last_state=&last_state3;
			addr_track=&addr_track3;
			p=LCD12864_Show_ImageTrack3;
			a=&bullet_pos3;
			break;
	}
	
    if(*Plant_state == NOPL)
    {
        if(*last_state != NOPL)
        {
            p(One_Bullet, *a);
            *a = 2;
        }
        *last_state = NOPL;
        return;
    }
	
	
    if(delay_noblock(track,200))
    {
		//////////////////////
		if(Get_Plot_State(Position_Item +1) == ZOMBIE||Get_Plot_State(Position_Item + 2) == ZOMBIE)
		{
			*last_state = *Plant_state;
			//当在第二格有僵尸时
			if(Get_Plot_State(Position_Item +1) == ZOMBIE)
			{
				
				if(*Plant_state == OEPL)
				{
					Set_Plot_Blood_State(*addr_track,Get_Plot_Blood_State(*addr_track)-20);
				}
				if(Get_Plot_Blood_State(*addr_track)<=0)
				{
					Set_Plot_State(Position_Item +1, EMPTY);       // 清除僵尸
					p(IMG_DATA_Empty, Position_Item +1);     // 清屏
					(*addr_track)++;
					score++;
					Game_Show_Score(1,0,score);
				}
				return;
			}
			//当在子弹那格有僵尸时
			if(Get_Plot_State(Position_Item + 2) == ZOMBIE)
			{
				
				if(*Plant_state == OEPL)
				{
					Set_Plot_Blood_State(*addr_track,Get_Plot_Blood_State(*addr_track)-20);
				}
				if(*Plant_state == PLPL)
				{
					Set_Plot_Blood_State(*addr_track,Get_Plot_Blood_State(*addr_track)-40);
				}
				if(Get_Plot_Blood_State(*addr_track)<=0)
				{
					Set_Plot_State(Position_Item +2, EMPTY);       // 清除僵尸
					p(IMG_DATA_Empty, Position_Item +2);     // 清屏
					(*addr_track)++;
					score++;
					Game_Show_Score(1,0,score);
				}
				return;
			}
			
		}
		/////////////////////
		if(Get_Plot_State(Position_Item+*a)!=ZOMBIE)
		{
			p(IMG_DATA_Empty, *a);
			Set_Plot_State(Position_Item+*a,EMPTY);//将当前地址写为空
		}
		(*a)++;

		if( Get_Plot_State(Position_Item + *a) == ZOMBIE )
		{
			//关键扣血加子弹还原代码
			*last_state = *Plant_state;
			
			if(*Plant_state == PLPL)
			{
				Set_Plot_Blood_State(*addr_track,Get_Plot_Blood_State(*addr_track)-40);
			}
			else
			{
				Set_Plot_Blood_State(*addr_track,Get_Plot_Blood_State(*addr_track)-20);
			}
			
			if(Get_Plot_Blood_State(*addr_track)<=0)
			{
				Set_Plot_State(Position_Item + *a, EMPTY);       // 清除僵尸
				p(IMG_DATA_Empty, *a);     // 清屏
				(*addr_track)++;
				score++;
				Game_Show_Score(1,0,score);
			}			
			*a = 2;
		}
         
		if(*a >= 8) *a = 2;
		
        if(*Plant_state == PLPL)
		{
        	p(Two_Bullet, *a);
			Set_Plot_State(Position_Item+*a,BULLET);
		}
        else
		{
        	p(One_Bullet, *a);
			Set_Plot_State(Position_Item+*a,BULLET);
		}
    }
    *last_state = *Plant_state;
}