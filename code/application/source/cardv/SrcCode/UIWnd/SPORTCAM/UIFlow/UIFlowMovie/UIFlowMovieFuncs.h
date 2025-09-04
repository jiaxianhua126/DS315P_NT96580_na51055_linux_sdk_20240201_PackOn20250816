
#ifndef _UIFLOWMOVIEFUNCS_H
#define _UIFLOWMOVIEFUNCS_H
//#include "UIFlow.h"
//#include "Type.h"

#define UIFlowWndMovie_Restart_Rec      0x5a5a

enum _MOV_TASK_STATE {
	MOV_ST_IDLE = 0,		// idle mode
	MOV_ST_MENU,			// menu mode
	MOV_ST_WARNING_MENU,
	MOV_ST_VIEW,			// preview mode
	MOV_ST_VIEW_WAIT,
	MOV_ST_REC,				// record movie
	MOV_ST_REC_WAIT,		// record movie
	MOV_ST_PAUSE,			// pause recording
	MOV_ST_SHUTTER_1,		// shutter 1 key pressed state
	MOV_ST_ZOOM = 0x80,		// zoom state (using MSB, because it could be combined with VIEW/REC state)
};

typedef struct _MOV_TASK_DATA {
	UINT8   State;			// current state
	UINT8   err;			// error status
	UINT16  TimerCount;		// timer count (per 100 ms)
	UINT16  SysTimeCount;	// System time count (per 1s)
	UINT16  MsgCount;		// message display count (per 100 ms)
	BOOL    bEnterMenu;		// enter menu confirm flag
} MOV_TASK_DATA;

extern MOV_TASK_DATA gMovData;
extern UINT8  FlowMovie_GetMovDataState(void);
extern void   FlowMovie_StartRec(void);
extern void   FlowMovie_StopRec(void);
extern void   FlowMovie_StopRecSelfTimer(void);
extern UINT8  FlowMovie_GetDataState(void);
extern void   FlowMovie_SetRecMaxTime(UINT32 RecMaxTime);
extern UINT32 FlowMovie_GetRecMaxTime(void);
extern void   FlowMovie_SetRecCurrTime(UINT32 RecCurrTime);
extern UINT32 FlowMovie_GetRecCurrTime(void);
extern UINT32 FlowMovie_GetSelfTimerID(void);
extern BOOL   FlowMovie_IsStorageErr(BOOL IsCheckFull);
extern void   FlowMovie_GetPictureInMovie(void);
extern BOOL   FlowMovie_ChkDrawStoreFullFolderFull(void);
extern void   FlowMovie_SensorHotPlugStatus(BOOL flag);
extern void   FlowMovie_OnTimer1SecIndex(void);

extern void   FlowMovie_SetSOSStatusNow(BOOL En);
extern BOOL   FlowMovie_GetSOSStatusNow(void);
extern void   FlowMovie_LCDDimDsiable(UINT8 uCount);
extern void   FlowMovie_DetLCDDim(void);
extern void   FlowMovie_SetLCDDimStatus(BOOL En);
extern BOOL   FlowMovie_GetLCDDimStatus(void);
extern BOOL   FlowMovie_WakeUpLCDBacklight(void);

extern int    BaseDay_DiffDays(int y1,int m1,int d1,int y2,int m2,int d2);
extern void   FlowMovie_BaseDaySet(int year,int month,int day);
extern void   FlowMovie_SaveBaseDay(void);
extern void   FlowMovie_Specail_Flag_Set(BOOL std);
extern UINT32 FlowMovie_Specail_Flag_Get(void);
extern BOOL   FlowMovie_Specail_FormatWarning(void);
extern BOOL   FlowMovie_CheckFormatWrning(void);

extern void   FlowMovie_DetVx1LED(UINT8 uState);
extern void   FlowMovie_USBRemovePowerOff(void);
extern void   FlowMovie_SetLedFlash_BeepWrn(BOOL std);
extern void   FlowMovie_SetGsensorParkingModeStatus(BOOL En);
extern BOOL   FlowMovie_GetGsensorParkingModeStatus(void);
extern void   FlowMovie_SetACCPowerOffStatus(BOOL En);
extern BOOL   FlowMovie_GetACCPowerOffStatus(void);
extern UINT32 FlowMovie_GetTimelapseCyclicValue(void);
extern UINT32 FlowMovie_GetParkingModeTLCyclicValue(void);
extern UINT32 FlowMovie_GetShutdownTimer(void);
extern void   FlowMovie_CreateFileRecoveryTxt(void);
extern void   FlowMovie_DeleteFileRecoveryTxt(void);
extern BOOL   FlowMovie_CheckFileRecoveryTxt(void);
extern void FlowMovie_AutoHDR(void);

#if 1//(defined(_NVT_ETHREARCAM_RX_))
extern BOOL   SysInit_GetEthTxFW_Update_getstd(void);
extern BOOL   SysInit_GetEthBootFW_Update_getstd(void);
extern void   FlowMovie_LCDIconDimDsiable(UINT8 uCount);
extern void   FlowMovie_DetLCDIconHide(void);
#endif

extern BOOL SysInit_getintoGPS_mode_getstd(void);
extern BOOL GPIOMap_IsLCDBacklightOn(void);
extern void GPIOMap_TurnOnLCDBacklight(void);
extern void GPIOMap_TurnOffLCDBacklight(void);
extern void UIFlowWndMovie_OnDeleteOld(void);
extern UINT32 System_GetEnableSensor(void);

extern BOOL isACCTrigPowerOn;
extern BOOL isACCTrigParkMode;
extern BOOL isACCTrigLowBitrate;
extern BOOL isACCTrigPreRecordDet;
extern BOOL ParkingM_PreRecord_EMR;
extern UINT8 g_FileRecoveryFlag;
extern BOOL g_NotRecordWrn;
extern BOOL g_RearErr;
extern UINT8 g_RearRebootCnt;

//Callback function
extern void FlowMovie_RawEncCB(UINT32 uiEventID);
#endif //_UIFLOWMOVIEFUNCS_H
