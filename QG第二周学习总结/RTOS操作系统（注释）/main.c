#include <REGX52.H>
#include <INTRINS.H>
#include "Delay.h"

#define MAX_TASKS 2 //表示有两个任务
#define MAX_TASK_DEP 32//表示栈的深度

unsigned char idata task_sp[MAX_TASKS];//任务的堆栈指针（存任务的）
unsigned char idata task_stack[MAX_TASKS][MAX_TASK_DEP];//每个task任务的堆栈
unsigned char task_id;//当前任务号

//task_sp数组存储每个任务的堆栈指针（SP），task_stack是每个任务的堆栈区域（每个32字节）

void task_switch(void);
void task0(void);
void task1(void);
void task_load(unsigned int fn,unsigned char tid);

void main()
{
	  task_load(task0,0);//函数名 = 自动传它的地址
	  task_load(task1,1);
	  task_id = 0;
	  SP=task_sp[0];//将初始化的任务地址，即任务初次执行的地址赋值给SP，让cpu从sp开始执行，在这里即从头开始执行task0，执行P2_0=0;语句，在后续切换中将不再执行此语句
}
//任务切换
void task_switch()
{
    task_sp[task_id]=SP;//保存当前任务的SP（即执行状态/执行到哪一条程序）到task_sp[task_id]，然后切换到下一个任务（循环0->1->0），设置SP为下一个任务的堆栈指针。
	task_id=task_id+1;
	if(task_id==MAX_TASKS)
	{
	  task_id=0;
	}
	SP=task_sp[task_id];//将另一个任务的运行地址（即执行状态/执行到哪一条程序）赋值给sp，即让cpu从另一个一个任务上次暂停的地方继续运行
}

void task0()
{
	P2_0=0;
  while(1)
	{
		
		Delay(1000);
		P2_0=~P2_0;
		//当第一次进入task0，led0亮1秒后熄灭并进入了任务交换，此时循环暂停在任务切换的位置，led0处于灭的状态。
		//当第二次进入task0时led0和7同时灭1秒后led0亮，暂停task0并进入task1。
		//当第三次进入task0，led0和7同时亮一秒。
		task_switch();
		
	}
}

void task1()
{
	P2_7=0;
  while(1)
	{
		Delay(1000);
		P2_7=~P2_7;
	    //当第一次进入task0时，led0处于灭的状态，led7亮一秒后熄灭，返回task0，此时led0和7都处于灭的状态。
		//当第二次进入task1时led0亮led7灭，1秒后led0亮，led7也亮并暂停task1并进入task0。
		task_switch();
		
	}
}
	
//总结这个代码实现了不同循环相互独立执行时，跳转循环后，上一个循环是暂停的状态，当再次进入这个循环是并非重新执行此循环，而是从暂停的地方继续该循环。



//unsigned char idata task_sp[MAX_TASKS];//任务的堆栈指针（存任务的）
//unsigned char idata task_stack[MAX_TASKS][MAX_TASK_DEP];//每个task任务的堆栈

void task_load(unsigned int fn,unsigned char tid)//fn为任务地址
{
	//将两个任务的任务地址分别存入他们各自堆栈的数组
  //task_sp[tid]=  task_stack[tid]+1;//跳到下一个任务
	task_stack[tid][1] = (unsigned char)(fn >> 8); //把函数地址的高8位放进栈的第2个字节
    task_stack[tid][0] = (unsigned char)fn;  //把函数地址的低8位放进栈的第1个字节
	task_sp[tid] = (unsigned char)&task_stack[tid][1];
	//取栈里第2个字节的地址，赋值给task_sp[tid]（任务栈指针），用于设置栈指针SP，指向栈顶（准备第一次执行），也可理解为初始化SP
}



