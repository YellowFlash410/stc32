#include "Fuzzy.h"
#include "camer.h"
#include "motor.h"
#include "INIT.h"
#include "steer.h"
extern PID_Datatypedef SteerPIDdata;    //舵机的PID参数
#define H_Min   2
void Data_Settings(void)           //结构体赋值
{
  //图像参数
  
  ImageStatus.MiddleLine = 39;//中线
  ImageStatus.Det_all_k = 0.7;  //待定自动补线斜率
  ImageStatus.CirquePass = 'F';//是否通过环岛
  ImageStatus.IsCinqueOutIn = 'F';//是否处于环岛出入口
  ImageStatus.CirqueOut = 'F';//是否正在出环岛
  ImageStatus.CirqueOff = 'F';//环岛逻辑关闭/结束标志
  ImageStatus.straight_acc = 0;//用于检测是否处于直道，如果是直道，速度会越来越块

  ImageStatus.TowPoint =24;           //前瞻 
  ImageStatus.Threshold_static = 60;   //静态阈值  40-80
  ImageStatus.Threshold_detach = 170;  //阳光算法  亮斑分离140-220
  ImageStatus.variance_acc = 21;       //直道检测
  SystemData.clrcle_num=0;
//  ImageStatus.newblue_flag=0;
//  SystemData.Stop = 1;                 //启动标志位

  /**位置式pid参数**/
//  SteerPIDdata.P = 5;
//  SteerPIDdata.I = 0.0;
//  SteerPIDdata.D = 8;

}