/*
 * imu_tanbai.c
 *
 *  Created on: 2023年4月9日
 *      Author: Chaoi
 */

#include "zf_common_headfile.h"

#include "Mahony.h"

#define Buf_SIZE  10	//队列长度，越大，平滑性越高

#define OFFSET_CONUT 100 //去偏移计数

IMU_Info imu;

int16_t  MPU6050_FIFO[6][Buf_SIZE];	//6个FIFO队列；0-2：陀螺仪数据；3-5：加速度计数据	

int16_t lastAx,lastAy,lastAz,lastGx,lastGy,lastGz;

static uint8_t Wr_Index = 0;	//当前FIFO的写入下标

static float Pitch_offset;
static float Roll_offset;
static float Yaw_offset;

//将val入队
static void MPU6050_NewVal(int16_t* buf,int16_t val) {
  	buf[Wr_Index] = val;
}

//计算FIFO中的平均值
static int16_t MPU6050_GetAvg(int16_t* buf)
{
  	int i;
	int32_t	sum = 0;
	for(i=0;i<Buf_SIZE;i++)
		sum += buf[i];
	sum = sum / Buf_SIZE;
	return (int16_t)sum;
}

//读取经过滤波的陀螺仪，加速度数据
void MPU6050_readGyro_Acc(int16_t *gyro,int16_t *acc)
{
	//static short buf[6];	//缓存原始数据：0-2：陀螺仪数据；3-5：加速度计数据
	static int16_t gx,gy,gz;
	static int16_t ax,ay,az;
	
	//将原始数据入队
	MPU6050_NewVal(&MPU6050_FIFO[0][0],mpu6050_acc_x);
	MPU6050_NewVal(&MPU6050_FIFO[1][0],mpu6050_acc_y);
	MPU6050_NewVal(&MPU6050_FIFO[2][0],mpu6050_acc_z);

	MPU6050_NewVal(&MPU6050_FIFO[3][0],mpu6050_gyro_x);
	MPU6050_NewVal(&MPU6050_FIFO[4][0],mpu6050_gyro_y);
	MPU6050_NewVal(&MPU6050_FIFO[5][0],mpu6050_gyro_z);
	
	//更新FIFO入口指针
	Wr_Index = (Wr_Index + 1) % Buf_SIZE;	

	//计算队列平均值
	gx =  MPU6050_GetAvg(&MPU6050_FIFO[4][0]);
	gy =  MPU6050_GetAvg(&MPU6050_FIFO[5][0]);
	gz =  MPU6050_GetAvg(&MPU6050_FIFO[6][0]);
	
	//陀螺仪数据要减去偏移量
	gyro[0] = gx - Roll_offset;	//gyro
	gyro[1] = gy - Pitch_offset;
	gyro[2] = gz - Yaw_offset;
		

	ax = 	MPU6050_GetAvg(&MPU6050_FIFO[0][0]);
	ay = 	MPU6050_GetAvg(&MPU6050_FIFO[1][0]);
	az = 	MPU6050_GetAvg(&MPU6050_FIFO[2][0]);
				
	acc[0] = ax; //acc
	acc[1] = ay;
	acc[2] = az;	
}

void MPU6050_Init_Offset(void)//Hello?
{
	unsigned int i;
	int16_t temp[3],temp2[3];
	int32_t	tempgx=0,tempgy=0,tempgz=0;
	int32_t tempax=0,tempay=0,tempaz=0;
	Pitch_offset = 0;
	Roll_offset = 0;
	Yaw_offset = 0;
	
	//等待MPU准备就绪
	for(i=0;i<100;i++){
  		system_delay_ms(5);
		MPU6050_readGyro_Acc(temp,temp2);
	}
	
	//计算imu数据的平均值作为偏移量
 	for(i=0;i<OFFSET_CONUT;i++){
		system_delay_ms(10);
		MPU6050_readGyro_Acc(temp,temp2);
		tempgx += temp[0];
		tempgy += temp[1];
		tempgz += temp[2];
		
		tempax += temp2[0];
		tempay += temp2[1];
		tempaz += temp2[2];
		
	}
	
	Pitch_offset = tempgy/OFFSET_CONUT;
	Roll_offset = tempgx/OFFSET_CONUT;
	Yaw_offset = tempgz/OFFSET_CONUT;
	
}

static void Get_IMU_Values(float *values)
{
	int16_t gyro[3],acc[3];
	
	MPU6050_readGyro_Acc(&gyro[0],&acc[0]);
	
	for(int i=0;i<3;i++)
	{
		values[i]=(mpu6050_gyro_transition (gyro[i]));	//这里我们改用逐飞的转换函数
		values[3+i]=(float) acc[i];
	}
	
}

//arcsin函数
float safe_asin(float v)
{
	if (isnan(v)) {
		return 0.0f;
	}
	if (v >= 1.0f) {
		return PI/2;
	}
	if (v <= -1.0f) {
		return -PI/2;
	}
	return asin(v);
}
void IMU_Update(void)
{
	static float q[4];
	float Values[6];	
	Get_IMU_Values(Values);	
	
	//将角度改为弧度，用Mahony计算imu
	MahonyAHRSupdateIMU(Values[0] * PI/180, Values[1] * PI/180, Values[2] * PI/180,Values[3], Values[4], Values[5]);		
	
	//保存四元数（Quaternion）。
	q[0] = q0;
	q[1] = q1;
	q[2] = q2;
	q[3] = q3;
	
	imu.ax = Values[3];
	imu.ay = Values[4];
	imu.az = Values[5];

	imu.Pitch_v = Values[0];
	imu.Roll_v = Values[1];
	imu.Yaw_v = Values[2];

	//用四元数计算imu的角度
	imu.Roll = (atan2(2.0f*(q[0]*q[1] + q[2]*q[3]),1 - 2.0f*(q[1]*q[1] + q[2]*q[2])))* 180/PI;	
	imu.Pitch = -safe_asin(2.0f*(q[0]*q[2] - q[1]*q[3]))* 180/PI;
	imu.Yaw = -atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2*q2 - 2 * q3 * q3 + 1)* 180/PI; // yaw
}

