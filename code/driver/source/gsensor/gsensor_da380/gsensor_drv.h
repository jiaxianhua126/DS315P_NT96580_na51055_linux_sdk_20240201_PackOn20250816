#ifndef _GSENSOR_DA380_H
#define _GSENSOR_DA380_H

#include "kwrap/type.h"
#include "kwrap/flag.h"
#include <linux/i2c.h>
#include "kwrap/util.h"

#define GSEN_I2C_NAME			"gsen_da380"
#define GSEN_I2C_ADDR			0x27

typedef struct {
	struct i2c_client  *iic_client;
	struct i2c_adapter *iic_adapter;
} GSEN_I2C_INFO;

typedef struct _GSENSOR_INFO {
	int reversed;
} GSENSOR_INFO, *PGSENSOR_INFO;

typedef enum _GSEN_I2C_ID {
	GSEN_I2C_ID_1 = 0,
	GSEN_I2C_ID_2 = 1,
	GSEN_I2C_ID_3 = 2,
	GSEN_I2C_ID_4 = 3,
	GSEN_I2C_ID_5 = 4,
	ENUM_DUMMY4WORD(GSEN_I2C_ID)
} GSEN_I2C_ID;

typedef struct _GSEN_I2C {
	GSEN_I2C_ID id;
	UINT32 addr;
} GSEN_I2C;

#define IOC_GSENSORGET_CHIP_ID                  _IOWR('r', 3, unsigned int)
#define IOC_GSENSOR_PARKING_SENSITIVITY     	_IOWR('w', 4, unsigned int)
#define EXCEED_THRESHOLD_FLAG            	   	_IOWR('r', 5, unsigned int)
#define IOC_GSENSOR_GET_CUR_VALUE   	    	_IOWR('r', 6, unsigned int)
#define IOC_GSENSOR_DISABLE_INT			        _IOWR('w', 7, unsigned int)
#define IOC_GSENSOR_COLLISION_SENSITIVITY	    _IOWR('w', 8, unsigned int)
#define IOC_GSENSOR_SHIFT_CONTROL		        _IOWR('w', 9, unsigned int)

#define SENSOR_COLLISION_SENSITIVITY_HIGH_VAL_H		0x2		//0.5g
#define SENSOR_COLLISION_SENSITIVITY_HIGH_VAL_L		0xAB
#define SENSOR_COLLISION_SENSITIVITY_MID_VAL_H		0x6
#define SENSOR_COLLISION_SENSITIVITY_MID_VAL_L		0x66
#define SENSOR_COLLISION_SENSITIVITY_LOW_VAL_H		0x6		//1.2g
#define SENSOR_COLLISION_SENSITIVITY_LOW_VAL_L		0x66

#define SENSOR_PARKING_SENSITIVITY_HIGH_VAL_H		0x1		//0.2g  0x555=1g
#define SENSOR_PARKING_SENSITIVITY_HIGH_VAL_L		0x13
#define SENSOR_PARKING_SENSITIVITY_MID_VAL_H		0x2
#define SENSOR_PARKING_SENSITIVITY_MID_VAL_L		0xAB
#define SENSOR_PARKING_SENSITIVITY_LOW_VAL_H		0x2		//0.5g
#define SENSOR_PARKING_SENSITIVITY_LOW_VAL_L		0xAB


#define DA380_SENSOR_DATA_SIZE_RES_LOW     (3)
#define DA380_SENSOR_DATA_SIZE_RES_HIGH    (6)

#define DA380_AXIS_X      (0)
#define DA380_AXIS_Y      (1)
#define DA380_AXIS_Z      (2)
#define DA380_AXES_NUM    (3)


/***********************************************
 *** REGISTER MAP
 ***********************************************/
#define DA380_REG_XOUT_EX_L			0x02
#define DA380_REG_XOUT_EX_H			0x03
#define DA380_REG_YOUT_EX_L			0x04
#define DA380_REG_YOUT_EX_H			0x05
#define DA380_REG_ZOUT_EX_L			0x06
#define DA380_REG_ZOUT_EX_H			0x07

/*============================================================================
TYPE / DATA STRUCTURE DEFINITIONS
============================================================================*/
typedef struct
{
    short    fData[DA380_AXES_NUM];
}da380_data_t;


typedef struct COLLISION_SHIFT_VALUE_S
{
    unsigned int COLLISION_HAPPEN; /**1-COLLISION_HAPPEN  0-COLLISION not HAPPEN*/
    unsigned int SHIFT_HAPPEN; /**1-SHIFT_HAPPEN  0-SHIFT not HAPPEN*/
} HI_COLLISION_SHIFT_VALUE_S;

#endif

