#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "stdint.h"

#include "zf_common_headfile.h"

typedef struct//µç»úÊä³ö
{
  int out;
}_OUT_Motor;

void _controller_perform(void) ;
void _controller_output(void)   ;
void CargoForward(void);
void CarBackward(void);
void EnableAuxMotor(void);
void DisableAuxMotor(void);
void TurnLeftOrRight(float inXrocker);
void goForwardOrBackward(float inYrcoker);
extern _OUT_Motor Motor1;

#endif
