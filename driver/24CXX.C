/*********************************Copyright (c)*********************************                                      
  *                                                
  ******************************************************************************
  * 文件名称：24CXX.C
  * 描    述：EEPROM读写模块
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
#include  "24CXX.H" 
#include  "includes.h"
#include  "I2C.H" 
/* 类型定义 typedef-----------------------------------------------------------*/
/* 预定义字符     ------------------------------------------------------------*/
/* 宏定义        -------------------------------------------------------------*/
/* 变量定义          ---------------------------------------------------------*/ 
extern void Delay_Ms(__IO uint32_t nCount);
extern void Delay_Us(__IO uint32_t nCount);

#define Device_Address  0xA0  //24CXX的设备地址
/*******************************************************************************
* 函数名称: 24CXX_Read_Byte()
* 功能描述: 从24CXX的指定地址读取1个字节的数据
* 输入参数: dataaddress--数据读取的地址
* 返回参数: 读取的数据
********************************************************************************/
unsigned char EEPROM_Read_Byte(unsigned char dataaddress)
{
        unsigned char temp;
    
	      I2C_Start();                         // 起始条件
	      I2C_Send_Byte(Device_Address);       // 向从器件发送设备地址
	      if(I2C_Wait_Ack()==0)                // 如果有从器件应答
            I2C_Send_Byte(dataaddress);      // 发送数据地址
	      else 
             return 0;
	      if(I2C_Wait_Ack()==0) 
	      {
	          I2C_Start();                       // 起始条件
	          I2C_Send_Byte((Device_Address|0x01));
	      }
	      else    
             return 0;
	      if(I2C_Wait_Ack()==0)	
             temp = I2C_Read_Byte();
	      else 
             return 0;

	       I2C_NAck();
	       I2C_Stop();
	       return temp;
     	
}
/*******************************************************************************
* 函数名称: 24CXX_Read_NByte()
* 功能描述: 从24CXX的指定地址读取N个字节的数据
* 输入参数: pbuffer--指向保存数据地址的指针
            n--读取数据的个数
            dataaddress--数据读取的首地址
* 返回参数: 读取结果：0--成功，1--失败
********************************************************************************/
unsigned char  EEPROM_Read_NByte( unsigned char *pbuffer, unsigned char n, unsigned char dataaddress )
{
        I2C_Start();                         // 起始条件
	      I2C_Send_Byte(Device_Address);       // 向从器件发送设备地址
	      if(I2C_Wait_Ack()==0)                // 如果有从器件应答
            I2C_Send_Byte(dataaddress);      // 发送数据地址
	      else 
               return 1;
	      if(I2C_Wait_Ack()==0) 
	      {
	        I2C_Start();                       // 起始条件
	        I2C_Send_Byte((Device_Address|0x01));
	      }
      	else      
					    return 1;
	      if(I2C_Wait_Ack()==0)	
               I2C_Read_NByte(pbuffer, n);
	       else 
               return 1;
	
	      return  0;	
}
/*******************************************************************************
* 函数名称:  24CXX_Write_Byte();
* 功能描述:  向24CXX的指定地址中写入1个字节的数据  
* 输入参数:  wdata--写入的数据
             dataaddress--数据读取的首地址
* 返回参数:  写入结果：0--成功，1--失败
********************************************************************************/
unsigned char  EEPROM_Write_Byte( unsigned char dataaddress, unsigned char wdata )
{
        I2C_Start();                         // 起始条件
        I2C_Send_Byte(Device_Address);       // 向从器件发送设备地址
	      if(I2C_Wait_Ack()==0)                // 如果有从器件应答
            I2C_Send_Byte(dataaddress);      // 发送数据地址
	      else 
            return 1;
        if(I2C_Wait_Ack()==0)                // 如果从器件应答
            I2C_Send_Byte(wdata);            // 发送要写入的数据
        else 
               return 1 ;
        if(I2C_Wait_Ack()==0)                // 如果从器件应答
               I2C_Stop();                   // 如果从器件应答 ，发送停止条件
        else           
               return 1;
    
        Delay_Ms(5);                 //等待EEPROM完成内部写入(重要)
	      return 0 ; 
}
/*******************************************************************************
* 函数名称:  24CXX_Write_NByte();
* 功能描述:  向24CXX的指定地址中写入1个字节的数据  
* 输入参数:  dataaddress--数据读取的地址
* 返回参数:  写入结果：0--成功，1--失败
********************************************************************************/
unsigned char  EEPROM_Write_NByte( unsigned char *pbuffer, unsigned char n, unsigned char dataaddress )
{
         unsigned char  temp; 
    
	       I2C_Start();                         // 起始条件
         I2C_Send_Byte(Device_Address);       // 向从器件发送设备地址
	       if(I2C_Wait_Ack()==0)                // 如果有从器件应答
            I2C_Send_Byte(dataaddress);      // 发送数据地址
	       else 
               return 1;
         if(I2C_Wait_Ack()==0)                // 如果从器件应答
             temp = I2C_Send_NByte(pbuffer, n);
	       else 
               return 1;
         Delay_Ms(5);                 //等待EEPROM完成内部写入(重要)
	       if(temp==0)    return 0;
	       else           return 1;

}
