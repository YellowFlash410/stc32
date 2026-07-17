#ifndef __camer_H_
#define __camer_H_
#include "zf_common_headfile.h"
//图像线的特征量
#define ImageSensorMid 39                    //图像屏幕中点
#define LimitL(L) (L = ((L < 1) ? 1 : L))    //限制幅度
#define LimitH(H) (H = ((H > 78) ? 78 : H))  //限制幅度
#define whilepoint_protect 50
//图像显示的大小
#define LCDH 60    //压缩后的图像高度
#define LCDW 80    //压缩后的图像宽度
#define uLCDH 120                         //用于图像显示的图像高度
#define uLCDW 160                         //用于图像显示的图像宽度
//图像数组
extern uint8 Image_Use[LCDH][LCDW];          //灰度图像
extern uint8 Pixle[LCDH][LCDW];              //二值化图像
#define GrayScale 256
//********道路类型************************************************************************
typedef enum {
  Normol,       //无任何特征    
  Straight,     ////直道
  Ramp,         //坡道
  LeftCirque,   ////左圆环
  RightCirque,  ////右圆环
  Cross_ture,    //十字
  Banmaxian,   //斑马线
} RoadType_e;
//********速度值类型*******************************************************
typedef struct {
  float nowspeed;     // pulse表示nowspeed
  int expectspeed;    // speed表示expectspeed（没用）
  float Length;       //走过路程  
  int MinSpeed;             //最低速度
  int MaxSpeed;             //最高速度
} SpeedDatatypedef;
//*****************图像数据状态类型***************************************************
//****************************************************************************************
typedef struct {
  //图像信息
	 int TowPoint_True;        //实际比较点           
  int TowPoint;             //初始比较点           给定前瞻
  int Det_True;             //由GetDet()函数解算出来的平均图像偏差
  int Det_all;              //图像的近端到远端的总偏差
  float Det_all_k;          //斜率
  uint8 Threshold;          //二值化阈值
  uint32 Threshold_static;  //二值化静态下限
  uint8 Threshold_detach;   //阳光算法分割阈值
  uint8 MiddleLine;         //屏幕中心
  uint8 Left_Line;          //左边丢边数
  uint8 Right_Line;         //右边丢边数
  uint8 OFFLine;            //图像顶边
  uint8 WhiteLine;          //双边丢边数

  //元素类型
  RoadType_e Road_type;  //元素类型
  
  //****圆环***（只用了圆环结束）
  uint8 IsCinqueOutIn;  //进出圆环
  uint8 CirquePass;     //圆环中
  uint8 CirqueOut;      //出圆环
  uint8 CirqueOff;      //圆环结束

  //左右手法则扫线数据
  int16 WhiteLine_L;        //左边丢线数
  int16 WhiteLine_R;        //右边丢线数
  int16 OFFLineBoundary;   //八领域截止行

  int Pass_Lenth;       //入环距离  用于防抖（没用）
     /****圆环***/
  int Cirque1lenth;        //tly1
  int Cirque2lenth;        //tly2 
  int Cross_Lenth;  // 270°转过之后一般是十字路口   作为三岔口的消抖
  int Cross_ture_lenth;      //没用
  int Sita;//据此判断在过去一段路程中转过多少角度    //没用
  int pansancha_Lenth;       //没用

  //车库
  int Barn_Lenth;  //入库停止距离
  //保护
  //  int Stop_lenth;  //出界保护放误判距离
  //方差
  int variance;  //直道检测阈值方差
  int straight_acc;  //直道加速标志位
  int  variance_acc;    //用于加速的阈值方差
//  int ramptestlenth;//坡道检测间隔
//  int rukuwait_lenth;
//  int rukuwait_flag;
//  int newblue_flag;
} ImageStatustypedef;
//*******************************************************************
typedef struct {
  /*左右边边界标志    T为正常跳变边    W为无边   H为障碍类多跳边的内边*/
  uint8 IsRightFind;      //右边有边标志
  uint8 IsLeftFind;       //左边有边标志
  uint8 isBlackFind;      //三叉边
  int Wide;               //边界宽度
  int LeftBorder;         //左边界
  int RightBorder;        //右边界
  int close_LeftBorder;   //靠边边界
  int close_RightBorder;  //靠边边界
//  int opp_LeftBorder;     //反向边界
//  int opp_RightBorder;    //反向边界
  int Center;             //中线
  int RightTemp;          //右边临时值
  int LeftTemp;           //左边临时值
  int CenterTemp;         //中线临时值
//  int Black_Point;        //单行黑点数量

  //左右手法则扫线数据            目前没用 
  int LeftBoundary_First;  //左边界 保存第一次数据
  int RightBoundary_First; //右边界 保存第一次数据
  int LeftBoundary;        //左边界 保存最后一次数据
  int RightBoundary;       //右边界 保存最后一次数据
}ImageDealDatatypedef;
//**********跳变点********************************************************************
//************************************************************************************
typedef struct {
  int point;
  uint8 type;
} JumpPointtypedef;
//***********************圆环用的**************************
typedef struct {
//    int16 Bend_Road;                            /*0 :无               1 :右弯道     2 :左弯道*/
    int16 image_element_rings;                  /*0 :无圆环          1 :左圆环       2 :右圆环*/
    int16 ring_big_small;                       /*0:无                     1 :大圆环       2 :小圆环*/
    int16 image_element_rings_flag;             /*圆环进程*/
//    int16 straight_long;                        /*长直道标志位*/
//    int16 Garage_Location;                      /*0 :无车库          1 :左车库       2 :右车库*/
//    int16 Zebra_Flag;                           /*0 :无斑马线       1 左车库       2 :右车库*/
//    int16 Ramp;                                  /*0 :无坡道          1：坡道*/
//    int16 RoadBlock_Flag;                        /*0 :无路障            1 :路障*/
//    int16 Out_Road;                               /*0 :无断路      1 :断路*/
} ImageFlagtypedef;
//********************************************************************************
//*******************速度参数等*************************************************8888
typedef struct{
//  uint8 SteerOK;      //舵机启动标志
//  uint8 CameraOK;     //摄像头启动显示标志
//  uint8 OldCameraOK;  //灰度传输标志
//  uint8 MotorOK;      //电机开关
  uint8 Point;        //赛道实际中心
//  uint8 UpdataOK;     //数据更新
  uint8 Stop;         //停止标志
//  uint8 GO_OK;        //冲冲冲
//  int Model;          //车辆模式
  //图像参数
//  int OutCicle_line;  //出环判断图像截止行  越大出环判断越严格越晚
//  int L_T_R_W;  // 出环左有边右无边数量  越大出环结束越严格
//  int Circleoff_offline;  //看到远处的距离判断出环结束  越小越严格
//  int CircleP;            //环内P
//***************下面没啥用************************
  //小圆环
  int circles_pl;
  int circles_pr;
  int circles_off_lenth;//小圆环出环防误判距离

   //中圆环
  int circlem_pl;
  int circlem_pr;
  int circlem_off_lenth;//小圆环出环防误判距离

   //大圆环
  int circlel_pl;
  int circlel_pr;
  int circlel_off_lenth;//小圆环出环防误判距离
  int clrcle_priority[3];//圆环类型
  int clrcle_num;// 在第几个圆环


 // int circle_kin;//入环补线半径
 // float circle_kout;//出环补线斜率
  //int circle_max_ang;//环内大叫限幅
  //直道
//  float straight_p;//直道P
//  float straight_d;//直道D
  int   straighet_towpoint;//直道前瞻
//  int debug_lenth;//调试距离

  //摄像头配置
  int exp_time; //曝光时间
//  int mtv_lroffset;//摄像头左右偏置
//  int mtv_gain;//摄像头增益

//  int ramp_lenth_start;//坡道距离
  int barn_lenth;//圆环距离
//  int outbent_acc;//出弯加速
//  int rounds; // 圈数
//  int speed_per_round; // 每圈减速多少
  SpeedDatatypedef SpeedData;
} SystemDatatypdef;
//**********************************************************
//*********************************************************************************
extern ImageStatustypedef ImageStatus;   //图像的全局变量
extern ImageDealDatatypedef ImageDeal[60];  //记录单行的信息（图像处理）
extern JumpPointtypedef JumpPoint[2];  
extern SystemDatatypdef SystemData;
extern ImageFlagtypedef ImageFlag;
extern uint8 Stop_car_Flag;
void compressimage();     //压缩图像函数
int Limit(int num, int numH, int numL);//限制函数
uint8 Threshold_deal(uint8* image,uint16 col,uint16 row,uint32 pixel_threshold);//大津法求阈值
void Get01change_dajin();  //大津法二值化函数
void Pixle_Filter();       //像素滤波
//画底边的线，静态存储，不声明
//画所有的边线
void GetJumpPointFromDet(uint8* p,uint8 type,int L,int H,JumpPointtypedef* Q);//找跳变点，拐点
void Search_Bottom_Line_OTSU(uint8 imageInput[LCDH][LCDW], uint8 Row, uint8 Col, uint8 Bottonline);//上交开源
void Search_Left_and_Right_Lines(uint8 imageInput[LCDH][LCDW], uint8 Row, uint8 Col, uint8 Bottonline);//上交开源
void Straightacc_Test(void);//直道检测并加速
void Ramp_Test();               //坡道检测
void Cross_Test2();                 //十字路口检测
void Element_Judgment_Right_Rings();//右圆环判断
void Element_Handle_Right_Rings();   //右圆环处理（再次判断）
void Element_Judgment_Left_Rings();  //左圆环判断
void Element_Handle_Left_Rings();     //左圆环处理
void Element_Test(void);      //元素检测
void Element_Handle();        //元素处理（圆环）

//void Stop_Test3();              //防出界
void GetDet();               //车眼睛状态（返回偏差）
uint8 banmaxian(void);
void ImageProcess(void);
#endif