#include "Timer0.h"

u16 sys_ms = 0;

// 只用1个数组，代替你原来 8 个变量！
// 0:轨道1  1:轨道2  2:轨道3
// 3:僵尸1  4:僵尸2  5:僵尸3  6:僵尸总体
u16 last_ms[7] = {0};

void Timer0_Init(void)
{
    TMOD |= 0x01;
    TH0 = 0xFC;
    TL0 = 0x67;
    ET0 = 1;
    TR0 = 1;
    EA  = 1;
}

void Timer0_ISR(void) interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x67;
    sys_ms++;
}


u8 delay_noblock(u8 index, u16 ms)
{
    if(sys_ms - last_ms[index] >= ms)
    {
        last_ms[index] = sys_ms;
        return 1;
    }
    return 0;
}