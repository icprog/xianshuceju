/*******************************************************************************                                     
  *                                         
  ******************************************************************************
  * �ļ����ƣ�KEY.H
  * ��    ��������ͷ�ļ�
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

#ifndef  __KEY_H__ 
#define  __KEY_H__
/**********************ͷ�ļ����ü�������������****************************************/
/*  ������Ҫ��ͷ�ļ�  */
 #include   "stm32f0xx_conf.h"
/*  �궨��  */

//˵����KEY�����ܽ���Դ����:��������ʱ����͵�ƽ �����ͷ�ʱ����ߵ�ƽ--�����жϷ�ʽ


//1������Ϊ��PC13
/** KEY1�����ܽ�  **/
#define KEY1_BUTTON_PIN                  GPIO_Pin_13
#define KEY1_BUTTON_PORT                 GPIOC
#define KEY1_BUTTON_CLK                  RCC_AHBPeriph_GPIOC
#define KEY1_BUTTON_EXTI_LINE            EXTI_Line13
#define KEY1_BUTTON_EXTI_PORT_SOURCE     EXTI_PortSourceGPIOC
#define KEY1_BUTTON_EXTI_PIN_SOURCE      EXTI_PinSource13
#define KEY1_BUTTON_EXTI_IRQn            EXTI4_15_IRQn
#define KEY1_USER                        GPIO_ReadInputDataBit(KEY1_BUTTON_PORT,KEY1_BUTTON_PIN)//��ȡ�û�������ֵ




#define  USER_BUTTON    1


//������������
extern  void  Key_Init(void);
extern  unsigned char Key_Scan(void);
#endif  
