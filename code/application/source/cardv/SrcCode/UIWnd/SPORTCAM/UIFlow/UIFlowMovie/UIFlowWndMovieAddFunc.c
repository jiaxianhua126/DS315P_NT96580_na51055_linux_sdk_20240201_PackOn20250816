#include "PrjInc.h"
#include "UIWnd/SPORTCAM/UIInfo/UICfgDefault.h"
#include "UIApp/Network/UIAppWiFiCmdMovie.h"
#if(defined(_NVT_ETHREARCAM_RX_))
#include "UIApp/Network/EthCamAppSocket.h"
#include "UIApp/Network/EthCamAppCmd.h"
#include "UIApp/Network/EthCamAppNetwork.h"
#endif
#include "DxInput.h"
//#include "DxOutput.h"
#include "FileDB.h"

//---------------------UIFlowWndMovieCtrl Debug Definition -----------------------------
#define __MODULE__          UIFlowWndMovieAddFunc
#define __DBGLVL__          2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>

static UINT8  g_isRearOK = 0;
static volatile BOOL g_PreviewStable_Record = FALSE;

UINT8  Get_IsRearOK(void)
{	
	return g_isRearOK;
}
void Set_IsRearOK(UINT8 value)
{
	g_isRearOK = value;
}
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
void UIFlowWndMovie_OnTXStatusDet(void)
{
#if (defined(_NVT_ETHREARCAM_RX_))
	if(GPIOMap_EthCam1Det()&&GPIOMap_EthCam2Det())
	{
		if(socketCliEthData1_IsRecv(ETHCAM_PATH_ID_1 +0) 
			&& EthCamNet_GetEthLinkStatus(ETHCAM_PATH_ID_1 +0)==ETHCAM_LINK_UP
			&&socketCliEthData1_IsRecv(ETHCAM_PATH_ID_1 +1) 
			&& EthCamNet_GetEthLinkStatus(ETHCAM_PATH_ID_1 +1)==ETHCAM_LINK_UP)
		{
			g_isRearOK++;
		}
		else
		{
			g_isRearOK = 0;
		}

	}
	else if(!GPIOMap_EthCam1Det()&&GPIOMap_EthCam2Det())
	{
		if(socketCliEthData1_IsRecv(ETHCAM_PATH_ID_1 +1) 
			&& EthCamNet_GetEthLinkStatus(ETHCAM_PATH_ID_1 +1)==ETHCAM_LINK_UP)
		{
			g_isRearOK++;
		}
		else
		{
			g_isRearOK = 0;
		}
	}
	else if (GPIOMap_EthCam1Det()&&!GPIOMap_EthCam2Det())
	{
		if(socketCliEthData1_IsRecv(ETHCAM_PATH_ID_1 +0) 
			&& EthCamNet_GetEthLinkStatus(ETHCAM_PATH_ID_1 +0)==ETHCAM_LINK_UP)
		{
			g_isRearOK++;
		}
		else
		{
			g_isRearOK = 0;
		}
	}
	DBG_IND("g_isRearOK = %d GPIOMap_EthCam1Det=%d GPIOMap_EthCam2Det=%d\r\n",g_isRearOK,GPIOMap_EthCam1Det(),GPIOMap_EthCam2Det());
#endif

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
						//do not start rec,it starts to wifi
					}
					else
					{
						Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
						#if 1//(GPS_PANEL_FUNC==ENABLE)
						if (UI_GetData(FL_ADAS_PANEL) == ADAS_PANEL_ON) {
	                        UxCtrl_SetShow(&UIFlowWndMovie_Panel_Normal_DisplayCtrl, FALSE);
	                        UxCtrl_SetShow(&UIFlowWndMovie_ADAS_Alert_PanelCtrl, TRUE);
	                        UI_SetData(FL_DUAL_CAM, DUALCAM_BEHIND);
	                        UI_SetData(FL_DUAL_CAM_MENU, UI_GetData(FL_DUAL_CAM));
	                        g_bSpeedPanelInit = TRUE;
	                    }
						#endif
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
					Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
				}
			}
		}
	}
	DBG_IND("%d g_PreviewStable_Record = %d g_isRearOK=%d autoWifi=%d isFirstPowerOn=%d\r\n",(System_GetState(SYS_STATE_POWERON) == SYSTEM_POWERON_SAFE),g_PreviewStable_Record,g_isRearOK,autoWifi,isFirstPowerOn);
}
void UIFlowMoive_AutoStartWiFi(void)
{
#if (!defined(_NVT_ETHREARCAM_TX_))//(AUTO_WIFI==ENABLE)
	if ((!autoWifi) && (/*(SysGetFlag(FL_WIFI) != WIFI_OFF)||*/(SysGetFlag(FL_WIFI_AUTO) == WIFI_AUTO_ON))) {
        if (isFirstPowerOn/* && GPIOMap_DetTV()*/) {
			AutoWiFiCnt++;
			//debug_msg("AutoWiFiCnt=%d\r\n",AutoWiFiCnt);
            if ((AutoWiFiCnt >= 4)) {
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
                #if(WIFI_UI_FLOW_VER == WIFI_UI_VER_1_0)
                Ux_OpenWindow(&UIMenuWndWiFiWaitCtrl, 0);
                #endif
                //#NT#2016/03/23#Isiah Chang -end
                BKG_PostEvent(NVTEVT_BKW_WIFI_ON);
                autoWifi = TRUE;
                isFirstPowerOn = FALSE;
                AutoWiFiCnt = 0;
            }
        } else {
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
            #if(WIFI_UI_FLOW_VER == WIFI_UI_VER_1_0)
            Ux_OpenWindow(&UIMenuWndWiFiWaitCtrl, 0);
            #endif
            //#NT#2016/03/23#Isiah Chang -end
            BKG_PostEvent(NVTEVT_BKW_WIFI_ON);
            autoWifi = TRUE;
            isFirstPowerOn = FALSE;
        }
	} else {
        autoWifi = TRUE;
        isFirstPowerOn = FALSE;
    }
#endif
}
#if 0
UINT32 Movie_GetCyclicRecTime(void)
{
    UINT32 uiCyclicRecTime = 0;

    switch (UI_GetData(FL_MOVIE_CYCLIC_REC)) {
    case MOVIE_CYCLICREC_1MIN:
        uiCyclicRecTime = 60;
        break;

    case MOVIE_CYCLICREC_2MIN:
        uiCyclicRecTime = 120;
        break;

    case MOVIE_CYCLICREC_3MIN:
        uiCyclicRecTime = 180;
        break;

    case MOVIE_CYCLICREC_5MIN:
        uiCyclicRecTime = 300;
        break;

    case MOVIE_CYCLICREC_10MIN:
        uiCyclicRecTime = 600;
        break;

    case MOVIE_CYCLICREC_OFF:
        uiCyclicRecTime = 900;
        break;

    default:
        uiCyclicRecTime = 300;
        break;
    }

    return uiCyclicRecTime;
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
            if (FlowMovie_GetRecCurrTime() <= 1) {
                Delay_DelayMs(1000);
            }*/
            FlowWiFiMovie_StopRec();
            Delay_DelayMs(100);
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
                Delay_DelayMs(1000);
            }*/
            FlowMovie_StopRec();
            Delay_DelayMs(100);
            break;
        }
    }
}
#if 0

static UINT32 g_uIconHideCnt = 0;
void FlowMovie_LCDIconDimDsiable(UINT8 uCount)
{
    g_uIconHideCnt = uCount;
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
#endif
#endif
void FlowMovie_SetCrash(void)
{
	//if (SysGetFlag(FL_MOVIE_URGENT_PROTECT_AUTO) == MOVIE_URGENT_PROTECT_AUTO_ON)
	//DBG_DUMP("^GFlowMovie_SetCrash type=%d\r\n",GetMovieRecType_2p(UI_GetData(FL_MOVIE_SIZE)));
	if (GetMovieRecType_2p(UI_GetData(FL_MOVIE_SIZE)) == MOVIE_REC_TYPE_FRONT) {
		#if(defined(_NVT_ETHREARCAM_RX_))
		ImageApp_MovieMulti_SetCrash(_CFG_REC_ID_1, TRUE);
		UINT32 i;
		for (i = 0; i < ETH_REARCAM_CAPS_COUNT; i++) {
			if(socketCliEthData1_IsRecv(ETHCAM_PATH_ID_1 +i)){
				ImageApp_MovieMulti_SetCrash(_CFG_ETHCAM_ID_1+i, TRUE);
			}
		}
		#else
		ImageApp_MovieMulti_TrigEMR(_CFG_REC_ID_1);
		#endif
	}
	else
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
}

void FlowMovie_SyncEthCamMneu(UINT8 id,BOOL bReOpen)
{
	#if(defined(_NVT_ETHREARCAM_RX_))
	ETHCAM_MENU_SETTING sEthCamMenuSetting[ETH_REARCAM_CAPS_COUNT]={0};
	EthCam_SendXMLCmd(id, ETHCAM_PORT_DEFAULT ,ETHCAM_CMD_SYNC_MENU_SETTING, bReOpen);
	#if (ETH_REARCAM_CAPS_COUNT>=2)
	sEthCamMenuSetting[id].Size=MOVIE_SIZE_FRONT_1920x1080P30;//MOVIE_SIZE_CLONE_1920x1080P30_1280x720P60;//UI_GetData(FL_MOVIE_SIZE);
	#else
	sEthCamMenuSetting[id].Size= 40;//MOVIE_SIZE_CLONE_1920x1080P30_1280x720P30;//UI_GetData(FL_MOVIE_SIZE);
	#endif
	sEthCamMenuSetting[id].WDR=MOVIE_WDR_OFF;//tx_671_always close,if you open wdr ,hdr will close .
	sEthCamMenuSetting[id].EV=UI_GetData(FL_EV2);
	sEthCamMenuSetting[id].DateImprint=UI_GetData(FL_MOVIE_DATEIMPRINT);
	sEthCamMenuSetting[id].SensorRotate=UI_GetData(FL_MOVIE_SENSOR_ROTATE);
	sEthCamMenuSetting[id].Codec=MOVIE_CODEC_H265;//UI_GetData(FL_MOVIE_CODEC);
	//sEthCamMenuSetting[id].Codec=UI_GetData(FL_MOVIE_CODEC);
	#if (ETH_REARCAM_CAPS_COUNT == 1)
	sEthCamMenuSetting[id].TimeLapse=UI_GetData(FL_MOVIE_TIMELAPSE_REC);
	#else
	sEthCamMenuSetting[id].TimeLapse=MOVIE_TIMELAPSEREC_OFF;
	#endif
	DBG_DUMP("Size=%d\r\n", sEthCamMenuSetting[id].Size);
	sEthCamMenuSetting[id].ParkingMode=UI_GetData(FL_PARKING_MODE);
	sEthCamMenuSetting[id].ParkingTimeLapse=UI_GetData(FL_PARKING_MODE_TIMELAPSE_REC);
	sEthCamMenuSetting[id].ACCTrigParkMode=isACCTrigParkMode;
	sEthCamMenuSetting[id].HDR=MOVIE_HDR_ON;// UI_GetData(FL_MOVIE_HDR);
	EthCam_SendXMLData(id, (UINT8 *)&sEthCamMenuSetting[id], sizeof(ETHCAM_MENU_SETTING));
	//if(memcmp(&g_sEthCamMenuSetting, &sEthCamMenuSetting, sizeof(ETHCAM_MENU_SETTING))){
	//	bReOpenMovie=1;
	//}
	//memcpy(&g_sEthCamMenuSetting[id], &sEthCamMenuSetting[id], sizeof(ETHCAM_MENU_SETTING));	
	#endif
}
#define SENSOR_NONE         0 
#define SENSOR_FRONT        1
#define SENSOR_BEHIND       2
#define SENSOR_BOTH         3 
void FlowMovie_DetTxDisconnected(void)
{
#if(defined(_NVT_ETHREARCAM_RX_))
	static UINT16 sensorStsCur = SENSOR_BOTH;
	static UINT16 sensorStsPre = SENSOR_BOTH;
	static UINT32 sensorStsCnt = 0;

	if(GPIOMap_EthCam1Det()&&EthCamNet_GetEthLinkStatus(ETHCAM_PATH_ID_1+0)==ETHCAM_LINK_UP){//mode change ,rear is link up
		sensorStsCur = SENSOR_BOTH;
	}else{ 
		sensorStsCur = SENSOR_FRONT;
	}
	//DBG_DUMP("%d%d%d link=%d %d\r\n",sensorStsCur,sensorStsPre,sensorStsCnt,EthCamNet_GetEthLinkStatus(ETHCAM_PATH_ID_1+0),GPIOMap_EthCam1Det());
	if(sensorStsPre!=sensorStsCur){
		sensorStsCnt++;
		//isDisconneced = TRUE;
		if(sensorStsCnt>=10){
			sensorStsCnt = 0;
			sensorStsPre = sensorStsCur;
			if(sensorStsCur==SENSOR_BOTH){
				if(System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI){
					bWiFiModeChanged = TRUE;
				}
				g_NotRecordWrn = FALSE;
				UI_SetData(FL_DUAL_CAM_MENU, DUALCAM_BOTH);
				UI_SetData(FL_DUAL_CAM, DUALCAM_BOTH);
				Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, System_GetState(SYS_STATE_CURRMODE));
			}
		}
	}else{
		sensorStsCnt = 0;
	}
#endif
}

#if 0//just for poloraid ,motor dv
static BOOL  bCapPicture = FALSE;
static UINT8 uiCapPictureCount = 0;
extern INT8 uigpsstatus;
void FlowMovie_SetCapPicture(BOOL flag)
{
	bCapPicture = flag;
}
BOOL FlowMovie_GetCapPicture(void)
{
	return bCapPicture;
}
void FlowMovie_SetCapPictureCount(UINT8 cnt)
{
	uiCapPictureCount = cnt;
}
UINT8 FlowMovie_GetCapPictureCount(void)
{
	return uiCapPictureCount;
}

void FlowMovie_LEDToggle(UINT8 uState)
{
	//if (UI_GetData(FL_LED_SWITCH) == LED_SWITCH_ON) 
	if (uState == 0)
	{
		if (LED_IsLEDOn(GPIOMAP_LED_GREEN))
		{
			LED_TurnOffLED(GPIOMAP_LED_GREEN);
		} else {
			LED_TurnOnLED(GPIOMAP_LED_GREEN);
		}
	} else {
		if (LED_IsLEDOn(GPIOMAP_LED_RED))
		{
			LED_TurnOffLED(GPIOMAP_LED_RED);
		} else {
			LED_TurnOnLED(GPIOMAP_LED_RED);
		}
	}
}
void FlowMovie_UpdateLED(void)
{
	static UINT32 LED_Cnt = 0;
	if ((SysGetFlag(FL_LED) == LED_ON)&&((gMovData.State == MOV_ST_REC)||(WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD)))
	{
		if (bCapPicture)
		{
			//debug_msg("bCapPicture = %d, uiCapPictureCount = %d\r\n", bCapPicture, uiCapPictureCount);
			uiCapPictureCount++;
			if (uiCapPictureCount < 30) //6
			{
				FlowMovie_LEDToggle(0);
				//FlowMovie_SendLedCommand(LED_CTRL_100MS_ON_OFF);
			}
			else
			{
				//debug_msg("bCapPicture == FALSE\r\n");
				bCapPicture = FALSE;
				uiCapPictureCount = 0;
				LED_TurnOffLED(GPIOMAP_LED_GREEN);
			}
		}
		else if (FlowMovie_GetSOSStatusNow() == TRUE)
		{
			LED_Cnt = 0;
			FlowMovie_LEDToggle(1);
			//FlowMovie_SendLedCommand(LED_CTRL_100MS_ON_OFF);
		}
		else if ((UI_GetData(FL_GPS) == GPS_ON)&&(uigpsstatus > 0))
		{
			LED_Cnt ++;
			if (LED_Cnt >= 10) {
				FlowMovie_LEDToggle(1);
				LED_Cnt = 0;
				//FlowMovie_SendLedCommand(LED_CTRL_ONE_SECOND_ON_OFF);
			}
		}
		else
		{
			LED_Cnt ++;
			if (LED_Cnt >= 30) {
				FlowMovie_LEDToggle(1);
				LED_Cnt = 0;
				//FlowMovie_SendLedCommand(LED_CTRL_THREE_SECONDS_ON_OFF);
			}
		}
	} else {
		LED_Cnt = 0;
	}
}
#endif
BOOL FlowMovie_IsEthCamConnectOK(void)
{
#if(defined(_NVT_ETHREARCAM_RX_))
	UINT32 i;
	BOOL ret = FALSE;
	for (i = 0; ((i < ETH_REARCAM_CAPS_COUNT)); i++) {
		if(socketCliEthData1_IsRecv(ETHCAM_PATH_ID_1 +i) && EthCamNet_GetEthLinkStatus(ETHCAM_PATH_ID_1 +i)==ETHCAM_LINK_UP){
			ret = TRUE;
		}
	}
	return ret;
#else
	return FALSE;
#endif
}
void FlowMovie_SyncTimeToRear(void)
{
	static UINT32 g_SyncEthCamTimeCnt = 0;
	if(g_SyncEthCamTimeCnt++ >= 10800)//3*3600
	{
		if(!BKG_GetTskBusy()){
			g_SyncEthCamTimeCnt = 0;
			BKG_PostEvent(NVTEVT_BKW_ETHCAM_SYNC_TIME_ONLY);
		}
	}

}
#if defined(_GPS_EDOG_)
void FlowMovie_DistanceVoice(void)
{

    if(EdogInfo_Alarm.Alarm_Distance > 900) {
        UISound_Play(DEMOSOUND_SOUND_900_TONE);
        //Delay_DelayMs(910);
    } else if(EdogInfo_Alarm.Alarm_Distance > 800) {
        UISound_Play(DEMOSOUND_SOUND_800_TONE);
        //Delay_DelayMs(780);
    } else if(EdogInfo_Alarm.Alarm_Distance > 700) {
        UISound_Play(DEMOSOUND_SOUND_700_TONE);
        //Delay_DelayMs(880);
    } else if(EdogInfo_Alarm.Alarm_Distance > 600) {
        UISound_Play(DEMOSOUND_SOUND_600_TONE);
        //Delay_DelayMs(840);
    } else if(EdogInfo_Alarm.Alarm_Distance > 500) {
        UISound_Play(DEMOSOUND_SOUND_500_TONE);
        //Delay_DelayMs(770);
    } else if(EdogInfo_Alarm.Alarm_Distance > 400) {
        UISound_Play(DEMOSOUND_SOUND_400_TONE);
        //Delay_DelayMs(840);
    } else if(EdogInfo_Alarm.Alarm_Distance > 300) {
        UISound_Play(DEMOSOUND_SOUND_300_TONE);
        //Delay_DelayMs(840);
    } else if(EdogInfo_Alarm.Alarm_Distance > 200) {
        UISound_Play(DEMOSOUND_SOUND_200_TONE);
        //Delay_DelayMs(660);
    } else if(EdogInfo_Alarm.Alarm_Distance > 120) {
        UISound_Play(DEMOSOUND_SOUND_120_TONE);
        //Delay_DelayMs(1160);
    } else if(EdogInfo_Alarm.Alarm_Distance > 110) {
        UISound_Play(DEMOSOUND_SOUND_110_TONE);
        //Delay_DelayMs(1160);
    } else if(EdogInfo_Alarm.Alarm_Distance > 100) {
        UISound_Play(DEMOSOUND_SOUND_100_TONE);
        //Delay_DelayMs(730);
    } else if(EdogInfo_Alarm.Alarm_Distance > 90) {
        UISound_Play(DEMOSOUND_SOUND_90_TONE);
        //Delay_DelayMs(910);
    } else if(EdogInfo_Alarm.Alarm_Distance > 80) {
        UISound_Play(DEMOSOUND_SOUND_80_TONE);
        //Delay_DelayMs(880);
    } else if(EdogInfo_Alarm.Alarm_Distance > 70) {
        UISound_Play(DEMOSOUND_SOUND_70_TONE);
        //Delay_DelayMs(910);
    } else if(EdogInfo_Alarm.Alarm_Distance > 60) {
        UISound_Play(DEMOSOUND_SOUND_60_TONE);
        //Delay_DelayMs(880);
    } else if(EdogInfo_Alarm.Alarm_Distance > 50) {
        UISound_Play(DEMOSOUND_SOUND_50_TONE);
        //Delay_DelayMs(840);
    } else if(EdogInfo_Alarm.Alarm_Distance > 40) {
        UISound_Play(DEMOSOUND_SOUND_40_TONE);
        //Delay_DelayMs(950);
    } else if(EdogInfo_Alarm.Alarm_Distance > 30) {
        UISound_Play(DEMOSOUND_SOUND_30_TONE);
        //Delay_DelayMs(910);
    } else if(EdogInfo_Alarm.Alarm_Distance > 20) {
        UISound_Play(DEMOSOUND_SOUND_20_TONE);
    } else if(EdogInfo_Alarm.Alarm_Distance > 10) {
        UISound_Play(DEMOSOUND_SOUND_10_TONE);
    }

    UISound_Play(DEMOSOUND_SOUND_M_TONE);
    //Delay_DelayMs(500);
}

void FlowMovie_AlarmTypeVoice(void)
{
    switch (EdogInfo_Alarm.Alarm_Type) {
    case 0x00:
        UISound_Play(DEMOSOUND_SOUND_TD0_TONE);
        //Delay_DelayMs(1960);
        break;
    case 0x01:
        UISound_Play(DEMOSOUND_SOUND_TD1_TONE);
        //Delay_DelayMs(1640);
        break;
    case 0x02:
        UISound_Play(DEMOSOUND_SOUND_TD2_TONE);
        //Delay_DelayMs(1710);
        break;
    case 0x04:
        UISound_Play(DEMOSOUND_SOUND_TD4_TONE);
        //Delay_DelayMs(1940);
        break;
    case 0x05:
        UISound_Play(DEMOSOUND_SOUND_TD5_TONE);
        //Delay_DelayMs(1510);
        break;
    case 0x06:
        UISound_Play(DEMOSOUND_SOUND_TD6_TONE);
        //Delay_DelayMs(3210);
        break;
    case 0x08:
        UISound_Play(DEMOSOUND_SOUND_TD8_TONE);
        //Delay_DelayMs(1950);
        break;
    case 0x0A:
        UISound_Play(DEMOSOUND_SOUND_TDA_TONE);
        //Delay_DelayMs(1950);
        break;
    case 0x0B:
        UISound_Play(DEMOSOUND_SOUND_TDB_TONE);
        //Delay_DelayMs(2100);
        break;
	case 0x0C:
        UISound_Play(DEMOSOUND_SOUND_TDB_TONE);
        //Delay_DelayMs(2100);
        break;
    case 0xE8:
        UISound_Play(DEMOSOUND_SOUND_TDE8_TONE);
        //Delay_DelayMs(1910);
        break;
    default:
        break;
    }
}


void FlowMovie_SpeedLmtVoice(void)
{

    switch (EdogInfo_Alarm.Alarm_LimitSpeed) {
    case 20:
        UISound_Play(DEMOSOUND_SPEED_LIMIT20_TONE);
        //Delay_DelayMs(2130);
        break;
    case 30:
        UISound_Play(DEMOSOUND_SPEED_LIMIT30_TONE);
        //Delay_DelayMs(2200);
        break;
    case 40:
        UISound_Play(DEMOSOUND_SPEED_LIMIT40_TONE);
        //Delay_DelayMs(2250);
        break;
    case 50:
        UISound_Play(DEMOSOUND_SPEED_LIMIT50_TONE);
        //Delay_DelayMs(2100);
        break;
    case 60:
        UISound_Play(DEMOSOUND_SPEED_LIMIT60_TONE);
        //Delay_DelayMs(2100);
        break;
    case 70:
        UISound_Play(DEMOSOUND_SPEED_LIMIT70_TONE);
        //Delay_DelayMs(2150);
        break;
    case 80:
        UISound_Play(DEMOSOUND_SPEED_LIMIT80_TONE);
        //Delay_DelayMs(2070);
        break;
    case 90:
        UISound_Play(DEMOSOUND_SPEED_LIMIT90_TONE);
        //Delay_DelayMs(2180);
        break;
    case 100:
        UISound_Play(DEMOSOUND_SPEED_LIMIT100_TONE);
        //Delay_DelayMs(1970);
        break;
    case 110:
        UISound_Play(DEMOSOUND_SPEED_LIMIT110_TONE);
        //Delay_DelayMs(2410);
        break;
    case 120:
        UISound_Play(DEMOSOUND_SPEED_LIMIT120_TONE);
        //Delay_DelayMs(2440);
        break;
    default:
        break;
    }
}

void FlowMovie_EdogAlarmVoice(void)
{

    switch (EdogInfo_Alarm.Alarm_Type) {
    case 0x00:
    case 0x01:
    case 0x02:
    case 0x04:
    case 0x05:
    case 0x08:
    case 0x0A:
    case 0x0B:
	case 0x0C:
        UISound_Play(DEMOSOUND_SOUND_TA0_TONE);
        //Delay_DelayMs(760);
        FlowMovie_DistanceVoice();
        FlowMovie_AlarmTypeVoice();
        FlowMovie_SpeedLmtVoice();
        break;
    case 0x06:
        UISound_Play(DEMOSOUND_SOUND_TA0_TONE);
        //Delay_DelayMs(760);
        FlowMovie_AlarmTypeVoice();
        break;

    case 0xE8:
        UISound_Play(DEMOSOUND_SOUND_TA0_TONE);
        //Delay_DelayMs(760);
        FlowMovie_AlarmTypeVoice();
        UISound_Play(DEMOSOUND_BEWARE_TONE);
        //Delay_DelayMs(1660);
        break;

    default:
        break;
    }

}
#elif defined(_GPS_EDOG_UNIQUE_SKY_)
void FlowMovie_DistanceVoice(void)
{
#if 1
	if(((EdogInfo_SentenceA.EDOG_Distance2<<8)|EdogInfo_SentenceA.EDOG_Distance1) > 700) {
        UISound_Play(DEMOSOUND_SOUND_EP82_TONE_800);
		//UISound_Play(DEMOSOUND_SOUND_EP12_TONE_M);	  
    } else if(((EdogInfo_SentenceA.EDOG_Distance2<<8)|EdogInfo_SentenceA.EDOG_Distance1) > 600) {
        UISound_Play(DEMOSOUND_SOUND_EP81_TONE_700);
		//UISound_Play(DEMOSOUND_SOUND_EP12_TONE_M);	  
    } else if(((EdogInfo_SentenceA.EDOG_Distance2<<8)|EdogInfo_SentenceA.EDOG_Distance1) > 500) {
        UISound_Play(DEMOSOUND_SOUND_EP80_TONE_600);
		//UISound_Play(DEMOSOUND_SOUND_EP12_TONE_M);	  
    } else if(((EdogInfo_SentenceA.EDOG_Distance2<<8)|EdogInfo_SentenceA.EDOG_Distance1)> 400) {
        UISound_Play(DEMOSOUND_SOUND_EP79_TONE_500);
		//UISound_Play(DEMOSOUND_SOUND_EP12_TONE_M);	  
    } else if(((EdogInfo_SentenceA.EDOG_Distance2<<8)|EdogInfo_SentenceA.EDOG_Distance1)> 300) {
        UISound_Play(DEMOSOUND_SOUND_EP78_TONE_400);
		//UISound_Play(DEMOSOUND_SOUND_EP12_TONE_M);	  
    } else if(((EdogInfo_SentenceA.EDOG_Distance2<<8)|EdogInfo_SentenceA.EDOG_Distance1)> 200) {
        UISound_Play(DEMOSOUND_SOUND_EP77_TONE_300);
		//UISound_Play(DEMOSOUND_SOUND_EP12_TONE_M);	  
    } else if(((EdogInfo_SentenceA.EDOG_Distance2<<8)|EdogInfo_SentenceA.EDOG_Distance1)> 100) {
        UISound_Play(DEMOSOUND_SOUND_EP76_TONE_200);
		//UISound_Play(DEMOSOUND_SOUND_EP12_TONE_M);	  
    } else if(((EdogInfo_SentenceA.EDOG_Distance2<<8)|EdogInfo_SentenceA.EDOG_Distance1)> 0) {
        UISound_Play(DEMOSOUND_SOUND_EP75_TONE_100);
		//UISound_Play(DEMOSOUND_SOUND_EP12_TONE_M);	  
    }
#endif
}

void FlowMovie_AlarmTypeVoice(UINT8 type)
{
	DBG_DUMP("^G========EdogInfo_SentenceA.EDOG_AlarmType=====0x%x\r\n",type);

	if((type>=0x00)&&(type<=0x0F))
	{
		 UISound_Play(DEMOSOUND_SOUND_EP1_TONE_CAMERA_OVERSPEED); 
	}
	else if((type>=0x10)&&(type<=0x1F))
	{
		 UISound_Play(DEMOSOUND_SOUND_EP2_TONE_CAMERA_FXIED); 
	}
	else if((type>=0x20)&&(type<=0x2F))
	{
		 UISound_Play(DEMOSOUND_SOUND_EP3_TONE_RADAR_SPEED_DETECT); 
	}
	else if((type>=0x30)&&(type<=0x3F))
	{
		 UISound_Play(DEMOSOUND_SOUND_EP8_TONE_CAMERA_BRIDGE_FIXED); 
	}
	else if((type>=0x40)&&(type<=0x4F))
	{
		 UISound_Play(DEMOSOUND_SOUND_EP25_TONE_SPEED_TEST_START); 
	}
	else if((type>=0x60)&&(type<=0x6F))
	{
		 UISound_Play(DEMOSOUND_SOUND_EP4_TONE_CAMERA_BRIDGE_UP); 
	}
	else if((type>=0x70)&&(type<=0x7F))
	{
		 UISound_Play(DEMOSOUND_SOUND_EP14_TONE_CAMERA_BRIDGE_DOWN); 
	}
	else if((type>=0x80)&&(type<=0x8F))
	{
		 UISound_Play(DEMOSOUND_SOUND_EP10_TONE_CAMERA_HIGHWAY_RADAR); 
	}
	else if((type>=0x90)&&(type<=0x9F))
	{
		 UISound_Play(DEMOSOUND_SOUND_EP9_TONE_CAMERA_HIGHWAY_FIXED); 
	}
	else if((type>=0xA0)&&(type<=0xAF))
	{
		 UISound_Play(DEMOSOUND_SOUND_KEJIZHIFA); //DEMOSOUND_SOUND_EP13_TONE_DIANZIJIANKONG
	}
	else if((type>=0xB0)&&(type<=0xBF))
	{
		 UISound_Play(DEMOSOUND_SOUND_EP14_TONE_CAMERA_BRIDGE_DOWN); 
	}


}


void FlowMovie_SpeedLmtVoice(void)
{

	switch (EdogInfo_SentenceA.EDOG_SpeedLimit) {
	case 0x00:
		//UISound_Play(DEMOSOUND_SOUND_EP87_TONE_20KM);
		break;
	case 0x01:
		//UISound_Play(DEMOSOUND_SOUND_EP87_TONE_20KM);
		break;
	case 0x02:
		UISound_Play(DEMOSOUND_SOUND_XIANSU);
		UISound_Play(DEMOSOUND_SOUND_EP87_TONE_20KM);
		break;
	case 0x03:
		UISound_Play(DEMOSOUND_SOUND_XIANSU);
		UISound_Play(DEMOSOUND_SOUND_EP88_TONE_30KM);
		break;
	case 0x04:
		UISound_Play(DEMOSOUND_SOUND_XIANSU);
		UISound_Play(DEMOSOUND_SOUND_EP89_TONE_40KM);
		break;
	case 0x05:
		UISound_Play(DEMOSOUND_SOUND_XIANSU);
		UISound_Play(DEMOSOUND_SOUND_EP90_TONE_50KM);
		break;
	case 0x06:
		UISound_Play(DEMOSOUND_SOUND_XIANSU);
		UISound_Play(DEMOSOUND_SOUND_EP91_TONE_60KM);
		break;
	case 0x07:
		UISound_Play(DEMOSOUND_SOUND_XIANSU);
		UISound_Play(DEMOSOUND_SOUND_EP92_TONE_70KM);
		break;
	case 0x08:
		UISound_Play(DEMOSOUND_SOUND_XIANSU);
		UISound_Play(DEMOSOUND_SOUND_EP93_TONE_80KM);
		break;
	case 0x09:
		UISound_Play(DEMOSOUND_SOUND_XIANSU);
		UISound_Play(DEMOSOUND_SOUND_EP94_TONE_90KM);
		break;
	case 0x0a:
		UISound_Play(DEMOSOUND_SOUND_XIANSU);
		UISound_Play(DEMOSOUND_SOUND_EP95_TONE_100KM);
		break;
	case 0x0b:
		UISound_Play(DEMOSOUND_SOUND_XIANSU);
		UISound_Play(DEMOSOUND_SOUND_EP96_TONE_110KM);
		break;
	case 0x0c:
		UISound_Play(DEMOSOUND_SOUND_XIANSU);
		UISound_Play(DEMOSOUND_SOUND_EP97_TONE_120KM);
		break;
	case 0x0d:
		//UISound_Play(DEMOSOUND_SOUND_EP97_TONE_120KM);
		break;
	case 0x0e:
		//UISound_Play(DEMOSOUND_SOUND_EP97_TONE_120KM);
		break;
	case 0x0f:
		//UISound_Play(DEMOSOUND_SOUND_EP97_TONE_120KM);
		break;
	case 0x10:
		//UISound_Play(DEMOSOUND_SOUND_EP97_TONE_120KM);
		break;
	case 0x11:
		//UISound_Play(DEMOSOUND_SOUND_EP97_TONE_120KM);
		break;
	case 0x12:
		//UISound_Play(DEMOSOUND_SOUND_EP97_TONE_120KM);
		break;
	default:
		break;
	}
}


void FlowMovie_EdogAlarmVoice(UINT8 type)
{
	DBG_DUMP("^G========EdogInfo_SentenceA.EDOG_AlarmType====0x%x\r\n",type);
	if(type!=0xff)
	{
		UISound_Play(DEMOSOUND_SOUND_EP42_TONE_DIDONG);
		if(((type>=0x00)&&(type<=0x4F))||((type>=0x60)&&(type<=0xBF)))
		{
			UISound_Play(DEMOSOUND_SOUND_EP45_TONE_FRONT);	
			FlowMovie_DistanceVoice();
			FlowMovie_AlarmTypeVoice(type);
			FlowMovie_SpeedLmtVoice();
			UISound_Play(DEMOSOUND_SOUND_EP21_TONE);
		}
		else 
		{
			switch(type)
			{
				case 0xC2:
					UISound_Play(DEMOSOUND_SOUND_EP44_TONE_CARE_FRONT1);	
					UISound_Play(DEMOSOUND_SOUND_EP6_TONE_HIGHWAY_ENTER);
					UISound_Play(DEMOSOUND_SOUND_EP24_TONE_SELECT_A_ROAD);
					break;
				case 0xC3:
					UISound_Play(DEMOSOUND_SOUND_EP44_TONE_CARE_FRONT1);	
					UISound_Play(DEMOSOUND_SOUND_EP39_TONE_HIGHWAY_EXIT);
					UISound_Play(DEMOSOUND_SOUND_EP24_TONE_SELECT_A_ROAD);
					break;
				case 0xC4:
					UISound_Play(DEMOSOUND_SOUND_EP44_TONE_CARE_FRONT1);	
					UISound_Play(DEMOSOUND_SOUND_EP35_TONE_END_TESTSPEED_AREA);
					UISound_Play(DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE);
					break;
				#if 0
				case 0xC5:
					UISound_Play(DEMOSOUND_SOUND_EP46_TONE_CARE_FRONT2);	
					UISound_Play(DEMOSOUND_SOUND_EP16_TONE_TIELUKOU);
					UISound_Play(DEMOSOUND_SOUND_EP36_TONE_PLEASE_SLOW_DOWN);
					break;
				#endif
				case 0xC7:
					UISound_Play(DEMOSOUND_SOUND_EP44_TONE_CARE_FRONT1);	
					UISound_Play(DEMOSOUND_SOUND_EP11_TONE_BIG_BEND);
					UISound_Play(DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE);
					break;
				case 0xC8:
					UISound_Play(DEMOSOUND_SOUND_EP46_TONE_CARE_FRONT2);	
					UISound_Play(DEMOSOUND_SOUND_EP31_TONE_FORBID_TURNLEFT);
					UISound_Play(DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE);
					break;
				case 0xD2:
					UISound_Play(DEMOSOUND_SOUND_EP46_TONE_CARE_FRONT2);	
					UISound_Play(DEMOSOUND_SOUND_EP18_TONE_DANGE_ROAD);
					UISound_Play(DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE);
					break;
				case 0xD3:
					UISound_Play(DEMOSOUND_SOUND_EP46_TONE_CARE_FRONT2);	
					UISound_Play(DEMOSOUND_SOUND_EP29_TONE_DOWNHILL);
					UISound_Play(DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE);
					break;
				case 0xD4:
					UISound_Play(DEMOSOUND_SOUND_EP46_TONE_CARE_FRONT2);	
					UISound_Play(DEMOSOUND_SOUND_EP30_TONE_JIAOLIUDAO);
					UISound_Play(DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE);
					break;
				case 0xD6:
					UISound_Play(DEMOSOUND_SOUND_EP46_TONE_CARE_FRONT2);	
					UISound_Play(DEMOSOUND_SOUND_EP33_TONE_ON_LINE_PHOTO);
					UISound_Play(DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE);
					break;
				case 0xD7:
					UISound_Play(DEMOSOUND_SOUND_EP46_TONE_CARE_FRONT2);	
					UISound_Play(DEMOSOUND_SOUND_EP26_TONE_SCHOOL_AREA);
					UISound_Play(DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE);
					break;
				case 0xD9:
					UISound_Play(DEMOSOUND_SOUND_EP46_TONE_CARE_FRONT2);	
					UISound_Play(DEMOSOUND_SOUND_EP27_TONE_CHECK_TRAFFIC_LAW);
					UISound_Play(DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE);
					break;
				case 0xDA:
					UISound_Play(DEMOSOUND_SOUND_EP46_TONE_CARE_FRONT2);	
					UISound_Play(DEMOSOUND_SOUND_EP37_TONE_DRINK_DRIVE);
					UISound_Play(DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE);
					break;
				case 0xDB:
					UISound_Play(DEMOSOUND_SOUND_EP44_TONE_CARE_FRONT1);	
					UISound_Play(DEMOSOUND_SOUND_EP23_TONE_HOLE_ENTER);
					UISound_Play(DEMOSOUND_SOUND_EP20_TONE_TURNON_LIGHT);
					break;
				#if 0
				case 0xE1:
					UISound_Play(DEMOSOUND_SOUND_EP44_TONE_CARE_FRONT1);	
					UISound_Play(DEMOSOUND_SOUND_EP38_TONE_GAS_STATION);
					UISound_Play(DEMOSOUND_SOUND_EP24_TONE_SELECT_A_ROAD);
					break;
				#endif
				case 0xE2:
					UISound_Play(DEMOSOUND_SOUND_EP44_TONE_CARE_FRONT1);	
					UISound_Play(DEMOSOUND_SOUND_EP7_TONE_OIL_STATION);
					UISound_Play(DEMOSOUND_SOUND_EP24_TONE_SELECT_A_ROAD);
					break;
				#if 0
				case 0xE3:
					UISound_Play(DEMOSOUND_SOUND_EP44_TONE_CARE_FRONT1);	
					UISound_Play(DEMOSOUND_SOUND_EP34_TONE_TOLL_STATION);
					UISound_Play(DEMOSOUND_SOUND_EP24_TONE_SELECT_A_ROAD);
					break;
				#endif
				case 0xE4:
					UISound_Play(DEMOSOUND_SOUND_EP44_TONE_CARE_FRONT1);	
					UISound_Play(DEMOSOUND_SOUND_EP22_TONE_REST_STATION);
					UISound_Play(DEMOSOUND_SOUND_EP24_TONE_SELECT_A_ROAD);
					break;
				case 0xE5:
					UISound_Play(DEMOSOUND_SOUND_EP46_TONE_CARE_FRONT2);	
					UISound_Play(DEMOSOUND_SOUND_EP28_TONE_FORBID_PARKING);
					UISound_Play(DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE);
					break;
				case 0xE7:
					UISound_Play(DEMOSOUND_SOUND_EP44_TONE_CARE_FRONT1);	
					UISound_Play(DEMOSOUND_SOUND_EP15_TONE_SINGLE_ROAD);
					UISound_Play(DEMOSOUND_SOUND_EP0_TONE_WRONGDIRECT);
					break;
				case 0xE8:
					UISound_Play(DEMOSOUND_SOUND_EP46_TONE_CARE_FRONT2);	
					UISound_Play(DEMOSOUND_SOUND_EP17_TONE_BUS_ROAD);
					UISound_Play(DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE);
					break;
				default:
					break;
			}
		}
	}
}
BOOL FlowMovie_isEdogTypeValid(UINT8 type)
{
	BOOL ret = FALSE;
	//DBG_DUMP("^G========FlowMovie_isEdogTypeValid====0x%x\r\n",type);
	if(type!=0xff)
	{
		if(((type>=0x00)&&(type<=0x4F))||((type>=0x60)&&(type<=0xBF)))
		{
			ret = TRUE;
		}
		else 
		{
			switch(type)
			{
				case 0xC2:
				case 0xC3:
				case 0xC4:
				//case 0xC5:
				case 0xC7:
				case 0xC8:
				case 0xD2:
				case 0xD3:
				case 0xD4:
				case 0xD6:
				case 0xD7:
				case 0xD9:
				case 0xDA:
				case 0xDB:
				//case 0xE1:
				case 0xE2:
				//case 0xE3:
				case 0xE4:
				case 0xE5:
				case 0xE7:
				case 0xE8:
					ret = TRUE;
					break;
				default:
					ret = FALSE;
					break;
			}
		}
	}
	else
	{
		ret = FALSE;
	}
	return ret;
}
#endif
#if 1//(defined(_NVT_ETHREARCAM_RX_))
static CHAR FolderName[32]="";
static CHAR FolderName1[32]="";
static CHAR FolderName2[32]="";
static CHAR FolderName3[32]="";
static CHAR FolderName4[32]="";
static CHAR FolderName5[32]="";
static UINT32 FileCnt=0;
static void Filesys_dirCB2(FIND_DATA *findDir, BOOL *bContinue, UINT16 *cLongname, UINT32 Param)
{
    *bContinue = TRUE;
    //DBG_DUMP(("Filesys_dirCB2 =%s  %s\r\n",findDir->filename,findDir->FATMainName));
    FileCnt++;
    switch(FileCnt)
    {
    case 1://./
        memcpy(&FolderName,findDir->filename, 20);
        DBG_DUMP("Filesys_dirCB2 1 **** =%s %d\r\n",FolderName,FileCnt);
        break;
    case 2://../
        memcpy(&FolderName1,findDir->filename, 20);
        DBG_DUMP("Filesys_dirCB2 2**** =%s %d\r\n",FolderName1,FileCnt);
        break;
    case 3:
        memcpy(&FolderName,findDir->filename, 20);
        DBG_DUMP("Filesys_dirCB2 3**** =%s %d\r\n",FolderName,FileCnt);
        break;
	case 4:
        memcpy(&FolderName1,findDir->filename, 20);
        DBG_DUMP("Filesys_dirCB2 4 **** =%s %d\r\n",FolderName1,FileCnt);
        break;
    case 5:
        memcpy(&FolderName2,findDir->filename, 20);
        DBG_DUMP("Filesys_dirCB2 5**** =%s %d\r\n",FolderName2,FileCnt);
        break;
    case 6:
        memcpy(&FolderName3,findDir->filename, 20);
        DBG_DUMP("Filesys_dirCB2 6**** =%s %d\r\n",FolderName3,FileCnt);
        break;
	case 7:
        memcpy(&FolderName4,findDir->filename, 20);
        DBG_DUMP("Filesys_dirCB2 7 **** =%s %d\r\n",FolderName4,FileCnt);
        break;
    case 8:
        memcpy(&FolderName5,findDir->filename, 20);
        DBG_DUMP("Filesys_dirCB2 8**** =%s %d\r\n",FolderName5,FileCnt);
        break;
    }  
}

BOOL UIFlowWndMovie_CheckFile(void)//no use
{
    FILEDB_HANDLE     FileDBHdl = 0;
    //PFILEDB_FILE_ATTR FileAttr = NULL;
    INT32   FileNum;

    //debug_err(("UIFlowWndMovie_CheckFile start! \r\n"));	
    FileDB_Refresh(0);

    //FileAttr = FileDB_NextFile(FileDBHdl);
    FileNum = FileDB_GetTotalFileNum(FileDBHdl);

    DBG_DUMP("UIFlowWndMovie_CheckFile =%d! \r\n",FileNum);	

    if (FileNum ==0)
    {
        return TRUE;
    }

    //debug_err(("UIFlowWndMovie_CheckFile Finsh \r\n"));	
    return FALSE;
}

BOOL UIFlowWndMovie_CheckFileFolder(void)
{
    static char item1_Buf[32] = {0};
    static char item2_Buf[32] = {0};
    static char item3_Buf[32] = {0};
    static char item4_Buf[32] = {0};
    static char item5_Buf[32] = {0};
    static char item6_Buf[32] = {0};

    DBG_DUMP("UIFlowWndMovie_CheckFileFolder\r\n");

    //if(UIFlowWndMovie_CheckFile())
    //    return  FALSE;

	if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED)
    {
        return FALSE;
    }

    if (FileSys_ScanDir("A:\\",Filesys_dirCB2,FALSE,0)==FST_STA_OK)
    {
        strncpy(item1_Buf, (FolderName),20);
        strncpy(item2_Buf, (FolderName1),20);
        strncpy(item3_Buf, (FolderName2),20);
		strncpy(item4_Buf, (FolderName3),20);
        strncpy(item5_Buf, (FolderName4),20);
        strncpy(item6_Buf, (FolderName5),20);

        DBG_DUMP("UIFlowWndMovie_CheckFileFolder 0 **** =%s %s\r\n",FolderName,item1_Buf);
        DBG_DUMP("UIFlowWndMovie_CheckFileFolder 1 **** =%s %s\r\n",FolderName1,item2_Buf);
        DBG_DUMP("UIFlowWndMovie_CheckFileFolder 2 **** =%s %s\r\n",FolderName2,item3_Buf);

        if(FileCnt<=2)
        {
            return FALSE;
        }
        else if(FileCnt==3)//include ./ ../
        {
            FileCnt=0;
            if((!strcmp(item1_Buf, "PERNIS"))|| \
               (!strcmp(item1_Buf, "asr_url.txt"))|| \
               (!strcmp(item1_Buf, "asr_serialnumber.txt"))|| \
               (!strcmp(item1_Buf, "edogtemp.dat"))|| \
               (!strcmp(item1_Buf, "edog_map.bin")))
            {
                return FALSE;
            }
        }
        else if(FileCnt==4)
        {
            FileCnt=0;
            if(((!strcmp(item1_Buf, "PERNIS"))||(!strcmp(item1_Buf, "asr_url.txt"))||(!strcmp(item1_Buf, "asr_serialnumber.txt"))||(!strcmp(item1_Buf, "edogtemp.dat"))||(!strcmp(item1_Buf, "edog_map.bin")))&& \
                ((!strcmp(item2_Buf, "PERNIS"))||(!strcmp(item2_Buf, "asr_url.txt"))||(!strcmp(item2_Buf, "asr_serialnumber.txt"))||(!strcmp(item2_Buf, "edogtemp.dat"))||(!strcmp(item2_Buf, "edog_map.bin"))))
            {
                return FALSE;
            }
        }
        else if(FileCnt==5)
        {
            FileCnt=0;
            if(((!strcmp(item1_Buf, "PERNIS"))||(!strcmp(item1_Buf, "asr_url.txt"))||(!strcmp(item1_Buf, "asr_serialnumber.txt"))||(!strcmp(item1_Buf, "edogtemp.dat"))||(!strcmp(item1_Buf, "edog_map.bin")))&& \
               ((!strcmp(item2_Buf, "PERNIS"))||(!strcmp(item2_Buf, "asr_url.txt"))||(!strcmp(item2_Buf, "asr_serialnumber.txt"))||(!strcmp(item2_Buf, "edogtemp.dat"))||(!strcmp(item2_Buf, "edog_map.bin")))&& \
               ((!strcmp(item3_Buf, "PERNIS"))||(!strcmp(item3_Buf, "asr_url.txt"))||(!strcmp(item3_Buf, "asr_serialnumber.txt"))||(!strcmp(item3_Buf, "edogtemp.dat"))||(!strcmp(item3_Buf, "edog_map.bin"))))
            {
                return FALSE;
            }
        }
		else if(FileCnt==6)
        {
            FileCnt=0;
            if(((!strcmp(item1_Buf, "PERNIS"))||(!strcmp(item1_Buf, "asr_url.txt"))||(!strcmp(item1_Buf, "asr_serialnumber.txt"))||(!strcmp(item1_Buf, "edogtemp.dat"))||(!strcmp(item1_Buf, "edog_map.bin")))&& \
               ((!strcmp(item2_Buf, "PERNIS"))||(!strcmp(item2_Buf, "asr_url.txt"))||(!strcmp(item2_Buf, "asr_serialnumber.txt"))||(!strcmp(item2_Buf, "edogtemp.dat"))||(!strcmp(item2_Buf, "edog_map.bin")))&& \
			   ((!strcmp(item3_Buf, "PERNIS"))||(!strcmp(item3_Buf, "asr_url.txt"))||(!strcmp(item3_Buf, "asr_serialnumber.txt"))||(!strcmp(item3_Buf, "edogtemp.dat"))||(!strcmp(item3_Buf, "edog_map.bin")))&& \
               ((!strcmp(item4_Buf, "PERNIS"))||(!strcmp(item4_Buf, "asr_url.txt"))||(!strcmp(item4_Buf, "asr_serialnumber.txt"))||(!strcmp(item4_Buf, "edogtemp.dat"))||(!strcmp(item4_Buf, "edog_map.bin"))))
            {
                return FALSE;
            }
        }
		else if(FileCnt==7)
        {
            FileCnt=0;
            if(((!strcmp(item1_Buf, "PERNIS"))||(!strcmp(item1_Buf, "asr_url.txt"))||(!strcmp(item1_Buf, "asr_serialnumber.txt"))||(!strcmp(item1_Buf, "edogtemp.dat"))||(!strcmp(item1_Buf, "edog_map.bin")))&& \
               ((!strcmp(item2_Buf, "PERNIS"))||(!strcmp(item2_Buf, "asr_url.txt"))||(!strcmp(item2_Buf, "asr_serialnumber.txt"))||(!strcmp(item2_Buf, "edogtemp.dat"))||(!strcmp(item2_Buf, "edog_map.bin")))&& \
			   ((!strcmp(item3_Buf, "PERNIS"))||(!strcmp(item3_Buf, "asr_url.txt"))||(!strcmp(item3_Buf, "asr_serialnumber.txt"))||(!strcmp(item3_Buf, "edogtemp.dat"))||(!strcmp(item3_Buf, "edog_map.bin")))&& \
               ((!strcmp(item4_Buf, "PERNIS"))||(!strcmp(item4_Buf, "asr_url.txt"))||(!strcmp(item4_Buf, "asr_serialnumber.txt"))||(!strcmp(item4_Buf, "edogtemp.dat"))||(!strcmp(item4_Buf, "edog_map.bin")))&&\
			   ((!strcmp(item5_Buf, "PERNIS"))||(!strcmp(item5_Buf, "asr_url.txt"))||(!strcmp(item5_Buf, "asr_serialnumber.txt"))||(!strcmp(item5_Buf, "edogtemp.dat"))||(!strcmp(item5_Buf, "edog_map.bin"))))
            {
                return FALSE;
            }
        }
		else 
        {
            FileCnt=0;
            if(((!strcmp(item1_Buf, "PERNIS"))||(!strcmp(item1_Buf, "asr_url.txt"))||(!strcmp(item1_Buf, "asr_serialnumber.txt"))||(!strcmp(item1_Buf, "edogtemp.dat"))||(!strcmp(item1_Buf, "edog_map.bin")))&& \
               ((!strcmp(item2_Buf, "PERNIS"))||(!strcmp(item2_Buf, "asr_url.txt"))||(!strcmp(item2_Buf, "asr_serialnumber.txt"))||(!strcmp(item2_Buf, "edogtemp.dat"))||(!strcmp(item2_Buf, "edog_map.bin")))&& \
			   ((!strcmp(item3_Buf, "PERNIS"))||(!strcmp(item3_Buf, "asr_url.txt"))||(!strcmp(item3_Buf, "asr_serialnumber.txt"))||(!strcmp(item3_Buf, "edogtemp.dat"))||(!strcmp(item3_Buf, "edog_map.bin")))&& \
               ((!strcmp(item4_Buf, "PERNIS"))||(!strcmp(item4_Buf, "asr_url.txt"))||(!strcmp(item4_Buf, "asr_serialnumber.txt"))||(!strcmp(item4_Buf, "edogtemp.dat"))||(!strcmp(item4_Buf, "edog_map.bin")))&& \
			   ((!strcmp(item5_Buf, "PERNIS"))||(!strcmp(item5_Buf, "asr_url.txt"))||(!strcmp(item5_Buf, "asr_serialnumber.txt"))||(!strcmp(item5_Buf, "edogtemp.dat"))||(!strcmp(item5_Buf, "edog_map.bin")))&& \
			   ((!strcmp(item6_Buf, "PERNIS"))||(!strcmp(item6_Buf, "asr_url.txt"))||(!strcmp(item6_Buf, "asr_serialnumber.txt"))||(!strcmp(item6_Buf, "edogtemp.dat"))||(!strcmp(item6_Buf, "edog_map.bin"))))
            {
                return FALSE;
            }
        }        
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif
#if (USE_FILEDB==ENABLE)
void UIFlowWndMovie_OnDeleteOld(void)
{
    UINT32 totalfilenum=0, filenum=0/*, sec=0*/;
    int index = 0,ROFilenum = 0,delROFilenum = 0,tmp = 0;
    PFILEDB_FILE_ATTR  pfile;

    // delete old file and start recording again
    if (SysGetFlag(FL_MOVIE_CYCLIC_REC) != MOVIE_CYCLICREC_OFF) 
	{
        /*
        switch (SysGetFlag(FL_MOVIE_CYCLIC_REC)) {
        case MOVIE_CYCLICREC_1MIN:
            sec = 60;
            break;
        case MOVIE_CYCLICREC_2MIN:
            sec = 120;
            break;
        case MOVIE_CYCLICREC_3MIN:
            sec = 180;
            break;
        case MOVIE_CYCLICREC_5MIN:
            sec = 300;
            break;
        case MOVIE_CYCLICREC_10MIN:
            sec = 600;
            break;
        }*/

        FileDB_Refresh(0);
        filenum = FileDB_GetTotalFileNum(0);
        totalfilenum = filenum;	  //get total file num

        if (filenum == 0) {
            DBG_DUMP("DeleteOld  !!!no file!!!!!++++++++++++++\r\n");
            return;
        }

        while (filenum--) {
            pfile = FileDB_SearhFile2(0,index);
            if (M_IsReadOnly(pfile->attrib)) {
                ROFilenum++;  //get ro file num
            }
            index++;
        }
        tmp = ROFilenum*10/totalfilenum;

        if (tmp >= 3) {
            delROFilenum = (3*ROFilenum - totalfilenum)/2;
        }

        DBG_DUMP("||||||RO::%d===ALL:%d====del:%d   sec:%d\r\n",ROFilenum,totalfilenum,delROFilenum,Movie_GetFreeSec());
        index = 0;

        while (totalfilenum--) 
        {
            pfile = FileDB_SearhFile2(0,index);

            if (Movie_GetFreeSec() < 600)//
			{ 
                if (M_IsReadOnly(pfile->attrib)) 
				{
                    //del RO  file >30%
                    if (delROFilenum > 0) 
					{
                        FileSys_SetAttrib(pfile->filePath,FST_ATTRIB_READONLY,FALSE);
                        FileSys_DeleteFile(pfile->filePath);
                        DBG_IND("====%d===path:%s\r\n",ret,pfile->filePath);
                        //FileDB_DeleteFile(0,index);
                        //debug_msg("1FP DEL File+++++++RO+++++++++%d %d  %d  %d  ret:%d\r\n",index,MovieExe_GetMaxRecSec(),(2*sec),delROFilenum,ret);
                    } 
                    delROFilenum--;
                } 
				else 
				{
					
                    //del normal file
                    FileSys_DeleteFile(pfile->filePath);
                    //FileDB_DeleteFile(0,index);
                    //debug_msg("1FP DEL File+++++++NORMAL+++++++++%d %d  %d\r\n",index,MovieExe_GetMaxRecSec(),(2*sec));
                }
            }
			else 
			{
            
                FileDB_Refresh(0);
                break;
            }
            index++;
        }
    }
}
#endif

