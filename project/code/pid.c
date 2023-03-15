#include "pid.h"

_ALL_PID all;

const float  controller_parameter[3][5] =
{
  /* 0.kp 1.ki 2.kd 3.积分限幅 4.pid输出限幅值 */
  /*调试参数*/
#if   0    /* 24V参数1 */
    {7.2 , 0.0,  0,  550 , 2000 },                           //rol_angle  （内环角度环）
    {0.065, 0.00001,  0.065,  500 , 2000 },                  //vel_encoder（外环速度环）
    {24.5 ,  0.0,  0,  500 , 2000 },                         //gyro       （内环角速度环）
#elif 0   /* 24V参数2 */
    {7.2 , 0.0,  0,  550 , 2000 },                           //rol_angle
    {0.072 , 0.00015,  0.00,  500 , 2000 },                  //vel_encoder
    {27.5 ,  0.0,  0,  500 , 2000 },                         //gyro

#elif 0   /* 20V参数1 */
    {7.5 , 0.0,  0,  550 , 2000 },                           //rol_angle
    {0.075 , 0.0002,  0.00,  500 , 2000 },                   //vel_encoder
    {30.6 ,  0.0,  0,  500 , 2000 },                         //gyro
#elif 0 /* 20V参数2 */
    {7.5 , 0.0,  0,  550 , 2000 },                           //rol_angle
    {0.070 , 0.0001,  0.05,  500 , 2000 },                   //vel_encoder
    {29.6 ,  0.0,  0,  500 , 2000 },                         //gyro
#elif 0 /* 20V参数3 */
    {8.8 , 0.0,  0,  550 , 2000 },                           //rol_angle
    {0.068 , 0.00005,  0.055,  500 , 2000 },                 //vel_encoder
    {26.5 ,  0.0,  0,  500 , 2000 },                         //gyro         ·
#elif 1 /* 20V参数4 */
    {7.5 , 0.0,  0,  550 , 2000 },                           //rol_angle
    {0.068 , 0.00005,  0.055,  500 , 2000 },                 //vel_encoder
    {26.5 ,  0.0,  0,  500 , 2000 },                         //gyro
#elif 0 /* 20V参数5 */
    {8.5 , 0.0,  0,  550 , 2000 },                           //rol_angle
    {0.065 , 0.00002,  0.050,  500 , 2000 },                 //vel_encoder
    {25.5 ,  0.0,  0,  500 , 2000 },                         //gyro
#elif 0 /* 20V参数6 */
    {8.9 , 0.001,  0,  550 , 2000 },                           //rol_angle
    {0.055 , 0.00002,  0.035,  500 , 2000 },                 //vel_encoder  ·
    {25.5 ,  0.0,  0,  500 , 2000 },                         //gyro

#elif 0 /* 12V参数 */
    {7.2, 0.0,  0,  500 , 2000 },                           //rol_angle     ·
    {0.08, 0.0,  0.0004,  550 , 2000 },                     //vel_encoder·
    {55.5,  0.0,  0,  550 , 2000 },                         //gyro
#endif
};


/* 名字：PID参数初始化
 * 功能：PID参数初始化配置
 * 参数：结构体指针_PID
 * 参数：PID各个参数值
 * 返回值：无
 */
void pid_init(_PID *controller,uint8_t label)
{
    controller->kp              = controller_parameter[label][0];
    controller->ki              = controller_parameter[label][1];
    controller->kd              = controller_parameter[label][2];
    controller->integral_max    = controller_parameter[label][3];
    controller->out_max         = controller_parameter[label][4];
}

/* 名字：各环PID参数初始化
 * 功能：各环PID参数初始化配置
 * 参数：无
 * 返回值：无
 */
void all_pid_init(void)
{
    pid_init(&all.rol_angle,0);
    pid_init(&all.vel_encoder,1);
    pid_init(&all.rol_gyro,2);
}

/* 名字：PID控制器
 * 功能：通过PID计算得到输出值
 * 参数：结构体指针 _PID
 * 返回值：PID输出值
 */
float pid_controller(_PID *controller)
{
    controller->err_last = controller->err;                                          //保留上次偏差
    controller->err = controller->expect - controller->feedback;                     //偏差计算
    controller->integral += controller->ki * controller->err;                        //积分
    //积分限幅
    if(controller->integral >  controller->integral_max)     controller->integral =  controller->integral_max;
    if(controller->integral < -controller->integral_max)     controller->integral = -controller->integral_max;
    //pid运算
    controller->out =  controller->kp*controller->err + controller->integral + controller->kd*(controller->err-controller->err_last);

    //输出限幅
    if(controller->out >  controller->out_max)   controller->out =  controller->out_max;
    if(controller->out < -controller->out_max)   controller->out = -controller->out_max;
    return controller->out;
}

/* 名字：清除PID控制器项积分项
 * 功能：清除PID控制器积分项
 * 参数：结构体指针 _PID
 * 返回值：无
 */
void clear_integral(_PID *controller)
{
    controller->integral = 0.0f;
}
