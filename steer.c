#include "camer.h"
#include "INIT.h"
#include "motor.h"
#include "Fuzzy.h"
#include "steer.h"
PID_Datatypedef SteerPIDdata;   //舵机的PID参数
extern int16 Speed_Goal_l;//目标速度
extern int16 Speed_Goal_r;//目标速度
float SteerErr;
int16 servo_angle=0;
//动态PID调参
//float Kp_base = 10.0;   
//float Kp_factor = 0.008; 

//void SteerPID_Realize(float offset) {
//  float iError, SteerErr;
//  int PWM;
//  float kp_two = 0.3;

//  iError = offset;
// 
//  SteerPIDdata.P = Kp_base + (iError * iError) * Kp_factor; 
//  
//  SteerPIDdata.D = 30.0; 

//  SteerErr = SteerPIDdata.P * iError +
//             iError * abs(iError) * kp_two +
//             (iError - SteerPIDdata.LastError) * SteerPIDdata.D;

//  SteerPIDdata.LastError = iError;

//  PWM = steer_middle - SteerErr;
//  SteerControl(PWM);
//}
//*************下面是舵机的*****************
//void SteerControl(uint32 duty) 
//{
//  LimitLeft(duty);
//  LimitRight(duty);  //限幅
//  pwm_set_duty(SERVO_PWM1, duty);
//}
//void SteerPID_Realize(float offset) {

//  float iError,  //当前误差
//   SteerErr;  //偏差
//  int PWM;
//  float kp_two = 0.1;
//  iError = offset;  //计算当前误差
//  SteerErr =
//     SteerPIDdata.P * iError 
//	+iError*kp_two
//	+(iError - SteerPIDdata.LastError)*SteerPIDdata.D;  //位置式PID算式
//  SteerPIDdata.LastError = iError;                       //更新上次误差
//  PWM = steer_middle - SteerErr;
//  SteerControl(PWM);
//  
//}
float kp_two = 0.0015;     // 二次项shu
void SteerControl(uint32 duty) 
{
  LimitLeft(duty);
  LimitRight(duty);  //限幅
  pwm_set_duty(SERVO_PWM1, duty);
}
void dynamic_pid_value_set(void)
{
    // 原二次项Kp逻辑：Kp_base + (MID_W-final_mid_line)2 * 0.0015
    SteerPIDdata.P = 1.5+ (ImageStatus.Det_True - ImageStatus.MiddleLine) * (ImageStatus.Det_True - ImageStatus.MiddleLine) * kp_two;
    SteerPIDdata.D = 5;  // 固定Kd_base=5
    SteerPIDdata.I = 0;  // 积分项禁用（原逻辑）
}
void SteerPID_Realize(float offset) {
  float iError;   // 当前误差（严格按你的变量名）
//  float SteerErr; // 偏差（严格按你的变量名）
  int PWM;        // PWM输出值（严格按你的变量名）

  // 步骤1：更新动态PID参数（每次计算前刷新）
  dynamic_pid_value_set();

  // 步骤2：计算当前误差（offset为图像偏差，对应原PID->Error）
  iError = offset;  

  // 步骤3：位置式PID算式（完全按你的公式格式）
  SteerErr = SteerPIDdata.P * iError          // P项（含动态更新的Kp）
           + iError * kp_two                  // 二次项（原动态PID逻辑）
           + (iError - SteerPIDdata.LastError) * SteerPIDdata.D;  // D项

  // 步骤4：更新上次误差（核心，对应原PID->Out_P更新）
  SteerPIDdata.LastError = iError;                      

  // 步骤5：计算最终PWM值（舵机中位 - 偏差，严格按你的逻辑）
  PWM = steer_middle - SteerErr;

  // 步骤6：输出到舵机（调用你的控制函数）
  SteerControl(PWM);
}