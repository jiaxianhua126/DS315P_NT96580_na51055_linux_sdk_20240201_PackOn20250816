
#include "PrjInc.h"
#include "UIApp/Photo/UIAppPhoto.h"
#include "GxTime.h"
#include "GxStrg.h"
#include "comm/hwclock.h"
#include "UIApp/Network/UIAppWiFiCmd.h"

//#include "PhotoTsk.h"
//#include "DxGPS.h"
#if (defined(_NVT_ETHREARCAM_RX_))
#include "UIApp/Network/EthCamAppCmd.h"
#include "UIApp/Network/EthCamAppNetwork.h"
#endif
#include "DxInput.h"
static UINT32  g_MovRecMaxTime = 0;
static UINT32  g_MovRecCurrTime = 0;
static CHAR    g_RecMaxTimeStr[20] = {0};
static UINT32  g_RecMaxTime = 0;
static CHAR    g_RecCurrTimeStr[20] = {0};
static UINT32  g_RecCurrTime = 0;
static CHAR    date_str[20] = {0};
static CHAR    time_str[20] = {0};

//MOVIE_SIZE_TAG
#if (!defined(COUNTRY_JP))	
static CHAR    *resolution_Buf[MOVIE_SIZE_ID_MAX] = {
	[MOVIE_SIZE_FRONT_3840x2160P30] = "4KP30",	
	[MOVIE_SIZE_FRONT_2560x1440P60] = "1440P60",
	[MOVIE_SIZE_FRONT_2560x1440P30] = "1440P30",
	[MOVIE_SIZE_FRONT_2304x1296P60] = "1296P60",
	[MOVIE_SIZE_FRONT_2304x1296P30] = "1296P30",
	[MOVIE_SIZE_FRONT_1920x1080P60] = "1080P60",
	[MOVIE_SIZE_FRONT_1920x1080P30] = "1080P30",	
	[MOVIE_SIZE_DUAL_3840x2160P30_1920x1080P30] = "4K+1K",
	[MOVIE_SIZE_DUAL_2560x1440P30_1920x1080P30] = "2K+1K",	
	[MOVIE_SIZE_DUAL_1920x1080P30_1920x1080P30] = "1K+1K",
	#if 0
	[MOVIE_SIZE_FRONT_1280x720P120] = "HD P120",
	[MOVIE_SIZE_FRONT_1280x720P240] = "HD P240",
	[MOVIE_SIZE_FRONT_1280x720P60] = "HD P60",
	[MOVIE_SIZE_FRONT_1280x720P30] = "HD P30",
	[MOVIE_SIZE_FRONT_848x480P30] = "WVGA P30",
	[MOVIE_SIZE_FRONT_640x480P240] = "VGA P240",
	[MOVIE_SIZE_FRONT_640x480P30] = "VGA P30",
	[MOVIE_SIZE_FRONT_320x240P30] = "QVGA P30",
	[MOVIE_SIZE_DUAL_2560x1440P30_1280x720P30] = "QHD P30+HD P30",
	[MOVIE_SIZE_DUAL_2304x1296P30_1280x720P30] = "3MHD P30+HD P30",
	[MOVIE_SIZE_DUAL_1920x1080P30_1920x1080P30] = "FHD P30+FHD P30",
	[MOVIE_SIZE_DUAL_1920x1080P30_1280x720P30] = "FHD P30+HD P30",
	[MOVIE_SIZE_DUAL_1920x1080P30_848x480P30] = "FHD P30+WVGA P30",
	[MOVIE_SIZE_TRI_1920x1080P30] = "3 x FHD P30",
	[MOVIE_SIZE_TRI_2560x1440P30_1920x1080P30_1920x1080P30] = "QHD P30+3 x FHD P30",
	[MOVIE_SIZE_QUAD_1920x1080P30] = "4 x FHD P30",
	[MOVIE_SIZE_CLONE_1920x1080P30_1920x1080P30] = "FHD P30+FHD P30",
	[MOVIE_SIZE_CLONE_1920x1080P30_1280x720P30] = "FHD P30+HD P30",
	[MOVIE_SIZE_CLONE_2560x1440P30_848x480P30] = "QHD P30+WVGA P30",
	[MOVIE_SIZE_CLONE_2304x1296P30_848x480P30] = "3MHD P30+WVGA P30",
	[MOVIE_SIZE_CLONE_1920x1080P60_848x480P30] = "FHD P60+WVGA P30",
	[MOVIE_SIZE_CLONE_1920x1080P60_640x360P30] = "FHD P60+VGA P30",
	[MOVIE_SIZE_CLONE_1920x1080P30_848x480P30] = "FHD P30+WVGA P30",
	[MOVIE_SIZE_CLONE_2048x2048P30_480x480P30] = "2048x2048 P30 + 480x480 P30",
	
	[MOVIE_SIZE_FRONT_2880x2160P50] = "UHD P50",
	[MOVIE_SIZE_FRONT_2880x2160P24] = "UHD P24",
	[MOVIE_SIZE_FRONT_2704x2032P60] = "2.7K P60",
	[MOVIE_SIZE_FRONT_2560x1440P80] = "QHD P80",
	[MOVIE_SIZE_FRONT_1920x1080P120] = "FHD P120",
	[MOVIE_SIZE_FRONT_1920x1080P96] = "FHD P96",
	#endif
};
#else
static CHAR    *resolution_Buf[MOVIE_SIZE_ID_MAX] = {
	[MOVIE_SIZE_FRONT_3840x2160P30] = "4KP27.5",	
	[MOVIE_SIZE_FRONT_2560x1440P60] = "1440P55",
	[MOVIE_SIZE_FRONT_2560x1440P30] = "1440P27.5",
	[MOVIE_SIZE_FRONT_2304x1296P60] = "1296P55",
	[MOVIE_SIZE_FRONT_2304x1296P30] = "1296P27.5",
	[MOVIE_SIZE_FRONT_1920x1080P60] = "1080P55",
	[MOVIE_SIZE_FRONT_1920x1080P30] = "1080P27.5",	
	[MOVIE_SIZE_DUAL_3840x2160P30_1920x1080P30] = "2160P27.5+1080P27.5",
	[MOVIE_SIZE_DUAL_2560x1440P30_1920x1080P30] = "1440P27.5+1080P27.5",	
	[MOVIE_SIZE_DUAL_1920x1080P30_1920x1080P30] = "1080P27.5+1080P27.5",
	#if 0
	[MOVIE_SIZE_FRONT_1280x720P120] = "HD P110",
	[MOVIE_SIZE_FRONT_1280x720P240] = "HD P220",
	[MOVIE_SIZE_FRONT_1280x720P60] = "HD P55",
	[MOVIE_SIZE_FRONT_1280x720P30] = "HD P27.5",
	[MOVIE_SIZE_FRONT_848x480P30] = "WVGA P27.5",
	[MOVIE_SIZE_FRONT_640x480P240] = "VGA P220",
	[MOVIE_SIZE_FRONT_640x480P30] = "VGA P27.5",
	[MOVIE_SIZE_FRONT_320x240P30] = "QVGA P27.5",
	[MOVIE_SIZE_DUAL_2560x1440P30_1280x720P30] = "QHD P30+HD P30",
	[MOVIE_SIZE_DUAL_2304x1296P30_1280x720P30] = "3MHD P30+HD P30",
	[MOVIE_SIZE_DUAL_1920x1080P30_1920x1080P30] = "FHD P30+FHD P30",
	[MOVIE_SIZE_DUAL_1920x1080P30_1280x720P30] = "FHD P30+HD P30",
	[MOVIE_SIZE_DUAL_1920x1080P30_848x480P30] = "FHD P30+WVGA P30",
	[MOVIE_SIZE_TRI_1920x1080P30] = "3 x FHD P30",
	[MOVIE_SIZE_TRI_2560x1440P30_1920x1080P30_1920x1080P30] = "QHD P30+3 x FHD P30",
	[MOVIE_SIZE_QUAD_1920x1080P30] = "4 x FHD P30",
	[MOVIE_SIZE_CLONE_1920x1080P30_1920x1080P30] = "FHD P30+FHD P30",
	[MOVIE_SIZE_CLONE_1920x1080P30_1280x720P30] = "FHD P30+HD P30",
	[MOVIE_SIZE_CLONE_2560x1440P30_848x480P30] = "QHD P30+WVGA P30",
	[MOVIE_SIZE_CLONE_2304x1296P30_848x480P30] = "3MHD P30+WVGA P30",
	[MOVIE_SIZE_CLONE_1920x1080P60_848x480P30] = "FHD P60+WVGA P30",
	[MOVIE_SIZE_CLONE_1920x1080P60_640x360P30] = "FHD P60+VGA P30",
	[MOVIE_SIZE_CLONE_1920x1080P30_848x480P30] = "FHD P30+WVGA P30",
	[MOVIE_SIZE_CLONE_2048x2048P30_480x480P30] = "2048x2048 P30 + 480x480 P30",
	
	[MOVIE_SIZE_FRONT_2880x2160P50] = "UHD P50",
	[MOVIE_SIZE_FRONT_2880x2160P24] = "UHD P24",
	[MOVIE_SIZE_FRONT_2704x2032P60] = "2.7K P55",
	[MOVIE_SIZE_FRONT_2560x1440P80] = "QHD P80",
	[MOVIE_SIZE_FRONT_1920x1080P120] = "FHD P110",
	[MOVIE_SIZE_FRONT_1920x1080P96] = "FHD P96",
	#endif
};

#endif
void FlowWiFiMovie_SetRecMaxTime(UINT32 RecMaxTime)
{
    g_MovRecMaxTime = RecMaxTime;
}

UINT32 FlowWiFiMovie_GetRecMaxTime(void)
{
    return g_MovRecMaxTime;
}

void FlowWiFiMovie_SetRecCurrTime(UINT32 RecCurrTime)
{
    g_MovRecCurrTime = RecCurrTime;
}

UINT32 FlowWiFiMovie_GetRecCurrTime(void)
{
    return g_MovRecCurrTime;
}

void FlowWiFiMovie_IconDrawDscMode(BOOL bShow)
{
    //UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_cameraCtrl, bShow);
}

void FlowWiFiMovie_IconDrawSize(BOOL bShow)
{
    VControl *pCtrl = &UIFlowWndWiFiMovie_Static_resolutionCtrl;

    if (bShow == FALSE)
    {
        UxCtrl_SetShow(pCtrl, FALSE);
        return;
    }

    UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer(resolution_Buf[SysGetFlag(FL_MOVIE_SIZE)]));

#if (defined(_NVT_ETHREARCAM_RX_))
	#if (!defined(COUNTRY_JP))	
    if (GPIOMap_EthCam1Det()) {
        switch (SysGetFlag(FL_MOVIE_SIZE)) {
/*			
        case MOVIE_SIZE_FRONT_3840x2160P30:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("4KP30+1440P30"));
            break;
        case MOVIE_SIZE_FRONT_2560x1600P30:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1600P30+1440P30"));
            break;
*/            
        case MOVIE_SIZE_FRONT_2560x1440P60:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P60+1440P30"));
            break;
        case MOVIE_SIZE_FRONT_2560x1440P30:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P30+1440P30"));
            break;
/*		
		case MOVIE_SIZE_FRONT_2560x1080P60:
			UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P60 21:9+1440P30"));
			break;
		case MOVIE_SIZE_FRONT_2560x1080P30:
			UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P30 21:9+1440P30"));
			break;*/
		case MOVIE_SIZE_FRONT_2304x1296P60:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1296P60+1440P30"));
            break;
        case MOVIE_SIZE_FRONT_2304x1296P30:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1296P30+1440P30"));
            break;
        case MOVIE_SIZE_FRONT_1920x1080P60:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1080P60+1440P30"));
            break;

        case MOVIE_SIZE_FRONT_1920x1080P30:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1080P30+1440P30"));
            break;

//        case MOVIE_SIZE_FRONT_1280x720P120:
//            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P120+1440P30"));
//            break;
//        case MOVIE_SIZE_FRONT_1280x720P60:
//            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P60+1440P30"));
//            break;
//        case MOVIE_SIZE_FRONT_1280x720P30:
 //          UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P30+1440P30"));
//           break;
        default:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P30+1440P30"));
            break;            
        }
    }
	#else
	if (GPIOMap_EthCam1Det()) {
        switch (SysGetFlag(FL_MOVIE_SIZE)) {
/*			
        case MOVIE_SIZE_FRONT_3840x2160P30:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("4KP27.5+1080P27.5"));
            break;
        case MOVIE_SIZE_FRONT_2560x1600P30:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1600P27.5+1080P27.5"));
            break;
*/            
        case MOVIE_SIZE_FRONT_2560x1440P60:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P55+1080P27.5"));
            break;
        case MOVIE_SIZE_FRONT_2560x1440P30:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P27.5+1080P27.5"));
            break;
/*		
		case MOVIE_SIZE_FRONT_2560x1080P60:
			UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P55 21:9+1080P27.5"));
			break;
		case MOVIE_SIZE_FRONT_2560x1080P30:
			UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P27.5 21:9+1080P27.5"));
			break;*/
		case MOVIE_SIZE_FRONT_2304x1296P60:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1296P55+1080P27.5"));
            break;
        case MOVIE_SIZE_FRONT_2304x1296P30:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1296P27.5+1080P27.5"));
            break;
        case MOVIE_SIZE_FRONT_1920x1080P60:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1080P55+1080P27.5"));
            break;

        case MOVIE_SIZE_FRONT_1920x1080P30:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1080P27.5+1080P27.5"));
            break;

//        case MOVIE_SIZE_FRONT_1280x720P120:
//            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P110+1080P27.5"));
//            break;
//        case MOVIE_SIZE_FRONT_1280x720P60:
//            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P55+1080P27.5"));
//            break;
//        case MOVIE_SIZE_FRONT_1280x720P30:
 //          UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P27.5+1080P27.5"));
//           break;
        default:
            UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P27.5+1080P27.5"));
            break;            
        }
    }
	#endif
#endif

    UxCtrl_SetShow(pCtrl, bShow);
}

void FlowWiFiMovie_DrawRecState(BOOL bShow)
{
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_PanelCtrl, bShow);
}
void FlowWiFiMovie_IconDrawMaxRecTime(BOOL bShow)
{
    if ((bShow == FALSE) || (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD))
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_maxtimeCtrl, FALSE);
        return;
    }

    if (GxStrg_GetDevice(0) == NULL)
    {
        snprintf(g_RecMaxTimeStr, 20, "%02d:%02d:%02d", 0, 0, 0);
        //snprintf(g_RecMaxTimeStr, 20, "%02d:%02d", 0, 0);
        UxStatic_SetData(&UIFlowWndWiFiMovie_Static_maxtimeCtrl, STATIC_VALUE, Txt_Pointer(g_RecMaxTimeStr));
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_maxtimeCtrl, TRUE);
        //No Storage, direct to return.
        return;
    }

    memset((void *)g_RecMaxTimeStr, 0, sizeof(g_RecMaxTimeStr));
    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) // fixed nand error
    {
        g_RecMaxTime = 0;
    }
    else
    {
        g_RecMaxTime = MovieExe_GetFreeRecSec();
    }

    if (g_RecMaxTime <= 3)//2
    {
        FlowWiFiMovie_SetRecMaxTime(0);
        g_RecMaxTime = 0;
    }
    /*else if (g_RecMaxTime > 86399) //modify for 256GB Card
    {   ///23:59:59
        FlowWiFiMovie_SetRecMaxTime(86399);
    }*/
    else
    {
        FlowWiFiMovie_SetRecMaxTime(g_RecMaxTime);
    }

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED)
    {
        snprintf(g_RecMaxTimeStr, 20, "%02d:%02d:%02d", 0, 0, 0);
        //snprintf(g_RecMaxTimeStr, 20, "%02d:%02d", 0, 0);
    }
    else
    {
        snprintf(g_RecMaxTimeStr, 20, "%02d:%02d:%02d", g_RecMaxTime/3600,(g_RecMaxTime%3600)/60, (g_RecMaxTime%3600)%60);
        //snprintf(g_RecMaxTimeStr, 20, "%02d:%02d", g_RecMaxTime/3600,(g_RecMaxTime%3600)/60);
    }
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_timeCtrl, FALSE);
    UxStatic_SetData(&UIFlowWndWiFiMovie_Static_maxtimeCtrl, STATIC_VALUE, Txt_Pointer(g_RecMaxTimeStr));
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_maxtimeCtrl, TRUE);
}

void FlowWiFiMovie_IconDrawRecTime(BOOL bShow)
{
    if (bShow == FALSE)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_timeCtrl, FALSE);
        return;
    }

    switch (WiFiCmd_GetStatus())
    {
    case WIFI_MOV_ST_RECORD:
        g_RecCurrTime = FlowWiFiMovie_GetRecCurrTime();
        memset((void *)g_RecCurrTimeStr, 0, sizeof(g_RecCurrTimeStr));
        snprintf(g_RecCurrTimeStr, 20, "%02d:%02d:%02d", g_RecCurrTime/3600,(g_RecCurrTime%3600)/60, (g_RecCurrTime%3600)%60);
        //snprintf(g_RecCurrTimeStr, 20, "%02d:%02d", (g_RecCurrTime%3600)/60, (g_RecCurrTime%3600)%60);
        UxStatic_SetData(&UIFlowWndWiFiMovie_Static_timeCtrl, STATIC_VALUE, Txt_Pointer(g_RecCurrTimeStr));
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_timeCtrl, TRUE);
        break;
    }
}

void FlowWiFiMovie_IconDrawDateTime(BOOL bShow)
{
    struct tm Curr_DateTime;
    Curr_DateTime = hwclock_get_time(TIME_ID_CURRENT);

    if (bShow == FALSE)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_YMD_StaticCtrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_HMS_StaticCtrl, FALSE);
        return;
    }
    // display Date/Time string in movie mode
    switch (SysGetFlag(FL_DATE_FORMAT))
    {
    case DATE_FORMAT_DMY:
        snprintf(date_str, 20, "%02d/%02d/%04d", Curr_DateTime.tm_mday, Curr_DateTime.tm_mon, Curr_DateTime.tm_year);
        break;

    case DATE_FORMAT_MDY:
        snprintf(date_str, 20, "%02d/%02d/%04d", Curr_DateTime.tm_mon, Curr_DateTime.tm_mday, Curr_DateTime.tm_year);
        break;

    case DATE_FORMAT_YMD:
    default:
        snprintf(date_str, 20, "%04d/%02d/%02d", Curr_DateTime.tm_year, Curr_DateTime.tm_mon, Curr_DateTime.tm_mday);
        break;
    }
	snprintf(time_str, 20, "%02d:%02d:%02d", Curr_DateTime.tm_hour, Curr_DateTime.tm_min, Curr_DateTime.tm_sec);
	
    UxStatic_SetData(&UIFlowWndWiFiMovie_YMD_StaticCtrl, STATIC_VALUE, Txt_Pointer(date_str));
    UxStatic_SetData(&UIFlowWndWiFiMovie_HMS_StaticCtrl, STATIC_VALUE, Txt_Pointer(time_str));
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_YMD_StaticCtrl, TRUE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_HMS_StaticCtrl, TRUE);
}

void FlowWiFiMovie_IconDrawRec(BOOL bShow)
{
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_PanelCtrl, bShow);
}

void FlowWiFiMovie_IconDrawEV(BOOL bShow)
{
#if 0
    if (bShow == FALSE)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_StatusICN_EVCtrl, FALSE);
        return;
    }

    UxState_SetData(&UIFlowWndWiFiMovie_StatusICN_EVCtrl, STATE_CURITEM, SysGetFlag(FL_EV));
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_StatusICN_EVCtrl, TRUE);
#endif
}

void FlowWiFiMovie_IconDrawStorage(BOOL bShow)
{
#if 0
    VControl *pCtrl = &UIFlowWndWiFiMovie_Status_StorageCtrl;

    if (bShow == FALSE)
    {
        UxCtrl_SetShow(pCtrl, FALSE);
        return;
    }

    /* Update status item data */
    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED)
    {
        UxState_SetData(pCtrl,STATE_CURITEM,UIFlowWndWiFiMovie_Status_Storage_ICONID_NULL);
    }
    else if (System_GetState(SYS_STATE_CARD) == CARD_LOCKED)
    {
        UxState_SetData(pCtrl,STATE_CURITEM,UIFlowWndWiFiMovie_Status_Storage_ICON_SD_LOCK);
    }
    else
    {
        UxState_SetData(pCtrl,STATE_CURITEM,UIFlowWndWiFiMovie_Status_Storage_ICON_SD_CARD);
    }
    UxCtrl_SetShow(pCtrl, TRUE);
#endif
}

void FlowWiFiMovie_IconDrawCyclicRec(BOOL bShow)
{
#if 0
    if (bShow == FALSE)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Status_CyclicRecCtrl, FALSE);
        return;
    }

    UxState_SetData(&UIFlowWndWiFiMovie_Status_CyclicRecCtrl, STATE_CURITEM, SysGetFlag(FL_MOVIE_CYCLIC_REC));
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Status_CyclicRecCtrl, TRUE);
#endif
}

void FlowWiFiMovie_IconDrawHDR(BOOL bShow)
{
#if 0
    if (bShow == FALSE)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Status_HDRCtrl, FALSE);
        return;
    }

	UxState_SetData(&UIFlowWndWiFiMovie_Status_HDRCtrl, STATE_CURITEM, SysGetFlag(FL_MOVIE_WDR));//FL_MOVIE_HDR
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_Status_HDRCtrl, TRUE);
#endif
}

void FlowWiFiMovie_IconDrawMotionDet(BOOL bShow)
{
    if (bShow == FALSE)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_MotionDet1Ctrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_MotionDet2Ctrl, FALSE);
        return;
    }

    if (UI_GetData(FL_MOVIE_AUDIO) == MOVIE_AUDIO_ON)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_MotionDet1Ctrl, TRUE);
    }
    else
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_MotionDet2Ctrl, TRUE);
    }
}

void FlowWiFiMovie_IconDrawBattery(BOOL bShow)
{
#if 0
    if (bShow == FALSE)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Status_batteryCtrl, FALSE);
        return;
    }

    UxState_SetData(&UIFlowWndWiFiMovie_Status_batteryCtrl, STATE_CURITEM, GetBatteryLevel());
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Status_batteryCtrl, bShow);
#endif
}

void FlowWiFiMovie_IconDrawDZoom(BOOL bShow)
{
#if 0
    if (bShow == FALSE)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Zoom_StaticCtrl, FALSE);
        return;
    }

    UxStatic_SetData(&UIFlowWndWiFiMovie_Zoom_StaticCtrl, STATIC_VALUE, Txt_Pointer(Get_DZoomRatioString()));
	bShow = (DZOOM_IDX_GET() > DZOOM_IDX_MIN()) ? TRUE : FALSE;
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Zoom_StaticCtrl, bShow);
#endif
}

void FlowWiFiMovie_DrawPIM(BOOL bShow)
{
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_StaticIcon_PIMCtrl, bShow);
}

void FlowWiFiMovie_IconDrawSOS(BOOL bShow)
{
    INT8 gpsstatus;
    gpsstatus = GetGPSSignalStatus();

    if (!bShow)
    {
        FlowMovie_SetSOSStatusNow(FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_SOSCtrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_SOS1Ctrl, FALSE);
    }
    else
    {
        if (gpsstatus < 0)
        {    
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_SOS1Ctrl, TRUE);	
        }
        else
        {
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_SOSCtrl, TRUE);
        }
    }
}

void FlowWiFiMovie_IconDrawAudio(BOOL bShow)
{
    if (bShow == FALSE)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Status_AudioCtrl, FALSE);
        return;
    }
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_Status_AudioCtrl, FALSE);
    if (UI_GetData(FL_MOVIE_AUDIO) == MOVIE_AUDIO_ON)
    {
        UxState_SetData(&UIFlowWndWiFiMovie_Status_AudioCtrl, STATE_CURITEM, SysGetFlag(FL_MOVIE_AUDIO));
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Status_AudioCtrl, TRUE);
		#if 0
        if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_Static_MotionDet2Ctrl))
        {
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_MotionDet2Ctrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_MotionDet1Ctrl, TRUE);
        }
        if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_Static_TimeLapse2Ctrl))
        {
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TimeLapse2Ctrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TimeLapse1Ctrl, TRUE);
        }
		#endif
    } 
    else
    {
        UxState_SetData(&UIFlowWndWiFiMovie_Status_AudioCtrl, STATE_CURITEM, SysGetFlag(FL_MOVIE_AUDIO));
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Status_AudioCtrl, TRUE);
		#if 0
        if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_Static_MotionDet1Ctrl))
        {
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_MotionDet2Ctrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_MotionDet1Ctrl, FALSE);
        }
        if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_Static_TimeLapse1Ctrl))
        {
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TimeLapse2Ctrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TimeLapse1Ctrl, FALSE);
        }
		#endif
    }
}

void FlowWiFiMovie_IconDrawTimelapse(BOOL bShow)
{
	VControl *pCtrl = &UIFlowWndWiFiMovie_Static_TimeLapse1Ctrl;

    if (bShow == FALSE)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TimeLapse1Ctrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TimeLapse2Ctrl, FALSE);
        return;
    }

    if (!isACCTrigParkMode) {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TimeLapse1Ctrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TimeLapse2Ctrl, FALSE);
        return;
    }

    switch (UI_GetData(FL_PARKING_MODE)) {
    case PARKING_MODE_MOTION_DET:
		UxStatic_SetData(pCtrl,STATIC_VALUE,ICON_PARKINGMODE_MD);
        UxCtrl_SetShow(pCtrl, TRUE);
        break;

    case PARKING_MODE_ON_1FPS:
    case PARKING_MODE_ON_2FPS:
    case PARKING_MODE_ON_3FPS:
    case PARKING_MODE_ON_5FPS:
    case PARKING_MODE_ON_10FPS:
		UxStatic_SetData(pCtrl,STATIC_VALUE,ICON_AUTO_1FPS);//ICON_PARKINGMODE_TL
        UxCtrl_SetShow(pCtrl, TRUE);
        break;

    case PARKING_MODE_LOW_BITRATE:
		UxStatic_SetData(pCtrl,STATIC_VALUE,ICON_PARKINGMODE_LB);
        UxCtrl_SetShow(pCtrl, TRUE);
        break;
	/*case PARKING_MODE_GSENSOR_DET:
		UxStatic_SetData(pCtrl,STATIC_VALUE,ICON_PARKINGMODE_GSENSOR);
		UxCtrl_SetShow(pCtrl, TRUE);
		break;
	case PARKING_MODE_MOTION_GSENSOR_DET:
		UxStatic_SetData(pCtrl,STATIC_VALUE,ICON_PARKINGMODE_GSENSOR);
		UxCtrl_SetShow(pCtrl, TRUE);
		break;*///harrison ds315

    default:
    case PARKING_MODE_OFF:
        UxCtrl_SetShow(pCtrl, FALSE);
        break;
    }
	#if 0///harrison ds315
	if((UI_GetData(FL_PARKING_MODE)) == PARKING_MODE_MOTION_GSENSOR_DET)
	{
		UxStatic_SetData(&UIFlowWndWiFiMovie_Static_TimeLapse2Ctrl,STATIC_VALUE,ICON_PARKINGMODE_MD);
		UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TimeLapse2Ctrl, TRUE);
	}
	else
	{		
		UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TimeLapse2Ctrl, FALSE);
	}
	#endif
}

void FlowWiFiMovie_DrawFolderCheck(BOOL bShow)
{
	if(bShow)
	{
		UxState_SetItemData(&UIFlowWndWiFiMovie_FolderCheck_StatusTxtCtrl, UIFlowWndWiFiMovie_FolderCheck_StatusTxt_STRID_FORMAT_WARNING1, STATE_ITEM_STRID, STRID_REAR_ERROR);
	}
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_FolderCheck_StatusTxtCtrl, bShow);
}

void FlowWiFiMovie_DrawCustomerType(BOOL bShow)
{
#if 0
    if (bShow == FALSE)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_CustomTypeCtrl, FALSE);
        return;
    }

    UxStatic_SetData(&UIFlowWndWiFiMovie_CustomTypeCtrl, STATIC_VALUE, Txt_Pointer("AUKEY DR02 P"));
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_CustomTypeCtrl, TRUE);
#endif
}

extern CHAR *Get_GpsSpeedString(void);
extern CHAR Speed1[32];
//static UINT32 g_year = DEF_YEAR;
static UINT32 g_Count = 0;
extern INT8 uitpmsstatus;
extern BOOL GPS_UpdateDateTime;
#if defined(_GPS_EDOG_)
extern BOOL EdogFstCnetd;
//extern BOOL g_GPS_PlaySound_onetime;
#elif defined(_GPS_EDOG_UNIQUE_SKY_)
extern BOOL EdogFstCnetd;
//extern BOOL g_GPS_PlaySound_onetime;
#endif
void FlowWiFiMovie_IconDrawGPSSignal(BOOL bShow)
{
    INT8 gpsstatus = 0;
    RMCINFO RMCInfo;
    //struct tm Curr_DateTime = {0};

    if (bShow == FALSE)
    {
        g_Count = 0;
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCtrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCCtrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCCCtrl, FALSE);
        return;
    }

    if (UI_GetData(FL_GPS) == GPS_OFF)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCtrl,FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCCtrl,FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCCCtrl,FALSE);
    }
    else
    {
        Get_GpsSpeedString();
        gpsstatus = GetGPSSignalStatus();
        if (gpsstatus < 0)
        {
            g_Count = 0;
            //GPS_UpdateDateTime = FALSE;
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCtrl,FALSE);
            //UxStatic_SetData(&UIFlowWndWiFiMovie_GPSSignalCtrl,STATIC_VALUE,Txt_Pointer(Get_GpsSpeedString()));
            UxStatic_SetData(&UIFlowWndWiFiMovie_GPSSignalCtrl,STATIC_VALUE,Txt_Pointer(Speed1));
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCCtrl,FALSE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCCCtrl,FALSE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPS_SMALL_ICON2Ctrl,FALSE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSN_SMALL_ICON2Ctrl,FALSE);
            //UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCtrl,TRUE);
            if(UxCtrl_IsShow(&UIFlowWndWiFiMovie_SOSCtrl))
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_SOS1Ctrl,TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_SOSCtrl,FALSE);
            }
        }
        else
        {
            if (gpsstatus == 1)
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCCCtrl,FALSE);
                UxStatic_SetData(&UIFlowWndWiFiMovie_GPSSignalCCCtrl,STATIC_VALUE,Txt_Pointer(Speed1));
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCtrl,FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCCtrl,FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPS_SMALL_ICON2Ctrl,TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSN_SMALL_ICON2Ctrl,FALSE);
                if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_SOS1Ctrl))
                {
                    UxCtrl_SetShow(&UIFlowWndWiFiMovie_SOS1Ctrl,FALSE);
                    UxCtrl_SetShow(&UIFlowWndWiFiMovie_SOSCtrl,TRUE);
                }
                //UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCCCtrl,TRUE);
                if (TRUE == GPSRec_GetRMCDate(&RMCInfo))
                {
                    if (GPS_UpdateDateTime == FALSE)
                    {
                        g_Count++;
						#if 0 //harrison ds315
						#if defined(_GPS_EDOG_)
						if ((g_Count == 1) && !g_GPS_PlaySound_onetime)
                        {
                            UISound_Play(DEMOSOUND_SOUND_GPS_OK0_TONE);
                            UISound_Play(DEMOSOUND_SOUND_GPS_OK1_TONE);
                            g_GPS_PlaySound_onetime = TRUE;
                        }
						#elif defined(_GPS_EDOG_UNIQUE_SKY_)
						if ((g_Count == 1) && !g_GPS_PlaySound_onetime)
                        {
                            UISound_Play(DEMOSOUND_SOUND_EP5_TONE_GPS_OK);
                            g_GPS_PlaySound_onetime = TRUE;
                        }
						#endif
                        //rtc_waitCSETDone();
                        //debug_err(("FlowMovie_GPS= %d %d %d %d \r\n",RMCInfo.Year,RMCInfo.Hour,RMCInfo.Day,g_Count));
                        g_year = 2000 + RMCInfo.Year;
                        if ((g_year < MIN_YEAR)||(g_year > MAX_YEAR))
                        {
                            g_year = DEF_YEAR;
                        }

                        //rtc_setDate(RMCInfo.Year, RMCInfo.Month, RMCInfo.Day);
                        if (g_Count%10 == 0)
                        {
                            Curr_DateTime.tm_year = g_year;
                            Curr_DateTime.tm_mon = RMCInfo.Month;
                            Curr_DateTime.tm_mday = RMCInfo.Day;
                            Curr_DateTime.tm_hour = RMCInfo.Hour;
                            Curr_DateTime.tm_min = RMCInfo.Minute;
                            Curr_DateTime.tm_sec = RMCInfo.Second;
                            HwClock_SetTime(TIME_ID_CURRENT, Curr_DateTime, 0);
                            g_Count = 0;
                            //GPS_UpdateDateTime = TRUE;
                            //debug_err(("FlowMovie_GPS##= %d %d %d \r\n",g_year,RMCInfo.Hour,RMCInfo.Day));

                            #if(defined(_NVT_ETHREARCAM_RX_))                  
							#if 0
                            UINT32 i;
                            for (i=0; i<ETH_REARCAM_CAPS_COUNT; i++){
                                if(EthCamNet_GetEthLinkStatus(i)==ETHCAM_LINK_UP){
                                    //sync time
									EthCam_SendXMLCmdData(i, ETHCAM_PORT_DEFAULT , ETHCAM_CMD_SYNC_TIME, 0, (UINT8 *)&Curr_DateTime, sizeof(struct tm));

                                }
                            }
							#else
							if(!BKG_GetTskBusy()){
								GPS_UpdateDateTime = TRUE;
								BKG_PostEvent(NVTEVT_BKW_ETHCAM_SYNC_TIME_ONLY);
							}
							#endif
                            #endif
                        }
						#endif
                    }
                }
            }
            else if(gpsstatus == 0)
            {
                g_Count = 0;
                //GPS_UpdateDateTime = FALSE;
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCCtrl,FALSE);
                //UxStatic_SetData(&UIFlowWndWiFiMovie_GPSSignalCCtrl,STATIC_VALUE,Txt_Pointer(Get_GpsSpeedString()));
                UxStatic_SetData(&UIFlowWndWiFiMovie_GPSSignalCCtrl,STATIC_VALUE,Txt_Pointer(Speed1));
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCtrl,FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCCCtrl,FALSE);
                //UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSSignalCCtrl,TRUE);

                UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPS_SMALL_ICON2Ctrl,FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSN_SMALL_ICON2Ctrl,TRUE);
                if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_SOS1Ctrl))
                {
                    UxCtrl_SetShow(&UIFlowWndWiFiMovie_SOS1Ctrl,FALSE);
                    UxCtrl_SetShow(&UIFlowWndWiFiMovie_SOSCtrl,TRUE);
                }
            }
        }
    }
    Ux_Redraw();
}

void FlowWiFiMovie_IconDrawWiFiConnected(BOOL bShow)
{
    bWiFiConnected = bShow;

    if (bShow == FALSE)
    {
        UxState_SetData(&UIFlowWndWiFiMovie_Status_WiFi_ConnectedCtrl, STATE_CURITEM, UIFlowWndWiFiMovie_Status_WiFi_Connected_ICON_WIFI);
    }
    else
    {
        UxState_SetData(&UIFlowWndWiFiMovie_Status_WiFi_ConnectedCtrl, STATE_CURITEM, UIFlowWndWiFiMovie_Status_WiFi_Connected_ICON_WIFI_CONNECTED_SMALL);
    }
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Status_WiFi_ConnectedCtrl, TRUE);
}

void FlowWiFiMovie_IconDrawWiFiDisConnected(BOOL bShow)
{
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_WiFi_DisconnectedCtrl, bShow);
}

void FlowWiFiMovie_OnTimer1SecIndex(void)
{
    if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_YMD_StaticCtrl))
    {
        FlowWiFiMovie_IconDrawDateTime(TRUE);
    }
}

void FlowWiFiMovie_IconDrawSNG(BOOL bShow)
{
    INT8 gpsstatus;
    gpsstatus = GetGPSSignalStatus();

    if(!bShow)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNGCtrl,FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNG1Ctrl,FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNG2Ctrl,FALSE);   
        return;		
    }
	
    if (gpsstatus < 0)
    {    
        if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_SOS1Ctrl))
        {
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNG1Ctrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNG2Ctrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNGCtrl, FALSE);
        }
        else
        {
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNGCtrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNG1Ctrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNG2Ctrl, FALSE);
        }
    }
    else
    {
        if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_SOSCtrl))
        {
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNG2Ctrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNGCtrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNG1Ctrl, FALSE);
        }
        else
        {
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNG1Ctrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNG2Ctrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNGCtrl, FALSE);
        }
    }
}

void FlowWiFiMovie_IconDrawTSR(BOOL bShow)
{
    INT8 gpsstatus;
    gpsstatus = GetGPSSignalStatus();

    if (!bShow)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSRCtrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR1Ctrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR2Ctrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR3Ctrl, FALSE);
        return;		
    }
	
    if (gpsstatus < 0)
    {    
        if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_SOS1Ctrl))
        {
            if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_Static_SNG1Ctrl))
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSRCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR2Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawRL(FALSE);
            }
            else
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSRCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawRL(FALSE);
            }
        }
        else
        {
            if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_Static_SNGCtrl))
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSRCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawRL(FALSE);
            }
            else
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSRCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR1Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawRL(FALSE);
            }
        }
    }
    else
    {
        if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_SOSCtrl))
        {
            if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_Static_SNG2Ctrl))
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSRCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR3Ctrl, TRUE);
                FlowWiFiMovie_IconDrawRL(FALSE);
            }
            else
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSRCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR2Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawRL(FALSE);
            }
        }
        else
        {
            if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_Static_SNG1Ctrl))
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSRCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR2Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawRL(FALSE);
            }
            else
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSRCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawRL(FALSE);
            }
        }
    }
}

void FlowWiFiMovie_IconDrawRL(BOOL bShow)
{
    INT8 gpsstatus;
    gpsstatus = GetGPSSignalStatus();

    if (!bShow)
    {
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RLCtrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL1Ctrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL2Ctrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL3Ctrl, FALSE);
        return;		
    }
	
    if (gpsstatus < 0)
    {    
        if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_SOS1Ctrl))
        {
            if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_Static_SNG1Ctrl))
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RLCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL2Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawTSR(FALSE);
            }
            else
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RLCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawTSR(FALSE);
            }
        }
        else
        {
            if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_Static_SNGCtrl))
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RLCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawTSR(FALSE);
            }
            else
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RLCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL1Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawTSR(FALSE);
            }
        }
    }
    else
    {
        if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_SOSCtrl))
        {
            if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_Static_SNG2Ctrl))
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RLCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL3Ctrl, TRUE);
                FlowWiFiMovie_IconDrawTSR(FALSE);
            }
            else
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RLCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL2Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawTSR(FALSE);
            }
        }
        else
        {
            if (UxCtrl_IsShow(&UIFlowWndWiFiMovie_Static_SNG1Ctrl))
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RLCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL2Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawTSR(FALSE);
            }
            else
            {
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RLCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL3Ctrl, FALSE);
                FlowWiFiMovie_IconDrawTSR(FALSE);
            }
        }
    }
}

void FlowWiFiMovie_initIcon(void)
{
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_WiFi_DisconnectedCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_StaticIcon_PIMCtrl, FALSE);
    
    //UxCtrl_SetShow(&UIFlowWndMovie_YMD_StaticCtrl,FALSE);
    //UxCtrl_SetShow(&UIFlowWndMovie_HMS_StaticCtrl,FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Status_AudioCtrl, FALSE);
	
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_MotionDet1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_MotionDet2Ctrl, FALSE);	
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TimeLapse1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TimeLapse2Ctrl, FALSE);
	
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPS_SMALL_ICON2Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPSN_SMALL_ICON2Ctrl, FALSE);
	
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_SOSCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_SOS1Ctrl, FALSE);
	
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNGCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNG1Ctrl, FALSE);	
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_SNG2Ctrl, FALSE);	
	
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSRCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR2Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_TSR3Ctrl, FALSE);
	
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RLCtrl, FALSE);	
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL1Ctrl, FALSE);	
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL2Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_Static_RL3Ctrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_Panel_PlayModeCtrl, FALSE);
}


void FlowWiFiMovie_UpdateIcons(BOOL bShow)
{
    if ((bShow == FALSE) || (SysGetFlag(FL_LCD_DISPLAY) == DISPOUT_OFF))
    {
        //FlowWiFiMovie_IconDrawDscMode(FALSE);
        FlowWiFiMovie_IconDrawSize(FALSE);
        FlowWiFiMovie_IconDrawRecTime(FALSE);
        FlowWiFiMovie_IconDrawMaxRecTime(FALSE);
        FlowWiFiMovie_IconDrawRec(FALSE);
        FlowWiFiMovie_IconDrawStorage(FALSE);
        FlowWiFiMovie_IconDrawCyclicRec(FALSE);
        //FlowWiFiMovie_IconDrawHDR(FALSE);
        FlowWiFiMovie_IconDrawMotionDet(FALSE);
        FlowWiFiMovie_IconDrawDZoom(FALSE);
        FlowWiFiMovie_IconDrawBattery(FALSE);
        //FlowWiFiMovie_IconDrawEV(FALSE);
        FlowWiFiMovie_IconDrawSOS(FALSE);
        FlowWiFiMovie_IconDrawAudio(FALSE);
        FlowWiFiMovie_IconDrawTimelapse(FALSE);
        FlowWiFiMovie_IconDrawDateTime(FALSE);
        FlowWiFiMovie_DrawPIM(FALSE);
        FlowWiFiMovie_DrawFolderCheck(FALSE);
        FlowWiFiMovie_DrawCustomerType(FALSE);
        //FlowWiFiMovie_IconDrawWiFiConnected(FALSE);
        FlowWiFiMovie_IconDrawWiFiDisConnected(FALSE);
        FlowWiFiMovie_IconDrawGPSSignal(FALSE);
    }
    else
    {
        //FlowWiFiMovie_IconDrawDscMode(FALSE);
        FlowWiFiMovie_IconDrawSize(TRUE);
        FlowWiFiMovie_IconDrawRecTime(FALSE);
        FlowWiFiMovie_IconDrawMaxRecTime(TRUE);
        FlowWiFiMovie_IconDrawRec(FALSE);
        FlowWiFiMovie_IconDrawStorage(FALSE);
        FlowWiFiMovie_IconDrawCyclicRec(FALSE);
        //FlowWiFiMovie_IconDrawHDR(FALSE);
        FlowWiFiMovie_IconDrawDZoom(FALSE);
        FlowWiFiMovie_IconDrawBattery(FALSE);
        //FlowWiFiMovie_IconDrawEV(FALSE);
        FlowWiFiMovie_IconDrawSOS(FALSE);
        FlowWiFiMovie_IconDrawAudio(TRUE);
        FlowWiFiMovie_IconDrawDateTime(TRUE);
        FlowWiFiMovie_DrawPIM(FALSE);
        FlowWiFiMovie_DrawFolderCheck(FALSE);
        FlowWiFiMovie_DrawCustomerType(FALSE);
        //FlowWiFiMovie_IconDrawWiFiConnected(FALSE);
        FlowWiFiMovie_IconDrawWiFiDisConnected(FALSE);
		#if 1
		FlowWiFiMovie_IconDrawMotionDet(FALSE);
		FlowWiFiMovie_IconDrawTimelapse(TRUE);
		#else
        //if ((SysGetFlag(FL_MOVIE_MOTION_DET) == MOVIE_MOTIONDET_OFF)&&(UI_GetData(FL_MOVIE_TIMELAPSE_REC) != MOVIE_TIMELAPSEREC_OFF)) //time lapse
        if ((SysGetFlag(FL_MOVIE_REC_MODE) == MOVIE_REC_MODE_ONEFRAM))
        {
            FlowWiFiMovie_IconDrawMotionDet(FALSE);
            FlowWiFiMovie_IconDrawTimelapse(TRUE);
        }
        //else if ((SysGetFlag(FL_MOVIE_MOTION_DET) == MOVIE_MOTIONDET_ON)&&(UI_GetData(FL_MOVIE_TIMELAPSE_REC) == MOVIE_TIMELAPSEREC_OFF)) //motion det
        else if ((SysGetFlag(FL_MOVIE_REC_MODE) == MOVIE_REC_MODE_MOTIONDET))
        {
            FlowWiFiMovie_IconDrawTimelapse(FALSE);
            FlowWiFiMovie_IconDrawMotionDet(TRUE);
        }
        else
        {
        	if(UI_GetData(FL_MOVIE_TIMELAPSE_REC) != MOVIE_TIMELAPSEREC_OFF)
			{
            	FlowWiFiMovie_IconDrawMotionDet(FALSE);
            	FlowWiFiMovie_IconDrawTimelapse(TRUE);
        	}
			else
			{
				FlowWiFiMovie_IconDrawMotionDet(FALSE);
				FlowWiFiMovie_IconDrawTimelapse(FALSE);
			}
        }
        //FlowWiFiMovie_IconDrawGPSSignal(TRUE);
		#endif
    }
}

