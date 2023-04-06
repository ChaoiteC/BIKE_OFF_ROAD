#ifndef _servo_H_
#define _servo_H_
#include "zf_common_headfile.h"

// **************************** �������� ****************************
#define SERVO_PWM               (TIM2_PWM_MAP1_CH1_A15)                         // ���������϶����Ӧ����
#define SERVO_FREQ              (50 )                                           // ���������϶��Ƶ��  �����ע�ⷶΧ 50-300


// 79Ϊˮƽֵ ��С�����ֵ���ܳ���92 ����ᷢ������
// ���������϶�����Χ �Ƕ� ��С��ֵΪ��ת����
#define SERVO_L_MAX             (79-50)
// ���������϶�����Χ �Ƕ� ���ӵ�ֵΪ��ת����
#define SERVO_R_MAX             (79+50)



#define SERVO_DUTY(x)         ((float)PWM_DUTY_MAX / (1000.0 / (float)SERVO_FREQ) * (0.5 + (float)(x) / 90.0))


void Servo_Init(float servo_motor_duty);
void Servo_Leftmove(float *servo_motor_duty);
void Servo_Rightmove(float *servo_motor_duty);
void Servo_Text(float *servo_motor_duty,float *servo_motor_dir);


#endif
