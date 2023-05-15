#ifndef _PID_H_
#define _PID_H_

#include "stdint.h"


//PID参数
typedef struct
{
    float err;
    float err_last;
    float expect;
    float feedback;
    float kp;
    float ki;
    float kd;
    float integral;
    float integral_max;
    float out;
    float out_max;
}_PID;

typedef struct
{
    //姿态外环（角度环）
    _PID rol_angle;
    //编码器速度环
    _PID vel_encoder;//编码器PID（速度环）
    _PID rol_gyro;//陀螺仪PID（角速度环）
}_ALL_PID;

typedef struct
{
    float kp,ki,kd;//三个系数
    float error,lastError;//误差、上次误差
    float integral,maxIntegral;//积分、积分限幅
    float output,maxOutput;//输出、输出限幅
    float expect;//期望
}PID;

extern _ALL_PID all;
extern _PID motor;
extern  PID MOTOR_SUM;



float pid_controller(_PID *controller);
void  all_pid_init(void);
void  clear_integral(_PID *controller);
void  PID_Init(PID *pid,float p,float i,float d,float maxI,float maxOut);
void  PID_Calc(PID *pid,float feedback);
void  PID_expect(PID *pid,float e);

#endif
