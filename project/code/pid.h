#ifndef _PID_H_
#define _PID_H_

#include "stdint.h"

typedef struct PID
{
    float kp,ki,kd;//三个系数
    float error,lastError;//误差、上次误差
    float integral,maxIntegral;//积分、积分限幅
    float output,maxOutput;//输出、输出限幅
    float expect;//期望
}PID;

/*
//动量轮三环pid
  typedef struct
{
    //姿态外环
    PID rol_angle;
    //编码器速度环
    PID vel_encoder;
    PID rol_gyro;
}ALL_PID;
*/

extern  PID MOTOR1_SUM;
extern  PID MOTOR2_SUM;

void  PID_Init(PID *pid,float p,float i,float d,float maxI,float maxOut);
void  PID_Calc(PID *pid,float feedback);
void  PID_expect(PID *pid,float e);

#endif
