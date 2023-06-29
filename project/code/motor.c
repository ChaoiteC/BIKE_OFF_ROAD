/*这个文件及它的头文件用于完成与电机相关的各个功能。*/

#include "zf_common_headfile.h"

/* 名字：MOTOR_init
 * 功能：各电机初始化
 * 参数：无
 * 输出：无
 */
void MOTOR_init(){
    gpio_init (MOTOR1_IO, GPO, 1, GPO_PUSH_PULL);
    pwm_init(MOTOR1_PWM, MOTOR_FREQ, 0);
    gpio_init (MOTOR2_IO, GPO, 1, GPO_PUSH_PULL);
    pwm_init(MOTOR2_PWM, MOTOR_FREQ, 0);
}


/* 名字：MOTOR1_speed_output
 * 功能：动量轮电机速度输出
 * 参数：duty
 * 输出：无
 */
void MOTOR1_speed_output(int16 duty){
    if(duty>9000){
        duty=9000;
    }
    else if(duty<-9000){
        duty=-9000;
    }
    if(duty>=0){
        //正向转动
        gpio_set_level(MOTOR1_IO, GPIO_HIGH);                                          // DIR输出高电平
        pwm_set_duty(MOTOR1_PWM, duty);
    }
    else{
        //反向转动
        gpio_set_level(MOTOR1_IO, GPIO_LOW);                                         // DIR输出低电平
        pwm_set_duty(MOTOR1_PWM, -duty);
    }
}



/**********************************************************************************************/
/* 名字：MOTOR2_Speed
 * 功能：电机速度输入
 * 参数：Duty
 * 输出：无
 */
void MOTOR2_Speed(int16 duty)
{
    if(duty>=0)
    {
        //正向转动
        gpio_set_level(MOTOR2_IO, GPIO_HIGH);                                          // DIR输出高电平
        pwm_set_duty(MOTOR2_PWM, duty);
    }
    else
    {
        //反向转动
        gpio_set_level(MOTOR2_IO, GPIO_LOW);                                         // DIR输出低电平
        pwm_set_duty(MOTOR2_PWM, -duty);
    }
}
