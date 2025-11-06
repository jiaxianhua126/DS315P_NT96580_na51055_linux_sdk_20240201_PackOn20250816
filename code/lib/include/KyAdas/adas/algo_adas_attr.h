#ifndef _ALGO_ADAS_ATTR_H_
#define _ALGO_ADAS_ATTR_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <time.h>
#include "common/algo_comm.h"

//ADAS算法功能枚举，前车碰撞FCW、车道偏离LDW、行人PED、限速牌SLI、摄像头遮挡OCCLUSION,红绿灯，斑马线
typedef enum
{
    ALGO_ADAS_MANAGER=0,
    ALGO_ADAS_FCW=1,
    ALGO_ADAS_LDW=2,
    ALGO_ADAS_PED=3,
    ALGO_ADAS_OCCLUSION=4,
    ALGO_ADAS_STGO=5,
    ALGO_ADAS_VIR_BUMPER=6,
    ALGO_ADAS_DANGER_OVERTAKE=7,
    ALGO_ADAS_LCA=8,
}AlgoAdasType;

#define ALGO_ATTR_ADAS_BASE_ID              ALGO_ATTR_VAL(ALGO_TYPE_ADAS,ALGO_ADAS_MANAGER,0) //(0x1000000)，ADAS属性命令标识符起始值

#define ALGO_INVOKE_CMD_ADAS_BASE_ID        ALGO_INVOKE_CMD_VAL(ALGO_TYPE_ADAS,ALGO_ADAS_MANAGER,ALGO_INVOKE_CMD_FLAG)//0x1004000,ADAS扩展命令标识符起始值

#define ALGO_PROCESS_CMD_ADAS_BASE_ID       ALGO_PROCESS_CMD_VAL(ALGO_TYPE_ADAS,ALGO_ADAS_MANAGER,ALGO_PROCESS_CMD_FLAG)//0x1008000,ADAS处理命令标识符起始值

/*
*   下列为ADAS 各个功能属性命令唯一标识符的起始值，ALGO_ATTR_VAL（算法类型，功能类型，属性）
*/

#define ALGO_ATTR_ADAS_FCW_BASE_ID              ALGO_ATTR_VAL(ALGO_TYPE_ADAS,ALGO_ADAS_FCW,0)//(0x1010000)

#define ALGO_ATTR_ADAS_LDW_BASE_ID              ALGO_ATTR_VAL(ALGO_TYPE_ADAS,ALGO_ADAS_LDW,0)//(0x1020000)

#define ALGO_ATTR_ADAS_PED_BASE_ID              ALGO_ATTR_VAL(ALGO_TYPE_ADAS,ALGO_ADAS_PED,0)//(0x1030000)

#define ALGO_ATTR_ADAS_OCCLUSION_BASE_ID        ALGO_ATTR_VAL(ALGO_TYPE_ADAS,ALGO_ADAS_OCCLUSION,0)//(0x1040000)

#define ALGO_ATTR_ADAS_STGO_BASE_ID             ALGO_ATTR_VAL(ALGO_TYPE_ADAS,ALGO_ADAS_STGO,0)//(0x1050000)

#define ALGO_ATTR_ADAS_VIRBUMPER_BASE_ID        ALGO_ATTR_VAL(ALGO_TYPE_ADAS,ALGO_ADAS_VIR_BUMPER,0)//(0x1060000)

#define ALGO_ATTR_ADAS_DANGEROVERTAK_BASE_ID    ALGO_ATTR_VAL(ALGO_TYPE_ADAS,ALGO_ADAS_DANGER_OVERTAKE,0)//(0x1070000)

#define ALGO_ATTR_ADAS_LCA_BASE_ID             ALGO_ATTR_VAL(ALGO_TYPE_ADAS,ALGO_ADAS_LCA,0)//(0x1080000)
typedef enum {
    /*
    *   名称：ADAS 功能使能
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中enable，默认值：1,可调值：0,1
    */
    ALGO_ATTR_ADAS_ENABLE    =ALGO_ATTR_ADAS_BASE_ID,
    
    /*
    *   名称：灭点位置
	*   属性：可获取、可设置
	*	参数：AlgoAdasAttr.vp，自动标定时无需手动设置好
    */
    ALGO_ATTR_ADAS_CALIB_VP,
    
    /*
    *   名称：摄像头高度
	*   属性：可获取、可设置
	*	参数：AlgoAdasAttr 中cameraHeight，单位mm，自动标定时无需手动设置
    */
    ALGO_ATTR_ADAS_CALIB_CAMERA_HEIGHT,

    /*
    *   名称：摄像头与车辆的位置参数
	*   属性：可获取、可设置
	*	参数：AlgoAdasAttr 中vehicleInfo，单位mm，默认值
    *	cameraToBumper 1500;
    *   cameraToLeftWheel 900;
    *   cameraToRightWheel 900;
    *   cameraToFrontAxle 0;
    */
    ALGO_ATTR_ADAS_CALIB_VEHICLE_PARAM,
    
    /*
    *   名称：自动标定 功能使能
	*   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中enable,默认值:1,可调值：0,1,传入值为1时会立即启动自动标定
    */
    ALGO_ATTR_ADAS_CALIB_AUTO_ENABLE,
    
    /*
    *   名称：自动标定 启动速度
	*   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中speedThreshold，默认值:20,可调值：[10,60]，单位秒km/h
    */
    ALGO_ATTR_ADAS_CALIB_AUTO_SPEED,
    
    /*
    *   名称：自动标定时长（帧数）
	*   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中autoCalibTime,默认值：480帧,可调值：>100帧
    */
    ALGO_ATTR_ADAS_CALIB_AUTO_TIME,

    /*
    *   名称：自动标定方式（预留，暂未开放，默认每次启动运行）
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中autoCalibMode
    *        1:设备第一次启动运行
    *        2:设备每次启动运行
    */
    ALGO_ATTR_ADAS_CALIB_AUTO_MODE,

    /*
    *   名称：清除标定历史，并立即进行自动标定，标定完成前不输出报警
    *   属性：仅可设置
    *	参数：需传入自动标定启动速度，仅本次标定使用：AlgoAdasAttr 中 speedThreshold，单位km/h
    */
    ALGO_ATTR_ADAS_RM_HISTORY_AND_RE_AUTO_CALIB_ATONCE,

    /*
    *   名称：前车碰撞 功能使能
	*   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中enable,默认值：1,可调值：0,1
    */
    ALGO_ATTR_ADAS_FCW_ENABLE=ALGO_ATTR_ADAS_FCW_BASE_ID,

    /*
    *   名称：前车碰撞 预警速度
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中speedThreshold,默认值：30,可调值:[10,60]，单位秒km/h
    */
    ALGO_ATTR_ADAS_FCW_WARN_SPEED,

    /*
    *   名称：前车碰撞 预警灵敏度
	*   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中senType ,默认值：中，可设置 高，中，低三个灵敏度
    *	高灵敏度ttc 3.5s；
    *	中灵敏度ttc 2.7s；
    *	低灵敏度ttc1.8s，并且gps速度减速明显时抑制报警；
    */
    ALGO_ATTR_ADAS_FCW_SENSITIVITY,

    /*
    *   名称：车距过近 功能使能
	*   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中enable，默认值：1,可调值：0,1
    */
    ALGO_ATTR_ADAS_DISCLOSE_ENABLE,

    /*
    *   名称：车距过近 预警速度
	*   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中speedThreshold，默认值：30,可调值：[5,60]，单位秒km/h
    */
    ALGO_ATTR_ADAS_DISCLOSE_WARN_SPEED,

    /*
    *   名称：车距过近 预警灵敏度
	*   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中senType ,默认值：中，可设置 高，中，低三个灵敏度
    *	高灵敏度absttc 1.2s；
    *	中灵敏度absttc 0.7s；
    *	低灵敏度absttc 0.5s
    */
    ALGO_ATTR_ADAS_DISCLOSE_SENSITIVITY,

    /*
    *   名称：车道偏离 功能使能
	*   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中enable,默认值：1,可调值：0,1
    */
    ALGO_ATTR_ADAS_LDW_ENABLE=ALGO_ATTR_ADAS_LDW_BASE_ID,

    /*
    *   名称：车道偏离 预警速度
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中speedThreshold，默认值：60,可调值： [30,80]，单位秒km/h
    */
    ALGO_ATTR_ADAS_LDW_WARN_SPEED,

    /*
    *   名称：车道偏离 预警灵敏度
	*   属性：可获取、可设置
	*	参数：AlgoAdasAttr 中senType ,默认值：中，可设置 高，中，低三个灵敏度
    *	高灵敏度，车轮与车道线的距离 0.15米,摆正时间 0.7s；
    *	中灵敏度，车轮与车道线的距离0米，摆正时间 1s；
    *	低灵敏度，车轮与车道线的距离-0.15米，摆正时间 1.5s；
    */
    ALGO_ATTR_ADAS_LDW_SENSITIVITY,

    /*
    *   名称：行人预警 功能使能
	*   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中enable,默认值：1,可调值：0,1
    */
    ALGO_ATTR_ADAS_PED_ENABLE=ALGO_ATTR_ADAS_PED_BASE_ID,

    /*
    *   名称：行人预警最小速度，大于该值输出报警
	*   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中 speedThreshold，默认值：10,可调值：[5,40]，单位秒km/h
    */
    ALGO_ATTR_ADAS_PED_WARN_SPEED,

    /*
    *   名称：行人预警最大速度，小于该值输出报警
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中 speedThreshold，默认值：80,可调值：[40,100]，单位秒km/h
    */
    ALGO_ATTR_ADAS_PED_WARN_MAX_SPEED,

    /*
    *   名称：行人预警灵敏度
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中senType ,默认值：中，可设置 高，中，低三个灵敏度
    *	高灵敏度 absttc 1.6s，报警区域车轮外侧0.1米；
    *	中灵敏度 absttc 1.3s，报警区域车轮外侧0米；
    *	低灵敏度 absttc 1.0s，报警区域车轮外侧-0.1米
    */
    ALGO_ATTR_ADAS_PED_SENSITIVITY,

    /*
    *   名称：摄像头遮挡使能（未适配，暂不开放）
	*   属性：可获取、可设置
	*	参数：AlgoAdasAttr 中 enable
    */
    ALGO_ATTR_ADAS_OCCLUSION_ENABLE=ALGO_ATTR_ADAS_OCCLUSION_BASE_ID,

    /*
    *   名称：镜头遮挡预警速度（未适配，暂不开放）
	*   属性：可获取、可设置
	*	参数：AlgoAdasAttr 中 speedThreshold
    */
    ALGO_ATTR_ADAS_OCCLUSION_WARN_SPEED,

    /*
    *   名称：前车起步,前车溜车 功能使能
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中enable,默认值：1,可调值：0,1
    */
    ALGO_ATTR_ADAS_STGO_ENABLE=ALGO_ATTR_ADAS_STGO_BASE_ID,

    /*
    *   名称：前车起步，前车溜车，报警最大速度，小于等于该值输出报警
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中 speedThreshold，默认值：1，可调值：[0,5]，单位km/h
    */
    ALGO_ATTR_ADAS_STGO_WARN_MAX_SPEED,

    /*
    *   名称：前车起步，前车溜车 预警灵敏度
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中senType ,默认值：中，可设置 高，中，低三个灵敏度
    *	高灵敏度 停车4s功能启用，采用gps速度判断停车，前车远离0.6米并且远离0.7s后触发报警；
    *	中灵敏度 停车5s功能启用，采用gps速度判断停车，前车远离1米并且远离1s后触发报警；
    *	低灵敏度 停车5s功能启用，采用三轴判断停车，前车远离2米并且远离2.5s后触发报警；
    */
    ALGO_ATTR_ADAS_STGO_SENSITIVITY,

    /*
    *   名称：虚拟保险杠  使能
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中 enable，默认值：1,可调值：0,1
    */
    ALGO_ATTR_ADAS_VIRBUMPER_ENABLE=ALGO_ATTR_ADAS_VIRBUMPER_BASE_ID,

    /*
    *   名称：虚拟保险杠报警速度,大于等于该值输出报警
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中 speedThreshold，默认值：1，可调值：[0,10]，单位km/h
    */
    ALGO_ATTR_ADAS_VIRBUMPER_WARN_SPEED,

    /*
    *   名称：虚拟保险杠报警最大速度,小于等于该值输出报警
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中 speedThreshold，默认值：30，可调值：[10,60]，单位km/h
    */
    ALGO_ATTR_ADAS_VIRBUMPER_WARN_MAX_SPEED,

    /*
    *   名称：虚拟保险杠 预警灵敏度
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中senType ,默认值：中，可设置 高，中，低三个灵敏度
    *	高灵敏度 报警距离3-5米，并且相互靠近；
    *	中灵敏度 报警距离2-4米，并且相互靠近；
    *	低灵敏度 报警距离1-3米，并且相互靠近;
    */
    ALGO_ATTR_ADAS_VIRBUMPER_SENSITIVITY,

    /*
    *   名称：前车危险变道 功能使能
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中 enable，默认值：1,可调值：0,1
    */
    ALGO_ATTR_ADAS_DANGER_OVERTAKE_ENABLE=ALGO_ATTR_ADAS_DANGEROVERTAK_BASE_ID,

    /*
    *   名称：前车危险变道 启动速度
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中 speedThreshold，默认值：30，可调值：[10,60]，单位km/h
    */
    ALGO_ATTR_ADAS_DANGER_OVERTAKE_WARN_SPEED,

    /*
    *   名称：前车危险变道 预警灵敏度
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中senType ,默认值：中，可设置 高，中，低三个灵敏度
    *	高灵敏度 absttc 1.2s；
    *	中灵敏度 absttc 0.7s；
    *	低灵敏度 absttc 0.5s;
    */
    ALGO_ATTR_ADAS_DANGER_OVERTAKE_SENSITIVITY,

    /*
    *   名称：lca（变道） 功能使能
    *   属性：可获取、可设置
    *	参数：参数：AlgoAdasAttr 中 enable，默认值：1,可调值：0,1，lca(亮灯)的功能必须启用，否则无效
    */
    ALGO_ATTR_ADAS_LCA_ENABLE = ALGO_ATTR_ADAS_LCA_BASE_ID,

    /*
    *   名称：lca（变道） 启动速度
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中 speedThreshold，默认值：30，可调值：[10,120]，单位km/h，该值必须大于 lca（亮灯）的速度，否则无效
    */
    ALGO_ATTR_ADAS_LCA_WARN_SPEED,

    /*
    *   名称：lca（变道） 预警灵敏度
    *   属性：可获取、可设置
    *	参数：AlgoAdasAttr 中senType ,默认值：中，可设置 高，中，低三个灵敏度
    *	高灵敏度 变道冷却时间0.7s，车轮与车道线距离0.15米；
    *	中灵敏度 变道冷却时间1s，车轮与车道线距离0.1米；
    *	低灵敏度 变道冷却时间1.5s，车轮与车道线距离-0.1米;
    */
    ALGO_ATTR_ADAS_LCA_SENSITIVITY,

}AlgoAdasAttrType;

/*
*   名称：ADAS 标定 灭点位置。
*   属性：可获取、可设置。
*	参数：valid：获取灭点时，1 为有效，0位无效。
*         vpX：灭点x ，以图像左上角为原点,相对于标定图像分辨率比例 vpX = x/imageWidth ,范围0~1;
*         vpY：灭点y ，以图像左上角为原点，相对于标定图像分辨率比例 vpY = y/imageHeight,范围0~1;
*/
typedef struct
{
    int     valid;
    float   vpX;
    float   vpY;
}AlgoAdasVp;

/*
*   名称：ADAS 标定，摄像头与车辆的相对位置信息。
*   属性：可获取、可设置。
*	参数： cameraToBumper :摄像头与前保险杠的距离 单位 mm。
*       cameraToLeftWheel :摄像头与左车轮的距离 单位mm。
*       cameraToRightWheel :摄像头与右车轮的距离 单位mm。
*       cameraToFrontAxle :摄像头与车轴的距离 单位mm。
*/
typedef struct
{
    float cameraToBumper ;
    float cameraToLeftWheel ;
    float cameraToRightWheel ;
    float cameraToFrontAxle ;
}AlgoAdasVehicleInfo;

typedef union
{
    int enable;
    int speedThreshold;
    int autoCalibTime;
    int autoCalibMode;
    float cameraHeight;
    AlgoAdasVp vp;
    AlgoAdasVehicleInfo vehicleInfo;
    AlgoSenType senType; //高灵敏度 0；中灵敏度 1；低灵敏度 2，详见 algo_comm.h头文件
}AlgoAdasAttr;


// ADAS 扩展命令标识符 枚举
typedef enum
{
    ALGO_ADAS_INVOKE_CMD_BASE =ALGO_INVOKE_CMD_ADAS_BASE_ID,
    ALGO_ADAS_INVOKE_CMD_SPEED,//车辆速度，
    ALGO_ADAS_INVOKE_CMD_TURNLIGTH,//车辆转向
    ALGO_ADAS_INVOKE_CMD_ACC,//设备加速度传感器
    ALGO_ADAS_INVOKE_CMD_GYROSCOPE,// 陀螺仪
    ALGO_ADAS_INVOKE_CMD_LOCATIONINFO,//定位信息
    ALGO_ADAS_INVOKE_CMD_BRAKE,// 刹车信息
}AlgoAdasInvokeCmd;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
