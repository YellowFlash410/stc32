#ifndef __steer_H_
#define __steer_H_
#include "zf_common_headfile.h"
#define steer_middle  700
#define steer_right   570       
#define steer_left    800
#define LimitLeft(Left)    (Left = ((Left > steer_left) ? steer_left : Left))
#define LimitRight(Right)  (Right = ((Right < steer_right) ? steer_right : Right))

extern PID_Datatypedef SteerPIDdata;
void SteerControl(uint32 duty);
void SteerPID_Realize(float offset);
void dynamic_pid_value_set(void);
extern float SteerErr;
#endif