/*
 * 此函数库用于对舵机的控制
 * 时间：2023/4/3
 * 还需要完善的：需要添加管口和定时器的宏定义来对函数实现通用性
 */
#include "zf_common_headfile.h"



#if ((SERVO_FREQ < 50) || (SERVO_FREQ > 300))
    #error "SERVO_MOTOR_FREQ ERROE!"
#endif

float servo_motor_duty;                                                // 舵机动作初始状态角度
//1为右转，0为左转
float servo_motor_dir = 1;                                                   // 舵机动作状态

/**********************************************************************************************/
/* 名字：Servo_Init
 * 功能：舵机初始化
 * 参数：无
 * 输出：无
 */
void Servo_Init(float servo_motor_duty)
{
    pwm_init(SERVO_PWM, SERVO_FREQ, 0);
    pwm_set_duty(SERVO_PWM, (uint32)SERVO_DUTY(servo_motor_duty));
    system_delay_ms(1000);
}

/**********************************************************************************************/
/* 名字：Servo_Rightmove
 * 功能：舵机左转
 * 参数：无
 * 输出：无
 */
void Servo_Leftmove(float *servo_motor_duty)
{
    float duty;
    duty=*servo_motor_duty;
    duty--;
    *servo_motor_duty=duty;
    pwm_set_duty(SERVO_PWM, (uint32)SERVO_DUTY(*servo_motor_duty));
}

/**********************************************************************************************/
/* 名字：Servo_Rightmove
 * 功能：舵机右转
 * 参数：无
 * 输出：无
 */
void Servo_Rightmove(float *servo_motor_duty)
{
    float duty;
    duty=*servo_motor_duty;
    duty++;
    *servo_motor_duty=duty;
    pwm_set_duty(SERVO_PWM, (uint32)SERVO_DUTY(*servo_motor_duty));
}

/**********************************************************************************************/
/* 名字：Servo_Text
 * 功能：舵机测试
 * 参数：无
 * 输出：无
 */
void Servo_Text(float *servo_motor_duty,float *servo_motor_dir)
{

     float duty;

       pwm_set_duty(SERVO_PWM, (uint32)SERVO_DUTY(*servo_motor_duty));
       if(*servo_motor_dir)
       {
           duty=*servo_motor_duty;
           duty++;
           *servo_motor_duty=duty;
                if(*servo_motor_duty >= SERVO_R_MAX)
                {

                    *servo_motor_dir = 0x00;
                }
       }
       else
       {
           duty=*servo_motor_duty;
           duty--;
           *servo_motor_duty=duty;
           if(*servo_motor_duty <= SERVO_L_MAX)
           {
               *servo_motor_dir = 0x01;
           }
       }
       system_delay_ms(5);
}

/**********************************************************************************************/
/* 名字：Servo_Limit
 * 功能：舵机限幅
 * 参数：无
 * 输出：无
 */
void Servo_Limit(float *servo_motor_duty,float *servo_motor_dir)
{
    if(*servo_motor_duty >= SERVO_R_MAX)
    {
        *servo_motor_dir = 0x00;
    }
    if(*servo_motor_duty <= SERVO_L_MAX)
    {
        *servo_motor_dir = 0x01;
    }
}
