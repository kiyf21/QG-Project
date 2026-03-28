#include <REGX52.H>
#include <INTRINS.H>

#define MAX_TASKS 2 //表示有两个任务
#define MAX_TASK_DEP 32//表示栈的深度

unsigned char idata task_sp[MAX_TASKS];//任务的堆栈指针（存任务的）
unsigned char idata task_stack[MAX_TASKS][MAX_TASK_DEP];//每个task任务的堆栈
unsigned char task_id;//当前任务号

void Delay1000ms(void);		
void task_switch(void);
void task0(void);
void task1(void);
void task_load(unsigned int fn,unsigned char tid);

void main()
{
		task_load(task0,0);
	  task_load(task1,1);
	  task_id = 0;
	  SP=task_sp[0];
}

void Delay1000ms()		
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 154;
	k = 122;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void task_switch()
{
   task_sp[task_id]=SP;
	
	task_id=task_id+1;
	if(task_id==MAX_TASKS)
	{
	  task_id=0;
	}
	SP=task_sp[task_id];
}

void task0()
{
	P2_0=0;
  while(1)
	{
		Delay1000ms();
		P2_0=~P2_0;
		task_switch();
	}
}

void task1()
{
	P2_7=0;
  while(1)
	{
		Delay1000ms();
		P2_7=~P2_7;
		task_switch();
	}
}
	
void task_load(unsigned int fn,unsigned char tid)
{
  //task_sp[tid]=  task_stack[tid]+1;//跳到下一个任务
	task_stack[tid][1] = (unsigned char)(fn >> 8); 
  task_stack[tid][0] = (unsigned char)fn;  
	task_sp[tid] = (unsigned char)&task_stack[tid][1];
}



