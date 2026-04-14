
#ifndef _UIFLOWMOVIEFUNCS_H
#define _UIFLOWMOVIEFUNCS_H
#include "lvgl/lvgl.h"
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
extern BOOL 	FlowMovie_IsStorageErr(BOOL IsCheckFull);
extern BOOL 	FlowMovie_IsStorageErr2(lv_obj_t* parent,BOOL IsCheckFull);
extern void   FlowMovie_OnTimer1SecIndex(void);

//Callback function
extern void FlowMovie_RawEncCB(UINT32 uiEventID);
extern void   FlowMovie_LCDDimDsiable(UINT8 uCount);
extern void   FlowMovie_DetLCDDim(void);
void Set_PreviewStable_Record(BOOL value);
BOOL Get_PreviewStable_Record(void);
void UIFlowWndMovie_OnAutoStartRec(void);
void UIFlowMoive_AutoStartWiFi(void);
extern void FlowMovie_UpdateLED(void);
extern void FlowMovie_SetCrash(void);
extern void FlowMovie_SetSOSStatusNow(BOOL En);
extern BOOL FlowMovie_GetSOSStatusNow(void);
extern BOOL   FlowMovie_WakeUpLCDBacklight(void);
extern void GPIOMap_TurnOnLCDBacklight(void);
extern void GPIOMap_TurnOffLCDBacklight(void);

// Functions from UIFlowLVGLCompat.c and UIFlowCompat.c
extern BOOL ParkingM_PreRecord_EMR;
extern BOOL g_NotRecordWrn;
extern BOOL bWndWiFiMovieOpenFirst;
extern BOOL bWiFiModeChanged;
extern BOOL WifiStarting;
extern BOOL g_uiWiFiRecordIngMotionDet;
extern BOOL g_uiWiFiParkingModeMotionDet;
extern BOOL bWiFiRec_AutoStart;
extern BOOL bWiFiRec_AutoStop;
extern char CarNo_Buf[13];
extern char Customize_Buf[13];
extern char gUICarNo_StrBuf[13];
extern char gUICustomize_StrBuf[13];
extern char g_GPSstamp_buffer[128];
extern char gUICustomer_Model[20];
extern char gUICustomer_Null[20];
extern char gUICustomer_StrBuf[20];
extern VControl UIFlowWndWrnMsgCtrl;
extern VControl UIFlowWndWiFiMovieCtrl;
extern VControl UIMenuWndWiFiMobileLinkOKCtrl;

extern void FlowMovie_BaseDaySet(int year, int month, int day);
extern UINT32 FlowWiFiMovie_GetRecCurrTime(void);
extern void FlowWiFiMovie_SetRecCurrTime(UINT32 RecCurrTime);
extern void FlowWiFiMovie_UpdateIcons(BOOL bShow);
extern void FlowWiFiMovie_IconDrawTimelapse(BOOL bShow);
extern void FlowWiFiMovie_IconDrawMotionDet(BOOL bShow);
extern void FlowWiFiMovie_IconDrawAudio(BOOL bShow);
extern UINT32 Get_ParkingModeTimeLapseValue(UINT32 uiIndex);
extern BOOL FlowMovie_IsEthCamConnectOK(void);
extern void FlowMovie_SetLedFlash_BeepWrn(BOOL std);
extern void FlowMovie_USBRemovePowerOff(void);
extern void UIVoice_Play(UINT32 index);
extern void UIFlowWndWiFiMovie_StopTimer(void);
extern UINT32 UIMenuWndPlayFileType_GetFileType(void);
extern INT32 UIFlowWndWiFiMovie_OnCustom2(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);

#endif //_UIFLOWMOVIEFUNCS_H
