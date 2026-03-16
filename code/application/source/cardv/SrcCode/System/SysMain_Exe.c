/*
    System Main Callback

    System Callback for System Module.

    @file       SysMain_Exe.c
    @ingroup    mIPRJSYS

    @note

    Copyright   Novatek Microelectronics Corp. 2010.  All rights reserved.
*/

////////////////////////////////////////////////////////////////////////////////
#include <unistd.h>
#include <sys/reboot.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include "PrjInc.h"
#include "Utility/SwTimer.h"
#include "vendor_common.h"
#include "GxTime.h"
#include "DxDisplay.h"
#include "comm/hwclock.h"
#include "UIWnd/UIFlow.h"
#include "UIWnd/SPORTCAM/UIInfo/UICfgDefault.h"
#include "UIApp/Network/EthCamAppNetwork.h"
#include "UIApp/Network/UIAppNetwork.h"
#include "UIApp/Network/UIAppWiFiCmdMovie.h"
#include "GxUSB.h"
#include "GxStrg.h"
#include "DxInput.h"
#include "UIApp/MD5/MD5.h"
#include "PStore.h"
#include "sys_mempool.h"
#include "Edog/EDogGlobal.h"
#include "DxEdog.h"



#define THIS_DBGLVL         2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          SysMainExe
#define __DBGLVL__          ((THIS_DBGLVL>=PRJ_DBG_LVL)?THIS_DBGLVL:PRJ_DBG_LVL)
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>
///////////////////////////////////////////////////////////////////////////////
extern void System_InstallModeObj(void);

extern VControl SystemObjCtrl;
extern VControl UISetupObjCtrl;
extern VControl *gUxCtrlTypeList[];
extern VControl *gAppCtrlTypeList[];

extern void GPIOMap_TurnOnLCDBacklight(void);
extern void GPIOMap_TurnOffLCDBacklight(void);
extern void GPIOMap_TurnOffLED(void);
extern void DrvGetCardGpio_State(void);
extern UINT32 XML_InitBuf(void);

#if (DISPLAY_FAST_SWITCH == ENABLE)
extern VControl FlowCommonCtrl;
#endif
#if(WIFI_AP_FUNC==ENABLE)
extern VControl UIWifiCmdObjCtrl;
#endif
static BOOL g_IsShutdownBegin = FALSE;

BOOL isACCTrigParkMode = FALSE; //isACCTrigTLMonior
BOOL isACCTrigLowBitrate = FALSE;
BOOL isACCTrigPreRecordDet = FALSE; //isACCTrigMotionDet
extern BOOL g_NotRecordWrn;

static UINT32 Sys_DateTime = DEFAULT_LAST_DATETIME;
extern BOOL g_bUsbRemovePowerOff;
extern BOOL g_bIsNeedReboot;
static UINT32 g_uiPreMovieSize = 0;
BOOL ComingParkMode = FALSE;
BOOL ExitParkMode = FALSE;


//-----------------------------------------------------------------------------
// delete FW bin file
//-----------------------------------------------------------------------------
BOOL Voice_Parrecordstart = FALSE;
BOOL BT_EVENT = FALSE;
void System_ResetNOW(void)
{
	//DBG_DUMP("GxSystem_SWResetNOW!!\r\n");
	reboot(0);
}
void GxSystem_SWResetNOW(void)
{
	DBG_DUMP("GxSystem_SWResetNOW!!\r\n");
	#if 1
	//设置参数参考watch dog reset.c ==>nvt_trigger_wdt_external
    DBG_DUMP("WTD reboot now...\r\n");
	system("modprobe na51055_wdt");
	system("mem w 0xF0050000 0x5a960112");
	system("mem w 0xF0050000 0x5a960113");
	system("mem w 0xf005000C 0x01");
	#else
	sync();
	SwTimer_DelayMs(100);
	reboot(RB_AUTOBOOT);
	#endif
}
INT32 UIMenuWndSetupDefaultSetting_Menu_Default_Reboot(BOOL std)
{
	//DBG_DUMP("FL_MOVIE_SIZE_MENU = %d\n",SysGetFlag(FL_MOVIE_SIZE_MENU));
	//DBG_DUMP("FL_MOVIE_SIZE = %d\n",SysGetFlag(FL_MOVIE_SIZE));
    Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_SYSRESET, 0);
    //SysSetFlag(FL_SYS_SOFT_RESET, SOFT_RESET_ON);
    SysSetFlag(FL_FIRSTPOWERON, FIRSTPOWERON_TRUE);  //@Ken 140620 for first power on
    Save_MenuInfo();
    //rtc_reset();  //reset time
	//DBG_DUMP("FL_MOVIE_SIZE_MENU = %d\n",SysGetFlag(FL_MOVIE_SIZE_MENU));
	//DBG_DUMP("FL_MOVIE_SIZE = %d\n",SysGetFlag(FL_MOVIE_SIZE));

    if (std == TRUE) {
		//GPIOMap_TurnOffLCDBacklight();
        SwTimer_DelayMs(100);
        GxSystem_SWResetNOW();//GxSystem_Reboot();
    }
    return 0;
}

#define DELETE_FWBIN_FILE_NAME  "A:\\"_BIN_NAME_".bin"
#define DELETE_FWBIN_FILE_NOTE  "A:\\update_no_delete.htk"
void DeleteBinFile(void)
{
    FST_FILE fp = NULL;
    BOOL bin_file_found, bin_file_delete;
    INT32 ret = -1;
    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        DBG_DUMP("System_GetState(SYS_STATE_CARD)  = %d!\r\n",  System_GetState(SYS_STATE_CARD) );
        return;
    }

    //DBG_DUMP("\r\n");
    //DBG_DUMP("================================\r\n");
    //DBG_DUMP("DeleteBinFile!!\r\n");
    //DBG_DUMP("================================\r\n");
    //DBG_DUMP("\r\n");
    fp = FileSys_OpenFile(DELETE_FWBIN_FILE_NAME, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (fp) {
        //DBG_DUMP("bin_file_found = TRUE\r\n");
        bin_file_found = TRUE;
        FileSys_CloseFile(fp);
    } else {
        bin_file_found = FALSE;
    }

    fp = FileSys_OpenFile(DELETE_FWBIN_FILE_NOTE, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (fp) {
        //DBG_DUMP("bin_file_delete = FALSE\r\n");
        bin_file_delete = FALSE;
        FileSys_CloseFile(fp);
    } else {
        bin_file_delete = TRUE;
    }

    if (bin_file_found && bin_file_delete) {
        ret = FileSys_DeleteFile(DELETE_FWBIN_FILE_NAME);
        if (ret == FST_STA_OK) {
            //DBG_DUMP("FileSys_DeleteFile ok!!\r\n");
            UIMenuWndSetupDefaultSetting_Menu_Default_Reboot(TRUE);
	   //SysResetFlag();
        } else {
            //DBG_DUMP("FileSys_DeleteFile fail!!\r\n");
        }
    } else if ((bin_file_found == TRUE) && (bin_file_delete == FALSE)) {
        UIMenuWndSetupDefaultSetting_Menu_Default_Reboot(FALSE);
	//SysResetFlag();
    }
}


#if (ACC_CLOSE_WIFI == ENABLE)
void *AccEnWiFi10MClose(void *arg);
static pthread_t Accclosewifi_thr;
void AccDisenWiFi10MClose_UnInstall(void)
{
	pthread_cancel(Accclosewifi_thr);
}

void AccEnWiFi10MClose_Install(VControl *pCtrl)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	pthread_create(&Accclosewifi_thr,NULL,(void *)AccEnWiFi10MClose,(void *)pCtrl);
} 

void *AccEnWiFi10MClose(void *arg)
{
	static int Acctime = 0;
	VControl *parg = (VControl *) arg;
	if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) //wifi mode
	{
		while(1) {
			select_sleep(1000);
			Acctime ++;
			if(Acctime > 600) {
				Acctime = 0;
				if (UxCtrl_IsShow(&UIFlowWndUSBCtrl)) {
					Ux_CloseWindow((VControl *)(&UIFlowWndUSBCtrl), 0);
				}
				UIFlowWndWiFiMovie_OnCustom2(parg, 0, NULL);
				AccDisenWiFi10MClose_UnInstall();
			}
		}
	}
	return 0;
}
#endif


void System_InstallAppObj(void)
{
	//Init object list for UIControl event process

	//register UI control type (from UIControl Lib)
	Ux_SetUITypeList(gUxCtrlTypeList, CTRL_EX_TYPE_MAX - CTRL_TYPE_MIN);

#if (DISPLAY_FAST_SWITCH == ENABLE)
	//register FlowCommonCtrl as base ctrl of CTRL_WND
	gUxCtrlTypeList[CTRL_USER - CTRL_TYPE_MIN] = &FlowCommonCtrl;
	FlowCommonCtrl.wType = CTRL_BASE;
	gUxCtrlTypeList[CTRL_WND - CTRL_TYPE_MIN]->wType = CTRL_USER;
#endif

#if(WIFI_AP_FUNC==ENABLE)
	gAppCtrlTypeList[APP_WIFICMD - APP_TYPE_MIN] = &UIWifiCmdObjCtrl; //set APP_WIFICMD = WifiCmdObjCtrl
#endif
	//register App control type (from AppControl Lib)
	Ux_SetAppTypeList(gAppCtrlTypeList, APP_TYPE_MAX - APP_TYPE_MIN);

	//set default active app = current system object
	Ux_SetActiveApp(&UISetupObjCtrl);
}

///////////////////////////////////////////////////////////////////////
#include "GxTimer.h"

int SX_TIMER_DET_TIMER_ID = -1;
void Timer_CB(UINT32 event, UINT32 param1, UINT32 param2);

SX_TIMER_ITEM(System_CntTimer, GxTimer_CountTimer, 1, TRUE)

void System_OnTimerInit(void)
{
	//PHASE-1 : Init & Open Drv or DrvExt
	{
		GxTimer_RegCB(Timer_CB);         //Register CB function of GxTimer
		SX_TIMER_DET_TIMER_ID = SxTimer_AddItem(&Timer_System_CntTimer);
		//5.註冊SxCmd服務 ---------> Cmd Function
		//HwClock_InstallCmd();
	}
	{
		//PHASE-2 : Init & Open Lib or LibExt
		//test GxTimer
		/*
#define TIMER_ONE_SEC                   1000
		static UINT32   g_uiAudioTestTimer = NULL_TIMER;
		if (g_uiAudioTestTimer == NULL_TIMER)
		{
		    g_uiAudioTestTimer = GxTimer_StartTimer(TIMER_ONE_SEC, NVTEVT_1SEC_TIMER, CONTINUE);
		}
		*/
	}
}
void System_OnTimerExit(void)
{
	//PHASE-2 : Close Lib or LibExt
	{
	}
	//PHASE-1 : Close Drv or DrvExt
	{
	}
}

///////////////////////////////////////////////////////////////////////
//System flow event

#if (PWR_FUNC == ENABLE)
#include "GxPower.h"
#endif

extern UINT32 Input_GroupStatus2Event(UINT32 status);
extern BOOL g_bConsumeStatus;
extern BOOL gbIsPlayBackModePowerOn;
extern INT32 System_GetFirstSensorMode(INT32 iCurrMode);

#if 0
INT32 System_GetPoweronModeByFWInfo(void)
{
	MODELEXT_HEADER *header = NULL;
	BININFO *pBinInfo = (BININFO *)Dx_GetModelExtCfg(MODELEXT_TYPE_BIN_INFO, &header);
	if (!pBinInfo || !header) {
		DBG_ERR("bininfo is null\r\n");
		return System_GetFirstSensorMode(PRIMARY_MODE_MAIN);
	}
	if (pBinInfo->fw.Resv[0]== 0)
		return System_GetFirstSensorMode(PRIMARY_MODE_MAIN);
	else
		return System_GetFirstSensorMode(PRIMARY_MODE_IPCAM);

}
#endif

INT32 System_GetBootFirstMode(void)
{
#if (IPCAM_MODE == ENABLE)
	#if 0
	return System_GetPoweronModeByFWInfo();
	#else
	return System_GetFirstSensorMode(PRIMARY_MODE_IPCAM);
	#endif
#else
    #if !UI_SENSOR
        return PRIMARY_MODE_MOVIE;
    #else
    	return System_GetFirstSensorMode(PRIMARY_MODE_MOVIE);
    #endif
	//return System_GetFirstSensorMode(PRIMARY_MODE_PHOTO);

#endif
}

//-----------------------------------------------------------------------------
// test gps
//-----------------------------------------------------------------------------
#if 1//(TEST_GPS == ENABLE)
#define TEST_GPS_FILE_NAME  "A:\\test.gps"
static BOOL getintotestGPS = FALSE;
void SysInit_getintoGPS_mode_setstd(BOOL std)
{
    getintotestGPS = std;
}
BOOL SysInit_getintoGPS_mode_getstd(void)
{
    return getintotestGPS;
}

BOOL SysInit_getintoGPS_getfile(void)
{
    FST_FILE fp = NULL;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        return 0;
    }

    fp = FileSys_OpenFile(TEST_GPS_FILE_NAME, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (fp) {
        //DBG_DUMP("getintoGPS_getfile = TRUE\r\n");
        SysInit_getintoGPS_mode_setstd(TRUE);
        FileSys_CloseFile(fp);
    } else {
       //DBG_DUMP("getintoGPS_getfile = FALSE\r\n");
        SysInit_getintoGPS_mode_setstd(FALSE);
    }
    return 0;
}
#endif

//-----------------------------------------------------------------------------
// test pcc
//-----------------------------------------------------------------------------
#if 1//(TEST_PCC == ENABLE)
#define TEST_PCC_FILE_NAME  "A:\\test.pcc"
static BOOL getintotestpcc = FALSE;
void SysInit_getintopcc_mode_setstd(BOOL std)
{
    getintotestpcc = std;
}
BOOL SysInit_getintopcc_mode_getstd(void)
{
    return getintotestpcc;
}

BOOL SysInit_getintopcc_getfile(void)
{
    FST_FILE fp = NULL;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        return 0;
    }

    fp = FileSys_OpenFile(TEST_PCC_FILE_NAME, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (fp) {
        //debug_msg("getintopcc_getfile = TRUE\r\n");
        SysInit_getintopcc_mode_setstd(TRUE);
        FileSys_CloseFile(fp);
    } else {
        SysInit_getintopcc_mode_setstd(FALSE);
    }
    return 0;
}
#endif

//-----------------------------------------------------------------------------
// test ADAS
//-----------------------------------------------------------------------------
#if 1//(TEST_ADAS == ENABLE)
#define TEST_ADAS_FILE_NAME  "A:\\test.adas"

static BOOL getintotestadas = FALSE;
void SysInit_getintoadas_mode_setstd(BOOL std)
{
    getintotestadas = std;
}
BOOL SysInit_getintoadas_mode_getstd(void)
{
    return getintotestadas;
}

BOOL SysInit_getintoadas_getfile(void)
{
    FST_FILE fp = NULL;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
		DBG_ERR("NO CARD!\r\n");
        return 0;
    }

    fp = FileSys_OpenFile(TEST_ADAS_FILE_NAME, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (fp) {
        DBG_WRN("getintoADAS_getfile = TRUE\r\n");
        SysInit_getintoadas_mode_setstd(TRUE);
        FileSys_CloseFile(fp);
    } else {
        SysInit_getintoadas_mode_setstd(FALSE);
    }
    return 0;
}
#endif


void System_LastDateTimeSet(void)
{
    struct tm Curr_DateTime;
    GxTime_GetTime(&Curr_DateTime);

    Sys_DateTime = Curr_DateTime.tm_year*1000000 + Curr_DateTime.tm_mon*10000 + Curr_DateTime.tm_mday*100 + Curr_DateTime.tm_hour;
    UI_SetData(FL_LAST_DATETIME, Sys_DateTime);
}

void SysInit_CheckDateTime(void)
{
    struct tm Curr_DateTime;
    GxTime_GetTime(&Curr_DateTime);

    DBG_DUMP("*** year = %d ***\r\n", Curr_DateTime.tm_year);
    #if 0
    if ((Curr_DateTime.tm_year < MIN_YEAR) || (Curr_DateTime.tm_year > MAX_YEAR)) {
        Curr_DateTime.tm_year = DEF_YEAR;
        Curr_DateTime.tm_mon = DEF_MONTH;
        Curr_DateTime.tm_mday = DEF_DAY;
        Curr_DateTime.tm_hour = 0;
        Curr_DateTime.tm_min = 0;
        Curr_DateTime.tm_sec = 0;

        HwClock_SetTime(TIME_ID_CURRENT, Curr_DateTime, 0);
        FlowMovie_BaseDaySet(Curr_DateTime.tm_year, Curr_DateTime.tm_mon, Curr_DateTime.tm_mday);
    }
    #else
    Sys_DateTime = UI_GetData(FL_LAST_DATETIME);
	//DBG_DUMP("Sys_DateTime = %d\n",Sys_DateTime);
    if ((Curr_DateTime.tm_year < (int)(Sys_DateTime/1000000)) || (Curr_DateTime.tm_year > MAX_YEAR)) {
        Curr_DateTime.tm_year = (int)(Sys_DateTime/1000000);
        Curr_DateTime.tm_mon = (int)((Sys_DateTime%1000000)/10000);
        Curr_DateTime.tm_mday = (int)((Sys_DateTime%10000)/100);
        Curr_DateTime.tm_hour = (int)(Sys_DateTime%100);
        Curr_DateTime.tm_min = 0;
        Curr_DateTime.tm_sec = 0;

		hwclock_set_time(TIME_ID_CURRENT, Curr_DateTime, 0);
        //GxTime_SetTime(Curr_DateTime);
    	//	Curr_DateTime = hwclock_get_time(TIME_ID_CURRENT);
	//	DBG_DUMP("*** year = %d ***\r\n", Curr_DateTime.tm_year);
        FlowMovie_BaseDaySet(Curr_DateTime.tm_year, Curr_DateTime.tm_mon, Curr_DateTime.tm_mday);
    }
    #endif
}


#if 1
//-----------------------------------------------------------------------------
// CarNo backup
//-----------------------------------------------------------------------------
#define CARNO_BACKUP_FILE_NAME  "A:\\CarNo_Backup.txt"
static BOOL CarNoBackup = FALSE;
void SysInit_CarNoBackup_setstd(BOOL std)
{
    CarNoBackup = std;
}
BOOL SysInit_CarNoBackup_getstd(void)
{
    return CarNoBackup;
}

BOOL SysInit_CarNoBackup_getfile(void)
{
    FST_FILE fp = NULL;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        SysInit_CarNoBackup_setstd(TRUE);
        return 0;
    }

    fp = FileSys_OpenFile(CARNO_BACKUP_FILE_NAME, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (fp) {
        //debug_msg("CarNoBackup_getfile = TRUE\r\n");
        SysInit_CarNoBackup_setstd(TRUE);
        FileSys_CloseFile(fp);
    } else {
        SysInit_CarNoBackup_setstd(FALSE);
    }
    return 0;
}

extern BOOL g_CarNoErr;
extern char CarNo_Buf[13];
#define FILE_SIZE_MAX   14
void GetCarNumFile(void)
{
    FST_FILE pFile = NULL;
    UINT32  uiFileSize = 0;
    char uiBuf[FILE_SIZE_MAX] = {0};
    char temCarNum[13] = "           ";
    INT32 ret = -1;
    UINT32 i = 0;

    if ((System_GetState(SYS_STATE_CARD) == CARD_REMOVED) || (g_CarNoErr == FALSE)) {
        return;
    }

    //FileSys_WaitFinish();
    pFile = FileSys_OpenFile(CARNO_BACKUP_FILE_NAME, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (pFile) {
        uiFileSize = (UINT32)FileSys_GetFileLen(CARNO_BACKUP_FILE_NAME);	// for small page nand
        //debug_err(("****** CarNum file size = %d ******\r\n", uiFileSize));

        if ((uiFileSize == 0) || (uiFileSize > FILE_SIZE_MAX)) {
            //debug_msg("****** CarNum read fail******\r\n");
            FileSys_CloseFile(pFile);
            return;
        }

        ret = FileSys_ReadFile(pFile, (UINT8*)uiBuf, &uiFileSize, 0, NULL);
        FileSys_CloseFile(pFile);
        //FileSys_DeleteFile(CARNO_BACKUP_FILE_NAME);
        
        if (ret == FST_STA_OK) {
            for (i = 0; i < 13; i++) {
                if ((uiBuf[i]== '\0') ||(uiBuf[i] == '\n') || (uiBuf[i] == '\r')) {
                    break;
                }
                temCarNum[i] = uiBuf[i];
            }
            //debug_msg("^G *** temCarNum:%s, sizeof:%d, ***\r\n", temCarNum, sizeof(temCarNum));
            memcpy(&CarNo_Buf, &temCarNum, sizeof(char)*13);
            //debug_msg("^G *** CarNo_Buf:%s***\r\n", CarNo_Buf);
        }
    }
}
#endif


void signal_hander(int signum)
{
	//DBG_DUMP("signum is %d\n", signum);
	BT_EVENT = TRUE;
	Ux_PostEvent(NVTEVT_KEY_CUSTOM1, 1, NVTEVT_KEY_PRESS);
}


//-----------------------------------------------------------------------------
// TX FW Update FW
//-----------------------------------------------------------------------------
//#define ETHCAM_TXFW_UPDATE  			"A:\\RearcamS2P.update"
//#define ETHCAM_TXFW_FILE    			"A:\\RearcamS2P.bin"
static BOOL GetEthTxFW_Update = FALSE;
void SysInit_SetEthTxFW_Update_setstd(BOOL std)
{
    GetEthTxFW_Update = std;
}
BOOL SysInit_GetEthTxFW_Update_getstd(void)
{
    return GetEthTxFW_Update;
}

void SysInit_EthTxFW_Update_getfile(void)
{
    FST_FILE fp = NULL;
    INT32 ret = -1;
    UINT32 uiSize = 0; //FileSize
    BOOL bin_file_found, update_file_found,bin_file_delete;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        SysInit_SetEthTxFW_Update_setstd(FALSE);
    }
	fp = FileSys_OpenFile(DELETE_FWBIN_FILE_NOTE, FST_OPEN_READ|FST_OPEN_EXISTING);
	if (fp) {
		//DBG_DUMP("bin_file_delete = FALSE\r\n");
		bin_file_delete = FALSE;
		FileSys_CloseFile(fp);
	} else {
		bin_file_delete = TRUE;
	}

    fp = FileSys_OpenFile(ETHCAM_TXFW_FILE, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (fp) {
        uiSize = (UINT32)FileSys_GetFileLen(ETHCAM_TXFW_FILE);

        if (uiSize < 100) {
            FileSys_CloseFile(fp);
            ret = FileSys_DeleteFile(ETHCAM_TXFW_FILE);
            if (ret == FST_STA_OK) {
                DBG_DUMP("ETHCAM_TXFW_FILE delete ok!!\r\n");
            } else {
                DBG_ERR("ETHCAM_TXFW_FILE delete fail!!\r\n");
            }
            bin_file_found = FALSE;
        } else {
            FileSys_CloseFile(fp);
            bin_file_found = TRUE;
        }
    } else {
        bin_file_found = FALSE;
    }

    fp = FileSys_OpenFile(ETHCAM_TXFW_UPDATE, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (fp) {
        FileSys_CloseFile(fp);
		if(bin_file_delete){
	        ret = FileSys_DeleteFile(ETHCAM_TXFW_UPDATE);
	        if (ret == FST_STA_OK) {
	            DBG_DUMP("ETHCAM_TXFW_UPDATE delete ok!!\r\n");
	        } else {
	            DBG_ERR("ETHCAM_TXFW_UPDATE delete fail!!\r\n");
	        }
		}
        update_file_found = TRUE;
    } else {
        update_file_found = FALSE;
    }

    if (bin_file_found && update_file_found) {
        SysInit_SetEthTxFW_Update_setstd(TRUE);
    } else {
        SysInit_SetEthTxFW_Update_setstd(FALSE);
    }
}

//-----------------------------------------------------------------------------
// TX FW Boot Update
//-----------------------------------------------------------------------------
#define ETHCAM_BOOT_FILE    			"A:\\ethcam\\FW671QFA.bin"
#define ETHCAM_BOOT_UPDATE  			"A:\\EthcamBootFW.update"

static BOOL GetEthBootFW_Update = FALSE;
void SysInit_SetEthBootFW_Update_setstd(BOOL std)
{
    GetEthBootFW_Update = std;
}
BOOL SysInit_GetEthBootFW_Update_getstd(void)
{
    return GetEthBootFW_Update;
}

void SysInit_EthBootFW_Update_getfile(void)
{
    FST_FILE fp = NULL;
    INT32 ret = -1;
    UINT32 uiSize = 0; //FileSize
    BOOL bin_file_found, update_file_found,bin_file_delete;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        SysInit_SetEthBootFW_Update_setstd(FALSE);
    }

	fp = FileSys_OpenFile(DELETE_FWBIN_FILE_NOTE, FST_OPEN_READ|FST_OPEN_EXISTING);
	if (fp) {
		//DBG_DUMP("bin_file_delete = FALSE\r\n");
		bin_file_delete = FALSE;
		FileSys_CloseFile(fp);
	} else {
		bin_file_delete = TRUE;
	}

    fp = FileSys_OpenFile(ETHCAM_BOOT_FILE, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (fp) {
        uiSize = (UINT32)FileSys_GetFileLen(ETHCAM_BOOT_FILE);

        if (uiSize < 100) {
            FileSys_CloseFile(fp);
            ret = FileSys_DeleteFile(ETHCAM_BOOT_FILE);
            if (ret == FST_STA_OK) {
                //DBG_DUMP("ETHCAM_BOOT_FILE delete ok!!\r\n");
            } else {
                //DBG_DUMP("ETHCAM_BOOT_FILE delete fail!!\r\n");
            }
            bin_file_found = FALSE;
        } else {
            FileSys_CloseFile(fp);
            bin_file_found = TRUE;
        }
    } else {
        bin_file_found = FALSE;
    }
	
    fp = FileSys_OpenFile(ETHCAM_BOOT_UPDATE, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (fp) {
        FileSys_CloseFile(fp);
		if(bin_file_delete){
	        ret = FileSys_DeleteFile(ETHCAM_BOOT_UPDATE);
	        if (ret == FST_STA_OK) {
	            //DBG_DUMP("ETHCAM_BOOT_UPDATE delete ok!!\r\n");
	        } else {
	            //DBG_DUMP("ETHCAM_BOOT_UPDATE delete fail!!\r\n");
	        }
		}
        update_file_found = TRUE;
    } else {
        update_file_found = FALSE;
    }

    if (bin_file_found && update_file_found) {
        SysInit_SetEthBootFW_Update_setstd(TRUE);
    } else {
        SysInit_SetEthBootFW_Update_setstd(FALSE);
    }
}

//-----------------------------------------------------------------------------
//  FW bin file
//-----------------------------------------------------------------------------
//#define FWBIN_FILE_NAME_SRC  	"A:\\PERNIS\\"_BIN_NAME_".bin"
//#define FWBIN_FILE_NAME_DST 	"A:\\"_BIN_NAME_".bin"

void Move_FrontFW(void)
{
    FST_FILE fp = NULL;
    BOOL bin_file_found;
    INT32 ret = -1;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        return;
    }

    DBG_DUMP("\r\n");
    DBG_DUMP("================================\r\n");
    DBG_DUMP("==========Move_FrontFW============!!\r\n");
    DBG_DUMP("================================\r\n");
    DBG_DUMP("\r\n");

    fp = FileSys_OpenFile(FWBIN_FILE_NAME_SRC, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (fp) {
        DBG_DUMP("bin_file_found = TRUE\r\n");
        bin_file_found = TRUE;
        FileSys_CloseFile(fp);
    } else {
        bin_file_found = FALSE;
    }

    if (bin_file_found) {
        ret = FileSys_MoveFile(FWBIN_FILE_NAME_SRC,FWBIN_FILE_NAME_DST);
        if (ret == FST_STA_OK) {
            DBG_DUMP("FileSys_MoveFile ok!!\r\n");
            SwTimer_DelayMs(100);
        	//GxSystem_SWResetNOW();//GxSystem_Reboot();
        } else {
            DBG_DUMP("FileSys_MoveFile fail!!\r\n");
        }
    } 
}

//#define REARBIN_FILE_NAME_SRC  		"A:\\PERNIS\\RearcamS2P.bin"
//#define REARBIN_FILE_NAME_DST 		"A:\\RearcamS2P.bin"
BOOL isFront_OK(void)
{
	FST_FILE fp = NULL;
    BOOL isFrontOK = FALSE;

    fp = FileSys_OpenFile(FWBIN_FILE_NAME_SRC, FST_OPEN_READ|FST_OPEN_EXISTING);
	if(fp)
	{
		isFrontOK = TRUE;
		FileSys_CloseFile(fp);
	}
	else
	{
		isFrontOK = FALSE;
	}
	DBG_DUMP("\r\n");
    DBG_DUMP("================================\r\n");
    DBG_DUMP("isFrontOK =%d!!\r\n",isFrontOK);
    DBG_DUMP("================================\r\n");
    DBG_DUMP("\r\n");
	return isFrontOK;
}
BOOL isRear_OK(void)
{
	FST_FILE fp = NULL;
    BOOL isRearOK = FALSE;
	
	fp = FileSys_OpenFile(REARBIN_FILE_NAME_SRC, FST_OPEN_READ|FST_OPEN_EXISTING);	
	if(fp)
	{
		isRearOK = TRUE;
		FileSys_CloseFile(fp);
	}
	else
	{
		isRearOK = FALSE;
	}
	DBG_DUMP("\r\n");
    DBG_DUMP("================================\r\n");
    DBG_DUMP(" isRearOK=%d !!\r\n",isRearOK);
    DBG_DUMP("================================\r\n");
    DBG_DUMP("\r\n");
	return isRearOK;

}
extern char gFW_MD5[64];
extern char gEthFW_MD5[64];
extern UINT8 g_FWCnt; 
extern void UIFlowWndWiFiMovie_StopTimer(void);

void Update_FW(void)
{
    //FST_FILE fp = NULL;
    INT32 ret = -1;
	char *MD5_DATA = NULL;
	FST_FILE hFile = NULL;
	char md5DataFront[64] = {0};
	char md5DataRear[64] = {0};
	BOOL isFWok = FALSE;
	#if (defined(_NVT_ETHREARCAM_RX_))
	INT32 argc = 1;
	char *argv[]={"aaa"};
	#endif
    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        return;
    }
	
	if(isFront_OK()){
		if(g_FWCnt == 1)
		{
			Move_FrontFW();//before rear update,move Front FW.
			hFile = FileSys_OpenFile(FWBIN_FILE_NAME_DST, FST_OPEN_READ);
			if(hFile != 0)
			{
				MD5_DATA = MD5Data(hFile);
				memset(md5DataFront,0, sizeof(md5DataFront)/sizeof(md5DataFront[0]));
				strncpy(md5DataFront,MD5_DATA,strlen(MD5_DATA));
				DBG_DUMP("\r\n[HTK] Front FW md5Data=%s %d\r\n",md5DataFront,strlen(md5DataFront));
			}
			FileSys_CloseFile(hFile);
			if(0!= memcmp(md5DataFront,gFW_MD5,sizeof(gFW_MD5)))
			{
	        	FileSys_DeleteFile(FWBIN_FILE_NAME_DST);
				FileSys_DeleteFile(FWBIN_FILE_NAME_SRC);
			}
			else
			{
				extern BOOL g_bIsNeedReboot;
				g_bIsNeedReboot = TRUE;
				System_PowerOff(SYS_POWEROFF_NORMAL);	
			}
			
		}
		else if (g_FWCnt == 2)
		{
			#if 0//do nothing 
			hFile = FileSys_OpenFile(FWBIN_FILE_NAME_SRC, FST_OPEN_READ);
			if(hFile != 0)
			{
				MD5_DATA = MD5Data(hFile);
				memset(md5DataFront,0, sizeof(md5DataFront)/sizeof(md5DataFront[0]));
				strncpy(md5DataFront,MD5_DATA,strlen(MD5_DATA));
				DBG_DUMP("\r\n[HTK] Front FW md5Data=%s %d\r\n",md5DataFront,strlen(md5DataFront));
			}
			FileSys_CloseFile(hFile);
			if(0!= memcmp(md5DataFront,gFW_MD5,sizeof(gFW_MD5)))
			{
	        	FileSys_DeleteFile(FWBIN_FILE_NAME_SRC);
				FileSys_DeleteFile(FWBIN_FILE_NAME_DST);
				extern UINT8 g_bIsNeedReboot;
				g_bIsNeedReboot = 2;
				System_PowerOff(SYS_POWEROFF_NORMAL);	
			}
			#endif
		}
		else // no md5
		{
			Move_FrontFW();//before rear update,move Front FW.
		}
	    //DBG_DUMP("================================\r\n");
	    DBG_DUMP("Front FW move!!\r\n");
	    //DBG_DUMP("================================\r\n");
	}
	
    if (isRear_OK()) {
	    //DBG_DUMP("================================\r\n");
	    DBG_DUMP("Rear FW move!!\r\n");
	    //DBG_DUMP("================================\r\n");
        ret = FileSys_MoveFile(REARBIN_FILE_NAME_SRC,REARBIN_FILE_NAME_DST);
        if (ret == FST_STA_OK) {
            DBG_DUMP("FileSys_MoveFile ok!!\r\n");
			//FileSys_CloseFile(fp);
            SwTimer_DelayMs(100);
			SysInit_SetEthTxFW_Update_setstd(TRUE);
        	FlowMovie_WakeUpLCDBacklight();
			if (WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD) {
		        if (FlowWiFiMovie_GetRecCurrTime() <= 1) {
		            Delay_DelayMs(1000);
		        }
		        FlowWiFiMovie_StopRec();
		        Delay_DelayMs(300);
		    }
			
			UIFlowWndWiFiMovie_StopTimer();
			if(g_FWCnt == 1)
			{
				hFile = FileSys_OpenFile(REARBIN_FILE_NAME_DST, FST_OPEN_READ);
				//DBG_DUMP("hFile = %d\r\n",hFile);
				if(hFile != 0)
				{
					MD5_DATA = MD5Data(hFile);
					memset(md5DataRear,0, sizeof(md5DataRear)/sizeof(md5DataRear[0]));
					strncpy(md5DataRear,MD5_DATA,strlen(MD5_DATA));
					DBG_DUMP("\r\n[HTK] ethCam FW md5Data=%s %d\r\n",md5DataRear,strlen(md5DataRear));
				}
				FileSys_CloseFile(hFile);
				if(0 == memcmp(md5DataRear,gFW_MD5,sizeof(gFW_MD5)))
				{
					#if (defined(_NVT_ETHREARCAM_RX_))
	            	Cmd_ethcam_tx_fwupdate(argc,argv);
					#endif
				}
				else
				{
					FileSys_DeleteFile(REARBIN_FILE_NAME_DST);
					FileSys_DeleteFile(REARBIN_FILE_NAME_SRC);
					extern BOOL g_bIsNeedReboot;
					g_bIsNeedReboot = TRUE;
					System_PowerOff(SYS_POWEROFF_NORMAL);	
				}
			}
			else if (g_FWCnt == 2)
			{
				Move_FrontFW();//before rear update,move Front FW.
				hFile = FileSys_OpenFile(FWBIN_FILE_NAME_DST, FST_OPEN_READ);
				if(hFile != 0)
				{
					MD5_DATA = MD5Data(hFile);
					memset(md5DataFront,0, sizeof(md5DataFront)/sizeof(md5DataFront[0]));
					strncpy(md5DataFront,MD5_DATA,strlen(MD5_DATA));
					DBG_DUMP("\r\n[HTK] Front FW md5Data=%s %d\r\n",md5DataFront,strlen(md5DataFront));
				}
				FileSys_CloseFile(hFile);
				
				FileSys_WaitFinish();
				hFile = FileSys_OpenFile(REARBIN_FILE_NAME_DST, FST_OPEN_READ);
				//DBG_DUMP("hFile = %d\r\n",hFile);
				if(hFile != 0)
				{
					MD5_DATA = MD5Data(hFile);
					memset(md5DataRear,0, sizeof(md5DataRear)/sizeof(md5DataRear[0]));
					strncpy(md5DataRear,MD5_DATA,strlen(MD5_DATA));
					DBG_DUMP("\r\n[HTK] ethCam FW md5Data=%s %d\r\n",md5DataRear,strlen(md5DataRear));
				}
				FileSys_CloseFile(hFile);
				
				if(0== memcmp(md5DataFront,gFW_MD5,sizeof(gFW_MD5))
					&&(0== memcmp(md5DataRear,gEthFW_MD5,sizeof(gEthFW_MD5))))
				{
					isFWok = TRUE;
				}
				else
				{
					isFWok = FALSE;
		        	FileSys_DeleteFile(FWBIN_FILE_NAME_DST);
					FileSys_DeleteFile(REARBIN_FILE_NAME_DST);
				}
				if(isFWok)
				{
					#if (defined(_NVT_ETHREARCAM_RX_))
	            	Cmd_ethcam_tx_fwupdate(argc,argv);
					#endif
				}
				else
				{
					//FileSys_DeleteFile(REARBIN_FILE_NAME_DST);
					extern BOOL g_bIsNeedReboot;
					g_bIsNeedReboot = TRUE;
					System_PowerOff(SYS_POWEROFF_NORMAL);	
				}
			}
			else//no md5 
			{
				#if (defined(_NVT_ETHREARCAM_RX_))
				Cmd_ethcam_tx_fwupdate(argc,argv);
				#endif
			}
        } else {
            DBG_DUMP("FileSys_MoveFile fail!!\r\n");
			FileSys_DeleteFile(FWBIN_FILE_NAME_SRC);
			FileSys_DeleteFile(REARBIN_FILE_NAME_SRC);
        }
    } 
}
void Delete_FW(void)
{
	FileSys_DeleteFile(FWBIN_FILE_NAME_SRC);
	FileSys_DeleteFile(REARBIN_FILE_NAME_SRC);
	FileSys_DeleteFile(FWBIN_FILE_NAME_DST);
	FileSys_DeleteFile(REARBIN_FILE_NAME_DST);
}
#if 1
#define  PS_EDOGDATA1    "EDOGDATA1"
#define  E_DOG_DATA_PATH  "/mnt/sd2/edog_map.bin"
#define  E_DOG_DATA_TMP_PATH  "/mnt/sd2/edogtemp.dat"
extern UINT32 XML_GetTempMem(UINT32 uiSize);

PPSTORE_SECTION_HANDLE  EDOGpSection=E_PS_SECHDLER;
UINT32  EdogPstoreSize =0 ;
#if 0
void GetEdogPstoreSize(void)
{
    BOOL is_exist = FALSE;
    BOOL b_next = FALSE;
    PSTORE_SEARCH_HANDLE search_hdl;
    b_next = PStore_SearchSectionOpen(&search_hdl);
    while (b_next) {
    	DBG_DUMP("%15s\r\n", search_hdl.pSectionName);
    	if (!strncmp(PS_EDOGDATA1, search_hdl.pSectionName, 12)) {
            CHKPNT;
			is_exist = TRUE;
			EdogPstoreSize= search_hdl.uiSectionSize;
    		break;
    	}
    	b_next = PStore_SearchSection(&search_hdl);
    }
    PStore_SearchSectionClose();

    if (is_exist == FALSE) {
    	DBG_DUMP("section %s does not exist\r\n", PS_EDOGDATA1);
    }
    DBGD(EdogPstoreSize);

}
#endif
BOOL EdogData_Load(void) //just for test ,write and read is the same??
{
	FILE		  *filehdl = NULL;
    INT32 ret = FST_STA_ERROR;
    UINT32    uiBuffer;
    ER er = E_PS_OK;

	if (System_GetState(SYS_STATE_CARD) != CARD_INSERTED)
	{
		return FALSE;
	}

    uiBuffer = XML_GetTempMem(POOL_SIZE_FILEDB);//OS_GetMempoolAddr(POOL_ID_APP);

    #if PST_FUNC
	DBG_DUMP("-------------------------load edog data start!!!-------------------------\r\n");
    //GetEdogPstoreSize();
	if(EDOGpSection==E_PS_SECHDLER)
    {
        EDOGpSection = PStore_OpenSection(PS_EDOGDATA1, PS_RDONLY);
    }
	er = PStore_ReadSection((UINT8 *)&EdogPstoreSize, 0, sizeof(EdogPstoreSize), EDOGpSection);
	if(E_PS_OK!=er){
		//DBG_DUMP("PS_EDOGDATA1 Read EdogPstoreSize =%d\r\n",EdogPstoreSize);
	}
	DBG_DUMP("PS_EDOGDATA1 Read EdogPstoreSize =%d\r\n",EdogPstoreSize);
	er = PStore_ReadSection((UINT8 *)uiBuffer, 0+4, EdogPstoreSize, EDOGpSection);
	if(E_PS_OK!=er){
		DBG_DUMP("PS_EDOGDATA1 Read Section er =%d\r\n",er);
	}
    
    filehdl = fopen(E_DOG_DATA_TMP_PATH,"w+");
    // Param filesize must > acture filesize
    if(filehdl!=NULL)
	{
	    ret = fwrite((UINT8*)uiBuffer,EdogPstoreSize, 1, filehdl);
		if(ret==1)
			DBG_DUMP("Load edog data success!!!\r\n");
		else
		{
			DBG_DUMP("Load edog data fail !!!\r\n");
			fclose(filehdl);
			return FALSE;
		}
	    fclose(filehdl);
		
		// 设置文件权限为只读
    	ret = chmod(E_DOG_DATA_TMP_PATH, S_IRUSR | S_IRGRP | S_IROTH);
	    if (ret == FST_STA_OK)
	    {
			DBG_DUMP("set edogdata.dat hidden Success.\r\n");
	    }
		DBG_DUMP("-------------------------load edog data complete!!!-------------------------\r\n");
	}
	else
	{
		DBG_DUMP("-------------------------open file fail!!!-------------------------\r\n");
		return FALSE;
	}
    #endif
	return TRUE;
}
FILE	*filehdl_edog = NULL;
UINT32      uiFileSize_edog = 0;
BOOL EdogData_Update_Check(void)
{
	BOOL ret = FALSE;
	struct stat st;

	filehdl_edog=fopen(E_DOG_DATA_PATH,"r");
	if(filehdl_edog!=NULL)
	{
		if (stat(E_DOG_DATA_PATH, &st) == 0)
		{
			DBG_DUMP("file size %ld \n", st.st_size);
			uiFileSize_edog = st.st_size;
		} 
		else 
		{
			DBG_DUMP("get file size fail\r\n");
			ret=FALSE;
			uiFileSize_edog = 0;
		}
		//DBG_DUMP("GPSRadar_IsDbValid====%d\r\n",GPSRadar_IsDbValid());

		if(uiFileSize_edog>0&&GPSRadar_IsDbValid())//if file not exist,the system is hung,when call GPSRadar_IsDbValid
		{
			ret = TRUE;
		
		}
		else
		{
			remove(E_DOG_DATA_PATH);
			ret = FALSE;
		}
		
	}
	DBG_DUMP("GPSRadar_IsDbValid====%d\r\n",ret);
	Delay_DelayMs(1000);
	if(filehdl_edog!=NULL)
	{
		fclose(filehdl_edog);
	}
	filehdl_edog = NULL;
	return ret;
}

UINT32 EdogData_Update(void)
{
    PPSTORE_SECTION_HANDLE  pSection;
	FILE		  *filehdl = NULL;
    UINT32      uiBuffer, uiFileSize;
	UINT32 i=0;
    ER er = E_PS_OK;
	struct stat st;
	BOOL bin_file_found=FALSE, bin_file_delete=FALSE;
	FST_FILE hFile = NULL;
	
	UINT32 uiPsFreeSpace = PStore_GetInfo(PS_INFO_FREE_SPACE);
    uiBuffer = ALIGN_CEIL_16(XML_GetTempMem(POOL_SIZE_FILEDB));//ALIGN_CEIL_16(OS_GetMempoolAddr(POOL_ID_APP));

    if(uiBuffer==0)
    {
        DBG_DUMP("not enough memory to read edogdata.dat file\r\n");
		return FALSE;
    }

	filehdl = fopen(E_DOG_DATA_PATH,"r");
	if (stat(E_DOG_DATA_PATH, &st) == 0) {
		  DBG_DUMP("file size %ld \n", st.st_size);
	} else {
	  DBG_DUMP("get file size fail\r\n");
	  return FALSE;
	}
	uiFileSize = st.st_size;
	if(filehdl != NULL)
	{
		fread((UINT8 *)uiBuffer, uiFileSize, 1, filehdl);//66x can get the file size and read the whole  file ,but the 67x can't get the file size,should specify the file size.
		fclose(filehdl);
		if((pSection = PStore_OpenSection(PS_EDOGDATA1, PS_RDWR)) != E_PS_SECHDLER)
		{
		 	PStore_CloseSection(pSection);
		 	PStore_DeleteSection(PS_EDOGDATA1);
			DBG_DUMP("PStore_DeleteSection PS_EDOGDATA1\r\n");
		}
		bin_file_found = TRUE;
		
	}
	else
	{
		return FALSE;
	}
	
	DBG_DUMP("----------------%s uiFileSize=%d  POOL_SIZE_APP=0x%x uiPsFreeSpace=%d\r\n",E_DOG_DATA_PATH,uiFileSize,POOL_SIZE_FILEDB,uiPsFreeSpace);
	//DBG_DUMP("----------------FileSys_GetFileLen   =%d\r\n",(UINT32)FileSys_GetFileLen(E_DOG_DATA_PATH));
	//uiFileSize = (UINT32)FileSys_GetFileLen(E_DOG_DATA_PATH);
#if PST_FUNC
    //save data to PStore	
	if((pSection = PStore_OpenSection(PS_EDOGDATA1, PS_RDWR | PS_CREATE)) != E_PS_SECHDLER)
	{	
		er = PStore_WriteSection((UINT8 *)&uiFileSize, 0, sizeof(uiFileSize), pSection);
		if(er != E_PS_OK)
		{
			DBG_DUMP("PS_EDOGDATA1	Write Section size =%d\r\n");
			PStore_CloseSection(pSection);
			return FALSE;	
		}
	
		er = PStore_WriteSection((UINT8 *)uiBuffer, 0 + sizeof(uiFileSize), uiFileSize, pSection);
		if(er != E_PS_OK)
		{
			DBG_DUMP("PS_EDOGDATA1  Write Section error i=%d\r\n",i);
			PStore_CloseSection(pSection);
			return FALSE;	
		}
		else
		{
			DBG_DUMP("PS_EDOGDATA1 Write Section success 0x%x\r\n",uiFileSize);
		}
	}
	PStore_CloseSection(pSection);
	DBG_DUMP("-------------------------Update edog data complete!!!-------------------------\r\n");
#endif
    hFile = FileSys_OpenFile(DELETE_FWBIN_FILE_NOTE, FST_OPEN_READ|FST_OPEN_EXISTING);
    if (hFile) {
        //DBG_DUMP("bin_file_delete = FALSE\r\n");
        bin_file_delete = FALSE;
        FileSys_CloseFile(hFile);
    } else {
        bin_file_delete = TRUE;
    }

	if(bin_file_delete&&bin_file_found)
	{
		remove(E_DOG_DATA_PATH);
		DBG_DUMP("Ignore deleting edogdata file.\r\n");
	}
	return TRUE;
}
#endif
void CloseEdogPstore(void)
{
    if(EDOGpSection != E_PS_SECHDLER)
    {
         PStore_CloseSection(EDOGpSection);
         EDOGpSection= E_PS_SECHDLER;
    }
}
UINT32 ReadPstore_EDogDate_Fun(UINT8 *buffer,UINT32 offset,UINT32 count)
{
    UINT32  result=-1;
    UINT32 len = 0;
	//CHKPNT;
	if(filehdl_edog!=NULL)
	{
	    len = (uiFileSize_edog >= (offset + count)) ? count : 0;
		fseek(filehdl_edog, offset, SEEK_SET);
		len = fread((UINT8 *)buffer, 1, len, filehdl_edog);		
		//DBG_DUMP("len=%d offset=%d count=%d 11111\r\n",len,offset,count);	
	    if(len < 0){
			len = 0;
	    }
		#if 0
		for(UINT32 i=0;i<len;i++)
		{
			DBG_DUMP("%02x",*(buffer+i));
		}
		DBG_DUMP("\r\n");
		#endif
	}
	else
	{
		len= (EdogPstoreSize >= (offset + count)) ? count : 0;
	    if((EDOGpSection != E_PS_SECHDLER)&&(len>0)){
		    result = PStore_ReadSection((UINT8 *)buffer, 0+4+offset,len, EDOGpSection);//4byte sotre data lens		    
			//DBG_DUMP("result=%d len=%d offset=%d count=%d 22222\r\n",result,len,offset,count);	
			if(result != E_PS_OK){
			   DBG_DUMP("Read PStore E_Dog Date fail  !!!\r\n");	
			   len = 0;
			}
	    }
	}
    return len;
}
#define PS_FORMAT_CHECK_FILE    "/mnt/sd2/PStore.plc"//"A:\\PStore.plc"
void SystemBoot_Delete_ASR(void)
{
	system("rm -rf /mnt/pstore/ASR");
}

void SystemBoot_PS_Format(void)
{
    FILE *fp = NULL;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        return;
    }

    fp = fopen(PS_FORMAT_CHECK_FILE, "r");
    if (fp)
    {
        fclose(fp);
        //System_PS_Format();
        SystemBoot_Delete_ASR();
    } 
}
//#define EDOGDATA_FILE_NAME_SRC "/mnt/sd/PERNIS/edog_map.bin"//"A:\\DCIM\\edog_map_enc.bin"
//#define EDOGDATA_FILE_NAME_DST "/mnt/sd/edog_map.bin"//"A:\\edog_map_enc.bin"

BOOL isEdogData_OK(void)
{
	FILE *fp = NULL;
    BOOL isFileOK = FALSE;
	
	fp = fopen(EDOGDATA_FILE_NAME_SRC, "r");	
	if(fp)
	{
		isFileOK = TRUE;
		fclose(fp);
		rename(EDOGDATA_FILE_NAME_SRC,EDOGDATA_FILE_NAME_DST);
		Delay_DelayMs(100);
		extern BOOL g_bIsNeedReboot;
		g_bIsNeedReboot = TRUE;
		System_PowerOff(SYS_POWEROFF_NORMAL);	
	}
	else
	{
		isFileOK = FALSE;
	}
	DBG_DUMP("\r\n");
    DBG_DUMP("================================\r\n");
    DBG_DUMP(" isEdogData_OK=%d !!\r\n",isFileOK);
    DBG_DUMP("================================\r\n");
    DBG_DUMP("\r\n");
	return isFileOK;

}
void  Delete_EdogDataFile(void)
{
	remove(EDOGDATA_FILE_NAME_SRC);
}
#define ADAS_CHECK_FILE    "/mnt/sd2/adas.plc"//"A:\\PStore.plc"

void SystemBoot_Adas_Check(void)
{
    FILE *fp = NULL;

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        return;
    }

    fp = fopen(ADAS_CHECK_FILE, "r");
    if (fp)
    {
        fclose(fp);
		system("umount /data/usr_adas"); 
		system("mount -o rw /dev/mtdblock8 /data/usr_adas");
		DBG_DUMP("=============remount======\r\n");
		system("rm -rf /data/usr_adas");
    } 
	/*else //default ro
	{
		system("umount /data/usr_adas"); 
		system("mount -o ro /dev/mtdblock8 /data/usr_adas");
	}*/
}

INT32 System_OnBoot(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	DBG_DUMP("^MOn Boot begin\r\n");
	
#if WATCHDOG_FUNC
	Watchdog_Init();
#endif

	if (paramNum == 1 && paramArray[0] == 0) { //power-on start
		//System_BootStart();
	}
	if (paramNum == 1 && paramArray[0] == 1) { //power-on end
		//#NT#2012/10/18#Philex Lin - begin
		UINT32 uiChangeTo;
#if (POWERON_WAIT_FS_READY == ENABLE)
		UINT32 uiFSStatus;
#endif
		//#NT#2012/10/18#Philex Lin - end
#if !defined(_IrRx_NONE_)
		IRRX_DEVICE_OBJ IrRxDevice;
#endif
		TM_BOOT_BEGIN("flow", "boot");

		//ui init state
		//#NT#2016/12/14#Niven Cho -begin
		//#NT#EMMC_AS_PSTORE
#if defined(_CPU2_LINUX_) && defined(_EMBMEM_EMMC_)
		System_OnStrgInit_PS(); //because ps uses filesys in this case, so ps init was moved here.
#if (BOOT_RESET_MENU_INFO == ENABLE)
		Load_MenuInfo();
#endif
#else
#if (BOOT_RESET_MENU_INFO == ENABLE)
		//EMMC_AS_PSTORE
        #if (defined(_CPU2_LINUX_) && defined(_EMBMEM_EMMC_))
		System_OnStrgInit_PS(); //because ps uses filesys in this case, so ps init was moved here.
		Load_MenuInfo();
		#else
        Load_MenuInfo(); //reset value cause the FL_FSStatus as '0', we do so before NVTEVT_STRG_ATTACH finish
        #endif
#endif
#endif
		//#NT#2016/12/14#Niven Cho -end
#if (BOOT_RESET_MENU_INFO == ENABLE)
		Init_MenuInfo();
#endif

		EthCamNet_SetTxIPAddr();//after load pstore

#if (UCTRL_FUNC)
		UctrlMain_Init();
#endif

		//wait fs init finish
#if (POWERON_WAIT_FS_READY == ENABLE)
		//if (System_GetState(SYS_STATE_POWERON) == SYSTEM_POWERON_SAFE) 
		{
#if(ONVIF_PROFILE_S!=ENABLE) //No File System
			//#NT#2017/04/18#Niven Cho -begin
            //#NT#FIX that B:\\ come first mounted.
            //wait all storages mounted.
			UINT32 i;
            UINT32 paramNum;
            UINT32 paramArray[MAX_MESSAGE_PARAM_NUM];
			UINT32 n_storage = (FS_MULTI_STRG_FUNC) ? 2 : 1;
			for (i=0; i<n_storage; i++)
			{
				UserWaitEvent(NVTEVT_STRG_ATTACH, &paramNum, paramArray);
			}
			//#NT#2017/04/18#Niven Cho -end
#endif
		}

		uiFSStatus = System_GetState(SYS_STATE_FS); //keep card insert status
		if(uiFSStatus != FS_INIT_OK) {
			DBG_WRN("FS init is not OK!\r\n");
		}

		//if (System_GetState(SYS_STATE_POWERON) == SYSTEM_POWERON_SAFE) {
			//if (System_OnStrgInit_EMBMEM_GetGxStrgType() == FST_FS_TYPE_UITRON) {
#if (IPCAM_FUNC != ENABLE)
				UI_SetFileDBFileID();
#endif
				// update card status again
				if (GxStrg_GetDeviceCtrl(0, CARD_READONLY)) {
					System_SetState(SYS_STATE_CARD, CARD_LOCKED);
				} else if (GxStrg_GetDeviceCtrl(0, CARD_INSERT)) {
					System_SetState(SYS_STATE_CARD, CARD_INSERTED);
				} else {
					System_SetState(SYS_STATE_CARD, CARD_REMOVED);
				}
				System_SetState(SYS_STATE_FS, uiFSStatus);
			//}
		//}
#endif
		DeleteBinFile();

		//wait disp init finish
		//wait audio init finish
		//wait usb init finish
		SxTimer_SetFuncActive(SX_TIMER_DET_TIMER_ID, TRUE);
#if(UI_FUNC)
		BKG_SetExecFuncTable(gBackgroundExtFuncTable);
#endif

		//get first app
#if !defined(_IrRx_NONE_)
		// Open IrRx driver
		irrx_open((PIRRX_DEVICE_OBJ)&IrRxDevice);
#endif
		//#NT#2016/03/07#KCHong -begin
		//#NT#Low power timelapse function
#if (TIMELAPSE_LPR_FUNCTION == ENABLE)
		extern BOOL g_bBootFromALM;
		if (g_bBootFromALM == FALSE) {
#endif


#if (POWERONLOGO_FUNCTION == ENABLE)
		{
			Display_ShowSplash(SPLASH_POWERON);
			Delay_DelayMs(80); // delay some time to avoid LCD flicker as power on
			GxVideo_SetDeviceCtrl(DOUT1, DISPLAY_DEVCTRL_BACKLIGHT, TRUE);
			//GPIOMap_TurnOnLCDBacklight();
		}
#endif
		TM_BOOT_END("video", "show_logo");

			//#NT#2016/03/07#KCHong -end
#if (POWERONSOUND_FUNCTION == ENABLE)
		// init Volume to max,100
		#if (AUDIO_FUNC == ENABLE)
		GxSound_SetVolume(100/*75*/); //100
		#endif
		if (System_GetState(SYS_STATE_POWERON) == SYSTEM_POWERON_SAFE) {
			// add power up sound
#if(UI_FUNC==ENABLE)
			UISound_Play(DEMOSOUND_SOUND_POWERON_TONE);
#endif
		}
#endif
		//#NT#2016/03/07#KCHong -begin
		//#NT#Low power timelapse function
#if (TIMELAPSE_LPR_FUNCTION == ENABLE)
		}
#endif
		//#NT#2016/03/07#KCHong -end

		//#NT#2013/1/6#Philex Lin-begin
#if 0 //(GPS_FUNCTION == ENABLE)
		DrvGPS_SetUartPort();
		GPSRec_Open(UART_BAUDRATE_9600);
#endif
		//#NT#2013/1/6#Philex Lin-end

#if (GSENSOR_FUNCTION == ENABLE)
       GSensorRec_Open();
#endif

#if (BT_FUNC == ENABLE)
		//System_OnBTInit();
		signal(SIGRTMAX, signal_hander); // 注册 SIGINT 的信号处理函数。
#endif
#if (OUTPUT_FUNC == ENABLE)
		// Turn on LED
		GxLED_SetCtrl(KEYSCAN_LED_RED, SET_TOGGLE_LED, TRUE);
#endif

		//#NT#2016/02/26#Niven Cho -begin
		//#NT#Fix, with FAST_BOOT=EN, linux, no compress, no partial, failed to boot.
#if defined(_CPU2_LINUX_)
		if (System_GetState(SYS_STATE_POWERON) == SYSTEM_POWERON_NORMAL) {
			//not so fast, linux is not ready yet, sir....
			DBG_DUMP("Wait CPU2 ready...\r\n");
			System_CPU2_WaitReady();
			//not so fast, fs is not mount yet, sir....
			DBG_DUMP("Wait FileSys mount finish...\r\n");
			//#NT#2016/03/02#Niven Cho -begin
			//#NT#Fix FAST_BOOT + LINUX + without card, boot failed.
			UserWaitEvent(NVTEVT_STRG_CHANGE, NULL, NULL);
			//#NT#2016/03/02#Niven Cho -end
		}
#endif
		//#NT#2016/02/26#Niven Cho -end
		TM_BOOT_END("flow", "boot");
#if (POWERON_FAST_BOOT == ENABLE)
		INIT_SETFLAG(FLGINIT_MODE);
#endif
#if (GPS_FUNCTION == ENABLE)
		// DrvGPS_SetUartPort();
		GPSRec_Open();
#endif
	
#if (ASR_FUNCTION == ENABLE)
		if (SysGetFlag(FL_ASR) == ASR_STANDARD) {
			ASR_SetMode(SysGetFlag(FL_LANGUAGE));
			ASR_Open();
		}
#endif
	
#if 1//(TEST_GPS == ENABLE)
		SysInit_getintoGPS_getfile();
#endif
	
#if 1//(TEST_PCC == ENABLE)
		SysInit_getintopcc_getfile();
#endif
	
		#if 1//(TEST_ADAS == ENABLE)
        SysInit_getintoadas_getfile();
		#endif

		SysInit_CarNoBackup_getfile();
		GetCarNumFile();
	
		XML_InitBuf();
		SysInit_CheckDateTime();
		SystemBoot_PS_Format();
		#if 0//delete
		if(EdogData_Update_Check())
		{
			EdogData_Update();
		}
		EdogData_Load();
		DBG_DUMP("------ Edog_Init = %ld ver=%s\r\n", Edog_Init(200),GPSRadar_GetLibVer());
		Edog_Handle_Init(); 
		EdogSound_Handle_Init();
		#endif
		SysInit_EthTxFW_Update_getfile();
		SysInit_EthBootFW_Update_getfile();
		DBG_DUMP("========BOOT========111111111111111111111\r\n");
		SystemBoot_Adas_Check();

		//bind user mem to ImageStream
		//ImageStream_ConfigUserDump();
		//open first app mode
		uiChangeTo = System_GetBootFirstMode();
#if ((POWERON_FAST_WIFI == ENABLE) && defined(_CPU2_LINUX_) && defined(_NETWORK_NONE_))
		UI_SetData(FL_WIFI_LINK, WIFI_LINK_OK);
		Ux_SendEvent(0, NVTEVT_SYSTEM_MODE, 2, uiChangeTo, SYS_SUBMODE_WIFI);
#elif ((POWERON_FAST_WIFI == ENABLE) && defined(_CPU2_ECOS_) && defined(_NETWORK_NONE_))
		UI_SetData(FL_WIFI_LINK, WIFI_LINK_OK);
		Ux_SendEvent(0, NVTEVT_SYSTEM_MODE, 2, uiChangeTo, SYS_SUBMODE_WIFI);
#else
		Ux_SendEvent(0, NVTEVT_SYSTEM_MODE, 1, uiChangeTo);
#endif
		UI_SetData(FL_NextMode, uiChangeTo);

		//!!!!! After boot, MUST reset power-on-state to SAFE for next time NVTEVT_SYSTEM_MODE !!!!!
		System_SetState(SYS_STATE_POWERON, SYSTEM_POWERON_SAFE);
	}
	DBG_DUMP("^MOn Boot end\r\n");
	return NVTEVT_CONSUME;
}

extern void UI_Quit(void);
extern UINT32 User_GetTempBuffer(UINT32 uiSize);
BOOL System_GetShutdownBegin(void)
{
	return g_IsShutdownBegin;
}

BOOL bUSBPreStd = FALSE;
INT32 System_OnShutdown(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
    int g_ipoweroffcnt = 0;
	bUSBPreStd = GxUSB_GetIsUSBPlug();
	DBG_DUMP("^MOn Shutdown begin %d\r\n",GxUSB_GetIsUSBPlug());
	if(g_IsShutdownBegin)
	{
		DBG_DUMP("^MOn Shutdown ignore\r\n");	
		return NVTEVT_CONSUME;
	}

	DBG_DUMP("^MOn Shutdown begin\r\n");
	if (paramNum == 1 && paramArray[0] == 0) { //power-off begin
		g_IsShutdownBegin=TRUE;
		if(System_IsBootFromRtos()){
			system("cardv sys dumpfbt_fdtapp"); //for fdt.app
		}

#if 1//(DISPLAY_FUNC == ENABLE)

#if 0//(POWEROFFLOGO_FUNCTION != ENABLE)
		if ((DX_HANDLE)GxVideo_GetDevice(DOUT1)) {
			GxVideo_SetDeviceCtrl(DOUT1, DISPLAY_DEVCTRL_BACKLIGHT, FALSE);
		}
#if (DISPLAY2_FUNC == ENABLE)
		if ((DX_HANDLE)GxVideo_GetDevice(DOUT2)) {
			GxVideo_SetDeviceCtrl(DOUT1, DISPLAY_DEVCTRL_BACKLIGHT, FALSE);
		}
#endif
#endif
		//DBG_DUMP("call System_OnShutdown\r\n");
        //stop watchdog
        #if WATCHDOG_FUNC
        //Watchdog_Disable();
		#endif
		//stop ASR
		#if (ASR_FUNCTION == ENABLE)
		if (SysGetFlag(FL_ASR) == ASR_STANDARD) {
			//printf("call ASR_STANDARD \r\n",SysGetFlag(FL_ASR) );
			ASR_Uninstall();
		}
		#endif
        //stop recording
        FlowMovie_USBRemovePowerOff();
		bWndWiFiMovieOpenFirst = FALSE;
		
		if (isACCTrigParkMode) {
			UI_SetData(FL_MOVIE_SIZE,g_uiPreMovieSize);
			UI_SetData(FL_MOVIE_SIZE_MENU, g_uiPreMovieSize);
		}

    	//#NT#2019/10/30#Philex Lin - begin
    	// fixed bug for can't stopping wifi station re-connect timer during shutdown
    	if (UI_GetData(FL_NetWorkMode) == NET_STATION_MODE)	
    	    Ux_CloseWindow(&UIMenuWndWiFiMobileLinkOKCtrl, 0);
    	//#NT#2019/10/30#Philex Lin - end
#if (UI_FUNC == ENABLE)
		// save RTC date data and file ID
		UI_SaveRTCDate();
#endif

#if (UI_FUNC == ENABLE)
        System_LastDateTimeSet();
        Save_MenuInfo();
#endif

        #if 1
        //close last app mode
        //Ux_SendEvent(0, NVTEVT_SYSTEM_MODE, 1, SYS_MODE_UNKNOWN);

        if (g_bUsbRemovePowerOff) {
            while (g_bUsbRemovePowerOff == TRUE) {
                g_ipoweroffcnt++;
                SwTimer_DelayMs(100);
                if (g_bUsbRemovePowerOff == FALSE) {
					//DBG_DUMP("call g_bUsbRemovePowerOff FALSE\r\n");
                    break;
                }
				/* wdj change g_ipoweroffcnt >= 30*/
                if (g_ipoweroffcnt >= 15) {
                    break;
                }
            }

            if (g_bUsbRemovePowerOff == FALSE) {
                Ux_SendEvent(0, NVTEVT_SYSTEM_MODE, 1, PRIMARY_MODE_MOVIE);
                if ((KeyScan_GetPlugDev() != PLUG_TV)&&(KeyScan_GetPlugDev() != PLUG_HDMI)) {
                    GPIOMap_TurnOnLCDBacklight();
                }
                Ux_PostEvent(NVTEVT_AC_Plug, 0, 0);
                return NVTEVT_CONSUME;
            }
        }
        #endif

		Display_SetEnable(LAYER_VDO1, FALSE); //turn off VDO1 to avoid garbage frame.
#endif

		//close last app mode
		Ux_SendEvent(0, NVTEVT_SYSTEM_MODE, 1, SYS_MODE_UNKNOWN);

#if _TODO //(IPCAM_FUNC == ENABLE)
		if (UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK) {
			//should close network application,then stop wifi
			Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_WIFI_STOP, 0);
		}
#else
        #if 0
		debug_msg("_TODO -> %s:%d, task(%x,%s) caller(%pF)\r\n", __FUNCTION__, __LINE__,
				  OS_GetTaskID(), OS_GetTaskName(), __builtin_return_address(0));
        #endif
#endif

		// low battery, lens error power off tone and screen
		if (System_GetState(SYS_STATE_POWEROFF) == SYS_POWEROFF_BATTEMPTY) {
			DBG_ERR("low battery **********\r\n");
		} else if (System_GetState(SYS_STATE_POWEROFF) == SYS_POWEROFF_LENSERROR) {
			DBG_ERR("lens error **********\r\n");
		} else {
#if (POWEROFFLOGO_FUNCTION == ENABLE)
            if (g_bUsbRemovePowerOff == FALSE) {
    			GxDisplay_Set(LAYER_OSD1, LAYER_STATE_ENABLE, 0); //turn off OSD1
    			GxDisplay_Flush(LAYER_OSD1);

    			Display_ShowSplash(SPLASH_POWEROFF);
    			GPIOMap_TurnOffLCDBacklight();
    			SwTimer_DelayMs(500);
                UISound_EnableKey(TRUE);
                UISound_Play(DEMOSOUND_SOUND_POWERON_TONE);//DEMOSOUND_SOUND_POWEROFF_TONE
                GxSound_WaitStop();
            }
#endif
		}

#if (UI_FUNC == ENABLE)
		//System_LastDateTimeSet();
		//Save_MenuInfo(); //move to front
#endif

#if (BT_FUNC == ENABLE)
		//System_OnBTExit();
#endif

		//#NT#2016/03/07#KCHong -begin
		//#NT#Low power timelapse function
#if (TIMELAPSE_LPR_FUNCTION == ENABLE)
		// Do not enable key and play power on tone
		extern BOOL g_bBootFromALM;
		if (g_bBootFromALM == FALSE) {
#endif
			//#NT#2016/03/07#KCHong -end
#if (POWEROFFSOUND_FUNCTION == ENABLE)
			//power off sound
#if(UI_FUNC==ENABLE)
			UISound_EnableKey(TRUE);
			UISound_Play(DEMOSOUND_SOUND_POWERON_TONE);
#endif
#endif
			//#NT#2016/03/07#KCHong -begin
			//#NT#Low power timelapse function
#if (TIMELAPSE_LPR_FUNCTION == ENABLE)
		}
#endif
		//#NT#2016/03/07#KCHong -end
		UI_LockEvent();

		UI_Quit(); //quit from event loop
	}
	if (paramNum == 1 && paramArray[0] == 1) { //power-off end
		//System_ShutDownEnd();
		//bQuit = TRUE;
	}
	g_IsShutdownBegin=FALSE;

	DBG_DUMP("^MOn Shutdown end\r\n");
	return NVTEVT_CONSUME;
}

INT32 System_OnACCShutdown(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
    DBG_DUMP("^MOn ACCShutdown begin\r\n");
    if (UI_GetData(FL_PARKING_MODE) != PARKING_MODE_OFF)
    {
        if (paramNum == 1 && paramArray[0] == 0) //power-off begin
        {
            if (isACCTrigParkMode)
            {
                DBG_DUMP("^MParking mode has been open already\r\n");
                return NVTEVT_CONSUME;
            }

            //GPIOMap_TurnOffLCDBacklight();

            //stop recording
            FlowMovie_USBRemovePowerOff();

            switch (UI_GetData(FL_PARKING_MODE))
            {
            case PARKING_MODE_ON_1FPS:
                isACCTrigLowBitrate = FALSE;
                isACCTrigPreRecordDet = FALSE;
                SysSetFlag(FL_PARKING_MODE_TIMELAPSE_REC, PARKING_MODE_TIMELAPSEREC_1SEC);
                break;

            case PARKING_MODE_ON_2FPS:
                isACCTrigLowBitrate = FALSE;
                isACCTrigPreRecordDet = FALSE;
                SysSetFlag(FL_PARKING_MODE_TIMELAPSE_REC, PARKING_MODE_TIMELAPSEREC_500MS);
                break;

            case PARKING_MODE_ON_3FPS:
                isACCTrigLowBitrate = FALSE;
                isACCTrigPreRecordDet = FALSE;
                SysSetFlag(FL_PARKING_MODE_TIMELAPSE_REC, PARKING_MODE_TIMELAPSEREC_333MS);
                break;

            case PARKING_MODE_ON_5FPS:
                isACCTrigLowBitrate = FALSE;
                isACCTrigPreRecordDet = FALSE;
                SysSetFlag(FL_PARKING_MODE_TIMELAPSE_REC, PARKING_MODE_TIMELAPSEREC_200MS);
                break;

            case PARKING_MODE_ON_10FPS:
                isACCTrigLowBitrate = FALSE;
                isACCTrigPreRecordDet = FALSE;
                SysSetFlag(FL_PARKING_MODE_TIMELAPSE_REC, PARKING_MODE_TIMELAPSEREC_100MS);
                break;

            case PARKING_MODE_MOTION_DET:
                isACCTrigLowBitrate = FALSE;
                isACCTrigPreRecordDet = TRUE;
                MovieExe_PM_MD_LowBitrateRec();
                break;

            case PARKING_MODE_LOW_BITRATE:
                isACCTrigLowBitrate = TRUE;
                isACCTrigPreRecordDet = FALSE;
                MovieExe_LowBitrateRec();
                break;

            default:
                break;
            }

			//isACCTrigPowerOn = TRUE;
			#if  PLAY_SOUND_IN_OTHER_TASK
			UIDogSound_Enable(FALSE);
	        DogSoundPlayID(UIVoice_GetIndex(DEMOSOUND_SOUND_PARRECORDSTART_TONE));							
			UIDogSound_Enable(TRUE);
			#else
			UIVoice_Play(DEMOSOUND_SOUND_PARRECORDSTART_TONE);
			#endif
			#if 1
			if (SysGetFlag(FL_PARKING_OFF_GPS) == PGPS_TRUE) {
				GPSRec_Close();
			}
			#endif
			Voice_Parrecordstart = TRUE;
			isACCTrigParkMode = TRUE;
			g_NotRecordWrn = FALSE;
			g_uiPreMovieSize = UI_GetData(FL_MOVIE_SIZE);
			
			if (g_uiPreMovieSize >= MOVIE_SIZE_DUAL_3840x2160P30_1920x1080P30
				&&g_uiPreMovieSize < MOVIE_SIZE_DUAL_1920x1080P30_1920x1080P30) {//dual
				UI_SetData(FL_MOVIE_SIZE, MOVIE_SIZE_DUAL_1920x1080P30_1920x1080P30);
				UI_SetData(FL_MOVIE_SIZE_MENU, MOVIE_SIZE_DUAL_1920x1080P30_1920x1080P30);
			}else if(g_uiPreMovieSize >= MOVIE_SIZE_FRONT_3840x2160P30
					&&g_uiPreMovieSize < MOVIE_SIZE_FRONT_1920x1080P30){//single
				UI_SetData(FL_MOVIE_SIZE, MOVIE_SIZE_FRONT_1920x1080P30);
				UI_SetData(FL_MOVIE_SIZE_MENU, MOVIE_SIZE_FRONT_1920x1080P30);
			}

            if ((UI_GetData(FL_PARKING_MODE) != PARKING_MODE_MOTION_DET) && (UI_GetData(FL_PARKING_MODE) != PARKING_MODE_LOW_BITRATE))
            {
                Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_BITRATE, 1, SysGetFlag(FL_MOVIE_BITRATE));
            }
            //Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_PROTECT_AUTO,   1, SysGetFlag(FL_MOVIE_URGENT_PROTECT_AUTO));
            //Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_PROTECT_MANUAL, 1, SysGetFlag(FL_MOVIE_URGENT_PROTECT_MANUAL));

            if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) //wifi mode
            {
				#if (ACC_CLOSE_WIFI == ENABLE)
				//delay 10min close wifi
				ComingParkMode = TRUE;
				AccEnWiFi10MClose_Install(pCtrl);
				Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, System_GetState(SYS_STATE_CURRMODE));		
				//UIFlowWndWiFiMovie_OnCustom2(pCtrl, paramNum, paramArray);
				#else
				UIFlowWndWiFiMovie_OnCustom2(pCtrl, paramNum, paramArray);
				#endif
            }
            else
            {
                Ux_SendEvent(0, NVTEVT_SYSTEM_MODE, 1, PRIMARY_MODE_MOVIE);
            }
            //GPIOMap_TurnOffLCDBacklight();
        }
    }
    else
    {
        g_bIsNeedReboot = FALSE; //add for not reboot
        isACCTrigParkMode = FALSE;
        isACCTrigLowBitrate = FALSE;
        isACCTrigPreRecordDet = FALSE;
        if (!g_bUsbRemovePowerOff)
        {
            Ux_SendEvent(0, NVTEVT_SYSTEM_SHUTDOWN, 1, 0);
        }
    }

    DBG_DUMP("^MOn ACCShutdown end\r\n");
    return NVTEVT_CONSUME;
}

INT32 System_OnACCPowerOn(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
    DBG_DUMP("^MSystem_OnACCPowerOn\r\n");

    //isACCTrigPowerOn = TRUE;
    g_bUsbRemovePowerOff = FALSE;
    if (isACCTrigParkMode)//if ((SysGetFlag(FL_PARKING_MODE_TIMELAPSE_REC) != PARKING_MODE_TIMELAPSEREC_OFF) || isACCTrigLowBitrate || isACCTrigPreRecordDet)
    {
    	isACCTrigParkMode = FALSE;
		//stop recording
		FlowMovie_USBRemovePowerOff();
		UI_SetData(FL_MOVIE_SIZE,g_uiPreMovieSize);
		UI_SetData(FL_MOVIE_SIZE_MENU, g_uiPreMovieSize);

		//acc exit open gps 
		if (SysGetFlag(FL_PARKING_OFF_GPS) == PGPS_TRUE) {	
			GPSRec_Open();
		}

        isACCTrigLowBitrate = FALSE;
        isACCTrigPreRecordDet = FALSE;
        ParkingM_PreRecord_EMR = FALSE;
        g_NotRecordWrn = FALSE;
        Voice_Parrecordstart = FALSE;
        SysSetFlag(FL_PARKING_MODE_TIMELAPSE_REC, PARKING_MODE_TIMELAPSEREC_OFF);
        Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_BITRATE, 1, SysGetFlag(FL_MOVIE_BITRATE));
        //Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_PROTECT_AUTO,   1, SysGetFlag(FL_MOVIE_URGENT_PROTECT_AUTO));
        //Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_PROTECT_MANUAL, 1, SysGetFlag(FL_MOVIE_URGENT_PROTECT_MANUAL));
		if (System_GetState(SYS_STATE_CURRSUBMODE) == SYS_SUBMODE_WIFI) {     //wifi mode
			#if (ACC_CLOSE_WIFI == ENABLE)
			//delay 10min close wifi
			DBG_DUMP("^MOn System_OnACCPowerOn SYS_SUBMODE_WIFI end\r\n");
			ExitParkMode = TRUE;
			AccDisenWiFi10MClose_UnInstall();
			Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, System_GetState(SYS_STATE_CURRMODE));
			#else
			UIFlowWndWiFiMovie_OnCustom2(pCtrl, paramNum, paramArray);
			#endif
		} else {
			Ux_SendEvent(0, NVTEVT_SYSTEM_MODE, 1, PRIMARY_MODE_MOVIE);
		}
	}
    DBG_DUMP("^MOn System_OnACCPowerOn end\r\n");
    return NVTEVT_CONSUME;
}

INT32 System_OnMode(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	static BOOL bFirst = TRUE;
	int mode_id;
	if (paramNum < 1) {
		return NVTEVT_CONSUME;
	}

	mode_id = paramArray[0];
	if (paramNum == 2) {
		System_SetState(SYS_STATE_NEXTSUBMODE, paramArray[1]);
	}
	if (bFirst) {
		TM_BOOT_BEGIN("flow", "mode");
	}
	System_ChangeMode(mode_id);
	if (bFirst) {
		TM_BOOT_END("flow", "mode");
	}
	bFirst = FALSE;

	return NVTEVT_CONSUME;
}

INT32 System_OnSleepLevel(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	int sleep_lv;
	if (paramNum < 1) {
		return NVTEVT_CONSUME;
	}

	sleep_lv = paramArray[0];
	System_ChangeSleep(sleep_lv);

	return NVTEVT_CONSUME;
}

INT32 System_OnAppOpen(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
    #if(SENSOR_FUNC == ENABLE)
	UINT32 nSensor, uSensorMask, iSensorDisp;
    #endif
	DBG_IND("\r\n");

	//System_ChangeMode(mode); //open phase
	//
	//  1. UIModeXXX.c::ModeXXX_Open()
	//      Ux_SetActiveApp(&AppObj);
	//      Ux_SendEvent(0, NVTEVT_EXE_OPEN, 0);
	//  2. UIAppXXX_Exe.c::XXXExe_OnOpen()
	//      Ux_DefaultEvent(pCtrl,NVTEVT_EXE_OPEN,paramNum,paramArray);
	//  3. SysMain_Exe.c::System_OnAppOpen()
	//      Ux_SendEvent(0, NVTEVT_SENSOR_ATTACH, 0);
	//      Ux_SendEvent(0, NVTEVT_LENS_ATTACH, 0);
	//             wait device control finish
	//  4. UIModeXXX.c::ModeXXX_Open()
	//      Ux_OpenWindow();
	#if (DISPLAY_FUNC == ENABLE)
	DBG_IND("^M -display attach\r\n");
	Ux_SendEvent(0, NVTEVT_VIDEO_ATTACH, 0);
	#endif
    #if (SENSOR_FUNC == ENABLE)
	DBG_IND("^M -sensor attach\r\n");
	Ux_SendEvent(0, NVTEVT_SENSOR_ATTACH, 0);
	nSensor = ImageUnit_GetParam(ISF_VIN(0), ISF_CTRL, VDOIN_PARAM_SENSORCOUNT); //return 0/1/2/4
	uSensorMask = ImageUnit_GetParam(ISF_VIN(0), ISF_CTRL, VDOIN_PARAM_SENSORMASK);
	iSensorDisp = ImageUnit_GetParam(ISF_VIN(0), ISF_CTRL, VDOIN_PARAM_SENSORDISPLAY);
	DBG_DUMP(" -sensor count=%d, insert_mask=%04x, attach_mask=%04x, disp_mask=%04x\r\n", nSensor, System_GetConnectSensor(), uSensorMask, iSensorDisp);
	DBG_IND("^M -lens attach\r\n");
	Ux_SendEvent(0, NVTEVT_LENS_ATTACH, 0);
	DBG_DUMP(" -lens count=%d\r\n", 0);
    #endif

	return NVTEVT_CONSUME;
}

INT32 System_OnAppClose(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
	DBG_IND("\r\n");

	//System_ChangeMode(mode); //close phase
	//
	//  4. UIModeXXX.c::ModeXXX_Close()
	//      Ux_CloseWindow();
	//  3. UIModeXXX.c::ModeXXX_Close()
	//      Ux_SendEvent(0, NVTEVT_EXE_CLOSE, 0);
	//  2. UIAppXXX_Exe.c::XXXExe_OnClose()
	//      Ux_DefaultEvent(pCtrl,NVTEVT_EXE_CLOSE,paramNum,paramArray);
	//  1. SysMain_Exe.c::System_OnAppClose()
	//      Ux_SendEvent(0, NVTEVT_SENSOR_DETACH, 0);
	//      Ux_SendEvent(0, NVTEVT_LENS_DETACH, 0);
	Ux_SendEvent(0, NVTEVT_VIDEO_DETACH, 0);
	Ux_SendEvent(0, NVTEVT_SENSOR_DETACH, 0);
	Ux_SendEvent(0, NVTEVT_LENS_DETACH, 0);

	return NVTEVT_CONSUME;
}

void Timer_CB(UINT32 event, UINT32 param1, UINT32 param2)
{
	//DBG_DUMP("1S\r\n");
	Ux_PostEvent(NVTEVT_TIMER, 1, event);
}

///////////////////////////////////////////////////////////////////////////////
//Device flow event
INT32 System_OnVideoInsert(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnVideoRemove(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnVideoAttach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnVideoDetach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnAudioInsert(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnAudioRemove(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnAudioAttach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnAudioDetach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnAudioMode(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnAudioInput(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnAudioVol(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnStrgInsert(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnStrgRemove(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnStrgAttach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnStrgDetach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnUsbInsert(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnUsbRemove(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnUsbChargeCurrent(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnBattEmpty(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnBattChange(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnPwrChargeOK(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnPwrChargeSuspend(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnPwrChargeResume(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);

INT32 System_OnVideoDir(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnVideoMode(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);

INT32 System_OnSensorInsert(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnSensorRemove(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnSensorAttach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnSensorDetach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnSensorDisplay(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnLensAttach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
INT32 System_OnLensDetach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);

/*
INT32 System_OnDefAttach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
    //  PWR-KEY:
    //  NORMAL-KEY:
    //  STATUS-KEY:
    //  TOUCH:
    //  LED:
    //  BATTERY:
    return NVTEVT_CONSUME;
}

INT32 System_OnSensorAttach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
    //  SENSOR
    return NVTEVT_CONSUME;
}

INT32 System_OnLensAttach(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray)
{
    //  LENS
    return NVTEVT_CONSUME;
}
*/

EVENT_ENTRY SystemObjCmdMap[] = {
////////////////////////////////////////////////////////////

	//System flow event
	{NVTEVT_SYSTEM_BOOT,             System_OnBoot              },
	{NVTEVT_SYSTEM_SHUTDOWN,         System_OnShutdown          },
	{NVTEVT_SYSTEM_MODE,             System_OnMode              },
	{NVTEVT_SYSTEM_SLEEP,            System_OnSleepLevel        },
	//App common event
	{NVTEVT_EXE_OPEN,                System_OnAppOpen           },
	{NVTEVT_EXE_CLOSE,               System_OnAppClose          },

#if (DISPLAY_FUNC == ENABLE)
	//Video device event
	{NVTEVT_VIDEO_INSERT,            System_OnVideoInsert       },
	{NVTEVT_VIDEO_REMOVE,            System_OnVideoRemove       },
	{NVTEVT_VIDEO_ATTACH,            System_OnVideoAttach       },
	{NVTEVT_VIDEO_DETACH,            System_OnVideoDetach       },
	{NVTEVT_VIDEO_MODE,              System_OnVideoMode         },
	{NVTEVT_VIDEO_DIR,               System_OnVideoDir          },
#endif
#if (AUDIO_FUNC == ENABLE)
	//Audio device event
	{NVTEVT_AUDIO_INSERT,            System_OnAudioInsert       },
	{NVTEVT_AUDIO_REMOVE,            System_OnAudioRemove       },
	{NVTEVT_AUDIO_ATTACH,            System_OnAudioAttach       },
	{NVTEVT_AUDIO_DETACH,            System_OnAudioDetach       },
	{NVTEVT_AUDIO_INPUT,             System_OnAudioInput        },
	{NVTEVT_AUDIO_PLAY_VOL,          System_OnAudioVol          },
	{NVTEVT_AUDIO_MODE,              System_OnAudioMode         },
#endif
#if (FS_FUNC == ENABLE)
	//Storage device event
	{NVTEVT_STRG_INSERT,             System_OnStrgInsert        },
	{NVTEVT_STRG_REMOVE,             System_OnStrgRemove        },
	{NVTEVT_STRG_ATTACH,             System_OnStrgAttach        },
	{NVTEVT_STRG_DETACH,             System_OnStrgDetach        },
#endif
#if(USB_MODE==ENABLE)
	//Usb device event
	{NVTEVT_USB_INSERT,              System_OnUsbInsert         },
	{NVTEVT_USB_REMOVE,              System_OnUsbRemove         },
	{NVTEVT_USB_CHARGE_CURRENT,      System_OnUsbChargeCurrent  },
#endif
#if (PWR_FUNC == ENABLE)
	//power device event
	{NVTEVT_PWR_BATTEMPTY,           System_OnBattEmpty         },
	{NVTEVT_PWR_BATTCHANGE,          System_OnBattChange        },
	{NVTEVT_PWR_CHARGE_OK,           System_OnPwrChargeOK       },
	{NVTEVT_PWR_CHARGE_SUSPEND,      System_OnPwrChargeSuspend  },
	{NVTEVT_PWR_CHARGE_RESUME,       System_OnPwrChargeResume   },
#endif
#if(UI_SENSOR==ENABLE)
	//sensor device event
	{NVTEVT_SENSOR_INSERT,           System_OnSensorInsert      },
	{NVTEVT_SENSOR_REMOVE,           System_OnSensorRemove      },
	{NVTEVT_SENSOR_ATTACH,           System_OnSensorAttach      },
	{NVTEVT_SENSOR_DETACH,           System_OnSensorDetach      },
	{NVTEVT_SENSOR_DISPLAY,          System_OnSensorDisplay     },
#endif
#if (LENS_FUNCTION == ENABLE)
	{NVTEVT_LENS_ATTACH,             System_OnLensAttach        },
	{NVTEVT_LENS_DETACH,             System_OnLensDetach        },
#endif

	//Other device event
	//{NVTEVT_DEFAULT_ATTACH,        System_OnDefAttach         },
	{NVTEVT_ACC_SHUTDOWN,            System_OnACCShutdown       }, //add for ACC power off
	{NVTEVT_ACC_POWERON,             System_OnACCPowerOn        }, //add for ACC power on

	{NVTEVT_NULL,                    0},  //End of Command Map
};

CREATE_APP(SystemObj, 0)

