#ifndef IMU_H_
#define IMU_H_

#include "zf_common_headfile.h"

typedef struct{
    float Roll;//解算所得角度
    float Pitch;
    float Yaw;

    float Roll_a;//加速度计算得到的角度
    float Pitch_a;
    float Roll_g;//陀螺仪计算得到的角速度
    float Pitch_g;

    float lastRoll;//上次的解算角度
    float lastPitch;

    int offset_gx;//陀螺仪零漂值
    int offset_gy;
    int offset_gz;
}IMU;

extern IMU IMU_Data;

void IMU_update();
void IMU_offset();
void IMU_get_data();

#endif /* IMU_H_ */
