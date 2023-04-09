#ifndef __MAHONY_H
#define __MAHONY_H
#include "math.h"

#define IMU_Update_Freq 500.0f	   //frequency in Hz must equal to the frequency of IMU_Update() 

extern volatile float q0, q1, q2, q3; // quaternion of sensor frame relative to auxiliary frame

void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);

#endif
