/*********************************Copyright (c)*********************************                                      
  *                                                 
  ******************************************************************************
  * �ļ����ƣ�LED.H
  * ��    ����LEDͷ�ļ�
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

#ifndef  __LED_H__ 
#define  __LED_H__
/**********************ͷ�ļ����ü�������������****************************************/
/*  ������Ҫ��ͷ�ļ�  */

/*  �궨��  */


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
