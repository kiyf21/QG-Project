#include "Timer0.h"

u16 sys_ms = 0;
u16 bullet_last_ms = 0;

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

u8 delay_noblock(u16 ms)
{
    if(sys_ms - bullet_last_ms >= ms)
    {
        bullet_last_ms = sys_ms;
        return 1;
    }
    return 0;
}


