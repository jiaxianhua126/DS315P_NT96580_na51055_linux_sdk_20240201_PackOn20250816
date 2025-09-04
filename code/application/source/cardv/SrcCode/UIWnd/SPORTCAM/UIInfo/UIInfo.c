////////////////////////////////////////////////////////////////////////////////
#include "PrjInc.h"
#include "UICfgDefault.h"
#include "GxPower.h"
#include "PowerDef.h"
#include "PStore.h"
#include "UIApp/Network/UIAppNetwork.h"
#include <libfdt.h>
#include <rtosfdt.h>
#include <compiler.h>
#if (USE_DCF == ENABLE)
#include "DCF.h"
#endif

///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          UIInfo
#define __DBGLVL__          2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>

#if defined(_EMBMEM_NAND_) || defined(_EMBMEM_SPI_NAND_)
	#define MAKE_FDT_PARTITION_PATH(x) "/nand/partition_"#x
#elif defined(_EMBMEM_SPI_NOR_)
	#define MAKE_FDT_PARTITION_PATH(x) "/nor/partition_"#x
#elif defined(_EMBMEM_EMMC_)
	#define MAKE_FDT_PARTITION_PATH(x) "/mmc@f0510000/partition_"#x
#endif

#define PARTITION_PATH_USR1  MAKE_FDT_PARTITION_PATH(usr1) //using for sysparameter
#define PARTITION_PATH_USR2  MAKE_FDT_PARTITION_PATH(usr2) //using for sysparameter restore	

#define MAKE_FDT_PARTITION_PATH_HELPER(X)	MAKE_FDT_PARTITION_PATH(X)
#define PARTITION_PATH_SYS					MAKE_FDT_PARTITION_PATH_HELPER(HUNTING_CAMERA_SYS_PARTITION_NAME)
#define	XSTR(X)								#X
#define STR(X)								XSTR(X)

#define SYSINFO_NAND    ENABLE //DISABLE

//---------------------UIInfo Global Variables -----------------------------
UIMenuStoreInfo  currentInfo = {0}; //#NT#Init the array to zero.
UIMenuStoreInfo  origInfo = {0}; /* backup */

BOOL bSysReady = 0;
BOOL bAutoSystemReset = FALSE;
//static BOOL bAutoReset = FALSE;

//---------------------UIInfo Prototype Declaration  -----------------------
//---------------------UIInfo Public API  ----------------------------------
//---------------------UIInfo Private API ----------------------------------
void SysSetFixedFlagSysInit(void);

//------------------------------------------------------------
#if (PST_FUNC == DISABLE)
int UIInfo_GetStrgPartitionInfo(unsigned long long *pPartOfs, unsigned long long *pPartSize, const char* fdt_path)
{
	unsigned char *p_fdt = (unsigned char *)fdt_get_base();

	if (p_fdt == NULL) {
		DBG_ERR("p_fdt is NULL.\n");
		return -1;
	}

	int len = 0;
	int nodeoffset = 0;
	const void *nodep = NULL;	/* property node pointer */
	unsigned long long partition_ofs = 0, partition_size = 0;

	nodeoffset = fdt_path_offset(p_fdt, fdt_path);
	if (nodeoffset < 0) {
		DBG_ERR("failed to offset for  %s = %d \n", fdt_path, nodeoffset);
		return -1;
	} else {
		DBG_DUMP("offset for  %s = %d \n", fdt_path, nodeoffset);
	}
	nodep = fdt_getprop(p_fdt, nodeoffset, "reg", &len);
	if (len == 0 || nodep == NULL) {
		DBG_ERR("failed to access reg.\n");
		return -1;
	} else {
		unsigned long long *p_data = (unsigned long long *)nodep;
		partition_ofs = be64_to_cpu(p_data[0]);
		partition_size = be64_to_cpu(p_data[1]);
		DBG_DUMP("partition reg = <0x%llX 0x%llX> \n", partition_ofs, partition_size);

		*pPartOfs = partition_ofs;
		*pPartSize = partition_size;
	}

	return 0;
}

#if defined(_EMBMEM_SPI_NAND_) || defined(_EMBMEM_SPI_NOR_)
static int find_mtd_device(const char* partition_name, char* result_buf, const UINT32 result_buf_size)
{
	char cmd[128] = {'\0'};
	char rst_file[] = "/tmp/mtd_rst";
	int ret = 0;

	if(!result_buf){
		DBG_ERR("result buffer can't be null!\n");
		return -1;
	}

	/* ************************************************************
	 * 1. cat /proc/mtd info (nvt-storage-partition.dtsi)
	 * 2. escape double quotes with \"(\\\" in IDE) for grep cmd
	 * 3. substring of matched mtdX
	 * 4. output /dev/mtdX
	 * ************************************************************/
	sprintf(cmd, "cat /proc/mtd | grep \\\"%s\\\" | grep -o 'mtd[0-9 ]*' > %s", partition_name, rst_file);
	ret = system(cmd);
	if(ret){
		DBG_ERR("find mtd device %s failed!(ret = %d)\n", partition_name, ret);
	}
	else{
		FILE *rst_fp = NULL;
		size_t read_size;
		char tmp[128] = {'\0'};

		rst_fp = fopen(rst_file, "r");
		if(rst_fp){
			read_size = fread(tmp, 1, result_buf_size, rst_fp);
			if(read_size <= strlen("mtd") || !strstr(tmp, "mtd")){
				ret = -1;
			}
			else{
				/* remove newline */
				if(tmp[strlen(tmp) - 1] == 0xA){
					tmp[strlen(tmp) - 1] = '\0';
				}

				snprintf(result_buf, result_buf_size, "/dev/%s", tmp);
			}

			DBG_IND("RESULT = %s\n", result_buf);
			fclose(rst_fp);
		}
		else{
			ret = -1;
		}
	}

	if(ret){
		DBG_ERR("find mtd device %s failed!(ret = %d)\n", partition_name, ret);
	}

	return ret;
}


static int find_sys_mtd_device(char* result_buf, const UINT32 result_buf_size)
{
	static char* rst = NULL;
	int ret = 0;
	const char partition_name[] = STR(HUNTING_CAMERA_SYS_PARTITION_NAME);

	/* no need to find twice if partition is already found */
	if(!rst){
		ret = find_mtd_device(partition_name, result_buf, result_buf_size);
		if(ret == 0){
			rst = strdup(result_buf);
		}
	}
	else{
		size_t sz = strlen(rst) + 1;
		if(result_buf_size < sz){
			DBG_ERR("result_buf_size can't less than %lu!\n", sz);
			ret = -1;
		}
		else{
			strcpy(result_buf, rst);
			ret = 0;
		}
	}

	if(ret){
		DBG_ERR("mtd device of partition %s not found!\n", partition_name);
	}

	return ret;
}
#endif

#endif


void Load_SysInfo(void)
{
	/*
	    DBG_IND("Read SYSINFO\r\n");
	#if (SYSINFO_NAND==ENABLE)
	    PStore_ReadReServedArea((UINT8*)&sysInfo,sizeof(UISysInfo));
	#else
	    //set to default value
	    sysInfo.ubBeepPowerIndex = BEEP_TONE_1;
	    sysInfo.ubBeepVolumnIndex = BEEP_VOL_2;
	    sysInfo.ubWallpaperStartupIndex = WALLPAPER_STARTUP_GE;
	    sysInfo.uhInfoSize = sizeof(sysInfo);
	#endif
	*/
}

void Save_SysInfo(void)
{
	/*
	    DBG_IND("Write SYSINFO\r\n");
	#if (SYSINFO_NAND==ENABLE)
	    PStore_WriteReServedArea((UINT8*)&sysInfo,sizeof(UISysInfo));
	#endif
	*/
}

//-----------------------------------------------------------------------------
// GPSSignal Status
//-----------------------------------------------------------------------------
extern INT8 uigpsstatus;
INT8 GetGPSSignalStatus(void)
{
    INT8 gpsstatus;
    //debug_err(("!!!uigpsstatus=%d\n\r",uigpsstatus));
    switch (uigpsstatus) {
    case GPSSignal_UNFINDABLE:
        gpsstatus = 0;
        break;
    case GPSSignal_FINDABLE:
        gpsstatus = 1;
        break;
    default:
        gpsstatus = -1;
        break;
    }
    return gpsstatus;
}

void UI_ResetSSIDPASSPHRASE(void)
{
    memset(currentInfo.strSSID, '\0', NVT_WSC_MAX_SSID_LEN);
    memset(currentInfo.strPASSPHRASE, '\0', NVT_MAX_WEP_KEY_LEN);
	//5G
    memset(currentInfo.strSSID_5G, '\0', NVT_WSC_MAX_SSID_LEN);
    strcpy(currentInfo.strPASSPHRASE,UINet_GetDefaultAPPASSPHRASE());
}

extern char CarNo_Buf[13];
extern char Customize_Buf[13];
BOOL g_CarNoErr = FALSE;

char gPrjCarNo[32] = {0};
char gPrjCustomize[32] = {0};
char gPrjHdrTime[32] = {0};
static UINT32 gWifi_Hdr_sHour = 0;
static UINT32  gWifi_Hdr_sMin = 0;
static UINT32 gWifi_Hdr_eHour = 0;
static UINT32  gWifi_Hdr_eMin = 0;

char* Prj_GetCarNoString(void)
{
    memcpy(&gPrjCarNo, &CarNo_Buf, sizeof(char)*13);
    return gPrjCarNo;
}

char* Prj_GetCustomizeString(void)
{
    memcpy(&gPrjCustomize, &Customize_Buf, sizeof(char)*13);
    return gPrjCustomize;
}

char *Prj_GetHdrTimeString(void)
{

    gWifi_Hdr_sHour = SysGetFlag(FL_TIME_STOP)/100;
    gWifi_Hdr_sMin	= SysGetFlag(FL_TIME_STOP)%100;
    gWifi_Hdr_eHour  = SysGetFlag(FL_TIME_START)/100;
    gWifi_Hdr_eMin  = SysGetFlag(FL_TIME_START)%100;	
    sprintf(gPrjHdrTime,"%02d:%02d-%02d:%02d",gWifi_Hdr_sHour,gWifi_Hdr_sMin,gWifi_Hdr_eHour,gWifi_Hdr_eMin);
    return gPrjHdrTime;
}

#define CARNO_BACKUP_FILE_NAME  "A:\\CarNo_Backup.txt"
static char g_scCharTmpBuffer[30] = {0};
UINT32 UI_WriteCarNoToFile(void)
{
    FST_FILE  pFileHdl = NULL;
    UINT32 ilen = 0;//,pos

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
        return 0;
    }

    pFileHdl = FileSys_OpenFile(CARNO_BACKUP_FILE_NAME, FST_OPEN_ALWAYS|FST_OPEN_WRITE);

    if (pFileHdl) {
        memset(&g_scCharTmpBuffer, 0, 30);

        sprintf((char*)g_scCharTmpBuffer, "%s\r\n", CarNo_Buf);
        ilen = strlen(g_scCharTmpBuffer);

        // 1. append file
        //FileSys_SeekFile(pFileHdl, 0 , FST_SEEK_END);
        //pos = FileSys_TellFile(pFileHdl);
        FileSys_WriteFile(pFileHdl, (UINT8*)g_scCharTmpBuffer, &ilen, 0, NULL);
        FileSys_CloseFile(pFileHdl);
        FileSys_SetAttrib(CARNO_BACKUP_FILE_NAME, FST_ATTRIB_HIDDEN, TRUE);
    }
    return 0;
}

//------------------------------------------------------------
#define PS_SYS_PARAM            "SYSP"
#define BLOCK_UIINFO    0

CHAR previewEVStr[EV_SETTING_MAX][5] = {
	//"-2.0",
	//"-1.7",
	//"-1.3",
	"-1.0",
	"-0.7",
	"-0.3",
	"+0.0",
	"+0.3",
	"+0.7",
	"+1.0",
	//"+1.3",
	//"+1.7",
	//"+2.0"
};

void UI_SetInitVolume(UINT32 volumeIndex)
{
	#if (AUDIO_FUNC == ENABLE)
	const static UINT32 volume_gain[BEEP_VOL_SETTING_MAX] =
	{0, 36, 60, 100};

	if (volumeIndex >= BEEP_VOL_SETTING_MAX) {
		volumeIndex = BEEP_VOL_2;    //set to default
	}

	GxSound_SetVolume(volume_gain[volumeIndex]);
	#endif
}

void UI_SetFileDBFileID(void)
{
#if 0//USE_FILEDB

    struct tm Curr_DateTime;
    Curr_DateTime = HwClock_GetTime(TIME_ID_CURRENT);

	if (((UINT32)Curr_DateTime.tm_year  == currentInfo.cbYear) && ((UINT32)Curr_DateTime.tm_mon== currentInfo.cbMonth) && ((UINT32)Curr_DateTime.tm_mday== currentInfo.cbDay)) {
		NH_FileDB_SetFileID(currentInfo.cbFileID);
	}
#endif
}

void UI_SaveRTCDate(void)
{
#if 0//USE_FILEDB
	FILEDB_HANDLE fileDbHandle = 0;
	FILEDB_FILE_ATTR *pFileAttr;
	RTC_DATE    Date;
	CHAR datetime[10];
	UINT32 uiFileID;

	pFileAttr = FileDB_CurrFile(fileDbHandle);
	if (pFileAttr != NULL) {
		strncpy(datetime, pFileAttr->filename, 4);
		datetime[4] = '\0';
		Date.s.year = atoi(datetime);

		strncpy(datetime, pFileAttr->filename + 5, 2);
		datetime[2] = '\0';
		Date.s.month = atoi(datetime);

		strncpy(datetime, pFileAttr->filename + 7, 2);
		datetime[2] = '\0';
		Date.s.day = atoi(datetime);

		strncpy(datetime, pFileAttr->filename + 17, 3);
		datetime[3] = '\0';
		uiFileID = atoi(datetime);

		currentInfo.cbYear = Date.s.year;
		currentInfo.cbMonth = Date.s.month;
		currentInfo.cbDay = Date.s.day;
		currentInfo.cbFileID = uiFileID;
	}
#endif
}

void Load_MenuInfo(void)
{
#if (PST_FUNC == ENABLE)
	#if 0
	MODELEXT_HEADER *head = NULL;
	BININFO *pBinInfo = (BININFO *)Dx_GetModelExtCfg(MODELEXT_TYPE_BIN_INFO, &head);
	PPSTORE_SECTION_HANDLE  pSection;
	UINT32  result;
	UINT32  uiFWUpdate = 0;
	UINT32  uiTmpBoot = 0;
	DBG_IND("Read UIINFO\r\n");

	if (pBinInfo == NULL) {
		DBG_ERR("pBinInfo is NULL\r\n");
		return;
	}

	uiFWUpdate = (pBinInfo->ld.LdCtrl2 & LDCF_UPDATE_FW);
	uiTmpBoot = (pBinInfo->ld.LdCtrl2 & LDCF_BOOT_CARD);

	// Read system info from PStore
	if (uiTmpBoot) {
		SysResetFlag();
		debug_msg("Boot from temp file, use default flags\r\n");
	} else if ((pSection = PStore_OpenSection(PS_SYS_PARAM, PS_RDWR)) != E_PS_SECHDLER) {
		//#NT#2016/06/23#Niven Cho -begin
		//#NT#porting KS's suggestion that PStore reset mechanism
		UINT32 uiPsFreeSpace = PStore_GetInfo(PS_INFO_FREE_SPACE);
		result = PStore_ReadSection((UINT8 *)&currentInfo, 0, sizeof(UIMenuStoreInfo), pSection);
		if ((result != E_PS_OK || currentInfo.uhInfoSize != sizeof(currentInfo) || uiFWUpdate) &&
			uiPsFreeSpace) {
			debug_msg("PStore reset info.\r\n");
			memset(&currentInfo, 0, sizeof(currentInfo));
			currentInfo.uhInfoSize = sizeof(UIMenuStoreInfo);
			SysResetFlag();
			PStore_WriteSection((UINT8 *)&currentInfo, 0, sizeof(UIMenuStoreInfo), pSection);
			PStore_CloseSection(pSection);
		} else if ((result != E_PS_OK || uiFWUpdate) && (currentInfo.uhInfoSize == sizeof(currentInfo)) &&
				   (uiPsFreeSpace == 0)) {
			//if current size is the same with previous, use PS_UPDATE instead
			//of PS_RDWR to prevent that PStore is no free space
			debug_msg("PStore reset info for uiPsFreeSpace=0.\r\n");
			PStore_CloseSection(pSection);
			memset(&currentInfo, 0, sizeof(currentInfo));
			currentInfo.uhInfoSize = sizeof(UIMenuStoreInfo);
			SysResetFlag();
			if ((pSection = PStore_OpenSection(PS_SYS_PARAM, PS_UPDATE)) != E_PS_SECHDLER) {
				PStore_WriteSection((UINT8 *)&currentInfo, 0, sizeof(UIMenuStoreInfo), pSection);
				PStore_CloseSection(pSection);
			} else {
				DBG_ERR("Update sys param fail in Load_MenuInfo\r\n");
			}
		} else {
			PStore_CloseSection(pSection);
		}
		//#NT#2016/06/23#Niven Cho -end
		//#NT#2017/03/02#Niven Cho -begin
		//#NT#EMMC_AS_PSTORE, reduce PStore_CloseSection
		//PStore_CloseSection(pSection);
		//#NT#2017/03/02#Niven Cho -end
		bSysReady = 1;
	} else {
		SysResetFlag();
		DBG_ERR("PStore Read sys param fail, use default flags\r\n");
	}

	DBG_IND("Read UIRES\r\n");

	#else

	PPSTORE_SECTION_HANDLE  pSection;
	UINT32  result;
	UINT32  uiFWUpdate = 0;
	UINT32  uiTmpBoot = 0;
    UINT32  RWOperation = PS_RDWR;

#if 1 //cmdline for ota
    FILE *fp = NULL;
    UINT32 u32ize = 0;
    char *pStrSrc = NULL;
    char *pStrOtsOk = "ota_flag=0x1";

    SysMain_system("cat /proc/cmdline > /tmp/ota.txt");
    fp = fopen("/tmp/ota.txt","r");
    if (fp != NULL)  {
        fseek(fp, 0, SEEK_END);
        u32ize = ftell(fp); // take file size
        fseek(fp, 0, SEEK_SET); // move to position zero
        pStrSrc = (char *)malloc(u32ize*sizeof(char));

        if (pStrSrc) {
            fread(pStrSrc, 1, u32ize, fp);
			if (strstr(pStrSrc, pStrOtsOk) != 0) {
                uiFWUpdate = 1;
                RWOperation = PS_RDWR | PS_CREATE;
                printf("%s: ota upgrade success\r\n", __func__);
            } else {
				printf("%s: ota upgrade failed\r\n", __func__);
			}
            free(pStrSrc);
        }

        fclose(fp);
        fp  = NULL;
        pStrSrc = NULL;
        u32ize = 0;
    }
#endif

	DBGH(uiFWUpdate);
	DBGH(uiTmpBoot);

	DBG_IND("Read UIINFO\r\n");

	// Read system info from PStore
	if (uiTmpBoot) {
		SysResetFlag();
		DBG_DUMP("Boot from temp file, use default flags\r\n");
	}else if ((pSection = PStore_OpenSection(PS_SYS_PARAM, RWOperation)) != E_PS_SECHDLER) {
		//#NT#2016/06/23#Niven Cho -begin
		//#NT#porting KS's suggestion that PStore reset mechanism
		UINT32 uiPsFreeSpace = PStore_GetInfo(PS_INFO_FREE_SPACE);
		result = PStore_ReadSection((UINT8 *)&currentInfo, 0, sizeof(UIMenuStoreInfo), pSection);
		if ((result != E_PS_OK || currentInfo.uhInfoSize != sizeof(currentInfo) || uiFWUpdate) &&
			uiPsFreeSpace) {
			DBG_DUMP("PStore reset info.\r\n");
			memset(&currentInfo, 0, sizeof(currentInfo));
			currentInfo.uhInfoSize = sizeof(UIMenuStoreInfo);
			SysResetFlag();
			PStore_WriteSection((UINT8 *)&currentInfo, 0, sizeof(UIMenuStoreInfo), pSection);
			PStore_CloseSection(pSection);
		} else if ((result != E_PS_OK || uiFWUpdate) && (currentInfo.uhInfoSize == sizeof(currentInfo)) &&
				   (uiPsFreeSpace == 0)) {
			//if current size is the same with previous, use PS_UPDATE instead
			//of PS_RDWR to prevent that PStore is no free space
			DBG_DUMP("PStore reset info for uiPsFreeSpace=0.\r\n");
			PStore_CloseSection(pSection);
			memset(&currentInfo, 0, sizeof(currentInfo));
			currentInfo.uhInfoSize = sizeof(UIMenuStoreInfo);
			SysResetFlag();
			if ((pSection = PStore_OpenSection(PS_SYS_PARAM, PS_UPDATE)) != E_PS_SECHDLER) {
				PStore_WriteSection((UINT8 *)&currentInfo, 0, sizeof(UIMenuStoreInfo), pSection);
				PStore_CloseSection(pSection);
			} else {
				DBG_ERR("Update sys param fail in Load_MenuInfo\r\n");
			}
		} else {
			PStore_CloseSection(pSection);
		}

#if 1
		if (((currentInfo.strCarNo[0] >= 48)&&(currentInfo.strCarNo[0] <= 57))
            || ((currentInfo.strCarNo[0] >= 65)&&(currentInfo.strCarNo[0] <= 90))
            || (currentInfo.strCarNo[0] == 32)
            || (currentInfo.strCarNo[0] == 45)
            || (currentInfo.strCarNo[0] == 46))
        {
            g_CarNoErr = FALSE;
            memcpy(&CarNo_Buf, &currentInfo.strCarNo, sizeof(char)*13);
        }
        else
        {
            g_CarNoErr = TRUE;
            strncpy(currentInfo.strCarNo, "           ", sizeof(char)*13);
        }

        if (((currentInfo.strCustomize[0] >= 48)&&(currentInfo.strCustomize[0] <= 57))
            || ((currentInfo.strCustomize[0] >= 65)&&(currentInfo.strCustomize[0] <= 90))
            || (currentInfo.strCustomize[0] == 32)
            || (currentInfo.strCustomize[0] == 45)
            || (currentInfo.strCustomize[0] == 46))
        {
            memcpy(&Customize_Buf, &currentInfo.strCustomize, sizeof(char)*13);
        }
        else
        {
            strncpy(currentInfo.strCustomize, "           ", sizeof(char)*13);
        }
#endif

		//#NT#2016/06/23#Niven Cho -end
		//#NT#2017/03/02#Niven Cho -begin
		//#NT#EMMC_AS_PSTORE, reduce PStore_CloseSection
		//PStore_CloseSection(pSection);
		//#NT#2017/03/02#Niven Cho -end
		bSysReady = 1;
	} else {
		SysResetFlag();
		DBG_ERR("PStore Read sys param fail, use default flags\r\n");
	}

	DBG_IND("Read UIRES\r\n");

	#endif
	
#else //for #if (PST_FUNC == ENABLE)
#if defined(_EMBMEM_EMMC_)
	unsigned long long partition_ofs= 0, partition_size = 0;
	int ret = -1;
	UINT32 sectorCnt = 0;
    FILE *fd_mmc = NULL;
	INT32 rw_len = 0;
	void *pTempbuf = NULL;
    
	ret = UIInfo_GetStrgPartitionInfo(&partition_ofs, &partition_size, PARTITION_PATH_USR1);
    if ((ret == 0) && (sizeof(currentInfo) < partition_size)) {
        if ((sizeof(currentInfo)/_EMBMEM_BLK_SIZE_) == 0) {
			sectorCnt = 1;
        } else if (((sizeof(currentInfo)/_EMBMEM_BLK_SIZE_) > 0) && ((sizeof(currentInfo)%_EMBMEM_BLK_SIZE_) != 0)) {
        	sectorCnt = sizeof(currentInfo)/_EMBMEM_BLK_SIZE_ + 1;
        } else if (((sizeof(currentInfo)/_EMBMEM_BLK_SIZE_) > 0) && ((sizeof(currentInfo)%_EMBMEM_BLK_SIZE_) == 0)) {
        	sectorCnt = sizeof(currentInfo)/_EMBMEM_BLK_SIZE_;
        }
		
		if ((fd_mmc = fopen("/dev/mmcblk2p14", "rb")) == NULL) { ///dev/mmcblk2p14 ==> partition_usr1 ; cat /proc/nvt_info/emmc
			DBG_ERR("/dev/mmcblk2p14 fail !!\r\n");
			SysResetFlag();
			return;
		} else {
		    pTempbuf = (void *)malloc(sectorCnt*_EMBMEM_BLK_SIZE_);

 			if (!pTempbuf) {
				DBG_ERR("allocate pTempbuf fail !!\r\n");
				SysResetFlag();	
 		    } else {			
				rw_len = (INT32)fread(pTempbuf, 1, sizeof(currentInfo), fd_mmc);
				if (rw_len != sizeof(currentInfo)) {
					DBG_ERR("read size %d < %ld\r\n", rw_len, sizeof(currentInfo));
					SysResetFlag();	
				} else {
					memcpy(&currentInfo, pTempbuf, sizeof(currentInfo));
				}
				free(pTempbuf);
				pTempbuf = NULL;
 		    }
			
			fclose(fd_mmc);
			SysCheckFlag();
		}				
    }
   	
#elif defined(_EMBMEM_SPI_NAND_)

	unsigned long long partition_ofs= 0, partition_size = 0;
	int ret = -1;
    FILE *nandump_fp = NULL;
	INT32 rw_len = 0;
	UINT32 sectorCnt = 0;
	void *tmpInfo = NULL;
	size_t read_size;
	char cmd[128] = {0};
 	char filename[128] = {0};

	sectorCnt = (sizeof(currentInfo) / _EMBMEM_BLK_SIZE_) + (sizeof(currentInfo) % _EMBMEM_BLK_SIZE_)? 1 : 0;

	ret = UIInfo_GetStrgPartitionInfo(&partition_ofs, &partition_size, PARTITION_PATH_SYS);
    if ((ret == 0) && (sizeof(currentInfo) < partition_size)) {

    	char sys_mtd_dev_path[128] = {'\0'};
    	ret = find_sys_mtd_device(sys_mtd_dev_path, sizeof(sys_mtd_dev_path));
    	if(ret){
    		goto EXIT;
    	}

		read_size = sectorCnt * _EMBMEM_BLK_SIZE_;
		tmpInfo = (void *)malloc(read_size);
		if(!tmpInfo){
			DBG_ERR("allocate tmpInfo failed!\n");
			ret = -1;
			goto EXIT;
		}

 		memset(tmpInfo, 0x0 , read_size);
 		sprintf(filename, "/tmp/nanddump.out");
		sprintf(cmd, "nanddump --bb skipbad -l %lu -f %s %s",
				read_size,
				filename,
				sys_mtd_dev_path
		);

 		DBG_DUMP("%s\n", cmd);
 		ret = system(cmd);
 		if(ret){
 			DBG_ERR("nanddump failed!\n");
 			goto EXIT;
 		}

 		nandump_fp = fopen(filename, "rb");
 		if(!nandump_fp){
 			DBG_ERR("open %s failed!\n", filename);
 			ret = -1;
 			goto EXIT;
 		}

 		rw_len = fread(tmpInfo, 1, read_size, nandump_fp);
 	 	if (rw_len != (INT32)(read_size)) {
 	 		DBG_ERR("fread size not matched(%d / %ld)\r\n", rw_len, read_size);
 	 		ret = -1;
 	 		goto EXIT;
 	 	}

 	 	if(((UIMenuStoreInfo*)tmpInfo)->uhInfoSize == sizeof(currentInfo)){
 	 		memcpy(&currentInfo, tmpInfo, sizeof(currentInfo));
 	 	}
 	 	else{
 	 		DBG_WRN("menu info size loaded from flash seems incorrect, reset menu info\n");
 	 		SysResetFlag();
 	 		currentInfo.uhInfoSize = sizeof(currentInfo);
 	 	}
    }

EXIT:

	if(ret){
		SysResetFlag();
		currentInfo.uhInfoSize = sizeof(currentInfo);
	}
	SysCheckFlag();
	origInfo = currentInfo;

	if(nandump_fp){
		fclose(nandump_fp);
		nandump_fp = NULL;
	}

	if(tmpInfo){
		free(tmpInfo);
		tmpInfo = NULL;
	}
#elif defined(_EMBMEM_SPI_NOR_)

	unsigned long long partition_ofs= 0, partition_size = 0;
	int ret = -1;
    FILE *sys_mtd_fp = NULL;
	INT32 rw_len = 0;
	UINT32 sectorCnt = 0;
	void *tmpInfo = NULL;
	size_t read_size;

	sectorCnt = (sizeof(currentInfo) / _EMBMEM_BLK_SIZE_) + (sizeof(currentInfo) % _EMBMEM_BLK_SIZE_)? 1 : 0;

	ret = UIInfo_GetStrgPartitionInfo(&partition_ofs, &partition_size, PARTITION_PATH_SYS);
    if ((ret == 0) && (sizeof(currentInfo) < partition_size)) {

    	char sys_mtd_dev_path[128] = {'\0'};
    	ret = find_sys_mtd_device(sys_mtd_dev_path, sizeof(sys_mtd_dev_path));
    	if(ret){
    		goto EXIT;
    	}

    	sys_mtd_fp = fopen(sys_mtd_dev_path, "rb");
		if (sys_mtd_fp == NULL) {
			DBG_ERR("open %s failed!\n", sys_mtd_dev_path);
			ret = -1;
			goto EXIT;
		}

		read_size = sectorCnt * _EMBMEM_BLK_SIZE_;
		tmpInfo = (void *)malloc(read_size);
		if(!tmpInfo){
			DBG_ERR("allocate tmpInfo failed!\n");
			ret = -1;
			goto EXIT;
		}

 		memset(tmpInfo, 0x0 , read_size);
 		rw_len = fread(tmpInfo, 1, read_size, sys_mtd_fp);
 	 	if (rw_len != (INT32)(read_size)) {
 	 		DBG_ERR("fread size not matched(%d / %ld)\r\n", rw_len, read_size);
 	 		ret = -1;
 	 		goto EXIT;
 	 	}

 	 	if(((UIMenuStoreInfo*)tmpInfo)->uhInfoSize == sizeof(currentInfo)){
 	 		memcpy(&currentInfo, tmpInfo, sizeof(currentInfo));
 	 	}
 	 	else{
 	 		DBG_WRN("menu info size loaded from flash seems incorrect(old:%lu new:%lu), reset menu info\n",
 	 				((UIMenuStoreInfo*)tmpInfo)->uhInfoSize,
					sizeof(currentInfo)
 	 		);
 	 		SysResetFlag();
 	 		currentInfo.uhInfoSize = sizeof(currentInfo);
 	 	}

 	 	UINT32 sum = MemCheck_CalcCheckSum16Bit((UINT32)tmpInfo, sizeof(currentInfo));
 	 	DBG_DUMP("**************size = %lx / mov size = %u / sum = %lx **************\n",
 	 			sizeof(currentInfo),
				//((UIMenuStoreInfo*)tmpInfo)->UIParameter[FL_MOVIE_SIZE],
				((UIMenuStoreInfo*)tmpInfo)->UIParameter[CamMode],
				sum);
    }

EXIT:

	if(ret){
		SysResetFlag();
		currentInfo.uhInfoSize = sizeof(currentInfo);
	}
	SysCheckFlag();
	origInfo = currentInfo;

	if(sys_mtd_fp){
		fclose(sys_mtd_fp);
		sys_mtd_fp = NULL;
	}

	if(tmpInfo){
		free(tmpInfo);
		tmpInfo = NULL;
	}

#else
	SysResetFlag();
#endif

#endif  //for #if (PST_FUNC == ENABLE)
}

void Load_LangString(void)
{
	//load language
#if(_LANG_STORE_ == _PSTORE_)
	UIRes_InitReadLang(currentInfo.ubLanguageIndex);
#endif
}

void Save_MenuInfo(void)
{
#if (PST_FUNC == ENABLE)
	#if 0
	MODELEXT_HEADER *head = NULL;
	BININFO *pBinInfo = (BININFO *)Dx_GetModelExtCfg(MODELEXT_TYPE_BIN_INFO, &head);
	PPSTORE_SECTION_HANDLE  pSection;
	UINT32 error = 0;
	UINT32  uiTmpBoot;

	if (pBinInfo == NULL) {
		DBG_ERR("pBinInfo is NULL\r\n");
		return;
	}
	uiTmpBoot = (pBinInfo->ld.LdCtrl2 & LDCF_BOOT_CARD);
	// Read system info from PStore
	if (uiTmpBoot) {
		SysResetFlag();
		debug_msg("Boot from temp file, skip Save_MenuInfo\r\n");
		return;
	}

	DBG_IND("Write UIINFO\r\n");
	//#NT#2013/3/15#Philex Lin - begin
	/*--- General ---*/
	strncpy(currentInfo.strSoftwareVer, Prj_GetVersionString(), (VER_STR_MAX - 1));
	currentInfo.strSoftwareVer[strlen(currentInfo.strSoftwareVer)] = '\0';

    strncpy(currentInfo.strCarNo, Prj_GetCarNoString(), (VER_STR_MAX - 1));
    currentInfo.strCarNo[strlen(currentInfo.strCarNo)] = '\0';
    strncpy(currentInfo.strCustomize, Prj_GetCustomizeString(), (VER_STR_MAX - 1));
    currentInfo.strCustomize[strlen(currentInfo.strCustomize)] = '\0';
	currentInfo.uhInfoSize = sizeof(UIMenuStoreInfo);
	//#NT#2013/3/15#Philex Lin - end

	//Using PStore to read / sys param
	//#NT#2016/06/23#Niven Cho -begin
	//#NT#porting KS's suggestion that PStore reset mechanism
	UINT32 uiPsFreeSpace = PStore_GetInfo(PS_INFO_FREE_SPACE);
	if (uiPsFreeSpace == 0) {
		if ((pSection = PStore_OpenSection(PS_SYS_PARAM, PS_UPDATE)) != E_PS_SECHDLER) {
			PStore_WriteSection((UINT8 *)&currentInfo, 0, sizeof(UIMenuStoreInfo), pSection);
			PStore_CloseSection(pSection);
		} else {
			DBG_ERR("Update sys param fail\r\n");
		}
	} else {
		if ((pSection = PStore_OpenSection(PS_SYS_PARAM, PS_RDWR | PS_CREATE)) != E_PS_SECHDLER) {
			PStore_WriteSection((UINT8 *)&currentInfo, 0, sizeof(UIMenuStoreInfo), pSection);
			PStore_CloseSection(pSection);
		} else {
			DBG_ERR("Write sys param fail\r\n");
		}
	}
	//#NT#2016/06/23#Niven Cho -end

	if (PStore_CheckSection(PS_SYS_PARAM, &error) != E_PS_OK) {
		DBG_ERR("PStore_CheckSection\r\n");
	}

	if (error != E_PS_OK) {
		DBG_ERR("PStore error msg :%x\r\n", error);
		{
			UINT32 BufSize = 0x1800000;
			UINT8 *pBuf = (UINT8 *)SxCmd_GetTempMem(BufSize);

			if (!pBuf) {
				DBG_ERR("pBuf is NULL\r\n");
				return;
			}
			//open file system for save file
			//Dep_Fs_Init(TRUE,TRUE);
			PStore_Dump(pBuf, BufSize);
            SxCmd_RelTempMem((UINT32)pBuf);
		}
		Ux_DumpEvents();
//        while (1);
	}

	#else

	PPSTORE_SECTION_HANDLE	pSection;
	UINT32 error = 0;
	UINT32  uiTmpBoot = 0;

	uiTmpBoot= 0;//(p_shm->boot.LdCtrl2 & LDCF_BOOT_CARD);
	DBGH(uiTmpBoot);
	// Read system info from PStore
	if (uiTmpBoot) {
		SysResetFlag();
		DBG_DUMP("Boot from temp file, skip Save_MenuInfo\r\n");
		return;
	}
	DBG_IND("Write UIINFO\r\n");

	//#NT#2013/3/15#Philex Lin - begin
	/*--- General ---*/
	strncpy(currentInfo.strSoftwareVer, Prj_GetVersionString(), (VER_STR_MAX - 1));
	currentInfo.strSoftwareVer[strlen(currentInfo.strSoftwareVer)] = '\0';
	currentInfo.uhInfoSize = sizeof(UIMenuStoreInfo);

    strncpy(currentInfo.strCarNo, Prj_GetCarNoString(), (VER_STR_MAX - 1));
    currentInfo.strCarNo[strlen(currentInfo.strCarNo)] = '\0';
    strncpy(currentInfo.strCustomize, Prj_GetCustomizeString(), (VER_STR_MAX - 1));
    currentInfo.strCustomize[strlen(currentInfo.strCustomize)] = '\0';
	currentInfo.uhInfoSize = sizeof(UIMenuStoreInfo);
	//#NT#2013/3/15#Philex Lin - end

	//Using PStore to read / sys param
	//#NT#2016/06/23#Niven Cho -begin
	//#NT#porting KS's suggestion that PStore reset mechanism
	UINT32 uiPsFreeSpace = PStore_GetInfo(PS_INFO_FREE_SPACE);
	if (uiPsFreeSpace == 0) {
		if ((pSection = PStore_OpenSection(PS_SYS_PARAM, PS_UPDATE)) != E_PS_SECHDLER) {
			PStore_WriteSection((UINT8 *)&currentInfo, 0, sizeof(UIMenuStoreInfo), pSection);
			PStore_CloseSection(pSection);
		} else {
			DBG_ERR("Update sys param fail\r\n");
		}
	} else {
		if ((pSection = PStore_OpenSection(PS_SYS_PARAM, PS_RDWR | PS_CREATE)) != E_PS_SECHDLER) {
			PStore_WriteSection((UINT8 *)&currentInfo, 0, sizeof(UIMenuStoreInfo), pSection);
			PStore_CloseSection(pSection);
		} else {
			DBG_ERR("Write sys param fail\r\n");
		}
	}
	//#NT#2016/06/23#Niven Cho -end

	if (PStore_CheckSection(PS_SYS_PARAM, &error) != E_PS_OK) {
		DBG_ERR("PStore_CheckSection\r\n");
	}

	if (error != E_PS_OK) {
		DBG_ERR("PStore error msg :%x\r\n", error);
		{
			UINT32 BufSize = 0x1800000;
			UINT8 *pBuf = (UINT8 *)SxCmd_GetTempMem(BufSize);

			if (!pBuf) {
				DBG_ERR("pBuf is NULL\r\n");
				return;
			}
			//open file system for save file
			//Dep_Fs_Init(TRUE,TRUE);
			PStore_Dump(pBuf, BufSize);
			SxCmd_RelTempMem((UINT32)pBuf);
		}
		Ux_DumpEvents();
		//while (1);
	}

	#endif
#else

#if defined(_EMBMEM_EMMC_)
	unsigned long long partition_ofs= 0, partition_size = 0;
	int ret = -1;
    FILE *fd_mmc = NULL;
	INT32 rw_len = 0;
    
	ret = UIInfo_GetStrgPartitionInfo(&partition_ofs, &partition_size, PARTITION_PATH_USR1);
    if ((ret == 0) && (sizeof(currentInfo) < partition_size)) {	
		if ((fd_mmc = fopen("/dev/mmcblk2p14", "wb")) == NULL) { ///dev/mmcblk2p14 ==> partition_usr1 ; cat /proc/nvt_info/emmc
			DBG_ERR("/dev/mmcblk2p14 fail !!\r\n");
		} else {
			rw_len = fwrite(&currentInfo, 1, sizeof(currentInfo), fd_mmc);
			if(rw_len != sizeof(currentInfo)) {
				DBG_ERR("Error to write file for /dev/mmcblk2p14");			
			}				
			fclose(fd_mmc);;
		}

		if ((fd_mmc = fopen("/dev/mmcblk2p15", "wb")) == NULL) { ///dev/mmcblk2p14 ==> partition_usr2 ; cat /proc/nvt_info/emmc
			DBG_ERR("/dev/mmcblk2p14 fail !!\r\n");
		} else {
			rw_len = fwrite(&currentInfo, 1, sizeof(currentInfo), fd_mmc);
			if(rw_len != sizeof(currentInfo)) {
				DBG_ERR("Error to write file for /dev/mmcblk2p14");			
			}				
			fclose(fd_mmc);
		}		
    }
#elif defined(_EMBMEM_SPI_NAND_)

	unsigned long long partition_ofs= 0, partition_size = 0;
	int ret = 0;
    FILE *sys_mtd_fp = NULL;
	INT32 rw_len = 0;
	UINT32 sectorCnt;
	char cmd[128] = {0};
	char filename[128] = {0};
	FILE *nandwrite_fp = NULL;
	void* tmpInfo = NULL;
	size_t write_size;

	SysCheckFlag();

	/* check if sys param changed */
	if(memcmp(&currentInfo, &origInfo, sizeof(currentInfo)) == 0){
		DBG_DUMP("menu info is not changed\n");
		goto EXIT;
	}

	sectorCnt = (sizeof(currentInfo) / _EMBMEM_BLK_SIZE_) + ((sizeof(currentInfo) % _EMBMEM_BLK_SIZE_)? 1 : 0);

	ret = UIInfo_GetStrgPartitionInfo(&partition_ofs, &partition_size, PARTITION_PATH_SYS);
    if ((ret == 0) && (sizeof(currentInfo) < partition_size)) {
    	char sys_mtd_dev_path[128] = {'\0'};
    	ret = find_sys_mtd_device(sys_mtd_dev_path, sizeof(sys_mtd_dev_path));
    	if(ret){
    		goto EXIT;
    	}

    	sys_mtd_fp = fopen(sys_mtd_dev_path, "wb");
    	if(!sys_mtd_fp){
    		DBG_ERR("open %s failed!\n", sys_mtd_dev_path);
    		ret = -1;
    		goto EXIT;
    	}

		write_size = sectorCnt * _EMBMEM_BLK_SIZE_;
		tmpInfo = malloc(write_size);
		if(!tmpInfo){
			DBG_ERR("allocate tmpInfo failed!\n");
			ret = -1;
			goto EXIT;
		}

		memset(tmpInfo, 0xFF, write_size); /* keep remain data 0xFF to avoid write flash */
		currentInfo.uhInfoSize = sizeof(currentInfo);
		memcpy(tmpInfo, &currentInfo, sizeof(currentInfo));
		sprintf(filename, "nandwrite.in");
		nandwrite_fp = fopen(filename, "wb");
		if(!nandwrite_fp){
			DBG_ERR("open %s filaed!\n", filename);
			ret = -1;
			goto EXIT;
		}

		rw_len = fwrite(tmpInfo, 1, write_size, nandwrite_fp);
		if(rw_len != (INT32)(write_size)) {
			DBG_ERR("fwrite size not matched(%ld / %ld)!\n", rw_len, write_size);
			ret = -1;
			goto EXIT;
		}

		sprintf(cmd, "flash_eraseall -N %s", sys_mtd_dev_path);
		DBG_DUMP("%s\n", cmd);
		ret = system(cmd);
		if(ret){
			DBG_ERR("flash_eraseall failed!\n");
			goto EXIT;
		}

		sprintf(cmd, "nandwrite %s %s", sys_mtd_dev_path, filename);
		DBG_DUMP("%s\n", cmd);
		ret = system(cmd);
		if(ret){
			DBG_ERR("nandwrite failed!\n");
			goto EXIT;
		}
    }

EXIT:
	if(nandwrite_fp){
		fclose(nandwrite_fp);
		nandwrite_fp = NULL;
	}

	if(tmpInfo){
		free(tmpInfo);
		tmpInfo = NULL;
	}

#elif defined(_EMBMEM_SPI_NOR_)

	unsigned long long partition_ofs= 0, partition_size = 0;
	int ret = 0;
    FILE *sys_mtd_fp = NULL;
	INT32 rw_len = 0;
	UINT32 sectorCnt;
	void* tmpInfo = NULL;
	size_t write_size;
	char cmd[128] = {'\0'};
	printf("%s:%d s\n", __FUNCTION__, __LINE__);

	SysCheckFlag();

	/* check if sys param changed */
	if(memcmp(&currentInfo, &origInfo, sizeof(currentInfo)) == 0){
		DBG_DUMP("menu info is not changed\n");
		goto EXIT;
	}

	sectorCnt = (sizeof(currentInfo) / _EMBMEM_BLK_SIZE_) + ((sizeof(currentInfo) % _EMBMEM_BLK_SIZE_)? 1 : 0);

	ret = UIInfo_GetStrgPartitionInfo(&partition_ofs, &partition_size, PARTITION_PATH_SYS);
    if ((ret == 0) && (sizeof(currentInfo) < partition_size)) {
    	char sys_mtd_dev_path[128] = {'\0'};
    	ret = find_sys_mtd_device(sys_mtd_dev_path, sizeof(sys_mtd_dev_path));
    	if(ret){
    		goto EXIT;
    	}

    	sys_mtd_fp = fopen(sys_mtd_dev_path, "wb");
    	if(!sys_mtd_fp){
    		DBG_ERR("open %s failed!\n", sys_mtd_dev_path);
    		ret = -1;
    		goto EXIT;
    	}

		write_size = sectorCnt * _EMBMEM_BLK_SIZE_;
		tmpInfo = malloc(write_size);
		if(!tmpInfo){
			DBG_ERR("allocate tmpInfo failed!\n");
			ret = -1;
			goto EXIT;
		}

		sprintf(cmd, "flash_eraseall -N %s", sys_mtd_dev_path);
		DBG_DUMP("%s\n", cmd);
		ret = system(cmd);
		if(ret){
			DBG_ERR("flash_eraseall failed!\n");
			goto EXIT;
		}

		memset(tmpInfo, 0xFF, write_size);
		currentInfo.uhInfoSize = sizeof(currentInfo);
		memcpy(tmpInfo, &currentInfo, sizeof(currentInfo));
		rw_len = fwrite(tmpInfo, 1, write_size, sys_mtd_fp);
		if(rw_len != (INT32)(write_size)) {
			DBG_ERR("fwrite size not matched(%ld / %ld)!\n", rw_len, write_size);
			ret = -1;
			goto EXIT;
		}
		fflush(sys_mtd_fp);

 	 	UINT32 sum = MemCheck_CalcCheckSum16Bit((UINT32)tmpInfo, sizeof(currentInfo));
 	 	DBG_DUMP("**************size = %lx / mov size = %u / sum = %lx **************\n",
 	 			sizeof(currentInfo),
				((UIMenuStoreInfo*)tmpInfo)->UIParameter[FL_MOVIE_SIZE],
				sum);
    }
    else{
    	DBG_ERR("can't get partition info or menu info size exceed partition size!\n");
    }

EXIT:
	if(sys_mtd_fp){
		fclose(sys_mtd_fp);
		sys_mtd_fp = NULL;
	}

	if(tmpInfo){
		free(tmpInfo);
		tmpInfo = NULL;
	}
	printf("%s:%d e\n", __FUNCTION__, __LINE__);

#endif
   		
#endif //for #if (PST_FUNC == ENABLE)
}

void Reset_MenuInfo(void)
{
    memcpy(&CarNo_Buf, "           ", sizeof(char)*13);
    memcpy(&Customize_Buf, "           ", sizeof(char)*13);

	SysResetFlag();             // reset system flags

    {
        //reset DateTime
        struct tm Curr_DateTime = {0};

        Curr_DateTime.tm_year = DEF_YEAR;
        Curr_DateTime.tm_mon = DEF_MONTH;
        Curr_DateTime.tm_mday = DEF_DAY;
        Curr_DateTime.tm_hour = 0;
        Curr_DateTime.tm_min = 0;
        Curr_DateTime.tm_sec = 0;

        hwclock_set_time(TIME_ID_CURRENT, Curr_DateTime, 0);
    }

	SysExeMenuSettingFuncs();   // execute menu setting related functions

	/* After reset, save to NAND */
	Save_MenuInfo();
}

void Init_SysInfo(void)
{
	DBG_IND("[Init_SysInfo][NAND update state]\r\n");
}

void Init_MenuInfo(void)
{
	DBG_IND("[Init_MenuInfo][PStore update state]\r\n");
	DBG_IND("Version %s  %d\r\n", currentInfo.pVersion, currentInfo.uhInfoSize);

	SysCheckFlag();             // check flag (limit value)
	SysSetFixedFlag();          // set fixed flag
	SysSetFixedFlagSysInit();   // set fixed flag for system init only
	SysExeMenuSettingFuncs();   // execute menu setting related functions
}

UIMenuStoreInfo *UI_GetMenuInfo(void)
{
	return &currentInfo;
}
#if 0
UINT32 UI_GetData(UINT32 attribute)
{
	DBG_IND("get UIParam[%d]\r\n", attribute);
#if (_FPGA_EMULATION_ == ENABLE)
	if (attribute == FL_MOVIE_SIZE) {
		return MOVIE_SIZE_VGA;    // VGA only
	}
#endif
	return currentInfo.UIParameter[attribute];
}
void UI_SetData(UINT32 attribute, UINT32 value)
{
	DBG_IND("set UIParam[%d]= %d\r\n", attribute, value);
	currentInfo.UIParameter[attribute] = value;
}
#endif

static UINT32 guiBatteryLevel       = UIDFT_BATTERY_LVL;
//-----------------------------------------------------------------------------
// Get USB connect type but naming is backward compatible for NT96220
//-----------------------------------------------------------------------------
/**
  Return AC plug in or unplugged

  Return AC plug in or unplugged.
  TRUE  -> AC plug in.
  FALSE -> AC is unplugged.

  @param void
  @return BOOL: TRUE -> AC plug in, FALSE -> AC is unplugged
*/
BOOL KeyScan_IsACIn(void)
{
	BOOL bACStatus;

#if _TODO

	if (GxUSB_GetConnectType() == USB_CONNECT_CHARGER) {
		bACStatus = TRUE;
	} else {
		bACStatus = FALSE;
	}
#else
	bACStatus = FALSE;
#endif

	return bACStatus;
}

//-----------------------------------------------------------------------------
// Auto Poweroff/USB detect/Enable Key sound scan items
//-----------------------------------------------------------------------------
void KeyScan_EnableMisc(BOOL bEn)
{
	if (bEn == FALSE) {
		// disable auto power off/USB detect timer
		// disable key tone flag
		GxPower_SetControl(GXPWR_CTRL_AUTOPOWEROFF_EN, 0xff); //reset
		GxPower_SetControl(GXPWR_CTRL_AUTOSLEEP_EN, 0xff); //reset
		SxTimer_SetFuncActive(SX_TIMER_DET_AUTOPOWEROFF_ID, FALSE);
#if 0 //(USB_MODE==ENABLE)
		SxTimer_SetFuncActive(SX_TIMER_DET_USB_ID, FALSE);
#endif
		//UISound_EnableKey(FALSE); // 660 is full-duplex for audio
	} else {
		// enable auto power off/USB detect timer
		// enable key tone flag
		//#NT#2016/11/21#Adam Su -begin
		//#NT#Fix Mantis Issue 0113246
		SxTimer_SetFuncActive(SX_TIMER_DET_AUTOPOWEROFF_ID, TRUE);
		//#NT#2016/11/21#Adam Su -end
#if 1 //(USB_MODE==ENABLE)
		SxTimer_SetFuncActive(SX_TIMER_DET_USB_ID, TRUE);
#endif
		//UISound_EnableKey(TRUE); // 660 is full-duplex for audio
	}
}

//-----------------------------------------------------------------------------
// Battery Level
//-----------------------------------------------------------------------------
UINT32 GetBatteryLevel(void)
{
#if 0
	if (KeyScan_IsACIn()) {
		guiBatteryLevel = BATTERY_CHARGE;
	} else {
#if (PWRLEVEL_FUNCTION == ENABLE)
		switch (GxPower_GetControl(GXPWR_CTRL_BATTERY_LEVEL)) {
		case VOLDET_BATTERY_LVL_4:
			guiBatteryLevel = BATTERY_FULL;
			break;
		case VOLDET_BATTERY_LVL_3:
			guiBatteryLevel = BATTERY_MED;
			break;
		case VOLDET_BATTERY_LVL_2:
			guiBatteryLevel = BATTERY_LOW;
			break;
		case VOLDET_BATTERY_LVL_1:
			guiBatteryLevel = BATTERY_EMPTY;
			break;

		case VOLDET_BATTERY_LVL_0:
			guiBatteryLevel = BATTERY_EXHAUSTED;
			break;
		}
#else
		guiBatteryLevel = BATTERY_FULL;
#endif
	}
#else
	guiBatteryLevel = BATTERY_FULL;
#endif

	return guiBatteryLevel;
}

//-----------------------------------------------------------------------------
// Set/Get System Flags
//-----------------------------------------------------------------------------
void SysSetFlag(UINT32 uiFlag, UINT32 uiValue)
{
	currentInfo.UIParameter[uiFlag] = uiValue;
}

UINT32 SysGetFlag(UINT32 uiFlag)
{
	return (currentInfo.UIParameter[uiFlag]);
}

static void SysLimitFlag(UINT32 uiFlag, UINT32 uiMinId, UINT32 uiMaxId, UINT32 uiDefaultId)
{
	UINT32  uiValue = SysGetFlag(uiFlag);

	if ((uiValue < uiMinId) || (uiValue > uiMaxId - 1)) {
		uiValue = uiDefaultId;
	}

	SysSetFlag(uiFlag, uiValue);
}

void SysCheckFlag(void)
{
	// Check and limit system flag value
	// Photo
	SysLimitFlag(FL_PHOTO_SIZE,         0,  PHOTO_SIZE_ID_MAX,          DEFAULT_PHOTO_SIZE);
	SysLimitFlag(FL_SCENE,              0,  SCENE_ID_MAX,               DEFAULT_SCENE);
	SysLimitFlag(FL_QUALITY,            0,  QUALITY_ID_MAX,             DEFAULT_PHOTO_QUALITY);
	SysLimitFlag(FL_SELFTIMER,          0,  SELFTIMER_ID_MAX,           DEFAULT_SELFTIMER);
	SysLimitFlag(FL_ANTISHAKE,          0,  ANTISHAKE_ID_MAX,           DEFAULT_ANTISHAKING);
	SysLimitFlag(FL_FD,                 0,  FD_ID_MAX,                  DEFAULT_FD);
	SysLimitFlag(FL_WB,                 0,  WB_ID_MAX,                  DEFAULT_WB);
	SysLimitFlag(FL_COLOR_EFFECT,       0,  COLOR_EFFECT_ID_MAX,        DEFAULT_PHOTO_COLOR);
	SysLimitFlag(FL_CONTINUE_SHOT,      0,  CONTINUE_SHOT_SETTING_MAX,  DEFAULT_CONTINUE_SHOT);
	SysLimitFlag(FL_SHARPNESS,          0,  SHARPNESS_ID_MAX,           DEFAULT_SHARPNESS);
	SysLimitFlag(FL_EV,                 0,  EV_SETTING_MAX,             DEFAULT_EV);
    SysLimitFlag(FL_EV2,                0,  EV_SETTING_MAX,             DEFAULT_EV2);
	SysLimitFlag(FL_ISO,                0,  ISO_ID_MAX,                 DEFAULT_ISO);
	SysLimitFlag(FL_METERING,           0,  METERING_ID_MAX,            DEFAULT_METERING);
    SysLimitFlag(FL_SATURATION,         0,  SATURATION_ID_MAX,          DEFAULT_SATURATION);
    SysLimitFlag(FL_DATE_STAMP,     	0,  DATE_STAMP_ID_MAX,      	DEFAULT_DATE_STAMP);
    SysLimitFlag(FL_DUAL_CAM,           0,  DUALCAM_SETTING_MAX,        DEFAULT_DUAL_CAM);
    SysLimitFlag(FL_DUAL_CAM_MENU,      0,  DUALCAM_SETTING_MAX,        DEFAULT_DUAL_CAM);
    SysLimitFlag(FL_RSC,                0,  RSC_SETTING_MAX,            DEFAULT_RSC);
    SysLimitFlag(FL_RSC_MENU,           0,  RSC_SETTING_MAX,            DEFAULT_RSC);
    SysLimitFlag(FL_WDR,                0,  WDR_SETTING_MAX,            DEFAULT_WDR);
    SysLimitFlag(FL_WDR_MENU,           0,  WDR_SETTING_MAX,            DEFAULT_WDR);
    SysLimitFlag(FL_SHDR,               0,  SHDR_SETTING_MAX,           DEFAULT_SHDR);
    SysLimitFlag(FL_SHDR_MENU,          0,  SHDR_SETTING_MAX,           DEFAULT_SHDR);

	// Movie
	SysLimitFlag(FL_MOVIE_SIZE,         0,  MOVIE_SIZE_ID_MAX,          DEFAULT_MOVIE_SIZE);
    SysLimitFlag(FL_MOVIE_SIZE_MENU,    0,  MOVIE_SIZE_ID_MAX,          DEFAULT_MOVIE_SIZE);
	SysLimitFlag(FL_MOVIE_CYCLIC_REC,   0,  MOVIE_CYCLICREC_ID_MAX,     DEFAULT_MOVIE_CYCLICREC);
	SysLimitFlag(FL_MOVIE_MOTION_DET,   0,  MOVIE_MOTIONDET_ID_MAX,     DEFAULT_MOVIE_MOTION_DET);
	SysLimitFlag(FL_MOVIE_AUDIO,        0,  MOVIE_AUDIO_ID_MAX,         DEFAULT_MOVIE_AUDIO);
	SysLimitFlag(FL_MOVIE_VOICE,        0,  MOVIE_VOICE_ID_MAX,         DEFAULT_MOVIE_VOICE);
	SysLimitFlag(FL_ASR,        		0,  ASR_ID_MAX,         		DEFAULT_ASR);
	SysLimitFlag(FL_ASR_CONTENT,        0,  ASR_CONTENT_ID_MAX,         DEFAULT_ASR_CONTENT);
	SysLimitFlag(FL_MOVIE_DATEIMPRINT,  0,  MOVIE_DATEIMPRINT_ID_MAX,   DEFAULT_MOVIE_DATEIMPRINT);
	SysLimitFlag(FL_MOVIE_HDR,          0,  MOVIE_HDR_ID_MAX,           DEFAULT_MOVIE_HDR);
    SysLimitFlag(FL_MOVIE_HDR_MENU,     0,  MOVIE_HDR_ID_MAX,           DEFAULT_MOVIE_HDR);
	SysLimitFlag(FL_MOVIE_HDR_CHANGE_BEFSIZE,     0,  MOVIE_SIZE_ID_MAX,           DEFAULT_HDR_CHANGE_BEFSIZE);
	SysLimitFlag(FL_MOVIE_HDR_STATECHANGE,     0,  MOVIE_HDR_STATE_ID_MAX,           DEFAULT_HDR_STATE_CHANGE);
	SysLimitFlag(FL_MOVIE_WDR,          0,  MOVIE_WDR_ID_MAX,           DEFAULT_MOVIE_WDR);
	SysLimitFlag(FL_MOVIE_WDR_MENU,     0,  MOVIE_WDR_ID_MAX,           DEFAULT_MOVIE_WDR);
	SysLimitFlag(FL_MOVIE_DEFOG,        0,  MOVIE_DEFOG_ID_MAX,         DEFAULT_MOVIE_DEFOG);
	SysLimitFlag(FL_MOVIE_DEFOG_MENU,   0,  MOVIE_DEFOG_ID_MAX,         DEFAULT_MOVIE_DEFOG);
	SysLimitFlag(FL_MOVIE_SENSOR_ROTATE,0,  SEN_ROTATE_MAX,             DEFAULT_SENSOR_ROTATE);
	SysLimitFlag(FL_MovieAudioRecIndex, 0,  MOVIE_VOL_MAX,              DEFAULT_MOVIE_REC_VOLUME);
	SysLimitFlag(FL_MovieAudioRec,      0,  MOVIE_AUD_REC_ID_MAX,       DEFAULT_MOVIE_REC_AUD);
	//#NT#2016/06/14#Charlie Chang -begin
	//#NT#support contrast, audio in, audio in sample rate, flip, movie quality set
	SysLimitFlag(FL_MOVIE_CONTRAST,     0,  MOVIE_CONTRAST_ID_MAX,      DEFAULT_MOVIE_CONTRAST);
	SysLimitFlag(FL_MOVIE_AUDIOIN,      0,  MOVIE_AUDIOIN_ID_MAX,       DEFAULT_MOVIE_AUDIOIN);
	SysLimitFlag(FL_MOVIE_AUDIOIN_SR,   0,  MOVIE_AUDIOIN_SR_ID_MAX,    DEFAULT_MOVIE_AUDIOIN_SR);
	SysLimitFlag(FL_MOVIE_FLIP_MIRROR,  0,  MOVIE_FLIP_MIRROR_ID_MAX,   DEFAULT_MOVIE_FLIP_MIRROR);
	SysLimitFlag(FL_MOVIE_QUALITY_SET,  0,  MOVIE_QUALITY_SET_ID_MAX,   DEFAULT_MOVIE_QUALITY_SET);
	//#NT#2016/06/14#Charlie Chang -end
	//#NT#2017/03/03#Jeah Yen -begin
	//#NT# support sbs mode
	SysLimitFlag(FL_MOVIE_SBS_MODE,     0,  MOVIE_SBS_ID_MAX,           DEFAULT_MOVIE_SBS_MODE);
	//#NT#2017/03/03#Jeah Yen -end
	SysLimitFlag(FL_MOVIE_CODEC,        0,  MOVIE_CODEC_ID_MAX,         DEFAULT_MOVIE_CODEC);
	SysLimitFlag(FL_MOVIE_DECODE,       0,  MOVIE_DECODE_ID_MAX,        DEFAULT_MOVIE_DECODE);
    SysLimitFlag(FL_MOVIE_TIMELAPSE_REC,0,  MOVIE_TIMELAPSEREC_ID_MAX,  DEFAULT_MOVIE_TIMELAPSE_REC);
    SysLimitFlag(FL_MOVIE_TIMELAPSE_REC_MENU, 0, MOVIE_TIMELAPSEREC_ID_MAX, DEFAULT_MOVIE_TIMELAPSE_REC);
    SysLimitFlag(FL_MovieRSCIndex,      0,  MOVIE_RSC_SETTING_MAX,      DEFAULT_MOVIE_RSC);
    SysLimitFlag(FL_MovieRSCIndex_MENU, 0,  MOVIE_RSC_SETTING_MAX,      DEFAULT_MOVIE_RSC);
    SysLimitFlag(FL_MOVIE_IR_CUT,       0,  MOVIE_IR_CUT_ID_MAX,        DEFAULT_IR_CUT);
    SysLimitFlag(FL_MOVIE_PTZ,          0,  MOVIE_PTZ_ID_MAX,           DEFAULT_MOVIE_PTZ);
    SysLimitFlag(FL_MOVIE_PIM,          0,  MOVIE_PIM_ID_MAX,           DEFAULT_MOVIE_PIM);
    SysLimitFlag(FL_MOVIE_URGENT_PROTECT_AUTO,   0,  MOVIE_URGENT_PROTECT_AUTO_ID_MAX,    DEFAULT_MOVIE_URGENT_PROTECT_AUTO);
    SysLimitFlag(FL_MOVIE_URGENT_PROTECT_MANUAL, 0,  MOVIE_URGENT_PROTECT_MANUAL_ID_MAX,  DEFAULT_MOVIE_URGENT_PROTECT_MANUAL);
    SysLimitFlag(FL_MOVIE_LDWS,         0,  MOVIE_LDWS_ID_MAX,          DEFAULT_MOVIE_LDWS);
    SysLimitFlag(FL_MOVIE_LDWS_MENU,    0,  MOVIE_LDWS_ID_MAX,          DEFAULT_MOVIE_LDWS);
    SysLimitFlag(FL_MOVIE_FCW,          0,  MOVIE_FCW_ID_MAX,           DEFAULT_MOVIE_FCWS);
    SysLimitFlag(FL_MOVIE_FCW_MENU,     0,  MOVIE_FCW_ID_MAX,           DEFAULT_MOVIE_FCWS);
    SysLimitFlag(FL_MOVIE_TIMERLAPS,    0,  MOVIE_TIMER_LAPS_ID_MAX,    DEFAULT_MOVIE_TIMERLAPS);
    SysLimitFlag(FL_MOVIE_BITRATE,      0,  MOVIE_BITRATE_ID_MAX,       DEFAULT_MOVIE_BITRATE);
    SysLimitFlag(FL_MOVIE_HDR_DET,      0,  MOVIE_HDR_DET_ID_MAX,       DEFAULT_MOVIE_HDR_DET);

	// Playback
	SysLimitFlag(FL_PROTECT,            0,  FILE_PROTECT_ID_MAX,            DEFAULT_PROTECT);
	SysLimitFlag(FL_MovieAudioPlayIndex,0,  MOVIE_AUDIO_VOL_SETTING_MAX,    DEFAULT_MOVIE_PLAY_VOLUME);

	// System
	SysLimitFlag(FL_AudioPlayIndex,     0,  AUDIO_VOL_MAX,          DEFAULT_AUDIO_PLAY_VOLUME);
	SysLimitFlag(FL_LANGUAGE,           0,  LANG_ID_MAX,            DEFAULT_LANGUAGE);
	SysLimitFlag(FL_BEEP,               0,  BEEP_ID_MAX,            DEFAULT_BEEP);
	SysLimitFlag(FL_AUTO_POWER_OFF,     0,  POWEROFF_SETTING_MAX,   DEFAULT_AUTO_POWER_OFF);
	SysLimitFlag(FL_FREQUENCY,          0,  FREQUENCY_ID_MAX,       DEFAULT_FREQUENCY);
	SysLimitFlag(FL_TV_MODE,            0,  TV_MODE_ID_MAX,         DEFAULT_TV_MODE);
	SysLimitFlag(FL_DualDisp,           0,  DUALDISP_SETTING_MAX,   DEFAULT_DUALDISP);
    SysLimitFlag(FL_GSENSOR,            0,  GSENSOR_ID_MAX,         DEFAULT_GSENSOR);
    SysLimitFlag(FL_LCD_OFF,            0,  LCDOFF_SETTING_MAX,     DEFAULT_LCD_OFF);
    SysLimitFlag(FL_SENSOR_ROTATE,      0,  SEN_ROTATE_MAX,         DEFAULT_SENSOR_ROTATE);
    SysLimitFlag(FL_SENSOR2_ROTATE,     0,  SEN_ROTATE_MAX,         DEFAULT_SENSOR_ROTATE);
    SysLimitFlag(FL_LED,                0,  LED_ID_MAX,             DEFAULT_LED);
    SysLimitFlag(FL_SYS_SOFT_RESET,     0,  SOFT_RESET_ID_MAX,      DEFAULT_SYS_SOFT_RESET);
    SysLimitFlag(FL_GPS,                0,  GPS_ID_MAX,             DEFAULT_GPS);
    SysLimitFlag(FL_TIME_ZONE,          0,  GMT_SETTING_MAX,        DEFAULT_TIME_ZONE);
    SysLimitFlag(FL_SPEED_UNIT,         0,  SPEED_UNIT_ID_MAX,      DEFAULT_SPEED_UNIT);
    SysLimitFlag(FL_GPS_STAMP,          0,  GPS_STAMP_ID_MAX,       DEFAULT_GPS_STAMP);
    SysLimitFlag(FL_FORMAT_WARNING,     0,  FORMAT_WARNING_MAX,     DEFAULT_FORMAT_WARNING);
    SysLimitFlag(FL_FIRSTPOWERON,       0,  FIRSTPOWERON_MAX,       DEFAULT_FIRSTPOWERON);
    SysLimitFlag(FL_BOOT_DELAY,         0,  BOOT_DELAY_SETTING_MAX, DEFAULT_BOOT_DELAY);
    SysLimitFlag(FL_MODEL_STAMP,        0,  MODEL_STAMP_ID_MAX,     DEFAULT_MODEL_STAMP);
    SysLimitFlag(FL_PARKING_MODE,       0,  PARKING_MODE_ID_MAX,    DEFAULT_PARKING_MODE);
    SysLimitFlag(FL_PARKING_MODE_TIMELAPSE_REC,  0,  PARKING_MODE_TIMELAPSEREC_ID_MAX,  DEFAULT_PARKING_MODE_TIMELAPSE_REC);
    SysLimitFlag(FL_PARKING_GSENSOR,    0,  PARKING_GSENSOR_ID_MAX, DEFAULT_PARKING_GSENSOR);
    SysLimitFlag(FL_PARKING_MOTION_DET, 0,  PARKING_MOTIONDET_ID_MAX, DEFAULT_PARKING_MOTION_DET);
    SysLimitFlag(FL_VIDEO_FORMAT,       0,  VIDEO_FORMAT_ID_MAX,    DEFAULT_VIDEO_FORMAT);
    SysLimitFlag(FL_VIDEO_FORMAT_MENU,  0,  VIDEO_FORMAT_ID_MAX,    DEFAULT_VIDEO_FORMAT);
    SysLimitFlag(FL_IR_REAR_COLOR,      0,  IR_REAR_COLOR_ID_MAX,   DEFAULT_IR_REAR_COLOR);
    SysLimitFlag(FL_REAR_SENSOR_MIRROR, 0,  REAR_SENSOR_MIRROR_ID_MAX, DEFAULT_REAR_SENSOR_MIRROR);
    SysLimitFlag(FL_SHUTDOWN_TIMER,     0,  SHUTDOWN_TIMER_ID_MAX,  DEFAULT_SHUTDOWN_TIMER);
    SysLimitFlag(FL_ENTER_PARKING_TIMER,0,  ENTER_PARKING_TIMER_ID_MAX, DEFAULT_ENTER_PARKING_TIMER);
    SysLimitFlag(FL_REAR_MIRROR_DISPLAY,0,  REAR_MIRROR_DISPLAY_ID_MAX, DEFAULT_REAR_MIRROR_DISPLAY);
    SysLimitFlag(FL_TIME_START,         0,  2360,                   DEFAULT_TIME_START);//max = 23:59
    SysLimitFlag(FL_TIME_STOP,          0,  2360,                   DEFAULT_TIME_STOP);//max = 23:59
	SysLimitFlag(FL_PARKING_OFF_GPS,0,PGPS_ID_MAX,DEFAULT_PARKING_OFF_GPS);
	SysLimitFlag(FL_DATE_FORMAT,        0,  DATE_FORMAT_ID_MAX,     DEFAULT_DATE_FORMAT);
	SysLimitFlag(FL_OPENING_LOGO,       0,  OPENING_LOGO_ID_MAX,    DEFAULT_OPENING_LOGO);
	SysLimitFlag(FL_LCD_DISPLAY,        0,  DISPOUT_ID_MAX,         DEFAULT_LCD_DISPLAY);
	SysLimitFlag(FL_LCD_BRIGHTNESS,     0,  LCDBRT_LVL_ID_MAX,      DEFAULT_LCD_BRIGHTNESS);
	SysLimitFlag(FL_MACRO,              0,  MACRO_ID_MAX,           DEFAULT_MACRO);
	SysLimitFlag(FL_USB_MODE,           0,  USB_MODE_ID_MAX,        DEFAULT_USB_MODE);

    SysLimitFlag(FL_VOLUME,             0,  VOLUME_ID_MAX,          DEFAULT_VOLUME);
#if (USE_DCF==ENABLE)
	// Sepcial flags
	SysLimitFlag(FL_DCF_DIR_ID,         MIN_DCF_DIR_NUM,    MAX_DCF_DIR_NUM,    MIN_DCF_DIR_NUM);
	SysLimitFlag(FL_DCF_FILE_ID,        MIN_DCF_FILE_NUM,   MAX_DCF_FILE_NUM,   MIN_DCF_FILE_NUM);
#endif
#if(WIFI_FUNC==ENABLE)
	//Wi-Fi
#if (WIFI_FINALCAM_APP_STYLE == ENABLE || UCTRL_APP_MOVIE_FEATURE_SETGET == ENABLE || YOUKU_SDK == ENABLE)
	SysLimitFlag(FL_WIFI_MOVIE_APP_PREVIEW_SIZE, 0,  WIFI_MOVIE_APP_PREVIEW_SIZE_ID_MAX, DEFAULT_MOVIE_WIFI_APP_PREVIEW_SIZE);
#endif
	SysLimitFlag(FL_WIFI_AUTO_RECORDING, 0,  WIFI_AUTO_RECORDING_ID_MAX, DEFAULT_MOVIE_WIFI_AUTO_RECORDING_OPTION);
	SysLimitFlag(FL_NetWorkMode, 0, NET_MODE_SETTING_MAX, DEFAULT_WIFI_MODE);
    SysLimitFlag(FL_WIFI,        0, WIFI_ID_MAX,          DEFAULT_WIFI);
    SysLimitFlag(FL_WIFI_AUTO,   0, WIFI_AUTO_ID_MAX,     DEFAULT_WIFI_AUTO);
    SysLimitFlag(FL_WIFI_BAND,   0, WIFI_BAND_ID_MAX,     DEFAULT_WIFI_BAND);
#endif

    SysLimitFlag(FL_IsCloneRec,  0, CLONE_REC_MAX,        DEFAULT_CLONE_REC);
	SysLimitFlag(FL_FW_UI_RESET, 0, FW_UI_RESET_MAX,	  DEFAULT_FW_UI_RESET);
    SysLimitFlag(FL_EDOG_OVERSPEED_ALARM,   0,  EDOG_OVERSPEED_ALARM_ID_MAX,    DEFAULT_EDOG_OVERSPEED_ALARM);

    //#NT#Check SSID and passphrase and reset it if illegal.
    if (currentInfo.strSSID[0] == 0xFF) {
        memset(currentInfo.strSSID, '\0', NVT_WSC_MAX_SSID_LEN);
    }
    if (currentInfo.strPASSPHRASE[0] == 0xFF) {
        memset(currentInfo.strPASSPHRASE, '\0', NVT_MAX_WEP_KEY_LEN);
    }

	//5G
    if (currentInfo.strSSID_5G[0] == 0xFF) {
        memset(currentInfo.strSSID_5G, '\0', NVT_WSC_MAX_SSID_LEN);
    }
}

void SysSetFixedFlag(void)
{
	// Fixed some system flags as system reset

	// Photo
	SysSetFlag(FL_CONTINUE_SHOT,           DEFAULT_CONTINUE_SHOT);
	SysSetFlag(FL_SELFTIMER,               DEFAULT_SELFTIMER);

	// Movie

	// Playback
	SysSetFlag(FL_PROTECT,                 DEFAULT_PROTECT);

	// System
	SysSetFlag(FL_LCD_DISPLAY,             DEFAULT_LCD_DISPLAY);
	SysSetFlag(FL_LCD_BRIGHTNESS,          DEFAULT_LCD_BRIGHTNESS);
	SysSetFlag(FL_MovieDisIndex,           MOVIE_DIS_OFF);

	SysSetFlag(FL_COMMON_LOCAL,            WIFI_OFF);
	SysSetFlag(FL_IsCloneRec,              CLONE_REC_OFF);
#if (defined(_MODEL_580_SDV_SJ10_) || defined(_MODEL_580_SDV_SJ10_FAST_BT_) || defined(_MODEL_580_SDV_I860_))
    SysSetFlag(FL_CHG_DISP,              LCD_CHG_DISP_NONE);
    SysSetFlag(FL_CURR_DISP,             LCD_CHG_DISP_LCD1);
#elif (defined(_MODEL_580_SDV_C300_) || defined(_MODEL_580_SDV_C300_FAST_BT_))
    SysSetFlag(FL_CHG_DISP,              LCD_CHG_DISP_NONE);
    SysSetFlag(FL_CURR_DISP,             LCD_CHG_DISP_LCD1);
#endif

#if (MOVIE_EIS == ENABLE) || (defined(_NVT_ETHREARCAM_RX_) && (ETHCAM_EIS ==ENABLE))
    SysSetFlag(FL_MOVIE_EIS, EIS_ON);
    SysSetFlag(FL_MovieRSCIndex_MENU, MOVIE_RSC_ON);
    SysSetFlag(FL_MovieRSCIndex, MOVIE_RSC_ON);
    SysSetFlag(FL_MovieRSCEffect_MENU, MOVIE_RSC_HIGH);
    SysSetFlag(FL_MovieRSCEffect, MOVIE_RSC_HIGH);
#else
    SysSetFlag(FL_MOVIE_EIS, EIS_OFF);
    SysSetFlag(FL_MovieRSCIndex_MENU, MOVIE_RSC_OFF);
    SysSetFlag(FL_MovieRSCIndex, MOVIE_RSC_OFF);
#endif
    //SysSetFlag(FL_FIRSTPOWERON,            FIRSTPOWERON_FALSE);
    SysSetFlag(FL_PARKING_MODE_TIMELAPSE_REC, PARKING_MODE_TIMELAPSEREC_OFF);

	//SysSetFlag(FL_COMMON_LOCAL,            WIFI_OFF);
	SysSetFlag(FL_IsCloneRec,              CLONE_REC_OFF);
#if 0 // unnecessary
	if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED) {
		SysSetFlag(FL_PHOTO_SIZE, PHOTO_SIZE_5M);
		SysSetFlag(FL_MOVIE_SIZE, MOVIE_SIZE_720P);
	}
#endif
   if (SysGetFlag(FL_TIME_START) == 0xFF) {
        SysSetFlag(FL_TIME_START, DEFAULT_TIME_START);
    }
    if (SysGetFlag(FL_TIME_STOP) == 0xFF) {
        SysSetFlag(FL_TIME_STOP, DEFAULT_TIME_STOP);
    }

}

void SysSetFixedFlagSysInit(void)
{
	// Set fixed system flags (only on system init)
	SysSetFlag(FL_WIFI_LINK,		WIFI_LINK_NG);
	SysSetFlag(FL_DUAL_CAM,			SysGetFlag(FL_DUAL_CAM_MENU));
	SysSetFlag(FL_MOVIE_SIZE,		SysGetFlag(FL_MOVIE_SIZE_MENU));
	SysSetFlag(FL_MOVIE_HDR_MENU,       DEFAULT_MOVIE_WDR);
	SysSetFlag(FL_MOVIE_WDR,		DEFAULT_MOVIE_WDR);
	//SysSetFlag(FL_MOVIE_DEFOG,     SysGetFlag(FL_MOVIE_DEFOG_MENU));
	//SysSetFlag(FL_MovieRSCIndex,   SysGetFlag(FL_MovieRSCIndex_MENU));
	SysSetFlag(FL_NetWorkMode,		DEFAULT_WIFI_MODE);  // Reset Wi-Fi mode to AP mode.
	//#NT#2016/07/12#KCHong#[0104994] -begin
	//#NT#Use FL_MOVIE_LDWS_MENU & FL_MOVIE_FCW_MENU instead of FL_MOVIE_LDWS & FL_MOVIE_FCW
    SysSetFlag(FL_MOVIE_LDWS,		DEFAULT_MOVIE_LDWS);//SysGetFlag(FL_MOVIE_LDWS_MENU)
    SysSetFlag(FL_MOVIE_FCW,		DEFAULT_MOVIE_FCWS);//SysGetFlag(FL_MOVIE_FCW_MENU)
	//#NT#2016/07/12#KCHong#[0104994] -end
	//#NT#2016/07/26#KCHong#[0105955] -begin
	//#NT#If ADAS is ON and timelapse changes to OFF, reopen movie mode
	SysSetFlag(FL_MOVIE_TIMELAPSE_REC, SysGetFlag(FL_MOVIE_TIMELAPSE_REC_MENU));
	//#NT#2016/07/26#KCHong#[0105955] -end
	//#NT#2016/08/19#Lincy Lin#[0106935] -begin
	//#NT# Support change WDR, SHDR, RSC setting will change mode after exit menu
	SysSetFlag(FL_RSC,				SysGetFlag(FL_RSC_MENU));
	SysSetFlag(FL_WDR,				SysGetFlag(FL_WDR_MENU));
	SysSetFlag(FL_SHDR,				SysGetFlag(FL_SHDR_MENU));
	//#NT#2016/08/19#Lincy Lin -end
	SysSetFlag(FL_DEFOG,			SysGetFlag(FL_DEFOG_MENU));
	SysSetFlag(FL_MOVIE_CODEC,		SysGetFlag(FL_MOVIE_CODEC_MENU));
	//after power ,always set 0.
	UI_SetData(FL_MOVIE_REC, 0);
    //wifi
#if(WIFI_FUNC==ENABLE)
	SysSetFlag(FL_NetWorkMode,          DEFAULT_WIFI_MODE);  // Reset Wi-Fi mode to AP mode.
#endif
	if ((UI_GetData(FL_MOVIE_SIZE) == MOVIE_SIZE_FRONT_2560x1440P60)
		/*||(UI_GetData(FL_MOVIE_SIZE) == MOVIE_SIZE_FRONT_1920x1080P60)*/)//
	{
		UI_SetData(FL_MOVIE_HDR, MOVIE_HDR_OFF);
		UI_SetData(FL_MOVIE_HDR_MENU, MOVIE_HDR_OFF);
		UI_SetData(FL_MOVIE_WDR, MOVIE_WDR_OFF);
		UI_SetData(FL_MOVIE_WDR_MENU, MOVIE_WDR_OFF);
	} 


}

void SysResetFlag(void)
{
	// Set system flag default value here
	// Photo
	SysSetFlag(FL_PHOTO_SIZE,           DEFAULT_PHOTO_SIZE);
	SysSetFlag(FL_QUALITY,              DEFAULT_PHOTO_QUALITY);
	SysSetFlag(FL_COLOR_EFFECT,         DEFAULT_PHOTO_COLOR);
	SysSetFlag(FL_SCENE,                DEFAULT_SCENE);
	SysSetFlag(FL_EV,                   DEFAULT_EV);
    SysSetFlag(FL_EV2,                  DEFAULT_EV2);
	SysSetFlag(FL_ISO,                  DEFAULT_ISO);
	SysSetFlag(FL_WB,                   DEFAULT_WB);
	SysSetFlag(FL_METERING,             DEFAULT_METERING);
	SysSetFlag(FL_SHARPNESS,            DEFAULT_SHARPNESS);
	SysSetFlag(FL_SATURATION,           DEFAULT_SATURATION);
	SysSetFlag(FL_FD,                   DEFAULT_FD);
	SysSetFlag(FL_ANTISHAKE,            DEFAULT_ANTISHAKING);
	SysSetFlag(FL_RSC,                  DEFAULT_RSC);
	SysSetFlag(FL_WDR,                  DEFAULT_WDR);
	SysSetFlag(FL_DUAL_CAM_MENU,        DEFAULT_DUAL_CAM);
	SysSetFlag(FL_QUICK_REVIEW,         DEFAULT_QUICK_REVIEW);
	SysSetFlag(FL_DATE_STAMP,           DEFAULT_DATE_STAMP);
	SysSetFlag(FL_SELFTIMER,            DEFAULT_SELFTIMER);
	SysSetFlag(FL_FLASH_MODE,           DEFAULT_FLASH_MODE);
	SysSetFlag(FL_CONTINUE_SHOT,        DEFAULT_CONTINUE_SHOT);
	SysSetFlag(FL_SHDR,                 DEFAULT_SHDR);
	//#NT#2016/08/19#Lincy Lin#[0106935] -begin
	//#NT# Support change WDR, SHDR, RSC setting will change mode after exit menu
	SysSetFlag(FL_RSC_MENU,             DEFAULT_RSC);
	SysSetFlag(FL_WDR_MENU,             DEFAULT_WDR);
	SysSetFlag(FL_SHDR_MENU,            DEFAULT_SHDR);
	//#NT#2016/08/19#Lincy Lin -end

	SysSetFlag(FL_DEFOG,            DEFAULT_DEFOG);

	// Movie
	if (System_GetEnableSensor() == (SENSOR_1 | SENSOR_2)) {
		SysSetFlag(FL_MOVIE_SIZE_MENU,  DEFAULT_MOVIE_SIZE_DUAL);
        SysSetFlag(FL_MOVIE_SIZE,       DEFAULT_MOVIE_SIZE_DUAL);
	} else {
		SysSetFlag(FL_MOVIE_SIZE_MENU,  DEFAULT_MOVIE_SIZE);
        SysSetFlag(FL_MOVIE_SIZE,       DEFAULT_MOVIE_SIZE);
	}
	SysSetFlag(FL_MOVIE_QUALITY,        DEFAULT_MOVIE_QUALITY);
	SysSetFlag(FL_MOVIE_COLOR,          DEFAULT_MOVIE_COLOR);
	SysSetFlag(FL_MOVIE_CYCLIC_REC,     DEFAULT_MOVIE_CYCLICREC);
	SysSetFlag(FL_MOVIE_MOTION_DET,     DEFAULT_MOVIE_MOTION_DET);
	SysSetFlag(FL_MOVIE_AUDIO,          DEFAULT_MOVIE_AUDIO);
	SysSetFlag(FL_MOVIE_VOICE,          DEFAULT_MOVIE_VOICE);
	SysSetFlag(FL_ASR,          		DEFAULT_ASR);
	SysSetFlag(FL_ASR_CONTENT,          DEFAULT_ASR_CONTENT);
	SysSetFlag(FL_MOVIE_DATEIMPRINT,    DEFAULT_MOVIE_DATEIMPRINT);
	SysSetFlag(FL_MOVIE_HDR_MENU,       DEFAULT_MOVIE_HDR);
    SysSetFlag(FL_MOVIE_HDR,            DEFAULT_MOVIE_HDR);
	SysSetFlag(FL_MOVIE_HDR_CHANGE_BEFSIZE,            DEFAULT_HDR_CHANGE_BEFSIZE);
	SysSetFlag(FL_MOVIE_HDR_STATECHANGE,            DEFAULT_HDR_STATE_CHANGE);
	SysSetFlag(FL_MOVIE_WDR_MENU,       DEFAULT_MOVIE_WDR);
    SysSetFlag(FL_MOVIE_WDR,            DEFAULT_MOVIE_WDR);
	SysSetFlag(FL_MOVIE_DEFOG_MENU, 	DEFAULT_MOVIE_DEFOG);
    SysSetFlag(FL_MOVIE_DEFOG, 	        DEFAULT_MOVIE_DEFOG);
	SysSetFlag(FL_MovieRSCIndex_MENU,   DEFAULT_MOVIE_RSC);
    SysSetFlag(FL_MovieRSCIndex,        DEFAULT_MOVIE_RSC);
	SysSetFlag(FL_MOVIE_SENSOR_ROTATE,  DEFAULT_SENSOR_ROTATE);
	SysSetFlag(FL_MOVIE_SENSOR_ROTATE_MENU,  DEFAULT_SENSOR_ROTATE);
	SysSetFlag(FL_MovieMCTFIndex,       DEFAULT_MCTFINDEX);
	SysSetFlag(FL_MOVIE_PTZ,                   DEFAULT_MOVIE_PTZ);
	SysSetFlag(FL_MOVIE_URGENT_PROTECT_AUTO,   DEFAULT_MOVIE_URGENT_PROTECT_AUTO);
	SysSetFlag(FL_MOVIE_URGENT_PROTECT_MANUAL, DEFAULT_MOVIE_URGENT_PROTECT_MANUAL);
	SysSetFlag(FL_MOVIE_IR_CUT,         DEFAULT_IR_CUT);
	//#NT#2016/07/26#KCHong#[0105955] -begin
	//#NT#If ADAS is ON and timelapse changes to OFF, reopen movie mode
	SysSetFlag(FL_MOVIE_TIMELAPSE_REC_MENU,  DEFAULT_MOVIE_TIMELAPSE_REC);
	//#NT#2016/07/26#KCHong#[0105955] -end
    SysSetFlag(FL_MOVIE_TIMELAPSE_REC,  DEFAULT_MOVIE_TIMELAPSE_REC);
	SysSetFlag(FL_MOVIE_PIM,            DEFAULT_MOVIE_PIM);
	//#NT#2016/07/12#KCHong#[0104994] -begin
	//#NT#Use FL_MOVIE_LDWS_MENU & FL_MOVIE_FCW_MENU instead of FL_MOVIE_LDWS & FL_MOVIE_FCW
	SysSetFlag(FL_MOVIE_LDWS_MENU,      DEFAULT_MOVIE_LDWS);
	SysSetFlag(FL_MOVIE_FCW_MENU,       DEFAULT_MOVIE_FCWS);
	//#NT#2016/07/12#KCHong#[0104994] -end
	SysSetFlag(FL_MovieAudioRecIndex,   DEFAULT_MOVIE_REC_VOLUME);
	SysSetFlag(FL_MovieAudioRec,        DEFAULT_MOVIE_REC_AUD);
	SysSetFlag(FL_MOVIE_DDD,            DEFAULT_MOVIE_DDD);
	SysSetFlag(FL_MOVIE_ADAS_CAL,       DEFAULT_MOVIE_ADAS_CAL);
	SysSetFlag(FL_MOVIE_CODEC,          DEFAULT_MOVIE_CODEC);
	SysSetFlag(FL_MOVIE_CODEC_MENU,     DEFAULT_MOVIE_CODEC);
	SysSetFlag(FL_MOVIE_DECODE,         DEFAULT_MOVIE_DECODE);
    SysSetFlag(FL_MOVIE_TIMERLAPS,      DEFAULT_MOVIE_TIMERLAPS);
    SysSetFlag(FL_MOVIE_BITRATE,        DEFAULT_MOVIE_BITRATE);
	SysSetFlag(FL_MOVIE_HDR_DET,		DEFAULT_MOVIE_HDR_DET);

	// Playback
	SysSetFlag(FL_PROTECT,              DEFAULT_PROTECT);
	SysSetFlag(FL_MovieAudioPlayIndex,  DEFAULT_MOVIE_PLAY_VOLUME);

	// System
	SysSetFlag(FL_AudioPlayIndex,       DEFAULT_AUDIO_PLAY_VOLUME);
	SysSetFlag(FL_AUTO_POWER_OFF,       DEFAULT_AUTO_POWER_OFF);
	SysSetFlag(FL_LCD_OFF,              DEFAULT_LCD_OFF);
	SysSetFlag(FL_BEEP,                 DEFAULT_BEEP);
	SysSetFlag(FL_LANGUAGE,             DEFAULT_LANGUAGE);
	SysSetFlag(FL_FREQUENCY,            DEFAULT_FREQUENCY);
	SysSetFlag(FL_TV_MODE,              DEFAULT_TV_MODE);
	SysSetFlag(FL_HDMI_MODE,            DEFAULT_HDMI_MODE);
	SysSetFlag(FL_DATE_FORMAT,          DEFAULT_DATE_FORMAT);
	SysSetFlag(FL_OPENING_LOGO,         DEFAULT_OPENING_LOGO);
	SysSetFlag(FL_CPU2_DEFAULT,         1);
    SysSetFlag(FL_SENSOR_ROTATE,        DEFAULT_SENSOR_ROTATE);
    SysSetFlag(FL_SENSOR2_ROTATE,       DEFAULT_SENSOR_ROTATE);
    SysSetFlag(FL_LED,                  DEFAULT_LED);
    SysSetFlag(FL_GPS,                  DEFAULT_GPS);
    SysSetFlag(FL_TIME_ZONE,            DEFAULT_TIME_ZONE);
    SysSetFlag(FL_SPEED_UNIT,           DEFAULT_SPEED_UNIT);
    SysSetFlag(FL_GPS_STAMP,            DEFAULT_GPS_STAMP);
    SysSetFlag(FL_FORMAT_WARNING,       DEFAULT_FORMAT_WARNING);
    SysSetFlag(FL_FORMAT_WARNING_DATE,  DEFAULT_FORMAT_WARNING_DATE);
    SysSetFlag(FL_FIRSTPOWERON,         DEFAULT_FIRSTPOWERON);
    SysSetFlag(FL_BOOT_DELAY,           DEFAULT_BOOT_DELAY);
    SysSetFlag(FL_MODEL_STAMP,          DEFAULT_MODEL_STAMP);
    SysSetFlag(FL_PARKING_MODE,         DEFAULT_PARKING_MODE);
    SysSetFlag(FL_PARKING_MODE_TIMELAPSE_REC,  DEFAULT_PARKING_MODE_TIMELAPSE_REC);
	SysSetFlag(FL_PARKING_GSENSOR,      DEFAULT_PARKING_GSENSOR);
    SysSetFlag(FL_PARKING_MOTION_DET,   DEFAULT_PARKING_MOTION_DET);
    SysSetFlag(FL_VIDEO_FORMAT,         DEFAULT_VIDEO_FORMAT);
    SysSetFlag(FL_VIDEO_FORMAT_MENU,    DEFAULT_VIDEO_FORMAT);
    SysSetFlag(FL_IR_REAR_COLOR,        DEFAULT_IR_REAR_COLOR);
    SysSetFlag(FL_REAR_SENSOR_MIRROR,   DEFAULT_REAR_SENSOR_MIRROR);
    SysSetFlag(FL_SHUTDOWN_TIMER,       DEFAULT_SHUTDOWN_TIMER);
    SysSetFlag(FL_LAST_DATETIME,        DEFAULT_LAST_DATETIME);
    SysSetFlag(FL_ENTER_PARKING_TIMER,  DEFAULT_ENTER_PARKING_TIMER);
    SysSetFlag(FL_REAR_MIRROR_DISPLAY,  DEFAULT_REAR_MIRROR_DISPLAY);
    SysSetFlag(FL_TIME_START,           DEFAULT_TIME_START);
    SysSetFlag(FL_TIME_STOP,            DEFAULT_TIME_STOP);
    SysSetFlag(FL_PARKING_OFF_GPS,			DEFAULT_PARKING_OFF_GPS);

	SysSetFlag(FL_LCD_DISPLAY,          DEFAULT_LCD_DISPLAY);
	SysSetFlag(FL_LCD_BRIGHTNESS,       DEFAULT_LCD_BRIGHTNESS);
	SysSetFlag(FL_DualDisp,             DEFAULT_DUALDISP);
	SysSetFlag(FL_MACRO,                DEFAULT_MACRO);
	SysSetFlag(FL_USB_MODE,             DEFAULT_USB_MODE);
	SysSetFlag(FL_GSENSOR,              DEFAULT_GSENSOR);
	SysSetFlag(FL_EDGE,                 DEFAULT_EDGE);
	SysSetFlag(FL_NR,                   DEFAULT_NR);

	//#NT#2016/06/14#Charlie Chang -begin
	//#NT#support contrast, two way audio in and sample rate, flip, movie qualiity set
	SysSetFlag(FL_MOVIE_CONTRAST,       DEFAULT_MOVIE_CONTRAST);
	SysSetFlag(FL_MOVIE_AUDIOIN,        DEFAULT_MOVIE_AUDIOIN);
	SysSetFlag(FL_MOVIE_AUDIOIN_SR,     DEFAULT_MOVIE_AUDIOIN_SR);
	SysSetFlag(FL_MOVIE_FLIP_MIRROR,    DEFAULT_MOVIE_FLIP_MIRROR);
	SysSetFlag(FL_MOVIE_QUALITY_SET,    DEFAULT_MOVIE_QUALITY_SET);
	//#NT#2016/06/14#Charlie Chang -end
	//#NT#2017/03/03#Jeah Yen -begin
	//#NT# support sbs mode
	SysSetFlag(FL_MOVIE_SBS_MODE,       DEFAULT_MOVIE_SBS_MODE);
	//#NT#2017/03/03#Jeah Yen -end
    SysSetFlag(FL_VOLUME,               DEFAULT_VOLUME);	
	// Wi-Fi
#if(WIFI_FUNC==ENABLE)

#if (WIFI_FINALCAM_APP_STYLE == ENABLE || UCTRL_APP_MOVIE_FEATURE_SETGET == ENABLE || YOUKU_SDK == ENABLE)
	SysSetFlag(FL_WIFI_MOVIE_APP_PREVIEW_SIZE,  DEFAULT_MOVIE_WIFI_APP_PREVIEW_SIZE);
#endif
	SysSetFlag(FL_WIFI_AUTO_RECORDING,          DEFAULT_MOVIE_WIFI_AUTO_RECORDING_OPTION);
	SysSetFlag(FL_NetWorkMode,                  DEFAULT_WIFI_MODE); // Reset To Wi-Fi mode to AP mode.
    SysSetFlag(FL_WIFI,        					DEFAULT_WIFI);
    SysSetFlag(FL_WIFI_AUTO,   					DEFAULT_WIFI_AUTO);
    SysSetFlag(FL_WIFI_BAND,   					DEFAULT_WIFI_BAND);
#endif

	SysSetFlag(FL_FW_UI_RESET, 					DEFAULT_FW_UI_RESET);
    SysSetFlag(FL_EDOG_OVERSPEED_ALARM, DEFAULT_EDOG_OVERSPEED_ALARM);

    //#NT#Check SSID and passphrase and reset it if illegal.
    if (currentInfo.strSSID[0] == 0xFF) {
        memset(currentInfo.strSSID, '\0', NVT_WSC_MAX_SSID_LEN);
    }
    if (currentInfo.strPASSPHRASE[0] == 0xFF) {
        memset(currentInfo.strPASSPHRASE, '\0', NVT_MAX_WEP_KEY_LEN);
    }
    //5G
    if (currentInfo.strSSID_5G[0] == 0xFF) {
        memset(currentInfo.strSSID_5G, '\0', NVT_WSC_MAX_SSID_LEN);
    }
	SysSetFlag(FL_ETHCAM_TX_IP_ADDR, 			DEFAULT_ETHCAM_TX_IP_ADDR);

	SysSetFixedFlag();

}

void SysExeMenuSettingFuncs(void)
{
#if (PHOTO_MODE==ENABLE)
	/*--- Photo ---*/
	Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_QUALITY,        1,  SysGetFlag(FL_QUALITY));
	Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_ISO,            1,  SysGetFlag(FL_ISO));
	Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_EV,             1,  SysGetFlag(FL_EV));
    Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_EV2,            1,  SysGetFlag(FL_EV2));
	Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_WB,             1,  SysGetFlag(FL_WB));
	Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_COLOR,          1,  SysGetFlag(FL_COLOR_EFFECT));
	Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_METERING,       1,  SysGetFlag(FL_METERING));
	Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_FD,             1,  SysGetFlag(FL_FD));
	Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_CAPTURE_SIZE,   1,  SysGetFlag(FL_PHOTO_SIZE));
	Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_SCENEMODE,      1,  SysGetFlag(FL_SCENE));
	Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_SHARPNESS,      1,  SysGetFlag(FL_SHARPNESS));
	Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_SATURATION,     1,  SysGetFlag(FL_SATURATION));
	Ux_SendEvent(&CustomPhotoObjCtrl, NVTEVT_EXE_DUALCAM,        1,  SysGetFlag(FL_DUAL_CAM));
#endif
#if (MOVIE_MODE==ENABLE)
	/*--- Movie ---*/
	Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIEQUALITY,   1,      SysGetFlag(FL_MOVIE_QUALITY));
	Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIECOLOR,     1,      SysGetFlag(FL_MOVIE_COLOR));
	Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_DUALCAM,        1,      SysGetFlag(FL_DUAL_CAM));

	/* Cyclic recording/record with mute or sound/DateImptint/Motion Detect */
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_CYCLIC_REC,          1,  SysGetFlag(FL_MOVIE_CYCLIC_REC));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOTION_DET,          1,  SysGetFlag(FL_MOVIE_MOTION_DET));
    //Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_PARKING_MOTION_DET,  1,  SysGetFlag(FL_PARKING_MOTION_DET));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_DATE_IMPRINT,  1,  SysGetFlag(FL_MOVIE_DATEIMPRINT));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_AUDIO,         1,  SysGetFlag(FL_MOVIE_AUDIO));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_VOICE,         1,  SysGetFlag(FL_MOVIE_VOICE));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_MCTF,          1,  SysGetFlag(FL_MovieMCTFIndex));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_GSENSOR,             1,  SysGetFlag(FL_GSENSOR));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_PARKING_GSENSOR,     1,  SysGetFlag(FL_PARKING_GSENSOR));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_SENSOR_ROTATE, 1,  SysGetFlag(FL_MOVIE_SENSOR_ROTATE));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_IR_CUT,        1,  SysGetFlag(FL_MOVIE_IR_CUT));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_PROTECT_AUTO,  1,  SysGetFlag(FL_MOVIE_URGENT_PROTECT_AUTO));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_PROTECT_MANUAL, 1,  SysGetFlag(FL_MOVIE_URGENT_PROTECT_MANUAL));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_LDWS,          1,  SysGetFlag(FL_MOVIE_LDWS));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_FCW,           1,  SysGetFlag(FL_MOVIE_FCW));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_CODEC,         1,  SysGetFlag(FL_MOVIE_CODEC));
	Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_WDR,           1,  SysGetFlag(FL_MOVIE_WDR));
    Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_BITRATE,       1,  SysGetFlag(FL_MOVIE_BITRATE));
#endif
	/*--- Setup ---*/
	Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_LANGUAGE,      1,  SysGetFlag(FL_LANGUAGE));
#if (TV_FUNC == ENABLE)
	Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_TVFORMAT,      1,  SysGetFlag(FL_TV_MODE));
#endif
	Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_POWEROFF,      1,  SysGetFlag(FL_AUTO_POWER_OFF));
	Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_LCDOFF,        1,  SysGetFlag(FL_LCD_OFF));
	Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_BEEPKEY,       1,  SysGetFlag(FL_BEEP));
	Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_DISPLAY,       1,  SysGetFlag(FL_LCD_DISPLAY));
	Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_FREQ,          1,  SysGetFlag(FL_FREQUENCY));
	Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_DATEFORMAT,    1,  SysGetFlag(FL_DATE_FORMAT));
    Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_TIMEZONE,      1,  SysGetFlag(FL_TIME_ZONE));
    Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_SPEED_UNIT,    1,  SysGetFlag(FL_SPEED_UNIT));
    Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_LED,           1,  SysGetFlag(FL_LED));
    Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_PARKING_MODE,  1,  SysGetFlag(FL_PARKING_MODE));
    Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_ENTER_PARKING_TIMER, 1, SysGetFlag(FL_ENTER_PARKING_TIMER));
    Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_VOLUME,        1,  SysGetFlag(FL_VOLUME));//
    Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_WIFI_OFF_ON,   1,  SysGetFlag(FL_WIFI));

#if (WIFI_FUNC==ENABLE)
	/*--- Wi-Fi ---*/
	if (UI_GetData(FL_NetWorkMode) == NET_AP_MODE || UI_GetData(FL_NetWorkMode) == NET_WPS_AP_PBC_MODE) {
		if (currentInfo.strSSID[0] != 0) { // Load SSID if existed.
			Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_WIFI_SET_SSID, 1, currentInfo.strSSID);
		}

		if (currentInfo.strPASSPHRASE[0] != 0) { // Load PASSPHARSE if existed.
			Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_WIFI_SET_PASSPHRASE, 1, currentInfo.strPASSPHRASE);
		}

        //5G
		if (currentInfo.strSSID_5G[0] != 0) { // Load SSID if existed.
			Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_WIFI_SET_SSID_5G, 1, currentInfo.strSSID_5G);
		}

        Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_WIFI_MODE, 1, SysGetFlag(FL_NetWorkMode));
	} else if (UI_GetData(FL_NetWorkMode) == NET_STATION_MODE) {
		char szTemp[NVT_WSC_MAX_SSID_LEN + NVT_MAX_WEP_KEY_LEN] = {0};

		if (currentInfo.strSSID_hotspot_1[0] && currentInfo.strPASSPHRASE_hotspot_1[0]) { // Load SSID and passphrase if existed.
			snprintf(szTemp, NVT_WSC_MAX_SSID_LEN + NVT_MAX_WEP_KEY_LEN, "%s:%s", currentInfo.strSSID_hotspot_1, currentInfo.strPASSPHRASE_hotspot_1);
			Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_WIFI_SEND_SSID_PASSPHRASE, 1, szTemp);
		}
	}
#endif
}

void Photo_SetUserIndex(PHOTO_USR_ITEM_T uiItem, UINT32 uhIndex)
{
	DBG_IND("Photo_SetUserIndex: Item %d, index %d\r\n", uiItem, uhIndex);

	if (UI_GetData(FL_IsInitSettingFlag) == FALSE) {
		/* Update Photo Mode user defined settings data while init setting flag is off */
		switch (uiItem) {
		case PHOTO_USR_FLASH:
			currentInfo.ubFlashIndex = uhIndex;
			break;
		case PHOTO_USR_EV:
			currentInfo.ubEVIndex = uhIndex;
			break;
		case PHOTO_USR_AFWINDOW:
			currentInfo.ubAFWindowIndex = uhIndex;
			break;
		case PHOTO_USR_AFBEAM:
			currentInfo.ubAFBeamIndex = uhIndex;
			break;
		case PHOTO_USR_METERING:
			currentInfo.ubAEmode = uhIndex;
			break;
		case PHOTO_USR_TIMELAPSE:
			currentInfo.ubTimelapseIndex = uhIndex;
			break;
		case PHOTO_USR_CONTSHOT:
			currentInfo.ubContshotIndex = uhIndex;
			break;
		case PHOTO_USR_CONTAF:
			currentInfo.ubContAF = uhIndex;
			break;
		case PHOTO_USR_QREVIEW:
			currentInfo.ubQviewIndex = uhIndex;
			break;
		case PHOTO_USR_DZOOMSTATUS:
			currentInfo.ubDzoom      = uhIndex;
			break;
		case PHOTO_USR_SLOWSHUTTER:
			currentInfo.ubSlowShutter = uhIndex;
			break;
		case PHOTO_USR_DATEIMPRINT:
			currentInfo.ubDatePrint = uhIndex;
			break;
		case PHOTO_USR_BLINK:
			currentInfo.ubBlinkDet = uhIndex;
			break;
		case PHOTO_USR_PANDET:
			currentInfo.ubPanModeIndex = uhIndex;
			break;
		case PHOTO_USR_COLOR:
			currentInfo.ubColorIndex = uhIndex;
			break;
		case PHOTO_USR_SIZE:
			currentInfo.ubSizeIndex = uhIndex;
			break;
		case PHOTO_USR_QUALITY:
			currentInfo.ubQualityIndex = uhIndex;
			break;
		case PHOTO_USR_ISO:
			currentInfo.ubISOIndex = uhIndex;
			break;
		case PHOTO_USR_WB:
			currentInfo.ubWBIndex = uhIndex;
			break;
		//#NT#Store FD index after power off
		case PHOTO_USR_FD:
			currentInfo.ubFDIndex = uhIndex;
			break;
		/*
		case PHOTO_USR_SATURATION:
		    currentInfo.ubSaturationIndex = uhIndex;
		    break;
		*/
		case PHOTO_USR_SHARPNESS:
			currentInfo.ubSharpnessIndex = uhIndex;
			break;
		/*
		case PHOTO_USR_CONTRAST:
		    currentInfo.ubContrastIndex = uhIndex;
		    break;
		*/
		case PHOTO_USR_DISPMODE:
			currentInfo.ubPhotoDispMode = uhIndex;
			break;
		default:
			DBG_ERR("Photo_SetUserIndex: Unknown item %d\r\n", uiItem);
			break;
		}
	} else {
		/* While init setting flag is on, do NOT update Photo Mode user defined settings data */
		DBG_IND("Photo_SetUserIndex: Init setting flag is ON, no update item %d\r\n", uiItem);
	}
}

UINT32 Photo_GetUserIndex(PHOTO_USR_ITEM_T uiItem)
{
	UINT32 uhUserIndex;

	switch (uiItem) {
	case PHOTO_USR_FLASH:
		uhUserIndex = currentInfo.ubFlashIndex;
		break;
	case PHOTO_USR_EV:
		uhUserIndex = currentInfo.ubEVIndex;
		break;
	case PHOTO_USR_AFWINDOW:
		uhUserIndex = currentInfo.ubAFWindowIndex;
		break;
	case PHOTO_USR_AFBEAM:
		uhUserIndex = currentInfo.ubAFBeamIndex;
		break;
	case PHOTO_USR_METERING:
		uhUserIndex = currentInfo.ubAEmode;
		break;
	case PHOTO_USR_TIMELAPSE:
		uhUserIndex = currentInfo.ubTimelapseIndex;
		break;
	case PHOTO_USR_CONTSHOT:
		uhUserIndex = currentInfo.ubContshotIndex;
		break;
	case PHOTO_USR_CONTAF:
		uhUserIndex = currentInfo.ubContAF;
		break;
	case PHOTO_USR_QREVIEW:
		uhUserIndex = currentInfo.ubQviewIndex;
		break;
	case PHOTO_USR_DZOOMSTATUS:
		uhUserIndex = currentInfo.ubDzoom;
		break;
	case PHOTO_USR_SLOWSHUTTER:
		uhUserIndex = currentInfo.ubSlowShutter;
		break;
	case PHOTO_USR_DATEIMPRINT:
		uhUserIndex = currentInfo.ubDatePrint;
		break;
	case PHOTO_USR_BLINK:
		uhUserIndex = currentInfo.ubBlinkDet;
		break;
	case PHOTO_USR_PANDET:
		uhUserIndex = currentInfo.ubPanModeIndex;
		break;
	case PHOTO_USR_COLOR:
		uhUserIndex = currentInfo.ubColorIndex;
		break;
	case PHOTO_USR_SIZE:
		uhUserIndex = currentInfo.ubSizeIndex;
		break;
	case PHOTO_USR_QUALITY:
		uhUserIndex = currentInfo.ubQualityIndex;
		break;
	case PHOTO_USR_ISO:
		uhUserIndex = currentInfo.ubISOIndex;
		break;
	case PHOTO_USR_WB:
		uhUserIndex = currentInfo.ubWBIndex;
		break;
	//#NT#Store FD index after power off
	case PHOTO_USR_FD:
		uhUserIndex = currentInfo.ubFDIndex;
		break;
	/*
	case PHOTO_USR_SATURATION:
	    uhUserIndex = currentInfo.ubSaturationIndex;
	    break;
	*/
	case PHOTO_USR_SHARPNESS:
		uhUserIndex = currentInfo.ubSharpnessIndex;
		break;
	/*
	case PHOTO_USR_CONTRAST:
	    uhUserIndex = currentInfo.ubContrastIndex;
	    break;
	*/

	case PHOTO_USR_DISPMODE:
		uhUserIndex = currentInfo.ubPhotoDispMode;
		break;

	default:
		uhUserIndex = 0xFFFF;
		DBG_ERR("Photo_GetUserIndex: Unknown item %d\r\n", uiItem);
		break;
	}
	DBG_IND("Photo_GetUserIndex: Get item %d user index %d\r\n", uiItem, uhUserIndex);

	return uhUserIndex;
}

#if (TV_FUNC == ENABLE)
extern DX_HANDLE gDevTVObj;
#endif
#if (HDMI_FUNC == ENABLE)
extern DX_HANDLE gDevHDMIObj;
#endif

PLUG_DEV KeyScan_GetPlugDev(void)
{
	UINT32 r = PLUG_OFF;
#if ((TV_FUNC == ENABLE) || (HDMI_FUNC == ENABLE))
	DX_HANDLE uiDevObj1, uiDevObj2;

	uiDevObj1 = (DX_HANDLE)GxVideo_GetDevice(DOUT1);
	uiDevObj2 = (DX_HANDLE)GxVideo_GetDevice(DOUT2);
#endif
#if (TV_FUNC == ENABLE)
	if (uiDevObj1 == gDevTVObj || uiDevObj2 == gDevTVObj) {
		r = PLUG_TV;
	}
#endif
#if (HDMI_FUNC == ENABLE)
	if (uiDevObj1 == gDevHDMIObj || uiDevObj2 == gDevHDMIObj) {
		r = PLUG_HDMI;
	}
#endif
	return r;
}
#if (USE_DCF==ENABLE)
//-----------------------------------------------------------------------------
// Update DCF Folder/File name Utility
//-----------------------------------------------------------------------------
static BOOL FlowDCF_GetNextDCFFolderID(UINT32 *pDirID)
{
	BOOL ret = FALSE;
	UINT32 uiCurDCFID, uiDirCount;
	SDCFDIRINFO dirinfo;

	uiCurDCFID = DCF_GetDBInfo(DCF_INFO_CUR_DIR_ID);
	uiDirCount = 0;

	do {
		if (uiCurDCFID == MAX_DCF_DIR_NUM) {
			uiCurDCFID = MIN_DCF_DIR_NUM;
		} else {
			uiCurDCFID++;
		}

		uiDirCount++;
		if (!DCF_GetDirInfo(uiCurDCFID, &dirinfo)) {
			*pDirID = uiCurDCFID;
			ret = TRUE;
			break;
		}
	} while (uiDirCount == (MAX_DCF_DIR_NUM - MIN_DCF_DIR_NUM));


	return ret;
}

void FlowDCF_UpdateName(void)
{
	CHAR FolderName[6] = "MEDIA";
	CHAR FileName[5] = "PTDC";
	char DCFpathname[0x20];
	UINT32    uiAddr, uiNextDCFID;
	CHAR filePath[DCF_FULL_FILE_PATH_LEN];
    struct tm Curr_DateTime;
    Curr_DateTime = HwClock_GetTime(TIME_ID_CURRENT);

	snprintf(FolderName, sizeof(FolderName), "%1d%02d%02d", Curr_DateTime.tm_year % 0x0A, Curr_DateTime.tm_mon,Curr_DateTime.tm_mday);
	snprintf(FileName, sizeof(FileName), "%02d%02d", Curr_DateTime.tm_hour,  Curr_DateTime.tm_min);

	uiAddr = DCF_GetDBInfo(DCF_INFO_DIR_FREE_CHARS);
	memcpy((UB *)DCFpathname, (UB *)uiAddr, DCF_DIR_NAME_LEN);
	if (strncmp(DCFpathname, FolderName, 5)) {
		if (FlowDCF_GetNextDCFFolderID(&uiNextDCFID) == TRUE) {
			DCF_SetDirFreeChars(FolderName);
			DCF_MakeDirPath(uiNextDCFID, filePath);
			if (FileSys_MakeDir(filePath) != FST_STA_OK) {
				DBG_ERR("MakeDir %s Fail\r\n", filePath);
			}
			DCF_SetNextID(uiNextDCFID, MIN_DCF_FILE_NUM);
		} else {
			debug_msg("DCF Folder full\r\n");
		}
	}

	// update DCF file name in current RTC time
	DCF_SetFileFreeChars(DCF_FILE_TYPE_ANYFORMAT, FileName);

}
#endif
