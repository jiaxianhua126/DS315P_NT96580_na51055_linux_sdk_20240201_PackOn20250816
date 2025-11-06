#ifndef _ALGO_ERROR_H_
#define _ALGO_ERROR_H_


typedef enum {
    ALGO_ERROR_NONE=0,
    ALGO_ERROR_OPERATE_ERROR=1,
    ALGO_ERROR_NOT_SUPPORT=2,
    ALGO_ERROR_RESOURCE_CONFLICT=3,
    ALGO_ERROR_INVALID_ARGUMENTS=4,
    ALGO_ERROR_BUSY=5,
    ALGO_ERROR_NOINIT=6,
    ALGO_ERROR_BUTT
}AlgoErrorType;

#define ALGO_ERROR_BASE_VAL (0x80000000)


/********************************************************************************************
|--------------------------------------------------------------------------------------------|
|  ERROR_FLAG  |   ALGO_ID   | ALGO_MOD_ID | INVOKE_FLAG  | PORCESS_FLAG |    ERROR_TYPE     |
|--------------------------------------------------------------------------------------------|
|<----1bits---><----7bits---> <----8bit---> <----1bit---> <--1bits-----> <------14bits------>|
*********************************************************************************************/
#define ALGO_ERROR_CREATE_VAL(algo,mod,error)\
    ((int32_t)(ALGO_ERROR_BASE_VAL|(algo<<24)|(mod<<16)|error))



#endif
