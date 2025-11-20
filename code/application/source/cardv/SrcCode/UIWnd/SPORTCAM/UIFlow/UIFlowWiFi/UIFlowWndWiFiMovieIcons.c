
#include "PrjInc.h"
#include "UIApp/Photo/UIAppPhoto.h"
#include "GxTime.h"
#include "GxStrg.h"
#include "comm/hwclock.h"
#include "UIApp/Network/UIAppWiFiCmd.h"

#define __MODULE__          UIWiFiMovieIcons
#define __DBGLVL__          2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>
//#include "PhotoTsk.h"
//#include "DxGPS.h"
#if (defined(_NVT_ETHREARCAM_RX_))
#include "UIApp/Network/EthCamAppCmd.h"
#include "UIApp/Network/EthCamAppNetwork.h"
#endif
#include "DxInput.h"
#include "algo_manager.h"
#include <math.h>

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
static UINT32 g_year = DEF_YEAR;
static UINT32 g_Count = 0;
extern INT8 uitpmsstatus;
extern BOOL GPS_UpdateDateTime;
#if defined(_GPS_EDOG_)
extern BOOL EdogFstCnetd;
extern BOOL g_GPS_PlaySound_onetime;
#elif defined(_GPS_EDOG_UNIQUE_SKY_)
extern BOOL EdogFstCnetd;
extern BOOL g_GPS_PlaySound_onetime;
#endif
void FlowWiFiMovie_IconDrawGPSSignal(BOOL bShow)
{
    INT8 gpsstatus = 0;
    RMCINFO RMCInfo;
    struct tm Curr_DateTime = {0};

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
                        	#if PLAY_SOUND_IN_OTHER_TASK
	                        UIDogSound_Enable(FALSE);
					        DogSoundPlayID(DEMOSOUND_SOUND_EP5_TONE_GPS_OK);							
							UIDogSound_Enable(TRUE);
							#else
                            UISound_Play(DEMOSOUND_SOUND_EP5_TONE_GPS_OK);
							#endif
                            g_GPS_PlaySound_onetime = TRUE;
                        }
						#endif
                        //rtc_waitCSETDone();
                        //debug_err(("FlowMovie_GPS= %d %d %d %d \r\n",RMCInfo.Year,RMCInfo.Hour,RMCInfo.Day,g_Count));
                        g_year = 2000 + RMCInfo.Year;
						#if 0
                        if ((g_year < MIN_YEAR)||(g_year > MAX_YEAR))
                        {
                            g_year = DEF_YEAR;
                        }
						#endif

                        //rtc_setDate(RMCInfo.Year, RMCInfo.Month, RMCInfo.Day);
                        if (g_Count%10 == 0)
                        {
                            Curr_DateTime.tm_year = g_year;
                            Curr_DateTime.tm_mon = RMCInfo.Month;
                            Curr_DateTime.tm_mday = RMCInfo.Day;
                            Curr_DateTime.tm_hour = RMCInfo.Hour;
                            Curr_DateTime.tm_min = RMCInfo.Minute;
                            Curr_DateTime.tm_sec = RMCInfo.Second;
                            hwclock_set_time(TIME_ID_CURRENT, Curr_DateTime, 0);
                            g_Count = 0;
                            //debug_err(("FlowMovie_GPS##= %d %d %d \r\n",g_year,RMCInfo.Hour,RMCInfo.Day));

                            #if(defined(_NVT_ETHREARCAM_RX_))                  
							if(!BKG_GetTskBusy()){
								GPS_UpdateDateTime = TRUE;
								BKG_PostEvent(NVTEVT_BKW_ETHCAM_SYNC_TIME_ONLY);
							}
							#else
                            GPS_UpdateDateTime = TRUE;							
                            #endif
                        }
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
void FlowWiFiMovie_IconDrawADASAnimation(void)
{
	static UINT32 i = ICON_ADAS_ANIMATION_01;
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_AnimationCtrl,FALSE);
	if(i>=ICON_ADAS_ANIMATION_01 &&i<=ICON_ADAS_ANIMATION_07)
	{
		UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_Car_AnimationCtrl, STATIC_VALUE, i);
	}
	else
	{
		i = ICON_ADAS_ANIMATION_01;
		UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_Car_AnimationCtrl, STATIC_VALUE, i);
	}
	i++;
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_AnimationCtrl,TRUE);
}
UINT32 FlowWiFiMovie_DrawADASDisNum(UINT32 Value)
{
	UINT32 ICON_ID = ICONID_NULL;

	switch(Value)
	{
	case 0:
		ICON_ID =ICON_ADAS_00;
		break;
	case 1:
		ICON_ID =ICON_ADAS_01;
		break;
	case 2:
		ICON_ID =ICON_ADAS_02;
		break;
	case 3:
		ICON_ID =ICON_ADAS_03;
		break;
	case 4:
		ICON_ID =ICON_ADAS_04;
		break;
	case 5:
		ICON_ID =ICON_ADAS_05;
		break;
	case 6:
		ICON_ID =ICON_ADAS_06;
		break;
	case 7:
		ICON_ID =ICON_ADAS_07;
		break;
	case 8:
		ICON_ID =ICON_ADAS_08;
		break;
	case 9:
		ICON_ID =ICON_ADAS_09;
		break;
	}

	return ICON_ID;
}

void FlowWiFiMovie_IconDrawADASDistance(UINT32 distance)
{
	UINT32 uiN0 = 0,uiN1 = 0;

	uiN0 = (distance%10);
	uiN1 = ((distance%100)/10);

	UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_Distance_Num0Ctrl,STATIC_VALUE,FlowWiFiMovie_DrawADASDisNum(uiN1));
    UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_Distance_Num1Ctrl,STATIC_VALUE,FlowWiFiMovie_DrawADASDisNum(uiN0));
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Distance_Num0Ctrl,TRUE);
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Distance_Num1Ctrl,TRUE);
}
void FlowWiFiMovie_IconHideADASDistance(void)
{
	UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_Distance_Num0Ctrl,STATIC_VALUE,ICON_ADAS_00);
    UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_Distance_Num1Ctrl,STATIC_VALUE,ICON_ADAS_00);
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Distance_Num0Ctrl,TRUE);
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Distance_Num1Ctrl,TRUE);
}


void FlowWiFiMovie_IconDrawADASDisplayType(UINT32 id)
{
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_TypeCtrl,FALSE);
	switch(id)
	{
		case ADAS_ALARM_LD_LEFT:
			UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_LANE_LEFT);
			break;
			
		case ADAS_ALARM_LD_RIGHT:
			UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_LANE_RIGHT);
			break;
			
		case ADAS_ALARM_FC:
			UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_FRONT_ALERT);
			break;

		case ADAS_ALARM_GO:
			UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_GO_ALERT);
			break;

		case ADAS_ALARM_FPW:
			UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_PEOPLE_ALERT);
			break;

		case ADAS_ALARM_VIRTUAL_BUMPERS:
			UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_VIRTUAL_BUMPER);
			break;

		case ADAS_ALARM_RCW_REAR:
			UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_REAR_ALERT);
			break;

		case ADAS_ALARM_LCA_LEFT:
			UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_CHANGE_LANE_LEFT);
			break;

		case ADAS_ALARM_LCA_RIGHT:
			UxStatic_SetData(&UIFlowWndWiFiMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_CHANGE_LANE_RIGHT);
			break;

		default:
			break;
	}
	
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_TypeCtrl,TRUE);
}
void FlowWiFiMovie_IconHideADASDisplayType(void)
{
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_TypeCtrl,FALSE);
}

extern AlgoEventData adas_eventData_app;

extern AlgoEventData rcw_eventData_app;
extern pthread_mutex_t g_data_mutex_front ;
extern pthread_mutex_t g_data_mutex_rear ;
void FlowWiFiMovie_IconDrawADASHideCar(void)
{
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_00Ctrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_01Ctrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_02Ctrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_03Ctrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_04Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_05Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_06Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Red_01Ctrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Red_00Ctrl, FALSE);
}

void FlowWiFiMovie_IconDrawADASUpdateCar(void)
#if 1
{
	AlgoEventData adas_eventData_app00 = {0};
	AlgoEventData rcw_eventData_app01 = {0};

	if (pthread_mutex_trylock(&g_data_mutex_front) == 0) {
		memcpy(&adas_eventData_app00, &adas_eventData_app, sizeof(adas_eventData_app));
		pthread_mutex_unlock(&g_data_mutex_front);

		// 只隐藏前路控件（4蓝1红）
		UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_00Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_01Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_02Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_03Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Red_00Ctrl, FALSE);
		
		if (adas_eventData_app00.result.type != ALGO_TYPE_ADAS) {
			DBG_DUMP("Not ADAS data, type=%d\r\n", adas_eventData_app00.result.type);
			return;
		}
		
		AlgoAdasResult* adas_result = &adas_eventData_app00.result.algoResult.adasResult;
		
		if (adas_result == NULL) {
			DBG_DUMP("ADAS result is NULL\r\n");
			return;
		}
		
		AlgoAdasFcwResult* fcw_result = &adas_result->fcw;
		
		if (fcw_result->objsize < 0 || fcw_result->objsize > ALGO_ADAS_OBJ_MAX_NUM) {
			DBG_DUMP("Invalid objsize: %d\r\n", fcw_result->objsize);
			return;
		}
		
		INT32 cipv_index = fcw_result->cipv;
		BOOL has_cipv = (cipv_index >= 0 && cipv_index < fcw_result->objsize);
		
		DBG_DUMP("FCW: objsize=%d, cipv=%d\r\n", fcw_result->objsize, cipv_index);
		
		// 前路车辆计数和红色标记
		INT32 front_count = 0;
		BOOL front_red_shown = FALSE;
		INT32 blue_count = 0;
		
		for (INT32 i = 0; i < fcw_result->objsize && front_count < 5; i++) {
			AlgoAdasObject* obj = &fcw_result->objects[i];
			
			FLOAT distance_x = fabs(obj->relative_distance.x);
			FLOAT distance_y = fabs(obj->relative_distance.y);

			if (distance_x > 30.0f || distance_y > 30.0f) {
				DBG_DUMP("Car %d out of range: (%.1f,%.1f)m\r\n", 
						 i, obj->relative_distance.x, obj->relative_distance.y);
				continue;
			}
			
			// 坐标计算
			const FLOAT max_distance = 30.0f;
			const INT32 display_offset_x = 50;
			const INT32 display_offset_y = 0;
			const INT32 display_width = 168;
			const INT32 display_height = 240;
			const INT32 self_car_display_x = display_width / 2;
			const INT32 self_car_display_y = display_height / 2;
			
			const FLOAT pixels_per_meter_x = (FLOAT)display_width / (2 * max_distance);
			const FLOAT pixels_per_meter_y = (FLOAT)(display_height - 3*30) / (2 * max_distance);
			
			INT32 pixel_offset_x = (INT32)(obj->relative_distance.x * pixels_per_meter_x);
			INT32 pixel_offset_y = (INT32)(obj->relative_distance.y * pixels_per_meter_y);
			
			INT32 display_x = self_car_display_x + pixel_offset_x;
			INT32 display_y = self_car_display_y - pixel_offset_y - 30;
			
			INT32 screen_x = display_offset_x + display_x;
			INT32 screen_y = display_offset_y + display_y;
			
			Ux_RECT rect;
			rect.x1 = screen_x - 11;
			rect.y1 = screen_y - 15;
			rect.x2 = screen_x + 12;
			rect.y2 = screen_y + 15;

			// 分配前路控件：优先显示红色，然后蓝色
			VControl* car_ctrl = NULL;
			BOOL is_red_car = (i == cipv_index && has_cipv);
			
			// 如果是红色车辆且还没显示红色
			if (is_red_car && !front_red_shown) {
				car_ctrl = (VControl*)&UIFlowWndWiFiMovie_ADAS_Car_Red_00Ctrl;
				front_red_shown = TRUE;
				if(ICON_ADAS_REAR_ALERT != UxStatic_GetData(&UIFlowWndWiFiMovie_ADAS_TypeCtrl, STATIC_VALUE)){
					// 直接使用Y轴距离（前方距离）
				    FLOAT distance_m = obj->relative_distance.y;
				    
				    // 米转英尺
				    UINT32 distance_ft = (UINT32)(distance_m * 3.28084f + 0.5f); // 四舍五入
				    
				    // 显示距离（英尺）
				    FlowMovie_IconDrawADASDistance(distance_ft);
				    
				    DBG_DUMP("Red Car Front Distance: %.1fm -> %dft\r\n", distance_m, distance_ft);
				}
			} 
			// 如果是蓝色车辆且还有蓝色名额（最多4个）
			else if (!is_red_car && blue_count < 4) {
				switch (blue_count) {
					case 0: car_ctrl = (VControl*)&UIFlowWndWiFiMovie_ADAS_Car_Blue_00Ctrl; break;
					case 1: car_ctrl = (VControl*)&UIFlowWndWiFiMovie_ADAS_Car_Blue_01Ctrl; break;
					case 2: car_ctrl = (VControl*)&UIFlowWndWiFiMovie_ADAS_Car_Blue_02Ctrl; break;
					case 3: car_ctrl = (VControl*)&UIFlowWndWiFiMovie_ADAS_Car_Blue_03Ctrl; break;
				}
				blue_count++;
			} else {
				// 没有名额了，跳过这个车辆
				continue;
			}
			
			if (car_ctrl != NULL) {
				UxCtrl_SetPos(car_ctrl, rect);
				UxCtrl_SetShow(car_ctrl, TRUE);
				
				if (is_red_car) {
					UxStatic_SetData(car_ctrl, STATIC_VALUE, ICON_ADAS_CAR_RED);
				} else {
					UxStatic_SetData(car_ctrl, STATIC_VALUE, ICON_ADAS_CAR_BLUE);
				}
				
				DBG_DUMP("Front Car %d: %s, real(%.1f,%.1f)m, screen(%d,%d)\r\n", 
						 i, is_red_car ? "RED" : "BLUE", 
						 obj->relative_distance.x, obj->relative_distance.y, screen_x, screen_y);
				
				front_count++;
			}
		}
	}
	
	if (pthread_mutex_trylock(&g_data_mutex_rear) == 0) {		 
	    memcpy(&rcw_eventData_app01, &rcw_eventData_app, sizeof(rcw_eventData_app));
	    pthread_mutex_unlock(&g_data_mutex_rear);

	    // 只隐藏后路控件（3蓝1红）
	    UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_04Ctrl, FALSE);
	    UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_05Ctrl, FALSE);
	    UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Blue_06Ctrl, FALSE);
	    UxCtrl_SetShow(&UIFlowWndWiFiMovie_ADAS_Car_Red_01Ctrl, FALSE);
	    
	    if (rcw_eventData_app01.result.type == ALGO_TYPE_RCW) {
	        AlgoRcwResult* rcw_result = &rcw_eventData_app01.result.algoResult.rcwResult;
	        
	        if (rcw_result != NULL) {
	            AlgoRcwCarResult* car_result = &rcw_result->rear;  // 使用rear成员
	            
	            if (car_result->objsize >= 0 && car_result->objsize <= ALGO_RCW_OBJ_MAX_NUM) {
	                INT32 cipv_index = car_result->cipv;
	                BOOL has_cipv = (cipv_index >= 0 && cipv_index < car_result->objsize);
	                
	                DBG_DUMP("RCW: objsize=%d, cipv=%d\r\n", car_result->objsize, cipv_index);
	                
	                // 后路车辆计数和红色标记
	                INT32 rear_count = 0;
	                BOOL rear_red_shown = FALSE;
	                INT32 blue_count = 0;
	                
	                for (INT32 i = 0; i < car_result->objsize && rear_count < 4; i++) {
	                    AlgoRcwObject* obj = &car_result->objects[i];  // 使用AlgoRcwObject
	                    
	                    FLOAT distance_x = fabs(obj->relative_distance.x);
	                    FLOAT distance_y = fabs(obj->relative_distance.y);
	                    
	                    if (distance_x > 30.0f || distance_y > 30.0f) {
	                        DBG_DUMP("Rear Car %d out of range: (%.1f,%.1f)m\r\n", 
	                                 i, obj->relative_distance.x, obj->relative_distance.y);
	                        continue;
	                    }
	                    
	                    // 后路坐标计算（Y轴方向与前方相反）
	                    const FLOAT max_distance = 30.0f;
	                    const INT32 display_offset_x = 50;
	                    const INT32 display_offset_y = 0;
	                    const INT32 display_width = 168;
	                    const INT32 display_height = 240;
	                    const INT32 self_car_display_x = display_width / 2;
	                    const INT32 self_car_display_y = display_height / 2;
	                    
	                    const FLOAT pixels_per_meter_x = (FLOAT)display_width / (2 * max_distance);
	                    const FLOAT pixels_per_meter_y = (FLOAT)(display_height - 3*30) / (2 * max_distance);
	                    
	                    INT32 pixel_offset_x = (INT32)(obj->relative_distance.x * pixels_per_meter_x);
	                    INT32 pixel_offset_y = (INT32)(obj->relative_distance.y * pixels_per_meter_y);
	                    
	                    // 后路车辆Y轴计算：使用 +30 而不是 -30
	                    INT32 display_x = self_car_display_x + pixel_offset_x;
	                    INT32 display_y = self_car_display_y - pixel_offset_y + 30;
	                    
	                    INT32 screen_x = display_offset_x + display_x;
	                    INT32 screen_y = display_offset_y + display_y;
	                    
	                    Ux_RECT rect;
	                    rect.x1 = screen_x - 11;
	                    rect.y1 = screen_y - 15;
	                    rect.x2 = screen_x + 12;
	                    rect.y2 = screen_y + 15;
	                    
	                    // 分配后路控件：优先显示红色，然后蓝色
	                    VControl* car_ctrl = NULL;
	                    BOOL is_red_car = (i == cipv_index && has_cipv);
	                    
	                    // 如果是红色车辆且还没显示红色
	                    if (is_red_car && !rear_red_shown) {
	                        car_ctrl = (VControl*)&UIFlowWndWiFiMovie_ADAS_Car_Red_01Ctrl;
	                        rear_red_shown = TRUE;
							
							if(ICON_ADAS_REAR_ALERT == UxStatic_GetData(&UIFlowWndWiFiMovie_ADAS_TypeCtrl, STATIC_VALUE))
							{
								// 后路使用Y轴距离的绝对值（后方距离）
							    FLOAT distance_m = fabs(obj->relative_distance.y);
							    
							    // 米转英尺
							    UINT32 distance_ft = (UINT32)(distance_m * 3.28084f + 0.5f); // 四舍五入
							    
							    // 显示距离（英尺）
							    FlowMovie_IconDrawADASDistance(distance_ft);
							    
							    DBG_DUMP("Rear Red Car Distance: %.1fm -> %dft\r\n", distance_m, distance_ft);
							}
	                    } 
	                    // 如果是蓝色车辆且还有蓝色名额（最多3个）
	                    else if (!is_red_car && blue_count < 3) {
	                        switch (blue_count) {
	                            case 0: car_ctrl = (VControl*)&UIFlowWndWiFiMovie_ADAS_Car_Blue_04Ctrl; break;
	                            case 1: car_ctrl = (VControl*)&UIFlowWndWiFiMovie_ADAS_Car_Blue_05Ctrl; break;
	                            case 2: car_ctrl = (VControl*)&UIFlowWndWiFiMovie_ADAS_Car_Blue_06Ctrl; break;
	                        }
	                        blue_count++;
	                    } else {
	                        // 没有名额了，跳过这个车辆
	                        continue;
	                    }
	                    
	                    if (car_ctrl != NULL) {
	                        UxCtrl_SetPos(car_ctrl, rect);
	                        UxCtrl_SetShow(car_ctrl, TRUE);
	                        
	                        if (is_red_car) {
	                            UxStatic_SetData(car_ctrl, STATIC_VALUE, ICON_ADAS_CAR_RED);
	                        } else {
	                            UxStatic_SetData(car_ctrl, STATIC_VALUE, ICON_ADAS_CAR_BLUE);
	                        }
	                        
	                        DBG_DUMP("Rear Car %d: %s, real(%.1f,%.1f)m, screen(%d,%d)\r\n", 
	                                 i, is_red_car ? "RED" : "BLUE", 
	                                 obj->relative_distance.x, obj->relative_distance.y, screen_x, screen_y);
	                        
	                        rear_count++;
	                    }
	                }
	            }
	        }
	    }
	}
}
#else
{
	AlgoEventData adas_eventData_app00 = {0};
	AlgoEventData rcw_eventData_app01 = {0};

	if (pthread_mutex_trylock(&g_data_mutex_front) == 0) {
		memcpy(&adas_eventData_app00, &adas_eventData_app, sizeof(adas_eventData_app));
		//DBG_DUMP("========SUCCESS1===============\r\n");
		pthread_mutex_unlock(&g_data_mutex_front);

		
	#if 1
		// 先隐藏所有汽车图标
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_00Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_01Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_02Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_03Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_04Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_05Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_06Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Red_00Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Red_01Ctrl, FALSE);
		// 安全检查：确保数据有效
		if (adas_eventData_app00.result.type != ALGO_TYPE_ADAS) {
			DBG_DUMP("Not ADAS data, type=%d\r\n", adas_eventData_app00.result.type);
			return;
		}
		
		AlgoAdasResult* adas_result = &adas_eventData_app00.result.algoResult.adasResult;
		
		// 安全检查：确保FCW数据有效
		if (adas_result == NULL) {
			DBG_DUMP("ADAS result is NULL\r\n");
			return;
		}
		
		AlgoAdasFcwResult* fcw_result = &adas_result->fcw;
		
		// 安全检查：确保对象数量有效
		if (fcw_result->objsize < 0 || fcw_result->objsize > ALGO_ADAS_OBJ_MAX_NUM) {
			DBG_DUMP("Invalid objsize: %d\r\n", fcw_result->objsize);
			return;
		}
		
		// 先标记正前方车辆（cipv）
		INT32 cipv_index = fcw_result->cipv;
		BOOL has_cipv = (cipv_index >= 0 && cipv_index < fcw_result->objsize);
		
		DBG_DUMP("FCW: objsize=%d, cipv=%d\r\n", fcw_result->objsize, cipv_index);
		
		// 遍历检测到的车辆
		for (INT32 i = 0; i < fcw_result->objsize && i < 8; i++) {
			// 安全检查：确保对象指针有效
			if (&fcw_result->objects[i] == NULL) {
				DBG_DUMP("Object %d is NULL\r\n", i);
				continue;
			}
			
			AlgoAdasObject* obj = &fcw_result->objects[i];
			 // 检查距离是否在30米范围内
			FLOAT distance_x = fabs(obj->relative_distance.x);
			FLOAT distance_y = fabs(obj->relative_distance.y);

			  // 如果x或y方向距离超过30米，不显示
			if (distance_x > 30.0f || distance_y > 30.0f) {
				DBG_DUMP("Car %d out of range: (%.1f,%.1f)m\r\n", 
						 i, obj->relative_distance.x, obj->relative_distance.y);
				continue;
			}
			// 将实际距离转换为显示区域内的坐标
			const FLOAT max_distance = 30.0f;
			
			// 显示区域参数
			const INT32 display_offset_x = 50;	  // 显示区域X起始位置
			const INT32 display_offset_y = 0;	  // 显示区域Y起始位置
			const INT32 display_width = 168;	  // 显示区域宽度
			const INT32 display_height = 240;	  // 显示区域高度
			
			// 小汽车在显示区域内的中心位置
			const INT32 self_car_display_x = display_width / 2; 	// 84
			const INT32 self_car_display_y = display_height / 2;	// 120
			
			// 计算像素/米的比例（显示区域覆盖自车+前后左右各30米）
			const FLOAT pixels_per_meter_x = (FLOAT)display_width / (2 * max_distance);   // 168/60 = 2.8像素/米
			const FLOAT pixels_per_meter_y = (FLOAT)(display_height - 3*30) / (2 * max_distance);  // 240/60 = 4.0像素/米
			
			// 计算相对于自车中心的像素偏移
			INT32 pixel_offset_x = (INT32)(obj->relative_distance.x * pixels_per_meter_x);
			INT32 pixel_offset_y = (INT32)(obj->relative_distance.y * pixels_per_meter_y);
			
			// 计算在显示区域内的坐标（以自车中心为原点）
			INT32 display_x = self_car_display_x + pixel_offset_x;
			INT32 display_y = self_car_display_y - pixel_offset_y - 30;	// 前方为-Y方向
			
			// 转换为屏幕绝对坐标
			INT32 screen_x = display_offset_x + display_x;
			INT32 screen_y = display_offset_y + display_y;
			
			// 创建矩形区域（23x30）- 中心对齐
			Ux_RECT rect;
			rect.x1 = screen_x - 11;   // 中心向左11像素
			rect.y1 = screen_y - 15;   // 中心向上15像素
			rect.x2 = screen_x + 12;   // 中心向右12像素
			rect.y2 = screen_y + 15;   // 中心向下15像素

			// 选择图标控件
			VControl* car_ctrl = NULL;
			
			// 分配控件（按顺序使用所有可用的控件）
			if (i < 7) {
				switch (i) {
					case 0: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_00Ctrl; break;
					case 1: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_01Ctrl; break;
					case 2: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_02Ctrl; break;
					case 3: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_03Ctrl; break;
					case 4: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_04Ctrl; break;
					case 5: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_05Ctrl; break;
					case 6: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_06Ctrl; break;
					default: break;
				}
			} else if (i < 9) {
				switch (i) {
					case 7: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Red_00Ctrl; break;
					case 8: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Red_01Ctrl; break;
					default: break;
				}
			}
			
			if (car_ctrl != NULL) {
				// 设置位置并显示
				UxCtrl_SetPos(car_ctrl, rect);
				UxCtrl_SetShow(car_ctrl, TRUE);
				
				// 如果是正前方车辆，设置为红色图标
				if (i == cipv_index && has_cipv) {
					UxStatic_SetData(car_ctrl, STATIC_VALUE, ICON_ADAS_CAR_RED);
				} else {
					UxStatic_SetData(car_ctrl, STATIC_VALUE, ICON_ADAS_CAR_BLUE);
				}
				
				DBG_DUMP("Car %d: real(%.1f,%.1f)m, screen(%d,%d)\r\n", 
						 i, obj->relative_distance.x, obj->relative_distance.y, screen_x, screen_y);
			}
		}
	#endif
	}
	
	if (pthread_mutex_trylock(&g_data_mutex_rear) == 0) {		 
		memcpy(&rcw_eventData_app01, &rcw_eventData_app, sizeof(rcw_eventData_app));
		pthread_mutex_unlock(&g_data_mutex_rear);
	}
}
#endif


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
		FlowMovie_IconHideADASDisplayType();
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
		FlowWiFiMovie_IconHideADASDisplayType();
    }
}

