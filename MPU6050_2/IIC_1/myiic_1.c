#include "myiic_1.h"
#include "delay.h"
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

//��ʼ��IIC
void IIC_Init_1(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;
 /*
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
 
  //GPIOA2,A3��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	*/
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOD, ENABLE );	//ʹ��GPIOBʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 �����
	
	IIC_SCL_1=1;
	IIC_SDA_1=1;
}
//����IIC��ʼ�ź�
void IIC_Start_1(void)
{
	SDA_OUT_1();     //sda�����
	IIC_SDA_1=1;	  	  
	IIC_SCL_1=1;
	delay_us(4);
 	IIC_SDA_1=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_1=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop_1(void)
{
	SDA_OUT_1();//sda�����
	IIC_SCL_1=0;
	IIC_SDA_1=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_1=1; 
	IIC_SDA_1=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack_1(void)
{
	u8 ucErrTime=0;
	SDA_IN_1();      //SDA����Ϊ����  
	IIC_SDA_1=1;delay_us(1);	   
	IIC_SCL_1=1;delay_us(1);	 
	while(READ_SDA_1)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop_1();
			return 1;
		}
	}
	IIC_SCL_1=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack_1(void)
{
	IIC_SCL_1=0;
	SDA_OUT_1();
	IIC_SDA_1=0;
	delay_us(2);
	IIC_SCL_1=1;
	delay_us(2);
	IIC_SCL_1=0;
}
//������ACKӦ��		    
void IIC_NAck_1(void)
{
	IIC_SCL_1=0;
	SDA_OUT_1();
	IIC_SDA_1=1;
	delay_us(2);
	IIC_SCL_1=1;
	delay_us(2);
	IIC_SCL_1=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte_1(u8 txd)
{                        
    u8 t;   
	SDA_OUT_1(); 	    
    IIC_SCL_1=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA_1=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_1=1;
		delay_us(2); 
		IIC_SCL_1=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte_1(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN_1();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL_1=0; 
        delay_us(2);
		IIC_SCL_1=1;
        receive<<=1;
        if(READ_SDA_1)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck_1();//����nACK
    else
        IIC_Ack_1(); //����ACK   
    return receive;
}



























