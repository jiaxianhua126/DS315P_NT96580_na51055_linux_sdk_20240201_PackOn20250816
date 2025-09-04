#ifndef _EDOGGLOBAL_H_
#define _EDOGGLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define  PLATFORM_NVT			(0)

#if (PLATFORM_NVT)
#include "Debug.h"
#endif

#ifdef __cplusplus
    extern   "C"
    {
#endif

//==============================================================================
//
//                              TYPEDEF DEFINE
//
//==============================================================================

//#define BOOL   				unsigned char			// 1 Byte
#define UCHAR				unsigned char			// 1 Byte
#define UINT				unsigned int			// 2 Bytes
#define USHORT				unsigned short			// 2 Bytes
#define BYTE   				unsigned char			// 1 Byte
#define WORD				unsigned short			// 2 Bytes
#define DWORD  				unsigned long			// 4 Bytes

//typedef unsigned char           BOOLEAN;
typedef unsigned char           INT8U;
typedef signed   char           INT8S;
typedef unsigned short          INT16U;
typedef signed   short          INT16S;
typedef unsigned int            INT32U;
typedef signed   int            INT32S;
typedef float        			FP32;
typedef double					FP64;
//typedef	long long		        INT64S;
//typedef	unsigned long long	 INT64U;
#if !(PLATFORM_NVT)
typedef double                  FP64;
#endif
//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================
#ifndef PUBLIC
#define PUBLIC
#endif

#ifndef LOCAL
#define LOCAL   							static
#endif

#ifndef TRUE
#define TRUE                   	 			1
#endif

#ifndef FALSE
#define FALSE                   			0
#endif

#ifndef NULL
#define NULL                    			((void*)0)
#endif

#define GPS_MAX_CHAN  						16
#define GPS_MULT   							(100000.0)
#define EDOG_ALGORITHM_CAS_NESTING_MAX		(8)

#define GPS_MODULE_ENC_HANDSHAKE
#define orginal

#define EDOG_DEBUG_EN			0
#if(EDOG_DEBUG_EN)
#if (PLATFORM_NVT)
#define edog_printf(fmtstr,args...)		debug_msg(fmtstr,##args)
#else
#define edog_printf(fmtstr,args...)		printf(fmtstr,##args)
#endif
#else
#define edog_printf(fmtstr,args...)
#endif

#define ESC_ATR_COLOR_DEFAULT                       "\033[0m"
#define ESC_FG_COLOR_RED                            "\033[31m"
#define ESC_FG_COLOR_GREEN                          "\033[32m"

#define FG_RED(X)                 ESC_FG_COLOR_RED             X ESC_ATR_COLOR_DEFAULT
#define FG_GREEN(X)               ESC_FG_COLOR_GREEN           X ESC_ATR_COLOR_DEFAULT

#ifndef	MEMSET
#define MEMSET(s,c,n)       memset(s,c,n)
#endif

#ifndef	MEMSET0
#define MEMSET0(s)      	memset(s,0,sizeof(*s))
#endif
#ifndef	MEMCPY
#define MEMCPY(d, s, c) 	memcpy (d, s, c)
#endif

#ifndef	MIN
#define MIN(a,b)        	((a)>(b)?(b):(a))
#endif
#ifndef	MAX
#define MAX(a,b)        	((a)<(b)?(b):(a))
#endif

//==============================================================================
//
//                              ENUM DEFINE
//
//==============================================================================
typedef enum error_a
{
  EDOG_NO_ERROR = 0,
  EDOG_ERROR
} error_t;

typedef enum _EDOG_TYPE_
{
	EDOG_TYPE_NONE 					= 0,
	EDOG_TYPE_STRELKA_1				= 1,
	EDOG_TYPE_STRELKAVB_2			= 2,
	EDOG_TYPE_CAMERAAHEAD_3			= 3,
	EDOG_TYPE_AvtodoriaStart_4		= 4,
	EDOG_TYPE_AvtodoriaFinish_5		= 5,
	EDOG_TYPE_Potok_6				= 6,
	EDOG_TYPE_PoliceStation_7		= 7,
	EDOG_TYPE_POSTDPS_8 			= 8,
	EDOG_TYPE_Radar_9				= 9,
	EDOG_TYPE_Muliage_10			= 10,
	//EDOG_TYPE_11 = 11,
	//EDOG_TYPE_12 = 12,
	EDOG_TYPE_Avtouragan_13			= 13,
	EDOG_TYPE_Mobile_14				= 14,
	EDOG_TYPE_KRIS_15				= 15,
	EDOG_TYPE_Platon_16				= 16,
	//EDOG_TYPE_17,
	//EDOG_TYPE_18,
	//EDOG_TYPE_19,
	//EDOG_TYPE_20,
	//EDOG_TYPE_21,
	EDOG_TYPE_Mesta_22				= 22,
	EDOG_TYPE_ODISSEY_23			= 23,
	EDOG_TYPE_REDSPEED_24			= 24,
	EDOG_TYPE_KORDON_25				= 25,
	EDOG_TYPE_VOCORD_26				= 26,
	EDOG_TYPE_BINAR_27				= 27,
	EDOG_TYPE_ARGUS_28				= 28,
	EDOG_TYPE_PKS_29				= 29,
	EDOG_TYPE_VIZIR_30				= 30,
	EDOG_TYPE_ARENA_31				= 31,
	EDOG_TYPE_ROBOT_32				= 32,
	EDOG_TYPE_MULT_33				= 33,
	EDOG_TYPE_RAPIRA_34				= 34,
	EDOG_TYPE_SFINKS_35				= 35,
	EDOG_TYPE_INTGRKDD_36			= 36,
	EDOG_TYPE_AZIMUT_37				= 37,
	//EDOG_TYPE_38
	EDOG_TYPE_RoadScan_39			= 39,
	EDOG_TYPE_SOVA_40				= 40,
	//EDOG_TYPE_41,
	//EDOG_TYPE_42,
	//EDOG_TYPE_43,
	EDOG_TYPE_Ptolemey_44			= 44,
	EDOG_TYPE_Autopatr_45			= 45,
	EDOG_TYPE_Polyscan_46			= 46,
	EDOG_TYPE_Speclab_47			= 47,
	EDOG_TYPE_TRAFSCAN_48			= 48,
	EDOG_TYPE_FORSAG_49				= 49,
	//EDOG_TYPE_50
	EDOG_TYPE_Orlan_51				= 51,
	EDOG_TYPE_DOZORK_52				= 52,
	//EDOG_TYPE_53,
	EDOG_TYPE_SERGEK_54				= 54,
	EDOG_TYPE_OSKON_55				= 55,
	//EDOG_TYPE_56,
	//EDOG_TYPE_57,
	//EDOG_TYPE_58,
	//EDOG_TYPE_59,
	EDOG_TYPE_STFALKON_60			= 60,
	EDOG_TYPE_Vlatacom_61			= 61,
	//EDOG_TYPE_62,
	//EDOG_TYPE_63,
	//EDOG_TYPE_64,
	//EDOG_TYPE_65,
	EDOG_TYPE_Kopernic_66			= 66,
	EDOG_TYPE_AUTODORIA_67			= 67,

	EDOG_TYPE_ALL		= 255,
	EDOG_TYPE_MAX		= 255
}EDOG_TYPE;

typedef enum _EDOG_FLAG_{
	EDOG_FLAG_NONE = 0,
	EDOG_FLAG_BUSLANE 			= 0x00000001,
	EDOG_FLAG_TRAFFICLIGHTS 	= 0x00000002,
	EDOG_FLAG_BACKSHOT 			= 0x00000004,
	EDOG_FLAG_ZEBRA 			= 0x00000008,
	EDOG_FLAG_OBOCHINA 			= 0x00000010,
	EDOG_FLAG_RECTANGLE			= 0x00000020,
	EDOG_FLAG_STARTCAS 			= 0x00000040,
	EDOG_FLAG_FINISHCAS 		= 0x00000080,
	EDOG_FLAG_SPEEDVAR			= 0x00000100,
	EDOG_FLAG_PARKING 			= 0x00000200,
	EDOG_FLAG_ROADLANE			= 0x00000400,
	EDOG_FLAG_RESERVED			= 0x00000800,
	EDOG_FLAG_KCC				= 0x10000000,
	EDOG_FLAG_COMBINATION		= 0x40000000,
	EDOG_FLAG_MAX				= 0x80000000
} EDOG_FLAG;

typedef enum _CAS_STAGE_
{
	CAS_STAGE_OFF = 0,
	CAS_STAGE_READY,
	CAS_STAGE_START,
	CAS_STAGE_MAX
}CAS_STAGE;

typedef enum _GPS_MODE_
{
	kGpsModeNone = 0,
	kGpsModeGps,
	kGpsModeGpsBds,
	kGpsModeGpsGlonass,
	kGpsModeMax
}GNSS_MODE_E;
//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
typedef	struct dir_f
{
	INT8S east;
	INT8S west;
	INT8S north;
	INT8S south;
}dir_flag;

typedef struct _GPSRADAR_GPSINFO
{
	INT32S     latitude;                  // current latitude  (業方* 10000)
	INT32S     longitude;                 // current longitude 業方* 10000
	INT32S     latitudeEnc;               // current latitude  (業方* 10000)
	INT32S     longitudeEnc;              // current longitude 業方* 10000
	INT16U     speed;               	  // speed over ground, knots
	INT16U     course;              	  //
	INT16U     year;					  //
	INT8U      month;                	  //
	INT8U      day;                 	  //
	INT8U      hour;                 	  //
	INT8U      minute;               	  //
	INT8U      second;               	  //
	INT8U      valid;                	  // 1 = Data valid, 0 = navigation rx warning
	 
	INT8U 	   validSatNum;					//For GPS
	INT8U	   blValidSatNum;			  	//For BDS or GLONASS
	INT8U 	   testmode;					//reserved
	INT8U  	   mode;					  	//GNSS_MODE_E

	INT8U	   SatInfo[3*GPS_MAX_CHAN];		//For GPS
	INT8U	   BDSatInfo[3*GPS_MAX_CHAN];	//For BDS
	INT8U 	   GLSatInfo[3*GPS_MAX_CHAN];	//For GLONASS

	INT8U 	   SatsInSolution[12];			//For GPS
	INT8U 	   BLSatsInSolution[12];		//For BDS or GLONASS

	dir_flag   direction_flag;
}ST_GPSRADAR_GPSINFO,*PST_GPSRADAR_GPSINFO;

//==============================================================================
//
//                              EXTERN FUNCTION PROTOTYPES
//
//==============================================================================
extern INT32U 	edog_resource_rd_cb_t(INT8U *buffer,INT32U offset,INT32U count);
extern void 	edog_notify_cb_t(INT8U alarm,INT32U event,INT32U speed,INT16U distance);
extern void 	edog_location_notify_cb_t(PST_GPSRADAR_GPSINFO gpsinfo);
extern int 		GPS_ComRead(INT8U *buf, INT32U len);
extern int 		GPS_ComWrite(INT8U *buf, INT32U len);

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
//EDOG
PUBLIC INT8U 	Edog_Init(INT32U base_time);
PUBLIC void  	Edog_Run(void);			//200ms once
PUBLIC INT32U 	GPSRadar_GetBaseDatabase_Ver(void);
PUBLIC INT8U 	GPSRadar_IsDbValid(void);

PUBLIC INT32U 	GPSRadar_GetPrevCASDistance(void);
PUBLIC INT16U 	GPSRadar_GetPrevCASOverspeed(void);
PUBLIC INT16U 	GPSRadar_GetPrevCASAverageSpeed(void);
PUBLIC CAS_STAGE GPSRadar_GetPrevCASStart(void);

PUBLIC INT32U 	GPSRadar_GetCurrentCASDistance(void);
PUBLIC INT16U 	GPSRadar_GetCurrentCASOverspeed(void);
PUBLIC INT16U 	GPSRadar_GetCurrentCASAverageSpeed(void);
PUBLIC CAS_STAGE GPSRadar_GetCurrentCASStart(void);

PUBLIC INT32U 	GPSRadar_GetCASNesting(void);

PUBLIC INT32U 	GPSRadar_GetBackShotStart(void);
PUBLIC INT32U 	GPSRadar_GetBackShotDistance(void);
PUBLIC INT16U  	GPSRadar_GetBackShotOverspeed(void);

PUBLIC INT32U 	GPSRadar_SetAlarmDistanceMin(INT16U dist);
PUBLIC INT32U 	GPSRadar_SetAlarmTypeEnable(INT8U type, INT8U enable);
PUBLIC INT32U 	GPSRadar_SetAlarmFlagEnable(INT16U flag, INT8U enable);
PUBLIC INT16U 	GPSRadar_SetBackShotDistance(INT16U dist);

PUBLIC INT32U 	GPSRadar_DistanceTwoPoints(FP64 lat1,FP64 lng1,FP64 lat2,FP64 lng2);
PUBLIC char* 	GPSRadar_GetLibVer(void);
#ifdef   __cplusplus
    }
#endif

#endif

