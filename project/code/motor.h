/*
 * motor.h
 *
 *  Created on: 2023年4月9日
 *      Author: 86152
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define  MOTOR1_IO           A0                            //有刷电机IO口 （输出方向）
#define  MOTOR1_PWM          TIM5_PWM_MAP0_CH2_A1          //有刷电机PWM （输出速度）

#define  MAX_Speed          (50)                          //最大的速度值  （用来限幅）

#define  MOTOR_FREQ         17000                         //电机频率


void MOTOR_Init();
void MOTOR_Speed(int16 Duty);
void MOTOR_PID();



#endif /* MOTOR_H_ */
