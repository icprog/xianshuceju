/*********************************Copyright (c)*********************************                                      
  *                                                 
  ******************************************************************************
  * 文件名称：LED.H
  * 描    述：LED头文件
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

#ifndef  __LED_H__ 
#define  __LED_H__
/**********************头文件调用及变量定义声明****************************************/
/*  包含必要的头文件  */

/*  宏定义  */


#define  LED_PORT          GPIOA
#define  LED_PIN           GPIO_Pin_5
#define  LED_PORT_CLK      RCC_AHBPeriph_GPIOA  

#define  LED_PIN_1         GPIO_Pin_5










extern    void LED_Init(void);
extern    void LED_BLINK(void);
extern    void Delay(__IO uint32_t nCount);
extern    void Delay_Us(__IO uint32_t nCount);
extern    void Delay_Ms(__IO uint32_t nCount);

#endif  

