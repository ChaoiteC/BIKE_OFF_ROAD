/*出発のベルが鳴る
  乗客は私一人だけ
  手を叩く わたしだけの音
  足鳴らす 足跡残すまで
  目を開ける 孤独の称号
  受け止める 孤高の衝動
  今 胸の奥 確かめる心音
  ほかに何も聴きたくない
  わたしが放つ音以外
  
  基于一阶互补滤波的姿态解算。*/

#include "zf_common_headfile.h"
#include <math.h>

#define Ka 0.95  //加速度数据权重
#define Kg 0.05  //陀螺仪数据权重
#define dt 0.005 //采样间隔（单位：秒）

IMU_FCOF IMU_Data;

float FCOF(float acc_m,float gyro_m,float* last_a){
    float temp_a;
    temp_a=Ka*acc_m+Kg*(*last_a+gyro_m*dt);//角速度对采样间隔积分加上上次解算角度即为从陀螺仪中推出的角度
    *last_a=temp_a;
    return temp_a;
}

/* @fn IMU_update
 * @brief 在定时器中姿态解算
 * @param void
 * @return void
 */
void IMU_update(){
    //数据处理
    IMU_Data.aAx=atan2(imu963ra_acc_x,imu963ra_acc_z)/(PI/180);//ax除以az再求反正切函数即为从加速度计中推出的角度
    IMU_Data.aAy=atan2(imu963ra_acc_y,imu963ra_acc_z)/(PI/180);
    //IMU_Data.aAz=atan2(imu963ra_acc_z,imu963ra_acc_y)/(PI/180);
    IMU_Data.gGx=-(imu963ra_gyro_x)/14.3;//从陀螺仪中推出的角速度，14.3根据陀螺仪量程所得
    IMU_Data.gGy=-(imu963ra_gyro_y)/14.3;
    //IMU_Data.gGz=-(imu963ra_gyro_z)/14.3;
    //一阶互补滤波
    IMU_Data.Rol=FCOF(IMU_Data.aAx,IMU_Data.gGy,&IMU_Data.lastRol);
    IMU_Data.Pit=FCOF(IMU_Data.aAy,IMU_Data.gGx,&IMU_Data.lastPit);
    //IMU_Data.Yaw=FCOF(IMU_Data.aAz,IMU_Data.gGx,&IMU_Data.lastYaw);//加速度计对水平方向的旋转无能为力，故Yaw角数据没有参考价值
}
