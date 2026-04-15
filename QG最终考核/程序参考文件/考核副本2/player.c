#include "player.h"

u8 Position = 11;
u8 Last_Position = 11;
u8 Type_Plant = 0;

extern code unsigned char IMG_DATA_Empty[32];
extern code unsigned char IMG_DATA_Position[32];
extern code unsigned char IMG_DATA2_Plant[32];
extern code unsigned char IMG_DATA_Pototas[32];

//按键控制游标上下移动选择地块并处理
void Chosen_Position(u8 key)
{
    if(key == 2) // 上
    {
        if(Position/10!=1)
		{
			Last_Position = Position;
			Position=Position-10;
		}
		Select_Plot(Last_Position,Position);//选择地块后对上一地块进行覆盖或不处理
	}
    if(key == 10) // 下
    {
        if(Position/10!=3)
		{
			Last_Position = Position;
			Position=Position+10;
		}
		Select_Plot(Last_Position,Position);
	}
	if(key == 5) //左
    {
        if(Position%10!=1)
		{
			Last_Position = Position;
			Position=Position-1;
		}
		Select_Plot(Last_Position,Position);
    }
    if(key == 7) //右
    {
        if(Position%10!=2)
		{
			Last_Position = Position;
			Position=Position+1;
		}
		Select_Plot(Last_Position,Position);
	}
    if(key == 6) // 确定
    {
		
		now_state_1 = KEY_PLANT;
    }

}
//按键控制植物选择
void Type_Plant_Key(u8 key)
{
	//选择植物类型按键

	if(key == 5)//左选
	{
		if(Type_Plant > 0) Type_Plant--;
		switch(Type_Plant)
		{
			case 1:Show_Position(Position,IMG_DATA_Position); break;//1选择植物
			case 0:Show_Position(Position,IMG_DATA2_Plant); break;//空置
			case 2:Show_Position(Position,IMG_DATA_Pototas); break;//2选择土豆
		}
	}
	if(key == 7)//右选
	{
		if(Type_Plant < 2) Type_Plant++;
		switch(Type_Plant)
		{
			case 1:Show_Position(Position,IMG_DATA_Position); break;
			case 0:Show_Position(Position,IMG_DATA2_Plant); break;
			case 2:Show_Position(Position,IMG_DATA_Pototas); break;
		}
	}
	if(key == 6)
	{
		switch(Type_Plant)
		{
			case 1:Show_Position(Position,IMG_DATA_Position);Set_Plot_State(Position,EMPTY); break;
			case 0:Show_Position(Position,IMG_DATA2_Plant); Set_Plot_State(Position,PEA);break;
			case 2:Show_Position(Position,IMG_DATA_Pototas);Set_Plot_State(Position,POTATO); break;
		}
		now_state_1 = KEY_CHOOSE;
	}
}

//显示游标位置通用画面
void Show_Position(u8 Position_1,u8 code *DData)
{
	switch(Position_1)
	{
		case 11:LCD12864_Show_ImageTry1(DData); break;
		case 21:LCD12864_Show_ImageTry2(DData); break;
		case 31:LCD12864_Show_ImageTry3(DData); break;
		case 12:LCD12864_Show_ImageTry11(DData);break;
		case 22:LCD12864_Show_ImageTry22(DData);break;
		case 32:LCD12864_Show_ImageTry33(DData);break;
	}
}

//种植地块选择，选择地块后对上一地块进行覆盖或不处理
void Select_Plot(u8 Last_Position,u8 Position)
{
	if(Get_Plot_State(Last_Position)==0)
	{
		Show_Position(Last_Position,IMG_DATA_Empty);
	}
	if(Get_Plot_State(Position)==0)
	{
		Show_Position(Position,IMG_DATA_Position);
	}
}

