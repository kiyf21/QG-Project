#ifndef __AREA_H__
#define __AREA_H__

// 地块状态定义
#define EMPTY    0   // 空
#define PEA      1   // 豌豆
#define POTATO   2   // 土豆

// 一共有多少块地（你自己改数量）
#define PLOT_NUM    6 

void Plot_Init(void);
unsigned char Get_Plot_State(unsigned char plot_id);
void Set_Plot_State(unsigned char plot_id, unsigned char sta);

#endif
