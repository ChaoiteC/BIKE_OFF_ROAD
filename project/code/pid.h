#ifndef _PID_H_
#define _PID_H_

#include "stdint.h"

typedef struct{
    float kp,ki,kd;//三个系数
    float error,lastError;//误差、上次误差
    float integral,maxIntegral;//积分、积分限幅
    float output,maxOutput;//输出、输出限幅
    float expect;//期望
}PID;

void  PID_set(PID *pid,float p,float i,float d,float maxI,float maxOut);
void  PID_calc(PID *pid,float feedback);
void  PID_expect(PID *pid,float e);

#endif
