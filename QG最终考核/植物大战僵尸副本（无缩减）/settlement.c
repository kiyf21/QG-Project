#include "settlement.h"

extern u8 game_over; 
extern u8 sign_num;
extern u8 score;

u8 game_result;
u8 save_choose;

void game_settlement(void)
{
	//有僵尸走到了尽头
	if(Get_Plot_State(21)==ZOMBIE||Get_Plot_State(11)==ZOMBIE||Get_Plot_State(31)==ZOMBIE)
	{
		Delay_ms(1000);
		game_over = 1;
		game_result=0;
		
	}
	//僵尸出现完毕
	if(sign_num==10)
	{
		unsigned char i;
		unsigned char zb=0;
		for(i=0;i<24;i++)
		{
			if(Get_Plot_State_nomal(i)==ZOMBIE)
			{
				zb=1;
			}
		}
		//场上不在剩下僵尸
		if(zb==0)
		{
			Delay_ms(1000);
			game_result=1;
			game_over = 1;
		}
	}
}


void Show_SettleMent(void)
{
	LCD12864_Clear();
	if(game_result==0)
	{
		LCD12864_Clear();
		LCD12864_Show_String(0,0,"you lost");
		Game_Show_Score(5,0,score);
		LCD12864_Show_String(0,1,"是否保存你的结果");
		if(save_choose == 0)
		{
			LCD12864_Set_Location(1,2);
			LCD12864_Write_Data(' ');											//左半角英文字符位显示空格
			LCD12864_Write_Data(0x10);
			LCD12864_Show_String(3,2,"保存");
		}
		else
		{
			LCD12864_Show_String(1,2, "  ");
			LCD12864_Show_String(3,2,"保存");
		}

		if(save_choose == 1)
		{
			LCD12864_Set_Location(1,3);
			LCD12864_Write_Data(' ');											//左半角英文字符位显示空格
			LCD12864_Write_Data(0x10);
			LCD12864_Show_String(3,3,"不保存");
		}
		else
		{
			LCD12864_Show_String(1, 3, "  ");
			LCD12864_Show_String(3,3,"不保存");
		}
	}
	if(game_result==1)
	{
		LCD12864_Clear();
		LCD12864_Show_String(0,0,"you win");
		Game_Show_Score(5,0,score);
		LCD12864_Show_String(0,1,"是否保存你的结果");
		if(save_choose == 0)
		{
			LCD12864_Set_Location(1,2);
			LCD12864_Write_Data(' ');											//左半角英文字符位显示空格
			LCD12864_Write_Data(0x10);
			LCD12864_Show_String(3,2,"保存");
		}
		else
		{
			LCD12864_Show_String(1,2, "  ");
			LCD12864_Show_String(3,2,"保存");
		}

		if(save_choose == 1)
		{
			LCD12864_Set_Location(1,3);
			LCD12864_Write_Data(' ');											//左半角英文字符位显示空格
			LCD12864_Write_Data(0x10);
			LCD12864_Show_String(3,3,"不保存");
		}
		else
		{
			LCD12864_Show_String(1, 3, "  ");
			LCD12864_Show_String(3,3,"不保存");
		}
	}
}
//需要改进
void SettleMent_Key(key)
{
    if(key == 2)
    {
        if(save_choose > 0) save_choose--;
    }
    if(key == 10)
    {
        if(save_choose < 1) save_choose++;
    }
    if(key == 6)
    {
        if(save_choose == 0) 
		{
			AT24C02_WriteByte(0,score);
		}
		Show_MainMenu();
        now_state = MENU_MAIN;
        
    }
    Show_SettleMent();
}

