#include "Mahony.h"

#define twoKpDef (2.0f * 0.5f) // 2 * proportional gain
#define twoKiDef (2.0f * 0.0f) // 2 * integral gain

volatile float twoKp = twoKpDef;										   // 2 * proportional gain (Kp)
volatile float twoKi = twoKiDef;										   // 2 * integral gain (Ki)
volatile float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;				   // quaternion of sensor frame relative to auxiliary frame
volatile float integralFBx = 0.0f, integralFBy = 0.0f, integralFBz = 0.0f; // integral error terms scaled by Ki

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

// AHRS algorithm update
void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz)
{
	float recipNorm;
	float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
	float hx, hy, bx, bz;
	float halfvx, halfvy, halfvz, halfwx, halfwy, halfwz;
	float halfex, halfey, halfez;
	float qa, qb, qc;

	if ((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f))
	{
		MahonyAHRSupdateIMU(gx, gy, gz, ax, ay, az);
		return;
	}

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
	{

		//normalize the acc data
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		//normalize the magnetic data
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

		//calculate the reference direction of magnetic using quaternion
		hx = 2.0f * (mx * (0.5f - q2q2 - q3q3) + my * (q1q2 - q0q3) + mz * (q1q3 + q0q2));
		hy = 2.0f * (mx * (q1q2 + q0q3) + my * (0.5f - q1q1 - q3q3) + mz * (q2q3 - q0q1));
		bx = sqrt(hx * hx + hy * hy);
		bz = 2.0f * (mx * (q1q3 - q0q2) + my * (q2q3 + q0q1) + mz * (0.5f - q1q1 - q2q2));

		// calculate gravity and magnetic 
		halfvx = q1q3 - q0q2;
		halfvy = q0q1 + q2q3;
		halfvz = q0q0 - 0.5f + q3q3;
		halfwx = bx * (0.5f - q2q2 - q3q3) + bz * (q1q3 - q0q2);
		halfwy = bx * (q1q2 - q0q3) + bz * (q0q1 + q2q3);
		halfwz = bx * (q0q2 + q1q3) + bz * (0.5f - q1q1 - q2q2);

		// calculate the err between gravity and magnetic
		halfex = (ay * halfvz - az * halfvy) + (my * halfwz - mz * halfwy);
		halfey = (az * halfvx - ax * halfvz) + (mz * halfwx - mx * halfwz);
		halfez = (ax * halfvy - ay * halfvx) + (mx * halfwy - my * halfwx);

		// pid calculate
		if (twoKi > 0.0f)
		{
			integralFBx += twoKi * halfex * (1.0f / IMU_Update_Freq); // integral error scaled by Ki
			integralFBy += twoKi * halfey * (1.0f / IMU_Update_Freq);
			integralFBz += twoKi * halfez * (1.0f / IMU_Update_Freq);
			gx += integralFBx; // apply integral feedback
			gy += integralFBy;
			gz += integralFBz;
		}
		else
		{
			integralFBx = 0.0f; // prevent integral windup
			integralFBy = 0.0f;
			integralFBz = 0.0f;
		}

		// Apply proportional feedback
		gx += twoKp * halfex;
		gy += twoKp * halfey;
		gz += twoKp * halfez;
	}

	// Integrate rate of change of quaternion
	gx *= (0.5f * (1.0f / IMU_Update_Freq)); // pre-multiply common factors
	gy *= (0.5f * (1.0f / IMU_Update_Freq));
	gz *= (0.5f * (1.0f / IMU_Update_Freq));
	qa = q0;
	qb = q1;
	qc = q2;
	//update quaternion
	q0 += (-qb * gx - qc * gy - q3 * gz);
	q1 += (qa * gx + qc * gz - q3 * gy);
	q2 += (qa * gy - qb * gz + q3 * gx);
	q3 += (qa * gz + qb * gy - qc * gx);

	// Normalise quaternion
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
