#ifndef _ALGO_ATTR_H_
#define _ALGO_ATTR_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#include "common/algo_comm.h"
#include "adas/algo_adas_attr.h"
#include "rcw/algo_rcw_attr.h"


typedef enum {
    ALGO_ATTR_ENABLE = ALGO_ATTR_BASE_ID,
    ALGO_ATTR_VERSION,
    ALGO_ATTR_LOGLEVEL,
}AlgoAttrType;
typedef enum
{
    ALGO_LEVEL_ERR=1,
    ALGO_LEVEL_INIT,
    ALGO_LEVEL_WARN,
    ALGO_LEVEL_INFO,
    ALGO_LEVEL_DEBUG,
    ALGO_LEVEL_BUTT,
}AlgoLogLevel;
typedef char AlgoVersionInfo;
typedef union
{
    AlgoVersionInfo *versionInfo;
    AlgoAdasAttr adasAttr;
    AlgoLogLevel logLevel;
    AlgoRcwAttr rcwAttr;
}AlgoAttr;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
