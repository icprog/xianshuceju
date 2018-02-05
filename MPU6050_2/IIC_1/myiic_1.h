#ifndef __MYIIC_1_H
#define __MYIIC_1_H
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
 #define SDA_IN_1()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define  SDA_OUT_1() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

//IO��������	 
#define IIC_SCL_1    PBout(10) 		//SCL
#define IIC_SDA_1    PBout(11) 		//SDA	 
#define READ_SDA_1   PBin(11) 		//����SDA 
/* 
//IO��������
#define SDA_IN_1()  {GPIOA->MODER&=~(3<<(3*2));GPIOA->MODER|=0<<3*2;}	//PA3����ģʽ
#define SDA_OUT_1() {GPIOA->MODER&=~(3<<(3*2));GPIOA->MODER|=1<<3*2;} //PA3���ģʽ
//IO��������	 
#define IIC_SCL_1    PAout(2) //SCL
#define IIC_SDA_1    PAout(3) //SDA	 
#define READ_SDA_1   PAin(3)  //����SDA 

#define SDA_IN_1()  {GPIOD->CRL&=0X0FFFFFFF;GPIOD->CRL|=(u32)8<<28;}
#define SDA_OUT_1() {GPIOD->CRL&=0X0FFFFFFF;GPIOD->CRL|=(u32)3<<28;}

//IO��������	 
#define IIC_SCL_1    PDout(6) //SCL
#define IIC_SDA_1    PDout(7) //SDA	 
#define READ_SDA_1   PDin(7)  //����SDA 
*/
//IIC���в�������
void IIC_Init_1(void);                //��ʼ��IIC��IO��				 
void IIC_Start_1(void);				//����IIC��ʼ�ź�
void IIC_Stop_1(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte_1(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte_1(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack_1(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack_1(void);					//IIC����ACK�ź�
void IIC_NAck_1(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte_1(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte_1(u8 daddr,u8 addr);	  
#endif
















