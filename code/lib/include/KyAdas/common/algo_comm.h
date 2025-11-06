#ifndef _ALGO_COMM_H_
#define _ALGO_COMM_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define ALGO_MAX_NAME_LEN                   128
#define ALGO_INVOKE_BYTE_NUM                256

#include <stdint.h>
#include <time.h>
//算法句柄

typedef void* AlgoHandle ;

#define NoAlgoHandle NULL

/*
*   算法和算法功能类型将作为属性设置读取命令、扩展命令接口、处理命令的唯一标识符索引，请勿改动
*/
//算法类型枚举，ADAS，DMS，BSD,EMERGENCY,RECOGNITION.
//ALGO_TYPE_BUTT 为算法类型数量枚举值。
//ALGO_TYPE_MGR 为算法管理者对象
typedef enum {
    ALGO_TYPE_MGR=0,
    ALGO_TYPE_ADAS=1,
    ALGO_TYPE_RCW=2,
    ALGO_TYPE_BUTT
}AlgoType;

/*
 * 灵敏度设置，每个算法可以设置高，中，低三个灵敏度，默认为中
    SEN_HIGH    高灵敏度
    SEN_MIDDLE  中灵敏度
    SEN_LOW     低灵敏度
 */
typedef enum
{
    SEN_HIGH = 0,    //高灵敏度
    SEN_MIDDLE = 1,  //中灵敏度
    SEN_LOW = 2      //低灵敏度
}AlgoSenType;



#define ALGO_INVOKE_CMD_FLAG                    0x4000 //扩展命令标识
#define ALGO_PROCESS_CMD_FLAG                   0x8000 //处理命令标识


/*定义算法属性，算法透传命令全局唯一标识符，算法类型，功能类型，功能属性命令*/
/******************************************************************************
|------------------------------------------------------------------------------|
|   ALGO_ID   | ALGO_MOD_ID | INVOKE_FLAG  | PORCESS_FLAG | ALGO_MOD_CMD       |
|------------------------------------------------------------------------------|
|<----8bits---> <----8bit---> <----1bit---> <--1bits-----> <------14bits------>|
*******************************************************************************/
#define ALGO_ATTR_ALGO_ADDR                 (0xff000000)

#define ALGO_MOD_ADDR                       (0x00ff0000)

#define ALOG_GET_ALGO_TYPE(cmd)\
    ((int32_t)((cmd&ALGO_ATTR_ALGO_ADDR)>>24)) //从各个命令标识符中获取算法类型

#define ALOG_GET_MODE_TYPE(cmd)\
    ((int32_t)((cmd&ALGO_MOD_ADDR)>>16)) //从各个命令标识符中获取算法功能类型

#define ALGO_BASE_VAL(algo,mod,val)\
    ((int32_t)((algo<<24)|(mod<<16)|(val))) //组织命令标识符



#define ALGO_ATTR_VAL                       ALGO_BASE_VAL

#define ALGO_ATTR_BASE_ID                   (0x00000000)

typedef int  AlgoAttrTypeVal;



#define ALGO_INVOKE_CMD_ALGO_ADDR           (0xff004000)

#define ALGO_INVOKE_CMD_VAL                 ALGO_BASE_VAL

typedef int  AlgoInvokeCmd;




#define ALGO_PROCESS_CMD_ALGO_ADDR          (0xff008000)

#define ALGO_PROCESS_CMD_VAL                ALGO_BASE_VAL

typedef int AlgoProcessCmd;


typedef struct
{
    /**
    * YUV图片的宽度
    */
    uint32_t u32Width;
   /**
    * YUV图片的高度
    */
    uint32_t u32Height;
    /**
    * YUV图片的跨度
    */
    uint32_t u32Stride;
   /**
   * YUV图片format,0 nv21 ,1,yv21,2,rgb
   */
    uint32_t u32Format;
   /**
    * YUV图片序列号
    */
    uint32_t u32TimeRef;

    /**
    * YUV图片时间戳
    */
    uint64_t u64PTS;

    /**
    * YUV图片的物理地址
    */
    uint64_t phyAddr;

    uint64_t phyAddr_uv;
    /**
    * YUV图片的虚拟地址
    */
    void     *virAddr;

    /**
    * 预留指针
    */
    void     *ptr;
    /**
    * YUV图片的大小
    */
    size_t   size;

   /**
    * 真实物理通道ID.
    */
    uint8_t channelId;//从 1 开始
   /**
    * 虚拟通道ID.
    */
    uint8_t virtualId;//从 0 开始
}ALGO_ORG_VIDEO_DATA;


typedef ALGO_ORG_VIDEO_DATA AlgoImage;


typedef struct
{
    size_t    imageNum;//当前有效的图像数据数量
    AlgoImage **image;//图像信息
}AlgoImages;

typedef AlgoImage VideoFrame;


//获取图像、释放图像回调，供算法内部使用
typedef int (*AlgoImageAlloc)(int width,int height,VideoFrame* frame);

typedef int (*AlgoImageFree)(uint64_t frameId, VideoFrame* frame);




/*算法invoke 透传私有数据包*/

typedef struct {
    int  valid; //location valid. 1:valid; 0:invalid
    double latitude;
    char lat;
    double longitude;
    char lon;
    double speed;//km/h
    double course;
    struct tm time;
    // Quality 0, 1, 2
    uint8_t quality;
    // Number of satellites: 1,2,3,4,5...
    uint8_t satellites;
    // Altitude eg: 280.2 (Meters above mean sea level)
    double altitude;
    uint8_t antenna;//0 normaled, 1 opened, 2 shorted,
}AlgoLocationInfo;

typedef struct{
    float speed;//车辆速度信息，km/h
    int64_t timestamp;       //时间戳
    float accData[3];//x,y,z 加速度传感器数据
    float gyrData[3];//x,y,z 陀螺仪数据
}AlgoEmerPara;

typedef struct{
    int64_t timestamp;       //时间戳
    char deviceID[128];      //设备ID
    int warnType;            //报警类型
    char algo_version[128];  //主动安全版本号
    char software_version[128];  //软件版本号
}AlgoSaveJsonPara;

typedef union
{
    float speed;//车辆速度信息，km/h
    int speed_type; //车辆速度类型 0为真实速度，1为模拟速度
    int brake; //刹车信息，1为制动，0为复位。
    int turnlight;//转向信息，1 左转 2右转。
    float accData[3];//x,y,z 加速度传感器数据
    float gyrData[3];//x,y,z 陀螺仪数据
    AlgoLocationInfo locationInfo; //定位信息。
    AlgoEmerPara emerg;
    AlgoSaveJsonPara jsonPara;
}AlgoCmdPara;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif
