/*
 * imu_FCOF.h
 *
 *  Created on: 2023骞�5鏈�24鏃�
 *      Author: Chaoi
 */

#ifndef IMU_FCOF_H_
#define IMU_FCOF_H_

struct FCOFI{
    float Pitch;
    float Roll;
    float Yaw;
};
void FCOF_update();

#endif /* IMU_FCOF_H_ */
