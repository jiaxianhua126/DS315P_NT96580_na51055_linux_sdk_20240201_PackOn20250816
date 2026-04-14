#include "PrjInc.h"
#include "UIWnd/LVGL_SPORTCAM/UIInfo/UICfgDefault.h"
#include "UIApp/Network/UIAppWiFiCmdMovie.h"
#include "DxInput.h"

#define __MODULE__          UIMovieFuncs
#define __DBGLVL__          2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>

#define MOVIE_REC_TIME_MIN				10
#define MOVIE_REC_MIN_CLUSTER_SIZE		(0x8000)    // 32KB
#define MOVIE_REC_SD_CLASS				(4)         // class 4

MOV_TASK_DATA   gMovData = { 0 };

static UINT32  g_MovRecMaxTime = 0;
static UINT32  g_MovRecCurrTime = 0;
static UINT32  g_MovRecSelfTimerSec = 0;
static UINT32  g_MovRecSelfTimerID = NULL_TIMER;

extern uint16_t warn_msgbox_auto_close_ms;
extern uint32_t warn_msgbox_auto_infinite_ms;
extern void UIFlowWrnMsgAPI_Open_StringID(lv_plugin_res_id id, uint16_t auto_close_time_ms);
extern void GPIOMap_TurnOnLCDBacklight(void);
extern void GPIOMap_TurnOffLCDBacklight(void);
extern BOOL GPIOMap_IsLCDBacklightOn(void);
extern BOOL ASR_GetPCMData_EN;

UINT8 FlowMovie_GetMovDataState(void)
{
	return gMovData.State;
}

void FlowMovie_StartRec(void)
{
	if (g_MovRecSelfTimerSec == 0) {
		g_MovRecCurrTime = 0;

		if (System_GetState(SYS_STATE_POWERON) == SYSTEM_POWERON_SAFE) {
			// wait playing sound stop
			////GxSound_WaitStop();
		}
		ASR_GetPCMData_EN = FALSE;
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_REC_START, 0);
		ASR_GetPCMData_EN = TRUE;

		// disable auto power off/USB detect timer
		////KeyScan_EnableMisc(FALSE);
		////gMovData.State = MOV_ST_REC;
	} else {
		DBG_ERR("not yet, g_MovSelfTimerSec=%d\r\n", g_MovRecSelfTimerSec);
	}
}

void FlowMovie_StopRec(void)
{
#if (_ADAS_FUNC_ == ENABLE)
	// Fixed icon disappear issue when stop record during ADAS warning window
	UxCtrl_SetShow(&UIFlowWndMovie_Panel_Normal_DisplayCtrl, TRUE);
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Alert_DisplayCtrl, FALSE);
#endif  // #if (_ADAS_FUNC_ == ENABLE)
	FlowMovie_SetSOSStatusNow(FALSE);

	////UxState_SetData(&UIFlowWndMovie_Status_RECCtrl, STATE_CURITEM, UIFlowWndMovie_Status_REC_ICON_REC_TRANSPAENT);
	Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_REC_STOP, 0);

	// enable auto power off/USB detect timer
	////KeyScan_EnableMisc(TRUE);
	gMovData.State = MOV_ST_VIEW;
}

void FlowMovie_StopRecSelfTimer(void)
{
	if (g_MovRecSelfTimerID != NULL_TIMER) {
		GxTimer_StopTimer(&g_MovRecSelfTimerID);
		g_MovRecSelfTimerID = NULL_TIMER;
	}
	g_MovRecSelfTimerSec = 0;
}

UINT8 FlowMovie_GetDataState(void)
{
	return gMovData.State;
}

void FlowMovie_SetRecMaxTime(UINT32 RecMaxTime)
{
	g_MovRecMaxTime = RecMaxTime;
}

UINT32 FlowMovie_GetRecMaxTime(void)
{
	return g_MovRecMaxTime;
}

void FlowMovie_SetRecCurrTime(UINT32 RecCurrTime)
{
	g_MovRecCurrTime = RecCurrTime;
}

UINT32 FlowMovie_GetRecCurrTime(void)
{
	return g_MovRecCurrTime;
}

BOOL FlowMovie_IsStorageErr2(lv_obj_t* parent,BOOL IsCheckFull)
{
#if (MOVIE_ENSURE_SD_32KCLUSTER == ENABLE)
	UINT32  uiClusterSize;
#endif
#if (MOVIE_ENSURE_SD_CLASS4 == ENABLE)
	PSDIO_MISC_INFORMATION pMiscInfo;
#endif

	// check card inserted
	if (System_GetState(SYS_STATE_CARD)  == CARD_REMOVED) {
		UIFlowWrnMsgAPI_Open_StringID(LV_PLUGIN_STRING_ID_STRID_PLEASE_INSERT_SD, warn_msgbox_auto_close_ms);
		return TRUE;
	}

	// check storage error
	if (UIStorageCheck(STORAGE_CHECK_ERROR, NULL) == TRUE) {
		UIFlowWrnMsgAPI_Open_StringID(LV_PLUGIN_STRING_ID_STRID_MEMORYERROR, warn_msgbox_auto_infinite_ms);
		return TRUE;
	}


	// check storage lock or directory read only
	if (UIStorageCheck(STORAGE_CHECK_LOCKED, NULL) == TRUE ||
		UIStorageCheck(STORAGE_CHECK_DCIM_READONLY, NULL) == TRUE) {
		UIFlowWrnMsgAPI_Open_StringID(LV_PLUGIN_STRING_ID_STRID_CARD_LOCKED, warn_msgbox_auto_close_ms);
		return TRUE;
	}

	// check storage full
	if (TRUE == IsCheckFull) {
		g_MovRecMaxTime = Movie_GetFreeSec();
		if (g_MovRecMaxTime <= MOVIE_REC_TIME_MIN) {
			g_MovRecMaxTime = 0;
			UIFlowWrnMsgAPI_Open_StringID(LV_PLUGIN_STRING_ID_STRID_CARD_FULL, warn_msgbox_auto_close_ms);
			return TRUE;
		}
	}

	// check folder full
	if (UIStorageCheck(STORAGE_CHECK_FOLDER_FULL, NULL) == TRUE) {
		UIFlowWrnMsgAPI_Open_StringID(LV_PLUGIN_STRING_ID_STRID_CARD_FULL, warn_msgbox_auto_close_ms);
		return TRUE;
	}

	// check serial number full
	if (MovieExe_CheckSNFull()) {
		UIFlowWrnMsgAPI_Open_StringID(LV_PLUGIN_STRING_ID_STRID_CARD_FULL, warn_msgbox_auto_close_ms);
		return TRUE;
	}

#if (MOVIE_ENSURE_SD_CLASS4 == ENABLE)
	// check sd card whether faster than class 4
	pMiscInfo = sdio_getMiscInfo();
	if (pMiscInfo->uiWriteRate < MOVIE_REC_SD_CLASS) {
		UIFlowWrnMsgAPI_Open_StringID(LV_PLUGIN_STRING_ID_STRID_SD_CLASS4, warn_msgbox_auto_close_ms);
		return TRUE;
	}
#endif

#if (MOVIE_ENSURE_SD_32KCLUSTER == ENABLE)
	// Check cluster size, need to be larger than 32KB
	uiClusterSize = FileSys_GetDiskInfo(FST_INFO_CLUSTER_SIZE);
	if (uiClusterSize < MOVIE_REC_MIN_CLUSTER_SIZE) {
		UIFlowWrnMsgAPI_Open_StringID(LV_PLUGIN_STRING_ID_STRID_CLUSTER_WRONG, warn_msgbox_auto_close_ms);
		return TRUE;
	}
#endif

	return FALSE;
}

UINT32 FlowMovie_GetSelfTimerID(void)
{
	return g_MovRecSelfTimerID;
}

void FlowMovie_OnTimer1SecIndex(void)
{

	switch (gMovData.State) {
	case MOV_ST_VIEW:
	case MOV_ST_VIEW | MOV_ST_ZOOM:
	case MOV_ST_REC:
	case MOV_ST_REC | MOV_ST_ZOOM:
		gMovData.SysTimeCount++;
        #if 0
		if (UxCtrl_IsShow(&UIFlowWndMovie_YMD_StaticCtrl)) {
			FlowMovie_IconDrawDateTime();
		}
        #endif
		break;

	}
}

static volatile UINT32 g_uiMovieAutoLcdPowerSaveCnt = 0;

void FlowMovie_LCDDimDsiable(UINT8 uCount)
{
    g_uiMovieAutoLcdPowerSaveCnt = uCount;
}
void FlowMovie_DetLCDDim(void)
{
}
static volatile BOOL g_PreviewStable_Record = FALSE;

BOOL Get_PreviewStable_Record(void)
{
	DBG_IND("%d\r\n",g_PreviewStable_Record);
	return 	g_PreviewStable_Record;
}
void Set_PreviewStable_Record(BOOL value)
{
	g_PreviewStable_Record = value;
	DBG_IND("%d\r\n",g_PreviewStable_Record);
}
static BOOL   isFirstPowerOn = TRUE;
static UINT32 AutoWiFiCnt = 0;
BOOL autoWifi = FALSE;
UINT32 g_uiPreTimelapse = 0;

void UIFlowWndMovie_OnAutoStartRec(void)
{
	if (Get_PreviewStable_Record() == TRUE)
	{
		if(GPIOMap_DetTVIPlugIn())
		{
			if (System_GetEnableSensor() == (SENSOR_1 | SENSOR_2))
			{
				Set_PreviewStable_Record(FALSE);
				if (gMovData.State != MOV_ST_REC)
				{
					if((!autoWifi) && (/*(SysGetFlag(FL_WIFI) != WIFI_OFF)||*/(SysGetFlag(FL_WIFI_AUTO) == WIFI_AUTO_ON))
						&&isFirstPowerOn)
					{
						DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
						//do not start rec,it starts to wifi
					}
					else
					{
						DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
						Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
					}
				}
			}
		}
		else //no rear connected
		{
			Set_PreviewStable_Record(FALSE);
			if (gMovData.State != MOV_ST_REC)
			{
				if((!autoWifi) && (/*(SysGetFlag(FL_WIFI) != WIFI_OFF)||*/(SysGetFlag(FL_WIFI_AUTO) == WIFI_AUTO_ON))
					&&isFirstPowerOn)
				{
					//do not start rec,it starts to wifi
				}
				else
				{
					Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_RELEASE);
				}
			}
		}
	}
	DBG_IND("%d g_PreviewStable_Record = %d g_isRearOK=%d autoWifi=%d isFirstPowerOn=%d\r\n",(System_GetState(SYS_STATE_POWERON) == SYSTEM_POWERON_SAFE),g_PreviewStable_Record,g_isRearOK,autoWifi,isFirstPowerOn);
}
void UIFlowMoive_AutoStartWiFi(void)
{
	// DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);

	// DBG_DUMP("%s SysGetFlag(FL_WIFI_AUTO) = %d line = %d\r\n", __func__, SysGetFlag(FL_WIFI_AUTO), __LINE__);
#if (!defined(_NVT_ETHREARCAM_TX_))//(AUTO_WIFI==ENABLE)
	if ((!autoWifi) && (/*(SysGetFlag(FL_WIFI) != WIFI_OFF)||*/(SysGetFlag(FL_WIFI_AUTO) == WIFI_AUTO_ON))) {
        if (isFirstPowerOn/* && GPIOMap_DetTV()*/) {
			DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
			AutoWiFiCnt++;
			DBG_DUMP("AutoWiFiCnt=%d\r\n", AutoWiFiCnt);
            if ((AutoWiFiCnt >= 4)) {
				DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
				WifiStarting = TRUE;
                if ((gMovData.State == MOV_ST_REC)||(gMovData.State == (MOV_ST_REC|MOV_ST_ZOOM))) {
                    if ((FlowMovie_GetRecCurrTime() <= 1)&&(SysGetFlag(FL_MOVIE_TIMELAPSE_REC) == MOVIE_TIMELAPSEREC_OFF)) {
                        Delay_DelayMs(1000);
                    }
                    FlowMovie_StopRec();
                    Delay_DelayMs(100);
                }

                //disable timelapse recording
                UI_SetData(FL_MOVIE_TIMELAPSE_REC, MOVIE_TIMELAPSEREC_OFF);
                UI_SetData(FL_MOVIE_TIMELAPSE_REC_MENU, MOVIE_TIMELAPSEREC_OFF);
                g_uiPreTimelapse = UI_GetData(FL_MOVIE_TIMERLAPS);
                UI_SetData(FL_MOVIE_TIMERLAPS, MOVIE_TIMER_LAPS_OFF);

                SysSetFlag(FL_WIFI_AUTO, WIFI_AUTO_OFF);
				if (SysGetFlag(FL_LED) == LED_ON) {
					//LED_TurnOnLED(GPIOMAP_LED_WIFI);
				}
				Control_LedTurn(WIFI_LED,1);
                //GxLED_SetCtrl(KEYSCAN_LED_FCS, TURNON_LED, TRUE);
                //#NT#2016/03/23#Isiah Chang -begin
                //#NT#add new Wi-Fi UI flow.
				DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
                #if(WIFI_UI_FLOW_VER == WIFI_UI_VER_1_0)
				DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
				lv_plugin_scr_open(UIFlowWifiWait, NULL);
                #endif
                //#NT#2016/03/23#Isiah Chang -end
                BKG_PostEvent(NVTEVT_BKW_WIFI_ON);
                autoWifi = TRUE;
                isFirstPowerOn = FALSE;
                AutoWiFiCnt = 0;
            }
        } else {
			DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
			WifiStarting = TRUE;
			if ((gMovData.State == MOV_ST_REC) || (gMovData.State == (MOV_ST_REC | MOV_ST_ZOOM))) {
				if ((FlowMovie_GetRecCurrTime() <= 1) &&
					(SysGetFlag(FL_MOVIE_TIMELAPSE_REC) == MOVIE_TIMELAPSEREC_OFF)) {
					Delay_DelayMs(1000);
				}
				FlowMovie_StopRec();
				Delay_DelayMs(100);
			}

			UI_SetData(FL_MOVIE_TIMELAPSE_REC, MOVIE_TIMELAPSEREC_OFF);
			UI_SetData(FL_MOVIE_TIMELAPSE_REC_MENU, MOVIE_TIMELAPSEREC_OFF);
			g_uiPreTimelapse = UI_GetData(FL_MOVIE_TIMERLAPS);
			UI_SetData(FL_MOVIE_TIMERLAPS, MOVIE_TIMER_LAPS_OFF);

			SysSetFlag(FL_WIFI_AUTO, WIFI_AUTO_OFF);
			Control_LedTurn(WIFI_LED, 1);
			#if (WIFI_UI_FLOW_VER == WIFI_UI_VER_1_0)
			lv_plugin_scr_open(UIFlowWifiWait, NULL);
			#endif
			BKG_PostEvent(NVTEVT_BKW_WIFI_ON);
			autoWifi = TRUE;
			isFirstPowerOn = FALSE;
		}
	} else {
		// DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
		autoWifi = TRUE;
		isFirstPowerOn = FALSE;
	}
#endif
}

void FlowMovie_SetCrash(void)
{
	//if (SysGetFlag(FL_MOVIE_URGENT_PROTECT_AUTO) == MOVIE_URGENT_PROTECT_AUTO_ON)
	DBG_DUMP("^GFlowMovie_SetCrash type=%d\r\n",GetMovieRecType_2p(UI_GetData(FL_MOVIE_SIZE)));
#if(defined(_NVT_ETHREARCAM_RX_))
	if (1) {
		ImageApp_MovieMulti_SetCrash(_CFG_REC_ID_1, TRUE);
		UINT32 i;
		for (i = 0; i < ETH_REARCAM_CAPS_COUNT; i++) {
			if(socketCliEthData1_IsRecv(ETHCAM_PATH_ID_1 +i)){
				ImageApp_MovieMulti_SetCrash(_CFG_ETHCAM_ID_1+i, TRUE);
			}
			#if (ETH_REARCAM_CLONE_FOR_DISPLAY == ENABLE)
			if(g_EthCamCfgDisplayPathWriteFile){
				if(socketCliEthData2_IsRecv(ETHCAM_PATH_ID_1 +i)){
					ImageApp_MovieMulti_SetCrash(_CFG_ETHCAM_CLONE_ID_1+i, TRUE);
				}
			}
			#endif
		}
	}
	else
#endif
	{
		UINT32 i, mask, movie_rec_mask;

			movie_rec_mask = Movie_GetMovieRecMask();
		mask = 1;
		for (i = 0; i < (SENSOR_CAPS_COUNT& SENSOR_ON_MASK); i++) {
			if (movie_rec_mask & mask) {
				ImageApp_MovieMulti_SetCrash(_CFG_REC_ID_1 + i, TRUE);
			}
			mask <<= 1;
		}
		#if(defined(_NVT_ETHREARCAM_RX_))
		for (i = 0; i < ETH_REARCAM_CAPS_COUNT; i++) {
			if(socketCliEthData1_IsRecv(ETHCAM_PATH_ID_1 +i)){
				ImageApp_MovieMulti_SetCrash(_CFG_ETHCAM_ID_1+i, TRUE);
			}
			#if (ETH_REARCAM_CLONE_FOR_DISPLAY == ENABLE)
			if(g_EthCamCfgDisplayPathWriteFile){
				if(socketCliEthData2_IsRecv(ETHCAM_PATH_ID_1 +i)){
					ImageApp_MovieMulti_SetCrash(_CFG_ETHCAM_CLONE_ID_1+i, TRUE);
				}
			}
			#endif
		}
		#endif
	}
}
static BOOL SOS_Status_now = FALSE;

void FlowMovie_SetSOSStatusNow(BOOL En)
{
    SOS_Status_now = En;
}
BOOL FlowMovie_GetSOSStatusNow(void)
{
    return SOS_Status_now;
}
BOOL FlowMovie_WakeUpLCDBacklight(void)
{
	DBG_DUMP("%s line = %d\r\n", __func__, __LINE__);
    return FALSE;
}
void FlowMovie_UpdateLED(void)
{
}
