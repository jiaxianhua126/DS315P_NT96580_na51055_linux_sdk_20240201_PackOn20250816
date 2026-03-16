#include "PrjInc.h"
#include "UIApp/Network/UIAppWiFiCmdMovie.h"
#include "UIFlowLVGL/UIFlowMovie/UIFlowMovieFuncs.h"
#include "algo_manager.h"

BOOL ParkingM_PreRecord_EMR = FALSE;
BOOL WifiStarting = FALSE;
BOOL bWiFiModeChanged = FALSE;
BOOL g_NotRecordWrn = FALSE;
BOOL g_uiWiFiRecordIngMotionDet = FALSE;
BOOL g_uiWiFiParkingModeMotionDet = FALSE;
BOOL bWiFiRec_AutoStart = FALSE;
BOOL bWiFiRec_AutoStop = FALSE;
BOOL autoWifi = FALSE;
BOOL WifiMotionLed_EN = FALSE;
BOOL g_bWiFiMovieHDR_changed = FALSE;
AlgoEventData adas_eventData_app = {0};
AlgoEventData rcw_eventData_app = {0};
static BOOL sSOSStatusNow = FALSE;

void FlowMovie_BaseDaySet(int year, int month, int day)
{
    UI_SetData(FL_FORMAT_WARNING_DATE, year * 10000 + month * 100 + day);
}

BOOL FlowMovie_WakeUpLCDBacklight(void)
{
    if (GPIOMap_IsLCDBacklightOn() == FALSE) {
        GPIOMap_TurnOnLCDBacklight();
        return TRUE;
    }

    return FALSE;
}

BOOL FlowMovie_IsEthCamConnectOK(void)
{
#if (defined(_NVT_ETHREARCAM_RX_))
    UINT32 i;
    BOOL ret = FALSE;

    for (i = 0; (i < ETH_REARCAM_CAPS_COUNT); i++) {
        if (socketCliEthData1_IsRecv(ETHCAM_PATH_ID_1 + i) &&
            EthCamNet_GetEthLinkStatus(ETHCAM_PATH_ID_1 + i) == ETHCAM_LINK_UP) {
            ret = TRUE;
        }
    }

    return ret;
#else
    return FALSE;
#endif
}

void FlowMovie_SetSOSStatusNow(BOOL En)
{
    sSOSStatusNow = En;
}

BOOL FlowMovie_GetSOSStatusNow(void)
{
    return sSOSStatusNow;
}

void FlowMovie_SetLedFlash_BeepWrn(BOOL std)
{
    (void)std;
}

UINT32 FlowWiFiMovie_GetRecCurrTime(void)
{
    return FlowMovie_GetRecCurrTime();
}

void FlowWiFiMovie_SetRecCurrTime(UINT32 time)
{
    FlowMovie_SetRecCurrTime(time);
}

void FlowWiFiMovie_UpdateIcons(BOOL force)
{
    (void)force;
}

void FlowWiFiMovie_IconDrawTimelapse(BOOL show)
{
    (void)show;
}

void FlowWiFiMovie_IconDrawMotionDet(BOOL show)
{
    (void)show;
}

void FlowWiFiMovie_IconDrawAudio(BOOL show)
{
    (void)show;
}

void FlowMovie_USBRemovePowerOff(void)
{
    if ((System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) &&
        (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD)) {
        FlowWiFiMovie_StopRec();
        Delay_DelayMs(100);
        return;
    }

    FlowMovie_StopRec();
    Delay_DelayMs(100);
}

INT32 UIFlowWndWiFiMovie_OnCustom2(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
    (void)pCtrl;
    (void)paramNum;
    (void)paramArray;
    return NVTEVT_CONSUME;
}

void UIFlowWndWiFiMovie_StopTimer(void)
{
}

UINT32 UIMenuWndPlayFileType_GetFileType(void)
{
    return 0;
}
