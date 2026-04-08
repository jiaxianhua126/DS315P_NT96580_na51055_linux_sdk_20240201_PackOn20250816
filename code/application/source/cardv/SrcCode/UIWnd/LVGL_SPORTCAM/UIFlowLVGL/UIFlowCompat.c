#include "PrjInc.h"
#include "UIWnd/UIFlow.h"
#include "UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowMovie/UIFlowMovieFuncs.h"
#include "UIApp/Network/WifiAppCmd.h"
#include "UIApp/Network/UIAppWiFiCmdMovie.h"
#include "Dx/include/DxInput.h"

static UINT32 g_uiCompatBaseDay = 0;
static UINT32 g_wifi_movie_rec_curr_time = 0;

BOOL ParkingM_PreRecord_EMR = FALSE;
BOOL g_NotRecordWrn = FALSE;
BOOL WifiStarting = FALSE;
BOOL WifiMotionLed_EN = FALSE;
BOOL g_bWiFiMovieHDR_changed = FALSE;
char CarNo_Buf[13] = "           ";
char Customize_Buf[13] = "           ";
char gUICarNo_StrBuf[13] = {""};
char gUICustomize_StrBuf[13] = {""};
char g_GPSstamp_buffer[128] = {0};
#if (MACHINE_TYPE==MACHINE_TYPE_DS315P)
char gUICustomer_Model[20] = {"PERNIS DS315WG"};
#else
char gUICustomer_Model[20] = {"PERNIS S2P"};
#endif
char gUICustomer_Null[20] = {"  "};
char gUICustomer_StrBuf[20] = {"  "};
AlgoEventData adas_eventData_app = {0};
AlgoEventData rcw_eventData_app = {0};
VControl UIFlowWndWrnMsgCtrl = {0};
VControl UIFlowWndWiFiMovieCtrl = {0};
VControl UIFlowWndMovie_Panel_Normal_DisplayCtrl = {0};
VControl UIFlowWndMovie_ADAS_Alert_DisplayCtrl = {0};
VControl UIMenuWndWiFiMobileLinkOKCtrl = {0};

void FlowMovie_BaseDaySet(int year, int month, int day)
{
	g_uiCompatBaseDay = (year * 10000U) + (month * 100U) + day;
	(void)g_uiCompatBaseDay;
}

UINT32 FlowWiFiMovie_GetRecCurrTime(void)
{
	return g_wifi_movie_rec_curr_time;
}

void FlowWiFiMovie_SetRecCurrTime(UINT32 RecCurrTime)
{
	g_wifi_movie_rec_curr_time = RecCurrTime;
}

BOOL FlowMovie_IsEthCamConnectOK(void)
{
	return FALSE;
}

void FlowWiFiMovie_UpdateIcons(BOOL bShow)
{
	(void)bShow;
}

void FlowWiFiMovie_IconDrawTimelapse(BOOL bShow)
{
	(void)bShow;
}

void FlowWiFiMovie_IconDrawMotionDet(BOOL bShow)
{
	(void)bShow;
}

void FlowWiFiMovie_IconDrawAudio(BOOL bShow)
{
	(void)bShow;
}

void FlowMovie_USBRemovePowerOff(void)
{
#if (WIFI_FUNC == ENABLE)
	if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) {
		if (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD) {
			FlowWiFiMovie_StopRec();
			Delay_DelayMs(100);
		}
		return;
	}
#endif

	switch (gMovData.State) {
	case MOV_ST_REC:
	case MOV_ST_REC | MOV_ST_ZOOM:
		FlowMovie_StopRec();
		Delay_DelayMs(20);
		break;
	default:
		break;
	}
}

void FlowMovie_SetLedFlash_BeepWrn(BOOL std)
{
	g_NotRecordWrn = std;
}

void UIFlowWndWiFiMovie_StopTimer(void)
{
}

BOOL FlowMovie_IsStorageErr(BOOL IsCheckFull)
{
	return FlowMovie_IsStorageErr2(NULL, IsCheckFull);
}

UINT32 UIMenuWndPlayFileType_GetFileType(void)
{
	return 0;
}

INT32 UIFlowWndWiFiMovie_OnCustom2(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	(void)pCtrl;
	(void)paramNum;
	(void)paramArray;

#if (WIFI_FUNC == ENABLE)
	WifiApp_SendCmd(WIFIAPP_CMD_NOTIFY_STATUS, WIFIAPP_RET_DISCONNECT);
	FlowMovie_WakeUpLCDBacklight();

	if (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD) {
		if (FlowWiFiMovie_GetRecCurrTime() <= 1) {
			Delay_DelayMs(1000);
		}
		FlowWiFiMovie_StopRec();
		Delay_DelayMs(300);
	}

	bWndWiFiMovieOpenFirst = FALSE;

	if (System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_MOVIE) {
		Ux_PostEvent(NVTEVT_SYSTEM_MODE, 2, System_GetState(SYS_STATE_CURRMODE), SYS_SUBMODE_NORMAL);
	} else {
		UI_SetData(FL_PreMode, UI_GetData(FL_ModeIndex));
		UI_SetData(FL_NextMode, PRIMARY_MODE_MOVIE);
		Ux_PostEvent(NVTEVT_SYSTEM_MODE, 2, PRIMARY_MODE_MOVIE, SYS_SUBMODE_NORMAL);
	}

	Ux_PostEvent(NVTEVT_EXE_WIFI_STOP, 0);
#endif

	return NVTEVT_CONSUME;
}
