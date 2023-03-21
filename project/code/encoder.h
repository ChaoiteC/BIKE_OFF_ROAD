#ifndef __ENCODER_H
#define __ENCODER_H
//#include "headfile.h"

#define ENCODER					TIM_3
#define ENCODER_LSB					TIM_3_ENC1_B04

void encoder_init(void);
unsigned short int get_count(void);
unsigned short int filter(void);

#endif






