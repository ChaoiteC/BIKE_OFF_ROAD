/*出発のベルが鳴る
  乗客は私一人だけ
  手を叩く わたしだけの音
  足鳴らす 足跡残すまで
  目を開ける 孤独の称号
  受け止める 孤高の衝動
  今 胸の奥 確かめる心音
  ほかに何も聴きたくない
  わたしが放つ音以外*/

#include "Mahony.h"

#define twoKpDef (2.0f * 0.5f) // 2*比例增益
#define twoKiDef (2.0f * 0.0f) // 2*积分增益

volatile float twoKp = twoKpDef;										   // 2 * proportional gain (Kp)
volatile float twoKi = twoKiDef;										   // 2 * integral gain (Ki)
volatile float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;				   // 传感器框架相对于辅助框架的四元数
volatile float integralFBx = 0.0f, integralFBy = 0.0f, integralFBz = 0.0f; // 以Ki为尺度的积分误差项

static float invSqrt(float x)
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float *)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

// AHRS算法更新
void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz)
{
	float recipNorm;
	float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
	float hx, hy, bx, bz;
	float halfvx, halfvy, halfvz, halfwx, halfwy, halfwz;
	float halfex, halfey, halfez;
	float qa, qb, qc;

	/*if ((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f))
	{
		MahonyAHRSupdateIMU(gx, gy, gz, ax, ay, az);
		return;
	}*///显然，我们有磁度计。

	// 只在加速器测量有效时计算反馈（避免加速器归一化中的NaN）
	if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
	{

		//将acc数据正常化
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		//将磁性数据正常化
		recipNorm = invSqrt(mx * mx + my * my + mz * mz);
		mx *= recipNorm;
		my *= recipNorm;
		mz *= recipNorm;

		q0q0 = q0 * q0;
		q0q1 = q0 * q1;
		q0q2 = q0 * q2;
		q0q3 = q0 * q3;
		q1q1 = q1 * q1;
		q1q2 = q1 * q2;
		q1q3 = q1 * q3;
		q2q2 = q2 * q2;
		q2q3 = q2 * q3;
		q3q3 = q3 * q3;

		//用四元数计算磁的参考方向
		hx = 2.0f * (mx * (0.5f - q2q2 - q3q3) + my * (q1q2 - q0q3) + mz * (q1q3 + q0q2));
		hy = 2.0f * (mx * (q1q2 + q0q3) + my * (0.5f - q1q1 - q3q3) + mz * (q2q3 - q0q1));
		bx = sqrt(hx * hx + hy * hy);
		bz = 2.0f * (mx * (q1q3 - q0q2) + my * (q2q3 + q0q1) + mz * (0.5f - q1q1 - q2q2));

		// 计算重力和磁力 
		halfvx = q1q3 - q0q2;
		halfvy = q0q1 + q2q3;
		halfvz = q0q0 - 0.5f + q3q3;
		halfwx = bx * (0.5f - q2q2 - q3q3) + bz * (q1q3 - q0q2);
		halfwy = bx * (q1q2 - q0q3) + bz * (q0q1 + q2q3);
		halfwz = bx * (q0q2 + q1q3) + bz * (0.5f - q1q1 - q2q2);

		// 计算重力和磁力之间的差值
		halfex = (ay * halfvz - az * halfvy) + (my * halfwz - mz * halfwy);
		halfey = (az * halfvx - ax * halfvz) + (mz * halfwx - mx * halfwz);
		halfez = (ax * halfvy - ay * halfvx) + (mx * halfwy - my * halfwx);

		// pid计算
		if (twoKi > 0.0f)
		{
			integralFBx += twoKi * halfex * (1.0f / IMU_Update_Freq); // 以Ki为尺度的积分误差
			integralFBy += twoKi * halfey * (1.0f / IMU_Update_Freq);
			integralFBz += twoKi * halfez * (1.0f / IMU_Update_Freq);
			gx += integralFBx; // 应用积分反馈
			gy += integralFBy;
			gz += integralFBz;
		}
		else
		{
			integralFBx = 0.0f; // 防止整体卷曲
			integralFBy = 0.0f;
			integralFBz = 0.0f;
		}

		// 应用比例反馈
		gx += twoKp * halfex;
		gy += twoKp * halfey;
		gz += twoKp * halfez;
	}

	// 整合四元数的变化率
	gx *= (0.5f * (1.0f / IMU_Update_Freq)); // 预乘公因数
	gy *= (0.5f * (1.0f / IMU_Update_Freq));
	gz *= (0.5f * (1.0f / IMU_Update_Freq));
	qa = q0;
	qb = q1;
	qc = q2;
	//更新四元数
	q0 += (-qb * gx - qc * gy - q3 * gz);
	q1 += (qa * gx + qc * gz - q3 * gy);
	q2 += (qa * gy - qb * gz + q3 * gx);
	q3 += (qa * gz + qb * gy - qc * gx);

	// 归一化四元数
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
}

// IMU算法更新
void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az)
{
	float recipNorm;			  
	float halfvx, halfvy, halfvz; 
	float halfex, halfey, halfez; 
	float qa, qb, qc;

	//只在加速度计测量有效时计算反馈（避免加速度计正常化中的NaN）。
	if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
	{


		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;


		halfvx = q1 * q3 - q0 * q2;
		halfvy = q0 * q1 + q2 * q3;
		halfvz = q0 * q0 - 0.5f + q3 * q3;


		halfex = (ay * halfvz - az * halfvy);
		halfey = (az * halfvx - ax * halfvz);
		halfez = (ax * halfvy - ay * halfvx);


		if (twoKi > 0.0f)
		{
			integralFBx += twoKi * halfex * (1.0f / IMU_Update_Freq); // 以Ki为尺度的积分误差
			integralFBy += twoKi * halfey * (1.0f / IMU_Update_Freq);
			integralFBz += twoKi * halfez * (1.0f / IMU_Update_Freq);
			gx += integralFBx; // 应用积分反馈
			gy += integralFBy;
			gz += integralFBz;
		}
		else
		{
			integralFBx = 0.0f; // 防止整体卷曲
			integralFBy = 0.0f;
			integralFBz = 0.0f;
		}


		gx += twoKp * halfex;
		gy += twoKp * halfey;
		gz += twoKp * halfez;
	}


	gx *= (0.5f * (1.0f / IMU_Update_Freq)); // 预乘公因数
	gy *= (0.5f * (1.0f / IMU_Update_Freq));
	gz *= (0.5f * (1.0f / IMU_Update_Freq));
	qa = q0;
	qb = q1;
	qc = q2;

	q0 += (-qb * gx - qc * gy - q3 * gz);
	q1 += (qa * gx + qc * gz - q3 * gy);
	q2 += (qa * gy - qb * gz + q3 * gx);
	q3 += (qa * gz + qb * gy - qc * gx);

	// 将四元数归一化
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
}
