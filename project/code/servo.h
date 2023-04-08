#ifndef _servo_H_
#define _servo_H_
#include "zf_common_headfile.h"

// **************************** 代码区域 ****************************
#define SERVO_PWM               (TIM2_PWM_MAP1_CH1_A15)                         // 定义主板上舵机对应引脚
#define SERVO_FREQ              (50 )                                           // 定义主板上舵机频率  请务必注意范围 50-300


// 79为水平值 减小和最大值不能超过92 否则会发生抖动
// 定义主板上舵机活动范围 角度 减小的值为左转最多的
#define SERVO_L_MAX             (79-50)
// 定义主板上舵机活动范围 角度 增加的值为右转最多的
#define SERVO_R_MAX             (79+50)



#define SERVO_DUTY(x)         ((float)PWM_DUTY_MAX / (1000.0 / (float)SERVO_FREQ) * (0.5 + (float)(x) / 90.0))


void Servo_Init(float servo_motor_duty);
void Servo_Leftmove(float *servo_motor_duty);
void Servo_Rightmove(float *servo_motor_duty);
void Servo_Text(float *servo_motor_duty,float *servo_motor_dir);


#endif
