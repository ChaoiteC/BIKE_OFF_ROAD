#ifndef  MOTOR_H_
#define  MOTOR_H_

#define  MOTOR1_IO           A0                            //有刷电机IO口 （输出方向）
#define  MOTOR1_PWM          TIM5_PWM_MAP0_CH2_A1          //有刷电机PWM （输出速度）

#define  MOTOR2_IO           (D12 )                           //无刷电机IO口
#define  MOTOR2_PWM          (TIM4_PWM_MAP1_CH2_D13)         //无刷电机PWM

#define  MAX_Speed           (50)                          //最大的速度值  （用来限幅）

#define  MOTOR_FREQ          17000                         //电机频率

void MOTOR_init();
void MOTOR1_speed_output(int16 Duty);
void MOTOR2_Speed(int16 Duty);

#endif /* MOTOR_H_ */
