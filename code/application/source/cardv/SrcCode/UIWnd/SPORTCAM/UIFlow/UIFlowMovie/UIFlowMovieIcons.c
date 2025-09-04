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
	[MOVIE_SIZE_FRONT_2560x1440P60] = "1440P60",
	[MOVIE_SIZE_FRONT_2560x1440P30] = "1440P30",
	[MOVIE_SIZE_FRONT_2304x1296P60] = "1296P60",
	[MOVIE_SIZE_FRONT_2304x1296P30] = "1296P30",
	[MOVIE_SIZE_FRONT_1920x1080P60] = "1080P60",
	[MOVIE_SIZE_FRONT_1920x1080P30] = "1080P30",	
	[MOVIE_SIZE_FRONT_3840x2160P30] = "4KP30",
	[MOVIE_SIZE_DUAL_2560x1440P30_1920x1080P30] = "1440P30+1080P30",
	[MOVIE_SIZE_FRONT_1280x720P120] = "HD P120",
	[MOVIE_SIZE_FRONT_1280x720P240] = "HD P240",
	[MOVIE_SIZE_FRONT_1280x720P60] = "HD P60",
	[MOVIE_SIZE_FRONT_1280x720P30] = "HD P30",
	[MOVIE_SIZE_FRONT_848x480P30] = "WVGA P30",
	[MOVIE_SIZE_FRONT_640x480P240] = "VGA P240",
	[MOVIE_SIZE_FRONT_640x480P30] = "VGA P30",
	[MOVIE_SIZE_FRONT_320x240P30] = "QVGA P30",
	[MOVIE_SIZE_DUAL_3840x2160P30_1920x1080P30] = "UHD P30+FHD P30",
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
};
#else
static CHAR    *resolution_Buf[MOVIE_SIZE_ID_MAX] = {
	[MOVIE_SIZE_FRONT_2560x1440P60] = "1440P55",
	[MOVIE_SIZE_FRONT_2560x1440P30] = "1440P27.5",
	[MOVIE_SIZE_FRONT_2304x1296P60] = "1296P55",
	[MOVIE_SIZE_FRONT_2304x1296P30] = "1296P27.5",
	[MOVIE_SIZE_FRONT_1920x1080P60] = "1080P55",
	[MOVIE_SIZE_FRONT_1920x1080P30] = "1080P27.5",	
	[MOVIE_SIZE_FRONT_3840x2160P30] = "4KP27.5",
	[MOVIE_SIZE_DUAL_2560x1440P30_1920x1080P30] = "1440P27.5+1080P27.5",
	[MOVIE_SIZE_FRONT_1280x720P120] = "HD P110",
	[MOVIE_SIZE_FRONT_1280x720P240] = "HD P220",
	[MOVIE_SIZE_FRONT_1280x720P60] = "HD P55",
	[MOVIE_SIZE_FRONT_1280x720P30] = "HD P27.5",
	[MOVIE_SIZE_FRONT_848x480P30] = "WVGA P27.5",
	[MOVIE_SIZE_FRONT_640x480P240] = "VGA P240",
	[MOVIE_SIZE_FRONT_640x480P30] = "VGA P27.5",
	[MOVIE_SIZE_FRONT_320x240P30] = "QVGA P27.5",
	[MOVIE_SIZE_DUAL_3840x2160P30_1920x1080P30] = "UHD P30+FHD P30",
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

	if (System_GetState(SYS_STATE_CARD)  == CARD_REMOVED) {
		snprintf(g_RecMaxTimeStr, 20, "%02d:%02d",0, 0);
	} else {
		snprintf(g_RecMaxTimeStr, 20, "%02d:%02d",(g_RecMaxTime % 3600) / 60, (g_RecMaxTime % 3600) % 60);
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
		snprintf(g_RecCurrTimeStr, 20, "%02d:%02d",/* g_RecCurrTime / 3600, */(g_RecCurrTime % 3600) / 60, (g_RecCurrTime % 3600) % 60);
		UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer(g_RecCurrTimeStr));
		UxCtrl_SetShow(pCtrl, TRUE);
		break;
        case MOV_ST_REC_WAIT:
        g_RecCurrTime = 0;
        memset((void *)g_RecCurrTimeStr, 0, sizeof(g_RecCurrTimeStr));
        snprintf(g_RecCurrTimeStr, 20, "%02d:%02d",/* g_RecCurrTime/3600,*/(g_RecCurrTime%3600)/60, (g_RecCurrTime%3600)%60);
        UxStatic_SetData(pCtrl,STATIC_VALUE,Txt_Pointer(g_RecCurrTimeStr));
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
    switch(SysGetFlag(FL_DATE_FORMAT))
    {
       case DATE_FORMAT_DMY:
           snprintf(date_str, 20, "%02d/%02d/%04d", Curr_DateTime.tm_mday, Curr_DateTime.tm_mon, Curr_DateTime.tm_year);
           break;

       case DATE_FORMAT_MDY:
           snprintf(date_str, 20, "%02d/%02d/%04d", Curr_DateTime.tm_mon, Curr_DateTime.tm_mday,Curr_DateTime.tm_year);
           break;

       case DATE_FORMAT_YMD:
       default:
           snprintf(date_str, 20, "%04d/%02d/%02d", Curr_DateTime.tm_year, Curr_DateTime.tm_mon, Curr_DateTime.tm_mday);
           break;
    }
	snprintf(time_str, 20, "%02d:%02d:%02d", Curr_DateTime.tm_hour, Curr_DateTime.tm_min, Curr_DateTime.tm_sec);
    UxStatic_SetData(&UIFlowWndMovie_YMD_StaticCtrl,STATIC_VALUE,Txt_Pointer(date_str));
    UxStatic_SetData(&UIFlowWndMovie_HMS_StaticCtrl,STATIC_VALUE,Txt_Pointer(time_str));
    UxCtrl_SetShow(&UIFlowWndMovie_YMD_StaticCtrl,TRUE);
    UxCtrl_SetShow(&UIFlowWndMovie_HMS_StaticCtrl,TRUE);
}

void FlowMovie_IconHideDateTime(void)
{
	UxCtrl_SetShow(&UIFlowWndMovie_YMD_StaticCtrl, FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_HMS_StaticCtrl, FALSE);
}

void FlowMovie_IconDrawRec(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl,TRUE);
}

void FlowMovie_IconHideRec(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl,FALSE);
}

void FlowMovie_IconDrawSize(VControl *pCtrl)
{
    //DBG_DUMP("%s: SysGetFlag(FL_MOVIE_SIZE) = %d\r\n", __func__, SysGetFlag(FL_MOVIE_SIZE));
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

//		  case MOVIE_SIZE_FRONT_1280x720P120:
//			  UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P120+1440P30"));
//			  break;
//		  case MOVIE_SIZE_FRONT_1280x720P60:
//			  UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P60+1440P30"));
//			  break;
//		  case MOVIE_SIZE_FRONT_1280x720P30:
 // 		 UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P30+1440P30"));
//			 break;
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

//		  case MOVIE_SIZE_FRONT_1280x720P120:
//			  UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P110+1080P27.5"));
//			  break;
//		  case MOVIE_SIZE_FRONT_1280x720P60:
//			  UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720P55+1080P27.5"));
//			  break;
//		  case MOVIE_SIZE_FRONT_1280x720P30:
 // 		 UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("720Pv+1080P27.5"));
//			 break;
		default:
			UxStatic_SetData(pCtrl, STATIC_VALUE, Txt_Pointer("1440P27.5+1080P27.5"));
			break;			  
		}
	}
	#endif
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
#if 0
	/* Update status item data */
	if (System_GetState(SYS_STATE_CARD)  == CARD_REMOVED) {
        UxState_SetData(pCtrl,STATE_CURITEM,UIFlowWndMovie_Status_Storage_ICONID_NULL);
	} else if (System_GetState(SYS_STATE_CARD)  == CARD_LOCKED) {
		UxState_SetData(pCtrl, STATE_CURITEM, UIFlowWndMovie_Status_Storage_ICON_SD_LOCK);
	} else {
		UxState_SetData(pCtrl, STATE_CURITEM, UIFlowWndMovie_Status_Storage_ICON_SD_CARD);
	}
#endif
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
#if 1//(SHDR_FUNC == ENABLE)
	UxState_SetItemData(pCtrl, UIFlowWndMovie_Status_HDR_ICON_MENU_HDR, STATE_ITEM_ICONID, ICON_MENU_HDR);
	UxState_SetData(pCtrl, STATE_CURITEM, SysGetFlag(FL_MOVIE_HDR));
#else
	UxState_SetItemData(pCtrl, UIFlowWndMovie_Status_HDR_ICON_MENU_HDR, STATE_ITEM_ICONID, ICON_MENU_WDR);
	UxState_SetData(pCtrl, STATE_CURITEM, SysGetFlag(FL_MOVIE_WDR));
#endif
	UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovie_IconHideHDR(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawMotionDet(VControl *pCtrl)
{
	UxState_SetData(pCtrl, STATE_CURITEM, SysGetFlag(FL_MOVIE_MOTION_DET));
	UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovie_IconHideMotionDet(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovie_IconDrawBattery(VControl *pCtrl)
{
	////UxState_SetData(pCtrl, STATE_CURITEM, GetBatteryLevel());
	UxState_SetData(pCtrl, STATE_CURITEM, BATTERY_FULL);
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
    UxCtrl_SetShow(pCtrl,FALSE);
}

void FlowMovie_DrawPIM(BOOL bDraw)
{
    UxCtrl_SetShow(&UIFlowWndMovie_StaticIcon_PIMCtrl, bDraw);
}

void FlowMovie_IconDrawSOS(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl,TRUE);
}

void FlowMovie_IconHideSOS(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl,FALSE);
    FlowMovie_SetSOSStatusNow(FALSE);
}

void FlowMovie_IconDrawAudio(VControl *pCtrl)
{
    UxState_SetData(pCtrl,STATE_CURITEM,SysGetFlag(FL_MOVIE_AUDIO));
    UxCtrl_SetShow(pCtrl,TRUE);
}

void FlowMovie_IconHideAudio(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl,FALSE);
}

void FlowMovie_IconDrawTimelapse(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl,TRUE);
}

void FlowMovie_IconHideTimelapse(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl,FALSE);
}

void FlowMovie_DrawFolderCheck(BOOL bShow)
{
	if(bShow)
	{
		UxState_SetItemData(&UIFlowWndMovie_FolderCheck_StatusTxtCtrl, UIFlowWndMovie_FolderCheck_StatusTxt_STRID_FORMAT_WARNING1, STATE_ITEM_STRID, STRID_REAR_ERROR);
	}

    UxCtrl_SetShow(&UIFlowWndMovie_FolderCheck_StatusTxtCtrl,bShow);
}

void FlowMovie_HideFolderCheck(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_FolderCheck_StatusTxtCtrl,FALSE);
}

void FlowMovie_DrawCustomerType(void)
{
    UxStatic_SetData(&UIFlowWndMovie_CustomTypeCtrl,STATIC_VALUE,Txt_Pointer("ME206G"));
    UxCtrl_SetShow(&UIFlowWndMovie_CustomTypeCtrl,TRUE);
}

void FlowMovie_HideCustomerType(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_CustomTypeCtrl,FALSE);
}
#if 1
extern CHAR *Get_GpsSpeedString(void);
extern char *GPS_OSDSpeedData(void);
extern CHAR Speed1[32];
extern CHAR GPSSpeedData[32];
static UINT32 g_year = DEF_YEAR;
static UINT32 g_Count = 0;
extern BOOL GPS_UpdateDateTime;
BOOL g_GPS_PlaySound_onetime = FALSE;
#endif
void FlowMovie_IconDrawGPSSignal(void)
{
	#if 1
    //static UINT32 g_year = 2019;
    //static UINT32 g_Count = 0;
    INT8 gpsstatus = 0;
    RMCINFO RMCInfo;
    struct tm Curr_DateTime = {0};
	static UINT8 compassUpdate_cnt = 0;

    if (UI_GetData(FL_GPS) == GPS_OFF)
    {
        g_Count = 0;
        UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCtrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCtrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCCtrl, FALSE);
        UxCtrl_SetShow(&UIFlowWndMovie_GPSCtrl, FALSE);
		FlowMovie_IconHideCompass();
    }
    else
    {
        Get_GpsSpeedString();
        GPS_OSDSpeedData();
        gpsstatus = GetGPSSignalStatus();
        if(gpsstatus<0)
        {
            //if (GPS_UpdateDateTime)
            {
                g_Count = 0;
                //GPS_UpdateDateTime = FALSE;
            }
            UxStatic_SetData(&UIFlowWndMovie_GPSSignalCtrl, STATIC_VALUE, Txt_Pointer("No GPS"));//Speed1
            UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCtrl, TRUE);
            UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCtrl, FALSE);
            UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCCtrl, FALSE);
            UxState_SetData(&UIFlowWndMovie_GPSCtrl, STATE_CURITEM, UIFlowWndMovie_GPS_ICONID_NULL);
            UxCtrl_SetShow(&UIFlowWndMovie_GPSCtrl, FALSE);
			FlowMovie_IconHideCompass();
        }
        else
        {
            if (gpsstatus)
            {
                UxStatic_SetData(&UIFlowWndMovie_GPSSignalCCCtrl, STATIC_VALUE, Txt_Pointer(GPSSpeedData));//Speed1
                UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCCtrl, TRUE);
                UxState_SetData(&UIFlowWndMovie_GPSCtrl, STATE_CURITEM, UIFlowWndMovie_GPS_ICON_GPS_ON);
				++compassUpdate_cnt;
				if(compassUpdate_cnt%10==0)
				{
					FlowMovie_IconDrawCompass();
				}
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
                            UISound_Play(DEMOSOUND_SOUND_EP5_TONE_GPS_OK);
                            g_GPS_PlaySound_onetime = TRUE;
                        }
						#endif
                        //rtc_waitCSETDone();
                        //debug_err(("FlowMovie_GPS= %d %d %d %d \r\n",RMCInfo.Year,RMCInfo.Hour,RMCInfo.Day,g_Count));
                        g_year = 2000 + RMCInfo.Year;

                        //rtc_setDate(RMCInfo.Year, RMCInfo.Month, RMCInfo.Day);
                        if (g_Count%10 == 0)
                        {
                            Curr_DateTime.tm_year = g_year;
                            Curr_DateTime.tm_mon = RMCInfo.Month;
                            Curr_DateTime.tm_mday = RMCInfo.Day;
                            Curr_DateTime.tm_hour = RMCInfo.Hour;
                            Curr_DateTime.tm_min = RMCInfo.Minute;
                            Curr_DateTime.tm_sec = RMCInfo.Second;
                            GxTime_SetTime(Curr_DateTime);
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
                    }
                }
            }
            else //if(gpsstatus==0)
            {
                //if (GPS_UpdateDateTime)
                {
                    g_Count = 0;
                    //GPS_UpdateDateTime = FALSE;
                }
                UxStatic_SetData(&UIFlowWndMovie_GPSSignalCCtrl, STATIC_VALUE, Txt_Pointer(GPSSpeedData));//Speed1
                UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCtrl, FALSE);
                UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCtrl, TRUE);
                UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCCtrl, FALSE);
                UxState_SetData(&UIFlowWndMovie_GPSCtrl, STATE_CURITEM, UIFlowWndMovie_GPS_ICON_GPS_OFF);
            }
            UxCtrl_SetShow(&UIFlowWndMovie_GPSCtrl, TRUE);
        }
        Ux_Redraw();
    }
	#endif
}

void FlowMovie_IconHideGPSSignal(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_GPSSignalCCCtrl, FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_GPSCtrl, FALSE);
}

void FlowMovie_IconDrawTPMS(void)
{
   //if( UI_GetData(FL_MOVIE_FCW)==MOVIE_FCW_ON)
   UxState_SetData(&UIFlowWndMovie_StatusIcon_TPMSCtrl, STATE_CURITEM,UIFlowWndMovie_StatusIcon_TPMS_ICON_TPMS_ALARM);
   UxCtrl_SetShow(&UIFlowWndMovie_StatusIcon_TPMSCtrl, TRUE);
}

void FlowMovie_IconHideTPMS(void)
{
   UxCtrl_SetShow(&UIFlowWndMovie_StatusIcon_TPMSCtrl, FALSE);
}

void FlowMovie_IconDrawCompass(void)
{
	switch(GPSRec_getAngle())
	{
		case NORTH_EAST:
			UxState_SetData(&UIFlowWndMovie_StatusIcon_CompassCtrl,STATE_CURITEM,UIFlowWndMovie_StatusIcon_Compass_ICON_NORTH_EAST);
			break;
		case EAST:
			UxState_SetData(&UIFlowWndMovie_StatusIcon_CompassCtrl,STATE_CURITEM,UIFlowWndMovie_StatusIcon_Compass_ICON_EAST);
			break;
		case SOUTH_EAST:
			UxState_SetData(&UIFlowWndMovie_StatusIcon_CompassCtrl,STATE_CURITEM,UIFlowWndMovie_StatusIcon_Compass_ICON_SOUTH_EAST);
			break;
		case SOUTH:
			UxState_SetData(&UIFlowWndMovie_StatusIcon_CompassCtrl,STATE_CURITEM,UIFlowWndMovie_StatusIcon_Compass_ICON_SOUTH);
			break;
		case SOUTH_WEST:
			UxState_SetData(&UIFlowWndMovie_StatusIcon_CompassCtrl,STATE_CURITEM,UIFlowWndMovie_StatusIcon_Compass_ICON_SOUTH_WEST);
			break;
		case WEST:
			UxState_SetData(&UIFlowWndMovie_StatusIcon_CompassCtrl,STATE_CURITEM,UIFlowWndMovie_StatusIcon_Compass_ICON_WEST);
			break;
		case NORTH_WEST:
			UxState_SetData(&UIFlowWndMovie_StatusIcon_CompassCtrl,STATE_CURITEM,UIFlowWndMovie_StatusIcon_Compass_ICON_NORTH_WEST);
			break;
		case NORTH:
			UxState_SetData(&UIFlowWndMovie_StatusIcon_CompassCtrl,STATE_CURITEM,UIFlowWndMovie_StatusIcon_Compass_ICON_NORTH);
			break;
		default:
			UxState_SetData(&UIFlowWndMovie_StatusIcon_CompassCtrl,STATE_CURITEM,UIFlowWndMovie_StatusIcon_Compass_ICONID_NULL);
			break;
	}
   UxCtrl_SetShow(&UIFlowWndMovie_StatusIcon_CompassCtrl, TRUE);
}

void FlowMovie_IconHideCompass(void)
{
   UxCtrl_SetShow(&UIFlowWndMovie_StatusIcon_CompassCtrl, FALSE);
}

//ADD Below Begin
#if 0//(GPS_PANEL_FUNC==ENABLE)
UINT32 FlowWndMovie_DrawDateNum(UINT32 Value)
{
	UINT32 ICON_ID = ICONID_NULL;

	switch(Value)
	{
	case 0:
		ICON_ID =ICON_DATE_0;
		break;
	case 1:
		ICON_ID =ICON_DATE_1;
		break;
	case 2:
		ICON_ID =ICON_DATE_2;
		break;
	case 3:
		ICON_ID =ICON_DATE_3;
		break;
	case 4:
		ICON_ID =ICON_DATE_4;
		break;
	case 5:
		ICON_ID =ICON_DATE_5;
		break;
	case 6:
		ICON_ID =ICON_DATE_6;
		break;
	case 7:
		ICON_ID =ICON_DATE_7;
		break;
	case 8:
		ICON_ID =ICON_DATE_8;
		break;
	case 9:
		ICON_ID =ICON_DATE_9;
		break;
	}

	return ICON_ID;
}

UINT32 FlowWndMovie_DrawTimeNum(UINT32 Value)
{
	UINT32 ICON_ID = ICONID_NULL;

	switch(Value)
	{
	case 0:
		ICON_ID =ICON_TIME_0;
		break;
	case 1:
		ICON_ID =ICON_TIME_1;
		break;
	case 2:
		ICON_ID =ICON_TIME_2;
		break;
	case 3:
		ICON_ID =ICON_TIME_3;
		break;
	case 4:
		ICON_ID =ICON_TIME_4;
		break;
	case 5:
		ICON_ID =ICON_TIME_5;
		break;
	case 6:
		ICON_ID =ICON_TIME_6;
		break;
	case 7:
		ICON_ID =ICON_TIME_7;
		break;
	case 8:
		ICON_ID =ICON_TIME_8;
		break;
	case 9:
		ICON_ID =ICON_TIME_9;
		break;
	}

	return ICON_ID;
}

UINT32 FlowWndMovie_DrawSpeedNum(UINT32 Value)
{
	UINT32 ICON_ID = ICONID_NULL;

	switch(Value)
	{
	case 0:
		ICON_ID =ICON_SPEED_0;
		break;
	case 1:
		ICON_ID =ICON_SPEED_1;
		break;
	case 2:
		ICON_ID =ICON_SPEED_2;
		break;
	case 3:
		ICON_ID =ICON_SPEED_3;
		break;
	case 4:
		ICON_ID =ICON_SPEED_4;
		break;
	case 5:
		ICON_ID =ICON_SPEED_5;
		break;
	case 6:
		ICON_ID =ICON_SPEED_6;
		break;
	case 7:
		ICON_ID =ICON_SPEED_7;
		break;
	case 8:
		ICON_ID =ICON_SPEED_8;
		break;
	case 9:
		ICON_ID =ICON_SPEED_9;
		break;
	}

	return ICON_ID;
}

void FlowMovie_IconDrawTimeDate(void)
{
    struct tm Curr_DateTime;
    UINT32 uiHour0,uiHour1,uiMin0,uiMin1;//uiS1,uiS0;
	UINT32 uiYear0,uiYear1,uiYear2,uiYear3,uiMon0,uiMon1,uiDay0,uiDay1;

    FlowMovie_IconHideTimeDate(); 
	
	GxTime_GetTime(&Curr_DateTime);

	//UxCtrl_SetShow(&UIFlowWndMovie_Clock_AMPMCtrl, FALSE);

#if 1 //M- 20221215
	//static char   itemHR_Buf[32] = "00";
	//static char   itemAMPM_Buf[32] = "AM";

	if ((Curr_DateTime.tm_hour) <= 11) {
		//snprintf(itemAMPM_Buf, 32, "AM");
		UxStatic_SetData(&UIFlowWndMovie_TIME_AMPMCtrl, STATIC_VALUE, ICON_AM);
	} else {
		//snprintf(itemAMPM_Buf, 32, "PM");
		UxStatic_SetData(&UIFlowWndMovie_TIME_AMPMCtrl, STATIC_VALUE, ICON_PM);
	}
	if ((Curr_DateTime.tm_hour) <= 12) {
		//snprintf(itemHR_Buf, 32, "%02ld", (Curr_DateTime.tm_hour));
	} else {
		//snprintf(itemHR_Buf, 32, "%02ld", (Curr_DateTime.tm_hour)-12);
		Curr_DateTime.tm_hour = (Curr_DateTime.tm_hour)-12;
	}

	UxCtrl_SetShow(&UIFlowWndMovie_TIME_AMPMCtrl, TRUE);
#endif

    //YEAR
    uiYear0 = ((Curr_DateTime.tm_year)%10);
    uiYear1 = (((Curr_DateTime.tm_year)/10)%10);
	uiYear2 = (((Curr_DateTime.tm_year)/100)%10);
	uiYear3 = ((Curr_DateTime.tm_year)/1000);
    //MONTH
    uiMon0 = ((Curr_DateTime.tm_mon)%10);
    uiMon1 = ((Curr_DateTime.tm_mon)/10);
    //DAY
    uiDay0 = ((Curr_DateTime.tm_mday)%10);
    uiDay1 = ((Curr_DateTime.tm_mday)/10);

    //HOUR
    uiHour0 = ((Curr_DateTime.tm_hour)%10);
    uiHour1 = ((Curr_DateTime.tm_hour)/10);
    //MIN
    uiMin0 = ((Curr_DateTime.tm_min)%10);
    uiMin1 = ((Curr_DateTime.tm_min)/10);

    UxStatic_SetData(&UIFlowWndMovie_DATE_Y3Ctrl,STATIC_VALUE,FlowWndMovie_DrawDateNum(uiYear3));
    UxStatic_SetData(&UIFlowWndMovie_DATE_Y2Ctrl,STATIC_VALUE,FlowWndMovie_DrawDateNum(uiYear2));
    UxStatic_SetData(&UIFlowWndMovie_DATE_Y1Ctrl,STATIC_VALUE,FlowWndMovie_DrawDateNum(uiYear1));
    UxStatic_SetData(&UIFlowWndMovie_DATE_Y0Ctrl,STATIC_VALUE,FlowWndMovie_DrawDateNum(uiYear0));
    UxStatic_SetData(&UIFlowWndMovie_DATE_M1Ctrl,STATIC_VALUE,FlowWndMovie_DrawDateNum(uiMon1));
    UxStatic_SetData(&UIFlowWndMovie_DATE_M0Ctrl,STATIC_VALUE,FlowWndMovie_DrawDateNum(uiMon0));
    UxStatic_SetData(&UIFlowWndMovie_DATE_D1Ctrl,STATIC_VALUE,FlowWndMovie_DrawDateNum(uiDay1));
    UxStatic_SetData(&UIFlowWndMovie_DATE_D0Ctrl,STATIC_VALUE,FlowWndMovie_DrawDateNum(uiDay0));

    UxStatic_SetData(&UIFlowWndMovie_TIME_H1Ctrl,STATIC_VALUE,FlowWndMovie_DrawTimeNum(uiHour1));
    UxStatic_SetData(&UIFlowWndMovie_TIME_H0Ctrl,STATIC_VALUE,FlowWndMovie_DrawTimeNum(uiHour0));
    UxStatic_SetData(&UIFlowWndMovie_TIME_M1Ctrl,STATIC_VALUE,FlowWndMovie_DrawTimeNum(uiMin1));
    UxStatic_SetData(&UIFlowWndMovie_TIME_M0Ctrl,STATIC_VALUE,FlowWndMovie_DrawTimeNum(uiMin0));

    UxCtrl_SetShow(&UIFlowWndMovie_DATE_Y3Ctrl,TRUE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_Y2Ctrl,TRUE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_Y1Ctrl,TRUE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_Y0Ctrl,TRUE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_M1Ctrl,TRUE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_M0Ctrl,TRUE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_D1Ctrl,TRUE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_D0Ctrl,TRUE);

    UxCtrl_SetShow(&UIFlowWndMovie_TIME_H1Ctrl,TRUE);
    UxCtrl_SetShow(&UIFlowWndMovie_TIME_H0Ctrl,TRUE);
    UxCtrl_SetShow(&UIFlowWndMovie_TIME_M1Ctrl,TRUE);
    UxCtrl_SetShow(&UIFlowWndMovie_TIME_M0Ctrl,TRUE);

    //Ux_Redraw();
}

void FlowMovie_IconHideTimeDate(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_Y3Ctrl,FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_Y2Ctrl,FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_Y1Ctrl,FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_Y0Ctrl,FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_M1Ctrl,FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_M0Ctrl,FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_D1Ctrl,FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_DATE_D0Ctrl,FALSE);

	UxCtrl_SetShow(&UIFlowWndMovie_TIME_AMPMCtrl, FALSE);

    UxCtrl_SetShow(&UIFlowWndMovie_TIME_H1Ctrl,FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_TIME_H0Ctrl,FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_TIME_M1Ctrl,FALSE);
    UxCtrl_SetShow(&UIFlowWndMovie_TIME_M0Ctrl,FALSE);
}

void FlowMovie_IconDrawSpeed(void)
{
    UINT32 uiN0,uiN1,uiN2,Cur_GPS_Speed;

	Cur_GPS_Speed = (UINT32)GPSRec_GetGPS_Speed();
    FlowMovie_IconHideSpeed(); 

	if (Cur_GPS_Speed < 6) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_0);
	} else if ((Cur_GPS_Speed >= 6)&& (Cur_GPS_Speed < 16)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_10);
	} else if ((Cur_GPS_Speed >= 16)&& (Cur_GPS_Speed < 26)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_20);
	} else if ((Cur_GPS_Speed >= 26)&& (Cur_GPS_Speed < 36)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_30);
	} else if ((Cur_GPS_Speed >= 36)&& (Cur_GPS_Speed < 46)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_40);
	} else if ((Cur_GPS_Speed >= 46)&& (Cur_GPS_Speed < 56)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_50);
	} else if ((Cur_GPS_Speed >= 56)&& (Cur_GPS_Speed < 66)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_60);
	} else if ((Cur_GPS_Speed >= 66)&& (Cur_GPS_Speed < 76)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_70);
	} else if ((Cur_GPS_Speed >= 76)&& (Cur_GPS_Speed < 86)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_80);
	} else if ((Cur_GPS_Speed >= 86)&& (Cur_GPS_Speed < 96)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_90);
	} else if ((Cur_GPS_Speed >= 96)&& (Cur_GPS_Speed < 106)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_100);
	} else if ((Cur_GPS_Speed >= 106)&& (Cur_GPS_Speed < 116)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_110);
	} else if ((Cur_GPS_Speed >= 116)&& (Cur_GPS_Speed < 126)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_120);
	} else if ((Cur_GPS_Speed >= 126)&& (Cur_GPS_Speed < 136)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_130);
	} else if ((Cur_GPS_Speed >= 136)&& (Cur_GPS_Speed < 146)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_140);
	} else if ((Cur_GPS_Speed >= 146)&& (Cur_GPS_Speed < 156)) {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_150);
	} else {
		UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_160);
	} 

    uiN0 = (Cur_GPS_Speed%10);
    uiN1 = ((Cur_GPS_Speed%100)/10);
    uiN2 = (Cur_GPS_Speed/100); 

    UxStatic_SetData(&UIFlowWndMovie_SPEED_N2Ctrl,STATIC_VALUE,FlowWndMovie_DrawSpeedNum(uiN2));
    UxStatic_SetData(&UIFlowWndMovie_SPEED_N1Ctrl,STATIC_VALUE,FlowWndMovie_DrawSpeedNum(uiN1));
    UxStatic_SetData(&UIFlowWndMovie_SPEED_N0Ctrl,STATIC_VALUE,FlowWndMovie_DrawSpeedNum(uiN0));

	if (UI_GetData(FL_SPEED_UNIT) == SPEED_UNIT_KPH) {
		UxStatic_SetData(&UIFlowWndMovie_SPEED_UNITCtrl, STATIC_VALUE, ICON_KMH);
	} else  {
		UxStatic_SetData(&UIFlowWndMovie_SPEED_UNITCtrl, STATIC_VALUE, ICON_MPH);
	}

	if (GetGPSSignalStatus() == 1) {
		UxStatic_SetData(&UIFlowWndMovie_GPS_STATUSCtrl, STATIC_VALUE, ICON_GPS_S_ON);
	} else {
		UxStatic_SetData(&UIFlowWndMovie_GPS_STATUSCtrl, STATIC_VALUE, ICON_GPS_S_OFF);
	}

	switch(GPSRec_getAngle())
	{
	case NORTH_EAST:
		UxStatic_SetData(&UIFlowWndMovie_COMPASSCtrl, STATIC_VALUE, ICON_COMPASS_NE);
		break;
	case EAST:
		UxStatic_SetData(&UIFlowWndMovie_COMPASSCtrl, STATIC_VALUE, ICON_COMPASS_E);
		break;
	case SOUTH_EAST:
		UxStatic_SetData(&UIFlowWndMovie_COMPASSCtrl, STATIC_VALUE, ICON_COMPASS_SE);
		break;
	case SOUTH:
		UxStatic_SetData(&UIFlowWndMovie_COMPASSCtrl, STATIC_VALUE, ICON_COMPASS_S);
		break;
	case SOUTH_WEST:
		UxStatic_SetData(&UIFlowWndMovie_COMPASSCtrl, STATIC_VALUE, ICON_COMPASS_SW);
		break;
	case WEST:
		UxStatic_SetData(&UIFlowWndMovie_COMPASSCtrl, STATIC_VALUE, ICON_COMPASS_W);
		break;
	case NORTH_WEST:
		UxStatic_SetData(&UIFlowWndMovie_COMPASSCtrl, STATIC_VALUE, ICON_COMPASS_NW);
		break;
	case NORTH:
		UxStatic_SetData(&UIFlowWndMovie_COMPASSCtrl, STATIC_VALUE, ICON_COMPASS_N);
		break;
	default:
		//UxStatic_SetData(&UIFlowWndMovie_COMPASSCtrl, STATIC_VALUE, ICON_COMPASS_S);
		break;
	}

	UxCtrl_SetShow(&UIFlowWndMovie_PANEL_SPEEDCtrl,TRUE);
	if (uiN2 == 0) {
		UxCtrl_SetShow(&UIFlowWndMovie_SPEED_N2Ctrl,FALSE);
	} else {
		UxCtrl_SetShow(&UIFlowWndMovie_SPEED_N2Ctrl,TRUE);
	}
	if ((uiN2 == 0) && (uiN1 == 0)) {
		UxStatic_SetData(&UIFlowWndMovie_SPEED_N1Ctrl,STATIC_VALUE,FlowWndMovie_DrawSpeedNum(uiN0));
		UxCtrl_SetShow(&UIFlowWndMovie_SPEED_N2Ctrl,FALSE);
		UxCtrl_SetShow(&UIFlowWndMovie_SPEED_N1Ctrl,TRUE);
		UxCtrl_SetShow(&UIFlowWndMovie_SPEED_N0Ctrl,FALSE);
	} else {
		UxCtrl_SetShow(&UIFlowWndMovie_SPEED_N1Ctrl,TRUE);
		UxCtrl_SetShow(&UIFlowWndMovie_SPEED_N0Ctrl,TRUE);
	}

	UxCtrl_SetShow(&UIFlowWndMovie_SPEED_UNITCtrl,TRUE);
	UxCtrl_SetShow(&UIFlowWndMovie_GPS_STATUSCtrl,TRUE);
	UxCtrl_SetShow(&UIFlowWndMovie_COMPASSCtrl,TRUE);

    //Ux_Redraw();
}

void FlowMovie_IconHideSpeed(void)
{
	UxCtrl_SetShow(&UIFlowWndMovie_PANEL_SPEEDCtrl,FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_SPEED_N2Ctrl,FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_SPEED_N1Ctrl,FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_SPEED_N0Ctrl,FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_SPEED_UNITCtrl,FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_GPS_STATUSCtrl,FALSE);
	UxCtrl_SetShow(&UIFlowWndMovie_COMPASSCtrl,FALSE);
}

void FlowMovie_IconDrawPanelSpeed(UINT32 Count)
{
	UxCtrl_SetShow(&UIFlowWndMovie_PANEL_SPEEDCtrl,FALSE);
	UxStatic_SetData(&UIFlowWndMovie_PANEL_SPEEDCtrl, STATIC_VALUE, ICON_PANEL_SPPED_0+Count-1);
	UxCtrl_SetShow(&UIFlowWndMovie_PANEL_SPEEDCtrl,TRUE);
}
#endif

void FlowMovie_IconDrawEIS(void)
{
	VControl *pCtrl = &UIFlowWndMovie_Status_EISCtrl;

	#if (ETHCAM_EIS == ENABLE)
	UxState_SetData(pCtrl, STATE_CURITEM, SysGetFlag(FL_MOVIE_EIS));
	UxCtrl_SetShow(pCtrl, TRUE);
	#else
	UxCtrl_SetShow(pCtrl, TRUE);//DEFAULT NO ICON
	#endif
}

void FlowMovie_IconHideEIS(void)
{
	UxCtrl_SetShow(&UIFlowWndMovie_Status_EISCtrl, FALSE);
}

void FlowMovie_UpdateIcons(BOOL bShow)
{
    if ((bShow == FALSE) || (SysGetFlag(FL_LCD_DISPLAY) == DISPOUT_OFF))
    {
        //FlowMovie_IconHideDscMode(&UIFlowWndMovie_Static_cameraCtrl);
        FlowMovie_IconHideSize(&UIFlowWndMovie_Static_resolutionCtrl);
        FlowMovie_IconHideRecTime(&UIFlowWndMovie_Static_timeCtrl);
        FlowMovie_IconHideMaxRecTime(&UIFlowWndMovie_Static_maxtimeCtrl);
        FlowMovie_IconHideRec(&UIFlowWndMovie_PanelCtrl);
        //FlowMovie_IconHideStorage(&UIFlowWndMovie_Status_StorageCtrl);
        FlowMovie_IconHideCyclicRec(&UIFlowWndMovie_Status_CyclicRecCtrl);
        FlowMovie_IconHideHDR(&UIFlowWndMovie_Status_HDRCtrl);
        FlowMovie_IconHideMotionDet(&UIFlowWndMovie_Status_MotionDetCtrl);
        FlowMovie_IconHideDZoom(&UIFlowWndMovie_Zoom_StaticCtrl);
        //FlowMovie_IconHideBattery(&UIFlowWndMovie_Status_batteryCtrl);
        //FlowMovie_IconHideEV(&UIFlowWndMovie_StatusICN_EVCtrl);
        FlowMovie_IconHideSOS(&UIFlowWndMovie_SOSCtrl);
        FlowMovie_IconHideAudio(&UIFlowWndMovie_Status_AudioCtrl);
        FlowMovie_IconHideTimelapse(&UIFlowWndMovie_StaticIcon_TimelapseCtrl);
        FlowMovie_IconHideDateTime();
        FlowMovie_DrawPIM(FALSE);
        FlowMovie_HideFolderCheck();
        FlowMovie_HideCustomerType();
        FlowMovie_IconHideGPSSignal();
		FlowMovie_IconHideTPMS();
        FlowMovie_IconHideEIS();
    }
    else
    {
        //FlowMovie_IconDrawDscMode(&UIFlowWndMovie_Static_cameraCtrl);
        FlowMovie_IconDrawSize(&UIFlowWndMovie_Static_resolutionCtrl);
        FlowMovie_IconHideRecTime(&UIFlowWndMovie_Static_timeCtrl);
        FlowMovie_IconDrawMaxRecTime(&UIFlowWndMovie_Static_maxtimeCtrl);
        FlowMovie_IconHideRec(&UIFlowWndMovie_PanelCtrl);
        //FlowMovie_IconHideStorage(&UIFlowWndMovie_Status_StorageCtrl);
        FlowMovie_IconHideCyclicRec(&UIFlowWndMovie_Status_CyclicRecCtrl);
        FlowMovie_IconDrawHDR(&UIFlowWndMovie_Status_HDRCtrl);
        FlowMovie_IconHideDZoom(&UIFlowWndMovie_Zoom_StaticCtrl);
        //FlowMovie_IconHideBattery(&UIFlowWndMovie_Status_batteryCtrl);
        //FlowMovie_IconDrawEV(&UIFlowWndMovie_StatusICN_EVCtrl);
        if (gMovData.State != MOV_ST_REC)
        {
            FlowMovie_IconHideSOS(&UIFlowWndMovie_SOSCtrl);
        }
        FlowMovie_IconDrawAudio(&UIFlowWndMovie_Status_AudioCtrl);
        FlowMovie_IconDrawDateTime();
        FlowMovie_DrawPIM(FALSE);
        FlowMovie_HideFolderCheck();
        FlowMovie_HideCustomerType();
        FlowMovie_IconHideTPMS();
        FlowMovie_IconHideEIS();
        if ((SysGetFlag(FL_MOVIE_MOTION_DET) == MOVIE_MOTIONDET_OFF)&&(UI_GetData(FL_MOVIE_TIMELAPSE_REC) != MOVIE_TIMELAPSEREC_OFF)) //time lapse
        {
            FlowMovie_IconHideMotionDet(&UIFlowWndMovie_Status_MotionDetCtrl);
            FlowMovie_IconDrawTimelapse(&UIFlowWndMovie_StaticIcon_TimelapseCtrl);
        }
        else if ((SysGetFlag(FL_MOVIE_MOTION_DET) == MOVIE_MOTIONDET_ON)&&(UI_GetData(FL_MOVIE_TIMELAPSE_REC) == MOVIE_TIMELAPSEREC_OFF)) //motion det
        {
            FlowMovie_IconHideTimelapse(&UIFlowWndMovie_StaticIcon_TimelapseCtrl);
            FlowMovie_IconDrawMotionDet(&UIFlowWndMovie_Status_MotionDetCtrl);
        }
        else
        {
            FlowMovie_IconHideMotionDet(&UIFlowWndMovie_Status_MotionDetCtrl);
            FlowMovie_IconHideTimelapse(&UIFlowWndMovie_StaticIcon_TimelapseCtrl);
        }
        //FlowMovie_IconDrawGPSSignal();
    }
}

