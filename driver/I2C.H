/*********************************Copyright (c)*********************************                                      
  *                                          
  ******************************************************************************
  * 文件名称：I2C.H
  * 描    述：I2C模块头文件
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

#ifndef  __I2C_H__
#define  __I2C_H__

/**********************头文件调用及变量定义声明*********************************/
/*  包含必要的头文件  */

/*  宏定义  */

// 对I2C数据总线进行操作。
//===========================================================
// PB6--SCL
// PB7--SDA

#define I2C_PRORT         GPIOB
#define I2C_PORT_CLK      RCC_AHBPeriph_GPIOB

#define I2C_SDA_PIN       GPIO_Pin_7
#define I2C_SCL_PIN       GPIO_Pin_6


#define	I2C_SDA_H         GPIO_SetBits(I2C_PRORT, I2C_SDA_PIN)
#define	I2C_SDA_L         GPIO_ResetBits(I2C_PRORT, I2C_SDA_PIN)
#define I2C_SDA_VAL       GPIO_ReadInputDataBit(I2C_PRORT,I2C_SDA_PIN)
#define	I2C_SCL_H         GPIO_SetBits(I2C_PRORT, I2C_SCL_PIN )
#define	I2C_SCL_L         GPIO_ResetBits(I2C_PRORT, I2C_SCL_PIN)



/*  子函数定义        */
extern  void I2C_GPIO_Init(void);
extern  void I2C_SDA_OUT(void);
extern  void I2C_SDA_IN(void);
extern  void I2C_Start(void);
extern  void I2C_Stop(void);
extern  unsigned char I2C_Wait_Ack(void);
extern  void I2C_Ack(void);
extern  void I2C_NAck(void);
extern  void I2C_Write_1(void);
extern  void I2C_Write_0(void);
extern  void I2C_Send_Byte(unsigned char ucData);
extern  unsigned char I2C_Send_NByte(unsigned char * pbuffer, unsigned char n);
extern  unsigned char I2C_Read_Byte(void);
extern  void I2C_Read_NByte(unsigned char * pbuffer, unsigned char n);


#endif  

