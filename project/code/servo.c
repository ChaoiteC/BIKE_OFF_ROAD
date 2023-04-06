/*
 * �˺��������ڶԶ���Ŀ���
 * ʱ�䣺2023/4/3
 * ����Ҫ���Ƶģ���Ҫ��ӹܿںͶ�ʱ���ĺ궨�����Ժ���ʵ��ͨ����
 */
#include "zf_common_headfile.h"



#if ((SERVO_FREQ < 50) || (SERVO_FREQ > 300))
    #error "SERVO_MOTOR_FREQ ERROE!"
#endif

/**********************************************************************************************/
/* ���֣�Servo_Init
 * ���ܣ������ʼ��
 * ��������
 * �������
 */
void Servo_Init(float servo_motor_duty)
{
    pwm_init(SERVO_PWM, SERVO_FREQ, 0);
    pwm_set_duty(SERVO_PWM, (uint32)SERVO_DUTY(servo_motor_duty));
    system_delay_ms(1000);
}

/**********************************************************************************************/
/* ���֣�Servo_Rightmove
 * ���ܣ������ת
 * ��������
 * �������
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
/* ���֣�Servo_Rightmove
 * ���ܣ������ת
 * ��������
 * �������
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
/* ���֣�Servo_Text
 * ���ܣ��������
 * ��������
 * �������
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
/* ���֣�Servo_Limit
 * ���ܣ�����޷�
 * ��������
 * �������
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
