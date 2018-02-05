#ifndef __MYIIC_1_H
#define __MYIIC_1_H
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//IIC 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
 #define SDA_IN_1()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define  SDA_OUT_1() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

//IO操作函数	 
#define IIC_SCL_1    PBout(10) 		//SCL
#define IIC_SDA_1    PBout(11) 		//SDA	 
#define READ_SDA_1   PBin(11) 		//输入SDA 
/* 
//IO方向设置
#define SDA_IN_1()  {GPIOA->MODER&=~(3<<(3*2));GPIOA->MODER|=0<<3*2;}	//PA3输入模式
#define SDA_OUT_1() {GPIOA->MODER&=~(3<<(3*2));GPIOA->MODER|=1<<3*2;} //PA3输出模式
//IO操作函数	 
#define IIC_SCL_1    PAout(2) //SCL
#define IIC_SDA_1    PAout(3) //SDA	 
#define READ_SDA_1   PAin(3)  //输入SDA 

#define SDA_IN_1()  {GPIOD->CRL&=0X0FFFFFFF;GPIOD->CRL|=(u32)8<<28;}
#define SDA_OUT_1() {GPIOD->CRL&=0X0FFFFFFF;GPIOD->CRL|=(u32)3<<28;}

//IO操作函数	 
#define IIC_SCL_1    PDout(6) //SCL
#define IIC_SDA_1    PDout(7) //SDA	 
#define READ_SDA_1   PDin(7)  //输入SDA 
*/
//IIC所有操作函数
void IIC_Init_1(void);                //初始化IIC的IO口				 
void IIC_Start_1(void);				//发送IIC开始信号
void IIC_Stop_1(void);	  			//发送IIC停止信号
void IIC_Send_Byte_1(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte_1(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack_1(void); 				//IIC等待ACK信号
void IIC_Ack_1(void);					//IIC发送ACK信号
void IIC_NAck_1(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte_1(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte_1(u8 daddr,u8 addr);	  
#endif
















