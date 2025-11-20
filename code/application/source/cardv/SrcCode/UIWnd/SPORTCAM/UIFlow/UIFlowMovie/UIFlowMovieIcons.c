#include "PrjInc.h"
#include "GxTime.h"

#define __MODULE__          UIMovieIcons
#define __DBGLVL__          2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>
//#include "DxGPS.h"
#if (defined(_NVT_ETHREARCAM_RX_))
#include "UIApp/Network/EthCamAppCmd.h"
#include "UIApp/Network/EthCamAppNetwork.h"
#endif
#include "DxInput.h"
#include "algo_manager.h"
#include <math.h>


static CHAR		g_RecMaxTimeStr[20] = {0};
static UINT32	g_RecMaxTime = 0;
static CHAR		g_RecCurrTimeStr[20] = {0};
static UINT32	g_RecCurrTime = 0;
static CHAR		date_str[20] = {0};
static CHAR		time_str[20] = {0};

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
	[MOVIE_SIZE_FRONT_640x480P240] = "VGA P240",
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
	[MOVIE_SIZE_FRONT_2704x2032P60] = "2.7K P60",
	[MOVIE_SIZE_FRONT_2560x1440P80] = "QHD P80",
	[MOVIE_SIZE_FRONT_1920x1080P120] = "FHD P120",
	[MOVIE_SIZE_FRONT_1920x1080P96] = "FHD P96",
	#endif
};

#endif

void FlowMovie_IconDrawDscMode(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovie_IconHideDscMode(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawMaxRecTime(VControl *pCtrl)
{
#if _TODO
	if (GxStrg_GetDevice(0) == 0) {
		//No Storage, direct to return.
		return;
	}
#endif

	memset((void *)g_RecMaxTimeStr, 0, sizeof(g_RecMaxTimeStr));
	//g_RecMaxTime = Movie_GetFreeSec();
	g_RecMaxTime = MovieExe_GetMaxRecSec();

	if (g_RecMaxTime <= 2)
	{
		FlowMovie_SetRecMaxTime(0);
	} 
	/*else if (g_RecMaxTime > 86399) { //modify for 256GB Card
		///23:59:59
		FlowMovie_SetRecMaxTime(86399);
	}*/
	else
	{
		FlowMovie_SetRecMaxTime(g_RecMaxTime);
	}

	if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
		snprintf(g_RecMaxTimeStr, 20, "%02d:%02d:%02d", 0, 0, 0);
	} else {
		snprintf(g_RecMaxTimeStr, 20, "%02d:%02d:%02d", g_RecMaxTime / 3600, (g_RecMaxTime % 3600) / 60, (g_RecMaxTime % 3600) % 60);
	}

	UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer(g_RecMaxTimeStr));
	UxCtrl_SetShow(pCtrl, TRUE);
}


void FlowMovie_IconHideMaxRecTime(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawRecTime(VControl *pCtrl)
{
	switch (gMovData.State) {
	case MOV_ST_REC:
	case MOV_ST_REC | MOV_ST_ZOOM:
		g_RecCurrTime = FlowMovie_GetRecCurrTime();
		memset((void *)g_RecCurrTimeStr, 0, sizeof(g_RecCurrTimeStr));
		snprintf(g_RecCurrTimeStr, 20, "%02d:%02d:%02d", g_RecCurrTime / 3600, (g_RecCurrTime % 3600) / 60, (g_RecCurrTime % 3600) % 60);
		UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer(g_RecCurrTimeStr));
		UxCtrl_SetShow(pCtrl, TRUE);
		break;
    case MOV_ST_REC_WAIT:
		g_RecCurrTime = 0;
		memset((void *)g_RecCurrTimeStr, 0, sizeof(g_RecCurrTimeStr));
		snprintf(g_RecCurrTimeStr, 20, "%02d:%02d:%02d", g_RecCurrTime / 3600, (g_RecCurrTime % 3600) / 60, (g_RecCurrTime % 3600) % 60);
		//snprintf(g_RecCurrTimeStr, 20, "%02d:%02d", (g_RecCurrTime % 3600) / 60, (g_RecCurrTime % 3600) % 60);
		UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer(g_RecCurrTimeStr));
		UxCtrl_SetShow(pCtrl, TRUE);
        break;
	}
}


void FlowMovie_IconHideRecTime(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawDateTime(void)
{
    struct tm Curr_DateTime;
    GxTime_GetTime(&Curr_DateTime);

	// display Date/Time string in movie mode
    switch (SysGetFlag(FL_DATE_FORMAT)) {
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
	UxStatic_SetData(&UIFlowWndMovie_YMD_StaticCtrl, STATIC_VALUE, Txt_Pointer(date_str));
	UxStatic_SetData(&UIFlowWndMovie_HMS_StaticCtrl, STATIC_VALUE, Txt_Pointer(time_str));
	UxCtrl_SetShow(&UIFlowWndMovie_YMD_StaticCtrl, TRUE);
	UxCtrl_SetShow(&UIFlowWndMovie_HMS_StaticCtrl, TRUE);
}

void FlowMovie_IconHideDateTime(void)
{
	UxCtrl_SetShow(&UIFlowWndMovie_YMD_StaticCtrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_HMS_StaticCtrl, FALSE);
}

void FlowMovie_IconDrawRec(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovie_IconHideRec(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawSize(VControl *pCtrl)
{
	UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer(resolution_Buf[SysGetFlag(FL_MOVIE_SIZE)]));
#if(defined(_NVT_ETHREARCAM_RX_))
	if(/*GPIOMap_EthCam1Det()||*/FlowMovie_IsEthCamConnectOK()) 
	{
		switch(SysGetFlag(FL_MOVIE_SIZE))
		{
			default:
			case MOVIE_SIZE_FRONT_3840x2160P30:
				UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("4KP30+1080P30"));
				break;
			case MOVIE_SIZE_FRONT_2560x1440P60:
				UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P60+1080P30"));
				break;
			case MOVIE_SIZE_FRONT_2560x1440P30:
				UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P30+1080P30"));
				break;
			case MOVIE_SIZE_FRONT_2304x1296P30:
				UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1296P30+1080P30"));
				break;
			case MOVIE_SIZE_FRONT_1920x1080P120:
				UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1080P120+1080P30"));
				break;
			case MOVIE_SIZE_FRONT_1920x1080P60:
				UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1080P60+1080P30"));
				break;
			case MOVIE_SIZE_FRONT_1920x1080P30: 	
				UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1080P30+1080P30"));
				break;
			case MOVIE_SIZE_FRONT_1280x720P120: 	
				UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P120+1080P30"));
				break;
			case MOVIE_SIZE_FRONT_1280x720P60:
				UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P60+1080P30"));
				break;
			case MOVIE_SIZE_FRONT_1280x720P30:
				UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P30+1080P30"));
				break;
		}
	}
#endif
	UxCtrl_SetShow(pCtrl, TRUE);
}


void FlowMovie_IconHideSize(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawEV(VControl *pCtrl)
{
	UxState_SetData(pCtrl, STATE_CURITEM, SysGetFlag(FL_EV));
	UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovie_IconHideEV(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawStorage(VControl *pCtrl)
{
	/* Update status item data */
	if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
		UxState_SetData(pCtrl, STATE_CURITEM, UIFlowWndMovie_Status_Storage_ICONID_NULL);
	} else if (System_GetState(SYS_STATE_CARD) == CARD_LOCKED) {
		UxState_SetData(pCtrl, STATE_CURITEM, UIFlowWndMovie_Status_Storage_ICON_SD_LOCK);
	} else {
		UxState_SetData(pCtrl, STATE_CURITEM, UIFlowWndMovie_Status_Storage_ICON_SD_CARD);
	}

	UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovie_IconHideStorage(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawCyclicRec(VControl *pCtrl)
{
	UxState_SetData(pCtrl, STATE_CURITEM, SysGetFlag(FL_MOVIE_CYCLIC_REC));
	UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovie_IconHideCyclicRec(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawHDR(VControl *pCtrl)
{
	UxState_SetData(pCtrl, STATE_CURITEM, SysGetFlag(FL_MOVIE_HDR));
	UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovie_IconHideHDR(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawMotionDet(void)
{
    if (1)//(UI_GetData(FL_MOVIE_MOTION_DET) == MOVIE_MOTIONDET_ON)
    {
        if (UI_GetData(FL_MOVIE_AUDIO) == MOVIE_AUDIO_ON) {
            UxCtrl_SetShow(&UIFlowWndMovie_Static_MotionDet1Ctrl, TRUE);
        } else {
            UxCtrl_SetShow(&UIFlowWndMovie_Static_MotionDet2Ctrl, TRUE);
        }
    }
    else
    {
        FlowMovie_IconHideMotionDet();
    }
}

void FlowMovie_IconHideMotionDet(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_Static_MotionDet1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_Static_MotionDet2Ctrl, FALSE);
}

void FlowMovie_IconDrawBattery(VControl *pCtrl)
{
	UxState_SetData(pCtrl, STATE_CURITEM, GetBatteryLevel());
	UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovie_IconHideBattery(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawDZoom(VControl *pCtrl)
{
	BOOL   bShow=0;
#if _TODO
#if (PHOTO_MODE==ENABLE)
	UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer(Get_DZoomRatioString()));
	bShow = (DZOOM_IDX_GET() > DZOOM_IDX_MIN()) ? TRUE : FALSE;
#endif
#endif
	UxCtrl_SetShow(pCtrl, bShow);
}

void FlowMovie_IconHideDZoom(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_DrawPIM(BOOL bDraw)
{
	UxCtrl_SetShow(&UIFlowWndMovie_StaticIcon_PIMCtrl, bDraw);
}

void FlowMovie_IconDrawSOS(void)
{
    INT8 gpsstatus;
    gpsstatus = GetGPSSignalStatus();
    if (gpsstatus < 0) {
        UxCtrl_SetShow(&UIFlowWndMovie_SOS1Ctrl, TRUE);	
    } else {
        UxCtrl_SetShow(&UIFlowWndMovie_SOSCtrl, TRUE);
    }
}

void FlowMovie_IconHideSOS(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_SOSCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_SOS1Ctrl, FALSE);
    FlowMovie_SetSOSStatusNow(FALSE);
}

void FlowMovie_IconDrawAudio(VControl *pCtrl)
{
    if (UI_GetData(FL_MOVIE_AUDIO) == MOVIE_AUDIO_ON) {
        UxState_SetData(&UIFlowWndMovie_Status_AudioCtrl, STATE_CURITEM, SysGetFlag(FL_MOVIE_AUDIO));
        UxCtrl_SetShow(&UIFlowWndMovie_Status_AudioCtrl, TRUE);
		#if 0
        if (UxCtrl_IsShow(&UIFlowWndMovie_Static_MotionDet2Ctrl)) {
            UxCtrl_SetShow(&UIFlowWndMovie_Static_MotionDet2Ctrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndMovie_Static_MotionDet1Ctrl, TRUE);
        }
        if (UxCtrl_IsShow(&UIFlowWndMovie_Static_TimeLapse2Ctrl)) {
            UxCtrl_SetShow(&UIFlowWndMovie_Static_TimeLapse2Ctrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndMovie_Static_TimeLapse1Ctrl, TRUE);
        }
		#endif
    } else {
        UxState_SetData(&UIFlowWndMovie_Status_AudioCtrl, STATE_CURITEM, SysGetFlag(FL_MOVIE_AUDIO));
        UxCtrl_SetShow(&UIFlowWndMovie_Status_AudioCtrl, TRUE);
		#if 0
        if (UxCtrl_IsShow(&UIFlowWndMovie_Static_MotionDet1Ctrl)) {
            UxCtrl_SetShow(&UIFlowWndMovie_Static_MotionDet2Ctrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndMovie_Static_MotionDet1Ctrl, FALSE);
        }
        if (UxCtrl_IsShow(&UIFlowWndMovie_Static_TimeLapse1Ctrl)) {
            UxCtrl_SetShow(&UIFlowWndMovie_Static_TimeLapse2Ctrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndMovie_Static_TimeLapse1Ctrl, FALSE);
        }
		#endif
    }
}

void FlowMovie_IconHideAudio(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawTimelapse(void)
{
	VControl *pCtrl = &UIFlowWndMovie_Static_TimeLapse1Ctrl;

    if (!isACCTrigParkMode) {
        UxCtrl_SetShow(&UIFlowWndMovie_Static_TimeLapse1Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_Static_TimeLapse2Ctrl, FALSE);
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
		break;*/ ////harrison ds315

    default:
    case PARKING_MODE_OFF:
        UxCtrl_SetShow(pCtrl, FALSE);
        break;
    }
	/*if((UI_GetData(FL_PARKING_MODE)) == PARKING_MODE_MOTION_GSENSOR_DET)
	{
		UxStatic_SetData(&UIFlowWndMovie_Static_TimeLapse2Ctrl,STATIC_VALUE,ICON_PARKINGMODE_MD);
		UxCtrl_SetShow(&UIFlowWndMovie_Static_TimeLapse2Ctrl, TRUE);
	}
	else
	{		
		UxCtrl_SetShow(&UIFlowWndMovie_Static_TimeLapse2Ctrl, FALSE);
	}*///////harrison ds315
}

void FlowMovie_IconHideTimelapse(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_Static_TimeLapse1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_Static_TimeLapse2Ctrl, FALSE);
}

void FlowMovie_DrawFolderCheck(BOOL bShow)
{
	if(bShow)
	{
		UxState_SetItemData(&UIFlowWndMovie_FolderCheck_StatusTxtCtrl, UIFlowWndMovie_FolderCheck_StatusTxt_STRID_FORMAT_WARNING1, STATE_ITEM_STRID, STRID_REAR_ERROR);
	}
    UxCtrl_SetShow(&UIFlowWndMovie_FolderCheck_StatusTxtCtrl, bShow);
}

void FlowMovie_DrawCustomerType(void)
{
    //UxStatic_SetData(&UIFlowWndMovie_CustomTypeCtrl, STATIC_VALUE, Txt_Pointer("PAPAGO! D1WiFi"));
    //UxCtrl_SetShow(&UIFlowWndMovie_CustomTypeCtrl, TRUE);
}

void FlowMovie_HideCustomerType(void)
{
    //UxCtrl_SetShow(&UIFlowWndMovie_CustomTypeCtrl, FALSE);
}


extern CHAR *Get_GpsSpeedString(void);
extern CHAR Speed1[32];
static UINT32 g_year = DEF_YEAR;
static UINT32 g_Count = 0;
extern INT8 uitpmsstatus;
extern BOOL GPS_UpdateDateTime;
#if defined(_GPS_EDOG_)
extern BOOL EdogFstCnetd;
BOOL g_GPS_PlaySound_onetime;
#elif defined(_GPS_EDOG_UNIQUE_SKY_)
extern BOOL EdogFstCnetd;
BOOL g_GPS_PlaySound_onetime;
#endif
void FlowMovie_IconDrawGPSSignal(void)
{
    INT8 gpsstatus;
    RMCINFO RMCInfo;
    struct tm Curr_DateTime = {0};

    if (UI_GetData(FL_GPS) == GPS_OFF)
    {
        UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCtrl,FALSE);
        UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCtrl,FALSE);
        UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCCtrl,FALSE);
    }
    else
    {
        Get_GpsSpeedString();
        gpsstatus = GetGPSSignalStatus();
        if (gpsstatus < 0)
        {
            g_Count = 0;
            //GPS_UpdateDateTime = FALSE;
            UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCtrl,FALSE);
            //UxStatic_SetData(&UIFlowWndMovie_GPSSignalCtrl,STATIC_VALUE,Txt_Pointer(Get_GpsSpeedString()));
            UxStatic_SetData(&UIFlowWndMovie_GPSSignalCtrl,STATIC_VALUE,Txt_Pointer(Speed1));
            UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCtrl,FALSE);
            UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCCtrl,FALSE);
            UxCtrl_SetShow(&UIFlowWndMovie_GPS_SMALL_ICON2Ctrl,FALSE);
            UxCtrl_SetShow(&UIFlowWndMovie_GPSN_SMALL_ICON2Ctrl,FALSE);
            //UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCtrl,TRUE);
            if(UxCtrl_IsShow(&UIFlowWndMovie_SOSCtrl))
            {
                UxCtrl_SetShow(&UIFlowWndMovie_SOS1Ctrl,TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_SOSCtrl,FALSE);
            }
        }
        else
        {
            if (gpsstatus == 1)
            {
                UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCCtrl,FALSE);
                UxStatic_SetData(&UIFlowWndMovie_GPSSignalCCCtrl,STATIC_VALUE,Txt_Pointer(Speed1));
                UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCtrl,FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCtrl,FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_GPS_SMALL_ICON2Ctrl,TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_GPSN_SMALL_ICON2Ctrl,FALSE);
                if (UxCtrl_IsShow(&UIFlowWndMovie_SOS1Ctrl))
                {
                    UxCtrl_SetShow(&UIFlowWndMovie_SOS1Ctrl,FALSE);
                    UxCtrl_SetShow(&UIFlowWndMovie_SOSCtrl,TRUE);
                }
                //UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCCtrl,TRUE);
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
                            hwclock_set_time(TIME_ID_CURRENT, Curr_DateTime, 0);
                            g_Count = 0;
                            //GPS_UpdateDateTime = TRUE;
                            //debug_err(("FlowMovie_GPS##= /%d/%d/%d %d:%d:%d\r\n",g_year,RMCInfo.Month,RMCInfo.Day,RMCInfo.Hour,RMCInfo.Minute,RMCInfo.Second));

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
                UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCtrl,FALSE);
                //UxStatic_SetData(&UIFlowWndMovie_GPSSignalCCtrl,STATIC_VALUE,Txt_Pointer(Get_GpsSpeedString()));
                UxStatic_SetData(&UIFlowWndMovie_GPSSignalCCtrl,STATIC_VALUE,Txt_Pointer(Speed1));
                UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCtrl,FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCCtrl,FALSE);
                //UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCtrl,TRUE);

                UxCtrl_SetShow(&UIFlowWndMovie_GPS_SMALL_ICON2Ctrl,FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_GPSN_SMALL_ICON2Ctrl,TRUE);
                if (UxCtrl_IsShow(&UIFlowWndMovie_SOS1Ctrl))
                {
                    UxCtrl_SetShow(&UIFlowWndMovie_SOS1Ctrl,FALSE);
                    UxCtrl_SetShow(&UIFlowWndMovie_SOSCtrl,TRUE);
                }
            }
        }
    }
    Ux_Redraw();
}

void FlowMovie_IconHideGPSSignal(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCCtrl, FALSE);
}

void FlowMovie_IconDrawSNG(void)
{
    INT8 gpsstatus;
    gpsstatus = GetGPSSignalStatus();
    if (gpsstatus < 0) {
        if (UxCtrl_IsShow(&UIFlowWndMovie_SOS1Ctrl)) {
            UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICON1Ctrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICON2Ctrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICONCtrl, FALSE);
        } else {
            UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICONCtrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICON1Ctrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICON2Ctrl, FALSE);
        }
    } else {
        if (UxCtrl_IsShow(&UIFlowWndMovie_SOSCtrl)) {
            UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICON2Ctrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICONCtrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICON1Ctrl, FALSE);
        } else {
            UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICON1Ctrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICON2Ctrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICONCtrl, FALSE);
        }
    }
}
void FlowMovie_IconHideSNG(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICONCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICON1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICON2Ctrl, FALSE);
}

void FlowMovie_IconDrawTSR(void)
{
    INT8 gpsstatus;
    gpsstatus = GetGPSSignalStatus();
    if (gpsstatus < 0) {
        if (UxCtrl_IsShow(&UIFlowWndMovie_SOS1Ctrl)) {
            if (UxCtrl_IsShow(&UIFlowWndMovie_SNG_SMALL_ICON1Ctrl)) {
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICONCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON2Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideRL();
            } else {
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICONCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideRL();
            }
        } else {
            if (UxCtrl_IsShow(&UIFlowWndMovie_SNG_SMALL_ICONCtrl)) {
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICONCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideRL();
            } else {
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICONCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON1Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideRL();
            }
        }
    } else {
        if (UxCtrl_IsShow(&UIFlowWndMovie_SOSCtrl)) {
            if (UxCtrl_IsShow(&UIFlowWndMovie_SNG_SMALL_ICON2Ctrl)) {
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICONCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON3Ctrl, TRUE);
                FlowMovie_IconHideRL();
            } else {
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICONCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON2Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideRL();
            }
        } else {
            if (UxCtrl_IsShow(&UIFlowWndMovie_SNG_SMALL_ICON1Ctrl)) {
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICONCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON2Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideRL();
            } else {
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICONCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideRL();
            }
        }
    }
}
void FlowMovie_IconHideTSR(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICONCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON2Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON3Ctrl, FALSE);
}

void FlowMovie_IconDrawRL(void)
{
    INT8 gpsstatus;
    gpsstatus = GetGPSSignalStatus();
    if (gpsstatus < 0) {
        if (UxCtrl_IsShow(&UIFlowWndMovie_SOS1Ctrl)) {
            if (UxCtrl_IsShow(&UIFlowWndMovie_SNG_SMALL_ICON1Ctrl)) {
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICONCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON2Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideTSR();
            } else {
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICONCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideTSR();
            }
        } else {
            if(UxCtrl_IsShow(&UIFlowWndMovie_SNG_SMALL_ICONCtrl)) {
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICONCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideTSR();
            } else {
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICONCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON1Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideTSR();
            }
        }
    } else {
        if (UxCtrl_IsShow(&UIFlowWndMovie_SOSCtrl)) {
            if (UxCtrl_IsShow(&UIFlowWndMovie_SNG_SMALL_ICON2Ctrl)) {
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICONCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON3Ctrl, TRUE);
                FlowMovie_IconHideTSR();
            } else {
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICONCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON2Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideTSR();
            }
        } else {
            if (UxCtrl_IsShow(&UIFlowWndMovie_SNG_SMALL_ICON1Ctrl)) {
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICONCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON2Ctrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideTSR();
            } else {
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICONCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON1Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON2Ctrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON3Ctrl, FALSE);
                FlowMovie_IconHideTSR();
            }
        }
    }
}
void FlowMovie_IconHideRL(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICONCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON2Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON3Ctrl, FALSE);
}

void FlowMovie_initIcon(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_FolderCheck_StatusTxtCtrl, FALSE);
    //UxCtrl_SetShow(&UIFlowWndMovie_SOS_BIGCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_YMD_StaticCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_HMS_StaticCtrl, FALSE);
    //UxCtrl_SetShow(&UIFlowWndMovie_CustomerTypeCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_Status_MotionDetCtrl, FALSE);    
    UxCtrl_SetShow(&UIFlowWndMovie_Static_MotionDet1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_Static_MotionDet2Ctrl, FALSE);	
    UxCtrl_SetShow(&UIFlowWndMovie_Static_TimeLapse1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_Static_TimeLapse1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_GPS_SMALL_ICON2Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_GPSN_SMALL_ICON2Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICONCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON2Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_TSR_SMALL_ICON3Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICON1Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_SNG_SMALL_ICON2Ctrl,FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICONCtrl, FALSE);	
    UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON1Ctrl, FALSE);	
    UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON2Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_RL_SMALL_ICON3Ctrl, FALSE);
}

void FlowMovie_IconDrawADASAnimation(void)
{
	static UINT32 i = ICON_ADAS_ANIMATION_01;
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_AnimationCtrl,FALSE);
	if(i>=ICON_ADAS_ANIMATION_01 &&i<=ICON_ADAS_ANIMATION_07)
	{
		UxStatic_SetData(&UIFlowWndMovie_ADAS_Car_AnimationCtrl, STATIC_VALUE, i);
	}
	else
	{
		i = ICON_ADAS_ANIMATION_01;
		UxStatic_SetData(&UIFlowWndMovie_ADAS_Car_AnimationCtrl, STATIC_VALUE, i);
	}
	i++;
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_AnimationCtrl,TRUE);
}
UINT32 FlowWndMovie_DrawADASDisNum(UINT32 Value)
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

void FlowMovie_IconDrawADASDistance(UINT32 distance)
{
	UINT32 uiN0 = 0,uiN1 = 0;

	uiN0 = (distance%10);
	uiN1 = ((distance%100)/10);

	UxStatic_SetData(&UIFlowWndMovie_ADAS_Distance_Num0Ctrl,STATIC_VALUE,FlowWndMovie_DrawADASDisNum(uiN1));
    UxStatic_SetData(&UIFlowWndMovie_ADAS_Distance_Num1Ctrl,STATIC_VALUE,FlowWndMovie_DrawADASDisNum(uiN0));
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Distance_Num0Ctrl,TRUE);
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Distance_Num1Ctrl,TRUE);
}
void FlowMovie_IconHideADASDistance(void)
{
	UxStatic_SetData(&UIFlowWndMovie_ADAS_Distance_Num0Ctrl,STATIC_VALUE,ICON_ADAS_00);
    UxStatic_SetData(&UIFlowWndMovie_ADAS_Distance_Num1Ctrl,STATIC_VALUE,ICON_ADAS_00);
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Distance_Num0Ctrl,TRUE);
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Distance_Num1Ctrl,TRUE);
}


void FlowMovie_IconDrawADASDisplayType(UINT32 id)
{
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_TypeCtrl,FALSE);
	switch(id)
	{
		case ADAS_ALARM_LD_LEFT:
			UxStatic_SetData(&UIFlowWndMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_LANE_LEFT);
			break;
			
		case ADAS_ALARM_LD_RIGHT:
			UxStatic_SetData(&UIFlowWndMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_LANE_RIGHT);
			break;
			
		case ADAS_ALARM_FC:
			UxStatic_SetData(&UIFlowWndMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_FRONT_ALERT);
			break;

		case ADAS_ALARM_GO:
			UxStatic_SetData(&UIFlowWndMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_GO_ALERT);
			break;

		case ADAS_ALARM_FPW:
			UxStatic_SetData(&UIFlowWndMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_PEOPLE_ALERT);
			break;

		case ADAS_ALARM_VIRTUAL_BUMPERS:
			UxStatic_SetData(&UIFlowWndMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_VIRTUAL_BUMPER);
			break;

		case ADAS_ALARM_RCW_REAR:
			UxStatic_SetData(&UIFlowWndMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_REAR_ALERT);
			break;

		case ADAS_ALARM_LCA_LEFT:
			UxStatic_SetData(&UIFlowWndMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_CHANGE_LANE_LEFT);
			break;

		case ADAS_ALARM_LCA_RIGHT:
			UxStatic_SetData(&UIFlowWndMovie_ADAS_TypeCtrl, STATIC_VALUE, ICON_ADAS_CHANGE_LANE_RIGHT);
			break;

		default:
			break;
	}
	
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_TypeCtrl,TRUE);
}
void FlowMovie_IconHideADASDisplayType(void)
{
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_TypeCtrl,FALSE);
}

AlgoEventData adas_eventData_app = {0};

AlgoEventData rcw_eventData_app = {0};
extern pthread_mutex_t g_data_mutex_front ;
extern pthread_mutex_t g_data_mutex_rear ;
void FlowMovie_IconDrawADASHideCar(void)
{
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_00Ctrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_01Ctrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_02Ctrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_03Ctrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_04Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_05Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_06Ctrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Red_01Ctrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Red_00Ctrl, FALSE);
}

void FlowMovie_IconDrawADASUpdateCar(void)
#if 1
{
	AlgoEventData adas_eventData_app00 = {0};
	AlgoEventData rcw_eventData_app01 = {0};

	if (pthread_mutex_trylock(&g_data_mutex_front) == 0) {
		memcpy(&adas_eventData_app00, &adas_eventData_app, sizeof(adas_eventData_app));
		pthread_mutex_unlock(&g_data_mutex_front);

		// 只隐藏前路控件（4蓝1红）
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_00Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_01Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_02Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_03Ctrl, FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Red_00Ctrl, FALSE);
		
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
				car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Red_00Ctrl;
				front_red_shown = TRUE;
				if(ICON_ADAS_REAR_ALERT != UxStatic_GetData(&UIFlowWndMovie_ADAS_TypeCtrl, STATIC_VALUE)){
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
					case 0: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_00Ctrl; break;
					case 1: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_01Ctrl; break;
					case 2: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_02Ctrl; break;
					case 3: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_03Ctrl; break;
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
	    UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_04Ctrl, FALSE);
	    UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_05Ctrl, FALSE);
	    UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Blue_06Ctrl, FALSE);
	    UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Car_Red_01Ctrl, FALSE);
	    
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
	                        car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Red_01Ctrl;
	                        rear_red_shown = TRUE;
							
							if(ICON_ADAS_REAR_ALERT == UxStatic_GetData(&UIFlowWndMovie_ADAS_TypeCtrl, STATIC_VALUE))
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
	                            case 0: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_04Ctrl; break;
	                            case 1: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_05Ctrl; break;
	                            case 2: car_ctrl = (VControl*)&UIFlowWndMovie_ADAS_Car_Blue_06Ctrl; break;
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


	

void FlowMovie_UpdateIcons(BOOL bShow)
{
	if ((bShow == FALSE) || (SysGetFlag(FL_LCD_DISPLAY) == DISPOUT_OFF)) {
		//FlowMovie_IconHideDscMode(&UIFlowWndMovie_Static_cameraCtrl);
		FlowMovie_IconHideSize(&UIFlowWndMovie_Static_resolutionCtrl);
        FlowMovie_IconHideRecTime(&UIFlowWndMovie_Static_timeCtrl);
		FlowMovie_IconHideMaxRecTime(&UIFlowWndMovie_Static_maxtimeCtrl);
		FlowMovie_IconHideRec(&UIFlowWndMovie_PanelCtrl);
		FlowMovie_IconHideStorage(&UIFlowWndMovie_Status_StorageCtrl);
		FlowMovie_IconHideCyclicRec(&UIFlowWndMovie_Status_CyclicRecCtrl);
		//FlowMovie_IconHideHDR(&UIFlowWndMovie_Status_HDRCtrl);
		FlowMovie_IconHideMotionDet();
		FlowMovie_IconHideDZoom(&UIFlowWndMovie_Zoom_StaticCtrl);
		FlowMovie_IconHideBattery(&UIFlowWndMovie_Status_batteryCtrl);
		//FlowMovie_IconHideEV(&UIFlowWndMovie_StatusICN_EVCtrl);
        FlowMovie_IconHideSOS();
        FlowMovie_IconHideAudio(&UIFlowWndMovie_Status_AudioCtrl);
        FlowMovie_IconHideTimelapse();
		FlowMovie_IconHideDateTime();
		FlowMovie_DrawPIM(FALSE);
        FlowMovie_DrawFolderCheck(FALSE);
        FlowMovie_HideCustomerType();
        FlowMovie_IconHideGPSSignal();
		FlowMovie_IconHideADASDisplayType();
	} else {
		//FlowMovie_IconDrawDscMode(&UIFlowWndMovie_Static_cameraCtrl);
		FlowMovie_IconDrawSize(&UIFlowWndMovie_Static_resolutionCtrl);
        if (gMovData.State != MOV_ST_REC) {
            FlowMovie_IconHideRecTime(&UIFlowWndMovie_Static_timeCtrl);
    		FlowMovie_IconDrawMaxRecTime(&UIFlowWndMovie_Static_maxtimeCtrl);
        }
		FlowMovie_IconHideRec(&UIFlowWndMovie_PanelCtrl);
		FlowMovie_IconHideStorage(&UIFlowWndMovie_Status_StorageCtrl);
		FlowMovie_IconHideCyclicRec(&UIFlowWndMovie_Status_CyclicRecCtrl);
		//FlowMovie_IconDrawHDR(&UIFlowWndMovie_Status_HDRCtrl);
		FlowMovie_IconHideDZoom(&UIFlowWndMovie_Zoom_StaticCtrl);
		FlowMovie_IconHideBattery(&UIFlowWndMovie_Status_batteryCtrl);
		//FlowMovie_IconDrawEV(&UIFlowWndMovie_StatusICN_EVCtrl);
        if (gMovData.State != MOV_ST_REC) {
            FlowMovie_IconHideSOS();
        }
        FlowMovie_IconDrawAudio(&UIFlowWndMovie_Status_AudioCtrl);
		FlowMovie_IconDrawDateTime();
		FlowMovie_DrawPIM(FALSE);
        FlowMovie_DrawFolderCheck(FALSE);
        FlowMovie_HideCustomerType();
		#if 1
		FlowMovie_IconHideMotionDet();
		FlowMovie_IconDrawTimelapse();//just for park mode
		#else
        //if ((SysGetFlag(FL_MOVIE_MOTION_DET) == MOVIE_MOTIONDET_OFF)&&(UI_GetData(FL_MOVIE_TIMELAPSE_REC) != MOVIE_TIMELAPSEREC_OFF)) {  //time lapse
        if ((SysGetFlag(FL_MOVIE_REC_MODE) == MOVIE_REC_MODE_ONEFRAM)) {  //time lapse
            FlowMovie_IconHideMotionDet();
            FlowMovie_IconDrawTimelapse();
        //} else if ((SysGetFlag(FL_MOVIE_MOTION_DET) == MOVIE_MOTIONDET_ON)&&(UI_GetData(FL_MOVIE_TIMELAPSE_REC) == MOVIE_TIMELAPSEREC_OFF)) {  //motion det
        } else if ((SysGetFlag(FL_MOVIE_REC_MODE) == MOVIE_REC_MODE_MOTIONDET)) {  //motion det
            FlowMovie_IconHideTimelapse();
            FlowMovie_IconDrawMotionDet();
        } else {
        	if((SysGetFlag(FL_PARKING_MODE_TIMELAPSE_REC) != PARKING_MODE_TIMELAPSEREC_OFF)||(UI_GetData(FL_MOVIE_TIMELAPSE_REC) != MOVIE_TIMELAPSEREC_OFF)){
				FlowMovie_IconHideMotionDet();
				FlowMovie_IconDrawTimelapse();
			}else{
            	FlowMovie_IconHideMotionDet();
            	FlowMovie_IconHideTimelapse();
			}
        }
        //FlowMovie_IconDrawGPSSignal();
		#endif
		FlowMovie_IconHideADASDisplayType();
	}
}

