#include "zf_common_headfile.h"

#define MOTOR1_GAIN_FACTOR 1 //动量轮输出经验增益系数

PID balance_acc;//角速度环
PID balance_ang;//角度环
PID balance_vel;//速度环

//上面这两个环的缺省值在bike_init.c中调整

int b_tick=0;//心跳计数
float cenBalComp=0;//离心抗衡补偿

//平衡初始化
void balance_init(){
    encoder_init();//编码器初始化，打开中断
    MOTOR_init();//电机初始化
}

//心跳平衡
void balance_heartbeat(){
    b_tick++;
    if(b_tick==25){
        PID_calc(&balance_vel,encoder_data_quaddec);
        b_tick=0;
    }
    if(b_tick%5==0){
        PID_calc(&balance_ang,balance_vel.output+IMU_Data.Rol+cenBalComp);
    }
    PID_calc(&balance_acc,balance_ang.output+imu963ra_acc_x);
    MOTOR1_speed_output((int16)(balance_acc.output*MOTOR1_GAIN_FACTOR));
}
