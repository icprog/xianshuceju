/*******************************************************************************                                  
  *                                            
  ******************************************************************************
  * �ļ����ƣ�KEY.C
  * ��    ��������ģ��
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
  #include "includes.h"
  #include "KEY.H" 
  
/********************************************************************************
�������ƣ�Key_Init()
��    �ܣ�������ʼ��
��    ������
�� �� ֵ����
*********************************************************************************/
void Key_Init(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      EXTI_InitTypeDef EXTI_InitStructure;
      
      /* ʹ��KEY������ӦGPIO��Clockʱ�� */

      RCC_AHBPeriphClockCmd(KEY1_BUTTON_CLK , ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

      //�û���������--KEY1��������
      GPIO_InitStructure.GPIO_Pin =  KEY1_BUTTON_PIN ;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
      GPIO_Init(KEY1_BUTTON_PORT , &GPIO_InitStructure);
      

      
     
      SYSCFG_EXTILineConfig(KEY1_BUTTON_EXTI_PORT_SOURCE, KEY1_BUTTON_EXTI_PIN_SOURCE);
      
     
      EXTI_InitStructure.EXTI_Line = KEY1_BUTTON_EXTI_LINE;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;
      EXTI_Init(&EXTI_InitStructure);
    
     

}
/********************************************************************************
�������ƣ�Key_Scan()
��    �ܣ�������������--ɨ�跽ʽ
��    ����
�� �� ֵ����
*********************************************************************************/
unsigned char Key_Scan(void)
{    	 
   return 0;  
}
