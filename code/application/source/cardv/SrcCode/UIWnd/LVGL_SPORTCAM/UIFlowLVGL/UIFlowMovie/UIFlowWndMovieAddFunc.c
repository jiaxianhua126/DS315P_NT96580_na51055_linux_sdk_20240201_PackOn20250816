#include "PrjInc.h"
#include "UIWnd/LVGL_SPORTCAM/UIInfo/UICfgDefault.h"
#include "UIApp/Network/UIAppWiFiCmdMovie.h"
#if(defined(_NVT_ETHREARCAM_RX_))
#include "UIApp/Network/EthCamAppSocket.h"
#include "UIApp/Network/EthCamAppCmd.h"
#include "UIApp/Network/EthCamAppNetwork.h"
#endif
#include "DxInput.h"
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
					if((!autoWifi) && ((SysGetFlag(FL_WIFI_AUTO) == WIFI_AUTO_ON))
						&&isFirstPowerOn)
					{
						//do not start rec,it starts to wifi
					}
					else
					{
						Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
						#if 1//(GPS_PANEL_FUNC==ENABLE)
						if (UI_GetData(FL_ADAS_PANEL) == ADAS_PANEL_ON) {
						    // LVGL-specific implementation
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
				if((!autoWifi) && ((SysGetFlag(FL_WIFI_AUTO) == WIFI_AUTO_ON))
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
	if ((!autoWifi) && ((SysGetFlag(FL_WIFI_AUTO) == WIFI_AUTO_ON))) {
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

BOOL FlowMovie_Specail_FormatWarning(void)
{
    return FALSE;
}

/* ���ؾ���ֵ */
int BaseDay_abs(int a,int b)
{
    if(a>=b)
        return (a-b);
    else
        return (b-a);
}

/* �ж��Ƿ�Ϊ����:��,���� 1 ; ����, ���� 0 . */
int BaseDay_IsLeap(int year)
{
    if(((year%4==0)&&(year%100!=0))||year%400==0)
        return 1;
    else
        return 0;
}

/* �ж�ĳ�����ڴ����(y��1��1��)������(y��m��d��)������ */
int BaseDay_Days(int y,int m,int d)
{
    int days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int i;
    int sum = 0 ;  /* �������� */

    if(BaseDay_IsLeap(y)) /* ���Ϊ����,2���� 29 �� */
        days[2] = 29;
    for(i=0;i<m;i++)
        sum = sum +days[i] ;
    sum = sum + d - 1 ;
    return sum;
}

/*
 �ж���������֮�������.
 ����һ:�� y1,�� m1,�� d1;
 ����һ:�� y2,�� m2,�� d2;
*/
int BaseDay_DiffDays(int y1,int m1,int d1,int y2,int m2,int d2)
{
    int s1,s2; /* �����������ڴ�����������ڵ����� */
    int count; /* �����������֮��Ĳ�ֵ */
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

    //debug_err("FlowMovie_CheckFormatWrning =%d\r\n",uiDayDiff);
    if(uiDayDiff > FlowMovie_CheckDateValue())
        return TRUE;
    else
        return FALSE;
}

void FlowMovie_USBRemovePowerOff(void)
{
    #if 1
    if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) {
        if (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD) {
            /*
            if (FlowMovie_GetRecCurrTime() <= 1) {
                Delay_DelayMs(1000);
            }
            */
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
            }
            */
            FlowMovie_StopRec();
            Delay_DelayMs(100);
            break;
        }
    }
}

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
		ImageApp_MovieMulti_SetCrash(_CFG_REC_ID_1, TRUE);
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
	//if(memcmp(&g_sEthCamMenuSetting, &sEthCamMenuSetting, sizeof(ETHCAM_MENU_SETTING)){
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
        }
        */

        FileDB_Refresh(0);
        filenum = FileDB_GetTotalFileNum(0);
        totalfilenum = filenum;   //get total file num

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

// Global variables
BOOL g_uiWiFiRecordIngMotionDet = FALSE;
BOOL g_uiWiFiParkingModeMotionDet = FALSE;
BOOL bWiFiConnected = FALSE;
BOOL bWndWiFiMovieOpenFirst = FALSE;
BOOL bWiFiRec_AutoStart = FALSE;
BOOL bWiFiRec_AutoStop = FALSE;
BOOL bWiFiModeChanged = FALSE;