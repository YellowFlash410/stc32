#ifndef __motor_H_
#define __motor_H_
#include "zf_common_headfile.h"
#include "camer.h"

//void IncPID_Init(PID *sptr,float *MOTOR_PID);                      //?????PID?????????
//int PID_Realize(PID *sptr, int ActualSpeed, int SetSpeed);   //?????PID????
//int PID_Cascade(PID *sprt, int NowPiont, int SetPoint);      //?????????PID????
//void pidinitall(void);
void Control_Speed();
//int range_protect(int duty, int min, int max);  //???
//void CS_control(void);
void speed_measure(void);
//void MOTOR_Control(void);
void MOTOR_init(void);
void Encoder_init(void);
void Speed_decision(void);
void speed_PIDL(void);
void speed_PIDR(void);
void Bruthless_init();
//void seepd_dif(void);
//void Start_gpio_init(void);
//void seepd_dif_two(void);
//#define S3010_MID 2660
//#define S3010_LEFT 3180                 //??????????????? ??
//#define S3010_RIGHT 2140                //??????????????? §³

typedef struct {
  float P;
  float I;
  float D;
  int LastError;  // Error[-1]
  int PrevError;  // Error[-2]
//  int EC;
//  float Kdin;   //????D
//  float Kdout;  //????D
} PID_Datatypedef;
extern float Speed_P_l,Speed_I_l,Speed_D_l;
extern float Speed_P_r,Speed_I_r,Speed_D_r;
extern int run_flag;
extern PID_Datatypedef SteerPIDdata;    //?????PID????
#endif /* MOTOR_H_ */
















