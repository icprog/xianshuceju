#ifndef __EXTI_H
#define __EXIT_H	 
#include "includes.h"
typedef struct 
{
	float gyro_x;
	float gyro_y;
	float gyro_z;
	float accel_x;
	float accel_y;
	float accel_z;
	float pitch;
	float yaw;
	float roll;
} Mpu_data;
extern Mpu_data mpu_series1;
 void EXTI2_3_Config(void); 					    
#endif

























