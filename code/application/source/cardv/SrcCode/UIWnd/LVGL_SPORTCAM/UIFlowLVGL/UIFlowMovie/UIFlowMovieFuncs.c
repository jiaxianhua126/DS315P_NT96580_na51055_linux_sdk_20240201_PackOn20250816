#include "PrjInc.h"
#include "Utility/SwTimer.h"
#include "UIWnd/LVGL_SPORTCAM/UIInfo/UICfgDefault.h"
#include "UIApp/Network/UIAppWiFiCmdMovie.h"
#include "UIApp/Network/WifiAppCmd.h"
#include "DxInput.h"
#include "KyAdas/algo_result.h"

#define __MODULE__          UIMovieFuncs
#define __DBGLVL__          2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>

// Function prototypes
void FlowMovie_SetLCDDimStatus(BOOL En);
BOOL FlowMovie_GetLCDDimStatus(void);
void FlowMovie_LCDIconDimDsiable(UINT8 uCount);
UINT32 FlowMovie_CheckDateValue(void);

#define MOVIE_REC_TIME_MIN				10
#define MOVIE_REC_MIN_CLUSTER_SIZE		(0x8000)    // 32KB
#define MOVIE_REC_SD_CLASS				(4)         // class 4

MOV_TASK_DATA   gMovData = { 0 };

static UINT32  g_MovRecMaxTime = 0;
static UINT32  g_MovRecCurrTime = 0;
static UINT32  g_MovRecSelfTimerSec = 0;
static UINT32  g_MovRecSelfTimerID = NULL_TIMER;
static volatile BOOL   g_bMovieAutoLcdPowerSaveStatus = FALSE;
static BOOL g_GS_ParkingMode = FALSE;
static BOOL g_ACCPowerOff = FALSE;
static UINT32 g_uIconHideCnt = 0;
static UINT32 uiBaseDay = DEFAULT_FORMAT_WARNING_DATE;
static BOOL sbSpecailFormatWarningFlg = FALSE;
static UINT8 g_FileRecoveryFlag = 0;
static BOOL g_bMovieHDR_changed = FALSE;

// Global variables
BOOL g_NotRecordWrn = FALSE;
BOOL WifiStarting = FALSE;
UINT32 g_wifi_movie_rec_curr_time = 0;
BOOL g_bWiFiMovieHDR_changed = FALSE;
BOOL WifiMotionLed_EN = FALSE;
BOOL ParkingM_PreRecord_EMR = FALSE;

// Buffers
char CarNo_Buf[13] = {0};
char Customize_Buf[13] = {0};
char g_GPSstamp_buffer[128] = {0};
char gUICustomer_Model[20] = {0};
char gUICustomer_Null[20] = {0};
char gUICustomer_StrBuf[20] = {0};
char gUICarNo_StrBuf[13] = {0};
char gUICustomize_StrBuf[13] = {0};

// Event data
AlgoEventData rcw_eventData_app;
AlgoEventData adas_eventData_app;

// VControl variables
VControl UIFlowWndWrnMsgCtrl;
VControl UIFlowWndMovie_Panel_Normal_DisplayCtrl;
VControl UIFlowWndMovie_ADAS_Alert_DisplayCtrl;
VControl UIMenuWndWiFiMobileLinkOKCtrl;




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





UINT32 FlowMovie_GetSelfTimerID(void)
{
	return g_MovRecSelfTimerID;
}

BOOL FlowMovie_IsStorageErr2(lv_obj_t* parent,BOOL IsCheckFull)
{
	// LVGL-specific implementation
	
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

	return FALSE;
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
    static UINT32 idlePeriod = 0;

    if ((KeyScan_GetPlugDev() == PLUG_TV) || (KeyScan_GetPlugDev() == PLUG_HDMI)) {
        return;
    }

    if (FlowMovie_GetSOSStatusNow() && (SysGetFlag(FL_MOVIE_TIMELAPSE_REC) == MOVIE_TIMELAPSEREC_OFF)) {
        g_uiMovieAutoLcdPowerSaveCnt = 0;
        g_bMovieAutoLcdPowerSaveStatus = FALSE;
    }

    idlePeriod = FlowMovie_CheckDateValue();
    if (idlePeriod == 0) {
        return;
    }

    if (g_uiMovieAutoLcdPowerSaveCnt >= idlePeriod) {
        GPIOMap_TurnOffLCDBacklight();
        g_uiMovieAutoLcdPowerSaveCnt = 0;
        g_bMovieAutoLcdPowerSaveStatus = TRUE;
    } else {
        g_uiMovieAutoLcdPowerSaveCnt++;
    }
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
    FlowMovie_LCDDimDsiable(0); //reset count
	FlowMovie_LCDIconDimDsiable(0); //reset count

    if ((FlowMovie_GetLCDDimStatus()||(GPIOMap_IsLCDBacklightOn() == FALSE))
        &&(KeyScan_GetPlugDev() != PLUG_TV)
        &&(KeyScan_GetPlugDev() != PLUG_HDMI))
    {
        GPIOMap_TurnOnLCDBacklight();
        FlowMovie_SetLCDDimStatus(FALSE);
        DBG_DUMP("call FlowMovie_WakeUpLCDBacklight\r\n");
        return TRUE;
    }
    return FALSE;
}
void FlowMovie_UpdateLED(void)
{
}

void FlowMovie_SetLCDDimStatus(BOOL En)
{
    g_bMovieAutoLcdPowerSaveStatus = En;
}

BOOL FlowMovie_GetLCDDimStatus(void)
{
    return g_bMovieAutoLcdPowerSaveStatus;
}

void FlowMovie_LCDIconDimDsiable(UINT8 uCount)
{
    g_uIconHideCnt = uCount;
}

void FlowMovie_DetLCDIconHide(void)
{
	if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI)
	{
		// LVGL-specific implementation
	} else {
		// LVGL-specific implementation
	}
}

UINT32 FlowMovie_CheckDateValue(void)
{
    UINT32 uiDateValue = 0;

    switch (SysGetFlag(FL_FORMAT_WARNING)) {
    case FORMAT_WARNING_15_DAY:
        uiDateValue = 15;
        break;
    case FORMAT_WARNING_30_DAY:
        uiDateValue = 30;
        break;
    case FORMAT_WARNING_60_DAY:
        uiDateValue = 60;
        break;
    case FORMAT_WARNING_OFF:
        uiDateValue = 0xFFFF;
        break;
    }
    return uiDateValue;
}



UINT32 FlowMovie_BaseDayGet(void)
{
    uiBaseDay = UI_GetData(FL_FORMAT_WARNING_DATE);

    return uiBaseDay;
}

void FlowMovie_SaveBaseDay(void)
{
    struct tm Curr_DateTime;
    Curr_DateTime = hwclock_get_time(TIME_ID_CURRENT);

    FlowMovie_BaseDaySet(Curr_DateTime.tm_year, Curr_DateTime.tm_mon, Curr_DateTime.tm_mday);
}

void FlowMovie_Specail_Flag_Set(BOOL std)
{
    sbSpecailFormatWarningFlg = std;
}

UINT32 FlowMovie_Specail_Flag_Get(void)
{
    return sbSpecailFormatWarningFlg;
}

BOOL FlowMovie_Specail_FormatWarning(void)
{
    return FALSE;
}


/* 返回绝对值 */
int BaseDay_abs(int a,int b)
{
    if(a>=b)
        return (a-b);
    else
        return (b-a);
}

/* 判断是否为闰年:是,返回 1 ; 不是, 返回 0 . */
int BaseDay_IsLeap(int year)
{
    if(((year%4==0)&&(year%100!=0))||year%400==0)
        return 1;
    else
        return 0;
}

/* 判断某个日期从年初(y年1月1日)到该天(y年m月d日)的天数 */
int BaseDay_Days(int y,int m,int d)
{
    int days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int i;
    int sum = 0 ;  /* 计算天数 */

    if(BaseDay_IsLeap(y)) /* 如果为闰年,2月有 29 天 */
        days[2] = 29;
    for(i=0;i<m;i++)
        sum = sum +days[i] ;
    sum = sum + d - 1 ;
    return sum;
}

/*
 判断两个日期之间的天数.
 日期一:年 y1,月 m1,日 d1;
 日期一:年 y2,月 m2,日 d2;
*/
int BaseDay_DiffDays(int y1,int m1,int d1,int y2,int m2,int d2)
{
    int s1,s2; /* 计算两个日期从年初到该日期的天数 */
    int count; /* 计算两个年份之间的差值 */
    int sum=0; /*                        */
    int t,t1,t2;

    if(y1==y2)
    {
        s1 = BaseDay_Days(y1,m1,d1);
        s2 = BaseDay_Days(y2,m2,d2);
        return BaseDay_abs(s1,s2);  
    }
    else if(y1>y2)
    {
        count = y1 - y2 ;
        if(count == 1)
        {
            t1 = BaseDay_Days(y1,m1,d1);
            t2 = BaseDay_Days(y2,12,31) - BaseDay_Days(y2,m2,d2);
            return (t1+t2+count);
        }
        else
        {   
            for(t = y2+1;t<y1;t++)
                sum = sum + BaseDay_Days(t,12,31);
            //cout<<sum<<endl;
            t2 = BaseDay_Days(y2,12,31) - BaseDay_Days(y2,m2,d2);
            t1 = BaseDay_Days(y1,m1,d1);
            return (sum+t1+t2+count);
        }
    }
    else
    {
        count = y2 - y1 ;
        if(count == 1)
        {
            t2 = BaseDay_Days(y2,m2,d2);
            t1 = BaseDay_Days(y1,12,31) - BaseDay_Days(y1,m1,d1);
            return (t1+t2+count);
        }
        else
        {
            for(t = y1+1;t<y2;t++)
                sum = sum + BaseDay_Days(t,12,31);
            t2 = BaseDay_Days(y2,m2,d2);
            t1 = BaseDay_Days(y1,12,31) - BaseDay_Days(y1,m1,d1);
            return (sum+t1+t2+count);
        }
    }
}

BOOL FlowMovie_CheckFormatWrning(void)
{
    UINT32  uiDayDiff = 0;
    UINT32  base_year,base_month,base_day;
    struct  tm Curr_DateTime = {0};

    if(UI_GetData(FL_FORMAT_WARNING) == FORMAT_WARNING_OFF)
        return FALSE;

    FlowMovie_BaseDayGet();

    base_year = uiBaseDay/10000;
    base_month = uiBaseDay/100 - base_year*100;
    base_day = uiBaseDay - base_year*10000 - base_month*100;

    Curr_DateTime = hwclock_get_time(TIME_ID_CURRENT);

    uiDayDiff = BaseDay_DiffDays(Curr_DateTime.tm_year, Curr_DateTime.tm_mon, Curr_DateTime.tm_mday, base_year, base_month, base_day);

    if(uiDayDiff > FlowMovie_CheckDateValue())
        return TRUE;
    else
        return FALSE;
}

void FlowMovie_DetVx1LED(UINT8 uState)
{
    // LVGL-specific implementation
}





void FlowMovie_SetGsensorParkingModeStatus(BOOL En)
{
    g_GS_ParkingMode = En;
}

BOOL FlowMovie_GetGsensorParkingModeStatus(void)
{
    return g_GS_ParkingMode;
}

void FlowMovie_SetACCPowerOffStatus(BOOL En)
{
    g_ACCPowerOff = En;
}

BOOL FlowMovie_GetACCPowerOffStatus(void)
{
    return g_ACCPowerOff;
}

UINT32 FlowMovie_GetTimelapseCyclicValue(void)
{
    UINT32 uiCyclicRecTime = 0;
    UINT32 num = 1;

    switch (UI_GetData(FL_MOVIE_TIMELAPSE_REC)) {
    case MOVIE_TIMELAPSEREC_100MS:
        uiCyclicRecTime = 180;
        break;
    case MOVIE_TIMELAPSEREC_200MS:
        uiCyclicRecTime = 360;
        break;
    case MOVIE_TIMELAPSEREC_500MS:
        uiCyclicRecTime = 900;
        break;
    case MOVIE_TIMELAPSEREC_1SEC:
        uiCyclicRecTime = 1800;
        break;
    case MOVIE_TIMELAPSEREC_2SEC:
        uiCyclicRecTime = 3600;
        break;
    case MOVIE_TIMELAPSEREC_5SEC:
        uiCyclicRecTime = 9000;
        break;
    case MOVIE_TIMELAPSEREC_10SEC:
        uiCyclicRecTime = 18000;
        break;
    case MOVIE_TIMELAPSEREC_30SEC:
        uiCyclicRecTime = 54000;
        break;
    case MOVIE_TIMELAPSEREC_1MIN:
        uiCyclicRecTime = 108000;
        break;
    case MOVIE_TIMELAPSEREC_5MIN:
        uiCyclicRecTime = 540000;
        break;
    case MOVIE_TIMELAPSEREC_10MIN:
        uiCyclicRecTime = 1080000;
        break;
    default:
        uiCyclicRecTime = 1800;
        break;
    }

    switch (UI_GetData(FL_MOVIE_CYCLIC_REC)) {
    case MOVIE_CYCLICREC_1MIN:
        num = 1;
        break;
    case MOVIE_CYCLICREC_2MIN:
        num = 2;
        break;
    case MOVIE_CYCLICREC_3MIN:
        num = 3;
        break;
    case MOVIE_CYCLICREC_5MIN:
        num = 5;
        break;
    case MOVIE_CYCLICREC_10MIN:
        num = 10;
        break;
    case MOVIE_CYCLICREC_OFF:
        num = 12;
        break;
    }

    uiCyclicRecTime = num * uiCyclicRecTime;

    return uiCyclicRecTime;
}

UINT32 FlowMovie_GetParkingModeTLCyclicValue(void)
{
    UINT32 uiCyclicRecTime = 0;
    UINT32 num = 1;

    switch (UI_GetData(FL_PARKING_MODE_TIMELAPSE_REC)) {
    case PARKING_MODE_TIMELAPSEREC_66MS:
        uiCyclicRecTime = 120;
        break;
    case PARKING_MODE_TIMELAPSEREC_100MS:
        uiCyclicRecTime = 180;
        break;
    case PARKING_MODE_TIMELAPSEREC_200MS:
        uiCyclicRecTime = 360;
        break;
    case PARKING_MODE_TIMELAPSEREC_333MS:
        uiCyclicRecTime = 601;
        break;
    case PARKING_MODE_TIMELAPSEREC_500MS:
        uiCyclicRecTime = 900;
        break;
    case PARKING_MODE_TIMELAPSEREC_1SEC:
        uiCyclicRecTime = 1800;
        break;
    }

    switch (UI_GetData(FL_MOVIE_CYCLIC_REC)) {
    case MOVIE_CYCLICREC_1MIN:
        num = 1;
        break;
    case MOVIE_CYCLICREC_2MIN:
        num = 2;
        break;
    case MOVIE_CYCLICREC_3MIN:
        num = 3;
        break;
    case MOVIE_CYCLICREC_5MIN:
        num = 5;
        break;
    case MOVIE_CYCLICREC_10MIN:
        num = 10;
        break;
    case MOVIE_CYCLICREC_OFF:
        num = 12;
        break;
    }

    uiCyclicRecTime = num * uiCyclicRecTime;

    return uiCyclicRecTime;
}

UINT32 FlowMovie_GetShutdownTimer(void)
{
    UINT32 uiShutdownTime = 0;

    switch (SysGetFlag(FL_SHUTDOWN_TIMER)) {
    case SHUTDOWN_TIMER_5MIN:
        uiShutdownTime = 300;
        break;
    case SHUTDOWN_TIMER_10MIN:
        uiShutdownTime = 600;
        break;
    case SHUTDOWN_TIMER_30MIN:
        uiShutdownTime = 1800;
        break;
    case SHUTDOWN_TIMER_1HOUR:
        uiShutdownTime = 3600;
        break;
    case SHUTDOWN_TIMER_2HOUR:
        uiShutdownTime = 2*3600;
        break;
    case SHUTDOWN_TIMER_3HOUR:
        uiShutdownTime = 3*3600;
        break;
    case SHUTDOWN_TIMER_4HOUR:
        uiShutdownTime = 4*3600;
        break;
    case SHUTDOWN_TIMER_6HOUR:
        uiShutdownTime = 6*3600;
        break;
    case SHUTDOWN_TIMER_8HOUR:
        uiShutdownTime = 8*3600;
        break;
    case SHUTDOWN_TIMER_12HOUR:
        uiShutdownTime = 12*3600;
        break;
    case SHUTDOWN_TIMER_18HOUR:
        uiShutdownTime = 18*3600;
        break;
    case SHUTDOWN_TIMER_24HOUR:
        uiShutdownTime = 24*3600;
        break;
    case SHUTDOWN_TIMER_48HOUR:
        uiShutdownTime = 48*3600;
        break;
    default:
        uiShutdownTime = 600;
        break;
    }

    return uiShutdownTime;
}

#define VIDEO_FILE_RECOVERY  "A:\\VideoRecovery.nvt"

void FlowMovie_WriteRecoveryTxt(UINT8 num)
{
    FST_FILE fp = NULL;
    CHAR ui_IntoLockFile[1] = {0};
    UINT32 pBufSize = 1;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        return;
    }

    fp = FileSys_OpenFile(VIDEO_FILE_RECOVERY, FST_CREATE_ALWAYS|FST_OPEN_WRITE);
    if (fp) {
        sprintf(ui_IntoLockFile, "%d", num);
        FileSys_SeekFile(fp, 0, FST_SEEK_SET);
        FileSys_WriteFile(fp, (UINT8 *)ui_IntoLockFile, &pBufSize, 0, NULL);
        FileSys_CloseFile(fp);
    }
}

void FlowMovie_CreateFileRecoveryTxt(void)
{
    FST_FILE fp = NULL;
    INT32 ret = -1;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        return;
    }

    if (UI_GetData(FL_VIDEO_FORMAT) == VIDEO_FORMAT_TS) {
        return;
    }

    fp = FileSys_OpenFile(VIDEO_FILE_RECOVERY, FST_OPEN_READ|FST_OPEN_WRITE|FST_OPEN_ALWAYS);
    if (fp) {
        FileSys_CloseFile(fp);
        DBG_DUMP("create %s Success.\r\n", VIDEO_FILE_RECOVERY);
        ret = FileSys_SetAttrib(VIDEO_FILE_RECOVERY, FST_ATTRIB_HIDDEN, TRUE);
        if (ret == FST_STA_OK) {
            DBG_DUMP("set %s hidden Success.\r\n", VIDEO_FILE_RECOVERY);
        }

        if (System_GetEnableSensor() == (SENSOR_1|SENSOR_2)) {
            //FlowMovie_WriteRecoveryTxt(2);//two sensor
        } else {
            //FlowMovie_WriteRecoveryTxt(1);//one sensor
        }
    } else {
        DBG_DUMP("create indication %s failed.\r\n", VIDEO_FILE_RECOVERY);
    }
}

void FlowMovie_DeleteFileRecoveryTxt(void)
{
    FST_FILE fp = NULL;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        return;
    }

    fp = FileSys_OpenFile(VIDEO_FILE_RECOVERY, FST_OPEN_READ);
    if (fp) {
        FileSys_CloseFile(fp);
        if (FileSys_DeleteFile(VIDEO_FILE_RECOVERY) != FST_STA_OK) {
            DBG_DUMP("Delete %s failed.\r\n", VIDEO_FILE_RECOVERY);
        } else {
            DBG_DUMP("Delete %s Success.\r\n", VIDEO_FILE_RECOVERY);
        }
    }
}

UINT8 FlowMovie_ReadRecoveryTxt(void)
{
    FST_FILE fp = NULL;
    char buf_tmp[4] = {0};
    UINT8 num = 0;
    UINT32 pBufSize = 1;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        return 0;
    }

    fp = FileSys_OpenFile(VIDEO_FILE_RECOVERY, FST_OPEN_READ);
    if (fp) {
        FileSys_SeekFile(fp, 0, FST_SEEK_SET);
        FileSys_ReadFile(fp, (UINT8 *)&buf_tmp, &pBufSize, 0, NULL);
        FileSys_CloseFile(fp);
        num = atoi(buf_tmp);
        DBG_DUMP("*** Recovery num = %d ***\r\n", num);
    }
    return num;
}

BOOL FlowMovie_CheckFileRecoveryTxt(void)
{
    if (UIStorageCheck(STORAGE_CHECK_ERROR, NULL) == TRUE) {
        return FALSE;
    }

    if (System_GetState(SYS_STATE_CARD) == CARD_INSERTED) {
        FST_FILE fp = NULL;

        fp = FileSys_OpenFile(VIDEO_FILE_RECOVERY, FST_OPEN_READ);
        if (fp) {
            FileSys_CloseFile(fp);
            g_FileRecoveryFlag = FlowMovie_ReadRecoveryTxt();
            DBG_DUMP("Check %s is existing, g_FileRecoveryFlag= %d \r\n", VIDEO_FILE_RECOVERY, g_FileRecoveryFlag);
            if (FileSys_DeleteFile(VIDEO_FILE_RECOVERY) != FST_STA_OK) {
                DBG_DUMP("Delete %s failed\r\n", VIDEO_FILE_RECOVERY);
                return FALSE;
            } else {
                DBG_DUMP("Delete %s Success.\r\n", VIDEO_FILE_RECOVERY);
            }
            return TRUE;
        }
    }
    return FALSE;
}

extern BOOL g_bMovieHDR_changed;
extern BOOL g_NotRecordWrn;
extern BOOL FlowMovie_CheckReOpenItem(void);

void FlowMovie_AutoHDR(void)
{
    struct tm Curr_DateTime = {0};
    UINT32 time_start = 0;
    UINT32 time_stop = 0;
    UINT32 temp = 0;

    time_start = SysGetFlag(FL_TIME_START);
    time_stop = SysGetFlag(FL_TIME_STOP);

    if (time_start >= time_stop) {
        return;
    }

    Curr_DateTime = hwclock_get_time(TIME_ID_CURRENT);
    temp = Curr_DateTime.tm_hour*100 + Curr_DateTime.tm_min;

    if ((((temp >= 0) && (temp < time_start)) || ((temp >= time_stop) && (temp <= 2359)))
        && (SysGetFlag(FL_MOVIE_HDR) == MOVIE_HDR_OFF))
    {
        if ((gMovData.State == MOV_ST_REC)||(gMovData.State == (MOV_ST_REC|MOV_ST_ZOOM))) {
            FlowMovie_StopRec();
            Delay_DelayMs(300);
        }
        g_NotRecordWrn = FALSE;
        g_bMovieHDR_changed = TRUE;
        SysSetFlag(FL_MOVIE_HDR, MOVIE_HDR_ON);
        SysSetFlag(FL_MOVIE_HDR_MENU, MOVIE_HDR_ON);
        SysSetFlag(FL_MOVIE_WDR, MOVIE_WDR_ON);
        SysSetFlag(FL_MOVIE_WDR_MENU, MOVIE_WDR_ON);
		FlowMovie_CheckReOpenItem();
        Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, System_GetState(SYS_STATE_CURRMODE));
    }
    else if ((temp >= time_start) && (temp < time_stop) && (SysGetFlag(FL_MOVIE_HDR) == MOVIE_HDR_ON))
    {
        if ((gMovData.State == MOV_ST_REC)||(gMovData.State == (MOV_ST_REC|MOV_ST_ZOOM))) {
            FlowMovie_StopRec();
            Delay_DelayMs(300);
        }
        g_NotRecordWrn = FALSE;
        g_bMovieHDR_changed = TRUE;
        SysSetFlag(FL_MOVIE_HDR, MOVIE_HDR_OFF);
        SysSetFlag(FL_MOVIE_HDR_MENU, MOVIE_HDR_OFF);
        SysSetFlag(FL_MOVIE_WDR, MOVIE_WDR_OFF);
        SysSetFlag(FL_MOVIE_WDR_MENU, MOVIE_WDR_OFF);
		FlowMovie_CheckReOpenItem();
        Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, System_GetState(SYS_STATE_CURRMODE));
    }
}

#if 1//(GPS_PANEL_FUNC==ENABLE)
BOOL  g_bSpeedPanelInit = FALSE;
void FlowMovie_UpdateADASPanel(void)
{
	if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) {
		// LVGL-specific implementation
	} else {
		// LVGL-specific implementation
	}
}
#endif

// Missing functions
UINT32 FlowWiFiMovie_GetRecCurrTime(void)
{
    return g_wifi_movie_rec_curr_time;
}

void FlowWiFiMovie_SetRecCurrTime(UINT32 time)
{
    g_wifi_movie_rec_curr_time = time;
}

void FlowMovie_BaseDaySet(int year, int month, int day)
{
    // Implementation placeholder
}

BOOL FlowMovie_IsEthCamConnectOK(void)
{
    return FALSE; // Default implementation
}

BOOL FlowMovie_IsStorageErr(BOOL IsCheckFull)
{
    return FALSE; // Default implementation
}

void FlowMovie_SetLedFlash_BeepWrn(BOOL bEnable)
{
    // Implementation placeholder
}

void FlowWiFiMovie_UpdateIcons(BOOL bShow)
{
    // Implementation placeholder
}

void FlowWiFiMovie_IconDrawTimelapse(BOOL bEnable)
{
    // Implementation placeholder
}

void FlowWiFiMovie_IconDrawMotionDet(BOOL bEnable)
{
    // Implementation placeholder
}

void FlowWiFiMovie_IconDrawAudio(BOOL bEnable)
{
    // Implementation placeholder
}

void FlowMovie_USBRemovePowerOff(void)
{
    // Implementation placeholder
}

INT32 UIFlowWndWiFiMovie_OnCustom2(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
    // Implementation placeholder
    return 0;
}

void UIFlowWndWiFiMovie_StopTimer(void)
{
    // Implementation placeholder
}

UINT32 UIMenuWndPlayFileType_GetFileType(void)
{
    // Implementation placeholder
    return 0;
}


