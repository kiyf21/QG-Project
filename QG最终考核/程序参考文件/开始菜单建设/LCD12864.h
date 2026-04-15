#ifndef _LCD12864_H
#define _LCD12864_H

//º¯ÊýÉùÃ÷
void LCD12864_Write_Cmd(unsigned char cmd,BuysC);
void LCD12864_Write_Data(unsigned char dat);
void LCD12864_Init(void);
void LCD12864_Clear(void);
void LCD_Flash(void);
void LCD12864_Show_String(unsigned char x,unsigned char y,unsigned char *str);
void LCD12864_Show_Onechar(unsigned char x, unsigned char y, unsigned char DData);
void LCD12864_Show_Image (unsigned char code *DData);
void LCD12864_Set_Location(unsigned char x, unsigned char y);
void LCD12864_Show_Image_ANY(
    unsigned char code *DData,
    unsigned char imgW,
    unsigned char imgH,
    unsigned char startX,
    unsigned char startY
);
void LCD12864_Show_ImageTry1 (unsigned char code *DData);
void LCD12864_Show_ImageTry2 (unsigned char code *DData);
void LCD12864_Show_ImageTry3 (unsigned char code *DData);
void LCD12864_Show_ImageTry11 (unsigned char code *DData);
void LCD12864_Show_ImageTry22 (unsigned char code *DData);
void LCD12864_Show_ImageTry33 (unsigned char code *DData);
#endif
