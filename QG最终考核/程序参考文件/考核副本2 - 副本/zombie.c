#include "zombie.h"


extern code unsigned char IMG_DATA_Empty[32]; 
code unsigned char IMG_DATA_Person[32] = 
{
    0x01,0xC0,0x06,0x38,0x30,0x0C,0x60,0x04,0x46,0x67,0x40,0xB2,0x71,0x0A,0x49,0x6A,
    0x4B,0x10,0x70,0xE6,0x3E,0x01,0x0F,0x88,0x0D,0xD0,0x18,0x34,0x09,0xD4,0x01,0x14,
};


//僵尸出怪顺序
idata u8 zombie_wave[]={3,2,1,2,1,3};
//当前出怪顺序
u8 wave_now = 0;
//一共多少只僵尸
u8 wave_total = 6;

u8 Position_Zombie_1 = 11; // 僵尸轨道基地址
u8 Position_Zombie_2 = 21;
u8 Position_Zombie_3 = 31;

void Read_zombie_wave(void)
{
	// 如果已经出完所有僵尸，直接退出
    if(wave_now >= wave_total)
    {
        return;
    }
	//设置每3s的中断，每3s出一次怪
	if(delay_noblock(6,4000) && wave_now < wave_total)
	{
		switch(zombie_wave[wave_now])
		{
			case 1:
				Set_Plot_State(Position_Zombie_1+7,ZOMBIE);
				LCD12864_Show_ImageTrack1(IMG_DATA_Person, 7);
				break;
			case 2:
				Set_Plot_State(Position_Zombie_2+7,ZOMBIE);
				LCD12864_Show_ImageTrack2(IMG_DATA_Person, 7);
				break;			
			case 3:
				Set_Plot_State(Position_Zombie_3+7,ZOMBIE);
				LCD12864_Show_ImageTrack3(IMG_DATA_Person, 7);
				break;
		}
		wave_now++;
	}
}


void Detect_Zombie1_move(void)
{
	u8 i;
	if( !delay_noblock(3,1500) )
	{
		return; // 时间没到，全部不动
	}

	// 时间到 → 整行所有僵尸一起走
	for(i=1; i<=7; i++)
	{
		// 如果是僵尸
		if(Get_Plot_State(Position_Zombie_1+i) == ZOMBIE)
		{
			// 前面为空才能走
			if(Get_Plot_State(Position_Zombie_1 + (i-1)) == EMPTY)
			{
				// 擦掉当前
				LCD12864_Show_ImageTrack1(IMG_DATA_Empty, i);
				Set_Plot_State(Position_Zombie_1 + i, EMPTY);

				// 左移一格
				LCD12864_Show_ImageTrack1(IMG_DATA_Person, i-1);
				Set_Plot_State(Position_Zombie_1 + (i-1), ZOMBIE);
			}
		}
	}
}

void Detect_Zombie2_move(void)
{
	u8 y;
	if( !delay_noblock(4,2000) )
	{
		return; // 时间没到，全部不动
	}

	// 时间到 → 整行所有僵尸一起走
	for(y=1; y<=7; y++)
	{
		// 如果是僵尸
		if(Get_Plot_State(Position_Zombie_2+y) == ZOMBIE)
		{
			// 前面为空才能走
			if(Get_Plot_State(Position_Zombie_2 + (y-1)) == EMPTY)
			{
				// 擦掉当前
				LCD12864_Show_ImageTrack2(IMG_DATA_Empty, y);
				Set_Plot_State(Position_Zombie_2 + y, EMPTY);

				// 左移一格
				LCD12864_Show_ImageTrack2(IMG_DATA_Person, y-1);
				Set_Plot_State(Position_Zombie_2 + (y-1), ZOMBIE);
			}
		}
	}
}
void Detect_Zombie3_move(void)
{
	u8 z;
	if( !delay_noblock(5,3000) )
	{
		return; // 时间没到，全部不动
	}

	// 时间到 → 整行所有僵尸一起走
	for(z=1; z<=7; z++)
	{
		// 如果是僵尸
		if(Get_Plot_State(Position_Zombie_3+z) == ZOMBIE)
		{
			// 前面为空才能走
			if(Get_Plot_State(Position_Zombie_3 + (z-1)) == EMPTY)
			{
				// 擦掉当前
				LCD12864_Show_ImageTrack3(IMG_DATA_Empty, z);
				Set_Plot_State(Position_Zombie_3 + z, EMPTY);

				// 左移一格
				LCD12864_Show_ImageTrack3(IMG_DATA_Person, z-1);
				Set_Plot_State(Position_Zombie_3 + (z-1), ZOMBIE);
			}
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