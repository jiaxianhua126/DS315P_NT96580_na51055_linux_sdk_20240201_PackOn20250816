#include "PrjInc.h"
#include "GxTime.h"
#include "GxStrg.h"
#include "UIFlowLVGL/UIFlowLVGL.h"
#include "UIFlowLVGL/UIFlowWrnMsg/UIFlowWrnMsgAPI.h"
#include <kwrap/debug.h>
#include "GxUSB.h"
#include "UsbDevDef.h"
#include "DxInput.h"
#include "UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowMovie/UIFlowMovieFuncs.h"
#include "UIApp/Network/UIAppWiFiCmdMovie.h"
#include "UIApp/Network/UIAppWiFiCmd.h"
#include "UIApp/Network/UIAppNetwork.h"
#include "UIApp/WifiCmdParser/WifiCmdParser.h"
#include "UIApp/Network/WifiAppCmd.h"
#include "Edog/EDogGlobal.h"



#if (USE_DCF == ENABLE)
#include "DCF.h"
#endif
BOOL   bWiFiConnected = FALSE;
BOOL   bWndWiFiMovieOpenFirst = FALSE;
BOOL   bWiFiRec_AutoStart = FALSE;
BOOL   bWiFiRec_AutoStop = FALSE;
BOOL   bWiFiTimelapse_Rec = FALSE;
BOOL   bWiFiModeChanged = FALSE;
BOOL   g_WiFiAutoRec = FALSE;
static BOOL gWiFiConnect_EN =FALSE;
extern BOOL g_bIsNeedReboot;

extern BOOL FlowMovie_IsStorageErr(BOOL IsCheckFull);

static lv_group_t* gp = NULL;
static lv_task_t* task_1sec_period = NULL;
static lv_task_t* task_200ms_period = NULL;
//#NT#2021/09/13#Philex Lin - begin
static lv_task_t* 	gUIMotionDetTimerID = NULL;
static BOOL    	g_uiRecordIngMotionDet = TRUE;
//#NT#2021/09/13#Philex Lin - end
//static volatile BOOL g_PreviewStable = FALSE;

static lv_event_t key_event = LV_USER_EVENT_KEY_RELEASE;

extern uint16_t warn_msgbox_auto_close_ms;
extern uint32_t warn_msgbox_auto_infinite_ms;
BOOL   g_uiWiFiRecordIngMotionDet = FALSE;
BOOL   g_uiWiFiParkingModeMotionDet = FALSE;

//MOVIE_SIZE_TAG
static CHAR    *resolution_Buf[MOVIE_SIZE_ID_MAX] = {
	[MOVIE_SIZE_FRONT_3840x2160P30] = "4K",
	[MOVIE_SIZE_DUAL_3840x2160P30_1920x1080P30] = "4K+1K",
};

/****************************************************************
 * do not access variable directly, use get_rec_status() instead
 **** ***********************************************************/
static bool rec_status = false;
static bool pim_status = false;

static void update_wifi_icons(void);
static void update_sos(void);

static bool get_pim_status(void)
{
	return pim_status;
}

static void set_pim_status(bool status)
{
	pim_status = status;
}
static bool get_rec_status(void)
{
	return rec_status;
}
static void set_rec_status(bool status)
{
	rec_status = status;

	if(status){
		lv_obj_set_hidden(image_status_rec_scr_uiflowmoviewifi, false);
		FlowWiFiMovie_StartRec();
		//gMovData.State = MOV_ST_REC;
	}
	else{
		//gMovData.State = MOV_ST_VIEW;
		FlowWiFiMovie_StopRec();
		update_wifi_icons();
	}

}
#if 0
static void toggle_rec_status(void)
{
	set_rec_status(!get_rec_status());
}
#endif
//static void  warn_msgbox(lv_obj_t* parent, const char* message, uint16_t auto_close_time_ms)
//{
//	lv_obj_t* msgbox = lv_msgbox_create(parent, message_box_1_scr_2);
//	lv_msgbox_set_text(msgbox, message);
//	lv_msgbox_start_auto_close(msgbox, auto_close_time_ms);
//
//	lv_group_t* gp = lv_obj_get_group(parent);
//
//	lv_group_add_obj(gp, msgbox);
//	lv_group_focus_obj(msgbox);
//}
//
//void  warn_msgbox_string_id(lv_obj_t* parent, lv_plugin_res_id id, uint16_t auto_close_time_ms)
//{
//	const lv_plugin_string_t* string = lv_plugin_get_string(id);
//	warn_msgbox(parent, string->ptr, auto_close_time_ms);
//}

static void update_date_time(void)
{
    struct tm Curr_DateTime;
    GxTime_GetTime(&Curr_DateTime);

	lv_label_set_text_fmt(label_date_scr_uiflowmoviewifi, "%04d/%02d/%02d", Curr_DateTime.tm_year, Curr_DateTime.tm_mon, Curr_DateTime.tm_mday);
	lv_label_set_text_fmt(label_time_scr_uiflowmoviewifi, "%02d:%02d:%02d", Curr_DateTime.tm_hour, Curr_DateTime.tm_min, Curr_DateTime.tm_sec);
}

static void update_rec_ellipse(void)
{
	if (WiFiCmd_GetStatus()==WIFI_MOV_ST_RECORD){
		bool is_hidden = lv_obj_get_hidden(image_status_rec_scr_uiflowmoviewifi);
		lv_obj_set_hidden(image_status_rec_scr_uiflowmoviewifi, !is_hidden);
	}
	else{
		lv_obj_set_hidden(image_status_rec_scr_uiflowmoviewifi, true);
	}
}

static void update_pim(void)
{
	if (get_pim_status()){
		bool is_hidden = lv_obj_get_hidden(image_pim_scr_uiflowmoviewifi);
		lv_obj_set_hidden(image_pim_scr_uiflowmoviewifi, !is_hidden);
	}
	else{
		lv_obj_set_hidden(image_pim_scr_uiflowmoviewifi, true);
	}
}

static void update_max_rec_time(void)
{
	if(!(WiFiCmd_GetStatus()==WIFI_MOV_ST_RECORD)){
		lv_obj_set_hidden(label_status_time_scr_uiflowmoviewifi,true);
		lv_obj_set_hidden(label_status_maxtime_scr_uiflowmoviewifi,false);
	}

	if (System_GetState(SYS_STATE_CARD)  == CARD_REMOVED) {
		lv_label_set_text_fmt(label_status_maxtime_scr_uiflowmoviewifi, "%02d:%02d:%02d", 0, 0, 0);
	} else {
		UINT32 free_sec = Movie_GetFreeSec();

		if (free_sec <= 2) {
			FlowMovie_SetRecMaxTime(0);
		} else if (free_sec > 86399) {
			///23:59:59
			FlowMovie_SetRecMaxTime(86399);
		} else {
			FlowMovie_SetRecMaxTime(free_sec);
		}
		lv_label_set_text_fmt(label_status_maxtime_scr_uiflowmoviewifi, "%02d:%02d:%02d", free_sec / 3600, (free_sec % 3600) / 60, (free_sec % 3600) % 60);
	}
}

static void update_rec_time(void)
{
   UINT32 rec_sec = FlowMovie_GetRecCurrTime();

	if(lv_obj_get_hidden(label_status_time_scr_uiflowmoviewifi))
	{
		lv_obj_set_hidden(label_status_time_scr_uiflowmoviewifi,false);
		lv_obj_set_hidden(label_status_maxtime_scr_uiflowmoviewifi,true);
	}

	lv_label_set_text_fmt(label_status_time_scr_uiflowmoviewifi, "%02d:%02d:%02d", rec_sec / 3600, (rec_sec % 3600) / 60, (rec_sec % 3600) % 60);
}

static void update_size(void)
{
	lv_label_set_text(label_status_resolution_scr_uiflowmoviewifi, resolution_Buf[SysGetFlag(FL_MOVIE_SIZE)]);
}

static void update_hdr(void)
{
	lv_obj_set_hidden(image_status_hdr_scr_uiflowmoviewifi,!SysGetFlag(FL_MOVIE_HDR));
}

static void update_motionDet(void)
{
	lv_obj_set_hidden(image_motiondetect_scr_uiflowmoviewifi,!SysGetFlag(FL_MOVIE_MOTION_DET));
}


/**************************************************************************************
 *
 * example how to update icon by flag , it's not like nvt gui framework's status icon,
 * resource must be specified in the user code.
 *
 * resource id is aligned with enumerate in the UIInfo.h,
 * out of array index is not checked here, user should be careful.
 *
 **************************************************************************************/
static void update_cyclic_rec(void)
{
	static lv_plugin_res_id res[] = {
			LV_PLUGIN_RES_ID_NONE,
			//LV_PLUGIN_IMG_ID_ICON_CYCLIC_REC_1MIN,
			LV_PLUGIN_IMG_ID_ICON_CYCLIC_REC_3MIN,
			LV_PLUGIN_IMG_ID_ICON_CYCLIC_REC_5MIN,
			//LV_PLUGIN_IMG_ID_ICON_CYCLIC_REC_10MIN,
	};


	lv_plugin_res_id img_id = res[SysGetFlag(FL_MOVIE_CYCLIC_REC)];


	/* hide cyclic rec icon if disabled */
	if(img_id != LV_PLUGIN_RES_ID_NONE){
		lv_obj_set_hidden(image_cyclic_rec_scr_uiflowmoviewifi, false);
		lv_plugin_img_set_src(image_cyclic_rec_scr_uiflowmoviewifi, img_id);
	}
	else{
		lv_obj_set_hidden(image_cyclic_rec_scr_uiflowmoviewifi, true);
	}
}

static void update_battery(void)
{
	static lv_plugin_res_id res[] = {
			LV_PLUGIN_IMG_ID_ICON_BATTERY_FULL,
			LV_PLUGIN_IMG_ID_ICON_BATTERY_MED,
			LV_PLUGIN_IMG_ID_ICON_BATTERY_LOW,
			LV_PLUGIN_IMG_ID_ICON_BATTERY_EMPTY,
			LV_PLUGIN_IMG_ID_ICON_BATTERY_ZERO,
			LV_PLUGIN_IMG_ID_ICON_BATTERY_CHARGE
	};


	/* user should call a function to get battery level here */
	lv_plugin_img_set_src(image_battery_scr_uiflowmoviewifi, res[0]);

	lv_obj_set_hidden(image_battery_scr_uiflowmoviewifi,true);
}

static void update_ev(void)
{
	static lv_plugin_res_id res[] = {
			LV_PLUGIN_IMG_ID_ICON_EV_P2P0,
		      LV_PLUGIN_IMG_ID_ICON_EV_P1P6,
		      LV_PLUGIN_IMG_ID_ICON_EV_P1P3,
		      LV_PLUGIN_IMG_ID_ICON_EV_P1P0,
		      LV_PLUGIN_IMG_ID_ICON_EV_P0P6,
		      LV_PLUGIN_IMG_ID_ICON_EV_P0P3,
		      LV_PLUGIN_IMG_ID_ICON_EV_P0P0,
		      LV_PLUGIN_IMG_ID_ICON_EV_M0P3,
		      LV_PLUGIN_IMG_ID_ICON_EV_M0P6,
		      LV_PLUGIN_IMG_ID_ICON_EV_M1P0,
		      LV_PLUGIN_IMG_ID_ICON_EV_M1P3,
		      LV_PLUGIN_IMG_ID_ICON_EV_M1P6,
		      LV_PLUGIN_IMG_ID_ICON_EV_M2P0,
	};
	/* user should call a function to get battery level here */
	lv_plugin_img_set_src(image_ev_scr_uiflowmoviewifi, res[SysGetFlag(FL_EV)]);

	lv_obj_set_hidden(image_ev_scr_uiflowmoviewifi,true);
}

static void update_card(void)
{

	/* Update status item data */
	if (System_GetState(SYS_STATE_CARD)  == CARD_REMOVED) {
		lv_plugin_img_set_src(image_storage_scr_uiflowmoviewifi,LV_PLUGIN_IMG_ID_ICON_INTERNAL_FLASH);

	} else if (System_GetState(SYS_STATE_CARD)  == CARD_LOCKED) {
			lv_plugin_img_set_src(image_storage_scr_uiflowmoviewifi,LV_PLUGIN_IMG_ID_ICON_SD_LOCK);
	} else {
		lv_plugin_img_set_src(image_storage_scr_uiflowmoviewifi,LV_PLUGIN_IMG_ID_ICON_SD_CARD);
	}
	lv_obj_set_hidden(image_storage_scr_uiflowmoviewifi,true);
}

static void update_wifi(bool status)
{
	static lv_plugin_res_id res[] = {
			  LV_PLUGIN_IMG_ID_ICON_WIFI,
		      LV_PLUGIN_IMG_ID_ICON_WIFI_CONNECTED_SMALL,
	};
	if(status)
	{
		lv_plugin_img_set_src(image_status_wifi_scr_uiflowmoviewifi, res[1]);
	}
	else
	{
		lv_plugin_img_set_src(image_status_wifi_scr_uiflowmoviewifi, res[0]);
	}

	lv_obj_set_hidden(image_status_wifi_scr_uiflowmoviewifi,false);
}

static void update_audio(void)
{
	static lv_plugin_res_id res[] = {
			LV_PLUGIN_IMG_ID_ICON_VOICE_OFF,
		      LV_PLUGIN_IMG_ID_ICON_VOICE_ON,
	};

	lv_plugin_img_set_src(image_status_audio_scr_uiflowmoviewifi, res[SysGetFlag(FL_MOVIE_AUDIO)]);
}
static void update_mode_video(void)
{
	lv_obj_set_hidden(image_mode_video_scr_uiflowmoviewifi,true);
}

static void update_sos(void)
{
	if(FlowMovie_GetSOSStatusNow())
	{
		lv_obj_set_hidden(image_status_waring_scr_uiflowmoviewifi,false);
	}
	else
	{
		lv_obj_set_hidden(image_status_waring_scr_uiflowmoviewifi,true);
	}
}

static void update_WiFiDisConnected(bool status)
{
	lv_obj_set_hidden(image_wifi_disconnected_scr_uiflowmoviewifi,status);
	DBG_DUMP("update_WiFiDisConnected = %d\r\n",status);
}

static void update_WiFiData(BOOL bShow)
{
	DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
    static char buf1[32],buf2[32];
    char *pMacAddr;
    UIMenuStoreInfo *ptMenuStoreInfo = UI_GetMenuInfo();

    if (bShow == true)
    {
        lv_obj_set_hidden(container_ssid_key_scr_uiflowmoviewifi, bShow);
        return;
    }

    if (UI_GetData(FL_WIFI_LINK)==WIFI_LINK_OK)
    {
		if ((UI_GetData(FL_NetWorkMode) == NET_AP_MODE)
			|| (UI_GetData(FL_NetWorkMode) == NET_WPS_AP_PBC_MODE)
			|| (UI_GetData(FL_NetWorkMode) == NET_STATION_MODE))
		{
            if ((SysGetFlag(FL_WIFI_BAND) == WIFI_BAND_52G)
				||(SysGetFlag(FL_WIFI_BAND) == WIFI_BAND_58G))
			{
                if (ptMenuStoreInfo->strSSID_5G[0] == 0)
				{
                    #if (MAC_APPEN_SSID==ENABLE)
                    pMacAddr = (char *)UINet_GetMAC();
                    if (UI_GetData(FL_NetWorkMode) == NET_AP_MODE)
					{
                        snprintf(buf1, sizeof(buf1), "SSID: %s%02x%02x%02x%02x%02x%02x", UINet_GetSSID_5G(), pMacAddr[0], pMacAddr[1], pMacAddr[2]
                                                                    ,pMacAddr[3], pMacAddr[4], pMacAddr[5]);
                        //snprintf(buf1, sizeof(buf1), "SSID: %s%02x%02x%02x", UINet_GetSSID_5G(), pMacAddr[3], pMacAddr[4], pMacAddr[5]);
                    }
					else
					{
                        snprintf(buf1, sizeof(buf1), "SSID: %s", UINet_GetSSID_5G());
                    }
                    #else
                    snprintf(buf1, sizeof(buf1), "SSID: %s", UINet_GetSSID_5G());
                    #endif
                }
				else
				{
                    snprintf(buf1, sizeof(buf1), "SSID: %s", UINet_GetSSID_5G());
                }
                snprintf(buf2, sizeof(buf2), "PWA2: %s", UINet_GetPASSPHRASE());

				lv_label_set_text_static(label_wifi_ssid_scr_uiflowmoviewifi,buf1);
				lv_label_set_text_static(label_wifi_password_scr_uiflowmoviewifi,buf2);
            }
			else
			{
                if (ptMenuStoreInfo->strSSID[0] == 0)
				{
                    #if (MAC_APPEN_SSID==ENABLE)
                    pMacAddr = (char *)UINet_GetMAC();
                    if (UI_GetData(FL_NetWorkMode) == NET_AP_MODE)
					{
                        snprintf(buf1, sizeof(buf1), "SSID: %s%02x%02x%02x%02x%02x%02x", UINet_GetSSID(), pMacAddr[0], pMacAddr[1], pMacAddr[2]
                                                                    ,pMacAddr[3], pMacAddr[4], pMacAddr[5]);
                        //snprintf(buf1, sizeof(buf1), "SSID: %s%02x%02x%02x", UINet_GetSSID(), pMacAddr[3], pMacAddr[4], pMacAddr[5]);
                    }
					else
					{
                        snprintf(buf1, sizeof(buf1), "SSID: %s", UINet_GetSSID());
                    }
                    #else
                    snprintf(buf1, sizeof(buf1), "SSID: %s", UINet_GetSSID());
                    #endif
                }
				else
				{
                    snprintf(buf1, sizeof(buf1), "SSID: %s", UINet_GetSSID());
                }
                snprintf(buf2, sizeof(buf2), "PWA2: %s", UINet_GetPASSPHRASE());

				lv_label_set_text_static(label_wifi_ssid_scr_uiflowmoviewifi,buf1);
				lv_label_set_text_static(label_wifi_password_scr_uiflowmoviewifi,buf2);
            }
        }
    }
    else
    {
        snprintf(buf1,sizeof(buf1),"%s:Fail","Conntecting");
		lv_label_set_text_static(label_wifi_ssid_scr_uiflowmoviewifi,buf1);
        lv_label_set_text_static(label_wifi_password_scr_uiflowmoviewifi,NULL);
    }

	lv_obj_set_hidden(container_ssid_key_scr_uiflowmoviewifi, bShow);
}
void FlowWiFiMovie_IconDrawCompass(void)
{
	lv_plugin_img_set_src(image_status_gps_scr_uiflowmoviewifi, LV_PLUGIN_IMG_ID_ICON_GPS);
	lv_obj_set_hidden(image_status_gps_scr_uiflowmoviewifi, false);
}

void FlowWiFiMovie_IconDrawGPSSignal(BOOL bShow)
{
}

void UIFlowMovieWiFi_update_icons(void)
{
	update_wifi_icons();
}

/*static*/ void update_wifi_icons(void)
{
	update_date_time();
	update_rec_ellipse();
	update_pim();
	update_size();
	update_ev();
	update_card();
	update_hdr();
	update_motionDet();
	update_cyclic_rec();
	update_battery();
	update_max_rec_time();
	update_audio();
	update_mode_video();
	update_sos();
	update_WiFiDisConnected(true);
	FlowWiFiMovie_IconDrawGPSSignal(true);
}

static void UIFlowMovieWiFi_MotionDetect(void)
{
	static UINT32  uiMotionDetGo = 0;
	static UINT32  uiMotionDetStop = 0;
	static BOOL    bMotionDetRec = FALSE; // TRUE: trigger record by MD
	static UINT32  uiMotionDetRet = 0;
	Ux_SendEvent(0, NVTEVT_EXE_MOTION_DET_RUN, 1, &uiMotionDetRet);

	if (uiMotionDetRet == TRUE)	{
		uiMotionDetGo++;
		if (uiMotionDetGo >= 2) {
			uiMotionDetStop = 0;
			// Recording of modtion detection in pure CarDV path
			if (!(WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD)) {
				// reset uiMotionDetGo
				uiMotionDetGo = 0;
				bMotionDetRec = TRUE;
				// record video
				set_rec_status(true);
			}
		}
	} else {
		if (bMotionDetRec == TRUE) {
			uiMotionDetStop++;
			if (uiMotionDetStop >= 2) { // 1 sec
				uiMotionDetGo = 0;
			}
			if (uiMotionDetStop >= 120) { // 60 Sec
				uiMotionDetStop = 0;
				if (FlowMovie_GetRecCurrTime() >= 1) {
					if (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD) {
						set_rec_status(false);
						// update ui window icon
						update_wifi_icons();
						bMotionDetRec = FALSE;
					}
				}
			}
		}
	}
}

static void task_1sec_period_cb(lv_task_t* task)
{
	update_date_time();
	FlowWiFiMovie_IconDrawGPSSignal(true);

    //when sensor2 insert or remove, record again
    if (((bWiFiModeChanged == TRUE))/*&&(!g_bSpeedPanelInit)*/)
    {
        bWiFiModeChanged = FALSE;
        if ((System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_MOVIE)&&(WiFiCmd_GetStatus() == WIFI_MOV_ST_LVIEW))
        {
            bWiFiRec_AutoStart = TRUE;
            Ux_PostEvent(NVTEVT_WIFI_EXE_MOVIE_REC, 1, 1);
        }
    }
}
static void task_200ms_period_cb(lv_task_t* task)
{
	FlowMovie_UpdateLED();
}

static void task_motionDet_cb(lv_task_t* task)
{
	//det screen saver
	FlowMovie_DetLCDDim();
	if (g_uiRecordIngMotionDet)
		UIFlowMovieWiFi_MotionDetect();
}

void UIFlowWndMovieWiFi_Initparam(void)
{
#if(PHOTO_MODE==ENABLE)
	// The same effect as Photo mode
	Ux_SendEvent(&CustomPhotoObjCtrl,	NVTEVT_EXE_WB,					1,	SysGetFlag(FL_WB));

	// The other settings
	Ux_SendEvent(&CustomPhotoObjCtrl,	NVTEVT_EXE_COLOR,				1,	MOVIE_COLOR_NORMAL);
#endif
	/* Video resolution setting must be set after other IQ settings */
	//Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIESIZE,			1,	SysGetFlag(FL_MOVIE_SIZE));

	/* Cyclic recording/record with mute or sound/DateImptint/Motion Detect */
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_CYCLIC_REC,			1,	SysGetFlag(FL_MOVIE_CYCLIC_REC));
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOTION_DET,			1,	SysGetFlag(FL_MOVIE_MOTION_DET));
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_DATE_IMPRINT,	1,	SysGetFlag(FL_MOVIE_DATEIMPRINT));
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_AUDIO,			1,	SysGetFlag(FL_MOVIE_AUDIO));
#if(PHOTO_MODE==ENABLE)
	//Ux_SendEvent(&CustomPhotoObjCtrl,	NVTEVT_EXE_EV,					1,	SysGetFlag(FL_EV));
#endif
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_MCTF,			1,	SysGetFlag(FL_MovieMCTFIndex));
	//Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_WDR,			1,	SysGetFlag(FL_MOVIE_WDR));
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_HDR,			1,	SysGetFlag(FL_MOVIE_HDR));
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_DEFOG,			1,	SysGetFlag(FL_MOVIE_DEFOG));
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_GSENSOR,				1,	SysGetFlag(FL_GSENSOR));
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_SENSOR_ROTATE,	1,	SysGetFlag(FL_MOVIE_SENSOR_ROTATE));
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_IR_CUT,		1,	SysGetFlag(FL_MOVIE_IR_CUT));
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_PROTECT_AUTO,	1,	SysGetFlag(FL_MOVIE_URGENT_PROTECT_AUTO));
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_PROTECT_MANUAL,	1,	SysGetFlag(FL_MOVIE_URGENT_PROTECT_MANUAL));
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_LDWS,			1,	SysGetFlag(FL_MOVIE_LDWS));
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_FCW,			1,	SysGetFlag(FL_MOVIE_FCW));
	Ux_SendEvent(&UISetupObjCtrl,		NVTEVT_EXE_FREQ,				1,	SysGetFlag(FL_FREQUENCY));
#if (MOVIE_RSC == ENABLE)
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIE_RSC,			1,	MOVIE_RSC_ON);
#endif
#if MOVIE_DIS
	Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_MOVIEDIS,			1,	MOVIE_DIS_ON);
#endif
#if SHDR_FUNC
	//Ux_SendEvent(&CustomMovieObjCtrl,	NVTEVT_EXE_SHDR,				1,	MOVIE_HDR_ON);
#endif
}


static void set_indev_keypad_group(lv_obj_t* obj)
{
	if(gp == NULL){
		gp = lv_group_create();
		lv_group_add_obj(gp, obj);
	}

	lv_indev_t* indev = lv_plugin_find_indev_by_type(LV_INDEV_TYPE_KEYPAD);
	lv_indev_set_group(indev, gp);
}

void UIFlowWndMovieWiFi_OnCustom2(void)
{

    if (FlowMovie_WakeUpLCDBacklight())
    {
        //return NVTEVT_CONSUME;
    }
    if (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD) {
        if (FlowMovie_GetRecCurrTime() <= 1) {
            Delay_DelayMs(1000);
        }
        FlowWiFiMovie_StopRec();
        Delay_DelayMs(300);
    }
    update_WiFiDisConnected(false);
    //return 0;
//#NT#2016/05/31#Ben Wang -begin
//#NT#Add UVC multimedia function.
#if(UVC_MULTIMEDIA_FUNC == ENABLE)
	if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_UVC) {
		Ux_PostEvent(NVTEVT_SYSTEM_MODE, 2, System_GetState(SYS_STATE_CURRMODE), SYS_SUBMODE_NORMAL);
		return NVTEVT_CONSUME;
	}
#endif
//#NT#2016/05/31#Ben Wang -end
#if (WIFI_FUNC == ENABLE)
#if 0//!defined(_NVT_SDIO_WIFI_NONE_) || !defined(_NVT_USB_WIFI_NONE_)
	//notify current connected socket,new connect not get IP and socket not create
	//cannot disconnet immediate,suggest after 500 ms

	WifiApp_SendCmd(WIFIAPP_CMD_NOTIFY_STATUS, WIFIAPP_RET_DISCONNECT);
	//delay 500 ms,and then close window
	//in window,use GxTimer replace Timer Delay,it would occupat UI task
//	GxTimer_StartTimer(TIMER_HALF_SEC, NVTEVT_DELAY_CLOSE_TIMER, ONE_SHOT);
	lv_task_once(lv_task_create(task_delay_close, 500, LV_TASK_PRIO_MID, NULL));

#else
	gWiFiConnect_EN = FALSE;
	bWndWiFiMovieOpenFirst = FALSE;
	Ux_PostEvent(NVTEVT_SYSTEM_MODE, 2, System_GetState(SYS_STATE_CURRMODE), SYS_SUBMODE_NORMAL);
	DBG_ERR("change mode.\r\n");
	//should close network application,then stop wifi
	Ux_PostEvent(NVTEVT_EXE_WIFI_STOP, 0);

#endif
#endif

}


static void UIFlowMovieWiFi_ScrOpen(lv_obj_t* obj)
{
	DBG_DUMP("%s\r\n", __func__);
    //after enter link wnd ,set wifi sub mode,avoid wifi on change normal movie mode
    System_ChangeSubMode(SYS_SUBMODE_WIFI);

	set_indev_keypad_group(obj);

    Ux_FlushEventByRange(NVTEVT_KEY_EVT_START, NVTEVT_KEY_EVT_END);
    /* Init window key mask variables & set key and key released mask */
    Input_SetKeyMask(KEY_PRESS, FLGKEY_KEY_MASK_DEFAULT);
    Input_SetKeyMask(KEY_RELEASE, FLGKEY_KEY_MASK_DEFAULT);
    Input_SetKeyMask(KEY_CONTINUE, FLGKEY_KEY_MASK_DEFAULT);

	/* init all flags */
	UIFlowWndMovieWiFi_Initparam();

	/* init all icons */
	update_wifi_icons();
	if (!bWndWiFiMovieOpenFirst)
    {
        bWndWiFiMovieOpenFirst = TRUE;
		update_wifi(false);
		update_WiFiData(false);
		bWiFiModeChanged = TRUE;
    }
    else
    {
        update_wifi(bWiFiConnected);
		update_WiFiData(true);
    }

	/* update icons periodically*/
	if(task_1sec_period == NULL)
	{
		task_1sec_period = lv_task_create(task_1sec_period_cb, 1000, LV_TASK_PRIO_MID, NULL);
	}

	if(task_200ms_period == NULL)
	{
		task_200ms_period = lv_task_create(task_200ms_period_cb, 200, LV_TASK_PRIO_MID, NULL);
	}

	//#NT#2021/9/13#Philex Lin - begin
	g_uiRecordIngMotionDet = (SysGetFlag(FL_MOVIE_MOTION_DET) == MOVIE_MOTIONDET_ON) ? TRUE : FALSE;
	if(gUIMotionDetTimerID == NULL)
	{
		gUIMotionDetTimerID = lv_task_create(task_motionDet_cb, 500, LV_TASK_PRIO_MID, NULL);
	}
	//#NT#2021/9/13#Philex Lin - end
	FlowMovie_SetSOSStatusNow(FALSE);
	bWiFiRec_AutoStart = FALSE;
    bWiFiRec_AutoStop = FALSE;
	WifiCmd_ReceiveCmd(TRUE);

    Ux_FlushEventByRange(NVTEVT_KEY_EVT_START, NVTEVT_KEY_EVT_END);
}

static void UIFlowMovieWiFi_ChildScrClose(lv_obj_t* obj, LV_USER_EVENT_NVTMSG_DATA* data)
{
	DBG_DUMP("%s\r\n", __func__);

	/* do nothing if current system mode is not matched */
	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE){
		DBG_WRN("current system mode is not movie\r\n");
		return;
	}

	/* once child scr closed, set keypad group again */
	set_indev_keypad_group(obj);
	update_wifi_icons();

	/* start timer again when exiting menu */
	if(task_1sec_period == NULL)
	{
		task_1sec_period = lv_task_create(task_1sec_period_cb, 1000, LV_TASK_PRIO_MID, NULL);
	}

	//#NT#2021/9/13#Philex Lin - begin
	g_uiRecordIngMotionDet = (SysGetFlag(FL_MOVIE_MOTION_DET) == MOVIE_MOTIONDET_ON) ? TRUE : FALSE;
	if(gUIMotionDetTimerID == NULL)
	{
		gUIMotionDetTimerID = lv_task_create(task_motionDet_cb, 500, LV_TASK_PRIO_MID, NULL);
	}
	//#NT#2021/9/13#Philex Lin - end

	gMovData.State = MOV_ST_VIEW;
}

static void UIFlowMovieWiFi_ScrClose(lv_obj_t* obj)
{
	DBG_DUMP("%s\r\n", __func__);

	/* do nothing if current system mode is not matched */
	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE){
		DBG_WRN("current system mode is not movie\r\n");
		return;
	}

    if (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD)
    {
        if (FlowMovie_GetRecCurrTime() <= 1)
        {
            Delay_DelayMs(1000);
        }
        FlowWiFiMovie_StopRec();
    }

	if(task_1sec_period)
	{
		lv_task_del(task_1sec_period);
		task_1sec_period = NULL;
	}

	if(task_200ms_period)
	{
		lv_task_del(task_200ms_period);
		task_200ms_period = NULL;
	}

	if(gUIMotionDetTimerID)
	{
		lv_task_del(gUIMotionDetTimerID);
		gUIMotionDetTimerID = NULL;
	}

    if (!bWndWiFiMovieOpenFirst)
    {
        WifiCmd_ReceiveCmd(FALSE);
    }
}

static void UIFlowMovieWiFi_OnExePIM(lv_obj_t* obj)
{
	if((WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD) && (SysGetFlag(FL_MOVIE_PIM) == MOVIE_PIM_ON))
	{
		set_pim_status(true);
		//show RawEnc icon
		update_pim();
		// Send RawEnc event
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_REC_RAWENC, 0);
	}
}

static void UIFlowMovieWiFi_OnKeyZoomIn(lv_obj_t* obj)
{

}

static void UIFlowMovieWiFi_OnKeyZoomOut(lv_obj_t* obj)
{

}

static void UIFlowMovieWiFi_OnKeyMode(lv_obj_t* obj)
{

}

static void UIFlowMovieWiFi_OnKeyPrev(lv_obj_t* obj)
{

}

static void UIFlowMovieWiFi_OnKeyDown(lv_obj_t* obj)
#if 1
{
	DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
	static  BOOL bEnterKeyPressed = FALSE;

	switch (key_event) {
		case LV_EVENT_KEY:
			bEnterKeyPressed = TRUE;
			break;
		case LV_USER_EVENT_KEY_RELEASE:
		if (!bEnterKeyPressed) {
			DBG_DUMP("enter key ignore.\r\n");
			break;
		}
		bEnterKeyPressed = FALSE;

		switch (WiFiCmd_GetStatus()) {
		case WIFI_MOV_ST_RECORD:
		case WIFI_MOV_ST_IDLE:
	    case WIFI_MOV_ST_LVIEW:
	        if (FlowMovie_WakeUpLCDBacklight())
	        {
	            return ;
	        }
			if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE)
	        {
	            return ;
	        }

			if ((UI_GetData(SYS_STATE_CARD) == CARD_INSERTED) && (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD))
		    {
				UIFlowMovieWiFi_OnExePIM(obj);
		    }
			break;
		}
		break;

	case LV_USER_EVENT_KEY_LONG_PRESS:
		if (bEnterKeyPressed) {
			bEnterKeyPressed = FALSE;
	        if (FlowMovie_WakeUpLCDBacklight())
	        {
	            return ;
	        }
	        break;
		}
	    break;
	}
}
#else
{
	UINT32  uiSoundMask;
	DBG_DUMP("%s\r\n", __func__);

	switch (gMovData.State) {
		case MOV_ST_VIEW:
		case MOV_ST_VIEW|MOV_ST_ZOOM:
		case MOV_ST_REC:
        case MOV_ST_REC|MOV_ST_ZOOM:
        case MOV_ST_REC_WAIT:

		if(task_1sec_period)
		{
			lv_task_del(task_1sec_period);
			task_1sec_period = NULL;
		}

		if(gUIMotionDetTimerID)
		{
			lv_task_del(gUIMotionDetTimerID);
			gUIMotionDetTimerID = NULL;
		}

		if ((gMovData.State == MOV_ST_REC)||(gMovData.State == (MOV_ST_REC|MOV_ST_ZOOM)))
		{
			if ((FlowMovie_GetRecCurrTime() <= 1)&&(SysGetFlag(FL_MOVIE_TIMELAPSE_REC) == MOVIE_TIMELAPSEREC_OFF))
			{
				Delay_DelayMs(1000);
			}
			FlowMovie_StopRec();
			Delay_DelayMs(300);
		}

		// enable shutter2 sound (shutter2 as OK key in menu)
		uiSoundMask = Input_GetKeySoundMask(KEY_PRESS);
		uiSoundMask |= FLGKEY_ENTER;
		Input_SetKeySoundMask(KEY_PRESS, uiSoundMask);
		Input_SetKeyMask(KEY_RELEASE, FLGKEY_KEY_MASK_NULL);

		// Open common mix (Item + Option) menu
		//lv_plugin_scr_open(UIFlowMenuCommonItem, NULL);
		lv_plugin_scr_open(UIFlowMenuCommonItem, NULL);
		gMovData.State = MOV_ST_MENU;
		break;
		#if 0
		case MOV_ST_REC:
		case MOV_ST_REC|MOV_ST_ZOOM:
		if (SysGetFlag(FL_MOVIE_URGENT_PROTECT_MANUAL) == MOVIE_URGENT_PROTECT_MANUAL_ON) {
		#if (_BOARD_DRAM_SIZE_ > 0x04000000)
		if (GetMovieRecType_2p(UI_GetData(FL_MOVIE_SIZE)) == MOVIE_REC_TYPE_FRONT) {
			if(gMovie_Rec_Option.emr_on == _CFG_EMR_SET_CRASH){
				ImageApp_MovieMulti_SetCrash(_CFG_REC_ID_1, TRUE);
			}else{
				ImageApp_MovieMulti_TrigEMR(_CFG_REC_ID_1);
			}
		} else
		#endif
		{
			UINT32 i, mask, movie_rec_mask;

			movie_rec_mask = Movie_GetMovieRecMask();
			mask = 1;
			for (i = 0; i < SENSOR_CAPS_COUNT; i++) {
				if (movie_rec_mask & mask) {
					ImageApp_MovieMulti_SetCrash(_CFG_REC_ID_1 + i, TRUE);
				}
				mask <<= 1;
			}
		}

#if USE_DCF == ENABLE
		DBG_WRN("======== DCF not support EMR func!! ========\n");
#endif
		}

		break;
		#endif
	}
}
#endif

static void UIFlowMovieWiFi_OnKeyUp(lv_obj_t* obj)
{
	DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
	static BOOL bUpKeyPressed = FALSE;

	switch (key_event) {
	case LV_EVENT_KEY:
		bUpKeyPressed = TRUE;
		break;

	case LV_USER_EVENT_KEY_RELEASE:
		if (!bUpKeyPressed) {
			break;
		}
		bUpKeyPressed = FALSE;

		if (FlowMovie_WakeUpLCDBacklight()) {
		}
		Delay_DelayMs(200);
		DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
		if (SysGetFlag(FL_MOVIE_AUDIO) == MOVIE_AUDIO_OFF) {
            SysSetFlag(FL_MOVIE_AUDIO, MOVIE_AUDIO_ON);
			#if PLAY_SOUND_IN_OTHER_TASK
			UIDogSound_Enable(FALSE);
			DogSoundPlayID(UIVoice_GetIndex(DEMOSOUND_SOUND_MICEN_TONE));
			UIDogSound_Enable(TRUE);
			#else
			UIVoice_Play(DEMOSOUND_SOUND_MICEN_TONE);
			#endif
			Delay_DelayMs(50);
        } else {
            SysSetFlag(FL_MOVIE_AUDIO, MOVIE_AUDIO_OFF);
			#if PLAY_SOUND_IN_OTHER_TASK
			UIDogSound_Enable(FALSE);
			DogSoundPlayID(UIVoice_GetIndex(DEMOSOUND_SOUND_MICDIS_TONE));
			UIDogSound_Enable(TRUE);
			#else
			UIVoice_Play(DEMOSOUND_SOUND_MICDIS_TONE);
			#endif
			Delay_DelayMs(50);
        }
		DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
        Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_AUDIO, 1, SysGetFlag(FL_MOVIE_AUDIO));
        update_audio();
		break;

	case LV_USER_EVENT_KEY_LONG_PRESS:
		break;
	}
}

static void UIFlowMovieWiFi_OnKeySSID(lv_obj_t* obj)
{
	DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
	static	BOOL bEnterKeyPressed = FALSE;
	BOOL	bShow = FALSE;
	switch (key_event)
	{
		case LV_EVENT_KEY:
			bEnterKeyPressed = TRUE;
			break;
		case LV_USER_EVENT_KEY_RELEASE:
			if (!bEnterKeyPressed) {
				DBG_DUMP("enter key ignore.\r\n");
				break;
			}
			DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
			bEnterKeyPressed = FALSE;

		    if (FlowMovie_WakeUpLCDBacklight())
		    {
		    }
			if (lv_obj_get_hidden(container_ssid_key_scr_uiflowmoviewifi))
			{
				bShow = FALSE;//show
			}
			else
			{
				bShow = TRUE;//hide
			}
			update_WiFiData(bShow);
			break;

		case LV_USER_EVENT_KEY_LONG_PRESS:
		    break;
	}
}
static void UIFlowMovieWiFi_OnKeyLeft(lv_obj_t* obj)
{
	static  BOOL bEnterKeyPressed = FALSE;
	UINT32  curStatus = 0;

	curStatus = WiFiCmd_GetStatus();
	switch (key_event)
	{
		case LV_EVENT_KEY:
			bEnterKeyPressed = TRUE;
			break;
		case LV_USER_EVENT_KEY_RELEASE:
		if (!bEnterKeyPressed) {
			DBG_DUMP("enter key ignore.\r\n");
			break;
		}
		bEnterKeyPressed = FALSE;
		switch(curStatus)
		{
		case WIFI_MOV_ST_RECORD:
			if (FlowMovie_WakeUpLCDBacklight())
			{
				//return NVTEVT_CONSUME;
			}

			if (System_GetState(SYS_STATE_CARD)  == CARD_REMOVED)
			{
				//Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_PLEASE_INSERT_SD,FLOWWRNMSG_TIMER_3SEC);
			}

			if ((curStatus == WIFI_MOV_ST_RECORD)&&(System_GetState(SYS_STATE_CARD)  == CARD_INSERTED) )
			{

#ifdef AUTO_EVENT_DET_FUNC
				if ((isACCTrigParkMode) && (isACCTrigPreRecordDet)) {
					if ((FlowMovie_GetSOSStatusNow() == FALSE) && (ParkingM_PreRecord_EMR == FALSE)) {
						ImageApp_MovieMulti_TrigEMR(_CFG_REC_ID_1); 
						ImageApp_MovieMulti_TrigEMR(_CFG_REC_ID_2);
						ParkingM_PreRecord_EMR = TRUE;
						FlowMovie_SetSOSStatusNow(TRUE);
						update_sos();

					}
					return ;
				}
#endif
				FlowMovie_SetCrash();
				if (FlowMovie_GetSOSStatusNow() == FALSE) {
					FlowMovie_SetSOSStatusNow(TRUE);
					update_sos();
				}
			}
			/*
				else if((gMovData.State == MOV_ST_VIEW)||(gMovData.State == MOV_ST_REC_WAIT))
				{
					if (System_GetState(SYS_STATE_CARD)  == CARD_INSERT)
					{
						MovRec_SetCrash();
						FlowMovie_IconDrawSOS(&UIFlowWndMovie_SOSCtrl);
						FlowMovie_SetSOSStatusNow(TRUE);
						gMovData.State = MOV_ST_VIEW;
						Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
					}
				}*/
			break;
		}
		break;

	case LV_USER_EVENT_KEY_LONG_PRESS:
		if (bEnterKeyPressed) {
			bEnterKeyPressed = FALSE;
			UIFlowWndMovieWiFi_OnCustom2();
		}
		break;
	}
}
static void UIFlowMovieWiFi_OnKeySOS(lv_obj_t* obj)
{
	static  BOOL bEnterKeyPressed = FALSE;
	UINT32	curStatus = 0;

	curStatus = WiFiCmd_GetStatus();

	switch (key_event)
	{
		case LV_EVENT_KEY:
			bEnterKeyPressed = TRUE;
			break;
		case LV_USER_EVENT_KEY_RELEASE:
			if (!bEnterKeyPressed) {
				DBG_DUMP("enter key ignore.\r\n");
				break;
			}
			bEnterKeyPressed = FALSE;
			switch(curStatus)
			{
			case WIFI_MOV_ST_RECORD:
				if (FlowMovie_WakeUpLCDBacklight())
				{
					//return NVTEVT_CONSUME;
				}

				if (System_GetState(SYS_STATE_CARD)  == CARD_REMOVED)
				{
					//Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_PLEASE_INSERT_SD,FLOWWRNMSG_TIMER_3SEC);
				}

				if ((curStatus == WIFI_MOV_ST_RECORD)&&(System_GetState(SYS_STATE_CARD)  == CARD_INSERTED) )
				{
					FlowMovie_SetCrash();
					if (FlowMovie_GetSOSStatusNow() == FALSE) {
						FlowMovie_SetSOSStatusNow(TRUE);
						update_sos();
					}
				}
				/*
					else if((gMovData.State == MOV_ST_VIEW)||(gMovData.State == MOV_ST_REC_WAIT))
					{
						if (System_GetState(SYS_STATE_CARD)  == CARD_INSERT)
						{
							MovRec_SetCrash();
							FlowMovie_IconDrawSOS(&UIFlowWndMovie_SOSCtrl);
							FlowMovie_SetSOSStatusNow(TRUE);
							gMovData.State = MOV_ST_VIEW;
							Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
						}
					}*/
				break;
			}
			break;
		case LV_USER_EVENT_KEY_LONG_PRESS:
			if (bEnterKeyPressed) {
				bEnterKeyPressed = FALSE;
			}
			break;
		default:
			break;
	}
}


static void UIFlowMovieWiFi_OnKeyCAP(lv_obj_t* obj)
{

	static	BOOL bEnterKeyPressed = FALSE;

	switch (key_event)
	{
		case LV_EVENT_KEY:
			bEnterKeyPressed = TRUE;
			break;
		case LV_USER_EVENT_KEY_RELEASE:
			if (!bEnterKeyPressed) {
				DBG_DUMP("enter key ignore.\r\n");
				break;
			}
			bEnterKeyPressed = FALSE;
			 if (FlowMovie_WakeUpLCDBacklight())
	        {
	            //return NVTEVT_CONSUME;
	        }

	        if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE)
	        {
	            return ;
	        }

	        if ((System_GetState(SYS_STATE_CARD) == CARD_INSERTED) && (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD))
	        {
	        }
			break;
		#if defined(BREATH_LED_FUNC)
		case LV_USER_EVENT_KEY_LONG_PRESS:
			if (bEnterKeyPressed) {
				bEnterKeyPressed = FALSE;
				if (UI_GetData(FL_AMBIANCE_LIGHT) != AMBIANCE_LIGHT_INTERIOR) {
					//DxAmbiance_On(PWM_DUTY_BREATH_FULL);
					//bInterior_LED = TRUE;
					UI_SetData(FL_AMBIANCE_LIGHT_PRE, UI_GetData(FL_AMBIANCE_LIGHT));
					UI_SetData(FL_AMBIANCE_LIGHT, AMBIANCE_LIGHT_INTERIOR);
				} else {
					//bInterior_LED = FALSE;
					//DxAmbiance_On(2);
					//UI_SetData(FL_AMBIANCE_LIGHT, AMBIANCE_LIGHT_ON);
					UI_SetData(FL_AMBIANCE_LIGHT, UI_GetData(FL_AMBIANCE_LIGHT_PRE));
				}
				Ux_SendEvent(&UISetupObjCtrl,	NVTEVT_EXE_AMBIANCE_LIGHT,		1,	SysGetFlag(FL_AMBIANCE_LIGHT));
			}
			break;
		#endif
		default:
			break;
	}
}


static void UIFlowMovieWiFi_OnKeyWiFi(lv_obj_t* obj)
{
	static  BOOL bEnterKeyPressed = FALSE;

	switch (key_event)
	{
		case LV_EVENT_KEY:
			bEnterKeyPressed = TRUE;
			break;
		case LV_USER_EVENT_KEY_RELEASE:
			if (!bEnterKeyPressed) {
				DBG_DUMP("enter key ignore.\r\n");
				break;
			}
			bEnterKeyPressed = FALSE;
			UIFlowWndMovieWiFi_OnCustom2();
			break;
		case LV_USER_EVENT_KEY_LONG_PRESS:
			if (bEnterKeyPressed) {
				bEnterKeyPressed = FALSE;
			}
			break;
		default:
			break;
	}
}
void UIFlowWndWiFiMovie_OnCustom1(void)
{
	DBG_WRN("======== UIFlowWndMovie_OnCustom1 ========\n");

	FlowMovie_SetCrash();
	if (FlowMovie_GetSOSStatusNow() == FALSE)
	{
		FlowMovie_SetSOSStatusNow(TRUE);
		update_sos();
	}
}


static void UIFlowMovieWiFi_FULL(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{
	DBG_DUMP("%s\r\n", __func__);

//	FlowMovie_StopRec();
    FlowWiFiMovie_StopRec();
	UIFlowWrnMsgAPI_Open_StringID(LV_PLUGIN_STRING_ID_STRID_CARD_FULL, warn_msgbox_auto_close_ms);
	update_wifi_icons();
	lv_obj_set_hidden(image_status_rec_scr_uiflowmoviewifi, true);
}

static void UIFlowMovieWiFi_OneSec(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{
	switch (WiFiCmd_GetStatus()) {
	case WIFI_MOV_ST_RECORD:
		if (msg->paramNum) {
			{
				if (SysGetFlag(FL_MOVIE_TIMELAPSE_REC) == MOVIE_TIMELAPSEREC_OFF){
					update_rec_ellipse();
				}
				//lv_obj_set_hidden(label_status_maxtime_scr_uiflowmoviewifi,true);
				FlowMovie_SetRecCurrTime(msg->paramArray[0]);
				update_rec_time();
			}
		}
		if (get_pim_status()){
			set_pim_status(false);
			update_pim();
		}
		break;
	}
}

static void UIFlowMovieWiFi_REC_FINISH(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{
	#if (USE_DCF == ENABLE)
	UINT32  uiFolderId = 0, uiFileId = 0;
	#endif
	DBG_DUMP("%s\r\n", __func__);

	switch (gMovData.State) {
	case MOV_ST_REC:
	case MOV_ST_REC|MOV_ST_ZOOM:

		//#NT#2016/09/20#Bob Huang -begin
		//#NT#Support HDMI Display with 3DNR Out
		//call stop rec first before starting to rec, keep rec mode
#if (_3DNROUT_FUNC == ENABLE)
		if (!gb3DNROut)
#endif
//#NT#2016/09/20#Bob Huang -end
		{
			gMovData.State = MOV_ST_VIEW;
		}

		//#NT#2012/10/23#Philex Lin - begin
		// enable auto power off/USB detect timer
		KeyScan_EnableMisc(TRUE);
		//#NT#2012/10/23#Philex Lin - end
		//lv_obj_set_hidden(label_status_time_scr_uiflowmoviewifi, true);
		update_wifi_icons();
		lv_obj_set_hidden(image_status_rec_scr_uiflowmoviewifi, true);

		break;

	//The flow here may be only for APC3 stop record than lock file function.
	//To be careful that gMovData have changed in UIFlowMovie_Stop.
	case MOV_ST_VIEW:
		#if _TODO
		// Enable key if user pressed shutter2 key to stop recording.
		Input_SetKeyMask(KEY_PRESS, MOVIE_KEY_PRESS_MASK);
		#endif
		break;
	}

}


static void UIFlowMovieWiFi_WR_ERROR(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{
	DBG_DUMP("%s\r\n", __func__);

	if (get_rec_status()||(WiFiCmd_GetStatus()==WIFI_MOV_ST_RECORD)) {
//		FlowMovie_StopRec();
		//set_rec_status(false);
		FlowMovie_SetRecCurrTime(0);
		FlowWiFiMovie_StopRec();
		update_max_rec_time();
		lv_obj_set_hidden(image_status_rec_scr_uiflowmoviewifi, true);
		if (System_GetState(SYS_STATE_CARD)  == CARD_LOCKED) {
			//gMovData.State = MOV_ST_WARNING_MENU;
			UIFlowWrnMsgAPI_Open_StringID(LV_PLUGIN_IMG_ID_ICON_SD_LOCK, warn_msgbox_auto_close_ms);
		} else {
			//gMovData.State = MOV_ST_WARNING_MENU;
			UIFlowWrnMsgAPI_Open_StringID(LV_PLUGIN_STRING_ID_STRID_MEMORYERROR, warn_msgbox_auto_close_ms);
		}
		update_wifi_icons();
	} else {
		// dummy
	}
}

static void UIFlowMovieWiFi_SLOW(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{
	DBG_DUMP("%s\r\n", __func__);

		// stop recoding when slow card event is happening
		FlowMovie_SetRecCurrTime(0);
		FlowWiFiMovie_StopRec();
		update_wifi_icons();

		// restart recording again
		FlowWiFiMovie_StartRec();
}

static void UIFlowMovieWiFi_EMR_COMPLETED(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{
#if (__DBGLVL__ >= 6)
	UINT32  uiPathId = 0;

	if (paramNum)
	{
		uiPathId = paramArray[0];
	}

	DBG_IND("EMR(%d) completed!\r\n", uiPathId);
#endif

	if((msg->paramNum == 2)&&(msg->paramArray[1] == MOVIE_USER_CB_EVENT_EMR_FILE_COMPLETED))
	{
		DBG_IND("EMR(%d) completed!\r\n", uiPathId);
	}
	else if((msg->paramNum == 2)&&(msg->paramArray[1] == MOVIE_USER_CB_EVENT_CARSH_FILE_COMPLETED))
	{
		DBG_IND("Crash (%d) completed!\r\n", uiPathId);
	}
	else if((msg->paramNum == 2)&&(msg->paramArray[1] == MOVIE_USER_CB_EVENT_PREV_CARSH_FILE_COMPLETED))
	{
		DBG_IND("Crash (%d) completed!\r\n", uiPathId);
	}
}

static void UIFlowMovieWiFi_OZOOMSTEPCHG(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{

}

static void UIFlowMovieWiFi_DZOOMSTEPCHG(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{

}

static void UIFlowMovieWiFi_BATTERY(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{

}

static void UIFlowMovieWiFi_STORAGE_CHANGE(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{

}

static void UIFlowMovieWiFi_Authorized_OK(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{
    UINT32 bNewUser = 0 ;
	UINT32 Live555_rtcp_support;

	// start live555 service
	ImageApp_Common_GetParam(0,IACOMMON_PARAM_SUPPORT_RTCP,&Live555_rtcp_support);
	if (Live555_rtcp_support==0)
		ImageApp_Common_RtspStart(0);
    //if (paramNum) {
		bNewUser = msg->paramArray[0];
    //}

	update_wifi(true);
	update_WiFiData(true);
    //LED_TurnOnLED(GPIOMAP_LED_WIFI);
    gWiFiConnect_EN = TRUE;

	if (bNewUser) {
		//delay 500 ms,disconnect last user and
		//in window,use GxTimer replace Timer Delay,it would occupat UI task
		GxTimer_StartTimer(TIMER_HALF_SEC, NVTEVT_DISCONNECT_LAST_TIMER, ONE_SHOT);
	}

#if 0 // Moved to UINet_DhcpSrvCBCliConn.
	//make sure, connec to RTSP mode
	if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE) {
		Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, PRIMARY_MODE_MOVIE);
	}
#endif
}

static void UIFlowMovieWiFi_DEAUTHENTICATED(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{
UINT32 Live555_rtcp_support;

	// stop live555 service
	ImageApp_Common_GetParam(0,IACOMMON_PARAM_SUPPORT_RTCP,&Live555_rtcp_support);
	if (Live555_rtcp_support==0)
		ImageApp_Common_RtspStop(0);

//#NT#2016/03/23#Isiah Chang -begin
//#NT#add new Wi-Fi UI flow.
#if (WIFI_UI_FLOW_VER == WIFI_UI_VER_2_0)
	Ux_PostEvent(NVTEVT_SYSTEM_MODE, 2, System_GetState(SYS_STATE_CURRMODE), SYS_SUBMODE_NORMAL);
#else
	gWiFiConnect_EN = FALSE;

	update_wifi(false);
	update_WiFiData(false);
#if !defined(_NVT_SDIO_WIFI_NONE_) || !defined(_NVT_USB_WIFI_NONE_)
	#if 1//_TODO
	UINet_CliReConnect(1);
	#endif
#endif
#endif
//#NT#2016/03/23#Isiah Chang -end
	//Ux_CloseWindow(pCtrl,0);

	//return NVTEVT_CONSUME;
}

static void UIFlowMovieWiFi_BAK_EVT(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{
	NVTEVT event;
	UINT32 status;

	event = msg->paramArray[ONDONE_PARAM_INDEX_CMD];
	status = msg->paramArray[ONDONE_PARAM_INDEX_RET];
	DBG_DUMP("%s event = 0x%x, status=%d\r\n", __FUNCTION__, event, status);

	switch (event) {
	case NVTEVT_BKW_FORMAT_CARD: {
			WifiCmd_Done(WIFIFLAG_FORMAT_DONE, WIFIAPP_RET_OK);
			//Rsvd
			break;
		}

	case NVTEVT_BKW_FORMAT_NAND: {
			WifiCmd_Done(WIFIFLAG_FORMAT_DONE, WIFIAPP_RET_OK);
			//Rsvd
			break;
		}

	case NVTEVT_BKW_FW_UPDATE: {
			if (status) {
				DBG_ERR("%s:update FW fail %d\r\n", __FUNCTION__, status);
				WifiCmd_Done(WIFIFLAG_UPDATE_DONE, status + WIFIAPP_RET_FW_OFFSET);
			} else {
				//#NT#2016/03/23#Isiah Chang -begin
				//#NT#add new Wi-Fi UI flow.
				INT32 ret;

				WifiCmd_Done(WIFIFLAG_UPDATE_DONE, WIFIAPP_RET_OK);

				ret = FileSys_DeleteFile(FW_UPDATE_NAME);
				if (ret != FST_STA_OK) {
					DBG_ERR("%s:delete FW fail %d\r\n", __FUNCTION__, status);
				}
				//#NT#2016/03/23#Isiah Chang -end
				Delay_DelayMs(2000);
				// Should power off immediatelly
				System_PowerOff(SYS_POWEROFF_NORMAL);
			}
			break;
		}
	case NVTEVT_BKW_WIFI_ON: {
		if (UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK) {
			//change to wifi mode,would close wait wnd
			//change to wifi mode would auto start record movie
			#if (WIFI_FUNC==ENABLE)
		    if (System_GetState(SYS_STATE_CURRMODE) != PRIMARY_MODE_MOVIE){
				#if _TODO
			    Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, PRIMARY_MODE_MOVIE);
				#endif
			}
			//Ux_PostEvent(NVTEVT_OPEN_WINDOW, 1, &UIMenuWndWiFiModuleLinkCtrl);
			Ux_PostEvent(NVTEVT_EXE_MOVIE_STRM_START,0);

			#endif
		} else {
			//Ux_CloseWindow(pCtrl, 0);
            lv_plugin_scr_close(UIFlowWifiLinkOK, NULL);
			#if (WIFI_AP_FUNC==ENABLE)
			//Ux_OpenWindow(&UIMenuWndWiFiModuleLinkCtrl, 0); //show link fail
            lv_plugin_scr_open(UIFlowWifiLink, NULL);
			#endif
		}
		break;
	}
	default:
		DBG_ERR("%s:Unknown event 0x%x\r\n", __FUNCTION__, event);
		break;
	}

}


static void UIFlowMovieWiFi_Key(lv_obj_t* obj, uint32_t key)
{

	switch(key)
	{
	case LV_USER_KEY_SHUTTER2:
	{
		DBG_DUMP("%sLV_USER_KEY_SHUTTER2\r\n", __func__);

		break;
	}

	case LV_USER_KEY_PREV:
	{

		DBG_DUMP("%sLV_USER_KEY_PREV\r\n", __func__);
		UIFlowMovieWiFi_OnKeyPrev(obj);
		break;
	}

	case LV_USER_KEY_NEXT:
	{
		DBG_DUMP("%sLV_USER_KEY_PREV\r\n", __func__);
		UIFlowMovieWiFi_OnExePIM(obj);
		break;
	}

	//#NT#2021/09/10#Philex Lin--begin
	case LV_USER_KEY_ZOOMIN:
	{
		UIFlowMovieWiFi_OnKeyZoomIn(obj);
		break;
	}

	case LV_USER_KEY_ZOOMOUT:
	{
		UIFlowMovieWiFi_OnKeyZoomOut(obj);
		break;
	}

	case LV_USER_KEY_MENU:
	{
		DBG_DUMP("%sLV_USER_KEY_MENU\r\n", __func__);
		UIFlowMovieWiFi_OnKeyDown(obj);
		break;
	}

	case LV_USER_KEY_SELECT:
	{
		DBG_DUMP("%sLV_USER_KEY_SELECT\r\n", __func__);
		UIFlowMovieWiFi_OnKeyDown(obj);
		break;
	}


	case LV_USER_KEY_MODE:
	{

		DBG_DUMP("%sLV_USER_KEY_MODE\r\n", __func__);
		UIFlowMovieWiFi_OnKeyMode(obj);
		break;
	}

	case LV_KEY_ENTER:
	{
		DBG_DUMP("%sLV_KEY_ENTER\r\n", __func__);
		UIFlowMovieWiFi_OnKeySSID(obj);
		break;
	}
	//#NT#2021/09/10#Philex Lin--end

	case LV_KEY_UP:
	{
		DBG_DUMP("%sLV_KEY_UP\r\n", __func__);
		UIFlowMovieWiFi_OnKeyUp(obj);
		break;
	}

	case LV_KEY_DOWN:
	{
		DBG_DUMP("%sLV_KEY_DOWN\r\n", __func__);
		//UIFlowMovieWiFi_OnExePIM(obj);
		UIFlowMovieWiFi_OnKeyDown(obj);
		break;
	}

	case LV_KEY_LEFT:
	{
		DBG_DUMP("%LV_KEY_LEFT\r\n", __func__);
		UIFlowMovieWiFi_OnKeyLeft(obj);
		break;
	}

	case LV_USER_KEY_SOS:
	{
		DBG_DUMP("%sLV_USER_KEY_SOS\r\n", __func__);
		UIFlowMovieWiFi_OnKeySOS(obj);
		break;
	}

	case LV_USER_KEY_CAP:
	{
		DBG_DUMP("%sLV_USER_KEY_CAP\r\n", __func__);
		UIFlowMovieWiFi_OnKeyCAP(obj);
		break;
	}

	case LV_USER_KEY_WIFI:
	{
		DBG_DUMP("%sLV_USER_KEY_WIFI\r\n", __func__);
		UIFlowMovieWiFi_OnKeyWiFi(obj);
		break;
	}

	case LV_USER_KEY_CUSTOM1:
	{
		DBG_DUMP("%sLV_USER_KEY_CUSTOM1\r\n", __func__);
		UIFlowWndWiFiMovie_OnCustom1();
		break;
	}

	}

}

static void UIFlowMovieWiFi_NVTMSG(lv_obj_t* obj, const LV_USER_EVENT_NVTMSG_DATA* msg)
{

	switch(msg->event)
	{
	case NVTEVT_CB_MOVIE_FULL:
		UIFlowMovieWiFi_FULL(obj,msg);
		break;

	case NVTEVT_CB_MOVIE_REC_ONE_SEC:
	{
		UIFlowMovieWiFi_OneSec(obj,msg);
		break;
	}

	//#NT#2021/09/10#Philex Lin--begin
	case NVTEVT_CB_MOVIE_REC_FINISH:
	{
		UIFlowMovieWiFi_REC_FINISH(obj,msg);
		break;
	}

	case NVTEVT_CB_MOVIE_WR_ERROR:
	{
		UIFlowMovieWiFi_WR_ERROR(obj,msg);
		break;
	}

	case NVTEVT_CB_MOVIE_SLOW:
	{
		UIFlowMovieWiFi_SLOW(obj,msg);
		break;
	}

	case NVTEVT_CB_EMR_COMPLETED:
	{
		UIFlowMovieWiFi_EMR_COMPLETED(obj,msg);
		break;
	}

	case NVTEVT_CB_OZOOMSTEPCHG:
	{
		UIFlowMovieWiFi_OZOOMSTEPCHG(obj,msg);
		break;
	}

	case NVTEVT_CB_DZOOMSTEPCHG:
	{
		UIFlowMovieWiFi_DZOOMSTEPCHG(obj,msg);
		break;
	}

	case NVTEVT_BATTERY:
	{
		UIFlowMovieWiFi_BATTERY(obj,msg);
		break;
	}

	case NVTEVT_STORAGE_CHANGE:
	{
		UIFlowMovieWiFi_STORAGE_CHANGE(obj,msg);
		break;
	}

	case NVTEVT_BACKGROUND_DONE:
	{
		NVTEVT message=msg->paramArray[ONDONE_PARAM_INDEX_CMD];
		switch (message)
		{
			case NVTEVT_BKW_STOPREC_PROCESS:
			{
				update_wifi_icons();
			}
			break;

			default:
			break;
		}
		UIFlowMovieWiFi_BAK_EVT(obj,msg);
		break;
	}

	//#NT#2021/09/10#Philex Lin--end
	case NVTEVT_WIFI_AUTHORIZED_OK:
	{
		UIFlowMovieWiFi_Authorized_OK(obj, msg);
		break;
	}

    case NVTEVT_WIFI_DEAUTHENTICATED:
    {
        UIFlowMovieWiFi_DEAUTHENTICATED(obj, msg);
        break;
    }

	default:
		break;

	}
}

void UIFlowMovieWiFiEventCallback(lv_obj_t* obj, lv_event_t event)
{

	switch(event)
	{
	case LV_PLUGIN_EVENT_SCR_OPEN:
		 UIFlowMovieWiFi_ScrOpen(obj);
		break;

	case LV_PLUGIN_EVENT_SCR_CLOSE:
		UIFlowMovieWiFi_ScrClose(obj);
		break;

	case LV_PLUGIN_EVENT_CHILD_SCR_CLOSE:
		UIFlowMovieWiFi_ChildScrClose(obj, (LV_USER_EVENT_NVTMSG_DATA*)lv_event_get_data());
		break;

	/* enter key state changed(pressed -> released) */
	case LV_EVENT_CLICKED:
		//UIFlowMovieWiFi_OnKeyMenu(obj);
		break;

	/* any key(including enter key) state changed(pressed), it's recommended to handle enter key in LV_EVENT_CLICKED instead of here. */
	case LV_EVENT_KEY:
	case LV_USER_EVENT_KEY_RELEASE:
	case LV_USER_EVENT_KEY_LONG_PRESS:
	case LV_USER_EVENT_KEY_SUPER_LONG_PRESS:
	{
		uint32_t* key = (uint32_t*)lv_event_get_data();

		DBG_DUMP("=====LV_EVENT_KEY============");
		if (*key != LV_USER_KEY_CUSTOM1) {
			key_event = event;
		}

		/* handle key event */
		UIFlowMovieWiFi_Key(obj, *key);

		/***********************************************************************************
		 * IMPORTANT!!
		 *
		 * calling lv_indev_wait_release to avoid duplicate event in long pressed key state
		 * the event will not be sent again until released
		 *
		 ***********************************************************************************/
		if(*key != LV_KEY_ENTER&&*key != LV_USER_EVENT_KEY_RELEASE)
			lv_indev_wait_release(lv_indev_get_act());
		break;
	}

	/* handle nvt event except key event */
	case LV_USER_EVENT_NVTMSG:
	{
		const LV_USER_EVENT_NVTMSG_DATA* msg = (const LV_USER_EVENT_NVTMSG_DATA*)lv_event_get_data();

		UIFlowMovieWiFi_NVTMSG(obj, msg);
		break;
	}
	case LV_EVENT_GESTURE:
	{
		lv_gesture_dir_t gesture_dir = lv_indev_get_gesture_dir(lv_indev_get_act());

		LV_UNUSED(gesture_dir); /* avoid compile error, please remove it manually */
		break;
	}

	case LV_EVENT_DRAG_BEGIN:
		break;

	case LV_EVENT_DRAG_END:
		break;

	case LV_EVENT_DRAG_THROW_BEGIN:
		break;

	default:
		break;

	}

}

