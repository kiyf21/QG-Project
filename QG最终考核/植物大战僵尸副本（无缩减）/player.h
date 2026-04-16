#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "pubilc.h"

extern unsigned char Position;

void Chosen_Position(unsigned char key);
void Show_Position(unsigned char Position_1,unsigned char code *DData);
void Select_Plot(unsigned char Last_Position,unsigned char Position);
void Type_Plant_Key(unsigned char key);
#endif
