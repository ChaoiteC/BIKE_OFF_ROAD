#ifndef _IMU_H_
#define _IMU_H_

#include "stdint.h"

typedef struct IMU
{
	float Pitch;
	float Roll;
	float Yaw;

	float Pitch_v;
	float Roll_v;
	float Yaw_v;

	float ax;
	float ay;
	float az;

} IMU_Info;

void ICM20602_Init_Offset(void);//ICM20602初始化去偏移
void IMU_Update(void);

extern IMU_Info imu;

#endif /* IMU_H_ */
