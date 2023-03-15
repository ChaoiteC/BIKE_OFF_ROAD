#include "pid.h"

_ALL_PID all;

const float  controller_parameter[3][5] =
{
  /* 0.kp 1.ki 2.kd 3.�����޷� 4.pid����޷�ֵ */
  /*���Բ���*/
#if   0    /* 24V����1 */
    {7.2 , 0.0,  0,  550 , 2000 },                           //rol_angle  ���ڻ��ǶȻ���
    {0.065, 0.00001,  0.065,  500 , 2000 },                  //vel_encoder���⻷�ٶȻ���
    {24.5 ,  0.0,  0,  500 , 2000 },                         //gyro       ���ڻ����ٶȻ���
#elif 0   /* 24V����2 */
    {7.2 , 0.0,  0,  550 , 2000 },                           //rol_angle
    {0.072 , 0.00015,  0.00,  500 , 2000 },                  //vel_encoder
    {27.5 ,  0.0,  0,  500 , 2000 },                         //gyro

#elif 0   /* 20V����1 */
    {7.5 , 0.0,  0,  550 , 2000 },                           //rol_angle
    {0.075 , 0.0002,  0.00,  500 , 2000 },                   //vel_encoder
    {30.6 ,  0.0,  0,  500 , 2000 },                         //gyro
#elif 0 /* 20V����2 */
    {7.5 , 0.0,  0,  550 , 2000 },                           //rol_angle
    {0.070 , 0.0001,  0.05,  500 , 2000 },                   //vel_encoder
    {29.6 ,  0.0,  0,  500 , 2000 },                         //gyro
#elif 0 /* 20V����3 */
    {8.8 , 0.0,  0,  550 , 2000 },                           //rol_angle
    {0.068 , 0.00005,  0.055,  500 , 2000 },                 //vel_encoder
    {26.5 ,  0.0,  0,  500 , 2000 },                         //gyro         ��
#elif 1 /* 20V����4 */
    {7.5 , 0.0,  0,  550 , 2000 },                           //rol_angle
    {0.068 , 0.00005,  0.055,  500 , 2000 },                 //vel_encoder
    {26.5 ,  0.0,  0,  500 , 2000 },                         //gyro
#elif 0 /* 20V����5 */
    {8.5 , 0.0,  0,  550 , 2000 },                           //rol_angle
    {0.065 , 0.00002,  0.050,  500 , 2000 },                 //vel_encoder
    {25.5 ,  0.0,  0,  500 , 2000 },                         //gyro
#elif 0 /* 20V����6 */
    {8.9 , 0.001,  0,  550 , 2000 },                           //rol_angle
    {0.055 , 0.00002,  0.035,  500 , 2000 },                 //vel_encoder  ��
    {25.5 ,  0.0,  0,  500 , 2000 },                         //gyro

#elif 0 /* 12V���� */
    {7.2, 0.0,  0,  500 , 2000 },                           //rol_angle     ��
    {0.08, 0.0,  0.0004,  550 , 2000 },                     //vel_encoder��
    {55.5,  0.0,  0,  550 , 2000 },                         //gyro
#endif
};


/* ���֣�PID������ʼ��
 * ���ܣ�PID������ʼ������
 * �������ṹ��ָ��_PID
 * ������PID��������ֵ
 * ����ֵ����
 */
void pid_init(_PID *controller,uint8_t label)
{
    controller->kp              = controller_parameter[label][0];
    controller->ki              = controller_parameter[label][1];
    controller->kd              = controller_parameter[label][2];
    controller->integral_max    = controller_parameter[label][3];
    controller->out_max         = controller_parameter[label][4];
}

/* ���֣�����PID������ʼ��
 * ���ܣ�����PID������ʼ������
 * ��������
 * ����ֵ����
 */
void all_pid_init(void)
{
    pid_init(&all.rol_angle,0);
    pid_init(&all.vel_encoder,1);
    pid_init(&all.rol_gyro,2);
}

/* ���֣�PID������
 * ���ܣ�ͨ��PID����õ����ֵ
 * �������ṹ��ָ�� _PID
 * ����ֵ��PID���ֵ
 */
float pid_controller(_PID *controller)
{
    controller->err_last = controller->err;                                          //�����ϴ�ƫ��
    controller->err = controller->expect - controller->feedback;                     //ƫ�����
    controller->integral += controller->ki * controller->err;                        //����
    //�����޷�
    if(controller->integral >  controller->integral_max)     controller->integral =  controller->integral_max;
    if(controller->integral < -controller->integral_max)     controller->integral = -controller->integral_max;
    //pid����
    controller->out =  controller->kp*controller->err + controller->integral + controller->kd*(controller->err-controller->err_last);

    //����޷�
    if(controller->out >  controller->out_max)   controller->out =  controller->out_max;
    if(controller->out < -controller->out_max)   controller->out = -controller->out_max;
    return controller->out;
}

/* ���֣����PID�������������
 * ���ܣ����PID������������
 * �������ṹ��ָ�� _PID
 * ����ֵ����
 */
void clear_integral(_PID *controller)
{
    controller->integral = 0.0f;
}
