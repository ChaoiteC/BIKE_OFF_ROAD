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
 * 功能：电机初始化
 * 参数：无
 * 输出：无
 */
void MOTOR_Init()
{
    gpio_init (MOTOR1_IO, GPO, 1, GPO_PUSH_PULL);
    pwm_init(MOTOR1_PWM, MOTOR_FREQ, 0);

    PID_expect(&MOTOR1_SUM,0);
    PID_init(&MOTOR1_SUM,1,0,5,800,5000);

    PID_expect(&MOTOR2_SUM,0);
    PID_init(&MOTOR2_SUM,1,0,5,800,5000);

}

/**********************************************************************************************/
/* 名字：MOTOR_Speed
 * 功能：电机速度输入
 * 参数：Speed
 * 输出：无
 */
void MOTOR_Speed(int16 Duty)
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
/* 名字：MOTOR_PID
 * 功能：对电机进行PID控制
 * 参数：无
 * 输出：无
 */
void MOTOR_PID()
{
    PID_Calc(&MOTOR1_SUM ,encoder_data_quaddec);
    if(!stop_flag){
        MOTOR_Speed((int16)MOTOR1_SUM.output);
    }
    else{
        MOTOR_Speed(0);
    }
}
