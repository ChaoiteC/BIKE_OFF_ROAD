/*���㷨�����������imu��̬*/

#include "zf_common_headfile.h"
#include "math.h"

_Matrix Mat = {0};
_Attitude att = {0};

#define MahonyPERIOD        5.0f                  //��̬�������ڣ�ms��
#define kp      0.5f                              //����������Ƽ��ٶȼ�/��ǿ�Ƶ������ٶ�
#define ki      0.0001f                           //�����������������ƫ�����������

float q0 = 1, q1 = 0, q2 = 0, q3 = 0;             //��Ԫ��Ԫ�ر�ʾ���Ʒ���
float exInt = 0, eyInt = 0, ezInt = 0;            //��Ȼ������

/**********************************************************************************************/
/* ���֣�mahony_update
 * ���ܣ���̬����
 * �������������������ݣ���λ������/�룩�����ٶ����ݣ���λ��g��
 * �������
 */
void mahony_update(float gx, float gy, float gz, float ax, float ay, float az)
{
    float norm;
    float vx, vy, vz;
    float ex, ey, ez;

   if(ax*ay*az==0)
      return;

   norm = invSqrt(ax*ax + ay*ay + az*az);
   ax = ax * norm;
   ay = ay * norm;
   az = az * norm;


   vx = Mat.DCM_T[0][2];
   vy = Mat.DCM_T[1][2];
   vz = Mat.DCM_T[2][2];


   ex = ay*vz - az*vy;
   ey = az*vx - ax*vz;
   ez = ax*vy - ay*vx;

   exInt = exInt + ex*ki;
   eyInt = eyInt + ey*ki;
   ezInt = ezInt + ez*ki;

   gx = gx + kp*ex + exInt;
   gy = gy + kp*ey + eyInt;
   gz = gz + kp*ez + ezInt;

   q0 = q0 + (-q1*gx - q2*gy - q3*gz)* MahonyPERIOD * 0.0005f;
   q1 = q1 + ( q0*gx + q2*gz - q3*gy)* MahonyPERIOD * 0.0005f;
   q2 = q2 + ( q0*gy - q1*gz + q3*gx)* MahonyPERIOD * 0.0005f;
   q3 = q3 + ( q0*gz + q1*gy - q2*gx)* MahonyPERIOD * 0.0005f;

   norm = invSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
   q0 = q0 * norm;
   q1 = q1 * norm;
   q2 = q2 * norm;
   q3 = q3 * norm;

   att.pit =  atan2(2.0f*(q0*q1 + q2*q3),q0*q0 - q1*q1 - q2*q2 + q3*q3) * rad_to_angle;
   att.rol =  asin(2.0f*(q0*q2 - q1*q3)) * rad_to_angle;

   att.yaw += Mpu.deg_s.z  * MahonyPERIOD * 0.001f;
}

/**********************************************************************************************/
/* ���֣�rotation_matrix
 * ���ܣ���ת���󣺻�������ϵ->��������ϵ
 * ��������
 * �������
 */
void rotation_matrix(void)
{
  Mat.DCM[0][0] = 1.0f - 2.0f * q2*q2 - 2.0f * q3*q3;
  Mat.DCM[0][1] = 2.0f * (q1*q2 -q0*q3);
  Mat.DCM[0][2] = 2.0f * (q1*q3 +q0*q2);

  Mat.DCM[1][0] = 2.0f * (q1*q2 +q0*q3);
  Mat.DCM[1][1] = 1.0f - 2.0f * q1*q1 - 2.0f * q3*q3;
  Mat.DCM[1][2] = 2.0f * (q2*q3 -q0*q1);

  Mat.DCM[2][0] = 2.0f * (q1*q3 -q0*q2);
  Mat.DCM[2][1] = 2.0f * (q2*q3 +q0*q1);
  Mat.DCM[2][2] = 1.0f - 2.0f * q1*q1 - 2.0f * q2*q2;
}

/**********************************************************************************************/
/* ���֣�rotation_matrix_T
 * ���ܣ���ת�����ת�þ��󣺵�������ϵ->��������ϵ
 * ��������
 * �������
 */
void rotation_matrix_T(void)
{
  Mat.DCM_T[0][0] = 1.0f - 2.0f * q2*q2 - 2.0f * q3*q3;
  Mat.DCM_T[0][1] = 2.0f * (q1*q2 +q0*q3);
  Mat.DCM_T[0][2] = 2.0f * (q1*q3 -q0*q2);

  Mat.DCM_T[1][0] = 2.0f * (q1*q2 -q0*q3);
  Mat.DCM_T[1][1] = 1.0f - 2.0f * q1*q1 - 2.0f * q3*q3;
  Mat.DCM_T[1][2] = 2.0f * (q2*q3 +q0*q1);

  Mat.DCM_T[2][0] = 2.0f * (q1*q3 +q0*q2);
  Mat.DCM_T[2][1] = 2.0f * (q2*q3 -q0*q1);
  Mat.DCM_T[2][2] = 1.0f - 2.0f * q1*q1 - 2.0f * q2*q2;
}

/**********************************************************************************************/
/* ���֣�Matrix_ready
 * ���ܣ��������׼����Ϊ��̬����ʹ��
 * ��������
 * �������
 */
void Matrix_ready(void)
{
  rotation_matrix();                      //��ת�������
  rotation_matrix_T();                    //ѡ��������������
}
