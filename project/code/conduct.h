#ifndef CONDUCT_H_
#define CONDUCT_H_

#include "zf_common_headfile.h"

void ready_start();
void gps_read();
void overturn_check();
void bluetooth_check();
void stop_do();

extern uint8 stop_flag;


#endif /* CONDUCT_H_ */
