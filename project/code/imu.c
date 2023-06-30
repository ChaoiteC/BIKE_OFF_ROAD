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

#define Ka 0.95  //加速度解算权重
#define Kg 0.05  //陀螺仪解算权重
#define dt 0.005 //采样间隔（单位：秒）

#define ANGLE_APPROX_COEFF 0 //航向角逼近系数

#define OFFSET_COUNT 200 //零漂测定数据量

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
    IMU_Data.gGx=-(imu963ra_gyro_x)/14.3;//从陀螺仪中推出的角速度，14.3根据陀螺仪量程所得
    IMU_Data.gGy=-(imu963ra_gyro_y)/14.3;
    
    //一阶互补滤波
    IMU_Data.Rol=FCOF(IMU_Data.aAx,IMU_Data.gGy,&IMU_Data.lastRol);
    IMU_Data.Pit=FCOF(IMU_Data.aAy,IMU_Data.gGx,&IMU_Data.lastPit);

    IMU_Data.Yaw+=-(imu963ra_gyro_z)/14.3*dt;
    //Yaw角修正
    if(IMU_Data.Yaw<gps_tau1201.direction){
        IMU_Data.Yaw+=ANGLE_APPROX_COEFF;
    }
    else if(IMU_Data.Yaw>gps_tau1201.direction){
        IMU_Data.Yaw-=ANGLE_APPROX_COEFF;
    }
}

//陀螺仪去零漂
void IMU_offset(){
    oled_clear();
    oled_show_chinese(0,0,16,(const uint8 *)IMU_OFFSET_1,5);
    oled_show_chinese(0,6,16,(const uint8 *)IMU_OFFSET_2,8);
    oled_show_string(0,3,"Count:   /200");
    for(int i=0;i<OFFSET_COUNT;i++){
        oled_show_int(64,3,i,3);
        system_delay_ms(5);
        if(imu963ra_gyro_x==imu963ra_gyro_y){
            i--;
            oled_show_string(0,4,"WARNING: IMU NO DATA");
        }
        else{
            IMU_Data.oGx+=imu963ra_gyro_x;
            IMU_Data.oGy+=imu963ra_gyro_y;
            IMU_Data.oGz+=imu963ra_gyro_z;
        }
    }
    IMU_Data.oGx/=OFFSET_COUNT;
    IMU_Data.oGy/=OFFSET_COUNT;
    IMU_Data.oGz/=OFFSET_COUNT;
}

void IMU_get_data(){
    imu963ra_get_acc();                                                         // 获取 IMU963RA 的加速度测量数值
    imu963ra_get_gyro();                                                        // 获取 IMU963RA 的角速度测量数值
    imu963ra_gyro_x-=IMU_Data.oGx;
    imu963ra_gyro_y-=IMU_Data.oGy;
    imu963ra_gyro_z-=IMU_Data.oGz;
}
