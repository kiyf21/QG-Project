#include "bullet.h"




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

u8 Position_Item_1=11;
u8 Position_Item_2=21;
u8 Position_Item_3=31;

u8 addr_track1=13;
u8 addr_track2=23;
u8 addr_track3=33;

// 轨道1
PlantState Plant_state1 = NOPL;
PlantState last_state1  = NOPL;
static u8 bullet_pos1   = 2;

// 轨道2
PlantState Plant_state2 = NOPL;
PlantState last_state2  = NOPL;
static u8 bullet_pos2   = 2;

// 轨道3
PlantState Plant_state3 = NOPL;
PlantState last_state3  = NOPL;
static u8 bullet_pos3   = 2;


void Bullet_Shoot1(void);
void Bullet_Shoot2(void);
void Bullet_Shoot3(void);
void Change_Plant_state_All(void);


void Bullet_Main(void)
{
	Change_Plant_state_All();
	Bullet_Shoot1();
	Bullet_Shoot2();
	Bullet_Shoot3();
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

// ====================== 轨道1 子弹 ======================
void Bullet_Shoot1(void)
{

	
	
    if(Plant_state1 == NOPL)
    {
        if(last_state1 != NOPL)
        {
            LCD12864_Show_ImageTrack1(One_Bullet, bullet_pos1);
            bullet_pos1 = 2;
        }
        last_state1 = NOPL;
        return;
    }
	
	
    if(delay_noblock(0,200))
    {
		//////////////////////
		if(Get_Plot_State(Position_Item_1 +1) == ZOMBIE||Get_Plot_State(Position_Item_1 + 2) == ZOMBIE)
		{
			//当在第二格有僵尸时
			if(Get_Plot_State(Position_Item_1 +1) == ZOMBIE)
			{
				
				if(Plant_state1 == OEPL)
				{
					Set_Plot_Blood_State(Position_Item_1 +1,Get_Plot_Blood_State(Position_Item_1 +1)-20);
				}
				if(Get_Plot_Blood_State(Position_Item_1 +1)<=0)
				{
					Set_Plot_State(Position_Item_1 +1, EMPTY);       // 清除僵尸
					LCD12864_Show_ImageTrack1(IMG_DATA_Empty, Position_Item_1 +1);     // 清屏
				}
			}
			//当在子弹那格有僵尸时
			if(Get_Plot_State(Position_Item_1 + 2) == ZOMBIE)
			{
				
				if(Plant_state1 == OEPL)
				{
					Set_Plot_Blood_State(Position_Item_1 + 2,Get_Plot_Blood_State(Position_Item_1 +2)-20);
				}
				if(Get_Plot_Blood_State(Position_Item_1 +2)<=0)
				{
					Set_Plot_State(Position_Item_1 +2, EMPTY);       // 清除僵尸
					LCD12864_Show_ImageTrack1(IMG_DATA_Empty, Position_Item_1 +2);     // 清屏
				}
			}
			last_state1 = Plant_state1;
			
			return;
		}
		/////////////////////
		if(Get_Plot_State(Position_Item_1+bullet_pos1)!=ZOMBIE)
		{
			LCD12864_Show_ImageTrack1(IMG_DATA_Empty, bullet_pos1);
			Set_Plot_State(Position_Item_1+bullet_pos1,EMPTY);//将当前地址写为空
		}
		bullet_pos1++;

		if( Get_Plot_State(Position_Item_1 + bullet_pos1) == ZOMBIE )
		{
			//关键扣血加子弹还原代码
			last_state1 = Plant_state1;
			
			if(Plant_state1 == PLPL)
			{
				Set_Plot_Blood_State(addr_track1,Get_Plot_Blood_State(addr_track1)-40);
			}
			else
			{
				Set_Plot_Blood_State(addr_track1,Get_Plot_Blood_State(addr_track1)-20);
			}
			
			if(Get_Plot_Blood_State(addr_track1)<=0)
			{
				Set_Plot_State(Position_Item_1 + bullet_pos1, EMPTY);       // 清除僵尸
				LCD12864_Show_ImageTrack1(IMG_DATA_Empty, bullet_pos1);     // 清屏
				addr_track1++;
			}			
			bullet_pos1 = 2;
		}
         
		if(bullet_pos1 >= 8) bullet_pos1 = 2;
		
        if(Plant_state1 == PLPL)
		{
        	LCD12864_Show_ImageTrack1(Two_Bullet, bullet_pos1);
			Set_Plot_State(Position_Item_1+bullet_pos1,BULLET);
		}
        else
		{
        	LCD12864_Show_ImageTrack1(One_Bullet, bullet_pos1);
			Set_Plot_State(Position_Item_1+bullet_pos1,BULLET);
		}
    }
    last_state1 = Plant_state1;
}
// ====================== 轨道2 子弹 ======================
void Bullet_Shoot2(void)
{
    if(Plant_state2 == NOPL)
    {
        if(last_state2 != NOPL)
        {
            LCD12864_Show_ImageTrack2(One_Bullet, bullet_pos2);
            bullet_pos2 = 2;
        }
        last_state2 = NOPL;
        return;
    }
	
    if(delay_noblock(1,200))
    {
		//////////////////////
		if(Get_Plot_State(Position_Item_2 +1) == ZOMBIE||Get_Plot_State(Position_Item_2 + 2) == ZOMBIE)
		{
			//当在第二格有僵尸时
			if(Get_Plot_State(Position_Item_2 +1) == ZOMBIE)
			{
				
				if(Plant_state2 == OEPL)
				{
					Set_Plot_Blood_State(Position_Item_2 +1,Get_Plot_Blood_State(Position_Item_2 +1)-20);
				}
				if(Get_Plot_Blood_State(Position_Item_2 +1)<=0)
				{
					Set_Plot_State(Position_Item_2 +1, EMPTY);       // 清除僵尸
					LCD12864_Show_ImageTrack2(IMG_DATA_Empty, Position_Item_2 +1);     // 清屏
				}
			}
			//当在子弹那格有僵尸时
			if(Get_Plot_State(Position_Item_2 + 2) == ZOMBIE)
			{
				
				if(Plant_state2 == OEPL)
				{
					Set_Plot_Blood_State(Position_Item_2 + 2,Get_Plot_Blood_State(Position_Item_2 +2)-20);
				}
				if(Get_Plot_Blood_State(Position_Item_2 +2)<=0)
				{
					Set_Plot_State(Position_Item_2 +2, EMPTY);       // 清除僵尸
					LCD12864_Show_ImageTrack2(IMG_DATA_Empty, Position_Item_2 +2);     // 清屏
				}
			}
			last_state2 = Plant_state2;
			
			return;
		}
		/////////////////////

		
		if(Get_Plot_State(Position_Item_2+bullet_pos2)!=ZOMBIE)
		{
			LCD12864_Show_ImageTrack2(IMG_DATA_Empty, bullet_pos2);
			Set_Plot_State(Position_Item_2+bullet_pos2,EMPTY);//将当前地址写为空
		}

        bullet_pos2++;
		
		if( Get_Plot_State(Position_Item_2 + bullet_pos2) == ZOMBIE )
		{
			//关键扣血加子弹还原代码
			last_state2 = Plant_state2;
			
			if(Plant_state2 == PLPL)
			{
				Set_Plot_Blood_State(addr_track2,Get_Plot_Blood_State(addr_track2)-40);
			}
			else
			{
				Set_Plot_Blood_State(addr_track2,Get_Plot_Blood_State(addr_track2)-20);
			}
			
			if(Get_Plot_Blood_State(addr_track2)<=0)
			{
				Set_Plot_State(Position_Item_2 + bullet_pos2, EMPTY);       // 清除僵尸
				LCD12864_Show_ImageTrack2(IMG_DATA_Empty, bullet_pos2);     // 清屏
				addr_track2++;
			}			
			bullet_pos2 = 2;
		}
		
		if(bullet_pos2 >= 8) bullet_pos2 = 2;
        if(Plant_state2 == PLPL)
		{
        	LCD12864_Show_ImageTrack2(Two_Bullet, bullet_pos2);
			Set_Plot_State(Position_Item_2+bullet_pos2,BULLET);
		}
        else
		{
        	LCD12864_Show_ImageTrack2(One_Bullet, bullet_pos2);
			Set_Plot_State(Position_Item_2+bullet_pos2,BULLET);
		}
    }
    last_state2 = Plant_state2;
}

// ====================== 轨道3 子弹 ======================
void Bullet_Shoot3(void)
{
    if(Plant_state3 == NOPL)
    {
        if(last_state3 != NOPL)
        {
            LCD12864_Show_ImageTrack3(One_Bullet, bullet_pos3);
            bullet_pos3 = 2;
        }
        last_state3 = NOPL;
        return;
    }
    if(delay_noblock(2,200))
    {
		
		//////////////////////
		if(Get_Plot_State(Position_Item_3 +1) == ZOMBIE||Get_Plot_State(Position_Item_3 + 2) == ZOMBIE)
		{
			//当在第二格有僵尸时
			if(Get_Plot_State(Position_Item_3 +1) == ZOMBIE)
			{
				
				if(Plant_state3 == OEPL)
				{
					Set_Plot_Blood_State(Position_Item_3 +1,Get_Plot_Blood_State(Position_Item_3 +1)-20);
				}
				if(Get_Plot_Blood_State(Position_Item_3 +1)<=0)
				{
					Set_Plot_State(Position_Item_3 +1, EMPTY);       // 清除僵尸
					LCD12864_Show_ImageTrack3(IMG_DATA_Empty, Position_Item_3 +1);     // 清屏
				}
			}
			//当在子弹那格有僵尸时
			if(Get_Plot_State(Position_Item_3 + 2) == ZOMBIE)
			{
				
				if(Plant_state3 == OEPL)
				{
					Set_Plot_Blood_State(Position_Item_3 + 2,Get_Plot_Blood_State(Position_Item_3 +2)-20);
				}
				if(Get_Plot_Blood_State(Position_Item_3 +2)<=0)
				{
					Set_Plot_State(Position_Item_3 +2, EMPTY);       // 清除僵尸
					LCD12864_Show_ImageTrack3(IMG_DATA_Empty, Position_Item_3 +2);     // 清屏
				}
			}
			last_state3 = Plant_state3;
			
			return;
		}
		/////////////////////
		
		
		if(Get_Plot_State(Position_Item_3+bullet_pos3)!=ZOMBIE)
		{
			LCD12864_Show_ImageTrack3(IMG_DATA_Empty, bullet_pos3);
			Set_Plot_State(Position_Item_3+bullet_pos3,EMPTY);//将当前地址写为空
		}
		
		
		bullet_pos3++; 
		
		
		if( Get_Plot_State(Position_Item_3 + bullet_pos3) == ZOMBIE )
		{
			//关键扣血加子弹还原代码
			last_state3 = Plant_state3;
			
			if(Plant_state3 == PLPL)
			{
				Set_Plot_Blood_State(addr_track3,Get_Plot_Blood_State(addr_track3)-40);
			}
			else
			{
				Set_Plot_Blood_State(addr_track3,Get_Plot_Blood_State(addr_track3)-20);
			}
			
			if(Get_Plot_Blood_State(addr_track3)<=0)
			{
				Set_Plot_State(Position_Item_3 + bullet_pos3, EMPTY);       // 清除僵尸
				LCD12864_Show_ImageTrack3(IMG_DATA_Empty, bullet_pos3);     // 清屏
				addr_track3++;
			}			
			bullet_pos3 = 2;
		}
		
		
		if(bullet_pos3 >= 8) bullet_pos3 = 2;
        if(Plant_state3 == PLPL)
		{
        	LCD12864_Show_ImageTrack3(Two_Bullet, bullet_pos3);
			Set_Plot_State(Position_Item_3+bullet_pos3,BULLET);
		}
        else
		{
        	LCD12864_Show_ImageTrack3(One_Bullet, bullet_pos3);
			Set_Plot_State(Position_Item_3+bullet_pos3,BULLET);
		}
    }
    last_state3 = Plant_state3;
}
   