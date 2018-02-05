/**
  ******************************************************************************
  * @file    Demonstrations/Src/stm32f0xx_it.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-June-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "stm32f0xx_it.h"

/** @addtogroup STM32F0xx_HAL_Demonstrations
  * @{
  */

/** @addtogroup Demo
  * @{
  */ 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
	 extern  uint8_t dataToComputer[10];
	 extern uint8_t falg_usart2,falg_usart3;
	 extern uint8_t system_state;
	 u8 NRA24_1_updata=0;//毫米波雷达1数据更新
	 u8 NRA24_2_updata=0;//毫米波雷达2数据更新
	 u8 mpu6050_updata=0;//陀螺仪数据更新
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	if(system_state)
	{
		DMA_Cmd(DMA1_Channel2, ENABLE);
    if(NRA24_1_updata||NRA24_2_updata||mpu6050_updata)
		{
	  	DMA_Cmd(DMA1_Channel2, ENABLE);
			NRA24_1_updata=0;
			NRA24_2_updata=0;
			mpu6050_updata=0;
		}
		
	}

}
void DMA1_Channel2_3_IRQHandler(void)
	{
		if(DMA_GetITStatus(DMA1_IT_TC2))
		{
			DMA_ClearITPendingBit(DMA1_IT_GL2);
			DMA_Cmd(DMA1_Channel2, DISABLE);
		}
	}

void DMA1_Channel4_5_6_7_IRQHandler(void)
	{
		if(DMA_GetITStatus(DMA1_IT_TC4))
		{
			DMA_ClearITPendingBit(DMA1_IT_GL4);
		}
		
		
		
		
		
		
		/////////////////////////////////////////////////////////////////////////
	  if(DMA_GetITStatus(DMA1_IT_TC5))
		{
			DMA_ClearITPendingBit(DMA1_IT_GL5);

		if((Uart2_Rx[2] == 0x0C) && (Uart2_Rx[3] == 0x07))
      {
        dataToComputer[1] = Uart2_Rx[6];
        dataToComputer[2] = Uart2_Rx[7];
				NRA24_1_updata=1;
      }
      else
      {
        dataToComputer[1] = 0xFF;
        dataToComputer[2] = 0xFF;
      }		
    } 
		
	////////////////////////////////////////////////////////////////////////////////	
		
		
		
		
				
		if(DMA_GetITStatus(DMA1_IT_TC6))
		{
			DMA_ClearITPendingBit(DMA1_IT_GL6);

		if((Uart3_Rx[2] == 0x0C) && (Uart3_Rx[3] == 0x07))
      {
        dataToComputer[3] = Uart3_Rx[6];
        dataToComputer[4] = Uart3_Rx[7];
				NRA24_2_updata=1;
      }
      else
      {
        dataToComputer[3] = 0xFF;
        dataToComputer[4] = 0xFF;
      }
	
	}
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) , for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

void USART1_IRQHandler(void)
{

}


void USART2_IRQHandler(void)
{
	
	

}


void USART3_4_IRQHandler (void)
{

}
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
