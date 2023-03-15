#include "zf_common_headfile.h"

_OUT_Motor Motor1 = {0};//ǰ���
_OUT_Motor Motor2 = {0};//����

/**********************************************************************************************/
/* ���֣��⻷�ٶȿ�����
 * ���ܣ�PID�����ٶȻ�
 * ��������
 * �������
 */
static void vel_controller(void)
{
  all.vel_encoder.expect = 0.0f;
  all.vel_encoder.feedback = encoderINFO.mainNumberValue;
  pid_controller(&all.vel_encoder);
}

/**********************************************************************************************/
/* ���֣��ڻ��Ƕȿ�����
 * ���ܣ�PID����ǶȻ�
 * ��������
 * �������
 */
static void angle_controller(void)
{
  all.rol_angle.expect = all.vel_encoder.out;
  all.rol_angle.feedback = (-att.rol)+(0);
  pid_controller(&all.rol_angle);
}

/**********************************************************************************************/
/* ���֣��ڻ����ٶȿ�����
 * ���ܣ�PID������ٶȻ�
 * ��������
 * �������
 */
static void gyro_controller(void)
{
  all.rol_gyro.expect = all.rol_angle.out;
  all.rol_gyro.feedback = -(Mpu.deg_s.y);
  pid_controller(&all.rol_gyro);
}

/**********************************************************************************************/
/* ���֣���������PID����������
 * ���ܣ�PID����
 * ��������
 * �������
 */
void _controller_perform(void)
{
  vel_controller();
  angle_controller();
  gyro_controller();
}
/**********************************************************************************************/
/* ���֣����С��״̬����
 * ���ܣ����С���Ƿ���
 * ����������������ĽǶȵ�ֵinAngleData
 * �������
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
/* ���֣�pwmMotorOut
 * ���ܣ�PWM���
 * ������
 * �������
 */

/*//���޸�

static void pwmMotorOut(uint16_t pwm1 , uint16_t pwm2 )
{
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, u16RangeLimit(pwm1 , 0 , 2000));
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, u16RangeLimit(pwm2 , 0 , 2000));
}

*/

/**********************************************************************************************/
/* ���֣�_controller_output
 * ���ܣ����������
 * ��������
 * �������
 */

/*
static uint16_t N20_motor_speed;
void _controller_output(void)
{
  static uint8_t FalldownAndRestart = 0;

  // ����Ƿ���
  if( detectionFallDown(att.rol)==1 )
  {
    N20_motor_speed = 2000;
    FalldownAndRestart = 1;
    DisableAuxMotor();
    Motor1.out = 0;
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

  if(Motor1.out>0)  dirAnticlockwise();
  else  dirClockwise();

  //������Ҫ�������������С�����˶�����GPS�Ĳ���������С�����н�
  TurnLeftOrRight(BluetoothParseMsg.Xrocker);
  goForwardOrBackward(BluetoothParseMsg.Yrocker);

  pwmMotorOut( int_abs(Motor1.out) , N20_motor_speed);
}
*/


//����Ҫ�ÿ��ƺ��������Ƶ������������ _controller_output��void�����������㷨�����������Ǿ�����㷨����

//void goForwardOrBackward(GPS����)    //������С�����˶��㷨

//void CargoForward(void)             //С����ǰ��

//void CarBackward(void)              //С���ĺ���

//void EnableAuxMotor(void)           //ʹ�ܵ��

//void DisableAuxMotor(void)          //ʧ�ܵ��


