/*********************************Copyright (c)*********************************                                      
  *                                               
  ******************************************************************************
  * 文件名称：includes.h
  * 描    述：
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
#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__	
	
/*Includes --------------------------------------------------------------------*/
  #include   "stm32f0xx.h" 
  #include   "stm32f0xx_conf.h"
  #include   "stm32f0xx_it.h "
  #include  "system_stm32f0xx.h"
  //#include  "stm32f0xx_nucleo.h"
 
  #include   <stdio.h>
  #include   <string.h>
	#include  "delay.h"
  #include "SYSTICK.H"
  #include "UART.H" 
	#include "UART2.H"
	#include "UART3.H"
	#include "USART4.H"
	#include "IWDG.H"
  #include "NVIC.H"
  #include <math.h>
  #include "mpu6050_i2c.h"
  #include "mpu6050_interrupt.h"
  #include "mpu6050_driver.h"
  #include "mpu6050_process.h"
  #include "exti.h"
  #include "inv_mpu.h"
  #include "inv_mpu_dmp_motion_driver.h"
  #include "dmpKey.h"
  #include "dmpmap.h"
  #include <stdio.h>
  #include <stdint.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include "mpu6050.h"
	#include "ioi2c.h"
	#include "delay.h"
	#include "Kalman_filter.h"
	#include "ANO-Tech.h"
//#include "MPU6050.h"
//============================================================================//	
	
/* 类型定义 typedef------------------------------------------------------------*/
/* 预定义字符------------------------------------------------------------------*/
/* 宏定义----------------------------------------------------------------------*/
/* 变量定义--------------------------------------------------------------------*/ 
   

/* 子函数声明--------------------------------------------------------------------*/ 
 extern  int main(void);
void sendtoFXCV(void);
#endif  


