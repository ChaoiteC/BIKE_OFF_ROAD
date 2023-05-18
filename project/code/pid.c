#include "zf_common_headfile.h"

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

_PID motor;

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
/********************************************************************************************************/


PID MOTOR1_SUM;


/**********************************************************************************************/
/* 名字：PID_Init
 * 功能：用于初始化pid参数的函数
 * 参数：无
 * 输出：无
 */
void PID_Init(PID *pid,float p,float i,float d,float maxI,float maxOut)
{

    pid->kp=p;
    pid->ki=i;
    pid->kd=d;
    pid->maxIntegral=maxI;
    pid->maxOutput=maxOut;
}

/**********************************************************************************************/
/* 名字：PID_expect
 * 功能：设置PID期望
 * 参数：无
 * 输出：无
 */
void PID_expect(PID *pid,float e)
{
    pid->expect=e;
}

/**********************************************************************************************/
/* 名字：PID_Calc
 * 功能：进行一次pid计算
 * 参数：(pid结构体,反馈值)，计算结果放在pid结构体的output成员中
 * 输出：无
 */
void PID_Calc(PID *pid,float feedback)
{
    //更新数据
    pid->lastError=pid->error;//将旧error存起来
    pid->error=pid->expect-feedback;//计算新error
    //计算微分
    float dout=(pid->error-pid->lastError)*pid->kd;
    //计算比例
    float pout=pid->error*pid->kp;
    //计算积分
    pid->integral+=pid->error*pid->ki;
    //积分限幅
    if(pid->integral > pid->maxIntegral)
        pid->integral=pid->maxIntegral;
    else if(pid->integral < -pid->maxIntegral)
        pid->integral=-pid->maxIntegral;
    //计算输出
    pid->output=pout+dout+pid->integral;
    //输出限幅
    if(pid->output > pid->maxOutput)
        pid->output=pid->maxOutput;
    else if(pid->output < -pid->maxOutput)
        pid->output=-pid->maxOutput;
}
/* @fn PID_Vanquisher
 * @brief 强大、健壮的“PID征服者”堂堂登场！你掌控PID参数的最有力工具！
 * @param void
 * @return void
 */
void PID_Vanquisher(){
    oled_clear();
    oled_show_string(0,0,"PID!*Vanquisher*!"       );
    oled_show_string(0,1,"Power by ChaoiteC"       );
    oled_show_string(0,4,"[UP]MOTOR 1"             );
    oled_show_string(0,5,"[DN]MOTOR 2"             );
    oled_show_string(0,7,"[RT]RE-TURN"             );
    PID* PID_E;
    uint8 sector,page;
    while(1){
        if(KEY_SHORT_PRESS==key_get_state(KEY_UP)){
            PID_E=&MOTOR1_SUM;
            //从FLASH读出PID参数
            sector=63;
            page=3;
            break;
        }
        else if(KEY_SHORT_PRESS==key_get_state(KEY_DOWN)){
            //PID_E=&MOTOR2_SUM;
            sector=63;
            page=2;
            //break;
        }
        else if(KEY_SHORT_PRESS==key_get_state(KEY_RT)){
            return;
        }
    }
    flash_read_page_to_buffer(sector,page);
    PID_E->kp=flash_union_buffer[0].float_type;
    PID_E->ki=flash_union_buffer[1].float_type;
    PID_E->kd=flash_union_buffer[2].float_type;
    PID_E->maxIntegral=flash_union_buffer[3].float_type;
    PID_E->maxOutput=flash_union_buffer[4].float_type;
    oled_clear();

    
}
