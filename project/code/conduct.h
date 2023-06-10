#ifndef CONDUCT_H_
#define CONDUCT_H_

#include "zf_common_headfile.h"

void start_check();
void overturn_check();
void bluetooth_check();
void stop_do();

extern uint8 stop_flag;
extern float gps_distance;//到下一点的距离
extern float gps_azimuth;//到下一点位的测量方位角
extern uint8 current_gps_point;//当前GPS正在前往的点位

#endif /* CONDUCT_H_ */
