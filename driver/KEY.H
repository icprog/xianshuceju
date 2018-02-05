/*******************************************************************************                                     
  *                                         
  ******************************************************************************
  * 文件名称：KEY.H
  * 描    述：按键头文件
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

#ifndef  __KEY_H__ 
#define  __KEY_H__
/**********************头文件调用及变量定义声明****************************************/
/*  包含必要的头文件  */
 #include   "stm32f0xx_conf.h"
/*  宏定义  */

//说明：KEY按键管脚资源定义:按键按下时输入低电平 按键释放时输入高电平--采用中断方式


//1个引脚为：PC13
/** KEY1按键管脚  **/
#define KEY1_BUTTON_PIN                  GPIO_Pin_13
#define KEY1_BUTTON_PORT                 GPIOC
#define KEY1_BUTTON_CLK                  RCC_AHBPeriph_GPIOC
#define KEY1_BUTTON_EXTI_LINE            EXTI_Line13
#define KEY1_BUTTON_EXTI_PORT_SOURCE     EXTI_PortSourceGPIOC
#define KEY1_BUTTON_EXTI_PIN_SOURCE      EXTI_PinSource13
#define KEY1_BUTTON_EXTI_IRQn            EXTI4_15_IRQn
#define KEY1_USER                        GPIO_ReadInputDataBit(KEY1_BUTTON_PORT,KEY1_BUTTON_PIN)//读取用户按键的值




#define  USER_BUTTON    1


//函数声明部分
extern  void  Key_Init(void);
extern  unsigned char Key_Scan(void);
#endif  

