  #include "includes.h"
	Mpu_data mpu_series1,mpu_series2;
  extern u8 mpu6050_updata;
/**************************************************************************
函数功能：外部中断初始化
入口参数：无
返回  值：无 
**************************************************************************/
extern  uint8_t dataToComputer[10] ;
 void EXTI2_3_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
  /* Enable GPIOE clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

  /* Configure PE2 and PE3 pins as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
  /* Connect EXTI2 Line to PE3 pin */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
  
  /* Configure EXTI3 line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;  
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI2_3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
}

void EXTI2_3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET)
  {
		 Read_DMP();	 
		 MPU6050_ReadData(1);
		 MPU6050_Angle_Calculate( MPU6050_Real_Data.Gyro_X,
                              MPU6050_Real_Data.Gyro_Y,
                              MPU6050_Real_Data.Gyro_Z,
                              MPU6050_Real_Data.Accel_X,
                              MPU6050_Real_Data.Accel_Y,
                              MPU6050_Real_Data.Accel_Z);	
	  mpu_series1.pitch=Pitch;
		mpu_series2.pitch=MPU6050_Angle.Pitch;
    mpu_series1.roll=Roll;
		mpu_series2.roll=MPU6050_Angle.Rool;

		dataToComputer[8]=(uint8_t)((int16_t)mpu_series1.roll>>8);
		dataToComputer[7]=(uint8_t)((int16_t)mpu_series1.roll);
		dataToComputer[6]=(uint8_t)((int16_t)mpu_series2.roll>>8);
		dataToComputer[5]=(uint8_t)((int16_t)mpu_series2.roll);		
    mpu6050_updata=1;
		
//		mpu_series1.accel_x=(float)((accel[0]/16384.0f)*9.81f);
//		mpu_series1.accel_y=(float)((accel[1]/16384.0f)*9.81f);
//		mpu_series1.accel_z=(float)((accel[2]/16384.0f)*9.81f);
//		mpu_series1.gyro_x=gyro[0]/65.5;
//		mpu_series1.gyro_y=gyro[1]/65.5;
//		mpu_series1.gyro_z=gyro[2]/65.5;
//		mpu_series1.roll=Roll;
//		mpu_series1.yaw=Yaw;

		 /* Clear the EXTI line 3 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line3);
  }
}






