#ifndef __TIMER0_H__
#define __TIMER0_H__

#include "pubilc.h"


void Timer0_Init(void);

unsigned char delay_noblock1(unsigned int ms);
unsigned char delay_noblock2(unsigned int ms);
unsigned char delay_noblock3(unsigned int ms);

unsigned char delay_noblockZ1(unsigned int ms);
unsigned char delay_noblockZ2(unsigned int ms);
unsigned char delay_noblockZ3(unsigned int ms);

unsigned char delay_ZOblock(unsigned int ms);


#endif