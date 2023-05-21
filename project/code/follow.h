#ifndef FOLLOW_H_
#define FOLLOW_H_

#include "zf_common_headfile.h"

void ready_start();
void gps_follow();
void mpu_follow();
void bluetooth_follow();
void stop_follow();

extern uint8 stop_bike;


#endif /* FOLLOW_H_ */
