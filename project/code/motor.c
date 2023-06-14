/*
 * motor.c
 *
 *  Created on: 2023年4月9日
 *      Author: 86152
 */
#include "zf_common_headfile.h"
/*电机闭环数据存储结构体*/

float Motor1_expect;

/**********************************************************************************************/
/* 名字：MOTOR_Init
 * 功能：电机初始化
 * 参数：无
 * 输出：无
 */
void MOTOR_Init()
{
    gpio_init (MOTOR1_IO, GPO, 1, GPO_PUSH_PULL);
    pwm_init(MOTOR1_PWM, MOTOR_FREQ, 0);

    gpio_init (MOTOR2_IO, GPO, 1, GPO_PUSH_PULL);
    pwm_init(MOTOR2_PWM, MOTOR_FREQ, 0);

    PID_expect(&MOTOR1_SUM,5000);
    PID_init(&MOTOR1_SUM,1,0,5,800,5000);
}

/**********************************************************************************************/
/* 名字：MOTOR1_Speed
 * 功能：电机速度输入
 * 参数：Duty
 * 输出：无
 */
void MOTOR1_Speed(int16 Duty)
{

    if(Duty>=0)
    {
        //正向转动
        gpio_set_level(MOTOR1_IO, GPIO_HIGH);                                          // DIR输出高电平
        pwm_set_duty(MOTOR1_PWM, Duty);
    }
    else
    {
        //反向转动
        gpio_set_level(MOTOR1_IO, GPIO_LOW);                                         // DIR输出低电平
        pwm_set_duty(MOTOR1_PWM, -Duty);
    }
}

/**********************************************************************************************/
/* 名字：MOTOR1_PID
 * 功能：对电机进行位置式PID控制
 * 参数：无
 * 输出：无
 */
void MOTOR1_PID()
{
    PID_Calc(&MOTOR1_SUM ,encoder_data_quaddec);
    if(!stop_flag){
        MOTOR1_Speed((int16)MOTOR1_SUM.output);
    }
    else{
        MOTOR1_Speed(0);
    }
}

/**********************************************************************************************/
/* 名字：MOTOR2_Speed
 * 功能：电机速度输入
 * 参数：Duty
 * 输出：无
 */
void MOTOR2_Speed(int16 Duty)
{
    if(Duty>=0)
    {
        //正向转动
        gpio_set_level(MOTOR2_IO, GPIO_HIGH);                                          // DIR输出高电平
        pwm_set_duty(MOTOR2_PWM, Duty);
    }
    else
    {
        //反向转动
        gpio_set_level(MOTOR2_IO, GPIO_LOW);                                         // DIR输出低电平
        pwm_set_duty(MOTOR2_PWM, -Duty);
    }
}
