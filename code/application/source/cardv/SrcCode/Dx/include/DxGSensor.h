#ifndef _DX_GSENSOR_H
#define _DX_GSENSOR_H

#include "kwrap/nvt_type.h"

typedef enum {
	GSENSOR_SENSITIVITY_OFF,
	GSENSOR_SENSITIVITY_LOW,
	GSENSOR_SENSITIVITY_MED,
	GSENSOR_SENSITIVITY_HIGH,
	ENUM_DUMMY4WORD(GSENSOR_SENSITIVITY)
} GSENSOR_SENSITIVITY;


#define DA380_AXIS_X      (0)
#define DA380_AXIS_Y      (1)
#define DA380_AXIS_Z      (2)
#define DA380_AXES_NUM    (3)
typedef struct
{
    short    fData[DA380_AXES_NUM];
}da380_data_t;




#define IOC_GSENSORGET_CHIP_ID                  _IOWR('r', 3, unsigned int)
#define IOC_GSENSOR_PARKING_SENSITIVITY     	_IOWR('w', 4, unsigned int)
#define EXCEED_THRESHOLD_FLAG            	   	_IOWR('r', 5, unsigned int)
#define IOC_GSENSOR_GET_CUR_VALUE   	    	_IOWR('r', 6, unsigned int)
#define IOC_GSENSOR_DISABLE_INT			        _IOWR('w', 7, unsigned int)
#define IOC_GSENSOR_COLLISION_SENSITIVITY	    _IOWR('w', 8, unsigned int)
#define IOC_GSENSOR_SHIFT_CONTROL		        _IOWR('w', 9, unsigned int)

//extern void GSensor_InstallID(void) _SECTION(".kercfg_text");
//extern void GPS_UninstallID(void);
BOOL GSensor_DA380_GetStatus(da380_data_t *GS_Data);
extern BOOL GSensorRec_Open(void);
extern BOOL GSensorRec_Close(void);
extern void GSensor_DA380_SetSensitivity(GSENSOR_SENSITIVITY GSensorSensitivity);
extern void GSensor_DA380_Sensitivity_Parking(GSENSOR_SENSITIVITY GSensorSensitivity_Parking);
#endif