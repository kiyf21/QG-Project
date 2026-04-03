#ifndef __LCD12864_H__
#define __LCD12864_H__

void lcd12864_clear(void);
void lcd12864_init(void);
void lcd12864_show_string(unsigned char x,unsigned char y,unsigned char *str);

#endif