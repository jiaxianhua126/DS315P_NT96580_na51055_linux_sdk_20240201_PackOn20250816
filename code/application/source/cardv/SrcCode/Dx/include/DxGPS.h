/**
    @file       GPSParser.h
    @ingroup

    @brief      Sample module brief
                Sample module description

    @note       Nothing (or anything need to be mentioned).

    Copyright   Novatek Microelectronics Corp. 2005.  All rights reserved.
*/

#ifndef _NMEAParser_H
#define _NMEAParser_H

//#include "type.h"
#include "uart.h"
#include "kwrap/nvt_type.h"

#define NMEA_BUFFER_OFFSET		(35*1024)   //35KB
#define NMEA_BUFFER_RESERVED	128
#define NMEA_SENTENCE_SIZE		240
#define NMEA_TYPE_SIZE			7
#define GSA_SENTENCE			0x41534750 //'A''S''G''P'
#define RMC_SENTENCE			0x434D5250 //'C''M''R''P'
#define GGA_SENTENCE			0x41474750 //'A''G''G''P'
#define GSV_SENTENCE			0x56534750 //'V''S''G''P'
#define GLL_SENTENCE			0x4C4C4750 //'L''L''G''P'
#define VTG_SENTENCE			0x47545650 //'G''T''V''P'
#define SNR_SENTENCE			0x4F534E45 //'O''S''N''E'
#define ROS_SENTENCE			0x534F5259 //'S''O''R''Y'
#define NRMC_SENTENCE			0x434D524E //'C''M''R''N'  //beidou
#define DGGA_SENTENCE			0x41474744 //'A''G''G''D'  //beidou
#define DGSV_SENTENCE			0x56534744 //'V''S''G''D'  //beidou
#define TXT_SENTENCE			0x54585450 //'T''X''T''P'//Unique Sky


#define GPS_FLAG_DATAVALID		0x00000001
#define GPS_FLAG_LOG			0x00000002

typedef struct {
	ER(*open)(void);
	ER(*close)(void);
	void(*init)(void);
	ER(*getString)(CHAR *pcString, UINT32 *pcBufferLen);
} GPS_UART_OBJ, *pGPS_UART_OBJ;

typedef struct {
	CHAR    *pGPSDataStartAddr;
	UINT32  GPSBufUsedPos;
	UINT32  GPSBufSize;
} GPSBuf, *pGPSBuf;

typedef struct {

	CHAR    *GGA;
	CHAR    *RMC;
	CHAR    *GSA;
	CHAR    *GSV;
	CHAR    *GLL;
	CHAR    *VTG;
	GPSBuf  GPSDataBuf;

} NMEASENTENCE;

typedef enum {
	No_Fix = 1,
	TWO_D_Fix,
	THREE_D_Fix
} FIXMODE;

//GSA, Satellite status
typedef struct {

	CHAR    SelMode;			//'A' auto selection of 2D or 3D fix
								//'M' manual
	UINT32  FixMode;			//'1' no fix
								//'2' 2D fix
								//'3' 3D fix
	UINT32  SatUsed01;			//PRNs of satellites used for fix (space for 12)
	UINT32  SatUsed02;
	UINT32  SatUsed03;
	UINT32  SatUsed04;
	UINT32  SatUsed05;
	UINT32  SatUsed06;
	UINT32  SatUsed07;
	UINT32  SatUsed08;
	UINT32  SatUsed09;
	UINT32  SatUsed10;
	UINT32  SatUsed11;
	UINT32  SatUsed12;
	double  PDOP;				//Position dilution of precision
	double  HDOP;				//Horizontal dilution of precision
	double  VDOP;				//Vertical dilution of precision

} GSAINFO;
extern GSAINFO GSAInfo;

//RMC, Recommended Minimum sentence C
typedef struct {

	UINT32    Hour;
	UINT32    Minute;
	UINT32    Second;
	UINT32    Year;
	UINT32    Month;
	UINT32    Day;
	CHAR      Status;			//Status A=active or V=Void
	CHAR      NSInd;
	CHAR      EWInd;
	CHAR      reservd;
	float     Latitude;
	float     Longitude;
	float     Speed;			//Speed over the ground in knots
	float     Angle;			//Track angle in degrees True

} RMCINFO;
extern RMCINFO RMCInfo;

//GGA, Global Positioning System Fix Data
typedef struct {

	UINT32    Hour;
	UINT32    Minute;
	UINT32    Second;
	double    Latitude;
	CHAR      NSInd;
	double    Longitude;
	CHAR      EWInd;
	UINT32    PosFixInd;		//Fix quality: 0 = invalid
								//             1 = GPS fix
	UINT32    SatNumber;		//Number of satellites being tracked
	double    HDOP;				//Horizontal dilution of position
	double    Altitude;			//Altitude, Meters, above mean sea level
	double    MSL;				//Height of geoid (mean sea level) above WGS84

} GGAINFO;
extern GGAINFO GGAInfo;

typedef struct {

	UINT32    SatNum;			//Satellite PRN number
	UINT32    Elev;				//Elevation, degrees
	UINT32    Azi;				//Azimuth, degrees
	UINT32    SNR;				//SNR - higher is better

} SATDATA;

//GSV, Satellites in view
typedef struct {

	UINT32    NumOfSen;			//Number of sentences for full data
	UINT32    SenNum;			//Sentence number
	UINT32    SatInView;		//Number of satellites in view
	SATDATA   SAT01;
	SATDATA   SAT02;
	SATDATA   SAT03;
	SATDATA   SAT04;
	SATDATA   SAT05;
	SATDATA   SAT06;
	SATDATA   SAT07;
	SATDATA   SAT08;
	SATDATA   SAT09;
	SATDATA   SAT10;
	SATDATA   SAT11;
	SATDATA   SAT12;
	SATDATA   SAT13;
	SATDATA   SAT14;
	SATDATA   SAT15;
	SATDATA   SAT16;

} GSVINFO;
extern GSVINFO GSVInfo;

typedef enum {
	GSA,
	RMC,
	GGA,
	GSV,
	GLL,
	VTG
} NMEATYPE;

typedef enum {
    GPSGMT_0 = 0,
    GPSGMT_P1,
    GPSGMT_P2,
    GPSGMT_P3,
    GPSGMT_P3_30,
    GPSGMT_P4,
    GPSGMT_P4_30,
    GPSGMT_P5,
    GPSGMT_P5_30,
    GPSGMT_P6,
    GPSGMT_P7,
    GPSGMT_P8,
    GPSGMT_P9,
    GPSGMT_P9_30,
    GPSGMT_P10,
    GPSGMT_P10_30,
    GPSGMT_P11,
    GPSGMT_P12,
    GPSGMT_P13,
    GPSGMT_M1,
    GPSGMT_M2,
    GPSGMT_M3,
    GPSGMT_M3_30,
    GPSGMT_M4,
    GPSGMT_M5,
    GPSGMT_M6,
    GPSGMT_M7,
    GPSGMT_M8,
    GPSGMT_M9,
    GPSGMT_M10,
    GPSGMT_M11,
    GPSGMT_M12,
    GPSGMT_P6_30,
    GPSGMT_M2_30,
} GPSGMT_TYPE;

//EDOG_MSG_TPYE_SATELLITE_DB	17bytes
typedef struct {
    char satellie_DB_header;
    char satellie_DB_cmdtype;
    char satellie_DB_GSM_Signal;
    char satellie_DB_GSM_1;
    char satellie_DB_GSM_2;
    char satellie_DB_GSM_3;
    char satellie_DB_GSM_4;
    char satellie_DB_GSM_5;
    char satellie_DB_GSM_6;
    char satellie_DB_GSM_7;
    char satellie_DB_GSM_8;
    char satellie_DB_GSM_9;
    char satellie_DB_GSM_10;
    char satellie_DB_GSM_11;
    char satellie_DB_GSM_12;
    char satellie_DB_end[2];
} EDOG_SATELLITE_DB;
extern EDOG_SATELLITE_DB g_Edog_satellie_DB;
typedef enum {
	NORTH_EAST = 1,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	NORTH_WEST,
	NORTH,
} DIRTYPE;


extern void GPS_InstallID(void) _SECTION(".kercfg_text");
extern void GPS_SetUartObj(GPS_UART_OBJ *UartObj);
extern ER GPSRec_Open(void);
extern ER GPSRec_Close(void);
extern ER GPSRec_Reset(void);
extern BOOL GPSRec_CheckData(void);
extern void GPS_SetSpeedUint(INT8 value);
extern FLOAT GPSRec_GetGPS_Speed(void);
extern CHAR *Get_GpsSpeedString(void);
extern char *GPS_GetMovieData(void);
extern char *GPS_GetMovieData_Coordinates(void);
extern char *GPS_GetMovieData_Speed(void);
extern char *GPS_OSDSpeedData(void);
extern BOOL GPSRec_GetRMCDate(RMCINFO *pRMCInfo);
extern BOOL GPSRec_GetGGADate(GGAINFO *pGGAInfo);

extern INT32 GPSRec_getAngle(void);
extern double GetRealXY(double dXY);
extern void GPSRec_GetRMCNData(void);
extern void GPSRec_GetRMCEData(void);

extern UINT32 GPSRec_GetGPS_Month(void);
extern UINT32 GPSRec_GetGPS_Day(void);
extern UINT32 GPSRec_GetGPS_Hour(void);
extern UINT32 GPSRec_GetGPS_Minute(void);

//#NT#2015/10/02#KCHong -begin
//#NT#Add GPS heartbeat to detect GPS status
extern BOOL GPSRec_GetSpeed(FLOAT *Speed);
extern UINT32 GetGPSHeartBeat(void);
//#NT#2015/10/02#KCHong -end
extern char *GetGPS_Data(void);
extern UINT32 _SECTION(".kercfg_data") GPSRECEIVE_ID; // GPS Task
extern UINT32 _SECTION(".kercfg_data") FLG_ID_GPS; // GPS Flag
//#HTK#20230830#add edog -start
extern char*   GPSRec_GetEdogVersion(void);
extern UINT32  GetGPSAvgRemainSec(void);

typedef struct{
	UINT8 Flag_ID1;
	UINT8 Flag_ID2;
	UINT8 Distatnce1;
	UINT8 Distatnce2;
	UINT8 Distatnce3;
	UINT8 SpeedLimit;
	UINT8 SpeedAvg;
	UINT8 Stus;
}AvgSpeed_Info;

//Edog Info alarm info
typedef struct{
    UINT8 	EDOG_Start;//"$"
    UINT8 	EDOG_DataType;
    UINT8 	EDOG_Len;
	UINT8 	EDOG_AlarmType;//default :0xff
    UINT8 	EDOG_SpeedLimit;
    UINT8  	EDOG_Distance1;
	UINT8   EDOG_Distance2;
    UINT8 	EDOG_RadarType;//no useless
    UINT8 	EDOG_RadarSingal;//no useless,0--3  
    UINT8 	EDOG_Flag1;//Russia use
    UINT8 	EDOG_Flag2;//Russia use
	UINT8 	EDOG_BackShot_Sts;//Russia  use
	UINT8 	EDOG_BackShot_Dis1;//Russia  use
	UINT8 	EDOG_BackShot_Dis2;//Russia  use
	UINT8 	EDOG_BackShot_Speed;//Russia  use
	UINT8 	EDOG_AvgSpeedCnt;//MAX :8
	//AvgSpeed_Info *pAvgSpeed_Info;
	AvgSpeed_Info AvgSpeed_Info[8]; 
    UINT8 	EDOG_ChkSum;
    UINT8 	EDOG_EndCode1;
    UINT8 	EDOG_EndCode2;
}EDOGINFO_UNIQUESKY_A;
typedef struct{
		UINT8 Valid;
		UINT8 PRN;
		UINT8 Cn;
}Satellite_Info;

#define 	RADAR_KU 			0xF9 //249
#define 	RADAR_K 			0xFA //250
#define 	RADAR_KA 			0xFB //251
#define 	RADAR_X 			0xFC //252
#define 	RADAR_Laser 		0xFD //253
#define 	RADAR_ERROR 		0xFE //254
#define 	RADAR_CONNECTED 	0xFF //255

#define 	FLAG_BACKSHOT 		0x00000004
#define 	FLAG_STARTCAS 		0x00000040
#define 	FLAG_FINISHCAS 		0x00000080

#define 	SPEED_DECTION_START	2
#define 	SPEED_DECTION_READY 1	
#define 	SPEED_DECTION_VALID	0


extern EDOGINFO_UNIQUESKY_A EdogInfo_SentenceA;
//#HTK#20230830#add edog -end
extern char*   GPSRec_GetEdogVersion(void);

#endif
