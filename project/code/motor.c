/*
 * motor.c
 *
 *  Created on: 2023年4月9日
 *      Author: 86152
 */
#include "zf_common_headfile.h"
/*电机闭环数据存储结构体*/

/**********************************************************************************************/
/* 名字：MOTOR_Init
 * 功能：舵机初始化
 * 参数：无
 * 输出：无
 */
void MOTOR_Init()
{
    gpio_init (MOTOR_IO, GPO, 1, GPO_PUSH_PULL);
    pwm_init(MOTOR_PWM, MOTOR_FREQ, 0);
}

/**********************************************************************************************/
/* 名字：MOTOR_Speed
 * 功能：舵机速度输入
 * 参数：Speed
 * 输出：无
 */
void MOTOR_Speed(int16 Duty)
{
    if(Duty>=0)
    {
        //正向转动
        gpio_set_level(MOTOR_IO, GPIO_LOW);                                          // DIR输出高电平
        pwm_set_duty(MOTOR_PWM, Duty);
    }
    else
    {
        //反向转动
        gpio_set_level(MOTOR_IO, GPIO_HIGH);                                         // DIR输出低电平
        pwm_set_duty(MOTOR_PWM, -Duty);
    }
}


/**********************************************************************************************/
/* 名字：MOTOR_PID
 * 功能：对电机进行PID控制
 * 参数：Speed
 * 输出：无
 */
void MOTOR_PID()
{
    PID_Init(&MOTOR_SUM , 5 , 3 , 4 , 800 , 2300);
    PID_Calc(&MOTOR_SUM , 2000 ,encoder_data_quaddec);
    MOTOR_Speed((int16)MOTOR_SUM.output);
}
