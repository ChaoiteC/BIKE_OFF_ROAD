#include "zf_common_headfile.h"

_OUT_Motor Motor1 = {0};//前电机
_OUT_Motor Motor2 = {0};//后电机

/**********************************************************************************************/
/* 名字：外环速度控制器
 * 功能：PID计算速度环
 * 参数：无
 * 输出：无
 */
static void vel_controller(void)
{
  all.vel_encoder.expect = 0.0f;
  all.vel_encoder.feedback = encoderINFO.mainNumberValue;
  pid_controller(&all.vel_encoder);
}

/**********************************************************************************************/
/* 名字：内环角度控制器
 * 功能：PID计算角度环
 * 参数：无
 * 输出：无
 */
static void angle_controller(void)
{
  all.rol_angle.expect = all.vel_encoder.out;
  all.rol_angle.feedback = (-att.rol)+(0);
  pid_controller(&all.rol_angle);
}

/**********************************************************************************************/
/* 名字：内环角速度控制器
 * 功能：PID计算角速度环
 * 参数：无
 * 输出：无
 */
static void gyro_controller(void)
{
  all.rol_gyro.expect = all.rol_angle.out;
  all.rol_gyro.feedback = -(Mpu.deg_s.y);
  pid_controller(&all.rol_gyro);
}

/**********************************************************************************************/
/* 名字：三环串级PID控制器运行
 * 功能：PID运算
 * 参数：无
 * 输出：无
 */
void _controller_perform(void)
{
  vel_controller();
  angle_controller();
  gyro_controller();
}
/**********************************************************************************************/
/* 名字：检测小车状态函数
 * 功能：检测小车是否倒下
 * 参数：动量轮输入的角度的值inAngleData
 * 输出：无
 */
static uint8_t detectionFallDown(float inAngleData)
{
  uint8_t detectionMark = 0;

  if( f_abs(inAngleData) > 20.0f )
  {
    detectionMark = 1;
  }
  return detectionMark;
}

/**********************************************************************************************/
/* 名字：pwmMotorOut
 * 功能：PWM输出
 * 参数：
 * 输出：无
 */
static void pwmMotorOut(uint32 pwm1 , uint32 pwm2 )
{
    u32RangeLimit(pwm1,0,2000);                              //限制pwm1的占空比在0-2000之间
    u32RangeLimit(pwm2,0,2000);                              //同上
    pwm_set_duty(TIM3_PWM_MAP0_CH1_A6, pwm1);           //开启TIM3的1，2通道输入占空比的值pwm
    pwm_set_duty(TIM3_PWM_MAP0_CH2_A7, pwm2);
}

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

//void goForwardOrBackward(GPS参数)    //这里是小车的运动算法

//void CargoForward(void)             //小车的前进

//void CarBackward(void)              //小车的后退

//void EnableAuxMotor(void)           //使能电机

//void DisableAuxMotor(void)          //失能电机


