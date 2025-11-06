#ifndef _ALGO_RESULT_COMM_H_
#define _ALGO_RESULT_COMM_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#include <stdint.h>

typedef enum {
      UNKNOWN_OBJECT = 0,
      VEHICLE = 1,     // Passenger car or truck.
      PEDESTRIAN = 2,  // Pedestrian, usually determined by moving behavior.
      SPEED_LIMIT = 101,
}AlgoObjType;
//约定x 为横向坐标，y为纵向坐标.,z垂直坐标
typedef struct
{
    int xmin;
    int ymin;
    int xmax;
    int ymax;

}Box2i;

typedef struct
{
    float xmin;
    float ymin;
    float xmax;
    float ymax;
}Box2f;

typedef struct
{
    int x;
    int y;

}Point2i;

typedef struct
{
    float x;
    float y;

}Point2f;

typedef struct
{
    float x ;
    float y ;
    float z ;
}Point3f;

    
/******************************************************************************
|----------------------------------------------------------------|
|   WRAN LEVEL | WARN RESULT|
|----------------------------------------------------------------|
|<----4bits---><--28bits-->|
******************************************************************************/
#define ALGO_WARN_RESULT(level,warn)\
    ((int32_t)((level<<28)|warn))

#define ALGO_WARN_TYPE_RESULT_DECODE_LEVEL(val)\
    ((int32_t)((val>>28)&0xf))

#define ALGO_WARN_RESULT_TYPE_CHECK(val,type)\
    ( (int) ( val & ( 1<<(type-1) ) ) )


// 设置报警类型对应的使能位状态为1
#define ALGO_WARN_TYPE_BIT_SET(type)\
    (int32_t)(1<<(type-1))
// 检查报警类型对应的使能位状态
#define ALGO_WARN_TYPE_CHECK_SET(val,type)\
    (int32_t)(val & (1<<(type-1)))

// 设置扩展信息对应的使能位状态
#define ALGO_EXTEND_INFO_SET(type)\
    (int32_t)(1<<(type-1))
// 检查扩展信息对应的使能位状态
#define ALGO_EXTEND_INFO_CHECK(val,type)\
    (int32_t)(val & (1<<(type-1)))


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
