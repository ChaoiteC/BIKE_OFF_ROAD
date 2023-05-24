#include "zf_common_headfile.h"

/*_OUT_Motor Motor1 = {0};//前电机
_OUT_Motor Motor2 = {0};//后电机*/

/**********************************************************************************************/
/* 名字：外环速度控制器
 * 功能：PID计算速度环
 * 参数：无
 * 输出：无
 */
/*static void vel_controller(void)
{
  PID_expect(&MOTOR2_SUM.vel_encoder,0.0f);
  PID_calc(&MOTOR2_SUM.vel_encoder,encoder_data_quaddec);
}*/

/**********************************************************************************************/
/* 名字：内环角度控制器
 * 功能：PID计算角度环
 * 参数：无
 * 输出：无
 */
/*static void angle_controller(void)
{
  PID_expect(&MOTOR2_SUM.rol_angle,MOTOR2_SUM.rol_angle.output);
  PID_calc(&MOTOR2_SUM.rol_angle,imu.Roll);
}*/

/**********************************************************************************************/
/* 名字：内环角速度控制器
 * 功能：PID计算角速度环
 * 参数：无
 * 输出：无
 */
/*static void gyro_controller(void)
{
  PID_expect(&MOTOR2_SUM.rol_gyro,MOTOR2_SUM.rol_angle.output);
  PID_calc(&MOTOR2_SUM.rol_gyro,imu.Roll);

  all.rol_gyro.expect = all.rol_angle.out;
  all.rol_gyro.feedback = -(Mpu.deg_s.y);
  pid_controller(&all.rol_gyro);
}*/

/**********************************************************************************************/
/* 名字：三环串级PID控制器运行
 * 功能：PID运算
 * 参数：无
 * 输出：无
 */
/*void _controller_perform(void)
{
  vel_controller();
  angle_controller();
  gyro_controller();
}*/
/**********************************************************************************************/
/* 名字：检测小车状态函数
 * 功能：检测小车是否倒下
 * 参数：动量轮输入的角度的值inAngleData
 * 输出：无
 */
/*static uint8_t detectionFallDown(float inAngleData)
{
  uint8_t detectionMark = 0;

  if( f_abs(inAngleData) > 20.0f )
  {
    detectionMark = 1;
  }
  return detectionMark;
}*/

/**********************************************************************************************/
/* 名字：pwmMotorOut
 * 功能：PWM输出
 * 参数：
 * 输出：无
 */
/*static void pwmMotorOut(uint32 pwm1 , uint32 pwm2 )
{
    u32RangeLimit(pwm1,0,2000);                              //限制pwm1的占空比在0-2000之间
    u32RangeLimit(pwm2,0,2000);                              //同上
    pwm_set_duty(TIM3_PWM_MAP0_CH1_A6, pwm1);           //开启TIM3的1，2通道输入占空比的值pwm
    pwm_set_duty(TIM3_PWM_MAP0_CH2_A7, pwm2);
}*/

/**********************************************************************************************/
/* 名字：_controller_output
 * 功能：控制器输出
 * 参数：无
 * 输出：无
 */

/*
static uint32 N20_motor_speed;
void _controller_output(void)
{
  static uint8_t FalldownAndRestart = 0;

  // 检测是否倒下,如果倒下就将电机关闭，清除PID算法数据
  if( detectionFallDown(att.rol)==1 )
  {
    N20_motor_speed = 2000;
    FalldownAndRestart = 1;
    DisableAuxMotor();                       //关闭电机
    Motor1.out = 0;                          //清除数据
    Motor2.out = 0;
    clear_integral(&all.vel_encoder);
    clear_integral(&all.rol_angle);
    clear_integral(&all.rol_gyro);
  }
  else if( (acc_raw.z >= 2500 && acc_raw.z <= 5000) && f_abs(att.rol) <= 20.0f && FalldownAndRestart == 0)
  {
    N20_motor_speed = 1;
    EnableAuxMotor();
    Motor1.out =  all.rol_gyro.out;
  }

  if(Motor1.out>0)  dirAnticlockwise();      //这里的函数用来控制小车的前行或者后退
  else  dirClockwise();

  //这里需要输入参数来控制小车的运动，用GPS的参数来控制小车的行进
  TurnLeftOrRight(BluetoothParseMsg.Xrocker);
  goForwardOrBackward(BluetoothParseMsg.Yrocker);

  pwmMotorOut( int_abs(Motor1.out) , N20_motor_speed);
}
*/


//下面要用控制函数（控制电机）来对上面 _controller_output（void）函数经行算法操作。如下是具体的算法操作

/**********************************************************************************************/
/* 名字：TurnLeftOrRight
 * 功能：控制小车左右
 * 参数：inXrocker               //控制指令
 * 输出：无
 */
/*
void TurnLeftOrRight(float inXrocker)
{
  static float LastXrocker = 0;
  if(inXrocker != LastXrocker)
        
  {
    if( inXrocker == 0  )
    {
    //这里的函数还没有替换
    // __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, (dirBASE + DIR_SIZE ) + dirADJUST );// 左转一定角度
    }
    else if( inXrocker == 5 )
    {
    // __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, (dirBASE - DIR_SIZE ) + dirADJUST );// 右转一定角度
    }              
    else if( inXrocker == 2 )
    {
    // __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, dirBASE + dirADJUST );//1.5ms 前方向
    }    
    LastXrocker = inXrocker;
  }
}
 */

/**********************************************************************************************/
/* 名字：goForwardOrBackward
 * 功能：控制小车前后
 * 参数：inYrcoker               //控制指令
 * 输出：无
 */
/*
void goForwardOrBackward(float inYrcoker)
{
  if( inYrcoker >= 0 && inYrcoker <= 1 )                    
  {
    EnableAuxMotor();                                       //使能前后动力电机
    CarBackward();                                          //后退
  }
  else if( inYrcoker >= 4 && inYrcoker <= 5 )
  {
    EnableAuxMotor();                                       //使能前后动力电机
    CargoForward();                                         //前进
  }
  else 
  {
    N20_motor_speed = 2000;                                 //N20电机速度设置为最低
    DisableAuxMotor();                                      //失能关闭前后动力电机
  }
}
*/


/*
void CargoForward(void)             //小车的前进
{
    void gpio_set_level(gpio_pin_enum pin,0);       //将驱动的pin口接入，输出相应的电平
    void gpio_set_level(gpio_pin_enum pin,1);
}
*/

/*
void CarBackward(void)              //小车的后退
{
    void gpio_set_level(gpio_pin_enum pin,1);      //同上
    void gpio_set_level(gpio_pin_enum pin,0);
}
*/

/*
void EnableAuxMotor(void)           //使能电机
{
    void gpio_set_level(gpio_pin_enum pin,0);
}
*/

/*
void DisableAuxMotor(void)          //失能电机
{
    void gpio_set_level(gpio_pin_enum pin,0);
}
*/


