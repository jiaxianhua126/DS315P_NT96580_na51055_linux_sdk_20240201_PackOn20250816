#ifndef _ALGO_ADAS_RESULT_H_
#define _ALGO_ADAS_RESULT_H_

#include "common/algo_result_comm.h"
//#include <string>
#define ALGO_ADAS_OBJ_MAX_NUM 50

typedef enum {
    SL_UNKNOWN = 0,
    SL_PLATE_05 = 1,
    SL_PLATE_10 = 2,
    SL_PLATE_15 = 3,
    SL_PLATE_20 = 4,
    SL_PLATE_25 = 5,
    SL_PLATE_30 = 6,
    SL_PLATE_35 = 7,
    SL_PLATE_40 = 8,
    SL_PLATE_50 = 9,
    SL_PLATE_60 = 10,
    SL_PLATE_70 = 11,
    SL_PLATE_80 = 12,
    SL_PLATE_90 = 13,
    SL_PLATE_100 = 14,
    SL_PLATE_110 = 15,
    SL_PLATE_120 = 16,
}AlgoAdasSliType;


typedef struct fcw_obj
{
    int         type;//识别到的物体类型
    float       score;//识别到的物体得分
    float       time_to_contact ;// 碰撞时间, time to contact, ref. mobileye paper.，单位s，靠近为正值，远离为负值。
    float       attc;// 绝对碰撞时间，单位s。
    Point2f     relative_distance ;// 相对距离，单位m,x为横向速度，y为纵向速度
    Point2f     relative_velocity ;// 相对速度，单位m/s,x为横向速度，y为纵向速度
    Box2f       bbox;//位置信息，各个数值为相对图像左上角的比例，范围0~1.
    int         has_plate; //是否检测到有效车牌的标志位
    int         plate_length; //车牌号有效位数
    char        plate_number[8]; // 车牌号 
    Box2f       plate_bbox;//车牌位置信息，各个数值为相对图像左上角的比例，范围0~1.
}AlgoAdasObject;

typedef struct
{
    int objsize;//车辆数量
    int cipv;//车辆正前方范围内车辆在objects中的索引，触发报警时报警车辆索引。
    int warn;//报警状态
    AlgoAdasObject objects[ALGO_ADAS_OBJ_MAX_NUM];
}AlgoAdasFcwResult;

typedef struct
{
    int objsize;//车辆数量
    int cipp;//车辆正前方范围内行人在objects中的索引，触发报警时报警行人索引。
    int warn;//报警状态
    AlgoAdasObject objects[ALGO_ADAS_OBJ_MAX_NUM];
}AlgoAdasPedResult;

typedef enum
{
    ALGO_ADAS_LINE_LL=0,//左边旁车道外侧车道线。
    ALGO_ADAS_LINE_L=1,//本车道左侧车道线。
    ALGO_ADAS_LINE_R=2,//本车道右侧车道线。
    ALGO_ADAS_LINE_RR=3,//右边旁车道外侧车道线。
}AlgoAdasLine;

typedef struct
{
    float a;                // 曲线参数
    float b;                // 曲线参数
    float c;                // 曲线参数
    float d;                // 曲线参数
    int min_y;              // y取值范围的最小值
    int max_y;              // y取值范围的最大值
    int type;               // 车道线类别，无车道线(0)，实线(1)，虚线(2)和其它(3)
    float curve_degree;     // 曲线的弯曲程度。
}AlgoAdasCurveLane;

typedef struct
{
    int     cred;	//置信度
    int     type;   //算法类型，0：传统算法，1深度学习算法。
    AlgoAdasLine which;//车道线位置
    float   curve;  //曲率半径，单位米
    float   distance;//车轮外侧距离车道线距离，单位m，未压线为正值，压线为负值。
    union
    {
        Point2f  point[2];//位置信息，传统算法是使用
        AlgoAdasCurveLane    lane;//曲线时计算点，深度学习算法时使用
    }laneInfo;
}AlgoAdasLdwLine;

typedef struct
{
    int  state;//0 :none;1: left 2:right
    int  lineNum;//识别到线的数量
    AlgoAdasLdwLine line[4];
    float  laneWidth;//本车道车道宽度,-1,或0无效.
    int distance_line_num;
    Point2f distance_line[6][2]; //距离线
}AlgoAdasLdwResult;

typedef struct
{
    int calib_history;
    int calib_process;//0~100 percent
    float vpx;
    float vpy;
}AlgoAdasCalibResult;

typedef enum
{
    ALGO_ADAS_WARN_TYPE_NONE=0,
    ALGO_ADAS_WARN_TYPE_FCW=1,              //前车碰撞
    ALGO_ADAS_WARN_TYPE_FDW=2,              //车距过近
    ALGO_ADAS_WARN_TYPE_FPW=3,              //行人碰撞
    ALGO_ADAS_WARN_TYPE_LDW_L=4,            //车道偏离 左偏离
    ALGO_ADAS_WARN_TYPE_LDW_R=5,            //车道偏离 右偏离
    ALGO_ADAS_WARN_TYPE_CAMERA_OCCLUSION=6, //遮挡摄像头
    ALGO_ADAS_WARN_TYPE_STOP_GO=7,          //前车起步报警
    ALGO_ADAS_WARN_TYPE_FORWARD_CAR_SLIDE=8,//前车滑车报警
    ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS=9,  //虚拟保险杠
    ALGO_ADAS_WARN_TYPE_LDW_LEFT=10,        //车道偏离,左偏离，无速度限制,用于lca融合
    ALGO_ADAS_WARN_TYPE_LDW_RIGHT=11,       //车道偏离，右偏离，无速度限制，用于lca融合
    ALGO_ADAS_WARN_TYPE_DANGER_OVERTAKE=12  //前车车辆危险变道
}AlgoAdasWarnType;

typedef struct
{
    AlgoAdasFcwResult fcw;
    AlgoAdasLdwResult ldw;
    AlgoAdasPedResult ped;
    AlgoAdasCalibResult calib;
}AlgoAdasResult;


#endif
