#ifndef __1602_H
#define __1602_H

#include "includes.h"

#define uchar unsigned char  
#define uint unsigned int  
	
extern void lcd1602IO_Init(void);
extern void DATA(uchar i);
extern void delay(uint a);
extern void delay_1ms(uint a);
extern void lcd_delay(void);
extern void enable(uchar del);
extern void write(uchar del);
extern void L1602_init(void);
extern void L1602_char(uchar hang,uchar lie,char sign);
extern void L1602_string(uchar hang,uchar lie,uchar *p);

#endif
