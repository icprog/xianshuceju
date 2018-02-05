




#ifndef __MPU6050_PROCESS_H__
#define __MPU6050_PROCESS_H__

typedef struct __ACCEL_AVERAGE_DATA__
{
    float X;
    float Y;
    float Z;
}ACCEL_AVERAGE_DATA;

typedef struct __GYRO_RADIAN_DATA__
{
    float X;
    float Y;
    float Z;
}GYRO_RADIAN_DATA;

typedef struct __MPU6050_ANGLE__
{
    float Pitch;
    float Rool;
    float Yaw;
}MPU6050_ANGLE;

extern ACCEL_AVERAGE_DATA   Accel_Raw_Average_Data; 
extern GYRO_RADIAN_DATA     Gyro_Radian_Data;
extern MPU6050_ANGLE        MPU6050_Angle;
float Kalman_Filter(float angle_m, float gyro_m);
void MPU6050_Data_Filter(void);
void MPU6050_Angle_Calculate( float gyro_x,
                              float gyro_y,
                              float gyro_z,
                              float accel_x,
                              float accel_y,
                              float accel_z);
void IMU_AHRSupdate(float gx,
                    float gy, 
                    float gz, 
                    float ax,
                    float ay,
                    float az,
                    float mx,
                    float my,
                    float mz);
#endif
