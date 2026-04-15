#include "Timer0.h"

u16 sys_ms = 0;

// 三个轨道独立时间，把原来的一个删掉，换成三个！
u16 last_ms1 = 0;  // 轨道1专用
u16 last_ms2 = 0;  // 轨道2专用
u16 last_ms3 = 0;  // 轨道3专用

u16 last_msZ1 = 0;  // 
u16 last_msZ2 = 0;  // 
u16 last_msZ3 = 0;  // 
u16 last_msZO = 0;  // 

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


// 下面这三个函数，每个轨道用自己的！互不干扰！
u8 delay_noblock1(u16 ms)
{
    if(sys_ms - last_ms1 >= ms)
    {
        last_ms1 = sys_ms;
        return 1;
    }
    return 0;
}

u8 delay_noblock2(u16 ms)
{
    if(sys_ms - last_ms2 >= ms)
    {
        last_ms2 = sys_ms;
        return 1;
    }
    return 0;
}

u8 delay_noblock3(u16 ms)
{
    if(sys_ms - last_ms3 >= ms)
    {
        last_ms3 = sys_ms;
        return 1;
    }
    return 0;
}

u8 delay_noblockZ1(u16 ms)
{
    if(sys_ms - last_msZ1 >= ms)
    {
        last_msZ1 = sys_ms;
        return 1;
    }
    return 0;
}
u8 delay_noblockZ2(u16 ms)
{
    if(sys_ms - last_msZ2 >= ms)
    {
        last_msZ2 = sys_ms;
        return 1;
    }
    return 0;
}
u8 delay_noblockZ3(u16 ms)
{
    if(sys_ms - last_msZ3 >= ms)
    {
        last_msZ3 = sys_ms;
        return 1;
    }
    return 0;
}
u8 delay_ZOblock(u16 ms)
{
    if(sys_ms - last_msZO >= ms)
    {
        last_msZO = sys_ms;
        return 1;
    }
    return 0;
}