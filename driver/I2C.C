/*********************************Copyright (c)*********************************                                      
  *                                      
  ******************************************************************************
  * �ļ����ƣ�I2C.C
  * ��    ��������ģ��IICģ��
  * �� �� ��: 
  * ��������:    
  * �� �� ��:             
  * �޸�����:    
  * ��    ��: 
  ******************************************************************************
  * attention
  *
  ******************************************************************************
  */
/*Includes --------------------------------------------------------------------*/
#include  "I2C.H" 
#include  "includes.h"

/* ���Ͷ��� typedef-----------------------------------------------------------*/
/* Ԥ�����ַ�     ------------------------------------------------------------*/
/* �궨��        -------------------------------------------------------------*/
/* ��������          ---------------------------------------------------------*/ 
extern void Delay_Us(__IO uint32_t nCount);
/*******************************************************************************
* ��������: I2C_GPIO_Init();
* ��������: ����I2C����,������ģ��ķ���ʵ��I2C����
* �������: void
* ���ز���: ��
********************************************************************************/
 void I2C_GPIO_Init(void)
{
     GPIO_InitTypeDef GPIO_InitStructure ;

     RCC_AHBPeriphClockCmd(I2C_PORT_CLK ,ENABLE);

     //����I2C_SCL/I2C_SDA����
     GPIO_InitStructure.GPIO_Pin   = I2C_SDA_PIN |I2C_SCL_PIN ;
     GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
     GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
     GPIO_Init(I2C_PRORT, &GPIO_InitStructure); 
     //GPIO_SetBits(I2C_PRORT, I2C_SDA_PIN |I2C_SCL_PIN );
     	
}
/*******************************************************************************
* ��������: I2C_SDA_OUT();
* ��������: ����SDA�˿�Ϊ���ģʽ
* �������: void
* ���ز���: ��
********************************************************************************/
 void I2C_SDA_OUT(void)
{
      GPIO_InitTypeDef  GPIO_InitStructure; 
      GPIO_InitStructure.GPIO_Pin   = I2C_SDA_PIN  ;
      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
      GPIO_Init(I2C_PRORT, &GPIO_InitStructure); 
}
/*******************************************************************************
* ��������: I2C_SDA_IN();
* ��������: ����SDA�˿�Ϊ����ģʽ
* �������: void
* ���ز���: ��
********************************************************************************/
 void I2C_SDA_IN(void)
{
      GPIO_InitTypeDef  GPIO_InitStructure; 
      GPIO_InitStructure.GPIO_Pin   = I2C_SDA_PIN  ;
      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
      GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
      GPIO_Init(I2C_PRORT, &GPIO_InitStructure); 
}
/*******************************************************************************
* ��������: I2C_Start();
* ��������: ��ʼ����
* �������: void
* ���ز���: ��
********************************************************************************/
void I2C_Start(void)
{
	I2C_SDA_OUT();
	I2C_SDA_H ;	  	  
	I2C_SCL_H ;
	Delay_Us(4);
 	I2C_SDA_L;   //START:when CLK is high,DATA change form high to low 
	Delay_Us(4);
	I2C_SCL_L  ;//ǯסI2C���ߣ�׼�����ͻ�������� 
  Delay_Us(4);
}
/*******************************************************************************
* ��������: I2C_Stop();
* ��������: ֹͣ����
* �������: void
* ���ز���: ��
********************************************************************************/
void I2C_Stop(void)
{
	      I2C_SDA_OUT();
        //I2C_SCL_L  ;
	      I2C_SDA_L; //STOP:when CLK is high DATA change form low to high	  	  
	      Delay_Us(4);
        I2C_SCL_H ;
	      Delay_Us(4);
	      I2C_SDA_H ; //����I2C���߽����ź�
        Delay_Us(4);	
}
/*******************************************************************************
* ��������: I2C_Wait_Ack();
* ��������: ���ӻ���Ӧ�����
* �������: ��
* ���ز���: �ӻ��Ƿ���Ӧ��1--ʧ�ܣ�0--�ɹ�
********************************************************************************/
unsigned char I2C_Wait_Ack(void)
{
	unsigned char utemp ;
	
	      I2C_SDA_H ;
        Delay_Us(2);	   
	      I2C_SCL_H ;
        Delay_Us(2);	 
	      I2C_SDA_IN();  //SDA����Ϊ����   
        utemp = I2C_SDA_VAL;
        Delay_Us(2);
        I2C_SCL_L  ;	
        Delay_Us(2);
        I2C_SDA_OUT();
        if( utemp)       return  1 ;
        else             return  0 ;
	
} 
/*******************************************************************************
* ��������: I2C_Ack();
* ��������: ����I2C������Ӧ�����
* �������: ��
* ���ز���: ��
********************************************************************************/
void I2C_Ack(void)
{       
        
	I2C_SCL_L;
  I2C_SDA_OUT();	
	I2C_SDA_L;
	Delay_Us(2);
	I2C_SCL_H ;
	Delay_Us(2);
	I2C_SCL_L;
        //I2C_SDA_H;
}
/*******************************************************************************
* ��������: I2C_NAck();
* ��������: ������I2C������Ӧ�����
* �������: ��
* ���ز���: ��
********************************************************************************/
void I2C_NAck(void)
{
	I2C_SCL_L;
  I2C_SDA_OUT();	
	I2C_SDA_H;
	Delay_Us(2);
	I2C_SCL_H ;
	Delay_Us(2);
	I2C_SCL_L;
}
/*******************************************************************************
* ��������: I2C_Write_1();
* ��������: ��IIC���߷���һ��1
* �������: ��
* ���ز���: ��
********************************************************************************/
 void I2C_Write_1(void)
{
	I2C_SDA_H;
	Delay_Us(2);
	I2C_SCL_H ;
	Delay_Us(2);
	I2C_SCL_L;		
	Delay_Us(2);
}
/*******************************************************************************
* ��������: I2C_Write_0();
* ��������: ��IIC���߷���һ��0
* �������: ��
* ���ز���: ��
********************************************************************************/
 void I2C_Write_0(void)
{
	I2C_SDA_L;
	Delay_Us(2);
	I2C_SCL_H ;
	Delay_Us(2);
	I2C_SCL_L;		
	Delay_Us(2);
}
/*******************************************************************************
* ��������: I2C_Send_Byte();
* ��������: ��IIC���߷���һ���ֽڵ�����
* �������: ucData--���͵�����
* ���ز���: ��
********************************************************************************/
void I2C_Send_Byte(unsigned char ucData)
{    
      unsigned char i;
	    //I2C_SDA_OUT();	
	    //I2C_SCL_L;		
      for(i = 8;i > 0;i--)
      {
	      if( ucData & 0x80)  I2C_Write_1();
	      else                I2C_Write_0();
        Delay_Us(2);
	      ucData <<= 1;
       }                  
	
       I2C_SDA_H;
			 Delay_Us(2);
			
}
/*******************************************************************************
* ��������: I2C_Send_Byte();
* ��������: ��IIC���߷���N���ֽڵ�����
* �������: pbuffer--ָ�������ݴ���׵�ַ
            n--���ݵĸ���
* ���ز���: �����Ƿ�ɹ��ı�־��0--�ɹ���1--ʧ��
********************************************************************************/
unsigned char I2C_Send_NByte(unsigned char * pbuffer, unsigned char n)
{
        unsigned char i;
        for(i = 0;i < n;i++)
        {  
           I2C_Send_Byte(* pbuffer);
	         if(I2C_Wait_Ack()==0)      
	         {
	            pbuffer++;			
	          }  
	          else 
	         {
	           I2C_Stop();
	            return 1;
	          }
        }
         I2C_Stop();
         return 0;	
}
/*******************************************************************************
* ��������: I2C_Read_Byte();
* ��������: ��IIC���߶�ȡһ���ֽ�
* �������: ��
* ���ز���: ��ȡ������
********************************************************************************/
unsigned char I2C_Read_Byte(void)
{    
      unsigned char  uData =0x00;
      unsigned char utemp,i;
      for(i = 8;i > 0;i--)
      {   
          I2C_SDA_H;
	        Delay_Us(2);
	        I2C_SCL_H ;
	         Delay_Us(2);
          I2C_SDA_IN();  //SDA����Ϊ����        
          Delay_Us(2);
          utemp = I2C_SDA_VAL;
          uData <<= 1;
          if(utemp) uData |= 0x01;
          Delay_Us(2);
          I2C_SCL_L;		
          Delay_Us(2);
          I2C_SDA_OUT();	
	
       }                  	
          I2C_SDA_H;
          Delay_Us(2);
			    return( uData );
}
/*******************************************************************************
* ��������: I2C_Read_NByte();
* ��������: ��IIC���߶�ȡN���ֽڵ�����
* �������: pbuffer--ָ�������ݴ���׵�ַ
            n--���ݵĸ���
* ���ز���: ��ȡ������
********************************************************************************/
void I2C_Read_NByte(unsigned char * pbuffer, unsigned char n)
{    
  unsigned char  i;
	for(i = 0;i < n;i++)
	{
	    pbuffer[i] = I2C_Read_Byte();
	    if( i < (n-1))   I2C_Ack();  //Ӧ��
	    else             I2C_NAck(); //��Ӧ��
	}
	 
	I2C_Stop();

}




