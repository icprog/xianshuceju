/*******************************************************************************                                    
  *                                                
  ******************************************************************************
  * 文件名称：UART.H
  * 描    述：串口头文件
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

#ifndef  __UART_H__ 
#define  __UART_H__
/**********************头文件调用及变量定义声明****************************************/
/*  包含必要的头文件  */
  
  #include   "stm32f0xx_conf.h"
  #include <stdarg.h>
  #include <stdio.h>


//板载串口1的宏定义

#define F072RB_COM                           USART1
#define F072RB_COM_CLK                       RCC_APB2Periph_USART1

#define F072RB_COM_TX_PIN                    GPIO_Pin_9
#define F072RB_COM_RX_PIN                    GPIO_Pin_10
#define F072RB_COM_PORT           	     		 GPIOA
#define F072RB_COM_PORT_CLK            	     RCC_AHBPeriph_GPIOA


#define F072RB_COM_TX_SOURCE                 GPIO_PinSource9
#define F072RB_COM_TX_AF                     GPIO_AF_1

#define F072RB_COM_RX_SOURCE                 GPIO_PinSource10
#define F072RB_COM_RX_AF                     GPIO_AF_1
#define Uart1_Rx_LEN 512

/*  子函数定义        */
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx);
extern  uint8_t Uart1_Rx[Uart1_Rx_LEN];
extern  void Uart_Init(void);  
extern  void Uart_Put_Char(USART_TypeDef* USARTx,unsigned char c);
extern  unsigned char Uart_Get_Char(void);
extern  int  fputc(int ch, FILE *f);
extern  unsigned char UartRead(unsigned char *buf, unsigned char len);
extern  void UartWrite(unsigned char *buf, unsigned char len);
extern  unsigned char CmdCompare(unsigned char *buf, const unsigned char *cmd);
extern  void TrimString16(unsigned char *out, unsigned char *in);
extern  void UartDriver(void);
extern  void UartRxMonitor(unsigned char ms);
void USART_Send_Date( USART_TypeDef* USARTx, uint8_t *pWord, uint16_t Len );
#endif  

