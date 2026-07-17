#include "zf_common_headfile.h"
#include "INIT.h"
#include "camer.h"
#include "motor.h"
#include "math.h"
#include "steer.h"
int  Angle;//以PWM差的形式表示打角，>0右转，小于0左转
int run_flag = 0;
int  bmq_record=0;//记录编码器(没用)
int16 speed1, speed2;
//速度决策2
int16 Speed_Goal;
//左轮
int16 Speed_Goal_l;//目标速度
int16 Speed_Encoder_l;//当前速度
float Speed_P_l,Speed_I_l,Speed_D_l;
int16 Speed_Erro_l;//当前误差
int16 Speed_PID_OUT_l;//占空比输出
int16 Speed_Lasterro_l;//上次误差
int16 Speed_Preverro_l;//上上次误差
//右轮
int16 Speed_Goal_r;//目标速度
int16 Speed_Encoder_r;//当前速度
float Speed_P_r,Speed_I_r,Speed_D_r;
int16 Speed_Erro_r;//当前误差
int16 Speed_PID_OUT_r;//占空比输出
int16 Speed_Lasterro_r;//上次误差
int16 Speed_Preverro_r;//上上次误差
extern uint8 zhidao;
extern float SteerErr;
void MOTOR_init()
{
    gpio_init(DIR_1, GPO, GPIO_HIGH, GPO_PUSH_PULL);   // GPIO 初始化为输出 默认上拉输出高
    pwm_init(PWM_1, 17000, 0);                         // PWM 通道初始化频率 17KHz 占空比初始为 0

    gpio_init(DIR_2, GPO, GPIO_HIGH, GPO_PUSH_PULL);   // GPIO 初始化为输出 默认上拉输出高
    pwm_init(PWM_2, 17000, 0);                         // PWM 通道初始化频率 17KHz 占空比初始为 0
}

void Bruthless_init()
{
//	// 初始化 A1 (P0.1) 为 300Hz, 11% 占空比
//	pwm_init(PWMB_CH2_P01, 300, 1100);

//	// 初始化 A3 (P0.3) 为 300Hz, 11% 占空比
//	pwm_init(PWMB_CH4_P03, 300, 1100);
//	
//	pwm_init(PWMA_CH1P_P10, 300, 1100);
	// 初始化 A1引脚 
    pwm_init(PWME_CH1N_PA1, 50, 500);
    
    // 初始化 A3 引脚
    pwm_init(PWME_CH2N_PA3, 50, 500);
	
	system_delay_ms(3000); 

    // 3. 尝试低速转动
    // 将脉宽提升到 1.1ms (1.1/20 * 10000 = 550)
    // 只要解锁成功，550 的占空比应该能让电机慢速转起来
    pwm_set_duty(PWME_CH1N_PA1, 750);
    pwm_set_duty(PWME_CH2N_PA3, 750);
}

void Encoder_init()
{
    encoder_quad_init(ENCODER_QUAD_1, ENCODER_QUAD_1_CHA, ENCODER_QUAD_1_CHB);   // 初始化编码器模块与引脚 带方向增量编码器模式
    encoder_quad_init(ENCODER_QUAD_2, ENCODER_QUAD_2_CHA, ENCODER_QUAD_2_CHB);   // 初始化编码器模块与引脚 带方向增量编码器模式
}
void speed_measure()
{
	    float diff_coeff;
//	    int offset1 = ImageStatus.Det_True - ImageStatus.MiddleLine;
          speed2 = -encoder_get_count(ENCODER_QUAD_1);     // 定时器取值
          encoder_clear_count(ENCODER_QUAD_1);                     // 定时器清空
          speed1 = encoder_get_count(ENCODER_QUAD_2);     // 定时器取值
          encoder_clear_count(ENCODER_QUAD_2);                     // 定时器清空
//	            gpio_set_level(DIR_1, GPIO_HIGH);                                   // DIR输出高电平
//            pwm_set_duty(PWM_1, 1000);                   // 计算占空比

//            gpio_set_level(DIR_2, GPIO_HIGH);                                   // DIR输出高电平
//            pwm_set_duty(PWM_2, 1000);                   // 计算占空比
          Control_Speed();              //变速控制
		     // 差速核心 
    if(abs(ImageStatus.Det_True - ImageStatus.MiddleLine) < 3||zhidao==1)  // 偏差很小 → 直走，不差速
    {
        Speed_Goal_l = Speed_Goal;
        Speed_Goal_r = Speed_Goal;
    }
    else  // 有偏差 → 自动差速，偏差越大差速越大
    {
        // 大转弯自动加大差速：offset 越大，系数越大

        if(abs(ImageStatus.Det_True - ImageStatus.MiddleLine) > 26)        // 大转弯
            diff_coeff = 0.5;       // 差速最大
        else if(ImageStatus.Road_type == LeftCirque||ImageStatus.Road_type == RightCirque)   // 中等转弯
            diff_coeff = 0.4;
        else                       // 小转弯
            diff_coeff = 0.1;

        // 你原来的差速公式
        Speed_Goal_l = Speed_Goal + SteerErr * diff_coeff;
        Speed_Goal_r = Speed_Goal - SteerErr * diff_coeff;

        // 速度限幅，防止乱飙
        if(Speed_Goal_l < 18) Speed_Goal_l = 18;
        if(Speed_Goal_l > 45) Speed_Goal_l = 45;
        if(Speed_Goal_r < 18) Speed_Goal_r = 18;
        if(Speed_Goal_r > 45) Speed_Goal_r = 45;
    }
          speed_PIDL();
          speed_PIDR();
//		gpio_set_level(DIR_1, GPIO_HIGH);   // 左轮
//		pwm_set_duty(PWM_1, 2000);          // 

//    gpio_set_level(DIR_2, GPIO_HIGH);   //右轮
//    pwm_set_duty(PWM_2, 2000);          // 
}
void Control_Speed()
{
        Speed_Goal = 40; //150                              Speed_Goal原本是40
        if(ImageStatus.Road_type ==LeftCirque
          ||ImageStatus.Road_type ==RightCirque) Speed_Goal =30; //150               Speed_Goal原本是30
        if(Stop_car_Flag == 1&& ImageStatus.Road_type !=LeftCirque
          &&ImageStatus.Road_type !=RightCirque &&ImageStatus.Road_type !=Ramp )
        {
            Speed_Goal = 0;
        }
		if(ImageStatus.Road_type == Ramp)Speed_Goal =5;//Speed_Goal原本是30
}
void Speed_decision()
{
    Speed_P_l = 0.3; //200
    Speed_I_l = 0.2; //40
    Speed_D_l = 0; //5
    Speed_P_r = 0.3;//200
    Speed_I_r = 0.2; //40
    Speed_D_r = 0;  //5
}

void speed_PIDL(void)
{
    Speed_Encoder_l  = speed1;//编码器采集当前速度
        Speed_Erro_l     =  Speed_Goal_l - Speed_Encoder_l;   //编码器反馈目标值与当前的差值
    Speed_PID_OUT_l += (Speed_P_l * (Speed_Erro_l - Speed_Lasterro_l)  +
                      Speed_I_l *  Speed_Erro_l  +
                      Speed_D_l * (Speed_Erro_l - 2 * Speed_Lasterro_l + Speed_Preverro_l));
    if(Speed_PID_OUT_l<-3000)
        Speed_PID_OUT_l = -3000;
    if(Speed_PID_OUT_l>3000)
        Speed_PID_OUT_l = 3000;
    Speed_Preverro_l =  Speed_Lasterro_l;
    Speed_Lasterro_l =  Speed_Erro_l;
    if(Speed_PID_OUT_l>=0)
    {
      gpio_set_level(DIR_2, GPIO_HIGH);                                   // DIR输出高电平
      pwm_set_duty(PWM_2, Speed_PID_OUT_l);                   // 计算占空比
    }
    else
    {
            gpio_set_level(DIR_2, GPIO_LOW);                                   // DIR输出高电平
            pwm_set_duty(PWM_2, -Speed_PID_OUT_l);                   // 计算占空比

    }
}
void speed_PIDR()
{
    Speed_Encoder_r  =  speed2;//编码器采集当前速度
//    gpt12_clear(COUNTER2_TIM);
        Speed_Erro_r     =  Speed_Goal_r - Speed_Encoder_r;   //编码器反馈目标值与当前的差值
    Speed_PID_OUT_r += (Speed_P_r * (Speed_Erro_r - Speed_Lasterro_r)  +
                      Speed_I_r *  Speed_Erro_r  +
                      Speed_D_r * (Speed_Erro_r - 2 * Speed_Lasterro_r + Speed_Preverro_r));
    if(Speed_PID_OUT_r<-3000)
        Speed_PID_OUT_r = -3000;
    if(Speed_PID_OUT_r>3000)
        Speed_PID_OUT_r = 3000;
    Speed_Preverro_r =  Speed_Lasterro_r;
    Speed_Lasterro_r =  Speed_Erro_r;
    if(Speed_PID_OUT_r>=0)
    {
      gpio_set_level(DIR_1, GPIO_HIGH);                                   // DIR输出高电平
      pwm_set_duty(PWM_1, Speed_PID_OUT_r);
    }
    else
    {
      gpio_set_level(DIR_1, GPIO_LOW);                                   // DIR输出高电平
      pwm_set_duty(PWM_1, -Speed_PID_OUT_r);
    }
}
//void Start_gpio_init(void)
//{
//    gpio_init(P20_7,GPI,0,GPI_PULL_DOWN);
//    gpio_init(P20_8, GPO, 0, GPO_PUSH_PULL); // P00_0初始化为GPIO功能、输出模式、输出高电平、推挽输出
//}