#ifndef __MAHONY_H
#define __MAHONY_H
#include "math.h"

#define IMU_Update_Freq 200.0f	   //频率（Hz）必须等于IMU_Update()的频率。

extern volatile float q0, q1, q2, q3; // 传感器框架相对于辅助框架的四元数

void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);

#endif
