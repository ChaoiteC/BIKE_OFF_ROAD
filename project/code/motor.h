/*
 * motor.h
 *
 *  Created on: 2023��4��9��
 *      Author: 86152
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define  MOTOR_IO           A0                            //��ˢ���IO�� ���������
#define  MOTOR_PWM          TIM5_PWM_MAP0_CH2_A1          //��ˢ���PWM ������ٶȣ�

#define  MAX_Speed          (50)                          //�����ٶ�ֵ  �������޷���

#define  MOTOR_FREQ         17000                         //���Ƶ��


void MOTOR_Init();
void MOTOR_Speed(int16 Duty);
void MOTOR_PID();



#endif /* MOTOR_H_ */
