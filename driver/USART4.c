 




  #include "includes.h"
  #include "USART4.H" 
  #include <stdarg.h>
	
  void Uart4_Init(void)
{
   
        GPIO_InitTypeDef  GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;
	
        RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA   , ENABLE);   // 使能GPIOA端口
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART4   , ENABLE); // 使能串口4时钟
	    
        GPIO_PinAFConfig(GPIOA ,GPIO_PinSource0, GPIO_AF_4);
        GPIO_PinAFConfig(GPIOA ,GPIO_PinSource1, GPIO_AF_4);                           
/////////////////////////////////////////////////////////////////////////////////////        
        /* PA0==TX PA1-RX  */  
                                      
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;                 
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
        GPIO_Init(GPIOA, &GPIO_InitStructure); 

        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
	      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
        GPIO_Init(GPIOA , &GPIO_InitStructure); 
///////////////////////////////////////////////////////////////////////////////////// 
           
        USART_InitStructure.USART_BaudRate = 115200;                 		      
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;     	       
        USART_InitStructure.USART_StopBits = USART_StopBits_1;                         
        USART_InitStructure.USART_Parity = USART_Parity_No;                            
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;               
        USART_Init(USART4, &USART_InitStructure); 	//串口配置
        USART_Cmd(USART4, ENABLE);//使能串口4
}
