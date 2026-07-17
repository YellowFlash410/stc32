/*
 * tft180.c
 *
 *  Created on: 2024年3月4日
 *      Author: xiaoming
 */

#include "camer.h"
#include "INIT.h"
#include "fuzzy.h"
#include "motor.h"
#include "steer.h"
#include "tft180.h"


extern int16 speed1;
extern int16 speed2;
extern int16 Speed_Goal_l;
extern int16 Speed_Goal_r;
extern int Speed_Goal;
int jishu=0;
extern int run_flag;
extern float variance_acc;


void drawleftline()
{
    int x;
	int i;
     for(i=0;i<=59;i+=1)
     {
        x=ImageDeal[i].LeftBorder;
        tft180_draw_point(x,i,RGB565_RED);
     }
}

void drawrightline()
{
    int x;
	int i;
      for( i=0;i<=59;i+=1)
      {
          x=ImageDeal[i].RightBorder;
          tft180_draw_point(x,i,RGB565_RED);
      }
}

void drawcenterline()
{
    int x;
	int i;
     for( i=0;i<=58;i+=1)
     {
//        x=ImageDeal[i].Center;
       // x = (ImageDeal[i].RightBorder + ImageDeal[i].LeftBorder)/2;
         x = (ImageDeal[i].RightBorder - ImageDeal[i].LeftBorder)/2;
        tft180_draw_point(x,i,RGB565_BLUE);
         
         if(jishu<=58)
         {
          wireless_uart_send_byte(x);
          jishu++;
         }

     }
}

//void draw_math()
//{
//    int x;
//    int j=0;
//    int y =0;
//	int i;
//    for( i =4;i<=58;i++)
//    {
//            x = (ImageDeal[i].RightBorder - ImageDeal[i].LeftBorder)/2;
//            tft180_show_int(j,y,x,2);
//            j+=15;
//            if(j>100){j = 0;y+=15;}
//    }
//}
void drawoffline()
{
    int x;
	int i;
     for(i=0;i<=79;i+=1)
     {
         x=ImageStatus.OFFLine;
         tft180_draw_point(i,x,RGB565_RED);
     }
}

void drawtowpointUP()
{
    int x;
	int i;
      for( i=0;i<=79;i+=1)
      {
          x=ImageStatus.TowPoint-5;
          tft180_draw_point(i,x,RGB565_CYAN);
      }
}

void drawtowpointDOWN()
{
      int x;
	int i;
      for(i=0;i<=79;i+=1)
      {
          x=ImageStatus.TowPoint+5;
          tft180_draw_point(i,x,RGB565_CYAN);
      }
}
void tft180()
{  //  tft180_displayimage032_zoom(Image_Use[0], LCDW, LCDH, LCDW, LCDH);    //灰度图像
   // tft180_displayimage03x(mt9v03x_image[0], 94, 60);
//    if(run_flag == 0)
//              {
    tft180_show_gray_image(0,0,Pixle[0],LCDW,LCDH,LCDW,LCDH,1);             //二值化图像

   //  tft180_displayimage032_zoom(mt9v03x_image_dvp[0], 188, 120, 160, 120);    //灰度图像
    drawleftline();     //画左边线
    drawrightline();    //画右边线
    drawcenterline();   //画中线
//    //draw_math();
    drawoffline();      //画图像顶边
    drawtowpointUP();   //画前瞻范围上线
    drawtowpointDOWN(); //画前瞻范围下线
//              }
//    tft180_show_string(0,63,"chazhi");
//    tft180_show_int8(30,63,ImageStatus.Det_True-39);
//    tft180_show_string(0,75,"motor1");
//    tft180_show_int8(30,75,speed1);
//		tft180_show_string(30,80,"motor2");	
//		tft180_show_int8(30,80,speed2);	
//			tft180_show_string(40,80,"motor1mb");	
//			tft180_show_int8(40,80,Speed_Goal_l);
//					tft180_show_string(50,80,"motor2mb");	
//			tft180_show_int8(50,80,Speed_Goal_r);			
//    tft180_show_string(0,105,"ptl");
//    tft180_show_int8(30,105,ImageStatus.Left_Line);         
//    tft180_show_string(0,120,"ptr");
//    tft180_show_int8(30,120,ImageStatus.Right_Line);       
//    tft180_show_string(0,135,"cir");
//    tft180_show_int8(30,135,ImageFlag.image_element_rings_flag);
//    tft180_show_string(90,75,"type");
//    tft180_show_int8(80,75, ImageStatus.Road_type);        

}