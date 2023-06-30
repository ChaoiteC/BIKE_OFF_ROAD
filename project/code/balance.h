#ifndef BALANCE_H_
#define BALANCE_H_

#include "zf_common_headfile.h"

extern PID balance_acc;//角速度环
extern PID balance_ang;//角度环
extern PID balance_vel;//速度环

void balance_init();
void balance_heartbeat();

#endif /* BALANCE_H_ */
