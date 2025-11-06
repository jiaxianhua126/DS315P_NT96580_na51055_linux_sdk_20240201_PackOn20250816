#ifndef _ALGO_RESULT_H_
#define _ALGO_RESULT_H_


#include "common/algo_comm.h"
#include "common/algo_error.h"
#include "common/algo_result_comm.h"
#include "adas/algo_adas_result.h"
#include "rcw/algo_rcw_result.h"
typedef  enum
{
    ALGO_EXTEND_INFO_NONE=0,
    ALGO_EXTEND_INFO_PASSBACK_PIC=1,
}AlgoExtendInfo;

typedef enum {
    ALGO_EVENT_RESULT_PER_IMAGE,// 算法每一帧处理结构类型
    ALGO_EVENT_ERROR,
    ALGO_EVENT_BUTT
}AlgoEventType;

typedef  struct
{
    AlgoType type;//算法类型ADAS DMS BSD
    uint32_t algoWarnType;//预警结果标识，按位标识 dms:AlgoDmsWarnType adas:AlgoAdasWarnType ,bsd:AlgoBsdWarnType
    uint32_t algoExtendInfo;//扩展标识，包括是否回传数据标识
    union
    {
        AlgoAdasResult adasResult;
        AlgoRcwResult rcwResult;
    }algoResult;
}AlgoProcessResult ;

typedef union {
    AlgoProcessResult result;
    AlgoErrorType errorType;
}AlgoEventData;

// 算法运算结果回调函数
typedef void  (*AlgoEventCallback)(AlgoEventType eventType, const AlgoEventData* dataInfo);


typedef enum
{
    ALGO_WARN_TYPE_NONE=0,
    ALGO_WARN_TYPE_FCW=1,               //前车碰撞
    ALGO_WARN_TYPE_FDW=2,               //车距过近
    ALGO_WARN_TYPE_FPW=3,               //行人碰撞
    ALGO_WARN_TYPE_LDW_L=4,             //车道偏离 左偏离
    ALGO_WARN_TYPE_LDW_R=5,             //车道偏离 右偏离
    ALGO_WARN_TYPE_FRONT_OCCLUSION=6,   //前视 遮挡摄像头
    ALGO_WARN_TYPE_STOP_GO=7,           //前车起步报警
    ALGO_WARN_TYPE_FORWARD_CAR_SLIDE=8, //前车滑车报警
    ALGO_WARN_TYPE_VIRTUAL_BUMPERS=9,   //虚拟保险杠
    ALGO_WARN_TYPE_RCW = 10,            //后向碰撞报警
    ALGO_WARN_TYPE_LCA_LEFT_L1 = 11,    //左侧 变道辅助 报警,一级报警，左后来车
    ALGO_WARN_TYPE_LCA_RIGHT_L1 = 12,   //右侧 变道辅助 报警，一级报警，右后来车
    ALGO_WARN_TYPE_LCA_LEFT_L2 = 13,    //左侧 变道辅助 报警，二级报警，同时向左侧变道
    ALGO_WARN_TYPE_LCA_RIGHT_L2 = 14,   //右侧 变道辅助 报警，二级报警，同时向右侧变道
    ALGO_WARN_TYPE_DANGER_OVERTAKE = 15 //前车危险变道
}AlgoWarnType;

typedef struct {
    uint32_t algoWarnType;//预警结果，按位标识 见枚举 AlgoWarnType
    AlgoAdasResult adasResult;
    AlgoRcwResult rcwResult;
}AlgoFuseEventData;




#endif
