#include "kwrap/type.h"
#include "kwrap/nvt_type.h"
#include "kwrap/error_no.h"
#include "kwrap/stdio.h"
#include "kwrap/flag.h"
#include "Dx.h"
#include "DxCommon.h"
#include "DxCfg.h"
#include "DxGSensor.h"
//#include "gsensor_drv.h"
//#include "gsensor_main.h"
#include "NvtUser/NvtUser.h"
#include "NvtUser/NvtBack.h"
#include "Utility/SwTimer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "kwrap/cmdsys.h"
#include "kwrap/task.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include "Utility/SwTimer.h"
#include "io/gpio.h"

///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          DxGSensor
#define __DBGLVL__          1 // 0=OFF, 1=ERROR, 2=TRACE
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>
#define _GSensor_DEBUG_SYMBOL			1
#if _GSensor_DEBUG_SYMBOL
#define GSensor_debug(arg)				DBG_DUMP arg
#else
#define GSensor_debug(arg)
#endif

#define _GSensor_NMEA_DEBUG_SYMBOL		0
#if _GSensor_NMEA_DEBUG_SYMBOL
#define NMEA_debug(arg)				DBG_DUMP arg
#else
#define NMEA_debug(arg)
#endif

//static pthread_t gsensor_thread;

//extern BOOL   FlowMovie_WakeUpLCDBacklight(void);
extern void FlowMovie_SetGsensorParkingModeStatus(BOOL En);
extern BOOL isACCTrigParkMode;

static GSENSOR_SENSITIVITY g_GSensorSensitivity = GSENSOR_SENSITIVITY_MED; //GSENSOR_SENSITIVITY_OFF;
static int gsensor_fd = -1;
static BOOL  g_bGsensorOpened = FALSE;

static da380_data_t raw_data = { {0} };
static da380_data_t old_raw_data = { {0} };
#if 0
void BlingLED(void)
{
    UINT32 GPIO_WIFI_PWREN = 43;
    UINT32 GPIO_WL_REG_ON = 37;

    GSensor_debug(("Bling LED\r\n"));
    gpio_setPin(GPIO_WIFI_PWREN);
    SwTimer_DelayMs(100);
    gpio_clearPin(GPIO_WIFI_PWREN);
    SwTimer_DelayMs(100);

    gpio_setPin(GPIO_WL_REG_ON);
    SwTimer_DelayMs(100);
    gpio_clearPin(GPIO_WL_REG_ON);
    SwTimer_DelayMs(100);

    FlowMovie_WakeUpLCDBacklight();
    GSensor_debug(("NVTEVT_KEY_CUSTOM1\r\n"));
}
THREAD_RETTYPE GSensor_TASK(void *pvParameters)
{
   
    //int threshold = 300;
    da380_data_t raw_data = { {0} };
    da380_data_t old_raw_data = { {0} };
    //int enSensitity = 1;
    int status = 0;

    GSensor_debug(("GSensor_InstallID"));
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	// pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    gsensor_fd = open("/dev/gsensor", O_RDWR);

    if (gsensor_fd == -1) {
        GSensor_debug(("open /dev/gsensor failed: %d\r\n", gsensor_fd));
        THREAD_RETURN(-1);
    }
    GSensor_debug(("open /dev/gsensor success!"));

    //ioctl(gsensor_fd, IOC_GSENSOR_COLLISION_SENSITIVITY, enSensitity);

    // ==> 存取data, ioctl(s_s32HALGSENSORfd, IOC_GSENSOR_COLLISION_SENSITIVITY, pstCfg->enSensitity);
    // ==> 存取data, ioctl(s_s32HALGSENSORfd, IOC_GSENSOR_NORMAL_MODE_GYRO_ONLY, &raw_data);

    while (TRUE) {
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        ioctl(gsensor_fd, IOC_GSENSOR_GET_CUR_VALUE, &raw_data);

        status = (abs(old_raw_data.fData[0]-raw_data.fData[0]) > DA380Threshold)
            + (abs(old_raw_data.fData[1]-raw_data.fData[1]) > DA380Threshold)
            + (abs(old_raw_data.fData[2]-raw_data.fData[2]) > DA380Threshold);
        GSensor_debug(("status = %d\n", status));
        GSensor_debug(("X: %d\r\n", raw_data.fData[0]));
        GSensor_debug(("Y: %d\r\n", raw_data.fData[1]));
        GSensor_debug(("Z: %d\r\n", raw_data.fData[2]));

        if (status > 0) {
            //BlingLED();
        }
        old_raw_data = raw_data;

        //sleep(1);

        pthread_testcancel();
    }

    THREAD_RETURN(0);
}

void GSensor_InstallID(void)
{
    GSensor_debug(("GSensor_InstallID"));
    pthread_create(&gsensor_thread, NULL, GSensor_TASK, NULL);
}

void GSensor_UninstallID(void)
{
    pthread_cancel(gsensor_thread); 
}
#endif


BOOL GSensor_DA380_CrashMode(void)
{
    return FALSE;
}

void GSensor_DA380_SetSensitivity(GSENSOR_SENSITIVITY GSensorSensitivity)
{
    	g_GSensorSensitivity = GSensorSensitivity;
	ioctl(gsensor_fd,IOC_GSENSOR_PARKING_SENSITIVITY,0);
	//debug_msg("g_GSetSensorSensitivity=%d \r\n",GSensorSensitivity);
}
BOOL Gsensor_Sensitivity_Parking = FALSE;
void GSensor_DA380_Sensitivity_Parking(GSENSOR_SENSITIVITY GSensorSensitivity_Parking)
{
	UINT32 GSensor_Sensitivity_data;
	if (0) //(isACCTrigParkMode) 
	{
	    switch(GSensorSensitivity_Parking)
	    {
	    case GSENSOR_SENSITIVITY_LOW:
			if (!Gsensor_Sensitivity_Parking) {
				DBG_DUMP("call GSENSOR_SENSITIVITY_LOW\r\n");
				GSensor_Sensitivity_data = 1;
				ioctl(gsensor_fd,IOC_GSENSOR_PARKING_SENSITIVITY,GSensor_Sensitivity_data);
				Gsensor_Sensitivity_Parking = TRUE;
			}
	        break;
	    case GSENSOR_SENSITIVITY_MED:
			if (!Gsensor_Sensitivity_Parking) {
				DBG_DUMP("call GSENSOR_SENSITIVITY_MED\r\n");
				GSensor_Sensitivity_data = 2;
				ioctl(gsensor_fd,IOC_GSENSOR_PARKING_SENSITIVITY,GSensor_Sensitivity_data);
				Gsensor_Sensitivity_Parking = TRUE;
			}
	        break;
	    case GSENSOR_SENSITIVITY_HIGH:
			if (!Gsensor_Sensitivity_Parking) {
				DBG_DUMP("call GSENSOR_SENSITIVITY_HIGH\r\n");
				GSensor_Sensitivity_data = 3;
				ioctl(gsensor_fd,IOC_GSENSOR_PARKING_SENSITIVITY,GSensor_Sensitivity_data);
				Gsensor_Sensitivity_Parking = TRUE;
			}
	        break;
	    default:
	        break;
	    }
	}else {
		ioctl(gsensor_fd,IOC_GSENSOR_PARKING_SENSITIVITY,0);
	}
}

static UINT32 DA380Threshold=0xFFFFFFFF;
static UINT32 GSensor_DA380_GetSensitivityLevel(void)
{
   if (1) //(!isACCTrigParkMode) //normal mode
    {
        switch(g_GSensorSensitivity)
        {
        case GSENSOR_SENSITIVITY_OFF:
            DA380Threshold = 0xFFFF;
            break;
        case GSENSOR_SENSITIVITY_LOW:
            DA380Threshold = 8500;//25 
            break;
        case GSENSOR_SENSITIVITY_MED:
            DA380Threshold = 6500;//20
            break;
        case GSENSOR_SENSITIVITY_HIGH:
            DA380Threshold = 4500;//0x100;//16
            break;
        default:
            DA380Threshold = 0xFFFF;
            break;
        }
    }
    else //parking mode
    {
        switch(g_GSensorSensitivity)
        {
       // case GSENSOR_SENSITIVITY_OFF:
       //    DA380Threshold = 0xFFFF;
	   //	}
       //     break;
        case GSENSOR_SENSITIVITY_LOW:
            DA380Threshold = 6000;//25 
            break;
        case GSENSOR_SENSITIVITY_MED:
            DA380Threshold = 4000;//20
            break;
        case GSENSOR_SENSITIVITY_HIGH:
            DA380Threshold = 2000;//0x100;//16
            break;
        default:
            DA380Threshold = 0xFFFF;
            break;
        }
    }

    return DA380Threshold;
}

BOOL GSensor_DA380_GetStatus(da380_data_t *GS_Data)
{
    UINT32  abs_cal_x = 0, abs_cal_y = 0, abs_cal_z = 0;
	UINT32 Threshold = 0,P_INT_COUNT = 0;
    UINT32 PM_Threshold = 200,PM_INT_COUNT = 0;
	if (g_bGsensorOpened == FALSE)
		return FALSE;
    Threshold = GSensor_DA380_GetSensitivityLevel();
    PM_Threshold = GSensor_DA380_GetSensitivityLevel();
    ioctl(gsensor_fd, IOC_GSENSOR_GET_CUR_VALUE, &raw_data);

    abs_cal_x = abs(old_raw_data.fData[0]-raw_data.fData[0]);
	if (abs_cal_x > Threshold)
		P_INT_COUNT++;
	if (abs_cal_x > PM_Threshold)
		PM_INT_COUNT++;
    abs_cal_y = abs(old_raw_data.fData[1]-raw_data.fData[1]);
	if (abs_cal_y > Threshold)
		P_INT_COUNT++;
	if (abs_cal_y > PM_Threshold)
		PM_INT_COUNT++;
    abs_cal_z =  abs(old_raw_data.fData[2]-raw_data.fData[2]);
    if (abs_cal_z > Threshold)
		P_INT_COUNT++;
	if (abs_cal_z > PM_Threshold)
		PM_INT_COUNT++;   

    //GSensor_debug(("X: %d--Y: %d--Z: %d\r\n", raw_data.fData[0],raw_data.fData[1],raw_data.fData[2]));
    if (old_raw_data.fData[0] == 0) { 
        old_raw_data = raw_data;
        //return  TRUE;
    } else {
        old_raw_data = raw_data;
    }
    //GSensor_debug(("..........DX = %d,DY = %d,DZ = %d th=%d PM_TH=%d\r\n",abs_cal_x,abs_cal_y,abs_cal_z,Threshold,PM_Threshold));
	
    if (PM_INT_COUNT >= 1) {
		//GSensor_debug(("^G ----------da380 GSensor_ParkingMode----------\n\r"));
		//FlowMovie_SetGsensorParkingModeStatus(TRUE);
	}

	if (P_INT_COUNT >= 1) {
		GSensor_debug(("----------da380_isr1 EMG----------\n\r"));
		return TRUE;
	} else {
        return FALSE;
    }
    return TRUE;
}

BOOL GSensorRec_Open(void)
{
    //GSensor_debug(("GSensorRec_Open\r\n"));
    if (g_bGsensorOpened==TRUE)
    {
        DBG_DUMP(".......GSensor DA380 open already!!!.......\r\n");
        return TRUE;
    }
    gsensor_fd = open("/dev/gsensor", O_RDWR);
    if (gsensor_fd == -1) {
        GSensor_debug(("open /dev/gsensor failed: %d\r\n", gsensor_fd));
        return FALSE;
    }
    g_bGsensorOpened = TRUE;
    return TRUE;
}

BOOL GSensorRec_Close(void)
{

    if (g_bGsensorOpened==FALSE)
    {
        GSensor_debug(("I2C close already\r\n"));
        return TRUE;
    }
    close(gsensor_fd);
    g_bGsensorOpened = FALSE;

    return TRUE;
}


