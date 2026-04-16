#include "zombie.h"

extern code unsigned char IMG_DATA_Empty[32]; 
code unsigned char IMG_DATA_Person[32] = 
{
    0x01,0xC0,0x06,0x38,0x30,0x0C,0x60,0x04,0x46,0x67,0x40,0xB2,0x71,0x0A,0x49,0x6A,
    0x4B,0x10,0x70,0xE6,0x3E,0x01,0x0F,0x88,0x0D,0xD0,0x18,0x34,0x09,0xD4,0x01,0x14,
};
code unsigned char IMG_DATA_Person1[32] = 
{
    0x03,0x80,0x1C,0xF8,0x20,0xEC,0x30,0x44,0x18,0x02,0x08,0x02,0x0C,0x06,0x0A,0x02,
    0x12,0x06,0x10,0x5E,0x32,0x0C,0x12,0x27,0x1F,0xCB,0x0D,0x10,0x0E,0x14,0x03,0x14,
};


extern u8 game_difficulty;////0为简单1为困难
//僵尸出怪顺序
idata u8 zombie_wave[]={2,1,3,0,3,1,2,10};
idata u8 zombie_wave_diff[]={3,2,3,0,1,2,1,4,3,2,1,10};


u8 sign_num=0;
//当前出怪顺序
u8 wave_now = 0;

extern u8 Position_Item_1;
extern u8 Position_Item_2;
extern u8 Position_Item_3;





u8 addr_1=13;//（3-8）一共可以写3*6只僵尸
u8 addr_2=23;
u8 addr_3=33;




void Read_zombie_wave(void)
{
	u8 *zombie_table;   // 出怪表指针
    u8 max_zombie;      // 最大僵尸数量
    if(game_difficulty == 1)
    {
        zombie_table = zombie_wave_diff;
        max_zombie = 12;
    }
    else
    {
        zombie_table = zombie_wave;
        max_zombie = 8;
    }
    if(wave_now >= max_zombie) return;

    if(delay_noblock(6,4000) && wave_now < max_zombie)
    {
        switch(zombie_table[wave_now])
        {
            case 1:
                Set_Plot_State(Position_Item_1+7,ZOMBIE);
                LCD12864_Show_ImageTrack1(IMG_DATA_Person1, 7);
				Set_Plot_Blood_State(addr_1,120);
				addr_1=addr_1+1;
                break;
            case 2:
                Set_Plot_State(Position_Item_2+7,ZOMBIE);
                LCD12864_Show_ImageTrack2(IMG_DATA_Person, 7);
				Set_Plot_Blood_State(addr_2,120);
				addr_2=addr_2+1;
                break;         
            case 3:
                Set_Plot_State(Position_Item_3+7,ZOMBIE);
                LCD12864_Show_ImageTrack3(IMG_DATA_Person, 7);
				Set_Plot_Blood_State(addr_3,120);
				addr_3=addr_3+1;
                break;
			case 0:
				LCD12864_Show_String(6,0,"Rd:2");
				break;
			case 4:
				LCD12864_Show_String(6,0,"Rd:3");
				break;
			case 10:
				sign_num=10;
			
				break;
			
        }
        wave_now++;
    }
}

// ====================== 轨道1 僵尸移动 ======================
void Detect_Zombie1_move(void)
{
    u8 z;

    if(!delay_noblock(3, 3000)) return;
	
    for(z=1; z<=7; z++)
    {
        if(Get_Plot_State(Position_Item_1 + z) == ZOMBIE && Get_Plot_State(Position_Item_1 + z-1) != ZOMBIE)
        {

			if(Get_Plot_State(Position_Item_1 + z-1) == PEA ||Get_Plot_State(Position_Item_1 + z-1) == POTATO)
			{
				Set_Plot_Blood_State(Position_Item_1 + z-1,Get_Plot_Blood_State(Position_Item_1 + z-1)-20);


				if(Get_Plot_Blood_State(Position_Item_1 + z-1) <= 0)
				{
					Set_Plot_State(Position_Item_1 + z-1, EMPTY);
					LCD12864_Show_ImageTrack1(IMG_DATA_Empty, z-1);
				}
				continue;
			}
			
			Set_Plot_State(Position_Item_1 + z, ZOMBIE);
            LCD12864_Show_ImageTrack1(IMG_DATA_Person1, z);
			
            Set_Plot_State(Position_Item_1 + (z-1), ZOMBIE);
            LCD12864_Show_ImageTrack1(IMG_DATA_Person1, z-1);

            Set_Plot_State(Position_Item_1 + z, EMPTY);
            LCD12864_Show_ImageTrack1(IMG_DATA_Empty, z);


			
        }
    }
}

// ====================== 轨道2 僵尸移动 ======================
void Detect_Zombie2_move(void)
{
    u8 z;
    if(!delay_noblock(4, 2000)) return;

    for(z=1; z<=7; z++)
    {
        if(Get_Plot_State(Position_Item_2 + z) == ZOMBIE && Get_Plot_State(Position_Item_2 + z-1) != ZOMBIE)
        {
			//植物扣血代码
			if(Get_Plot_State(Position_Item_2 + z-1) == PEA ||Get_Plot_State(Position_Item_2 + z-1) == POTATO)
			{
				Set_Plot_Blood_State(Position_Item_2 + z-1,Get_Plot_Blood_State(Position_Item_2 + z-1)-20);


				if(Get_Plot_Blood_State(Position_Item_2 + z-1) <= 0)
				{
					Set_Plot_State(Position_Item_2 + z-1, EMPTY);
					LCD12864_Show_ImageTrack2(IMG_DATA_Empty, z-1);
				}
				continue;
			}
            Set_Plot_State(Position_Item_2 + z, ZOMBIE);
            LCD12864_Show_ImageTrack2(IMG_DATA_Person, z);
			
            Set_Plot_State(Position_Item_2 + (z-1), ZOMBIE);
            LCD12864_Show_ImageTrack2(IMG_DATA_Person, z-1);
			
            Set_Plot_State(Position_Item_2 + z, EMPTY);
            LCD12864_Show_ImageTrack2(IMG_DATA_Empty, z);
        }
    }
}

// ====================== 轨道3 僵尸移动（你原来的）======================
void Detect_Zombie3_move(void)
{
    u8 z;
    if(!delay_noblock(5,4000)) return;

    for(z=1; z<=7; z++)
    {
        if(Get_Plot_State(Position_Item_3+z) == ZOMBIE && Get_Plot_State(Position_Item_3 + z-1) != ZOMBIE)
        {
			if(Get_Plot_State(Position_Item_3 + z-1) == PEA ||Get_Plot_State(Position_Item_3 + z-1) == POTATO)
			{
				Set_Plot_Blood_State(Position_Item_3 + z-1,Get_Plot_Blood_State(Position_Item_3 + z-1)-20);

				if(Get_Plot_Blood_State(Position_Item_3 + z-1) <= 0)
				{
					Set_Plot_State(Position_Item_3 + z-1, EMPTY);
					LCD12864_Show_ImageTrack3(IMG_DATA_Empty, z-1);
				}
				continue;
			}
			
			Set_Plot_State(Position_Item_3 + z, ZOMBIE);
			LCD12864_Show_ImageTrack3(IMG_DATA_Person, z);
			
			Set_Plot_State(Position_Item_3 + (z-1), ZOMBIE);
			LCD12864_Show_ImageTrack3(IMG_DATA_Person, z-1);
			
			Set_Plot_State(Position_Item_3 + z, EMPTY);
			LCD12864_Show_ImageTrack3(IMG_DATA_Empty, z);
        }
    }
}

//主函数
void Zombie_Main(void)
{
    Read_zombie_wave();
    Detect_Zombie1_move();
    Detect_Zombie2_move();
    Detect_Zombie3_move();
}