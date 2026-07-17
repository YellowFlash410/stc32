#include "INIT.h"
#include "KEYJC.h"
void KEYGPIO_init()
{
	gpio_init(KEY1_PIN, GPI, 1, GPI_PULL_UP);
	gpio_init(KEY2_PIN, GPI, 1, GPI_PULL_UP);
	gpio_init(KEY3_PIN, GPI, 1, GPI_PULL_UP);
	gpio_init(KEY4_PIN, GPI, 1, GPI_PULL_UP);

    gpio_init(SWITCH1_PIN, GPI, 1, GPI_PULL_UP);
    gpio_init(SWITCH2_PIN, GPI, 1, GPI_PULL_UP);
}
void BUZZER_init()
{
	gpio_init(BUZZER_PIN, GPO, 1, GPO_PUSH_PULL);
}
void JG_init()
{
	gpio_init(JG_HEAD_PIN, GPO, 1, GPO_PUSH_PULL);
}
void DJLED_init()
{
	 gpio_init(LED, GPO, GPIO_HIGH, GPO_PUSH_PULL);     // GPIO 初始化为输出 默认上拉输出高
}
void servo_init()
{
	pwm_init(SERVO_PWM1, SERVO_FREQ, 0);
	//例子pwm_set_duty(PWME_CH1P_PA0, SERVO_DUTY(30));
}
void DT_INIT()
{
    pwm_init(PWM_1, FREQ, 0);                   // PWM 通道1 初始化频率 50Hz  占空比初始为 0
    pwm_init(PWM_2, FREQ, 0);                   // PWM 通道2 初始化频率 50Hz  占空比初始为 0
    pwm_init(PWM_3, FREQ, 0);                   // PWM 通道2 初始化频率 50Hz  占空比初始为 0
    pwm_init(PWM_4, FREQ, 0);                   // PWM 通道2 初始化频率 50Hz  占空比初始为 0	
}
