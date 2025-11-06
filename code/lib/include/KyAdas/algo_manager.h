#ifndef KY_ALGO_MANAGER_H_
#define KY_ALGO_MANAGER_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "common/algo_comm.h"
#include "common/algo_error.h"
#include "algo_result.h"
#include "algo_attr.h"

typedef struct {
    int imageWidth;
    int imageHeight;
    AlgoImageAlloc allocCallback;
    AlgoImageFree  freeCallback;
    AlgoEventCallback eventCallback;//算法运算结果回调
    const char* modelPath;//模型文件存放路径, 算法只读
    const char* configPath;//配置文件存放路径，算法需要读写
    int fps;      //帧率，默认为12fps
    int sync_enable;//是否采用同步处理，0，采用异步，1，采用同步。
}AlgoPara;


typedef struct {
    char algoName[ALGO_MAX_NAME_LEN];
    AlgoType type;
    AlgoPara algoPara;
}AlgoCreatePara;

typedef enum AlgoActiveMode{
    AlgoNetMode = 1,        // 设备直接连接网络激活 [ 暂时不支持]
    AlgoSerialMode = 2,     // 设备通过串口通信 与 windows服务器连接进行激活
    AlgoSocketMode = 3      // 设备通过socket通信 与 windows服务器连接进行激活
}AlgoActiveMode;

typedef enum AlgoActiveType{
    ACTIVE_ALGO_NONE = 0,
    ACTIVE_ALGO_ADAS = 1,       // 只激活前路算法
    ACTIVE_ALGO_REAR = 2,       // 只激活后路算法
    ACTIVE_ALGO_ADASREAR = 3,   // 激活前路 和 后路算法
}AlgoActiveType;

typedef struct
{
    const char * activePath; // 激活文件存放路径
    const char * logPath;   //调试log存储路径（例：/data），为空（NULL）时不写, 建议出货版本不写
    AlgoActiveMode activeMode;  // 激活方式
    AlgoActiveType activeAlgoType; // 要激活的算法类型
    const char * serialPath; // 设备串口通信地址,激活时使用 ，例如 "/dev/ttyS0"
    const char *serverIp;  // socket激活时，服务器ip地址
    int serverPort;       // socket激活时，服务器端口号
    int debug_enable;   // 1：启用调试模式，运行半小时后算法失效，无需激活, 0: 不启用
}AlgoInitPara;
/*
 * @description: sdk global initialization; 创建算法前调用一次
 * @param:
 * @output:
 * @return :On success, returns 0;on error, it returns an error number
*/
int  ALGO_MANAGER_Init(AlgoInitPara *para);

/*
 * @description: sdk global destroy initialization；释放所有算法后调用一次
 * @param:
 * @output:
 * @return :On success, returns 0;on error, it returns an error number
*/
int  ALGO_MANAGER_DeInit(void);

/*
 * @description:  create  algo's  handle
 * @param:creatPara
 * @output:
 * @return :On success, returns 0;on error, it returns an error number
*/
int  ALGO_MANAGER_Create(AlgoHandle *algoHandle,const AlgoCreatePara *creatPara);

/*
 * @description:  destroy  algo's  handle
 * @param:
 * @output:
 * @return :On success, returns 0;on error, it returns an error number
*/
int  ALGO_MANAGER_Destroy(AlgoHandle algoHandle);


/*
 * @description:  get the algo's handle of already created by algo's name
 * @param:
 * @output:
 * @return :On success, returns 0;on error, it returns an error number
*/
int  ALGO_MANAGER_GetHandleByName(AlgoHandle *algoHandle,const char *algoName);




/*
 * @description:  get the algo's handle of already created by algo's type
 * @param:
 * @output:
 * @return :On success, returns 0;on error, it returns an error number
*/
int  ALGO_MANAGER_GetHandleByType(AlgoHandle *algoHandle,AlgoType type);


/*
 * @description:  set the algo's attr follow the algo's attr type
 * @param:
 * @output:
 * @return :On success, returns 0;on error, it returns an error number
*/
int  ALGO_MANAGER_SetAttr(AlgoAttrTypeVal type,const AlgoAttr* attr);




/*
 * @description:  get the algo's attr follow the algo's attr type
 * @param:
 * @output:
 * @return :On success, returns 0;on error, it returns an error number
*/
int  ALGO_MANAGER_GetAttr(AlgoAttrTypeVal type,AlgoAttr* attr);




/*
 * @description:定义算法透传接口，扩展型接口
 * @param:
 * @output:
 * @return :On success, returns 0;on error, it returns an error number
*/
int  ALGO_MANAGER_Invoke(AlgoInvokeCmd cmd, const AlgoCmdPara* cmdPara);


/*
 * @description:  async process algo
 * @param: image
 * @output: algo result
 * @return :On success, returns 0;on error, it returns an error number
*/
int  ALGO_MANAGER_AsyncProcessImage(AlgoHandle algoHandle,AlgoProcessCmd cmd,const AlgoImages *image);



/*
 * @description:  process algo
 * @param: image
 * @output: algo result
 * @return :On success, returns 0;on error, it returns an error number
*/
int  ALGO_MANAGER_ProcessImage(AlgoHandle algoHandle,AlgoProcessCmd cmd,const AlgoImages *image,AlgoEventData *eventData);

/*
 * @description:算法结果融合
 * @param:
 * @output:
 * @return :On success, returns 0;on error, it returns an error number
*/
int ALGO_MANAGER_FUSE_RESULT(const AlgoEventData *adas_data,const AlgoEventData *rcw_data, AlgoFuseEventData *algoFuseEventData);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
