#ifndef _ALGO_RCW_ATTR_H_
#define _ALGO_RCW_ATTR_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <time.h>
#include "common/algo_comm.h"
#include "common/algo_result_comm.h"

//RCW算法功能枚举
typedef enum
{
    ALGO_RCW_MANAGER=0,
    ALGO_RCW_RCW=1,
    ALGO_RCW_LCA=2,
}AlgoRcwType;

#define ALGO_ATTR_RCW_BASE_ID              ALGO_ATTR_VAL(ALGO_TYPE_RCW,ALGO_RCW_MANAGER,0) //(0x3000000)，BSD属性命令标识符起始值

#define ALGO_INVOKE_CMD_RCW_BASE_ID        ALGO_INVOKE_CMD_VAL(ALGO_TYPE_RCW,ALGO_RCW_MANAGER,ALGO_INVOKE_CMD_FLAG)//0x3004000,BSD扩展命令标识符起始值

#define ALGO_PROCESS_CMD_RCW_BASE_ID       ALGO_PROCESS_CMD_VAL(ALGO_TYPE_RCW,ALGO_RCW_MANAGER,ALGO_PROCESS_CMD_FLAG)//0x3008000,BSD处理命令标识符起始值

/*
*   下列为BSD 各个功能属性命令唯一标识符的起始值，ALGO_ATTR_VAL（算法类型，功能类型，属性）
*/

#define ALGO_ATTR_RCW_RCW_BASE_ID          ALGO_ATTR_VAL(ALGO_TYPE_RCW,ALGO_RCW_RCW,0)//(0x3010000)

#define ALGO_ATTR_RCW_LCA_BASE_ID          ALGO_ATTR_VAL(ALGO_TYPE_RCW,ALGO_RCW_LCA,0)//(0x3020000)


typedef enum {

    /*
    *   名称：RCW 功能使能
    *   属性：可获取、可设置
    *	参数：AlgoRcwAttr.enable,默认：1，可设置 0，1
    */
    ALGO_ATTR_RCW_ENABEL = ALGO_ATTR_RCW_RCW_BASE_ID,

    /*
    *   名称：RCW 速度设置
    *   属性：可获取、可设置。
    *	参数：AlgoRcwAttr.speedThreshold，默认：30，可设置[10,60]，单位km/h
    */
    ALGO_ATTR_RCW_SPEED_THRESHOLD,

    /*
    *   名称：RCW 灵敏度
    *   属性：可获取、可设置
    *   参数：AlgoAdasAttr 中senType ,默认值：中，可设置 高，中，低三个灵敏度
    *   高灵敏度 ttc 3.5s，纵向距离小于15米；
    *   中灵敏度 ttc 2.7s，纵向距离小于12.5米；
    *   低灵敏度 ttc 1.8s，纵向距离小于10米；
    */
    ALGO_ATTR_RCW_SENSITIVITY,

    /*
    *   名称：RCW灭点 自动标定时无需设置
    *   属性：可获取、可设置
    *	参数：AlgoRcwAttr 中 vp,
    *       valid: 获取时:1 有效，0 无效
    *       vpX :地面标记点x ，以图像左上角为原点,相对于标定图像分辨率比例 vpX = x/imageWidth;
    *       vpY :地面标记点y ，以图像左上角为原点，相对于标定图像分辨率比例 vpY = y/imageHeight;
    */
    ALGO_ATTR_RCW_CALIB_VP,

    /*
    *   名称：摄像头高度，自动标定时无需设置
	*   属性：可获取、可设置
	*	参数：AlgoRcwAttr 中cameraHeight，单位mm
    */
    ALGO_ATTR_RCW_CALIB_CAMERA_HEIGHT,

    /*
    *   名称：RCW 标定，摄像头与车辆的相对位置信息。
    *   属性：可获取、可设置。
    *	参数： cameraToBumper :摄像头与车尾的距离 单位 mm。
    *       cameraToLeftWheel :摄像头与左车轮的距离 单位mm。
    *       cameraToRightWheel :摄像头与右车轮的距离 单位mm。
    *       cameraToFrontAxle :摄像头与车轴的距离 单位mm。
    */
    ALGO_ATTR_RCW_CALIB_VEHICLE_PARAM,

    /*
    *   名称：自动标定 使能
	*   属性：可获取、可设置
    *	参数：AlgoRcwConfig中enable,默认值:1,可调值：0,1
    */
    ALGO_ATTR_RCW_CALIB_AUTO_ENABLE,
    
    /*
    *   名称：自动标定启动速度
	*   属性：可获取、可设置
    *	参数：AlgoRcwConfig 中speed，默认值:20, 可调值：>5，单位秒km/h
    */
    ALGO_ATTR_RCW_CALIB_AUTO_SPEED,

    /*
    *   名称：自动标定时长（帧数）
	*   属性：可获取、可设置。
    *	参数：AlgoRcwAttr 中autoCalibTime,默认值：480,可调值：>100
    */
    ALGO_ATTR_RCW_CALIB_AUTO_TIME,

    /*
    *   名称：自动标定方式 (预留，暂未开放，默认每次启动运行)
    *   属性：可获取、可设置。
    *	参数：AlgoRcwAttr 中autoCalibMode
    *        1:设备第一次启动运行
    *        2:设备每次启动运行
    */
    ALGO_ATTR_RCW_CALIB_AUTO_MODE,

    /*
    *   名称：清除标定历史，并立即进行自动标定，标定完成前不输出报警
    *   属性：仅可设置
    *	参数：需传入自动标定启动速度，仅本次标定使用：AlgoRcwAttr 中 speedThreshold
    */
    ALGO_ATTR_RCW_RM_HISTORY_AND_RE_AUTO_CALIB_ATONCE,

    /*
    *   名称：LCA (亮灯) 功能使能
    *   属性：可获取、可设置
    *	参数：AlgoRcwAttr.enable，默认值：1，可设置 0，1
    */
    ALGO_ATTR_RCW_LCA_ENABEL = ALGO_ATTR_RCW_LCA_BASE_ID,

    /*
    *   名称：LCA （亮灯）预警启动速度
    *   属性：可获取、可设置
    *	参数：AlgoRcwAttr.speedThreshold，默认值：10，可设置[10,120],单位km/h
    */
    ALGO_ATTR_RCW_LCA_SPEED_THRESHOLD,

    /*
    *   名称：LCA （亮灯）灵敏度
    *   属性：可获取、可设置
    *   参数：AlgoAdasAttr 中senType ,默认值：中，可设置 高，中，低三个灵敏度
    *   高灵敏度 后车相对速度 >= -0.2m/h，纵向距离8-14米；
    *   中灵敏度 后车相对速度 >= -0.1m/h，纵向距离7-12.5米；
    *   低灵敏度 后车相对速度 >= 0m/h，纵向距离6-11米；
    */
    ALGO_ATTR_RCW_LCA_SENSITIVITY,

}AlgoRcwAttrType;


typedef struct
{
    int     valid;// 获取是1 有效，0 无效
    float   vpX;//地面标记点x ，以图像左上角为原点,相对于标定图像分辨率比例 vpX = x/imageWidth;
    float   vpY;//地面标记点y ，以图像左上角为原点，相对于标定图像分辨率比例 vpY = y/imageHeight;
}AlgoRcwVp;

/*
*   名称：RCW 标定，摄像头与车辆的相对位置信息。
*   属性：可获取、可设置。
*	参数： cameraToBumper :摄像头与车尾的距离 单位 mm。
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
}AlgoRcwVehicleInfo;

typedef union
{
    int enable;
    int speedThreshold;
    int autoCalibTime;
    int autoCalibMode;
    float cameraHeight;
    AlgoRcwVp vp;
    AlgoRcwVehicleInfo vehInfo;
    AlgoSenType sen;
}AlgoRcwAttr;

// RCW 扩展命令标识符 枚举
typedef enum
{
    ALGO_RCW_INVOKE_CMD_BASE =ALGO_INVOKE_CMD_RCW_BASE_ID,
    ALGO_RCW_INVOKE_CMD_SPEED,//车辆速度，
    ALGO_RCW_INVOKE_CMD_TURNLIGTH,//车辆转向
    ALGO_RCW_INVOKE_CMD_ACC,//设备加速度传感器
    ALGO_RCW_INVOKE_CMD_GYROSCOPE,// 陀螺仪
    ALGO_RCW_INVOKE_CMD_LOCATIONINFO,//定位信息
    ALGO_RCW_INVOKE_CMD_BRAKE,// 刹车信息
}AlgoRcwInvokeCmd;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
