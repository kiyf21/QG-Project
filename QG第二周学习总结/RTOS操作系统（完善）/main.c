#include <REGX52.H>
#include <INTRINS.H>
#include "Delay.h"

#define MAX_TASKS 2           // 2个任务
#define MAX_TASK_DEP 32       // 栈深度

// 任务状态：就绪=运行中，挂起=暂停
#define TASK_READY   0
#define TASK_SUSPEND 1

unsigned char idata task_sp[MAX_TASKS];          // 任务堆栈指针
unsigned char idata task_stack[MAX_TASKS][MAX_TASK_DEP]; // 任务堆栈
unsigned char task_id;                           // 当前任务ID
unsigned char task_state[MAX_TASKS];            // 任务状态（挂起/运行）

// 函数声明
void task_switch(void);
void task0(void);
void task1(void);
void task_load(unsigned int fn,unsigned char tid);

// 任务挂起函数
void task_suspend(unsigned char tid)
{
    task_state[tid] = TASK_SUSPEND;
    task_switch();
}

// 任务唤醒（运行）函数
void task_resume(unsigned char tid)
{
    task_state[tid] = TASK_READY;
}

void main()
{
    task_load(task0,0);
    task_load(task1,1);
	
    // 默认都为运行状态
    task_state[0] = TASK_READY;
    task_state[1] = TASK_READY;
	
    task_id = 0;
    SP = task_sp[0];
}

// 任务切换（自动跳过挂起的任务）
void task_switch()
{
    unsigned char next_id;
    task_sp[task_id] = SP;

    // 寻找下一个就绪的任务
    next_id = task_id + 1;
    if(next_id >= MAX_TASKS) next_id = 0;

    // 如果下一个任务挂起，再找下一个
    while(task_state[next_id] == TASK_SUSPEND)
    {
        next_id++;
        if(next_id >= MAX_TASKS) next_id = 0;
    }

    task_id = next_id;
    SP = task_sp[task_id];
}

void task0(void)
{
    P2_0 = 0;
    while(1)
    {
        Delay(1000);
        P2_0 = ~P2_0;
        task_switch();
        task_suspend(0); 
    }
}

void task1(void)
{
    P2_7 = 0;
    while(1)
    {
        Delay(1000);
        P2_7 = ~P2_7;
		task_switch();
    }
}

// 任务初始化
void task_load(unsigned int fn,unsigned char tid)
{
    task_stack[tid][1] = (unsigned char)(fn >> 8); 
    task_stack[tid][0] = (unsigned char)fn;  
    task_sp[tid] = (unsigned char)&task_stack[tid][1];
}
