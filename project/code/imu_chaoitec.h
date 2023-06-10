#ifndef IMU_CHAOITEC_H_
#define IMU_CHAOITEC_H_

#include "zf_common_headfile.h"

typedef struct IMU_JS{
	float Rol;//解算所得角度
	float Pit;
	//float Yaw;

    float aAx;//加速度计算得到的角度
    float aAy;
    float aAz;
    float gGx;//陀螺仪计算得到的角速度
    float gGy;
    float gGz;

    float lastRol;//上次的解算角度
    float lastPit;
    float lastYaw;

}IMU_JS;

extern IMU_JS IMU_Data;

void IMU_update();

#endif /* IMU_CHAOITEC_H_ */
