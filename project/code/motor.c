/*
 * motor.c
 *
 *  Created on: 2023��4��9��
 *      Author: 86152
 */
#include "zf_common_headfile.h"
/*����ջ����ݴ洢�ṹ��*/

/**********************************************************************************************/
/* ���֣�MOTOR_Init
 * ���ܣ������ʼ��
 * ��������
 * �������
 */
void MOTOR_Init()
{
    gpio_init (MOTOR_IO, GPO, 1, GPO_PUSH_PULL);
    pwm_init(MOTOR_PWM, MOTOR_FREQ, 0);
}

/**********************************************************************************************/
/* ���֣�MOTOR_Speed
 * ���ܣ�����ٶ�����
 * ������Speed
 * �������
 */
void MOTOR_Speed(int16 Duty)
{
    if(Duty>=0)
    {
        //����ת��
        gpio_set_level(MOTOR_IO, GPIO_LOW);                                          // DIR����ߵ�ƽ
        pwm_set_duty(MOTOR_PWM, Duty);
    }
    else
    {
        //����ת��
        gpio_set_level(MOTOR_IO, GPIO_HIGH);                                         // DIR����͵�ƽ
        pwm_set_duty(MOTOR_PWM, -Duty);
    }
}


/**********************************************************************************************/
/* ���֣�MOTOR_PID
 * ���ܣ��Ե������PID����
 * ������Speed
 * �������
 */
void MOTOR_PID()
{
    PID_Init(&MOTOR_SUM , 5 , 3 , 4 , 800 , 2300);
    PID_Calc(&MOTOR_SUM , 2000 ,encoder_data_quaddec);
    MOTOR_Speed((int16)MOTOR_SUM.output);
}
