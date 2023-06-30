#ifndef BALANCE_H_
#define BALANCE_H_

#include "zf_common_headfile.h"

extern PID balance_acc;//瑙掗�熷害鐜�
extern PID balance_ang;//瑙掑害鐜�
extern PID balance_vel;//閫熷害鐜�

void balance_init();
void balance_heartbeat();

#endif /* BALANCE_H_ */
