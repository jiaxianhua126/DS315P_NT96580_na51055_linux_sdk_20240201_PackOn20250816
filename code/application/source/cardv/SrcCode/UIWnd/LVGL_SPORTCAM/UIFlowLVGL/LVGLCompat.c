#include "PrjInc.h"
#include "UIApp/Network/UIAppWiFiCmdMovie.h"
#include "UIApp/Network/UIAppNetwork.h"
#include "UIFlowLVGL/UIFlowLVGL.h"
#include "UIFlowLVGL/UIFlowMovie/UIFlowMovie.h"
#include "UIFlowLVGL/UIFlowMovie/UIFlowMovieFuncs.h"
#include "UIFlowLVGL/UIFlowWifiLink/UIFlowWifiLink.h"
#include "UIFlowLVGL/UIFlowWifiLinkOK/UIFlowWifiLinkOK.h"
#include "algo_manager.h"

extern INT8 GetGPSSignalStatus(void);

BOOL ParkingM_PreRecord_EMR = FALSE;
BOOL WifiStarting = FALSE;
BOOL bWiFiConnected = FALSE;
BOOL bWndWiFiMovieOpenFirst = FALSE;
BOOL bWiFiModeChanged = FALSE;
BOOL g_NotRecordWrn = FALSE;
BOOL g_uiWiFiRecordIngMotionDet = FALSE;
BOOL g_uiWiFiParkingModeMotionDet = FALSE;
BOOL bWiFiRec_AutoStart = FALSE;
BOOL bWiFiRec_AutoStop = FALSE;
BOOL WiFiManualSetSOS = FALSE;
BOOL autoWifi = FALSE;
BOOL WifiMotionLed_EN = FALSE;
BOOL g_bWiFiMovieHDR_changed = FALSE;
BOOL g_WiFiAutoRec = FALSE;
AlgoEventData adas_eventData_app = {0};
AlgoEventData rcw_eventData_app = {0};
static BOOL sSOSStatusNow = FALSE;

extern void UIFlowMovie_update_icons(void);

static void LVGLCompat_UpdateWiFiOverlay(void)
{
    static char ssid_buf[32];
    static char key_buf[32];
    const BOOL connected = (UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK) || bWiFiConnected;

    if (connected) {
        snprintf(ssid_buf, sizeof(ssid_buf), "%s", UINet_GetConnectedMAC());
        if (label_mac_scr_uiflowwifilinkok != NULL) {
            lv_label_set_text_static(label_mac_scr_uiflowwifilinkok, ssid_buf);
        }

        lv_plugin_scr_close(UIFlowWifiLink, NULL);
        if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) {
            lv_plugin_scr_open(UIFlowWifiLinkOK, NULL);
        }
        return;
    }

    snprintf(ssid_buf, sizeof(ssid_buf), "%s", UINet_GetSSID());
    snprintf(key_buf, sizeof(key_buf), "%s", UINet_GetPASSPHRASE());

    if (label_ssid_scr_uiflowwifilink != NULL) {
        lv_label_set_text_static(label_ssid_scr_uiflowwifilink, ssid_buf);
    }
    if (label_pwa2_scr_uiflowwifilink != NULL) {
        lv_label_set_text_static(label_pwa2_scr_uiflowwifilink, key_buf);
    }

    lv_plugin_scr_close(UIFlowWifiLinkOK, NULL);
    if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) {
        lv_plugin_scr_open(UIFlowWifiLink, NULL);
    }
}

static void LVGLCompat_UpdateAudioIcon(BOOL show)
{
    if (image_audio_scr_uiflowmovie == NULL) {
        return;
    }

    if (!show) {
        lv_obj_set_hidden(image_audio_scr_uiflowmovie, true);
        return;
    }

    lv_img_set_src(image_audio_scr_uiflowmovie,
                   (UI_GetData(FL_MOVIE_AUDIO) == MOVIE_AUDIO_ON) ? &icon_sound_rec_on : &icon_sound_rec_off);
    lv_obj_set_hidden(image_audio_scr_uiflowmovie, false);
}

static void LVGLCompat_UpdateTimelapseIcon(BOOL show)
{
    if (image_timelapse_scr_uiflowmovie == NULL) {
        return;
    }

    if (!show || !isACCTrigParkMode) {
        lv_obj_set_hidden(image_timelapse_scr_uiflowmovie, true);
        return;
    }

    switch (UI_GetData(FL_PARKING_MODE)) {
    case PARKING_MODE_MOTION_DET:
        lv_img_set_src(image_timelapse_scr_uiflowmovie, &icon_motion_det_on);
        lv_obj_set_hidden(image_timelapse_scr_uiflowmovie, false);
        break;

    case PARKING_MODE_ON_1FPS:
    case PARKING_MODE_ON_2FPS:
    case PARKING_MODE_ON_3FPS:
    case PARKING_MODE_ON_5FPS:
    case PARKING_MODE_ON_10FPS:
        lv_img_set_src(image_timelapse_scr_uiflowmovie, &icon_time_lapse_on);
        lv_obj_set_hidden(image_timelapse_scr_uiflowmovie, false);
        break;

    case PARKING_MODE_LOW_BITRATE:
        lv_img_set_src(image_timelapse_scr_uiflowmovie, &icon_time_lapse_off);
        lv_obj_set_hidden(image_timelapse_scr_uiflowmovie, false);
        break;

    case PARKING_MODE_OFF:
    default:
        lv_obj_set_hidden(image_timelapse_scr_uiflowmovie, true);
        break;
    }
}

static void LVGLCompat_UpdateGPSIcon(BOOL show)
{
    INT8 gps_status;

    if (image_gps_scr_uiflowmovie == NULL) {
        return;
    }

    if (!show || (UI_GetData(FL_GPS) == GPS_OFF)) {
        lv_obj_set_hidden(image_gps_scr_uiflowmovie, true);
        return;
    }

    gps_status = GetGPSSignalStatus();
    lv_img_set_src(image_gps_scr_uiflowmovie, (gps_status > 0) ? &icon_gps_on : &icon_gps_off);
    lv_obj_set_hidden(image_gps_scr_uiflowmovie, false);
}

static void LVGLCompat_UpdateSOSIcon(BOOL show)
{
    if (image_sos_scr_uiflowmovie == NULL) {
        return;
    }

    if (!show) {
        lv_obj_set_hidden(image_sos_scr_uiflowmovie, true);
        FlowMovie_SetSOSStatusNow(FALSE);
        return;
    }

    lv_img_set_src(image_sos_scr_uiflowmovie,
                   (GetGPSSignalStatus() < 0) ? &icon_urgent_protect_auto : &icon_urgent_protect_manual);
    lv_obj_set_hidden(image_sos_scr_uiflowmovie, false);
}

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
    UIFlowMovie_update_icons();
    LVGLCompat_UpdateSOSIcon(FlowMovie_GetSOSStatusNow());
    LVGLCompat_UpdateAudioIcon(TRUE);
    LVGLCompat_UpdateTimelapseIcon(TRUE);
    LVGLCompat_UpdateGPSIcon(TRUE);
    LVGLCompat_UpdateWiFiOverlay();
}

void FlowWiFiMovie_IconDrawMaxRecTime(BOOL show)
{
    if (label_maxtime_scr_uiflowmovie == NULL || label_rec_time_scr_uiflowmovie == NULL) {
        return;
    }

    if (!show || (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD)) {
        lv_obj_set_hidden(label_maxtime_scr_uiflowmovie, true);
        return;
    }

    UIFlowMovie_update_icons();
    lv_obj_set_hidden(label_rec_time_scr_uiflowmovie, true);
    lv_obj_set_hidden(label_maxtime_scr_uiflowmovie, false);
}

void FlowWiFiMovie_IconDrawRecTime(BOOL show)
{
    if (label_maxtime_scr_uiflowmovie == NULL || label_rec_time_scr_uiflowmovie == NULL) {
        return;
    }

    if (!show) {
        lv_obj_set_hidden(label_rec_time_scr_uiflowmovie, true);
        return;
    }

    UIFlowMovie_update_icons();
    lv_obj_set_hidden(label_maxtime_scr_uiflowmovie, true);
    lv_obj_set_hidden(label_rec_time_scr_uiflowmovie, false);
}

void FlowWiFiMovie_IconDrawDateTime(BOOL show)
{
    if ((label_date_scr_uiflowmovie == NULL) || (label_time_scr_uiflowmovie == NULL)) {
        return;
    }

    if (show) {
        UIFlowMovie_update_icons();
    }

    lv_obj_set_hidden(label_date_scr_uiflowmovie, !show);
    lv_obj_set_hidden(label_time_scr_uiflowmovie, !show);
}

void FlowWiFiMovie_IconDrawRec(BOOL show)
{
    if (image_rec_ellipse_scr_uiflowmovie == NULL) {
        return;
    }

    if (show) {
        UIFlowMovie_update_icons();
    } else {
        lv_obj_set_hidden(image_rec_ellipse_scr_uiflowmovie, true);
    }
}

void FlowWiFiMovie_IconDrawTimelapse(BOOL show)
{
    LVGLCompat_UpdateTimelapseIcon(show);
}

void FlowWiFiMovie_IconDrawMotionDet(BOOL show)
{
    if (image_motiondetect_scr_uiflowmovie != NULL) {
        lv_obj_set_hidden(image_motiondetect_scr_uiflowmovie, !show);
    }
}

void FlowWiFiMovie_DrawPIM(BOOL show)
{
    if (image_pim_scr_uiflowmovie != NULL) {
        lv_obj_set_hidden(image_pim_scr_uiflowmovie, !show);
    }
}

void FlowWiFiMovie_IconDrawAudio(BOOL show)
{
    LVGLCompat_UpdateAudioIcon(show);
}

void FlowWiFiMovie_IconDrawSOS(BOOL show)
{
    if (show) {
        FlowMovie_SetSOSStatusNow(TRUE);
    }
    LVGLCompat_UpdateSOSIcon(show);
}

void FlowWiFiMovie_IconDrawGPSSignal(BOOL show)
{
    LVGLCompat_UpdateGPSIcon(show);
    LVGLCompat_UpdateSOSIcon(FlowMovie_GetSOSStatusNow());
}

void FlowWiFiMovie_IconDrawWiFiConnected(BOOL show)
{
    bWiFiConnected = show;
    UIFlowMovie_update_icons();
    LVGLCompat_UpdateWiFiOverlay();
}

void FlowWiFiMovie_IconDrawWiFiDisConnected(BOOL show)
{
    (void)show;
    bWiFiConnected = FALSE;
    UIFlowMovie_update_icons();
    LVGLCompat_UpdateWiFiOverlay();
}

void UIFlowWndWiFiMovie_UpdateWiFiData(BOOL bShow)
{
    if (!bShow && (System_GetState(SYS_STATE_CURRSUBMODE) != SYS_SUBMODE_WIFI)) {
        lv_plugin_scr_close(UIFlowWifiLink, NULL);
        lv_plugin_scr_close(UIFlowWifiLinkOK, NULL);
        return;
    }

    LVGLCompat_UpdateWiFiOverlay();
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
