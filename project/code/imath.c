/*此函数库用来对编码器的数值进行存放或者进行数学运算*/

#include "imath.h"

/**********************************************************************************************/
/* 名字：invSqrt
 * 功能：获得平方根倒数
 * 参数：x
 * 输出：x的平方根倒数
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
/* 名字：_set_val
 * 功能：三轴数据进行赋值操作
 * 参数：*_out_data输出数据，*_in_data输入数据
 * 输出：无
 */
void _set_val(SI_F_XYZ *_out_data,SI_F_XYZ *_in_data)
{
  _out_data->x = _in_data->x;
  _out_data->y = _in_data->y;
  _out_data->z = _in_data->z;
}

/**********************************************************************************************/
/* 名字：setFloatValue
 * 功能：三轴数据进行赋值操作
 * 参数：*_in_data输入数据，value你想输入的值
 * 输出：无
 */
void  setFloatValue(SI_F_XYZ *_in_data,float value)
{
    _in_data->x = value;
    _in_data->y = value;
    _in_data->z = value;
}

/**********************************************************************************************/
/* 名字：f_abs
 * 功能：浮点型数据绝对值
 * 参数：浮点数f
 * 输出：浮点数f的绝对值
 */
float f_abs(float f)
{
    if (f >= 0.0f)
        return f;
    return -f;
}

/**********************************************************************************************/
/* 名字：u16RangeLimit
 * 功能：16位整形数据进行范围限制
 * 参数：thr_min最小值，thr_max最大值，thr_in你需要限制的值
 * 输出：thr_in限制后的值
 */
uint16_t u16RangeLimit(uint16_t thr_in,uint16_t thr_min,uint16_t thr_max)
{
    if(thr_in < thr_min)    thr_in = thr_min;
    if(thr_in > thr_max)    thr_in = thr_max;

    return thr_in;
}

 /**********************************************************************************************/
 /* 名字：u32RangeLimit
  * 功能：32位无符号整形变量数据进行范围限制
  * 参数：thr_min最小值，thr_max最大值，thr_in你需要限制的值
  * 输出：thr_in限制后的值
  */
  uint32 u32RangeLimit(uint32 thr_in,uint32 thr_min,uint32 thr_max)
 {
     if(thr_in < thr_min)    thr_in = thr_min;
     if(thr_in > thr_max)    thr_in = thr_max;

     return thr_in;
 }

/**********************************************************************************************/
/* 名字：int_abs
 * 功能：整型数据绝对值
 * 参数：整型数f
 * 输出：整型数f的绝对值
 */
int int_abs(int f)
{
    if (f >= 0)
        return f;
    return -f;
}
