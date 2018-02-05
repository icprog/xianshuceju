



#include "includes.h"

ACCEL_AVERAGE_DATA   Accel_Raw_Average_Data; 
GYRO_RADIAN_DATA     Gyro_Radian_Data;
MPU6050_ANGLE        MPU6050_Angle;
#define Gyro_G 	0.0152672	
void MPU6050_Data_Filter(void)  // this*0.01 + (��һ���õ�)last *0.99 Ҫ��
{
    unsigned int i=0;
    static unsigned int first_flag = 0;
    static unsigned int filter_cnt = 0;    //������ٶȼ��˲��Ĵ���
    
    long temp_accel_x = 0; //������ż��ٶȼ�X��ԭ�����ݵ��ۼӺ�
    long temp_accel_y = 0; //������ż��ٶȼ�Y��ԭ�����ݵ��ۼӺ�
    long temp_accel_z = 0; //������ż��ٶȼ�Z��ԭ�����ݵ��ۼӺ�
    
    static short accel_x_buffer[10] = {0}; //������ż��ٶȼ�X�����10�����ݵ�����
    static short accel_y_buffer[10] = {0}; //������ż��ٶȼ�Y�����10�����ݵ�����
    static short accel_z_buffer[10] = {0}; //������ż��ٶȼ�Z�����10�����ݵ�����
    
    if(first_flag == 0) //�����һ�ν����ú��������������ƽ����������г�ʼ��
    {
        first_flag = 1; //�Ժ��ٽ���
        for(i=0;i<10;i++)
        {
            accel_x_buffer[i] = MPU6050_Raw_Data.Accel_X;
            accel_y_buffer[i] = MPU6050_Raw_Data.Accel_Y;
            accel_z_buffer[i] = MPU6050_Raw_Data.Accel_Z;
        }
    }
    else  //������ǵ�һ����
    {
        accel_x_buffer[filter_cnt] = MPU6050_Raw_Data.Accel_X;
        accel_y_buffer[filter_cnt] = MPU6050_Raw_Data.Accel_Y;
        accel_z_buffer[filter_cnt] = MPU6050_Raw_Data.Accel_Z;   
        
        filter_cnt ++;
        if(filter_cnt == 10)
        {
            filter_cnt = 0;
        }        
    }
    
    for(i=0;i<10;i++)
    {
        temp_accel_x += accel_x_buffer[i];
        temp_accel_y += accel_y_buffer[i];
        temp_accel_z += accel_z_buffer[i];
    }
    
    Accel_Raw_Average_Data.X = (float)temp_accel_x / 10.0;
    Accel_Raw_Average_Data.Y = (float)temp_accel_y / 10.0;
    Accel_Raw_Average_Data.Z = (float)temp_accel_z / 10.0;
    
    Gyro_Radian_Data.X = (float)(MPU6050_Real_Data.Gyro_X  * (3.14159265/180.0));
    Gyro_Radian_Data.Y = (float)(MPU6050_Real_Data.Gyro_Y  * (3.14159265/180.0));
    Gyro_Radian_Data.Z = (float)(MPU6050_Real_Data.Gyro_Z  * (3.14159265/180.0));
}

void MPU6050_Angle_Calculate( float gyro_x,
                              float gyro_y,
                              float gyro_z,
                              float accel_x,
                              float accel_y,
                              float accel_z)
{
    static float q0 = 1;
    static float q1 = 0;
    static float q2 = 0;
    static float q3 = 0;
    
    static float exInt = 0;
    static float eyInt = 0;
    static float ezInt = 0;
    
    const float kp = 1000.0; //
    const float ki = 0.002; //0.0;
    const float halfT = 0.0005; //�������ڵ�һ��ֵ

    float norm; //������ģ
    float vx,vy,vz;
    float ex,ey,ez;

    float ax,ay,az; //���ٶ�������ģ�ı�ֵ 
    float gx,gy,gz; //������

    static float pre_ax = 0;
    static float pre_ay = 0;
    static float pre_az = 0;
    //���ٶ��˲�
    accel_x = accel_x *0.02 + pre_ax * 0.98;//cyq:0.02
    pre_ax = accel_x;
    
    accel_y = accel_y *0.02 + pre_ay * 0.98;
    pre_ay = accel_y;

    accel_z = accel_z *0.02 + pre_az * 0.98;
    pre_az = accel_z;    
    
    norm = sqrt(accel_x * accel_x + accel_y * accel_y + accel_z * accel_z);
    ax = accel_x / norm;
    ay = accel_y / norm;
    az = accel_z / norm;
    
    vx = 2 * (q1*q3 - q0*q2);
    vy = 2 * (q0*q1 + q2*q3);
    vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;
    
    ex = (ay*vz - az*vy);
    ey = (az*vx - ax*vz);
    ez = (ax*vy - ay*vx);
    
    exInt += ki*ex;
    eyInt += ki*ey;
    ezInt += ki*ez;
    
    gx = gyro_x + kp*ex + exInt;
    gy = gyro_y + kp*ey + eyInt;
    gz = gyro_z + kp*ez + ezInt;
    
    q0 += (      - q1*gx - q2*gy - q3*gz)*halfT;
    q1 += (q0*gx +         q2*gz - q3*gy)*halfT;
    q2 += (q0*gy - q1*gz +         q3*gx)*halfT;
    q3 += (q0*gz + q1*gy - q2*gx        )*halfT;

    norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
    q0 = q0 / norm;
    q1 = q1 / norm;
    q2 = q2 / norm;
    q3 = q3 / norm;
    
    //MPU6050_Angle.Pitch = asin(-2 * q1 * q3 + 2 * q0* q2) * 57.3; 
    MPU6050_Angle.Rool= atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1) * 57.3; 
    //MPU6050_Angle.Yaw = -atan2( 2 * q1 * q2 + 2 * q0 * q3,1.0 - 2.0 * ( q2 * q2 + q3 * q2 ) ) * (180.0/3.14159265);//��׼
    //MPU6050_Angle.Yaw-=MPU6050_Real_Data.Gyro_Z/180/3.14;
}
///////////////////////////////////////////////////////////////////////////////
//float dt=0.005;//ע�⣺dt��ȡֵΪkalman�˲�������ʱ��
//float angle, angle_dot;//�ǶȺͽ��ٶ�
//float P[2][2] = {{ 1, 0 },{ 0, 1 }};
//float Pdot[4] ={ 0,0,0,0};
//float Q_angle=0.001, Q_gyro=0.005; //�Ƕ��������Ŷ�,���ٶ��������Ŷ�
//float R_angle=0.5 ,C_0 = 1;
//float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;


////�������˲�
//float Kalman_Filter(float angle_m, float gyro_m)//angleAx �� gyroGy
//{
//	angle+=(gyro_m-q_bias) * dt;
//	angle_err = angle_m - angle;
//	Pdot[0]=Q_angle - P[0][1] - P[1][0];
//	Pdot[1]=-P[1][1];
//	Pdot[2]=-P[1][1];
//	Pdot[3]=Q_gyro;
//	P[0][0] += Pdot[0] * dt;
//	P[0][1] += Pdot[1] * dt;
//	P[1][0] += Pdot[2] * dt;
//	P[1][1] += Pdot[3] * dt;
//	PCt_0 = C_0 * P[0][0];
//	PCt_1 = C_0 * P[1][0];
//	E = R_angle + C_0 * PCt_0;
//	K_0 = PCt_0 / E;
//	K_1 = PCt_1 / E;
//	t_0 = PCt_0;
//	t_1 = C_0 * P[0][1];
//	P[0][0] -= K_0 * t_0;
//	P[0][1] -= K_0 * t_1;
//	P[1][0] -= K_1 * t_0;
//	P[1][1] -= K_1 * t_1;
//	angle += K_0 * angle_err; //���ŽǶ�
//	q_bias += K_1 * angle_err;
//	angle_dot = gyro_m-q_bias;//���Ž��ٶ�


//return angle;
//}
////////////////////////////////////////////////////////////////////////////////////////////////////
///**************************ʵ�ֺ���********************************************
//*����ԭ��:	   void IMU_AHRSupdate
//*��������:	 ����AHRS ������Ԫ�� 
//��������� ��ǰ�Ĳ���ֵ��
//���������û��
//*******************************************************************************/
//volatile float exInt, eyInt, ezInt;  // ������
//volatile float q0=1.0f, q1, q2, q3; // ȫ����Ԫ��
//volatile float integralFBhand,handdiff;
//#define Kp 1.0f   // proportional gain governs rate of convergence to accelerometer/magnetometer
//#define Ki 0.1f   // integral gain governs rate of convergence of gyroscope biases

//float last_ex=0,last_ey=0,last_ez=0;
//void IMU_AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz) {
//  float norm;
//  float hx, hy, hz, bx, bz;
//  float vx, vy, vz, wx, wy, wz;
//  float ex, ey, ez,halfT;

//  // �Ȱ���Щ�õõ���ֵ���
//  float q0q0 = q0*q0;
//  float q0q1 = q0*q1;
//  float q0q2 = q0*q2;
//  float q0q3 = q0*q3;
//  float q1q1 = q1*q1;
//  float q1q2 = q1*q2;
//  float q1q3 = q1*q3;
//  float q2q2 = q2*q2;   
//  float q2q3 = q2*q3;
//  float q3q3 = q3*q3;          
//  

//  halfT = 0.001;


//  norm = sqrt(ax*ax + ay*ay + az*az);       
//  ax = ax / norm;
//  ay = ay / norm;
//  az = az / norm;

//  norm = sqrt(mx*mx + my*my + mz*mz);          
//  mx = mx / norm;
//  my = my / norm;
//  mz = mz / norm;

//  // compute reference direction of flux
//  hx = 2*mx*(0.5f - q2q2 - q3q3) + 2*my*(q1q2 - q0q3) + 2*mz*(q1q3 + q0q2);
//  hy = 2*mx*(q1q2 + q0q3) + 2*my*(0.5f - q1q1 - q3q3) + 2*mz*(q2q3 - q0q1);
//  hz = 2*mx*(q1q3 - q0q2) + 2*my*(q2q3 + q0q1) + 2*mz*(0.5f - q1q1 - q2q2);         
//  bx = sqrt((hx*hx) + (hy*hy));
//  bz = hz;     
//  
//  // estimated direction of gravity and flux (v and w)
//  vx = 2*(q1q3 - q0q2);
//  vy = 2*(q0q1 + q2q3);
//  vz = q0q0 - q1q1 - q2q2 + q3q3;
//  wx = 2*bx*(0.5 - q2q2 - q3q3) + 2*bz*(q1q3 - q0q2);
//  wy = 2*bx*(q1q2 - q0q3) + 2*bz*(q0q1 + q2q3);
//  wz = 2*bx*(q0q2 + q1q3) + 2*bz*(0.5 - q1q1 - q2q2);
//  
//  // error is sum of cross product between reference direction of fields and direction measured by sensors
//  ex = (ay*vz - az*vy) + (my*wz - mz*wy);
//  ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
//  ez = (ax*vy - ay*vx) + (mx*wy - my*wx);

//if(ex != 0.0f && ey != 0.0f && ez != 0.0f){
//  exInt = exInt + ex * Ki * halfT;
//  eyInt = eyInt + ey * Ki * halfT;	
//  ezInt = ezInt + ez * Ki * halfT;

//  // adjusted gyroscope measurements
//  gx = gx + Kp*ex + exInt;
//  gy = gy + Kp*ey + eyInt;
//  gz = gz + Kp*ez + ezInt;

//  last_ex = ex;
//  last_ey = ey;
//  last_ez = ez;
//  }

//  // integrate quaternion rate and normalise
//  q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
//  q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
//  q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
//  q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;  
//  
//  // normalise quaternion
//  norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
//  q0 = q0 / norm;
//  q1 = q1 / norm;
//  q2 = q2 / norm;
//  q3 = q3 / norm;
//   MPU6050_Angle.Rool = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * (180.0/3.14159265); 
//   MPU6050_Angle.Pitch =-asin(-2 * q1 * q3 + 2 * q0 * q2) * (180.0/3.14159265); 
//   MPU6050_Angle.Yaw = -atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2*q2 - 2 * q3 * q3 + 1)* (180.0/3.14159265);//��׼
//  
//}
