/*********************************Copyright (c)*********************************                                      
  *                                      
  ******************************************************************************
  * 文件名称：I2C.C
  * 描    述：软件模拟IIC模块
  * 创 建 者: 
  * 创建日期:    
  * 修 改 者:             
  * 修改日期:    
  * 版    本: 
  ******************************************************************************
  * attention
  *
  ******************************************************************************
  */
/*Includes --------------------------------------------------------------------*/
#include  "I2C.H" 
#include  "includes.h"

/* 类型定义 typedef-----------------------------------------------------------*/
/* 预定义字符     ------------------------------------------------------------*/
/* 宏定义        -------------------------------------------------------------*/
/* 变量定义          ---------------------------------------------------------*/ 
extern void Delay_Us(__IO uint32_t nCount);
/*******************************************************************************
* 函数名称: I2C_GPIO_Init();
* 功能描述: 设置I2C引脚,用软件模拟的方法实现I2C功能
* 输入参数: void
* 返回参数: 无
********************************************************************************/
 void I2C_GPIO_Init(void)
{
     GPIO_InitTypeDef GPIO_InitStructure ;

     RCC_AHBPeriphClockCmd(I2C_PORT_CLK ,ENABLE);

     //配置I2C_SCL/I2C_SDA引脚
     GPIO_InitStructure.GPIO_Pin   = I2C_SDA_PIN |I2C_SCL_PIN ;
     GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
     GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
     GPIO_Init(I2C_PRORT, &GPIO_InitStructure); 
     //GPIO_SetBits(I2C_PRORT, I2C_SDA_PIN |I2C_SCL_PIN );
     	
}
/*******************************************************************************
* 函数名称: I2C_SDA_OUT();
* 功能描述: 设置SDA端口为输出模式
* 输入参数: void
* 返回参数: 无
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
* 函数名称: I2C_SDA_IN();
* 功能描述: 设置SDA端口为输入模式
* 输入参数: void
* 返回参数: 无
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
* 函数名称: I2C_Start();
* 功能描述: 开始条件
* 输入参数: void
* 返回参数: 无
********************************************************************************/
void I2C_Start(void)
{
	I2C_SDA_OUT();
	I2C_SDA_H ;	  	  
	I2C_SCL_H ;
	Delay_Us(4);
 	I2C_SDA_L;   //START:when CLK is high,DATA change form high to low 
	Delay_Us(4);
	I2C_SCL_L  ;//钳住I2C总线，准备发送或接收数据 
  Delay_Us(4);
}
/*******************************************************************************
* 函数名称: I2C_Stop();
* 功能描述: 停止条件
* 输入参数: void
* 返回参数: 无
********************************************************************************/
void I2C_Stop(void)
{
	      I2C_SDA_OUT();
        //I2C_SCL_L  ;
	      I2C_SDA_L; //STOP:when CLK is high DATA change form low to high	  	  
	      Delay_Us(4);
        I2C_SCL_H ;
	      Delay_Us(4);
	      I2C_SDA_H ; //发送I2C总线结束信号
        Delay_Us(4);	
}
/*******************************************************************************
* 函数名称: I2C_Wait_Ack();
* 功能描述: 检查从机的应答操作
* 输入参数: 无
* 返回参数: 从机是否有应答：1--失败，0--成功
********************************************************************************/
unsigned char I2C_Wait_Ack(void)
{
	unsigned char utemp ;
	
	      I2C_SDA_H ;
        Delay_Us(2);	   
	      I2C_SCL_H ;
        Delay_Us(2);	 
	      I2C_SDA_IN();  //SDA设置为输入   
        utemp = I2C_SDA_VAL;
        Delay_Us(2);
        I2C_SCL_L  ;	
        Delay_Us(2);
        I2C_SDA_OUT();
        if( utemp)       return  1 ;
        else             return  0 ;
	
} 
/*******************************************************************************
* 函数名称: I2C_Ack();
* 功能描述: 产生I2C的主机应答操作
* 输入参数: 无
* 返回参数: 无
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
* 函数名称: I2C_NAck();
* 功能描述: 不产生I2C的主机应答操作
* 输入参数: 无
* 返回参数: 无
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
* 函数名称: I2C_Write_1();
* 功能描述: 向IIC总线发送一个1
* 输入参数: 无
* 返回参数: 无
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
* 函数名称: I2C_Write_0();
* 功能描述: 向IIC总线发送一个0
* 输入参数: 无
* 返回参数: 无
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
* 函数名称: I2C_Send_Byte();
* 功能描述: 向IIC总线发送一个字节的数据
* 输入参数: ucData--发送的数据
* 返回参数: 无
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
* 函数名称: I2C_Send_Byte();
* 功能描述: 向IIC总线发送N个字节的数据
* 输入参数: pbuffer--指向发送数据存放首地址
            n--数据的个数
* 返回参数: 发送是否成功的标志：0--成功，1--失败
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
* 函数名称: I2C_Read_Byte();
* 功能描述: 从IIC总线读取一个字节
* 输入参数: 无
* 返回参数: 读取的数据
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
          I2C_SDA_IN();  //SDA设置为输入        
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
* 函数名称: I2C_Read_NByte();
* 功能描述: 从IIC总线读取N个字节的数据
* 输入参数: pbuffer--指向发送数据存放首地址
            n--数据的个数
* 返回参数: 读取的数据
********************************************************************************/
void I2C_Read_NByte(unsigned char * pbuffer, unsigned char n)
{    
  unsigned char  i;
	for(i = 0;i < n;i++)
	{
	    pbuffer[i] = I2C_Read_Byte();
	    if( i < (n-1))   I2C_Ack();  //应答
	    else             I2C_NAck(); //无应答
	}
	 
	I2C_Stop();

}





