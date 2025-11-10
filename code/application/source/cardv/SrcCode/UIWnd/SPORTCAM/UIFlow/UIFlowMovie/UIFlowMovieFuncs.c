#include "PrjInc.h"
#include "Utility/SwTimer.h"
#include "UIApp/Network/UIAppWiFiCmdMovie.h"
#include "UIWnd/UIFlow.h"
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
static volatile UINT32 g_uiMovieAutoLcdPowerSaveCnt = 0;
static volatile BOOL   g_bMovieAutoLcdPowerSaveStatus = FALSE;
static BOOL SOS_Status_now = FALSE;
//static BOOL g_bVx1_LEDOn = FALSE;
static BOOL g_GS_ParkingMode = FALSE;
static BOOL g_ACCPowerOff = FALSE;

extern void GPIOMap_TurnOnLCDBacklight(void);
extern void GPIOMap_TurnOffLCDBacklight(void);
extern BOOL GPIOMap_IsLCDBacklightOn(void);
extern UINT32 System_GetEnableSensor(void);
extern void UIFlowWndMovie_OnDeleteOld(void);

//extern BOOL g_NotRecordWrn;
extern BOOL SlowCard_Flag;
extern BOOL MotionLed_EN;
extern BOOL g_bMovieHDR_changed;
extern BOOL   FlowMovie_CheckReOpenItem(void);
extern BOOL Voice_Parrecordstart;
extern BOOL ASR_GetPCMData_EN;

UINT8 FlowMovie_GetMovDataState(void)
{
	return gMovData.State;
}

void FlowMovie_StartRec(void)
{
	if (g_MovRecSelfTimerSec == 0) {
        gMovData.State = MOV_ST_REC;
		g_MovRecCurrTime = 0;

        //MovRec_SetROPercent(30);

#if (USE_FILEDB == DISABLE)
		// update DCF Folder/File name
		FlowDCF_UpdateName();
#endif
        //FlowMovie_CreateFileRecoveryTxt();

		if (System_GetState(SYS_STATE_POWERON) == SYSTEM_POWERON_SAFE) {
			// wait playing sound stop
			GxSound_WaitStop();
		}

		//#NT#2012/10/23#Philex Lin - begin
		// disable auto power off/USB detect timer
		KeyScan_EnableMisc(FALSE);
		//#NT#2012/10/23#Philex Lin - end

        // add for time lapse rec
        #if 0//USE_FILEDB
        //if (SysGetFlag(FL_MOVIE_TIMELAPSE_REC) != MOVIE_TIMELAPSEREC_OFF)
        {
            if (SysGetFlag(FL_MOVIE_CYCLIC_REC) != MOVIE_CYCLICREC_OFF) {
                debug_msg("===FL_MOVIE_TIMELAPSE_REC   UIFlowWndMovie_OnDeleteOld===\r\n");
                // delete old files if disk is almost full
                UIFlowWndMovie_OnDeleteOld();

                Delay_DelayMs(300);
            }
        }
        #endif
		if ((!SlowCard_Flag) && (!Voice_Parrecordstart)){	
			UIVoice_Play(DEMOSOUND_SOUND_RECORDINGSTART_TONE);
			Voice_Parrecordstart = FALSE;
		}
		ASR_GetPCMData_EN = FALSE;
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_REC_START, 0);
		ASR_GetPCMData_EN = TRUE;

        #if 0
        if (SysGetFlag(FL_LED) == LED_ON) {
            GxLED_SetCtrl(KEYSCAN_LED_GREEN, SET_TOGGLE_LED, FALSE);
            GxLED_SetCtrl(KEYSCAN_LED_GREEN, TURNON_LED, TRUE);
        }
        #else
		MotionLed_EN = FALSE;
		FlowMovie_SetLedFlash_BeepWrn(FALSE);
        #endif
		if(GPIOMap_EthCam1Det()&&(!FlowMovie_IsEthCamConnectOK()))
		{
			g_NotRecordWrn = TRUE;
		}
		else
		{
			g_NotRecordWrn = FALSE;
		}
	} else {
		DBG_ERR("not yet, g_MovSelfTimerSec=%d\r\n", g_MovRecSelfTimerSec);
	}
}

void FlowMovie_StopRec(void)
{
	DBG_DUMP("call FlowMovie_StopRec\r\n");
#if (_ADAS_FUNC_ == ENABLE)
	// Fixed icon disappear issue when stop record during ADAS warning window
	UxCtrl_SetShow(&UIFlowWndMovie_Panel_Normal_DisplayCtrl, TRUE);
	UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Alert_DisplayCtrl, FALSE);
	DBG_ERR("======FlowMovie_StopRec===========\r\n");
#endif  // #if (_ADAS_FUNC_ == ENABLE)

    //FlowMovie_DeleteFileRecoveryTxt();

	UxCtrl_SetShow(&UIFlowWndMovie_PanelCtrl, FALSE);
	Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_REC_STOP, 0);

    FlowMovie_IconHideSOS();
    FlowMovie_DrawPIM(FALSE);
    FlowMovie_SetSOSStatusNow(FALSE);

    #if 0
    if (SysGetFlag(FL_LED) == LED_ON) {
        GxLED_SetCtrl(KEYSCAN_LED_GREEN, SETLED_SPEED, GXLED_1SEC_LED_TOGGLE_CNT/10);
        GxLED_SetCtrl(KEYSCAN_LED_GREEN, SET_TOGGLE_LED, TRUE);
        GxLED_SetCtrl(KEYSCAN_LED_GREEN, TURNON_LED, TRUE);
    }
    #else
    MotionLed_EN = TRUE;
    FlowMovie_SetLedFlash_BeepWrn(TRUE);
    #endif

	//#NT#2012/10/23#Philex Lin - begin
	// enable auto power off/USB detect timer
	KeyScan_EnableMisc(TRUE);
	//#NT#2016/06/21#Niven Cho -begin
	//#NT#Remove danger code
	//#NT#2016/06/21#Niven Cho -end
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

BOOL FlowMovie_IsStorageErr(BOOL IsCheckFull)
{
#if _LINUX_MOVIE_TODO_
#if (MOVIE_ENSURE_SD_32KCLUSTER == ENABLE)
	UINT32  uiClusterSize;
#endif
#if (MOVIE_ENSURE_SD_CLASS4 == ENABLE)
	PSDIO_MISC_INFORMATION pMiscInfo;
#endif

	// check card inserted
	if (System_GetState(SYS_STATE_CARD)  == CARD_REMOVED) {
		Delay_DelayMs(100);
		UIVoice_Play(DEMOSOUND_SOUND_PINSERTCARD_TONE);		
		Ux_OpenWindow(&UIFlowWndWrnMsgCtrl, 2, UIFlowWndWrnMsg_StatusTXT_Msg_STRID_PLEASE_INSERT_SD, FLOWWRNMSG_TIMER_2SEC);
		return TRUE;
	}

	// check storage error
	if (UIStorageCheck(STORAGE_CHECK_ERROR, NULL) == TRUE) {
        #if 0
		Ux_OpenWindow(&UIFlowWndWrnMsgCtrl, 2, FLOWWRNMSG_ISSUE_MEM_ERR, FLOWWRNMSG_TIMER_2SEC);
        #else
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl, 2, FLOWWRNMSG_ISSUE_CARD_ERR, FLOWWRNMSG_TIMER_2SEC);
        #endif
		return TRUE;
	}


	// check storage lock or directory read only
	if (UIStorageCheck(STORAGE_CHECK_LOCKED, NULL) == TRUE ||
		UIStorageCheck(STORAGE_CHECK_DCIM_READONLY, NULL) == TRUE) {
		Ux_OpenWindow(&UIFlowWndWrnMsgCtrl, 2, UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CARD_LOCKED, FLOWWRNMSG_TIMER_2SEC);
		return TRUE;
	}

	// check storage full
	if (TRUE == IsCheckFull) {
		g_MovRecMaxTime = Movie_GetFreeSec();
		if (g_MovRecMaxTime <= MOVIE_REC_TIME_MIN) {
			g_MovRecMaxTime = 0;
			DBG_DUMP("call check storage full\r\n");
			Ux_OpenWindow(&UIFlowWndWrnMsgCtrl, 2, UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CARD_FULL, FLOWWRNMSG_TIMER_2SEC);
			return TRUE;
		}
	}

	// check folder full
	if (UIStorageCheck(STORAGE_CHECK_FOLDER_FULL, NULL) == TRUE) {
		DBG_DUMP("call check folder full\r\n");
		Ux_OpenWindow(&UIFlowWndWrnMsgCtrl, 2, UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CARD_FULL, FLOWWRNMSG_TIMER_2SEC);
		return TRUE;
	}

	// check serial number full
	if (MovieExe_CheckSNFull()) {
		DBG_DUMP("call check serial number full\r\n");
		Ux_OpenWindow(&UIFlowWndWrnMsgCtrl, 2, UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CARD_FULL, FLOWWRNMSG_TIMER_2SEC);
		return TRUE;
	}

#if (MOVIE_ENSURE_SD_CLASS4 == ENABLE)
	// check sd card whether faster than class 4
	pMiscInfo = sdio_getMiscInfo();
	if (pMiscInfo->uiWriteRate < MOVIE_REC_SD_CLASS) {
		Ux_OpenWindow(&UIFlowWndWrnMsgCtrl, 2, UIFlowWndWrnMsg_StatusTXT_Msg_STRID_SD_CLASS4, FLOWWRNMSG_TIMER_2SEC);
		return TRUE;
	}
#endif

#if (MOVIE_ENSURE_SD_32KCLUSTER == ENABLE)
	// Check cluster size, need to be larger than 32KB
	uiClusterSize = FileSys_GetDiskInfo(FST_INFO_CLUSTER_SIZE);
	if (uiClusterSize < MOVIE_REC_MIN_CLUSTER_SIZE) {
		Ux_OpenWindow(&UIFlowWndWrnMsgCtrl, 2, UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CLUSTER_WRONG, FLOWWRNMSG_TIMER_2SEC);
		return TRUE;
	}
#endif
#endif
	return FALSE;
}

UINT32 FlowMovie_GetSelfTimerID(void)
{
	return g_MovRecSelfTimerID;
}

#if 0
BOOL FlowMovie_ChkDrawStoreFullFolderFull(void)
{

	if (UIStorageCheck(STORAGE_CHECK_FULL, &(g_MovRecMaxTime)) == TRUE) {
		g_MovRecMaxTime = UIMovRecObj_GetData(RECMOVIE_MAXSECOND);
		if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
			Ux_OpenWindow(&UIFlowWndWrnMsgCtrl, 2, FLOWWRNMSG_ISSUE_MEM_FULL, FLOWWRNMSG_TIMER_2SEC);
			return TRUE;
		} else {
			Ux_OpenWindow(&UIFlowWndWrnMsgCtrl, 2, FLOWWRNMSG_ISSUE_CARD_FULL, FLOWWRNMSG_TIMER_2SEC);
			return TRUE;
		}
	}

	return FALSE;
}
#endif

void FlowMovie_GetPictureInMovie(void)
{
#if (0)//(_MOVIE_PIM_MODE_ == ENABLE)
	UINT32  sec, unsafe;

	switch (gMovData.State) {
	case MOV_ST_REC:
		sec = MovRec_Disk2Second();
		unsafe = MovRec_CheckUnsavedFileBlocks();

		if ((sec > 3) && (unsafe == 0)) {
			RawEnc_SetCaptureOne();
			//UxCtrl_SetShow(&UIFlowWndMovie_Static_pimCtrl, TRUE);
		} else {
			if (unsafe) {
				debug_err(("unsafe to take picture !\r\n"));
			} else {
				debug_err(("no space to encode RAW !\r\n"));
			}
		}
		break;
	}
#endif
}

void FlowMovie_OnTimer1SecIndex(void)
{

	switch (gMovData.State) {
	case MOV_ST_VIEW:
	case MOV_ST_VIEW | MOV_ST_ZOOM:
	case MOV_ST_REC:
	case MOV_ST_REC | MOV_ST_ZOOM:
    case MOV_ST_REC_WAIT:
		//gMovData.SysTimeCount++;
		if (UxCtrl_IsShow(&UIFlowWndMovie_YMD_StaticCtrl)) {
			FlowMovie_IconDrawDateTime();
		}
		break;
	}
}

void FlowMovie_SetSOSStatusNow(BOOL En)
{
    SOS_Status_now = En;
}
BOOL FlowMovie_GetSOSStatusNow(void)
{
    return SOS_Status_now;
}

UINT32 Get_LCDBacklightValue(void)
{
    UINT32 BacklightValue = 0;

    switch (SysGetFlag(FL_LCD_OFF)) {
    case LCDOFF_ON:
        BacklightValue = 0;
        break;
    case LCDOFF_1SEC:
        BacklightValue = 2;
        break;
    case LCDOFF_3SEC:
        BacklightValue = 6;
        break;
    case LCDOFF_15SEC:
        BacklightValue = 30;
        break;
    case LCDOFF_30SEC:
        BacklightValue = 60;
        break;
    case LCDOFF_1MIN:
        BacklightValue = 120;
        break;
    case LCDOFF_3MIN:
        BacklightValue = 360;
        break;
    case LCDOFF_5MIN:
        BacklightValue = 600;
        break;
    case LCDOFF_10MIN:
        BacklightValue = 1200;
        break;
    }
    return BacklightValue;
}

void FlowMovie_LCDDimDsiable(UINT8 uCount)
{
    g_uiMovieAutoLcdPowerSaveCnt = uCount;
}

void FlowMovie_DetLCDDim(void)
{
    static UINT32 idlePeriod = 0;

    /*
    if (GxUSB_GetConnectType() == USB_CONNECT_PC) {
        return;
    }*/

    if ((KeyScan_GetPlugDev() == PLUG_TV) || (KeyScan_GetPlugDev() == PLUG_HDMI)) {
        return;
    }

    /*
    if (DrvKey_DetNormalKey() != 0) {
        g_uiMovieAutoLcdPowerSaveCnt = 0;
        g_bMovieAutoLcdPowerSaveStatus = FALSE;
    }*/

    if (FlowMovie_GetSOSStatusNow() && (SysGetFlag(FL_MOVIE_TIMELAPSE_REC) == MOVIE_TIMELAPSEREC_OFF) && (!isACCTrigParkMode)) {
        g_uiMovieAutoLcdPowerSaveCnt = 0;
        g_bMovieAutoLcdPowerSaveStatus = FALSE;
    }

    idlePeriod = Get_LCDBacklightValue();
    if (idlePeriod == 0) {
        return;
    }

    //debug_err(("g_uiMovieAutoLcdPowerSaveCnt = %d\r\n", g_uiMovieAutoLcdPowerSaveCnt));
    if (g_uiMovieAutoLcdPowerSaveCnt >= idlePeriod) {
        GPIOMap_TurnOffLCDBacklight();
        g_uiMovieAutoLcdPowerSaveCnt = 0;
        g_bMovieAutoLcdPowerSaveStatus = TRUE;
    } else {
        g_uiMovieAutoLcdPowerSaveCnt++;
        //g_bMovieAutoLcdPowerSaveStatus = FALSE;
    }
}

void FlowMovie_SetLCDDimStatus(BOOL En)
{
    g_bMovieAutoLcdPowerSaveStatus = En;
}
static UINT32 g_uIconHideCnt = 0;

void FlowMovie_LCDIconDimDsiable(UINT8 uCount)
{
    g_uIconHideCnt = uCount;
}

BOOL FlowMovie_GetLCDDimStatus(void)
{
    return g_bMovieAutoLcdPowerSaveStatus;
}

void FlowMovie_DetLCDIconHide(void)
{
	if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI)
	{
		if(UxCtrl_IsShow(&UIFlowWndWiFiMovie_Panel_Normal_DisplayCtrl))
		{
			//g_uIconHideCnt++;
			//DBG_DUMP("111count = %d\r\n",g_uIconHideCnt);
			if(g_uIconHideCnt >= 180)
			{
				UxCtrl_SetShow(&UIFlowWndWiFiMovie_Panel_Normal_DisplayCtrl, FALSE);
				g_uIconHideCnt = 0;
			}
		}
	}
	else
	{
		if(UxCtrl_IsShow(&UIFlowWndMovie_Panel_Normal_DisplayCtrl))
		{
			//g_uIconHideCnt++;
			//DBG_DUMP("222count = %d\r\n",g_uIconHideCnt);
			if(g_uIconHideCnt >= 180)
			{
				UxCtrl_SetShow(&UIFlowWndMovie_Panel_Normal_DisplayCtrl, FALSE);
				g_uIconHideCnt = 0;
			}
		}
	}
}


BOOL FlowMovie_WakeUpLCDBacklight(void)
{
    FlowMovie_LCDDimDsiable(0); //reset count
	FlowMovie_LCDIconDimDsiable(0); //reset count
	#if 1//(GPS_PANEL_FUNC==ENABLE)
	//Show Icon
	if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) {
		if (UI_GetData(FL_ADAS_PANEL) == ADAS_PANEL_OFF) {
			if(!UxCtrl_IsShow(&UIFlowWndWiFiMovie_Panel_Normal_DisplayCtrl)) {
				UxCtrl_SetShow(&UIFlowWndWiFiMovie_Panel_Normal_DisplayCtrl, TRUE);
			}
		} else {
			#if 0//_TODO	
			if(!UxCtrl_IsShow(&UIFlowWndWiFiMovie_GPS_INFOCtrl)) {
				UxCtrl_SetShow(&UIFlowWndWiFiMovie_GPS_INFOCtrl, TRUE);
			}
			#endif
		}
	} else {
		if (UI_GetData(FL_ADAS_PANEL) == ADAS_PANEL_OFF) {
			if(!UxCtrl_IsShow(&UIFlowWndMovie_Panel_Normal_DisplayCtrl)) {
				UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Alert_DisplayCtrl, FALSE);
				UxCtrl_SetShow(&UIFlowWndMovie_Panel_Normal_DisplayCtrl, TRUE);
			}
		} else {
			#if 0//_TODO
			if(!UxCtrl_IsShow(&UIFlowWndMovie_GPS_INFOCtrl)) {
				UxCtrl_SetShow(&UIFlowWndMovie_GPS_INFOCtrl, TRUE);
			}
			#endif
		}
	}
	#else 
	//Show Icon
	if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) {
		if(!UxCtrl_IsShow(&UIFlowWndWiFiMovie_Panel_Normal_DisplayCtrl)) {
			UxCtrl_SetShow(&UIFlowWndWiFiMovie_Panel_Normal_DisplayCtrl, TRUE);
		}
	} else {
		if(!UxCtrl_IsShow(&UIFlowWndMovie_Panel_Normal_DisplayCtrl)) {
			UxCtrl_SetShow(&UIFlowWndMovie_Panel_Normal_DisplayCtrl, TRUE);
		}
	}
	#endif

    if ((FlowMovie_GetLCDDimStatus()||(GPIOMap_IsLCDBacklightOn() == FALSE))
        &&(KeyScan_GetPlugDev() != PLUG_TV)
        &&(KeyScan_GetPlugDev() != PLUG_HDMI))
    {
        GPIOMap_TurnOnLCDBacklight();
        FlowMovie_SetLCDDimStatus(FALSE);
	printf("call FlowMovie_WakeUpLCDBacklight\r\n");
        return TRUE;
    }
    return FALSE;
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

static UINT32 uiBaseDay = DEFAULT_FORMAT_WARNING_DATE;
void FlowMovie_BaseDaySet(int year,int month,int day)
{
    uiBaseDay = year*10000 + month*100 + day;
    UI_SetData(FL_FORMAT_WARNING_DATE,uiBaseDay);
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

static BOOL sbSpecailFormatWarningFlg = FALSE;
void FlowMovie_Specail_Flag_Set(BOOL std)
{
    sbSpecailFormatWarningFlg = std;
}

UINT32 FlowMovie_Specail_Flag_Get(void)
{
    return sbSpecailFormatWarningFlg;
}

//#Jason add for check file date begin//2013/12/20 begin
#if 0
UINT32 UIFlowWndMovie_CheckFileDate(void)
{
    RTC_DATE    Date;
    RTC_TIME    Time;
    UINT32  creDateTime[6],modDateTime[6];
    UINT32 FileNum;
    FILEDB_HANDLE     FileDBHdl = 0;
    PFILEDB_FILE_ATTR FileAttr = NULL;
    static BOOL uiFileDateError =FALSE;

    Date = rtc_getDate();
    Time = rtc_getTime();

    FileAttr = FileDB_CurrFile(FileDBHdl);
    FileNum = FileDB_GetTotalFileNum(FileDBHdl);

    debug_err(("%02d \r\n",FileNum));

    if(FileNum)
    {
        debug_err(("getpath %d %s \r\n",FileNum,FileAttr->filePath));

        FileSys_GetDateTime(FileAttr->filePath,creDateTime,modDateTime);
        /*	
        if (modDateTime[0] > 2050)  modDateTime[0] = 2050;
        if (modDateTime[1] > 12)  modDateTime[0] = 12;
        if (modDateTime[2] > 31)  modDateTime[0] = 31;
        */	
        debug_err(("%02d/%02d/%02d\r\n",modDateTime[0],modDateTime[1],modDateTime[2]));

        if(modDateTime[0]>Date.s.year)
        {
            uiFileDateError=TRUE;
        }
        else if((modDateTime[0]==Date.s.year)&&(modDateTime[1] >Date.s.month))
        {
            uiFileDateError=TRUE;
        }
        else if((modDateTime[0]==Date.s.year)&&(modDateTime[1] ==Date.s.month)&&(modDateTime[2] >Date.s.day))
        {
            uiFileDateError=TRUE;
        }
        else
        {
            uiFileDateError=FALSE;
        }
    }
    else
    {
        uiFileDateError=FALSE;
    }
    return uiFileDateError;
 }
#endif
//#Jason add for check file date begin//2013/12/20 end

BOOL FlowMovie_Specail_FormatWarning(void)
{
#if 0
    int itmpDateTime = 0;
    static int siWarnningCnt = 0;
    BOOL std = FALSE;
    struct  tm Curr_DateTime = {0};

    if (siWarnningCnt == 0)
    {
        Curr_DateTime = HwClock_GetTime(TIME_ID_CURRENT);

        itmpDateTime = Curr_DateTime.tm_year*10000 + Curr_DateTime.tm_mon*100 + Curr_DateTime.tm_mday;

        /*
        if (itmpDateTime == 20170102)
        {
            std = TRUE;
            FlowMovie_Specail_Flag_Set(TRUE);
        }
        if (UIFlowWndMovie_CheckFileDate() == TRUE)
        {
            std = TRUE;
        }*/
    }
    siWarnningCnt++;

    if (siWarnningCnt > 600)
    {
        siWarnningCnt = 2;
    }

    return std;

#else
    return FALSE;
#endif
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

    //uiDayDiff=(Curr_DateTime.tm_year*10000 + Curr_DateTime.tm_mon*100 + Curr_DateTime.tm_mday) - FlowMovie_BaseDayGet();

    uiDayDiff = BaseDay_DiffDays(Curr_DateTime.tm_year, Curr_DateTime.tm_mon, Curr_DateTime.tm_mday, base_year, base_month, base_day);

    //debug_err(("FlowMovie_CheckFormatWrning =%d\r\n",uiDayDiff));
    if(uiDayDiff > FlowMovie_CheckDateValue())
        return TRUE;
    else
        return FALSE;
}

/*
uState:  0 --> Off
uState:  1 --> On
uState:  2 --> Toggle
*/
void FlowMovie_DetVx1LED(UINT8 uState)
{
    #if 0
    //DBG_DUMP("*** EnableSensor= %d ***\r\n",System_GetEnableSensor());
    if (System_GetEnableSensor() == (SENSOR_1|SENSOR_2))
    {
        if (uState == 0)
        {
            g_bVx1_LEDOn = FALSE;
        }
        else if (uState == 1)
        {
            g_bVx1_LEDOn = TRUE;
        }
        else
        {
            if (g_bVx1_LEDOn)
            {
                g_bVx1_LEDOn = FALSE;
            }
            else
            {
                g_bVx1_LEDOn = TRUE;
            }
        }
        vx1_cfgTransmitterGPIO(VX1_TXMODULE_THCV231, VX1_TXGPIO_4, VX1_GPIODIR_OUTPUT, &g_bVx1_LEDOn);
    }
    #endif
}

void FlowMovie_USBRemovePowerOff(void)
{
    #if 1
    if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) {
        if (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD) {
            /*
            if (FlowWiFiMovie_GetRecCurrTime() <= 1) {
                SwTimer_DelayMs(1000);
            }*/
            FlowWiFiMovie_StopRec();
            SwTimer_DelayMs(100);
        }
    }
    else
    #endif
    {
        switch (gMovData.State) {
        case MOV_ST_REC:
        case MOV_ST_REC|MOV_ST_ZOOM:
        //case MOV_ST_REC_WAIT:
            /*
            if (FlowMovie_GetRecCurrTime() <= 1) {
                SwTimer_DelayMs(1000);
            }*/
            FlowMovie_StopRec();
            SwTimer_DelayMs(20);
            break;
        }
    }
}

void FlowMovie_SetLedFlash_BeepWrn(BOOL std)
{
    if (std) {
        if (SysGetFlag(FL_LED) == LED_ON) {
            //GxLED_SetCtrl(KEYSCAN_LED_GREEN, SETLED_SPEED, GXLED_1SEC_LED_TOGGLE_CNT/10);
            //GxLED_SetCtrl(KEYSCAN_LED_GREEN, SET_TOGGLE_LED, TRUE);
            //GxLED_SetCtrl(KEYSCAN_LED_GREEN, TURNON_LED, TRUE);
        }
         if(!g_RearErr){//no rear error
        	g_NotRecordWrn = TRUE;
			
			DBG_ERR("1-------444444\r\n");
		}
    } else {
        if (SysGetFlag(FL_LED) == LED_ON) {
           // GxLED_SetCtrl(KEYSCAN_LED_GREEN, SET_TOGGLE_LED, FALSE);
           // GxLED_SetCtrl(KEYSCAN_LED_GREEN, TURNON_LED, TRUE);
        }
         g_NotRecordWrn = FALSE;
    }
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

    //1 min cyclic value
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
        //num = 15;
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

    //1 min cyclic value
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
        //num = 15;
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

    /*
    if (UI_GetData(FL_VIDEO_FORMAT) == VIDEO_FORMAT_TS) {
        return;
    }*/

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
        //DBG_DUMP("%s------>%d\r\n", __func__, buf_tmp);
        FileSys_ReadFile(fp, (UINT8 *)&buf_tmp, &pBufSize, 0, NULL);
        //DBG_DUMP("%s------>%d\r\n", __func__, buf_tmp);
        FileSys_CloseFile(fp);
        num = atoi(buf_tmp);
        DBG_DUMP("*** Recovery num = %d ***\r\n", num);
    }
    return num;
}

UINT8 g_FileRecoveryFlag = 0;
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
    //DBG_DUMP("*** temp= %d, time_start= %d, time_stop= %d, SysGetFlag(FL_MOVIE_HDR)= %d ***\r\n", temp, time_start, time_stop, SysGetFlag(FL_MOVIE_HDR));

    if ((((temp >= 0) && (temp < time_start)) || ((temp >= time_stop) && (temp <= 2359)))
        && (SysGetFlag(FL_MOVIE_HDR) == MOVIE_HDR_OFF))
    {
        if ((gMovData.State == MOV_ST_REC)||(gMovData.State == (MOV_ST_REC|MOV_ST_ZOOM))) {
            /*
            if ((FlowMovie_GetRecCurrTime() <= 1)&&(SysGetFlag(FL_MOVIE_TIMELAPSE_REC) == MOVIE_TIMELAPSEREC_OFF)) {
                Delay_DelayMs(1000);
            }*/
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
            /*
            if ((FlowMovie_GetRecCurrTime() <= 1)&&(SysGetFlag(FL_MOVIE_TIMELAPSE_REC) == MOVIE_TIMELAPSEREC_OFF)) {
                Delay_DelayMs(1000);
            }*/
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
	static UINT32 StartCount = 0;
	static UINT32 DetCount = 0;
	/*if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) {
		if (UxCtrl_IsShow(&UIFlowWndMovie_ADAS_Alert_PanelCtrl)) {
			if (g_bSpeedPanelInit) {
				StartCount ++;
				if (StartCount <= 17) {
					FlowWiFiMovie_IconDrawPanelSpeed(StartCount);
				} else {
					StartCount = 0;
					g_bSpeedPanelInit = FALSE;
				}
			} else {
				StartCount = 0;
			}

			if (!g_bSpeedPanelInit) {
				DetCount ++;
				if (DetCount >= 2){
					//FlowWiFiMovie_IconDrawTimeDate();
					FlowWiFiMovie_IconDrawSpeed();
					DetCount = 0;
				}
			}
		} else {
			StartCount = 0;
			DetCount = 0;
			g_bSpeedPanelInit = FALSE;
		}
	} else*/ {
		if (UxCtrl_IsShow(&UIFlowWndMovie_ADAS_Alert_PanelCtrl)) {
			if (g_bSpeedPanelInit) {
				StartCount ++;
				if (StartCount <= 17) {
					//FlowMovie_IconDrawPanelSpeed(StartCount);
					FlowMovie_IconDrawADASAnimation();
				} else {
					StartCount = 0;
					g_bSpeedPanelInit = FALSE;
				}
			} else {
				StartCount = 0;
			}

			if (!g_bSpeedPanelInit) {
				DetCount ++;
				if (DetCount >= 2){
					//FlowMovie_IconDrawTimeDate();
					//FlowMovie_IconDrawSpeed();
					FlowMovie_IconDrawADASAnimation();
					DetCount = 0;
				}
			}
		} else {
			StartCount = 0;
			DetCount = 0;
			g_bSpeedPanelInit = FALSE;
		}
	}
}
#endif


