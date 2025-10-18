#include "kwrap/type.h"
#include "kwrap/nvt_type.h"
#include "kwrap/error_no.h"
#include "kwrap/stdio.h"
#include "kwrap/flag.h"
#include "Dx.h"
#include "IOCfg.h"
#include "DxCommon.h"
#include "DxCfg.h"
#include "DxGPS.h"
#include "NvtUser/NvtUser.h"
#include "NvtUser/NvtBack.h"
//#include "Debug.h"
#include "Utility/SwTimer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "kwrap/cmdsys.h"
#include "kwrap/task.h"
#include <pthread.h>
#include "Edog/EDogGlobal.h"
#include <semaphore.h>
#include "DxEdog.h"

///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          DxGPS
#define __DBGLVL__          1 // 0=OFF, 1=ERROR, 2=TRACE
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>
#define _GPS_DEBUG_SYMBOL			0
#if _GPS_DEBUG_SYMBOL
#define GPS_debug(arg)				DBG_DUMP arg
#else
#define GPS_debug(arg)
#endif

#define _GPS_NMEA_DEBUG_SYMBOL		0
#if _GPS_NMEA_DEBUG_SYMBOL
#define NMEA_debug(arg)				DBG_DUMP arg
#else
#define NMEA_debug(arg)
#endif

#define _GPS_CheckSum_Enable		0   //Enable to open check sum mechanism
//Declare functions
void GPSRec_NMEAParser(CHAR *NMEA_str, UINT32 Len, NMEATYPE NMEAtype);


//Declare variables
GSAINFO GSAInfo;
RMCINFO RMCInfo;
GGAINFO GGAInfo;
GSVINFO GSVInfo;
_ALIGNED(4) NMEASENTENCE NMEASentence={0};


#define PRI_GPSRECEIVE            10
#define STKSIZE_GPSRECEIVE        6144//64KB stack size

UINT32  GPSRECEIVE_ID = 0;
UINT32  FLG_ID_GPS = 0;
//#include "DebugModule.h"
///////////////////////////////////////////////////////////////////////////////

// global variables for parsing NMEA code
CHAR    type[NMEA_TYPE_SIZE], RemainStr[NMEA_SENTENCE_SIZE], PostPtr[NMEA_SENTENCE_SIZE + 20], *pPostPrt;
UINT32  PostPtrLen;
UINT32  CheckSum;
//GSA used
CHAR    SelMode;
UINT32  FixMode , SatUsed01, SatUsed02, SatUsed03, SatUsed04, SatUsed05, SatUsed06 , SatUsed07 , SatUsed08 , SatUsed09 , SatUsed10 , SatUsed11 , SatUsed12 ;
double  PDOP, HDOP, VDOP;
//RMC used
UINT32  Date;
CHAR    Status,MagVarInd;
double  Speed, Angle, MagVar;
//GGA used
double  UTCTime;
UINT32  PosFixInd, SatNumber, Empty1, Empty2;
double  Lat, Lon, Alt, MSL;
CHAR    NSInd, EWInd, M1, M2;
//GSV used
UINT32  NumOfSen, SenNum, SatInView, SatNum1, Elev1, Azi1, SNR1, SatNum2, Elev2, Azi2, SNR2, SatNum3, Elev3, Azi3, SNR3, SatNum4, Elev4, Azi4, SNR4;

//GPS heartbeat
static UINT32 GPSHeartBeat = 0; 

static GPS_UART_OBJ GpsUart = {
	.open		= uart2_open,
	.close		= uart2_close,
	.init		= uart2_init,
	.getString	= uart2_getString,
};
//#HTK#2023/08/30#add edog -start
INT32 temp_Latitude = 0;
INT32 temp_Longitude = 0;
static UINT32 g_AlarmTypePrev = 0xff, g_AlarmTypeNow = 0xff;
#define NVTEVT_KEY_EDOG_ALARM 0x11060124
UINT32 g_AvgReaminSec = 0;
BOOL g_bAvgCalStart = FALSE;
UINT32 g_AvgTotalSec = 0;
extern BOOL g_bManualCloseEdogWnd;

//#NT#2023/03/11#delai.zhang -begin
//#NT#APP task get value ,GPS taks set value.Two tasks assign a value to a variable at the same time
BOOL edogCBdata_update_ok =FALSE;
static float angle_curret = 0.0,angle_before = 0.0,speed_current = 0.0,speed_before = 0.0,Latitude_current = 0.0,Latitude_before = 0.0,Longitude_current = 0.0,Longitude_before = 0.0;
static CHAR NS_current,NS_before,EW_current,EW_before; 
extern void TPMSRecTsk(void); //Add for TPMS or Edog Data Receive
//THREAD_RETTYPE TPMSRecTsk(void *pvParameters);
//#HTK#2023/08/30#add edog -end

extern void GPSRecTsk(void);
#define GPS_DATANORMAL	0;
#define GPS_DATAERROR	1;

UINT16 GPSRec_TransformData(CHAR *NMEA_str, UINT32 Len, CHAR *pPostPrt, UINT32 *PostPtrLen);
BOOL GPSRec_CheckSum(CHAR *NMEA_str, UINT32 Len, UINT32 CheckSum);
BOOL GPSRec_GetUTCDate(UINT32 *Year, UINT32 *Month, UINT32 *Day);
BOOL GPSRec_GetUTCTime(UINT32 *Hour, UINT32 *Minute, UINT32 *Second);
THREAD_RETTYPE GPS_TASK(void *pvParameters);

//#HTK#2023/08/30#add edog -start
void GPSGetData_Lock(void);
void GPSGetData_Unlock(void);
char *GPSRec_GetString(void);
UINT32 GPSRec_GetStringLen(void);
void GPSRec_ResetString(void);
//#HTK#2023/08/30#add edog -end

CHAR uiMovieStampData[128] = {0};
CHAR g_cLongitude_buffer[16] = {0};
CHAR g_cDimensionality_buffer[16] = {0};
CHAR g_cDirectAngle[16] = {0};

extern UINT32 SysGet_TimeZoneValue(void);

EDOG_SATELLITE_DB g_Edog_satellie_DB;
BOOL g_bEdogSatelliteDBMSG = FALSE;
BOOL g_GPSLinked = FALSE;
BOOL g_GPSStatus = FALSE;
FLOAT g_CurSpeed = 0.0;

INT8 uigpsstatus = -1;
//static UINT32 GPS_year=2017,GPS_month=1,GPS_day=1;
//static UINT32 GPS_hour=0,GPS_min=0,GPS_second=0;
static BOOL AddDayFlag   = FALSE;
static BOOL AddMonthFlag = FALSE;
static BOOL DecDayFlag   = FALSE;
static BOOL DecMonthFlag = FALSE;
static int siGPSBeingCnt = 0;
INT8 uiSpeed_Uint = 0;
INT8 data_errflag =0;
static BOOL GSA_Flag = TRUE;
static THREAD_HANDLE gps_thread;

INT32 GPSRec_getAngle(void)
{
	INT32 idirection = 0;
	DIRTYPE diretion = 0;
	idirection = RMCInfo.Angle;

	//debug_msg("idirection  :%d\r\n",idirection);

	//memset(g_cDirectAngle,0,16);

	if(idirection > 337 || idirection < 23)  //north
	{
		sprintf(g_cDirectAngle, "N");
		diretion = NORTH;
	}
	else if(idirection > 292 && idirection <= 337)	//north west
	{
		sprintf(g_cDirectAngle, "NW");
		diretion = NORTH_WEST;
	}
	else if(idirection > 247 && idirection <= 292)	//west
	{
		sprintf(g_cDirectAngle, "W");
		diretion = WEST;
	}
	else if(idirection > 202 && idirection <= 247)	//south west
	{
		sprintf(g_cDirectAngle, "SW");
		diretion = SOUTH_WEST;
	}
	else if(idirection > 157 && idirection <= 202)	//south
	{
		sprintf(g_cDirectAngle, "S");
		diretion = SOUTH;
	}
	else if(idirection > 112 && idirection <= 157)	//south east
	{
		sprintf(g_cDirectAngle, "SE");
		diretion = SOUTH_EAST;
	}
	else if(idirection > 67 && idirection <= 112)	//east
	{
		sprintf(g_cDirectAngle, "E");
		diretion = EAST;
	}
	else if(idirection >= 23  && idirection <= 67)	//north east
	{
		sprintf(g_cDirectAngle, "NE");
		diretion = NORTH_EAST;
	}
	return diretion;
}


double GetRealXY(double dXY)
{
    double dRealXY = dXY/100.0;
    int nXYDegree = (int) dXY/100;
    double dDecimal = dRealXY - nXYDegree;
    dDecimal = (dDecimal*100.0/60.0);
    dRealXY = nXYDegree + dDecimal;
    return dRealXY;
}

//Real xx.xxxxx to RMC. Original 20170821
static double GetGPSXY(double rXY)
{
	double dGPSXY;

	int nXYDegree = (int) rXY*100;
	double dDecimal = rXY - (int) rXY;
	dDecimal = (dDecimal*60.0/100.0)*100;
	dGPSXY = nXYDegree + dDecimal;
	
	return dGPSXY;
}

UINT32 GPSRec_GetGPS_Month(void)
{
    if(AddMonthFlag == TRUE)
    {
        AddMonthFlag = FALSE;
        if((RMCInfo.Month+1)>12)
        {
            RMCInfo.Year = RMCInfo.Year+1;
            return 1;
        }
        else
            return RMCInfo.Month+1;
    }
    else if(DecMonthFlag == TRUE)
    {
        DecMonthFlag = FALSE;
        if((RMCInfo.Month-1) == 0)
        {
            RMCInfo.Year = RMCInfo.Year-1;
            return 12;
        }
        else
            return RMCInfo.Month-1;
    }
    else
    {
        return RMCInfo.Month;
    }
}

UINT32 GPSRec_GetGPS_Day(void)
{
    UINT32 AddValue = 0;
    UINT32 DecValue = 0;
    BOOL SpecialTimeZoneAddFlag = FALSE;
    BOOL SpecialTimeZoneDecFlag = FALSE;

    switch(SysGet_TimeZoneValue())
    {
    case GPSGMT_M12:    DecValue = 12;      break;
    case GPSGMT_M11:    DecValue = 11;      break;
    case GPSGMT_M10:    DecValue = 10;      break;
    case GPSGMT_M9:     DecValue = 9;       break;
    case GPSGMT_M8:     DecValue = 8;       break;
    case GPSGMT_M7:     DecValue = 7;       break;
    case GPSGMT_M6:     DecValue = 6;       break;
    case GPSGMT_M5:     DecValue = 5;       break;
    case GPSGMT_M4:     DecValue = 4;       break;
    case GPSGMT_M3:     DecValue = 3;       break;
    case GPSGMT_M2:     DecValue = 2;       break;
    case GPSGMT_M1:     DecValue = 1;       break;
    case GPSGMT_0:
        AddValue = 0;
        DecValue = 0;
        break;
    case GPSGMT_P1:     AddValue = 24 -1;   break;
    case GPSGMT_P2:     AddValue = 24 -2;   break;
    case GPSGMT_P3:     AddValue = 24 -3;   break;
    case GPSGMT_P4:     AddValue = 24 -4;   break;
    case GPSGMT_P5:     AddValue = 24 -5;   break;
    case GPSGMT_P6:     AddValue = 24 -6;   break;
    case GPSGMT_P7:     AddValue = 24 -7;   break;
    case GPSGMT_P8:     AddValue = 24 -8;   break;
    case GPSGMT_P9:     AddValue = 24 -9;   break;
    case GPSGMT_P10:    AddValue = 24 -10;  break;
    case GPSGMT_P11:    AddValue = 24 -11;  break;
    case GPSGMT_P12:    AddValue = 24 -12;  break;
    case GPSGMT_P13:    AddValue = 24 -13;  break;
    case GPSGMT_M2_30:
        if((RMCInfo.Hour < 2)||((RMCInfo.Hour == 2)&&(RMCInfo.Minute <= 30)))
            SpecialTimeZoneDecFlag = TRUE;
        break;
    case GPSGMT_M3_30:
        if((RMCInfo.Hour < 3)||((RMCInfo.Hour == 3)&&(RMCInfo.Minute <= 30)))
            SpecialTimeZoneDecFlag = TRUE;
        break;
    case GPSGMT_P3_30:
        if((RMCInfo.Hour > 20)||((RMCInfo.Hour == 20)&&(RMCInfo.Minute >= 30)))
            SpecialTimeZoneAddFlag = TRUE;
        break;
    case GPSGMT_P4_30:
        if((RMCInfo.Hour > 19)||((RMCInfo.Hour == 19)&&(RMCInfo.Minute >= 30)))
            SpecialTimeZoneAddFlag = TRUE;
        break;
    case GPSGMT_P5_30:
        if((RMCInfo.Hour > 18)||((RMCInfo.Hour == 18)&&(RMCInfo.Minute >= 30)))
            SpecialTimeZoneAddFlag = TRUE;
        break;
    case GPSGMT_P6_30:
        if((RMCInfo.Hour > 17)||((RMCInfo.Hour == 17)&&(RMCInfo.Minute >= 30)))
            SpecialTimeZoneAddFlag = TRUE;
        break;
    case GPSGMT_P9_30:
        if((RMCInfo.Hour > 14)||((RMCInfo.Hour == 14)&&(RMCInfo.Minute >= 30)))
            SpecialTimeZoneAddFlag = TRUE;
        break;
    case GPSGMT_P10_30:
        if((RMCInfo.Hour > 13)||((RMCInfo.Hour == 13)&&(RMCInfo.Minute >= 30)))
            SpecialTimeZoneAddFlag = TRUE;
        break;

    default:
        break;
    }

    if((AddValue != 0)||(SpecialTimeZoneAddFlag == TRUE))
    {
        if((RMCInfo.Hour >= AddValue)||(SpecialTimeZoneAddFlag == TRUE))
        {
            AddDayFlag = TRUE;
            switch(RMCInfo.Month)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if((RMCInfo.Day+1)>31)
                    AddMonthFlag = TRUE;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if((RMCInfo.Day+1)>30)
                    AddMonthFlag = TRUE;
                break;
            case 2:
                if(((RMCInfo.Year+2000)%4 == 0)&&((RMCInfo.Year+2000)%100 != 0))
                {
                    if((RMCInfo.Day+1)>29)
                        AddMonthFlag = TRUE;
                }
                else
                {
                    if((RMCInfo.Day+1)>28)
                        AddMonthFlag = TRUE;
                }
                break;
            default:
                break;
            }
            if(AddMonthFlag == TRUE)
                return 1;
            else
                return RMCInfo.Day+1;
        }
        else
        {
            return RMCInfo.Day;
        }
    }
    if((DecValue != 0)||(SpecialTimeZoneDecFlag == TRUE))
    {
        if((RMCInfo.Hour < DecValue)||(SpecialTimeZoneDecFlag == TRUE))
        {
            DecDayFlag = TRUE;
            switch(RMCInfo.Month)
            {
            case 1:
            case 2:
            case 4:
            case 6:
            case 8:
            case 9:
            case 11:
                if((RMCInfo.Day-1) == 0)
                {
                    DecMonthFlag = TRUE;
                    return 31;
                }
                break;
            case 5:
            case 7:
            case 10:
            case 12:
                if((RMCInfo.Day-1) == 0)
                {
                    DecMonthFlag = TRUE;
                    return 30;
                }
                break;
            case 3:
                if(((RMCInfo.Year+2000)%4 == 0)&&((RMCInfo.Year+2000)%100 != 0))
                {
                    if((RMCInfo.Day-1)== 0)
                    {
                        DecMonthFlag = TRUE;
                        return 29;
                    }
                }
                else
                {
                    if((RMCInfo.Day-1)== 0)
                    {
                        DecMonthFlag = TRUE;
                        return 28;
                    }
                }
                break;
            default:
                break;
            }
            return RMCInfo.Day-1;
        }
        else
        {
            return RMCInfo.Day;
        }
    }
    return RMCInfo.Day;
}


UINT32 GPSRec_GetGPS_Hour(void)
{
    switch(SysGet_TimeZoneValue())
    {
    case GPSGMT_M12:
        return(RMCInfo.Hour + 24-12);
        break;
    case GPSGMT_M11:
        return(RMCInfo.Hour + 24-11);
        break;
    case GPSGMT_M10:
        return(RMCInfo.Hour + 24-10);
        break;
    case GPSGMT_M9:
        return(RMCInfo.Hour + 24-9);
        break;
    case GPSGMT_M8:
        return(RMCInfo.Hour + 24-8);
        break;
    case GPSGMT_M7:
        return(RMCInfo.Hour + 24-7);
        break;
    case GPSGMT_M6:
        return(RMCInfo.Hour + 24-6);
        break;
    case GPSGMT_M5:
        return(RMCInfo.Hour + 24-5);
        break;
    case GPSGMT_M4:
        return(RMCInfo.Hour + 24-4);
        break;
    case GPSGMT_M3:
        return(RMCInfo.Hour + 24-3);
        break;
    case GPSGMT_M2:
        return(RMCInfo.Hour + 24-2);
        break;
    case GPSGMT_M1:
        return(RMCInfo.Hour + 24-1);
        break;
    case GPSGMT_0:	return RMCInfo.Hour;
        break;
    case GPSGMT_P1:	return RMCInfo.Hour + 1;
        break;
    case GPSGMT_P2:	return RMCInfo.Hour + 2;
        break;
    case GPSGMT_P3:	return RMCInfo.Hour + 3;
        break;
    case GPSGMT_P4:	return RMCInfo.Hour + 4;
        break;
    case GPSGMT_P5:	return RMCInfo.Hour + 5;
        break;
    case GPSGMT_P6:	return RMCInfo.Hour + 6;
        break;
    case GPSGMT_P7:	return RMCInfo.Hour + 7;
        break;
    case GPSGMT_P8:	return RMCInfo.Hour + 8;
        break;
    case GPSGMT_P9:	return RMCInfo.Hour + 9;
        break;
    case GPSGMT_P10:	return RMCInfo.Hour + 10;
        break;
    case GPSGMT_P11:	return RMCInfo.Hour + 11;
        break;
    case GPSGMT_P12:	return RMCInfo.Hour + 12;
        break;
    case GPSGMT_P13:	return RMCInfo.Hour + 13;
        break;
    case GPSGMT_M2_30:
        return(RMCInfo.Hour + 24-2);
        break;
    case GPSGMT_M3_30:
        return(RMCInfo.Hour + 24-3);
        break;
    case GPSGMT_P3_30:	return RMCInfo.Hour + 3;
        break;
    case GPSGMT_P4_30:	return RMCInfo.Hour + 4;
        break;
    case GPSGMT_P5_30:	return RMCInfo.Hour + 5;
        break;
    case GPSGMT_P6_30:  return RMCInfo.Hour + 6;
        break;
    case GPSGMT_P9_30:	return RMCInfo.Hour + 9;
        break;
    case GPSGMT_P10_30:	return RMCInfo.Hour + 10;
        break;
    default:
        return RMCInfo.Hour;
        break;
    }
}

UINT32 GPSRec_GetGPS_Minute(void)
{
    switch(SysGet_TimeZoneValue())
    {
    case GPSGMT_M2_30:
    case GPSGMT_M3_30:
        if(RMCInfo.Minute > 30)
        { 
            RMCInfo.Minute =RMCInfo.Minute - 30;
            return RMCInfo.Minute;
        }
        else
        {
            RMCInfo.Minute =60 - 30 + RMCInfo.Minute;
            RMCInfo.Hour =RMCInfo.Hour-1;
            return RMCInfo.Minute;
        }
        break;
    case GPSGMT_P3_30:
    case GPSGMT_P4_30:
    case GPSGMT_P5_30:
    case GPSGMT_P6_30:
    case GPSGMT_P9_30:
    case GPSGMT_P10_30:
        if(RMCInfo.Minute < 30)
        {
            RMCInfo.Minute=RMCInfo.Minute + 30;
            return RMCInfo.Minute ;
        }
        else
        {
            RMCInfo.Minute=RMCInfo.Minute + 30 - 60;
            RMCInfo.Hour =RMCInfo.Hour+1;
            return RMCInfo.Minute ;
        }
        break;
    default:
        return RMCInfo.Minute;
        break;
    }
}

void GPSRec_GetRMCNData(void)
{
#if 1
	if(edogCBdata_update_ok)
	{
		Latitude_current = RMCInfo.Latitude;
		Latitude_before = Latitude_current;
	}
	else
	{
		Latitude_current = Latitude_before;
	}
    sprintf(g_cDimensionality_buffer, "%f",GetRealXY(Latitude_current));
	//sprintf(g_cDimensionality_buffer, "%f",Latitude_current);
#else //delete by chase

    CHAR temp_Latitude[16]={0};
    UINT32 len=0,i=0,j=0,doc_position=0;
    CHAR tmp[16] = {0};

    sprintf(temp_Latitude, "%f",RMCInfo.Latitude);

    len = strlen(temp_Latitude);

    for(i = 0;i < len;i++)
    {
        if(temp_Latitude[i] == '.')
        {
            doc_position = i;
            break;
        }
        //debug_msg("RMC_LA=%c \r\n",temp_Latitude[i]);
    }

    if (doc_position < 2)
    {
        return;
    }

    tmp[0] = temp_Latitude[doc_position-1];
    tmp[1] = temp_Latitude[doc_position-2];
    tmp[2] = '.';

    temp_Latitude[doc_position-2]=tmp[2] ;
    temp_Latitude[doc_position-1]=tmp[1] ;
    temp_Latitude[doc_position]=tmp[0] ;

    //debug_msg("***LA= %s Tmp=%s  LEN=%d\r\n",temp_Latitude,tmp,len);
    for(j=0;j<(doc_position+3);j++)
    {
        //debug_msg("@@@LA= %c  J=%d\r\n",temp_Latitude[j],j);
        g_cDimensionality_buffer[j]= temp_Latitude[j];
    }
#endif
}

void GPSRec_GetRMCEData(void)
{
#if 1
    if(edogCBdata_update_ok)
	{
		Longitude_current = RMCInfo.Longitude;
		Longitude_before = Longitude_current;
	}
	else
	{
		Longitude_current = Longitude_before;
	}
    sprintf(g_cLongitude_buffer, "%f",GetRealXY(Longitude_current));
    //sprintf(g_cLongitude_buffer, "%f",Longitude_current);
#else //delete by chase

    CHAR temp_Logitude[16]={0};
    UINT32 len=0,i=0,j=0,doc_position=0;
    CHAR tmp[16] = {0};

    sprintf(temp_Logitude, "%f",RMCInfo.Longitude);

    len = strlen(temp_Logitude);

    for(i = 0;i < len;i++)
    {
        if(temp_Logitude[i] == '.')
        {
            doc_position = i;
            break;
        }
        //debug_msg("RMC_LO=%c \r\n",temp_Logitude[i]);
    }

    if (doc_position < 2)
    {
        return;
    }

    tmp[0] = temp_Logitude[doc_position-1];
    tmp[1] = temp_Logitude[doc_position-2];
    tmp[2] = '.';

    temp_Logitude[doc_position-2]=tmp[2] ;
    temp_Logitude[doc_position-1]=tmp[1] ;
    temp_Logitude[doc_position]=tmp[0] ;

    //debug_msg("***LO= %s Tmp=%s  LEN=%d\r\n",temp_Logitude,tmp,len);
    for(j=0;j<(doc_position+3);j++)
    {
        //debug_msg("@@@LO= %c  J=%d\r\n",temp_Logitude[j],j);
        g_cLongitude_buffer[j]= temp_Logitude[j];
    }
#endif
}

char *GPS_GetMovieData(void)
{
    if (RMCInfo.Speed > 300)
    {
        return uiMovieStampData;
    }

	if(edogCBdata_update_ok)
	{
		speed_current = RMCInfo.Speed;
		speed_before = speed_current;
		angle_curret = RMCInfo.Angle;
		angle_before = angle_curret;
		NS_current = RMCInfo.NSInd;
		NS_before = NS_current;
		EW_current = RMCInfo.EWInd;
		EW_before = EW_current;
		Latitude_current = RMCInfo.Latitude;
		Latitude_before = Latitude_current;
		Longitude_current = RMCInfo.Longitude;
		Longitude_before = Longitude_current;
	}
	else
	{
		speed_current = speed_before;
		angle_curret = angle_before;
		NS_current = NS_before;
		EW_current = EW_before;
		Latitude_current = Latitude_before;
		Longitude_current = Longitude_before;
	}
	GPSRec_GetRMCEData();
	GPSRec_GetRMCNData();
	if (uiSpeed_Uint == 1) //SPEED_UNIT_MPH
	{
		sprintf(uiMovieStampData, "%c%s %c%s %d Mph",EW_current,g_cLongitude_buffer,NS_current,g_cDimensionality_buffer,(INT32)(speed_current * 1.15078));
	}
	else
	{
		sprintf(uiMovieStampData, "%c%s %c%s %d km/h",EW_current,g_cLongitude_buffer,NS_current,g_cDimensionality_buffer,(INT32)(speed_current * 1.852));
	}

    //sprintf(uiMovieStampData, "%c%s %c%s %d km/h", RMCInfo.EWInd, g_cLongitude_buffer, RMCInfo.NSInd,g_cDimensionality_buffer,(INT32)(RMCInfo.Speed * 1.852));
    //sprintf(uiMovieStampData, "%c%s %c%s %s %dkm/h", RMCInfo.EWInd, g_cLongitude_buffer, RMCInfo.NSInd,g_cDimensionality_buffer,g_cDirectAngle,(INT32)(RMCInfo.Speed * 1.852));
    //sprintf(uiMovieStampData, "%c%1f %c%1f %s %s", RMCInfo.EWInd, RMCInfo.Latitude, RMCInfo.NSInd,RMCInfo.Longitude,g_cDirectAngle,Speed1);
    return uiMovieStampData;
}

char *GPS_GetMovieData_Coordinates(void)
{
	if(edogCBdata_update_ok)
	{
		//speed_current = RMCInfo.Speed;
		//speed_before = speed_current;
		//angle_curret = RMCInfo.Angle;
		//angle_before = angle_curret;
		NS_current = RMCInfo.NSInd;
		NS_before = NS_current;
		EW_current = RMCInfo.EWInd;
		EW_before = EW_current;
		Latitude_current = RMCInfo.Latitude;
		Latitude_before = Latitude_current;
		Longitude_current = RMCInfo.Longitude;
		Longitude_before = Longitude_current;
	}
	else
	{
		//speed_current = speed_before;
		//angle_curret = angle_before;
		NS_current = NS_before;
		EW_current = EW_before;
		Latitude_current = Latitude_before;
		Longitude_current = Longitude_before;
	}

	GPSRec_GetRMCEData();
	GPSRec_GetRMCNData();
	sprintf(uiMovieStampData, "%c%s %c%s", EW_current,g_cLongitude_buffer, NS_current,g_cDimensionality_buffer);
    return uiMovieStampData;
}

char *GPS_GetMovieData_Speed(void)
{

    if (RMCInfo.Speed > 300)
    {
        return uiMovieStampData;
    }

	if(edogCBdata_update_ok)
	{
		speed_current = RMCInfo.Speed;
		speed_before = speed_current;
		//angle_curret = RMCInfo.Angle;
		//angle_before = angle_curret;
		//NS_current = RMCInfo.NSInd;
		//NS_before = NS_current;
		//EW_current = RMCInfo.EWInd;
		//EW_before = EW_current;
		//Latitude_current = RMCInfo.Latitude;
		//Latitude_before = Latitude_current;
		//Longitude_current = RMCInfo.Longitude;
		//Longitude_before = Longitude_current;
	}
	else
	{
		speed_current = speed_before;
		//angle_curret = angle_before;
		//NS_current = NS_before;
		//EW_current = EW_before;
		//Latitude_current = Latitude_before;
		//Longitude_current = Longitude_before;
	}

	if (uiSpeed_Uint == 1) //SPEED_UNIT_MPH
	{
		sprintf(uiMovieStampData, "%d Mph", (INT32)(speed_current* 1.15078));
	}
	else
	{
		sprintf(uiMovieStampData, "%d km/h", (INT32)(speed_current*1.852));
	}
    return uiMovieStampData;
}
sem_t sem;

void GPS_InstallID(void)
{
    //OS_CONFIG_TASK(GPSRECEIVE_ID, PRI_GPSRECEIVE, STKSIZE_GPSRECEIVE, GPSRecTsk);
    //OS_CONFIG_FLAG(FLG_ID_GPS);
	sem_init(&sem, 0, 1);
	if ((gps_thread = vos_task_create(GPS_TASK, 0, "GPSTsk", PRI_GPSRECEIVE, STKSIZE_GPSRECEIVE)) == 0) {
		DBG_ERR("==GPSTsk create failed.====\r\n");
	} else {
		DBG_ERR("==GPSTsk create success.====\r\n");
	    vos_task_resume(gps_thread);
	}
}

void GPS_UninstallID(void)
{
	DBG_DUMP("===Destroy GPSTsk====\r\n");
	vos_task_destroy(gps_thread);
}

void GPS_SetUartObj(GPS_UART_OBJ *UartObj)
{
	memcpy(&GpsUart, UartObj, sizeof(GPS_UART_OBJ));
}

static BOOL bGPSRecOpened = FALSE;
ER GPSRec_Open(void)
{
    Dx_InitGPS_PWREN();
    usleep(1000);
    if (bGPSRecOpened)
        return E_SYS;

    if (GpsUart.open() == E_OK)
    {
        DBG_DUMP("UART open success\r\n");
        GpsUart.init();
    }
    else
    {
        DBG_ERR("UART open fail!\r\n");
        return E_SYS;
    }

    DBG_DUMP("Start GPS receive task\r\n");
    //sta_tsk(GPSRECEIVE_ID,0);

    //loc_cpu();
    bGPSRecOpened = TRUE;
    //unl_cpu();
    GPS_InstallID();
    return E_OK;
}

ER GPSRec_Close(void)
{
    if (!bGPSRecOpened)
        return E_SYS;

    if (GpsUart.close() == E_OK)
        DBG_DUMP("UART close success\r\n");
    else
        DBG_ERR("UART close fail!\r\n");

    DBG_DUMP("Terminate GPS receive task\r\n");

    //ter_tsk(GPSRECEIVE_ID);

    //loc_cpu();
    bGPSRecOpened = FALSE;
    //unl_cpu();
	
	GPS_UninstallID();
	Dx_InitGPS_NOPWREN();
    return E_OK;
}

#if 0
void GPSRecTsk(void)
{
    UINT32  uiLen;
    UINT16  CheckSentenceType1, CheckSentenceType2;
    UINT32  CheckSentenceType3;
    CHAR    RecSentence[NMEA_SENTENCE_SIZE];
    CHAR    *pSentenceData;

    //kent_tsk();

    //clr_flg(FLG_ID_GPS, GPS_FLAG_DATAVALID);

    while(GPSRECEIVE_ID)
    {
        uiLen = NMEA_SENTENCE_SIZE;
        if (GpsUart.getString(RecSentence, &uiLen) == E_PAR)
        {
            DBG_ERR("UART parameter error!\r\n");
        }
        //DBG_DUMP("%s\r\n", RecSentence);
        //Each NMEA sentence begins with '$' (0x24)
        if (RecSentence[0] == 0x24)
        {
            GPSHeartBeat ++;        //#NT#2015/10/02#KCHong#Add GPS heartbeat to detect GPS status
            pSentenceData = RecSentence;
            CheckSentenceType1 = *(UINT16 *)(pSentenceData + 2);
            CheckSentenceType2 = *(UINT16 *)(pSentenceData + 4);
            CheckSentenceType3 = ((UINT)CheckSentenceType2 << 16) | (UINT)CheckSentenceType1;

            switch(CheckSentenceType3)
            {
            case GSA_SENTENCE:
                NMEASentence.GSA = RecSentence;
                GPSRec_NMEAParser(RecSentence, uiLen, GSA);
                break;

            case RMC_SENTENCE:
                NMEASentence.RMC = RecSentence;
                GPSRec_NMEAParser(RecSentence, uiLen, RMC);
                break;

            case GGA_SENTENCE:
                NMEASentence.GGA = RecSentence;
                GPSRec_NMEAParser(RecSentence, uiLen, GGA);
                break;

            case GSV_SENTENCE:
                NMEASentence.GSV = RecSentence;
                GPSRec_NMEAParser(RecSentence, uiLen, GSV);
                break;

            case GLL_SENTENCE:
                NMEASentence.GLL = RecSentence;
                GPSRec_NMEAParser(RecSentence, uiLen, GLL);
                break;

            case VTG_SENTENCE:
                NMEASentence.VTG = RecSentence;
                GPSRec_NMEAParser(RecSentence, uiLen, VTG);
                break;

            default:
                DBG_ERR("GPS: Can't identify this sentence 0x%X \r\n",CheckSentenceType3);
                break;
            }

        }

    }

}
#endif

ER GPSRec_Reset(void)
{
    return E_OK;
}

BOOL GPSRec_CheckData(void)
{
    //DBG_DUMP("GPS: DATA VALID: 0x%X\r\n", kchk_flg(FLG_ID_GPS, GPS_FLAG_DATAVALID));
    //if (kchk_flg(FLG_ID_GPS, GPS_FLAG_DATAVALID))
        return TRUE;
    //else
    //    return FALSE;
    
}


UINT16 GPSRec_TransformData(CHAR *NMEA_str, UINT32 Len, CHAR *pPostPrt, UINT32 *PostPtrLen)
{
    UINT32 i;
    UINT16 count = 0;

    //Process sentence, change ',' as ' '.
    //If message is null, change to corresponding value.
    // DBG_DUMP("%s\n", NMEA_str);
     //DBG_DUMP("call Len = %d\r\n",strlen(NMEA_str)); 
    bzero(pPostPrt,Len);
    Len = strlen(NMEA_str);
    *PostPtrLen = Len;
    for (i = 0; i <= Len; i++)
    {
        *pPostPrt = *NMEA_str;

        if (*NMEA_str == ',')
        {
            *pPostPrt = 0x20;   //Instead of ' '
            if ((*(NMEA_str+1) == ',')|(*(NMEA_str+1) == '*'))
            {
                *++pPostPrt = 0x30;  //Insert '0'
                *PostPtrLen = *PostPtrLen + 1;
            }
            count++;
        }
        else if ((*NMEA_str == '*')|(i == Len))
        {
            *pPostPrt = 0x20;   //Instead of ' '
        }

        NMEA_str++;
        pPostPrt++;

    }

    NMEA_str -= Len;
    pPostPrt -= *PostPtrLen;
    //DBG_DUMP("pPostPrt = %s\r\n",pPostPrt);
    //DBG_DUMP("call count = %d\r\n",count);	
    //DBG_DUMP("\n");
   //DBG_DUMP("\n");
    return count;
}

BOOL GPSRec_CheckSum(CHAR *NMEA_str, UINT32 Len, UINT32 CheckSum)
{
    UINT32 i, LenTemp = 1;
    CHAR XORData;
    XORData = *(NMEA_str++);

    //Doing 8 bit exclusive OR of all characters between, but not including, the '$' and '*'.
    for (i = 1; i < Len; i++)
    {
        NMEA_str++;
        if (*NMEA_str == '*')
            break;

        LenTemp++;
        XORData ^= *NMEA_str;
    }
    NMEA_str -= LenTemp;

    if (XORData == (CHAR)CheckSum)
    {
        return TRUE;
    }
    else
    {
        DBG_ERR("GPS: check sum error! 0x%X != 0x%X\r\n",CheckSum, XORData);
        return FALSE;
    }

}


void GPSRec_NMEAParser(CHAR *NMEA_str, UINT32 Len, NMEATYPE NMEAtype)
{
    UINT32 i;
    UINT16 dotCount = 0;

    pPostPrt = PostPtr;
    PostPtrLen = Len;

    dotCount = GPSRec_TransformData(NMEA_str, Len, pPostPrt, &PostPtrLen);
    switch(NMEAtype)
    {
    case GSA:
        sscanf(pPostPrt, "%s %c %d %d %d %d %d %d %d %d %d %d %d %d %d %lf %lf %lf %X\n", type, &SelMode, &FixMode, &SatUsed01, &SatUsed02, &SatUsed03, &SatUsed04, &SatUsed05, &SatUsed06, &SatUsed07, &SatUsed08, &SatUsed09, &SatUsed10, &SatUsed11, &SatUsed12, &PDOP, &HDOP, &VDOP, &CheckSum);
        #if (_GPS_CheckSum_Enable)
            GPSRec_CheckSum(NMEA_str, Len, CheckSum);
        #endif

        if (FixMode != No_Fix)
        {
            GSAInfo.SelMode = SelMode;
            GSAInfo.FixMode = FixMode;
            GSAInfo.SatUsed01 = SatUsed01;
            GSAInfo.SatUsed02 = SatUsed02;
            GSAInfo.SatUsed03 = SatUsed03;
            GSAInfo.SatUsed04 = SatUsed04;
            GSAInfo.SatUsed05 = SatUsed05;
            GSAInfo.SatUsed06 = SatUsed06;
            GSAInfo.SatUsed07 = SatUsed07;
            GSAInfo.SatUsed08 = SatUsed08;
            GSAInfo.SatUsed09 = SatUsed09;
            GSAInfo.SatUsed10 = SatUsed10;
            GSAInfo.SatUsed11 = SatUsed11;
            GSAInfo.SatUsed12 = SatUsed12;
            GSAInfo.PDOP = PDOP;
            GSAInfo.HDOP = HDOP;
            GSAInfo.VDOP = VDOP;
            GPS_debug(("#GSA SelMode = %c, FixMode = %d \r\n",GSAInfo.SelMode,GSAInfo.FixMode));
            GPS_debug(("#GSA SelMode = %c, FixMode = %d \r\n",GSAInfo.SelMode,GSAInfo.FixMode));
            GPS_debug(("#GSA SatUsed1 = %d, %d, %d, %d \r\n",GSAInfo.SatUsed01,GSAInfo.SatUsed02, GSAInfo.SatUsed03, GSAInfo.SatUsed04));
            GPS_debug(("#GSA SatUsed2 = %d, %d, %d, %d \r\n",GSAInfo.SatUsed05,GSAInfo.SatUsed06, GSAInfo.SatUsed07, GSAInfo.SatUsed08));
            GPS_debug(("#GSA SatUsed3 = %d, %d, %d, %d \r\n",GSAInfo.SatUsed09,GSAInfo.SatUsed10, GSAInfo.SatUsed11, GSAInfo.SatUsed12));
            GPS_debug(("#PDOP = %.1f, HDOP = %.1f, VDOP = %.1f CheckSum = %X\r\n",GSAInfo.PDOP,GSAInfo.HDOP, GSAInfo.VDOP,CheckSum));
        }

		if ((SelMode == 'A') && (FixMode == 2)) {
			GSA_Flag = FALSE;
			//DBG_DUMP("call GSA is 2D \r\n");
		} else {
			GSA_Flag = TRUE;
		}
		
        if (Len)
        {
            for (i = 0; i < Len; i++)
                NMEA_debug(("%c",*NMEA_str++));
        }
        NMEA_debug(("\r\n"));

        //Check processed sentence
        /*
        if (PostPtrLen)
        {
            for (i = 0; i < PostPtrLen; i++)
                NMEA_debug(("%c",*pPostPrt++));
        }
        NMEA_debug(("\r\n"));
        */
        break;

    case RMC:
        sscanf(pPostPrt, "%s %lf %c %lf %c %lf %c %lf %lf %d %lf %c %X\n", type, &UTCTime, &Status, &Lat, &NSInd, &Lon, &EWInd, &Speed, &Angle, &Date, &MagVar, &MagVarInd, &CheckSum);
        #if (_GPS_CheckSum_Enable)
            GPSRec_CheckSum(NMEA_str, Len, CheckSum);
        #endif

		//DBG_WRN("-------- dotCount = %d\r\n", dotCount);
		if ((dotCount != 12)/* ||(!GSA_Flag)*/)
		{
			//DBG_DUMP("dotCount = %d\r\n",dotCount);
			data_errflag = 1;
			//DBG_DUMP("call RMC  Speed  = %d \r\n",Speed);
			break;
		} else {
			data_errflag = 0;
		}

        {
            RMCInfo.Hour =      (UINT32)UTCTime / 10000;
            RMCInfo.Minute =    ((UINT32)UTCTime % 10000) / 100;
            RMCInfo.Second =    ((UINT32)UTCTime % 100);
            RMCInfo.Status =    Status;
            RMCInfo.Latitude =  Lat;
            RMCInfo.NSInd =     NSInd;
            RMCInfo.Longitude = Lon;
            RMCInfo.EWInd =     EWInd;
            RMCInfo.Speed =     Speed;
            RMCInfo.Angle =     Angle;
            RMCInfo.Day =       Date / 10000;
            RMCInfo.Month =     (Date % 10000) / 100;
            RMCInfo.Year =      (Date % 100);
        }

        //DBG_WRN("------Status = %c\r\n", Status);
        if (Status == 'A')   //Data valid
        {
            uigpsstatus = 1;
            //set_flg(FLG_ID_GPS, GPS_FLAG_DATAVALID);

            RMCInfo.Day = GPSRec_GetGPS_Day();
            RMCInfo.Month = GPSRec_GetGPS_Month();
            RMCInfo.Hour = GPSRec_GetGPS_Hour();
            RMCInfo.Minute = GPSRec_GetGPS_Minute();

            //debug_msg("*** GPS=%d %d %d ***\r\n",RMCInfo.Hour,RMCInfo.Day,SpecalAdd);
            if (RMCInfo.Hour > 23)
            {
                RMCInfo.Hour = RMCInfo.Hour-24;

                //if(SpecalAdd ==FALSE)
                //    RMCInfo.Day=RMCInfo.Day+1;
            }
            GPS_debug(("uigpsstatus=%d\r\n",uigpsstatus));
            GPS_debug(("\x1b[34m"));   //Blue
            GPS_debug(("#RMC: Status = %c, Speed = %.1f, Angle = %.1f \r\n",RMCInfo.Status,RMCInfo.Speed,RMCInfo.Angle));
            GPS_debug(("#RMC: Date = %d\\%d\\%d CheckSum = %X\r\n",RMCInfo.Year,RMCInfo.Month,RMCInfo.Day,CheckSum));
            GPS_debug(("\x1b[30m"));   //Black
        }
        else if (Status == 'V')
        {
            GPS_debug(("uigpsstatus=%d\r\n",uigpsstatus));
            uigpsstatus = 0;
            //clr_flg(FLG_ID_GPS, GPS_FLAG_DATAVALID);
        }

        NMEA_debug(("\x1b[34m"));   //Blue
        if (Len)
        {
            for (i = 0; i < Len; i++)
                NMEA_debug(("%c",*NMEA_str++));
        }
        NMEA_debug(("\r\n"));
        //Check processed sentence
        /*
        if (PostPtrLen)
        {
            for (i = 0; i < PostPtrLen; i++)
                NMEA_debug(("%c",*pPostPrt++));
        }
        NMEA_debug(("\r\n"));
        */
        NMEA_debug(("\x1b[30m"));   //Black
        break;

    case GGA:
        sscanf(pPostPrt, "%s %lf %lf %c %lf %c %d %d %lf %lf %c %lf %c %d %d %X\n", type, &UTCTime, &Lat, &NSInd, &Lon, &EWInd, &PosFixInd, &SatNumber, &HDOP, &Alt, &M1, &MSL, &M2, &Empty1, &Empty2, &CheckSum);
        #if (_GPS_CheckSum_Enable)
            GPSRec_CheckSum(NMEA_str, Len, CheckSum);
        #endif

        // if (PosFixInd == 1)  //Data valid
        {
            GGAInfo.Hour = (UINT32)UTCTime / 10000;
            GGAInfo.Minute = ((UINT32)UTCTime % 10000) / 100;
            GGAInfo.Second = ((UINT32)UTCTime % 100);
            GGAInfo.Latitude = Lat;
            GGAInfo.NSInd = NSInd;
            GGAInfo.Longitude = Lon;
            GGAInfo.EWInd = EWInd;
            GGAInfo.PosFixInd = PosFixInd;
            GGAInfo.SatNumber = SatNumber;
            GGAInfo.HDOP = HDOP;
            GGAInfo.Altitude = Alt;
            GGAInfo.MSL = MSL;
            GPS_debug(("\x1b[31m"));   //Red
            GPS_debug(("#GGA: Time = %d:%d:%d CheckSum = %X\r\n", GGAInfo.Hour, GGAInfo.Minute, GGAInfo.Second,CheckSum));
            GPS_debug(("#GGA: Lat = %1f %c, Lon = %1f %c \r\n", GGAInfo.Latitude, NSInd, GGAInfo.Longitude, EWInd));
            GPS_debug(("#GGA: PosFixInd = %d, SatNum = %d, HDOP = %2.1f, Alt = %.1f, MSL = %.1f \r\n", GGAInfo.PosFixInd, GGAInfo.SatNumber, GGAInfo.HDOP, GGAInfo.Altitude, GGAInfo.MSL));
            GPS_debug(("\x1b[30m"));   //Black

        }

        NMEA_debug(("\x1b[31m"));   //Red
        if (Len)
        {
            for (i = 0; i < Len; i++)
                NMEA_debug(("%c",*NMEA_str++));
        }
        NMEA_debug(("\r\n"));

        //Check processed sentence
        /*
        if (PostPtrLen)
        {
            for (i = 0; i < PostPtrLen; i++)
                NMEA_debug(("%c",*pPostPrt++));
        }
        NMEA_debug(("\r\n"));
        */
        NMEA_debug(("\x1b[30m"));   //Black
        break;

    case GSV:
        sscanf(pPostPrt, "%s %d %d %d %s\n", type, &NumOfSen, &SenNum, &SatInView, RemainStr);
        if (NumOfSen == SenNum)
        {
            if ((SatInView % 4) == 1)
                sscanf(pPostPrt, "%s %d %d %d %d %d %d %d %X\n", type, &NumOfSen, &SenNum, &SatInView, &SatNum1, &Elev1, &Azi1, &SNR1, &CheckSum);
            else if ((SatInView % 4) == 2)
                sscanf(pPostPrt, "%s %d %d %d %d %d %d %d %d %d %d %d %X\n", type, &NumOfSen, &SenNum, &SatInView, &SatNum1, &Elev1, &Azi1, &SNR1, &SatNum2, &Elev2, &Azi2, &SNR2, &CheckSum);
            else if ((SatInView % 4) == 3)
                sscanf(pPostPrt, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %X\n", type, &NumOfSen, &SenNum, &SatInView, &SatNum1, &Elev1, &Azi1, &SNR1, &SatNum2, &Elev2, &Azi2, &SNR2, &SatNum3, &Elev3, &Azi3, &SNR3, &CheckSum);
            else
                sscanf(pPostPrt, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %X\n", type, &NumOfSen, &SenNum, &SatInView, &SatNum1, &Elev1, &Azi1, &SNR1, &SatNum2, &Elev2, &Azi2, &SNR2, &SatNum3, &Elev3, &Azi3, &SNR3, &SatNum4, &Elev4, &Azi4, &SNR4, &CheckSum);
        }
        else
        {
            sscanf(pPostPrt, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %X\n", type, &NumOfSen, &SenNum, &SatInView, &SatNum1, &Elev1, &Azi1, &SNR1, &SatNum2, &Elev2, &Azi2, &SNR2, &SatNum3, &Elev3, &Azi3, &SNR3, &SatNum4, &Elev4, &Azi4, &SNR4, &CheckSum);
        }

        #if (_GPS_CheckSum_Enable)
            GPSRec_CheckSum(NMEA_str, Len, CheckSum);
        #endif

        if(NumOfSen == 0)
        {
            g_Edog_satellie_DB.satellie_DB_GSM_1 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_2 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_3 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_4 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_5 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_6 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_7 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_8 = 0;
			#if 1//BDGSV Mark
            g_Edog_satellie_DB.satellie_DB_GSM_9 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_10 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_11 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_12 = 0;
            #endif
        }
        else if(NumOfSen == 1)
        {
            g_Edog_satellie_DB.satellie_DB_GSM_5 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_6 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_7 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_8 = 0;
			#if 1//BDGSV Mark
            g_Edog_satellie_DB.satellie_DB_GSM_9 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_10 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_11 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_12 = 0;
            #endif
        }
        else if(NumOfSen == 2)
        {
			#if 1//BDGSV Mark
            g_Edog_satellie_DB.satellie_DB_GSM_9 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_10 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_11 = 0;
            g_Edog_satellie_DB.satellie_DB_GSM_12 = 0;
            #endif
        }
        else
        {
            ;
        }

        //debug_msg("GPS Saterlite  Num:%d  %d\r\n",NumOfSen,SenNum);
        if (SenNum == 1)   //GSV1
        {
            GSVInfo.NumOfSen =     NumOfSen;
            GSVInfo.SatInView =    SatInView;
            GSVInfo.SAT01.SatNum = SatNum1;
            GSVInfo.SAT01.Elev =   Elev1;
            GSVInfo.SAT01.Azi =    Azi1;
            GSVInfo.SAT01.SNR =    SNR1;
            GSVInfo.SAT02.SatNum = SatNum2;
            GSVInfo.SAT02.Elev =   Elev2;
            GSVInfo.SAT02.Azi =    Azi2;
            GSVInfo.SAT02.SNR =    SNR2;
            GSVInfo.SAT03.SatNum = SatNum3;
            GSVInfo.SAT03.Elev =   Elev3;
            GSVInfo.SAT03.Azi =    Azi3;
            GSVInfo.SAT03.SNR =    SNR3;
            GSVInfo.SAT04.SatNum = SatNum4;
            GSVInfo.SAT04.Elev =   Elev4;
            GSVInfo.SAT04.Azi =    Azi4;
            GSVInfo.SAT04.SNR =    SNR4;
            GPS_debug(("\x1b[35m"));   //Violet
            GPS_debug(("#GSV%d SatInView = %d, CheckSum = %X\r\n",SenNum, SatInView, CheckSum));
            GPS_debug(("#GSV%d Sat1 = %d, %d, %d, %d, Sat2 = %d, %d, %d, %d\r\n",SenNum, SatNum1, Elev1, Azi1, SNR1, SatNum2, Elev2, Azi2, SNR2));
            GPS_debug(("#GSV%d Sat3 = %d, %d, %d, %d, Sat4 = %d, %d, %d, %d\r\n",SenNum, SatNum3, Elev3, Azi3, SNR3, SatNum4, Elev4, Azi4, SNR4));
            GPS_debug(("\x1b[30m"));      //Black

            g_Edog_satellie_DB.satellie_DB_GSM_1 = SNR1;
            g_Edog_satellie_DB.satellie_DB_GSM_2 = SNR2;
            g_Edog_satellie_DB.satellie_DB_GSM_3 = SNR3;
            g_Edog_satellie_DB.satellie_DB_GSM_4 = SNR4;
        }
        else if (SenNum == 2)   //GSV2
        {
            GSVInfo.NumOfSen =     NumOfSen;
            GSVInfo.SatInView =    SatInView;
            GSVInfo.SAT05.SatNum = SatNum1;
            GSVInfo.SAT05.Elev =   Elev1;
            GSVInfo.SAT05.Azi =    Azi1;
            GSVInfo.SAT05.SNR =    SNR1;
            GSVInfo.SAT06.SatNum = SatNum2;
            GSVInfo.SAT06.Elev =   Elev2;
            GSVInfo.SAT06.Azi =    Azi2;
            GSVInfo.SAT06.SNR =    SNR2;
            GSVInfo.SAT07.SatNum = SatNum3;
            GSVInfo.SAT07.Elev =   Elev3;
            GSVInfo.SAT07.Azi =    Azi3;
            GSVInfo.SAT07.SNR =    SNR3;
            GSVInfo.SAT08.SatNum = SatNum4;
            GSVInfo.SAT08.Elev =   Elev4;
            GSVInfo.SAT08.Azi =    Azi4;
            GSVInfo.SAT08.SNR =    SNR4;
            GPS_debug(("\x1b[35m"));   //Violet
            GPS_debug(("#GSV%d SatInView = %d, CheckSum = %X\r\n",SenNum, SatInView, CheckSum));
            GPS_debug(("#GSV%d Sat5 = %d, %d, %d, %d, Sat6 = %d, %d, %d, %d\r\n",SenNum, SatNum1, Elev1, Azi1, SNR1, SatNum2, Elev2, Azi2, SNR2));
            GPS_debug(("#GSV%d Sat7 = %d, %d, %d, %d, Sat8 = %d, %d, %d, %d\r\n",SenNum, SatNum3, Elev3, Azi3, SNR3, SatNum4, Elev4, Azi4, SNR4));
            GPS_debug(("\x1b[30m"));      //Black

            g_Edog_satellie_DB.satellie_DB_GSM_5 = SNR1;
            g_Edog_satellie_DB.satellie_DB_GSM_6 = SNR2;
            g_Edog_satellie_DB.satellie_DB_GSM_7 = SNR3;
            g_Edog_satellie_DB.satellie_DB_GSM_8 = SNR4;
        }
        #if 1//BDGSV Mark
        else if (SenNum == 3)   //GSV3
        {
            GSVInfo.NumOfSen =     NumOfSen;
            GSVInfo.SatInView =    SatInView;
            GSVInfo.SAT09.SatNum = SatNum1;
            GSVInfo.SAT09.Elev =   Elev1;
            GSVInfo.SAT09.Azi =    Azi1;
            GSVInfo.SAT09.SNR =    SNR1;
            GSVInfo.SAT10.SatNum = SatNum2;
            GSVInfo.SAT10.Elev =   Elev2;
            GSVInfo.SAT10.Azi =    Azi2;
            GSVInfo.SAT10.SNR =    SNR2;
            GSVInfo.SAT11.SatNum = SatNum3;
            GSVInfo.SAT11.Elev =   Elev3;
            GSVInfo.SAT11.Azi =    Azi3;
            GSVInfo.SAT11.SNR =    SNR3;
            GSVInfo.SAT12.SatNum = SatNum4;
            GSVInfo.SAT12.Elev =   Elev4;
            GSVInfo.SAT12.Azi =    Azi4;
            GSVInfo.SAT12.SNR =    SNR4;
            GPS_debug(("\x1b[35m"));   //Violet
            GPS_debug(("#GSV%d SatInView = %d, CheckSum = %X\r\n",SenNum, SatInView, CheckSum));
            GPS_debug(("#GSV%d Sat9 = %d, %d, %d, %d,  Sat10 = %d, %d, %d, %d\r\n",SenNum, SatNum1, Elev1, Azi1, SNR1, SatNum2, Elev2, Azi2, SNR2));
            GPS_debug(("#GSV%d Sat11 = %d, %d, %d, %d, Sat12 = %d, %d, %d, %d\r\n",SenNum, SatNum3, Elev3, Azi3, SNR3, SatNum4, Elev4, Azi4, SNR4));
            GPS_debug(("\x1b[30m"));      //Black

            g_Edog_satellie_DB.satellie_DB_GSM_9 = SNR1;
            g_Edog_satellie_DB.satellie_DB_GSM_10 = SNR2;
            g_Edog_satellie_DB.satellie_DB_GSM_11 = SNR3;
            g_Edog_satellie_DB.satellie_DB_GSM_12 = SNR4;
        }
        #endif
        else
        {
            //DBG_ERR("GPS: Invalid number of GSV");
        }

        g_bEdogSatelliteDBMSG = TRUE;

        NMEA_debug(("\x1b[35m"));   //Violet
        if (Len)
        {
            for (i = 0; i < Len; i++)
                NMEA_debug(("%c",*NMEA_str++));
        }
        NMEA_debug(("\r\n"));
        //Check processed sentence
        /*
        if (PostPtrLen)
        {
            for (i = 0; i < PostPtrLen; i++)
                NMEA_debug(("%c",*pPostPrt++));
        }
        NMEA_debug(("\r\n"));
        */
        NMEA_debug(("\x1b[30m"));      //Black
        break;
	case BDGSV:
		sscanf(pPostPrt, "%s %lu %lu %lu %s\n", type, &NumOfSen, &SenNum, &SatInView, RemainStr);
		#if 0
		if (NumOfSen == SenNum)
		{
			if ((SatInView % 4) == 1)
				sscanf(pPostPrt, "%s %lu %lu %lu %lu %lu %lu %lu %lX\n", type, &NumOfSen, &SenNum, &SatInView, &SatNum1, &Elev1, &Azi1, &SNR1, &CheckSum);
			else if ((SatInView % 4) == 2)
				sscanf(pPostPrt, "%s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lX\n", type, &NumOfSen, &SenNum, &SatInView, &SatNum1, &Elev1, &Azi1, &SNR1, &SatNum2, &Elev2, &Azi2, &SNR2, &CheckSum);
			else if ((SatInView % 4) == 3)
				sscanf(pPostPrt, "%s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lX\n", type, &NumOfSen, &SenNum, &SatInView, &SatNum1, &Elev1, &Azi1, &SNR1, &SatNum2, &Elev2, &Azi2, &SNR2, &SatNum3, &Elev3, &Azi3, &SNR3, &CheckSum);
			else
				sscanf(pPostPrt, "%s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lX\n", type, &NumOfSen, &SenNum, &SatInView, &SatNum1, &Elev1, &Azi1, &SNR1, &SatNum2, &Elev2, &Azi2, &SNR2, &SatNum3, &Elev3, &Azi3, &SNR3, &SatNum4, &Elev4, &Azi4, &SNR4, &CheckSum);
		}
		else
		#endif
		{
//			  sscanf_s(pPostPrt, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %X\n", type, NMEA_TYPE_SIZE, &NumOfSen, &SenNum, &SatInView, &SatNum1, &Elev1, &Azi1, &SNR1, &SatNum2, &Elev2, &Azi2, &SNR2, &SatNum3, &Elev3, &Azi3, &SNR3, &SatNum4, &Elev4, &Azi4, &SNR4, &CheckSum);
			sscanf(pPostPrt, "%s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lX\n", type, &NumOfSen, &SenNum, &SatInView, &SatNum1, &Elev1, &Azi1, &SNR1, &SatNum2, &Elev2, &Azi2, &SNR2, &SatNum3, &Elev3, &Azi3, &SNR3, &SatNum4, &Elev4, &Azi4, &SNR4, &CheckSum);
		}
		
    #if (_GPS_CheckSum_Enable)
		//GPSRec_CheckSum(NMEA_str, Len, CheckSum);
    #endif
		
		if(NumOfSen == 0)
		{	
#if 0
			g_Edog_satellie_DB.satellie_DB_GSM_1 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_2 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_3 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_4 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_5 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_6 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_7 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_8 = 0;
#endif
			g_Edog_satellie_DB.satellie_DB_GSM_9 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_10 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_11 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_12 = 0;
		}
		/*else if(NumOfSen == 1)
		{
			g_Edog_satellie_DB.satellie_DB_GSM_5 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_6 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_7 = 0;
			g_Edog_satellie_DB.satellie_DB_GSM_8 = 0;
			//g_Edog_satellie_DB.satellie_DB_GSM_9 = 0;
			//g_Edog_satellie_DB.satellie_DB_GSM_10 = 0;
			//g_Edog_satellie_DB.satellie_DB_GSM_11 = 0;
			//g_Edog_satellie_DB.satellie_DB_GSM_12 = 0;
		}
		else if(NumOfSen == 2)
		{
			//g_Edog_satellie_DB.satellie_DB_GSM_9 = 0;
			//g_Edog_satellie_DB.satellie_DB_GSM_10 = 0;
			//g_Edog_satellie_DB.satellie_DB_GSM_11 = 0;
			//g_Edog_satellie_DB.satellie_DB_GSM_12 = 0;
		}*/
		else
		{
			;
		}

		if (SenNum == 1)   //GSV1
		{
			GSVInfo.NumOfSen =	   NumOfSen;
			GSVInfo.SatInView =    SatInView;
			GSVInfo.SAT09.SatNum = SatNum1;
			GSVInfo.SAT09.Elev =   Elev1;
			GSVInfo.SAT09.Azi =    Azi1;
			GSVInfo.SAT09.SNR =    SNR1;
			GSVInfo.SAT10.SatNum = SatNum2;
			GSVInfo.SAT10.Elev =   Elev2;
			GSVInfo.SAT10.Azi =    Azi2;
			GSVInfo.SAT10.SNR =    SNR2;
			GSVInfo.SAT11.SatNum = SatNum3;
			GSVInfo.SAT11.Elev =   Elev3;
			GSVInfo.SAT11.Azi =    Azi3;
			GSVInfo.SAT11.SNR =    SNR3;
			GSVInfo.SAT12.SatNum = SatNum4;
			GSVInfo.SAT12.Elev =   Elev4;
			GSVInfo.SAT12.Azi =    Azi4;
			GSVInfo.SAT12.SNR =    SNR4;
			//DBG_DUMP(("\x1b[35m"));	//Violet
			//DBG_DUMP(("#GSV%d SatInView = %d, CheckSum = %X\r\n",SenNum, SatInView, CheckSum));
			//DBG_WRN("#GSV%d Sat9 = %d, %d, %d, %d,  Sat10 = %d, %d, %d, %d\r\n",SenNum, SatNum1, Elev1, Azi1, SNR1, SatNum2, Elev2, Azi2, SNR2);
			//DBG_DUMP(("#GSV%d Sat11 = %d, %d, %d, %d, Sat12 = %d, %d, %d, %d\r\n",SenNum, SatNum3, Elev3, Azi3, SNR3, SatNum4, Elev4, Azi4, SNR4));
			//DBG_DUMP(("\x1b[30m"));	   //Black

			g_Edog_satellie_DB.satellie_DB_GSM_9 = SNR1;
			g_Edog_satellie_DB.satellie_DB_GSM_10 = SNR2;
			g_Edog_satellie_DB.satellie_DB_GSM_11 = SNR3;
			g_Edog_satellie_DB.satellie_DB_GSM_12 = SNR4;
		}
#if 0
		else if (SenNum == 2)	//GSV2
		{
			GSVInfo.NumOfSen =	   NumOfSen;
			GSVInfo.SatInView =    SatInView;
			GSVInfo.SAT05.SatNum = SatNum1;
			GSVInfo.SAT05.Elev =   Elev1;
			GSVInfo.SAT05.Azi =    Azi1;
			GSVInfo.SAT05.SNR =    SNR1;
			GSVInfo.SAT06.SatNum = SatNum2;
			GSVInfo.SAT06.Elev =   Elev2;
			GSVInfo.SAT06.Azi =    Azi2;
			GSVInfo.SAT06.SNR =    SNR2;
			GSVInfo.SAT07.SatNum = SatNum3;
			GSVInfo.SAT07.Elev =   Elev3;
			GSVInfo.SAT07.Azi =    Azi3;
			GSVInfo.SAT07.SNR =    SNR3;
			GSVInfo.SAT08.SatNum = SatNum4;
			GSVInfo.SAT08.Elev =   Elev4;
			GSVInfo.SAT08.Azi =    Azi4;
			GSVInfo.SAT08.SNR =    SNR4;
			//DBG_DUMP(("\x1b[35m"));	//Violet
			//DBG_DUMP(("#GSV%d SatInView = %d, CheckSum = %X\r\n",SenNum, SatInView, CheckSum));
			//DBG_DUMP(("#GSV%d Sat5 = %d, %d, %d, %d, Sat6 = %d, %d, %d, %d\r\n",SenNum, SatNum1, Elev1, Azi1, SNR1, SatNum2, Elev2, Azi2, SNR2));
			//DBG_DUMP(("#GSV%d Sat7 = %d, %d, %d, %d, Sat8 = %d, %d, %d, %d\r\n",SenNum, SatNum3, Elev3, Azi3, SNR3, SatNum4, Elev4, Azi4, SNR4));
			//DBG_DUMP(("\x1b[30m"));	   //Black

			g_Edog_satellie_DB.satellie_DB_GSM_5 = SNR1;
			g_Edog_satellie_DB.satellie_DB_GSM_6 = SNR2;
			g_Edog_satellie_DB.satellie_DB_GSM_7 = SNR3;
			g_Edog_satellie_DB.satellie_DB_GSM_8 = SNR4;
		}
		else if (SenNum == 3)	//GSV3
		{
			GSVInfo.NumOfSen =	   NumOfSen;
			GSVInfo.SatInView =    SatInView;
			GSVInfo.SAT09.SatNum = SatNum1;
			GSVInfo.SAT09.Elev =   Elev1;
			GSVInfo.SAT09.Azi =    Azi1;
			GSVInfo.SAT09.SNR =    SNR1;
			GSVInfo.SAT10.SatNum = SatNum2;
			GSVInfo.SAT10.Elev =   Elev2;
			GSVInfo.SAT10.Azi =    Azi2;
			GSVInfo.SAT10.SNR =    SNR2;
			GSVInfo.SAT11.SatNum = SatNum3;
			GSVInfo.SAT11.Elev =   Elev3;
			GSVInfo.SAT11.Azi =    Azi3;
			GSVInfo.SAT11.SNR =    SNR3;
			GSVInfo.SAT12.SatNum = SatNum4;
			GSVInfo.SAT12.Elev =   Elev4;
			GSVInfo.SAT12.Azi =    Azi4;
			GSVInfo.SAT12.SNR =    SNR4;
			//DBG_DUMP(("\x1b[35m"));	//Violet
			//DBG_DUMP(("#GSV%d SatInView = %d, CheckSum = %X\r\n",SenNum, SatInView, CheckSum));
			//DBG_DUMP(("#GSV%d Sat9 = %d, %d, %d, %d,	Sat10 = %d, %d, %d, %d\r\n",SenNum, SatNum1, Elev1, Azi1, SNR1, SatNum2, Elev2, Azi2, SNR2));
			//DBG_DUMP(("#GSV%d Sat11 = %d, %d, %d, %d, Sat12 = %d, %d, %d, %d\r\n",SenNum, SatNum3, Elev3, Azi3, SNR3, SatNum4, Elev4, Azi4, SNR4));
			//DBG_DUMP(("\x1b[30m"));	   //Black

			g_Edog_satellie_DB.satellie_DB_GSM_9 = SNR1;
			g_Edog_satellie_DB.satellie_DB_GSM_10 = SNR2;
			g_Edog_satellie_DB.satellie_DB_GSM_11 = SNR3;
			g_Edog_satellie_DB.satellie_DB_GSM_12 = SNR4;
		}
#endif
		else
		{
			//DBG_ERR("GPS: Invalid number of GSV");
		}

		g_bEdogSatelliteDBMSG = TRUE;

		DBG_IND(("\x1b[35m"));	 //Violet
		if (Len)
		{
			for (i = 0; i < Len; i++)
				DBG_IND(("%c",*NMEA_str++));
		}
		DBG_IND(("\r\n"));
		//Check processed sentence
		/*
		if (PostPtrLen)
		{
			for (i = 0; i < PostPtrLen; i++)
				DBG_WRN(("%c",*pPostPrt++));
		}
		DBG_WRN(("\r\n"));
		*/
		DBG_IND(("\x1b[30m"));		//Black
		break;

    //Do not support GLL and VTG yet
    case GLL:
        NMEA_debug(("\x1b[36m"));   //Blue
        if (Len)
        {
            for (i = 0; i < Len; i++)
                NMEA_debug(("%c",*NMEA_str++));
        }
        NMEA_debug(("\r\n"));
        NMEA_debug(("\x1b[30m"));   //Black
        break;

    case VTG:
        NMEA_debug(("\x1b[32m"));   //Green
        if (Len)
        {
            for (i = 0; i < Len; i++)
                NMEA_debug(("%c",*NMEA_str++));
        }
        NMEA_debug(("\r\n"));
        NMEA_debug(("\x1b[30m"));   //Black
        break;

    default:
        break;
    }

}

void GPS_SetSpeedUint(INT8 value)
{
    uiSpeed_Uint = value;
}

FLOAT GPSRec_GetGPS_Speed(void)
{
    #if 0
    static FLOAT uiSpeed[5] = {0,0,0,0,0};
    static FLOAT CurSpeed = 0;
    static BOOL SpeedAVE = FALSE;
    static UINT32 SpeedIndex = 0;
    int i;

    if (uiSpeed_Uint == 1) //SPEED_UNIT_MPH
    {
        CurSpeed = RMCInfo.Speed * 1.15078;
    }
    else
    {
        CurSpeed = RMCInfo.Speed * 1.852;
    }

    uiSpeed[SpeedIndex] = CurSpeed;
    SpeedIndex++;
    if(SpeedIndex >= 5)
    {
        SpeedAVE = TRUE;
        SpeedIndex = 0;
    }

    if(SpeedAVE)
    {
        CurSpeed = 0;
        for(i = 0; i < 5; i++)
        {
            CurSpeed = CurSpeed + uiSpeed[i];
        }
        CurSpeed = CurSpeed/5;
    }

    return CurSpeed;
    #else

    static FLOAT CurSpeed = 0;

    if (uiSpeed_Uint == 1) //SPEED_UNIT_MPH
    {
        CurSpeed = RMCInfo.Speed * 1.15078;
    }
    else
    {
        CurSpeed = RMCInfo.Speed * 1.852;
    }

    return CurSpeed;
    #endif
}

CHAR Speed1[32] = {0};
CHAR *Get_GpsSpeedString(void)
{
    UINT32 uiSpeed = 0;

    static int siGPSstd = 0;

    static int siErrorCnt = 0;

    uiSpeed = GPSRec_GetGPS_Speed();
	//if (data_errflag == 0)
	if (1)
	{
	    if(siGPSstd != siGPSBeingCnt)
	    {
	        siGPSstd = siGPSBeingCnt;

	        if(siGPSstd >= 1024)
	        {
	            siGPSBeingCnt = 0;
	            siGPSstd = siGPSBeingCnt;
	        }
	        if (uiSpeed_Uint == 1) //SPEED_UNIT_MPH
	        {
	            sprintf(Speed1, "%d MPH", uiSpeed);
	        }
	        else
	        {
	            sprintf(Speed1, "%d KM/H", uiSpeed);
	        }

	    	uigpsstatus = 1;
	    	siErrorCnt = 0;
			
	        if(RMCInfo.Status == 'V')
	        {
	            RMCInfo.Status = ' ';
	            uigpsstatus = 0;
	            if (uiSpeed_Uint == 1) //SPEED_UNIT_MPH
	            {
	                sprintf(Speed1, "%d MPH", 0);
	            }
	            else
	            {
	                sprintf(Speed1, "%d KM/H", 0);
	            }
	        }
	    }

	    /*
	    if(GPSRec_CheckData())
	    {
	        //clr_flg(FLG_ID_GPS, GPS_FLAG_DATAVALID);
	        sprintf(Speed1, "%d km/h", uiSpeed);
	        uigpsstatus = 1 ;
	    }
	    */
	    else
	    {
	        siErrorCnt++;
	        if(siErrorCnt >= 4) // 2
	        {
	            siErrorCnt = 0;

	            {
	                sprintf(Speed1, "%s", "No GPS");
	                //memset(g_cLongitude_buffer, 0, 16);
	                //memset(g_cDimensionality_buffer, 0, 16);
	                uigpsstatus = -1;
	            }
	        }
	    }
	}else {
		DBG_DUMP("call gps data error\r\n");
	}
    return Speed1;
}

//#HTK#2014/09/24 Jason add for PPG Movie GPS Data begin




CHAR GPSSpeedData[32] = {0};
char *GPS_OSDSpeedData(void)
{
    sprintf(GPSSpeedData, "%s", "          ");

    if (RMCInfo.Speed < 300)
    {
        if (uiSpeed_Uint == 1) //SPEED_UNIT_MPH
        {
            sprintf(GPSSpeedData, "%d MPH", (INT32)(RMCInfo.Speed * 1.15078));
        }
        else
        {
            sprintf(GPSSpeedData, "%d KM/H", (INT32)(RMCInfo.Speed * 1.852));
        }
    }
    return GPSSpeedData;
}

//#HTK#2014/09/24 Jason add for PPG Movie GPS Data end

BOOL GPSRec_GetRMCDate(RMCINFO *pRMCInfo)
{
    memcpy(pRMCInfo,&RMCInfo,sizeof(RMCINFO));
    if (RMCInfo.Status == 'A')  //Data valid
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL GPSRec_GetUTCDate(UINT32 *Year, UINT32 *Month, UINT32 *Day)
{
    if (RMCInfo.Status == 'A')  //Data valid
    {
        *Year   = RMCInfo.Year;
        *Month  = RMCInfo.Month;
        *Day    = RMCInfo.Day;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL GPSRec_GetUTCTime(UINT32 *Hour, UINT32 *Minute, UINT32 *Second)
{
    if (RMCInfo.Status == 'A')   //Data valid
    {
        *Hour   = RMCInfo.Hour;
        *Minute = RMCInfo.Minute;
        *Second = RMCInfo.Second;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL GPSRec_GetGGADate(GGAINFO *pGGAInfo)
{
    memcpy(pGGAInfo,&GGAInfo,sizeof(GGAINFO));
    if (PosFixInd == 1)  //Data valid
    {
        return TRUE;
    }
    else
        return FALSE;
}



//#NT#2015/10/02#KCHong -begin
//#NT#Add GPS heartbeat to detect GPS status
BOOL GPSRec_GetSpeed(FLOAT *Speed)
{
    //static FLOAT CurSpeed = 0;

    //CurSpeed = RMCInfo.Speed * 1.852;

    if (RMCInfo.Status == 'A')   //Data valid
    {
        if (RMCInfo.Speed < 300)
        {
            *Speed = RMCInfo.Speed * 1.852;
        }
        return TRUE;
    }
    else
    {
        *Speed = 0.0;
        return FALSE;
    }
}

UINT32 GetGPSHeartBeat(void)
{
    return GPSHeartBeat;
}

void dumpArr(CHAR *arr, UINT32 len)
{
    UINT32 i;
    for (i = 0; i < len; i++) {
        DBG_DUMP("%d 0x%x %d %c\n", i, *(arr+i), *(arr+i), *(arr+i));
    }
}

UINT16 Check_GpsData(void)
{
	CHAR Check_RecSentences[800] = {0};
	UINT32 Check_RecSentences_Len = 0;
	ER check_result;
	sleep(1);
	memset(Check_RecSentences,0,sizeof(Check_RecSentences));
	memset(Check_RecSentences,0,sizeof(Check_RecSentences));
	check_result = GpsUart.getString(Check_RecSentences, &Check_RecSentences_Len);
	if (check_result == E_PAR) {
		DBG_ERR("UART parameter error!\r\n");
	}
	//DBG_DUMP("%s\r\n",Check_RecSentences);
	if ((strstr(Check_RecSentences,"GPRMC") == NULL)||(strstr(Check_RecSentences,"GPGGA") == NULL)){
		//printf("data_error\r\n");
		Dx_InitGPS_NOPWREN();
		usleep(3000);
		Dx_InitGPS_PWREN();
		return GPS_DATAERROR;
	}
	return GPS_DATANORMAL;
}
void InsertSort(Satellite_Info a[], int n)
{
    int i, j;
	Satellite_Info temp;
    for(i=1; i<n; i++)
        if(a[i].Cn > a[i-1].Cn)   
        {
            temp.Cn= a[i].Cn;   
			temp.PRN= a[i].PRN; 
			temp.Valid= a[i].Valid; 
            for(j=i-1; j>=0 && a[j].Cn < temp.Cn; j--)  
            {
                a[j+1].Cn= a[j].Cn; 
				a[j+1].PRN= a[j].PRN; 
				a[j+1].Valid= a[j].Valid; 
			}
            a[j+1].Cn= temp.Cn;
			a[j+1].PRN= temp.PRN; 
			a[j+1].Valid= temp.Valid; 
        }
}

THREAD_RETTYPE GPS_TASK(void *pvParameters)
{
    CHAR    RecSentences[800] = {0};
	UINT32  uiLen;
	CHAR 	RecSentence[NMEA_SENTENCE_SIZE] = {0};
	UINT32  RecSentences_Len;
    CHAR *delim = "\n";
	CHAR *pRecSentence = NULL;
    //UINT32 	lineNo = 0;
    CHAR    *pSentenceData = NULL;
    UINT16  CheckSentenceType1, CheckSentenceType2;
    static UINT32  CheckSentenceType3;
	RecSentences_Len = 0;
    ER result;
    //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	//pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	uiLen = NMEA_SENTENCE_SIZE;	
	//while(Check_GpsData());
    while (TRUE) {
		//memset(RecSentences,0,sizeof(RecSentences));
		//memset(RecSentence,0,sizeof(RecSentence));
		bzero(RecSentences, sizeof(RecSentences));
		bzero(RecSentence,sizeof(RecSentence));
        //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        result = GpsUart.getString(RecSentences, &RecSentences_Len);
		//DBG_DUMP("result = %d\r\n",result);
		//uiLen = RecSentences_Len;
        if (result == E_PAR) {
            DBG_ERR("UART parameter error!\r\n");
        }
        if (result == E_TMOUT) {
	   		data_errflag = 0;
            continue;
        }
        //DBG_DUMP("%s\r\n", RecSentences);
        pRecSentence = strtok(RecSentences, delim);
        while(pRecSentence != NULL) {
            //lineNo++;
            // DBG_DUMP("%d. %s\n", lineNo, RecSentence);
	    	strcpy(RecSentence,pRecSentence);
            if (RecSentence[0] == 0x24) {
                GPSHeartBeat ++;        //#NT#2015/10/02#KCHong#Add GPS heartbeat to detect GPS status
                pSentenceData = RecSentence;
                CheckSentenceType1 = *(UINT16 *)(pSentenceData + 2);
                CheckSentenceType2 = *(UINT16 *)(pSentenceData + 4);
                CheckSentenceType3 = ((UINT)CheckSentenceType2 << 16) | (UINT)CheckSentenceType1;

                // DBG_DUMP("CheckSentenceType1 = 0x%x, %d\n", CheckSentenceType1, CheckSentenceType1);
                // DBG_DUMP("CheckSentenceType2 = 0x%x, %d\n", CheckSentenceType2, CheckSentenceType2);
                // DBG_DUMP("CheckSentenceType3 = 0x%x, %d\n", CheckSentenceType3, CheckSentenceType3);

                switch(CheckSentenceType3) {
                case GSV_SENTENCE:
                    //DBG_DUMP("GSV\n");
                    NMEASentence.GSV = RecSentence;
                    GPSRec_NMEAParser(RecSentence, uiLen, GSV);
                    break;

				case GSA_SENTENCE:
					// DBG_DUMP("GSA\n");
					NMEASentence.GSA = RecSentence;
					GPSRec_NMEAParser(RecSentence, uiLen, GSA);
					break;
				case BDGSV_SENTENCE:
					//DBG_WRN("%s\r\n", RecSentence);
					NMEASentence.GSV = RecSentence;
					GPSRec_NMEAParser(RecSentence, uiLen, BDGSV);
					break;

                case RMC_SENTENCE:
				case NRMC_SENTENCE:
                    //DBG_DUMP("RMC\n");
                    edogCBdata_update_ok = FALSE;
                    siGPSBeingCnt++;
                    NMEASentence.RMC = RecSentence;
                    GPSRec_NMEAParser(RecSentence, uiLen, RMC);
                    GPSRec_getAngle();
                    GPSRec_GetRMCNData();
                    GPSRec_GetRMCEData();
					edogCBdata_update_ok = TRUE;
                    break;
				case TXT_SENTENCE:// switch to tpms task
					TPMSRecTsk();
					break;
#if 0
                case GSA_SENTENCE:
                    // DBG_DUMP("GSA\n");
                    NMEASentence.GSA = RecSentence;
                    GPSRec_NMEAParser(RecSentence, uiLen, GSA);
                    break;

                case GGA_SENTENCE:
                    // DBG_DUMP("GGA\n");
                    NMEASentence.GGA = RecSentence;
                    GPSRec_NMEAParser(RecSentence, uiLen, GGA);
                    break;

                case GLL_SENTENCE:
                    // DBG_DUMP("GLL\n");
                    NMEASentence.GLL = RecSentence;
                    GPSRec_NMEAParser(RecSentence, uiLen, GLL);
                    break;

                case VTG_SENTENCE:
                    // DBG_DUMP("VTG\n");
                    NMEASentence.VTG = RecSentence;
                    GPSRec_NMEAParser(RecSentence, uiLen, VTG);
                    break;
#endif			
                default:
                    // DBG_ERR("GPS: Can't identify this sentence 0x%X \r\n",CheckSentenceType3);
                    break;
                }
            }
			pRecSentence = strtok(NULL, delim);
        }
        //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        //pthread_testcancel();
		usleep(1000000);//excute too fast that can't get any data .GPS send data one time/persecond.
    }

    // DBG_DUMP("GPS Data end!!\n");
	//GPSRec_Close();
    //THREAD_RETURN(0);
}
//#NT#2015/
#if 1
static CHAR EdogRecsentence[1024] = {0};
static UINT32 edogdatacnt = 0;
char *GPSRec_GetString(void)
{
	return EdogRecsentence;
}
UINT32 GPSRec_GetStringLen(void)
{
	return edogdatacnt;	
}
void GPSRec_ResetString(void)
{
	edogdatacnt = 0;
	memset(EdogRecsentence,'\0',sizeof(EdogRecsentence));
}	
//THREAD_RETTYPE TPMSRecTsk(void *pvParameters)
void TPMSRecTsk(void)
{
    #if 0
	UINT32    cLen;
    //CHAR    RecSentencetmp[1] = {0};
	UINT32 i = 0;
    CHAR    RecSentence[NMEA_SENTENCE_SIZE];
    kent_tsk();
    clr_flg(FLG_ID_GPS, GPS_FLAG_DATAVALID);
    
    debug_msg("^^^TPMSRecTsk--- \r\n");
	while(1)
    {
    
		GPSGetData_Lock();
    	uart3_getString(RecSentence,&cLen);
		DBG_DUMP("%s\r\n end\r\n",RecSentence);
		if(edogdatacnt > 1024)
		{
			edogdatacnt = 0;
			memset(EdogRecsentence,'\0',sizeof(EdogRecsentence));
		}
		for(i=0;i<strlen(RecSentence);i++)
		{
			EdogRecsentence[edogdatacnt] = RecSentence[i];
			edogdatacnt++;
		}
		
		DBG_DUMP("start %d  strlen(RecSentence)=%d\r\n",cLen,strlen(RecSentence));
		for(i=0;i<strlen(RecSentence);i++)
		{
			DBG_DUMP("%c",RecSentence[i]);
		}
    	GPSGetData_Unlock();
	}
	#else
	static UINT32    	cLen = 0;
    CHAR    	RecSentence[NMEA_SENTENCE_SIZE] = {0};
	ER 			result = E_OK;
    DBG_DUMP("^G^^TPMSRecTsk--- \r\n");
    while(1)
    {
    	GPSGetData_Lock();
        //one byte recieve uart2 msg -begin
        result = GpsUart.getString(RecSentence, &cLen);
		
		if(result!=E_OK)
		{
			GPSGetData_Unlock();
			usleep(200000);
			//DBG_DUMP("^G^^3333--- \r\n");
			continue;
		}
		//DBG_DUMP("RecSentence=%s cLen=%u %d\r\n",RecSentence,cLen,siGPSBeingCnt);
		if(edogdatacnt >= 1024)
		{
			GPSRec_ResetString();
		}
		cLen = ((cLen > NMEA_SENTENCE_SIZE) ? NMEA_SENTENCE_SIZE : cLen);
		if((1024 - edogdatacnt) >= cLen){//have enough buf
			memcpy(EdogRecsentence+edogdatacnt,RecSentence,cLen);	
			edogdatacnt += cLen;
		}else{//have no enough buf
			memcpy(EdogRecsentence+edogdatacnt,RecSentence,(1024 - edogdatacnt));	
			edogdatacnt += (1024 - edogdatacnt);
		}
		siGPSBeingCnt++;
		data_errflag = 0;
		#if 0
		DBG_DUMP("curret/total=%d/%d\r\n",cLen,edogdatacnt);
		for(i=0;i<cLen;i++)
		{
			DBG_DUMP("%c",RecSentence[i]);
		}
		DBG_DUMP("\r\n end\r\n");
		#endif
    	//DBG_DUMP("^G^^11111--- \r\n");
    	GPSGetData_Unlock();
		usleep(200000);//should sleep ,otherwise GPS_ComRead can't get lock.
    }
	#endif
}

EDOGINFO_UNIQUESKY_A EdogInfo_SentenceA = {0};

//ALARMINFO_EDOG EdogInfo_Alarm;
BOOL g_bEdogShowUI = FALSE; //Add for Send Show UI Event
extern BOOL g_bManualCloseEdogWnd;

UINT32 GetGPSAvgRemainSec(void)
{
    return g_AvgReaminSec;
}

//read edog data into a file ,then through file operation,it need a little memory.
//read edog data into a memory buffer ,then it need a large memory .
extern UINT32 ReadPstore_EDogDate_Fun(INT8U *buffer,INT32U offset,INT32U count);
INT32U 	edog_resource_rd_cb_t(INT8U *buffer,INT32U offset,INT32U count)
{
	UINT32 len = 0;
	len = ReadPstore_EDogDate_Fun(buffer,offset,count);
	return len;
}
void 	edog_notify_cb_t(INT8U alarm,INT32U event,INT32U speed,INT16U distance)//alarm notify
{
	//DBG_DUMP("alarm=%d event=0x%x speed=%d distance=%d 0x%x\r\n",alarm,event,speed,distance,distance);
	#if 1
	EdogInfo_SentenceA.EDOG_AlarmType = event&0xffff;
	EdogInfo_SentenceA.EDOG_SpeedLimit = speed/10;
	EdogInfo_SentenceA.EDOG_Distance1 = distance&0x00ff;//low byte
	EdogInfo_SentenceA.EDOG_Distance2 = (distance>>8)&0xff;//high byte
	if(!alarm)//invalid
	{
		g_AlarmTypeNow = 0xff;
	}
	else //valid
	{
		g_AlarmTypeNow = EdogInfo_SentenceA.EDOG_AlarmType;
	}
    if(g_AlarmTypeNow != 0xff)
    {
    
    }
    else
    { 
		#if 1
		if((GPSRadar_GetCASNesting()!=0)
				&&(GPSRadar_GetCurrentCASStart()==SPEED_DECTION_START))
		{
			if(!g_bAvgCalStart)
			{
				//debug_msg("distance=%d speed=%d \r\n",GPSRadar_GetCurrentCASDistance(),GPSRadar_GetCurrentCASOverspeed());
				g_AvgTotalSec = GPSRadar_GetCurrentCASDistance()/((GPSRadar_GetCurrentCASOverspeed())*1000/3600);
				g_AvgReaminSec = g_AvgTotalSec;
				g_bAvgCalStart = TRUE;
			}
		}

		#endif
		//g_bEdogShowUI = FALSE;
        g_bManualCloseEdogWnd = FALSE;
    }
	if(g_bAvgCalStart)
	{
		if(g_AvgReaminSec>=1)
		{
			g_AvgReaminSec--;
		}
	}
	Ux_PostEvent(NVTEVT_KEY_EDOG_ALARM, 2, g_AlarmTypePrev,g_AlarmTypeNow);
	g_AlarmTypePrev = g_AlarmTypeNow;
	#endif
}
void 	edog_location_notify_cb_t(PST_GPSRADAR_GPSINFO gpsinfo)//location notify
{
	Satellite_Info gps_info[32] = {0};
	INT8 i = 0;
	#if 0
	DBG_DUMP("latitude=%d longitude=%d latitudeEnc=%d latitudeEnc=%d speed=%d course=%d year=%d month=%d day=%d\r\n",
											gpsinfo->latitude,                  // current latitude  (度数* 10000)  wsk精确到0.1秒
											gpsinfo->longitude,                 // current longitude 度数* 10000
											gpsinfo->latitudeEnc,               // current latitude  (度数* 10000)  wsk精确到0.1秒
											gpsinfo->longitudeEnc,              // current longitude 度数* 10000
											gpsinfo->speed,               	  // speed over ground, knots
											gpsinfo->course,              	  //angle 
											gpsinfo->year,
											gpsinfo->month,               //
											gpsinfo->day);                  //	
	DBG_DUMP("hour=%d minute=%d second=%d valid=%d validSatNum=%d blValidSatNum=%d testmode=%d direction_flag=%d\r\n",
											gpsinfo->hour,                 //
											gpsinfo->minute,               //
											gpsinfo->second,               //
											gpsinfo->valid,                // 1 = Data valid, 0 = navigation rx warning
											 
											gpsinfo->validSatNum,
											gpsinfo->blValidSatNum,
											gpsinfo->testmode,
											gpsinfo->direction_flag);
	
	for(i=0;i < 3*GPS_MAX_CHAN;i++){//gps
		DBG_DUMP("i=%d  SatInfo=%d \r\n",i,gpsinfo->SatInfo[i]);
	}	
	for(i=0;i < 3*GPS_MAX_CHAN;i++){//beidou
		DBG_DUMP("i=%d  SatInfo=%d \r\n",i,gpsinfo->BDSatInfo[i]);
	}
	for(i = 0;i < 32 ;i++)
	{
		DBG_DUMP("i=%d valid=%d SatInfo=%d \r\n",gps_info[i].PRN,gps_info[i].Valid,gps_info[i].Cn);

	}
	#if 0
	for(i=0;i < 3*GPS_MAX_CHAN;i++){//GLONASS
		DBG_DUMP("i=%d  SatInfo=%d \r\n",i,gpsinfo->GLSatInfo[i]);
	}
	for(i=0;i < GPS_MAX_CHAN;i++){
		DBG_DUMP("i=%d  SatsInSolution=%d \r\n",i,gpsinfo->SatsInSolution[i]);
	}
	#endif
	#endif
    #if 0//just for test time
	gpsinfo->hour = 18;
	gpsinfo->minute=30;
	gpsinfo->second=30;
	gpsinfo->day=31;
	gpsinfo->month =12;
	gpsinfo->year =22;
	DBG_DUMP("%04d-%02d-%02d %02d:%02d:%02d \r\n",gpsinfo->year,gpsinfo->month,gpsinfo->day,gpsinfo->hour,gpsinfo->minute,gpsinfo->second);
	#endif
	for(i=0;i < GPS_MAX_CHAN;i++){//gps
		if(gpsinfo->SatInfo[i*3+1])
		{
			gps_info[i].PRN  = gpsinfo->SatInfo[i*3];
			gps_info[i].Valid= gpsinfo->SatInfo[i*3+1];
			gps_info[i].Cn	 = gpsinfo->SatInfo[i*3+2];
		}
		else
		{
			gps_info[i].PRN  = 0;
			gps_info[i].Valid = gpsinfo->SatInfo[i*3+1];
			gps_info[i].Cn	 = 0;
		}
	}	
	for(i=0 ;i < GPS_MAX_CHAN;i++){//beidou
		if(gpsinfo->BDSatInfo[i*3+1])
		{
			gps_info[i+GPS_MAX_CHAN].PRN = gpsinfo->BDSatInfo[i*3];
			gps_info[i+GPS_MAX_CHAN].Valid	= gpsinfo->BDSatInfo[i*3+1];
			gps_info[i+GPS_MAX_CHAN].Cn  = gpsinfo->BDSatInfo[i*3+2];
		}
		else
		{
			gps_info[i+GPS_MAX_CHAN].PRN = 0;
			gps_info[i+GPS_MAX_CHAN].Valid= gpsinfo->BDSatInfo[i*3+1];
			gps_info[i+GPS_MAX_CHAN].Cn  = 0;
		}
	}
	InsertSort(gps_info,32);

	edogCBdata_update_ok = FALSE;
	#if 1
    RMCInfo.Hour        = (UINT32)gpsinfo->hour;
    RMCInfo.Minute      = (UINT32)gpsinfo->minute;
    RMCInfo.Second      = (UINT32)gpsinfo->second;
	RMCInfo.Day         = gpsinfo->day;
    RMCInfo.Month       = gpsinfo->month;
    RMCInfo.Year        = gpsinfo->year - 2000;
    RMCInfo.Status      = gpsinfo->valid?'A':'V';
	if (RMCInfo.Status == 'A') //Data valid
    {  
        // if(g_iGPSPosition == FALSE)
        //g_iGPSPosition = TRUE;
        
        RMCInfo.Day     = GPSRec_GetGPS_Day();
        RMCInfo.Month   = GPSRec_GetGPS_Month();
        RMCInfo.Hour    = GPSRec_GetGPS_Hour();
        RMCInfo.Minute  = GPSRec_GetGPS_Minute();
        
        //  debug_err(("###GPS=%d %d %d\r\n",RMCInfo.Hour,RMCInfo.Day,SpecalAdd));
        if(RMCInfo.Hour >23)
        {
            RMCInfo.Hour = RMCInfo.Hour-24;
        }
		 g_bEdogSatelliteDBMSG = TRUE;
		uigpsstatus = 1;
    }
    else if (RMCInfo.Status == 'V')
    {
        //GPS_debug(("uigpsstatus=%d\r\n",uigpsstatus));
        uigpsstatus = 0;
    }
	temp_Latitude = gpsinfo->latitude;
    RMCInfo.NSInd       = (temp_Latitude>0) ?'N':'S';
    RMCInfo.Latitude    = GetGPSXY((abs(temp_Latitude) /100000.0));
	temp_Longitude = gpsinfo->longitude;
    RMCInfo.EWInd       = (temp_Longitude>0) ?'E':'W';
	RMCInfo.Longitude   = GetGPSXY((abs(temp_Longitude) /100000.0));
    RMCInfo.Speed       = (float)gpsinfo->speed/1.852;	
    RMCInfo.Angle       = (UINT16)gpsinfo->course;	
	edogCBdata_update_ok = TRUE;
	if(gps_info[0].Valid == 1){//valid
		g_Edog_satellie_DB.satellie_DB_GSM_1 = gps_info[0].Cn;
	}else{//invalid
		g_Edog_satellie_DB.satellie_DB_GSM_1 = 0;
	}
	
	if(gps_info[1].Valid == 1){
		g_Edog_satellie_DB.satellie_DB_GSM_2 = gps_info[1].Cn;
	}else{
		g_Edog_satellie_DB.satellie_DB_GSM_2 = 0;
	}
	
	if(gps_info[2].Valid == 1){
		g_Edog_satellie_DB.satellie_DB_GSM_3 = gps_info[2].Cn;
	}else{
		g_Edog_satellie_DB.satellie_DB_GSM_3 = 0;
	}
	
	if(gps_info[3].Valid == 1){
		g_Edog_satellie_DB.satellie_DB_GSM_4 = gps_info[3].Cn;
	}else{
		g_Edog_satellie_DB.satellie_DB_GSM_4 = 0;
	}
	if(gps_info[4].Valid == 1){
		g_Edog_satellie_DB.satellie_DB_GSM_5 = gps_info[4].Cn;
	}else{
		g_Edog_satellie_DB.satellie_DB_GSM_5 = 0;
	}
	
	if(gps_info[5].Valid == 1){
		g_Edog_satellie_DB.satellie_DB_GSM_6 = gps_info[5].Cn;
	}else{
		g_Edog_satellie_DB.satellie_DB_GSM_6 = 0;
	}
	
	if(gps_info[6].Valid == 1){
		g_Edog_satellie_DB.satellie_DB_GSM_7 = gps_info[6].Cn;
	}else{
		g_Edog_satellie_DB.satellie_DB_GSM_7 = 0;
	}
	
	if(gps_info[7].Valid == 1){
		g_Edog_satellie_DB.satellie_DB_GSM_8 = gps_info[7].Cn;
	}else{
		g_Edog_satellie_DB.satellie_DB_GSM_8 = 0;
	}
	if(gps_info[8].Valid == 1){
		g_Edog_satellie_DB.satellie_DB_GSM_9 = gps_info[8].Cn;
	}else{
		g_Edog_satellie_DB.satellie_DB_GSM_9 = 0;
	}
	
	if(gps_info[9].Valid == 1){
		g_Edog_satellie_DB.satellie_DB_GSM_10 = gps_info[9].Cn;
	}else{
		g_Edog_satellie_DB.satellie_DB_GSM_10 = 0;
	}
	
	if(gps_info[10].Valid == 1){
		g_Edog_satellie_DB.satellie_DB_GSM_11 = gps_info[10].Cn;
	}else{
		g_Edog_satellie_DB.satellie_DB_GSM_11 = 0;
	}
	
	if(gps_info[11].Valid == 1){
		g_Edog_satellie_DB.satellie_DB_GSM_12 = gps_info[11].Cn;
	}else{
		g_Edog_satellie_DB.satellie_DB_GSM_12 = 0;
	}

	
	#endif
}
void GPSGetData_Lock(void)
{
	sem_wait(&sem);
	//DBG_DUMP("GPSGetData_Lock \r\n");
}
void GPSGetData_Unlock(void)
{
	//DBG_DUMP("GPSGetData_Unlock \r\n");
	sem_post(&sem);
}

int 	GPS_ComRead(INT8U *buf, INT32U len)//
{
	GPSGetData_Lock();
	UINT32 size = GPSRec_GetStringLen();
	memset(buf,'\0',1024);
	memcpy(buf,GPSRec_GetString(),size);
	GPSRec_ResetString();
	//DBG_DUMP("222222===\r\n");
	GPSGetData_Unlock();
	return size;
}
int 	GPS_ComWrite(INT8U *buf, INT32U len)//useless
{
	return 0;
}
char gEdogVersion[33]="";

char*   GPSRec_GetEdogVersion(void)
{
	#if 1
	UINT32 builddate = GPSRadar_GetBaseDatabase_Ver();
	sprintf(gEdogVersion, "%d",builddate);
	#else
	if((EdogInfo_SentenceV.EDOG_Version1==0x00)
		&&(EdogInfo_SentenceV.EDOG_Version2==0x00)
		&&(EdogInfo_SentenceV.EDOG_Version3==0x00)
		&&(EdogInfo_SentenceV.EDOG_Version4==0x00))
	{
		sprintf(gEdogVersion, "          ",((EdogInfo_SentenceV.EDOG_Version4<<24)|(EdogInfo_SentenceV.EDOG_Version3<<16)|(EdogInfo_SentenceV.EDOG_Version2<<8)|EdogInfo_SentenceV.EDOG_Version1));
	}
	else
	{
		sprintf(gEdogVersion, "%d",((EdogInfo_SentenceV.EDOG_Version4<<24)|(EdogInfo_SentenceV.EDOG_Version3<<16)|(EdogInfo_SentenceV.EDOG_Version2<<8)|EdogInfo_SentenceV.EDOG_Version1));
	}
	#endif
	return gEdogVersion;
}

#endif


