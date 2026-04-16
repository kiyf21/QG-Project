#include "score.h"

u8 score = 0;

void Show_SaveScore(void)
{
	LCD12864_Clear();
    score=AT24C02_ReadByte(0);
	LCD12864_Show_String(0,0,"上次存档得分：");
	Game_Show_Score(3,1,score);
	LCD12864_Show_String(0,2,"按任意键返回");
}



void Game_Show_Score(u8 x,u8 y,u8 score)
{
	switch(score)
	{
		case 0:LCD12864_Show_String(x,y,"00");break;
		case 1:LCD12864_Show_String(x,y,"10");break;
		case 2:LCD12864_Show_String(x,y,"20");break;
		case 3:LCD12864_Show_String(x,y,"30");break;
		case 4:LCD12864_Show_String(x,y,"40");break;
		case 5:LCD12864_Show_String(x,y,"50");break;
		case 6:LCD12864_Show_String(x,y,"60");break;	
		case 7:LCD12864_Show_String(x,y,"70");break;
		case 8:LCD12864_Show_String(x,y,"80");break;
		case 9:LCD12864_Show_String(x,y,"90");break;
	}
}

		