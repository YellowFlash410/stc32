/*********************************************************************************************************************
* STC32G144K Opensourec Library 即（STC32G144K 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2025 SEEKFREE 逐飞科技
*
* 本文件是STC32G144K开源库的一部分
*
* STC32G144K 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MDK FOR C251
* 适用平台          STC32G144K
* 店铺链接          https://seekfree.taobao.com/
*
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "camer.h"
#include "INIT.h"
#include "motor.h"
#include "steer.h"
#include "tft180.h"
#include "fuzzy.h"
uint16 pit_ms_count = 0;
extern int16 Speed_Goal_r;
extern int16 Speed_Goal_l;
extern int16 Speed2;
extern int16 Speed1;
void main(void)
{
    clock_init(SYSTEM_CLOCK_96M); 				// 时钟配置及系统初始化<务必保留>
    debug_init();                       		// 调试串口信息初始化

    // 此处编写用户代码 例如外设初始化代码等
    Data_Settings(); // 参数给定
    JG_init();    //初始化激光笔的io    
	KEYGPIO_init();        // 按键初始化
    tft180_init();     // 初始化屏幕
    servo_init();      // 舵机初始化
    mt9v03x_init();   // 摄像头初始化
    Speed_decision();  //pid参数初始化
    MOTOR_init();   // 电机初始化
		//Bruthless_init();//驱动无刷电机
   Encoder_init();  // 编码器初始化
	dl1b_init();   //TOF测距初始化
 //Start_gpio_init(); 软启动开跑初始化
    mt9v03x_set_exposure_time(300);  // 曝光时间300
    pit_ms_init(TIM1_PIT,5,NULL);        // 5ms中断 电机控制
   pit_ms_init(TIM0_PIT,20,NULL);     // 20ms中断 舵机控制
	pit_ms_init(TIM6_PIT,5,NULL);      //定时测距TOF
	pwm_set_duty(SERVO_PWM1, SERVO_DUTY(90));
    // 此处编写用户代码 例如外设初始化代码等
    while(1)
    {
//			pwm_set_duty(SERVO_PWM1, 700); 
//			system_delay_ms(1500);
//			
//		 pwm_set_duty(SERVO_PWM1, 800); 
//			system_delay_ms(1500);
//			pwm_set_duty(SERVO_PWM1, 630);
//			system_delay_ms(1500);
			
        // 此处编写需要循环执行的代码
		 if(mt9v03x_finish_flag)
		 {
            ImageProcess();
		 }
            tft180();
		 printf("%d,%d,%d,%d\n",Speed1,Speed2,Speed_Goal_l,Speed_Goal_r);
        // 此处编写需要循环执行的代码
    }
}


