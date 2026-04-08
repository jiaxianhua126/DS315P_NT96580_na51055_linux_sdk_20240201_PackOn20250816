
#ifndef _UIFLOWLVGL_SPORTCAM_H
#define _UIFLOWLVGL_SPORTCAM_H

/**************************************************************************************
 * External Variables
 **************************************************************************************/

extern const PALETTE_ITEM gDemoKit_Palette_Palette[256];

/**************************************************************************************
 * Include headers
 **************************************************************************************/


#if(IPCAM_FUNC!= ENABLE)
#include "UIWnd/LVGL_SPORTCAM/UIInfo/UIInfo.h"
#include "UIWnd/LVGL_SPORTCAM/UIInfo/DateTimeInfo.h"
#endif

/* Resource */
#include "UIWnd/LVGL_SPORTCAM/Resource/UIResource.h"
#include "UIWnd/LVGL_SPORTCAM/Resource/BG_Opening.h"
#include "UIWnd/LVGL_SPORTCAM/Resource/SoundData.h"
#include "UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowWaitMoment/UIFlowWaitMomentAPI.h"
#include "UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowUSB/UIFlowWndUSBAPI.h"
#include "UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowCompat.h"
#include "UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowWrnMsg/UIFlowWrnMsgAPI.h"
#include "UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowMovie/UIFlowMovieFuncs.h"
#include "UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowPlay/UIFlowPlayFuncs.h"
#include "UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowPhoto/UIFlowPhotoFuncs.h"
#include "KyAdas/algo_result.h"
#include "UIWnd/LVGL_SPORTCAM/UIInfo/UIInfo.h"
#include "UIWnd/LVGL_SPORTCAM/UIInfo/UIPhotoInfo.h"
#include "UIWnd/LVGL_SPORTCAM/UIInfo/UIPhotoMapping.h"
#include "UIWnd/LVGL_SPORTCAM/UIInfo/UIMovieInfo.h"
#include "UIWnd/LVGL_SPORTCAM/UIInfo/UIMovieMapping.h"
#include "UIWnd/LVGL_SPORTCAM/UIInfo/DateTimeInfo.h"
#include "UIFlowLVGL/UIFlowLVGL.h"
#include "UIFlowLVGL/UIFlowMenuCommonItem/TabMenu.h"
#include "UIFlowLVGL/UIFlowMenuCommonItem/MenuId.h"
#include "UIFlowLVGL/UIFlowMenuCommonItem/MenuMovie.h"
#include "UIFlowLVGL/UIFlowMenuCommonItem/MenuMode.h"
#include "UIFlowLVGL/UIFlowMenuCommonItem/MenuSetup.h"
#include "UIFlowLVGL/UIFlowMenuCommonItem/MenuPhoto.h"
#include "UIFlowLVGL/UIFlowMenuCommonItem/MenuPlayback.h"
#include "UIFlowLVGL/UIFlowMenuCommonItem/MenuCommon.h"

/*
 * Reuse the SPORTCAM system flag/default model while the runtime UI is LVGL.
 * SysMain still references several legacy movie/Wi-Fi helpers directly.
 */
extern BOOL ParkingM_PreRecord_EMR;
extern BOOL g_NotRecordWrn;
extern BOOL bWndWiFiMovieOpenFirst;
extern BOOL bWiFiModeChanged;
extern BOOL WifiStarting;
extern BOOL autoWifi;
extern BOOL WifiMotionLed_EN;
extern BOOL g_uiWiFiRecordIngMotionDet;
extern BOOL g_uiWiFiParkingModeMotionDet;
extern BOOL bWiFiRec_AutoStart;
extern BOOL bWiFiRec_AutoStop;
extern BOOL g_bWiFiMovieHDR_changed;
extern BOOL isACCTrigParkMode;
extern BOOL isACCTrigLowBitrate;
extern BOOL isACCTrigPreRecordDet;
extern char CarNo_Buf[13];
extern char Customize_Buf[13];
extern char gUICarNo_StrBuf[13];
extern char gUICustomize_StrBuf[13];
extern char g_GPSstamp_buffer[128];
extern char gUICustomer_Model[20];
extern char gUICustomer_Null[20];
extern char gUICustomer_StrBuf[20];
extern AlgoEventData adas_eventData_app;
extern AlgoEventData rcw_eventData_app;
extern VControl UIFlowWndWrnMsgCtrl;
extern VControl UIFlowWndWiFiMovieCtrl;
extern VControl UIFlowWndMovie_Panel_Normal_DisplayCtrl;
extern VControl UIFlowWndMovie_ADAS_Alert_DisplayCtrl;
extern VControl UIMenuWndWiFiMobileLinkOKCtrl;

extern void FlowMovie_BaseDaySet(int year, int month, int day);
extern BOOL FlowMovie_WakeUpLCDBacklight(void);
extern UINT32 FlowWiFiMovie_GetRecCurrTime(void);
extern void FlowWiFiMovie_SetRecCurrTime(UINT32 RecCurrTime);
extern void FlowWiFiMovie_UpdateIcons(BOOL bShow);
extern void FlowWiFiMovie_IconDrawTimelapse(BOOL bShow);
extern void FlowWiFiMovie_IconDrawMotionDet(BOOL bShow);
extern void FlowWiFiMovie_IconDrawAudio(BOOL bShow);
extern void FlowMovie_SetSOSStatusNow(BOOL En);
extern BOOL FlowMovie_GetSOSStatusNow(void);
extern void FlowMovie_USBRemovePowerOff(void);
extern void UIFlowWndWiFiMovie_StopTimer(void);
extern UINT32 Get_ParkingModeTimeLapseValue(UINT32 uiIndex);
extern BOOL FlowMovie_IsEthCamConnectOK(void);
extern BOOL FlowMovie_IsStorageErr(BOOL IsCheckFull);
extern void FlowMovie_SetLedFlash_BeepWrn(BOOL std);
extern INT32 UIFlowWndWiFiMovie_OnCustom2(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern void UIVoice_Play(UINT32 index);
extern UINT32 UIMenuWndPlayFileType_GetFileType(void);

#ifndef FLOWWRNMSG_TIMER_KEEP
typedef enum {
	FLOWWRNMSG_TIMER_KEEP = 0,
	FLOWWRNMSG_TIMER_1SEC,
	FLOWWRNMSG_TIMER_2SEC,
	FLOWWRNMSG_TIMER_3SEC,
	FLOWWRNMSG_TIMER_4SEC,
	FLOWWRNMSG_TIMER_5SEC,
	FLOWWRNMSG_TIMER_MAX
} FLOWWRNMSG_TIMER;
#endif

#ifndef UIFlowWndWrnMsg_StatusTXT_Msg_STRID_PLEASE_INSERT_SD
#define UIFlowWndWrnMsg_StatusTXT_Msg_STRID_PLEASE_INSERT_SD FLOWWRNMSG_ISSUE_PLEASE_INSERT_SD
#endif

/**************************************************************************************
 * Type Define
 **************************************************************************************/

/* nvt message */
typedef struct {
	NVTEVT event;
	UINT32* paramArray;
	UINT32 paramNum;
} LV_USER_EVENT_NVTMSG_DATA;


/* user defined event, must start from _LV_PLUGIN_EVENT_LAST */
typedef enum {

	LV_USER_EVENT_START = _LV_PLUGIN_EVENT_LAST,
	LV_USER_EVENT_NVTMSG = LV_USER_EVENT_START, 		/* lv_event_get_data(): LV_USER_EVENT_NVTMSG_DATA */
	LV_USER_EVENT_KEY_RELEASE,							/* lv_event_get_data():  */

} LV_USER_EVENT;

/* user defined key for mapping NVT_KEY_XXX */
typedef enum {

	LV_USER_KEY_DOWN = LV_KEY_DOWN,
	LV_USER_KEY_UP = LV_KEY_UP,

	LV_USER_KEY_DEF_START = 128,
	LV_USER_KEY_SHUTTER1,
	LV_USER_KEY_SHUTTER2,
	LV_USER_KEY_ZOOMIN,
	LV_USER_KEY_ZOOMOUT,
	LV_USER_KEY_PREV,
	LV_USER_KEY_NEXT,
	LV_USER_KEY_MENU,
	LV_USER_KEY_SELECT,
	LV_USER_KEY_MODE,
	LV_USER_KEY_CALIBRATION,
	LV_USER_KEY_DEF_END = 255,
	LV_USER_KEY_UNKNOWN = LV_USER_KEY_DEF_END,

} LV_USER_KEY;


/**************************************************************************************
 * Macros
 **************************************************************************************/

#define MAX_MESSAGE_PARAM_NUM      3
LV_USER_EVENT_NVTMSG_DATA* gen_nvtmsg_data(NVTEVT event, UINT32 paramNum, ...);


/**************************************************************************************
 * Global Functions
 **************************************************************************************/

int lv_user_task_handler_lock(void);
void lv_user_task_handler_unlock(void);
int lv_user_task_handler_temp_release(int (*cb)(void));

void lv_user_update_pointer_state(
		uint32_t x,
		uint32_t y,
		bool pressed
);

#endif
