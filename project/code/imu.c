/*此算法函数用来解决imu姿态*/

#include "zf_common_headfile.h"
#include "math.h"

_Matrix Mat = {0};
_Attitude att = {0};

#define MahonyPERIOD        5.0f                  //姿态解算周期（ms）
#define kp      0.5f                              //比例增益控制加速度计/磁强计的收敛速度
#define ki      0.0001f                           //积分增益控制陀螺仪偏差的收敛速率

float q0 = 1, q1 = 0, q2 = 0, q3 = 0;             //四元数元素表示估计方向
float exInt = 0, eyInt = 0, ezInt = 0;            //标度积分误差

/**********************************************************************************************/
/* 名字：mahony_update
 * 功能：姿态解算
 * 参数：陀螺仪三轴数据（单位：弧度/秒），加速度数据（单位：g）
 * 输出：无
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
/* 名字：rotation_matrix
 * 功能：旋转矩阵：机体坐标系->地理坐标系
 * 参数：无
 * 输出：无
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
/* 名字：rotation_matrix_T
 * 功能：旋转矩阵的转置矩阵：地理坐标系->机体坐标系
 * 参数：无
 * 输出：无
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
/* 名字：Matrix_ready
 * 功能：矩阵更新准备，为姿态解算使用
 * 参数：无
 * 输出：无
 */
void Matrix_ready(void)
{
  rotation_matrix();                      //旋转矩阵更新
  rotation_matrix_T();                    //选择矩阵的逆矩阵更新
}
