#ifndef _ALGO_RCW_RESULT_H_
#define _ALGO_RCW_RESULT_H_

#include "common/algo_result_comm.h"

#define ALGO_RCW_OBJ_MAX_NUM 50

typedef enum
{
    ALGO_RCW_LINE_LL=0,//左边旁车道外侧车道线。
    ALGO_RCW_LINE_L=1,//本车道左侧车道线。
    ALGO_RCW_LINE_R=2,//本车道右侧车道线。
    ALGO_RCW_LINE_RR=3,//右边旁车道外侧车道线。
}RcwLine;

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
}RcwCurveLane;

typedef struct
{
    int     cred;	//置信度
    int     type;   //算法类型，0：传统算法，1深度学习算法。
    RcwLine which;//车道线位置
    float   curve;  //曲率半径，单位米
    float   distance;//车轮外侧距离车道线距离，单位m，未压线为正值，压线为负值。
    union
    {
        Point2f  point[2];//位置信息，传统算法是使用
        RcwCurveLane    lane;//曲线时计算点，深度学习算法时使用
    }laneInfo;
}RcwLdwLine;

typedef struct
{
    int  state;//0 :none;1: left 2:right
    int  lineNum;//识别到线的数量
    RcwLdwLine line[4];
    float  laneWidth;//本车道车道宽度,-1,或0无效.
    int distance_line_num;
    Point2f distance_line[6][2]; //距离线
}RcwLdwResult;

typedef enum
{
    ALGO_RCW_WARN_TYPE_NONE=0,
    ALGO_RCW_WARN_TYPE_RCW_REAR=1,      //后向碰撞
    ALGO_RCW_WARN_TYPE_RCW_PRE=2,       //后向预碰撞
    ALGO_RCW_WARN_TYPE_LCA_LEFT=3,      //一级报警，左后来车
    ALGO_RCW_WARN_TYPE_LCA_RIGHT=4,     //一级报警，右后来车
}AlgoRcwWarnType;


typedef struct rcw_obj
{
    int         type;//识别到的物体类型
    float       score;//识别到的物体得分
    float       time_to_contact ;// 碰撞时间, time to contact, ref. mobileye paper.，单位s，靠近为正值，远离为负值。
    float       attc;// 绝对碰撞时间，单位s。
    Point2f     relative_distance ;// 相对距离，单位m,x为横向速度，y为纵向速度
    Point2f     relative_velocity ;// 相对速度，单位m/s,x为横向速度，y为纵向速度
    Box2f       bbox;//位置信息，各个数值为相对图像左上角的比例，范围0~1.
    int         has_plate; //是否检测到有效车牌的标志位: 0 该车辆没有检测车牌，1 该车辆检测到了车牌
    int         plate_length; //车牌号有效位数
    char        plate_number[8]; // 车牌号
    Box2f       plate_bbox;//车牌位置信息，各个数值为相对图像左上角的比例，范围0~1.
}AlgoRcwObject;

typedef struct
{
    int calib_history;
    int calib_process;//0~100 percent
    float vpx;
    float vpy;
}AlgoRcwCalibResult;

typedef struct
{
    int objsize;//车辆数量
    int cipv;   //车辆正后方范围内车辆在objects中的索引，触发报警时报警车辆索引。
    int lipv;   //车辆左后方后方范围内车辆在objects中的索引，触发报警时报警车辆索引。
    int ripv;   //车辆右后方范围内车辆在objects中的索引，触发报警时报警车辆索引。
    int warn;   //报警状态
    AlgoRcwObject objects[ALGO_RCW_OBJ_MAX_NUM];
}AlgoRcwCarResult;
//变道辅助和正后方车距预警的信息
typedef struct {
    RcwLdwResult line;
    AlgoRcwCarResult rear;
    AlgoRcwCalibResult calib;
    int failure_level; //算法失效等级，0：正常，1:部分失效，2:完全失效
}AlgoRcwResult;


#endif
