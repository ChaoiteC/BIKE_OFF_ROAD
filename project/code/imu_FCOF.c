/*这个文件及它的头文件是惯性导航系统姿态解算的一阶互补滤波版本。*/

#include "zf_common_headfile.h"

FCOF FCOF_info;

float acc_ratio = 0.98;      //加速度计比例
float gyro_ratio = 0.02;    //陀螺仪比例
float dt = 0.005;           //采样周期

//----------------------------------------------------------------
//  @brief      一阶互补滤波
//  @param      angle_m     加速度计数据
//  @param      gyro_m      陀螺仪数据
//  @return     float       数据融合后的角度
//----------------------------------------------------------------
float angle_calc(float angle_m, float gyro_m){
    float temp_angle;
    float gyro_now;
    float error_angle;
    static float last_angle;
    static uint8 first_angle;
    if(!first_angle){//判断是否为第一次运行本函数
        //如果是第一次运行，则将上次角度值设置为与加速度值一致
        first_angle = 1;
        last_angle = angle_m;
    }
    gyro_now = gyro_m * gyro_ratio;
    //根据测量到的加速度值转换为角度之后与上次的角度值求偏差
    error_angle = (angle_m - last_angle)*acc_ratio;
    //根据偏差与陀螺仪测量得到的角度值计算当前角度值
    temp_angle = last_angle + (error_angle + gyro_now)*dt;
    //保存当前角度值
    last_angle = temp_angle;
    return temp_angle;
}

void FCOF_update(void){
    FCOF_info.Pitch=angle_calc(imu963ra_acc_y, imu963ra_gyro_y);
    FCOF_info.Roll=angle_calc(imu963ra_acc_x, imu963ra_gyro_x);
    FCOF_info.Yaw=angle_calc(imu963ra_acc_z, imu963ra_gyro_z);
}
