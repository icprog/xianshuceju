/*******************************************************************************                                      
  *                                               
  ******************************************************************************
  * 文件名称：UART.C
  * 描    述：串口通信模块
  * 创 建 者: 
  * 创建日期:    
  * 修 改 者:             
  * 修改日期: 
  * 版    本: v1.0.0
  ******************************************************************************
  * attention
  *
  ******************************************************************************
  */
/*Includes --------------------------------------------------------------------*/
  #include "includes.h"
  #include "UART.H" 
  #include <stdarg.h>
/* 类型定义 typedef-----------------------------------------------------------*/
/* 预定义字符     ------------------------------------------------------------*/
/* 宏定义        -------------------------------------------------------------*/
/* 变量定义          ---------------------------------------------------------*/ 
//#define Uart1_Rx_LEN 512
//uint8_t Uart1_Rx[Uart1_Rx_LEN];
/*******************************************************************************
* 函数名称: Uart_Init()
* 功能描述: 串口初始化
* 输入参数: void
* 返回参数: 无
********************************************************************************/

extern uint8_t dataToComputer[10];
uint8_t Uart1_Rx[Uart1_Rx_LEN];
void Uart_Init(void)
{
   
        GPIO_InitTypeDef  GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;
				DMA_InitTypeDef  DMA_InitStructure;
        NVIC_InitTypeDef NVIC_InitStructure;
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
                    
        RCC_AHBPeriphClockCmd( F072RB_COM_PORT_CLK   , ENABLE);   // 使能GPIOB端口
        RCC_APB2PeriphClockCmd(F072RB_COM_CLK   , ENABLE); // 使能串口1时钟
	    
        GPIO_PinAFConfig(F072RB_COM_PORT ,F072RB_COM_TX_SOURCE, F072RB_COM_TX_AF);
        GPIO_PinAFConfig(F072RB_COM_PORT ,F072RB_COM_RX_SOURCE, F072RB_COM_RX_AF);                           
/////////////////////////////////////////////////////////////////////////////////////        
        /* PA9==TX PA10-RX  */  
                                      
        GPIO_InitStructure.GPIO_Pin   = F072RB_COM_TX_PIN ;                 
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
        GPIO_Init(F072RB_COM_PORT, &GPIO_InitStructure); 

        GPIO_InitStructure.GPIO_Pin   = F072RB_COM_RX_PIN ;
	      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
        GPIO_Init(F072RB_COM_PORT , &GPIO_InitStructure); 
///////////////////////////////////////////////////////////////////////////////////// 
           
        USART_InitStructure.USART_BaudRate = 115200;                 		      
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;     	       
        USART_InitStructure.USART_StopBits = USART_StopBits_1;                         
        USART_InitStructure.USART_Parity = USART_Parity_No;                            
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;               
        USART_Init(F072RB_COM, &USART_InitStructure); 	//串口配置
				USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
        USART_ITConfig(F072RB_COM, USART_IT_RXNE ,ENABLE);//打开中断	
			  USART_ClearFlag(F072RB_COM, USART_FLAG_TC);
        USART_Cmd(F072RB_COM, ENABLE);//使能串口1
				
        DMA_DeInit(DMA1_Channel2);
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->TDR);
        DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)dataToComputer;
				DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
				DMA_InitStructure.DMA_BufferSize =10;
				DMA_InitStructure.DMA_PeripheralInc = DMA_MemoryInc_Disable;
				DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
				DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
				DMA_InitStructure.DMA_MemoryDataSize =DMA_MemoryDataSize_Byte;
				DMA_InitStructure.DMA_Mode = DMA_Mode_Circular    ;
				DMA_InitStructure.DMA_Priority = DMA_Priority_High;
				DMA_InitStructure.DMA_M2M =  DMA_M2M_Disable;
				DMA_Init(DMA1_Channel2, &DMA_InitStructure);
  
        DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);
  
        NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_3_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPriority = 4;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
       // DMA_Cmd(DMA1_Channel2, ENABLE);
}
//开启一次DMA传输
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );  //关闭USART1 TX DMA1 所指示的通道      
 	DMA_SetCurrDataCounter(DMA_CHx,7);//DMA通道的DMA缓存的大小
 	DMA_Cmd(DMA_CHx, ENABLE);  //使能USART1 TX DMA1 所指示的通道 
}	  

/*******************************************************************************
* 函数名称: Uart_Put_Char()
* 功能描述: 通过UART发送一个字符
* 输入参数: void
* 返回参数: 无
********************************************************************************/
void Uart_Put_Char(USART_TypeDef* USARTx,unsigned char c)
{    
	 
     while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	
	   USART_SendData(USARTx,c);  
	   
}

/*******************************************************************************
* 函数名称: Uart_Get_Char()
* 功能描述: 通过UART接收一个字符
* 输入参数: void
* 返回参数: 无
********************************************************************************/ 
unsigned char Uart_Get_Char(void)
{    
     unsigned char temp;
     while(USART_GetFlagStatus(F072RB_COM, USART_FLAG_RXNE) == RESET);//等待接收为空
     temp = (unsigned char)(USART_ReceiveData(F072RB_COM));
     return(temp);    
}
/*******************************************************************************
函数名称：fputc(int ch, FILE *f)
功    能：串口实现Printf()函数功能
参    数：无
返回值  ：
********************************************************************************/
int fputc(int ch, FILE *f)
{
  while (USART_GetFlagStatus(USART4, USART_FLAG_TXE) == RESET);
  USART_SendData(USART4,(uint8_t)ch);
  return (ch);
}

void USART_Send_Date( USART_TypeDef* USARTx, uint8_t *pWord, uint16_t Len )
{
	uint8_t i = 0;
	for(i=0; i<Len; i++) {
		USART_SendData(USARTx, (uint8_t)*pWord);
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);
		pWord++;
	}

}





	
 
