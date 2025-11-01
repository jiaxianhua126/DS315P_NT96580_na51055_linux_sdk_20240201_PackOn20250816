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
void FlowMovie_IconDrawGPSSignal(void)
{
    INT8 gpsstatus;
    RMCINFO RMCInfo;
    //struct tm Curr_DateTime = {0};

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
						#if 0///harrison ds315
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
							//HwClock_SetTime(TIME_ID_CURRENT, Curr_DateTime, 0); 
                            g_Count = 0;
                            //GPS_UpdateDateTime = TRUE;
                            //debug_err(("FlowMovie_GPS##= /%d/%d/%d %d:%d:%d\r\n",g_year,RMCInfo.Month,RMCInfo.Day,RMCInfo.Hour,RMCInfo.Minute,RMCInfo.Second));

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
	}
}

