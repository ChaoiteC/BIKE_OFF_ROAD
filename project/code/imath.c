/*�˺����������Ա���������ֵ���д�Ż��߽�����ѧ����*/

#include "imath.h"

/**********************************************************************************************/
/* ���֣�invSqrt
 * ���ܣ����ƽ��������
 * ������x
 * �����x��ƽ��������
 */
float invSqrt(float x)
{
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)&y;
    i = 0x5f3759df - (i>>1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

/**********************************************************************************************/
/* ���֣�_set_val
 * ���ܣ��������ݽ��и�ֵ����
 * ������*_out_data������ݣ�*_in_data��������
 * �������
 */
void _set_val(SI_F_XYZ *_out_data,SI_F_XYZ *_in_data)
{
  _out_data->x = _in_data->x;
  _out_data->y = _in_data->y;
  _out_data->z = _in_data->z;
}

/**********************************************************************************************/
/* ���֣�setFloatValue
 * ���ܣ��������ݽ��и�ֵ����
 * ������*_in_data�������ݣ�value���������ֵ
 * �������
 */
void  setFloatValue(SI_F_XYZ *_in_data,float value)
{
    _in_data->x = value;
    _in_data->y = value;
    _in_data->z = value;
}

/**********************************************************************************************/
/* ���֣�f_abs
 * ���ܣ����������ݾ���ֵ
 * ������������f
 * �����������f�ľ���ֵ
 */
float f_abs(float f)
{
    if (f >= 0.0f)
        return f;
    return -f;
}

/**********************************************************************************************/
/* ���֣�u16RangeLimit
 * ���ܣ�16λ�������ݽ��з�Χ����
 * ������thr_min��Сֵ��thr_max���ֵ��thr_in����Ҫ���Ƶ�ֵ
 * �����thr_in���ƺ��ֵ
 */
uint16_t u16RangeLimit(uint16_t thr_in,uint16_t thr_min,uint16_t thr_max)
{
    if(thr_in < thr_min)    thr_in = thr_min;
    if(thr_in > thr_max)    thr_in = thr_max;

    return thr_in;
}

 /**********************************************************************************************/
 /* ���֣�u32RangeLimit
  * ���ܣ�32λ�޷������α������ݽ��з�Χ����
  * ������thr_min��Сֵ��thr_max���ֵ��thr_in����Ҫ���Ƶ�ֵ
  * �����thr_in���ƺ��ֵ
  */
  uint32 u32RangeLimit(uint32 thr_in,uint32 thr_min,uint32 thr_max)
 {
     if(thr_in < thr_min)    thr_in = thr_min;
     if(thr_in > thr_max)    thr_in = thr_max;

     return thr_in;
 }

/**********************************************************************************************/
/* ���֣�int_abs
 * ���ܣ��������ݾ���ֵ
 * ������������f
 * �����������f�ľ���ֵ
 */
int int_abs(int f)
{
    if (f >= 0)
        return f;
    return -f;
}
