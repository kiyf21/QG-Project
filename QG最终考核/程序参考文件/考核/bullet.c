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

u8 Position_Bullet_1=11;
u8 Position_Bullet_2=23-2;
u8 Position_Bullet_3=33-2;

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
	
	//当前无植物的时候
    if(Plant_state1 == NOPL)
    {
		//从有植物变为无植物的时候
        if(last_state1 != NOPL)
        {
            LCD12864_Show_ImageTrack1(IMG_DATA_Empty, bullet_pos1);
			
			Set_Plot_State(Position_Bullet_1+bullet_pos1,EMPTY);//将当前地址写为空
			
            bullet_pos1 = 2;
        }
        last_state1 = NOPL;
        return;
    }
		
	//当前有植物的时候
    if(delay_noblock1(300))
    {
//		if( Get_Plot_State(Position_Bullet_1 + bullet_pos1) == Z.OMBIE )
//		{
//			
//			return;
//		}
        LCD12864_Show_ImageTrack1(IMG_DATA_Empty, bullet_pos1);
		Set_Plot_State(Position_Bullet_1+bullet_pos1,EMPTY);//将当前地址写为空
		
        bullet_pos1++; 
		
		if( Get_Plot_State(Position_Bullet_1 + bullet_pos1) == ZOMBIE )
		{
			
			return;
		}
	
		//恢复bullet_pos1
		if(bullet_pos1 >= 8) bullet_pos1 = 2;
		
		//判断发射一颗子弹还是两颗
		if(Plant_state1 == PLPL)
		{
			LCD12864_Show_ImageTrack1(Two_Bullet, bullet_pos1);
			Set_Plot_State(Position_Bullet_1+bullet_pos1,BULLET);//将当前地址写为子弹
		}
		else
		{
			LCD12864_Show_ImageTrack1(One_Bullet, bullet_pos1);
			Set_Plot_State(Position_Bullet_1+bullet_pos1,BULLET);
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
            LCD12864_Show_ImageBullet2(IMG_DATA_Empty, bullet_pos2);
            bullet_pos2 = 2;
        }
        last_state2 = NOPL;
        return;
    }

    if(delay_noblock2(300))
    {
        LCD12864_Show_ImageBullet2(IMG_DATA_Empty, bullet_pos2);
		Set_Plot_State(Position_Bullet_2+bullet_pos2,EMPTY);//将当前地址写为空
		
        bullet_pos2++; 
		if( Get_Plot_State(Position_Bullet_2 + bullet_pos2) == ZOMBIE )
		{
			
			return;
		}
		
		if(bullet_pos2 >= 8) bullet_pos2 = 2;
        if(Plant_state2 == PLPL)
		{
        	LCD12864_Show_ImageBullet2(Two_Bullet, bullet_pos2);
			Set_Plot_State(Position_Bullet_1+bullet_pos2,BULLET);
		}
        else
		{
        	LCD12864_Show_ImageBullet2(One_Bullet, bullet_pos2);
			Set_Plot_State(Position_Bullet_1+bullet_pos2,BULLET);
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
            LCD12864_Show_ImageBullet3(IMG_DATA_Empty, bullet_pos3);
            bullet_pos3 = 2;
        }
        last_state3 = NOPL;
        return;
    }

    if(delay_noblock3(300))
    {
        LCD12864_Show_ImageBullet3(IMG_DATA_Empty, bullet_pos3);
		Set_Plot_State(Position_Bullet_3+bullet_pos3,EMPTY);//将当前地址写为空
        bullet_pos3++; 
		if( Get_Plot_State(Position_Bullet_3 + bullet_pos3) == ZOMBIE )
		{
			
			return;
		}
		if(bullet_pos3 >= 8) bullet_pos3 = 2;
        if(Plant_state3 == PLPL)
		{
        	LCD12864_Show_ImageBullet3(Two_Bullet, bullet_pos3);
			Set_Plot_State(Position_Bullet_1+bullet_pos3,BULLET);
		}
        else
		{
        	LCD12864_Show_ImageBullet3(One_Bullet, bullet_pos3);
			Set_Plot_State(Position_Bullet_1+bullet_pos3,BULLET);
		}
    }
    last_state3 = Plant_state3;
}


//将子弹一的bullet_pos1转化为可写入数组的地址    
	







