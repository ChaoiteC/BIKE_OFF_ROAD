#ifndef _PID_H_
#define _PID_H_

#include "stdint.h"


//PID����
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
    //��̬�⻷���ǶȻ���
    _PID rol_angle;
    //�������ٶȻ�
    _PID vel_encoder;//������PID���ٶȻ���
    _PID rol_gyro;//������PID�����ٶȻ���
}_ALL_PID;

extern _ALL_PID all;


float pid_controller(_PID *controller);
void all_pid_init(void);
void clear_integral(_PID *controller);

#endif
