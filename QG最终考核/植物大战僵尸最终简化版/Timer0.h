#ifndef __TIMER0_H__
#define __TIMER0_H__

#include "pubilc.h"


void Timer0_Init(void);

unsigned char delay_noblock(unsigned char index, unsigned int ms);


#endif