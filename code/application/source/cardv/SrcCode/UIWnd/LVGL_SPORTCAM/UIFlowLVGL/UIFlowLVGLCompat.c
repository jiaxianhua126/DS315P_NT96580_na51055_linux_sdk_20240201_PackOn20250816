#include "PrjInc.h"

#define __MODULE__          UIFlowLVGLCompat
#define __DBGLVL__          2
#define __DBGFLT__          "*"
#include <kwrap/debug.h>

BOOL ParkingM_PreRecord_EMR = FALSE;
BOOL g_NotRecordWrn = FALSE;
BOOL bWndWiFiMovieOpenFirst = FALSE;
BOOL bWiFiModeChanged = FALSE;
BOOL WifiStarting = FALSE;
BOOL g_uiWiFiRecordIngMotionDet = FALSE;
BOOL g_uiWiFiParkingModeMotionDet = FALSE;
BOOL bWiFiRec_AutoStart = FALSE;
BOOL bWiFiRec_AutoStop = FALSE;
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
VControl UIFlowWndWrnMsgCtrl = {0};
VControl UIFlowWndWiFiMovieCtrl = {0};
VControl UIMenuWndWiFiMobileLinkOKCtrl = {0};

static UINT32 g_wifi_movie_rec_curr_time = 0;
static BOOL g_movie_sos_status_now = FALSE;

void FlowMovie_BaseDaySet(int year, int month, int day)
{
	UINT32 base_day = year * 10000 + month * 100 + day;

	UI_SetData(FL_FORMAT_WARNING_DATE, base_day);
}

BOOL FlowMovie_WakeUpLCDBacklight(void)
{
	GPIOMap_TurnOnLCDBacklight();
	return FALSE;
}

UINT32 FlowWiFiMovie_GetRecCurrTime(void)
{
	return g_wifi_movie_rec_curr_time;
}

void FlowWiFiMovie_SetRecCurrTime(UINT32 RecCurrTime)
{
	g_wifi_movie_rec_curr_time = RecCurrTime;
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

void FlowMovie_SetSOSStatusNow(BOOL En)
{
	g_movie_sos_status_now = En;
}

BOOL FlowMovie_GetSOSStatusNow(void)
{
	return g_movie_sos_status_now;
}

UINT32 Get_ParkingModeTimeLapseValue(UINT32 uiIndex)
{
	switch (uiIndex) {
	case PARKING_MODE_TIMELAPSEREC_66MS:
		return 66;
	case PARKING_MODE_TIMELAPSEREC_100MS:
		return 100;
	case PARKING_MODE_TIMELAPSEREC_200MS:
		return 200;
	case PARKING_MODE_TIMELAPSEREC_333MS:
		return 333;
	case PARKING_MODE_TIMELAPSEREC_500MS:
		return 500;
	case PARKING_MODE_TIMELAPSEREC_1SEC:
	default:
		return 1000;
	}
}

BOOL FlowMovie_IsEthCamConnectOK(void)
{
#if defined(_NVT_ETHREARCAM_RX_)
	UINT32 i;

	for (i = 0; i < ETH_REARCAM_CAPS_COUNT; i++) {
		if (socketCliEthData1_IsRecv(ETHCAM_PATH_ID_1 + i) &&
			EthCamNet_GetEthLinkStatus(ETHCAM_PATH_ID_1 + i) == ETHCAM_LINK_UP) {
			return TRUE;
		}
	}
#endif
	return FALSE;
}

void FlowMovie_SetLedFlash_BeepWrn(BOOL std)
{
	g_NotRecordWrn = std;
}

void FlowMovie_USBRemovePowerOff(void)
{
	switch (FlowMovie_GetMovDataState()) {
	case MOV_ST_REC:
	case MOV_ST_REC | MOV_ST_ZOOM:
		FlowMovie_StopRec();
		Delay_DelayMs(100);
		break;
	default:
		break;
	}
}

INT32 UIFlowWndWiFiMovie_OnCustom2(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	(void)pCtrl;
	(void)paramNum;
	(void)paramArray;

	bWndWiFiMovieOpenFirst = FALSE;

	if (FlowMovie_GetMovDataState() == MOV_ST_REC ||
		FlowMovie_GetMovDataState() == (MOV_ST_REC | MOV_ST_ZOOM)) {
		FlowMovie_StopRec();
		Delay_DelayMs(100);
	}

	Ux_PostEvent(NVTEVT_EXE_WIFI_STOP, 0);
	return NVTEVT_CONSUME;
}

void UIVoice_Play(UINT32 index)
{
	(void)index;
	UISound_Play(DEMOSOUND_SOUND_KEY_TONE);
}
