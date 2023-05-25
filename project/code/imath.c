/*
 * imath.c
 *
 *  Created on: 2023Äê5ÔÂ24ÈÕ
 *      Author: 86152
 */

#ifndef IMATH_C_
#define IMATH_C_
#include "zf_common_headfile.h"

int16 RangeLimit(int16 thr_in,int16 thr_max)
{
    if(thr_in < -thr_max)    thr_in = -thr_max;
    if(thr_in >  thr_max)    thr_in =  thr_max;
    return thr_in;
}


#endif /* IMATH_C_ */
