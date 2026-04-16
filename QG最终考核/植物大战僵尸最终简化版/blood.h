#ifndef __BLOOD_H__
#define __BLOOD_H__

#include "pubilc.h"






// 一共有多少块地+血量状态
#define PLOT_NUM_BLOOD    21
unsigned char Get_Plot_Blood_State(unsigned char plot_id);
void Set_Plot_Blood_State(unsigned char plot_id, unsigned char sta);


#endif
