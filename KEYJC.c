#include "KEYJC.h"
 uint8 key1_status;
 uint8 key2_status;
 uint8 key3_status;
 uint8 key4_status;

 uint8 key1_last_status;
 uint8 key2_last_status;
 uint8 key3_last_status;
 uint8 key4_last_status;

 uint8 key1_flag;
 uint8 key2_flag;
 uint8 key3_flag;
 uint8 key4_flag;
uint8 test1, test2, test3, test4;
void KEY_scan()
{
        key1_last_status = key1_status;
        key2_last_status = key2_status;
        key3_last_status = key3_status;
        key4_last_status = key4_status;

		    // 读取当前按键状态
        key1_status = gpio_get_level(KEY1_PIN);
        key2_status = gpio_get_level(KEY2_PIN);
        key3_status = gpio_get_level(KEY3_PIN);
        key4_status = gpio_get_level(KEY4_PIN);
        
        //检测到按键按下之后  并放开置位标志位
        if(key1_status && !key1_last_status)    key1_flag = 1;
        if(key2_status && !key2_last_status)    key2_flag = 1;
        if(key3_status && !key3_last_status)    key3_flag = 1;
        if(key4_status && !key4_last_status)    key4_flag = 1;
        
        //标志位置位之后，可以使用标志位执行自己想要做的事件
        if(key1_flag)   
        {
            key1_flag = 0;//使用按键之后，应该清除标志位
            test1++;
        }
        
        if(key2_flag)   
        {
            key2_flag = 0;//使用按键之后，应该清除标志位
            test2++;
        }
        
        if(key3_flag)   
        {
            key3_flag = 0;//使用按键之后，应该清除标志位
            test3++;
        }
        
        if(key4_flag)   
        {
            key4_flag = 0;//使用按键之后，应该清除标志位
            test4++;
        }
}