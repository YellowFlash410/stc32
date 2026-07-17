#ifndef __INIT_H_
#define __INIT_H_
#include "zf_common_headfile.h"
  // 舵机对应的 0-180 活动角度对应 控制脉冲的 0.5ms-2.5ms 高电平
  //
  // 那么不同频率下的占空比计算方式就是
  // PWM_DUTY_MAX/(1000/freq)*(1+Angle/180) 在 50hz 时就是 PWM_DUTY_MAX/(1000/50)*(1+Angle/180)
  //
  // 那么 100hz 下 90度的打角 即高电平时间1.5ms 计算套用为
  // PWM_DUTY_MAX/(1000/100)*(1+90/180) = PWM_DUTY_MAX/10*1.5
//蜂鸣器
#define BUZZER_PIN IO_P65
//激光笔
#define JG_HEAD_PIN IO_P67
//电机
#define DIR_3               ( IO_P50 ) 
#define PWM_3               ( PWMD_CH2_P51 )
                              
#define DIR_4               ( IO_P52 ) 
#define PWM_4               ( PWMD_CH4_P53 )


#define DIR_1               ( IO_P75 )
#define PWM_1               ( PWMB_CH1_P74 )
                              
#define DIR_2               ( IO_P77 )
#define PWM_2               ( PWMB_CH3_P76 )                   
//led                         
#define LED                 ( IO_P52 )
//舵机
#define SERVO_DUTY(x)         ((float)PWM_DUTY_MAX / (1000.0 / (float)SERVO_FREQ) * (0.5 + (float)(x) / 90.0))

#define SERVO_PWM1              (PWME_CH1P_PA0)                         // 定义主板上舵机对应引脚
#define SERVO_PWM2              (PWME_CH2P_PA2)                         // 定义主板上舵机对应引脚
#define SERVO_PWM3              (PWME_CH3P_PA4)                         // 定义主板上舵机对应引脚
#define SERVO_PWM4              (PWME_CH4P_PA6)                         // 定义主板上舵机对应引脚

#define SERVO_FREQ              (50 )                                           // 定义主板上舵机频率  请务必注意范围 50-300

#define SERVO_L_MAX             (80 )                                           // 定义主板上舵机活动范围 角度
#define SERVO_R_MAX             (100)                                           // 定义主板上舵机活动范围 角度
//电调
#define FREQ               (50)                                                // 控制频率为50HZ，最高支持300HZ
#define PWM1              (PWMF_CH1_PA1)
#define PWM2              (PWMF_CH2_PA3)
#define PWM3              (PWMF_CH3_PA5)
#define PWM4              (PWMF_CH4_PA7)
        //用法 pwm_set_duty(PWM_1, duty);
//编码器
#define ENCODER_QUAD_1                 	(PWMA_ENCODER)              // 带方向编码器对应使用的编码器接口 
#define ENCODER_QUAD_1_CHA            	(PWMA_ENCODER_CH1P_P60)     // PULSE 对应的引脚
#define ENCODER_QUAD_1_CHB              (PWMA_ENCODER_CH2P_P62)     // DIR 对应的引脚

#define ENCODER_QUAD_2                 	(PWMC_ENCODER)              // 带方向编码器对应使用的编码器接口
#define ENCODER_QUAD_2_CHA   		    (PWMC_ENCODER_CH1P_P40)     // PULSE 对应的引脚
#define ENCODER_QUAD_2_CHB       	    (PWMC_ENCODER_CH2P_P42)     // DIR 对应的引脚

          //用法，要和PIT结合起来
//TFT  无
void KEYGPIO_init();
void BUZZER_init();
void JG_init();
//void MOTOR();函数中已经有了
void DJLED_init();
void servo_init();
void DT_INIT();
//void ENCODER();函数中已经有了
#endif