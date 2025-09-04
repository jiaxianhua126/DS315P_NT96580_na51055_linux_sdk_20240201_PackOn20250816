/**
    Copyright   Novatek Microelectronics Corp. 2007.  All rights reserved.

    @file       BuildDateInfo.c
    @ingroup    mIPRJAPCfg

    @brief      Project source build time information
                Project source build time information

    @note       The project source build time info will be updated every time you build the image.

    @date       2007/11/06
*/

/** \addtogroup mIPRJAPCfg*/
//@{

#include <stdio.h>
#include "ProjectInfo.h"
#include "PrjCfg.h"
#include <string.h>
#include "EthCam/EthCamSocket.h"
#include "bin_info.h"
//-----------------------------------------------------------------------------
// FW info
//-----------------------------------------------------------------------------
//FW updtae FW need access external fw version via versioninfo.s offset 0x000000A8
//#NT#2016/08/17#Niven Cho -begin
//#NT#add _L to indicate linux version
#if defined(_CPU2_LINUX_)
char gFWExternalVersion[33] = FW_VERSION_NUM"_L";
#else
char gFWExternalVersion[33] = "";//FW_VERSION_NUM;
#endif
char gPrjCheckInDate[33] = "20220506-sdk";
//#NT#2016/08/17#Niven Cho -end

#if defined(_NVT_ETHREARCAM_RX_)
extern char gFWEthcamVersion[ETHCAM_PATH_ID_MAX][30];
char *Prj_GetEthCam1VersionString(void)
{
	return gFWEthcamVersion[ETHCAM_PATH_ID_1];
}
char *Prj_GetEthCam2VersionString(void)
{
    return gFWEthcamVersion[ETHCAM_PATH_ID_2];
}
#endif

//-----------------------------------------------------------------------------
// User define info
//-----------------------------------------------------------------------------
static char gVersion[9];
static char gModelName[9];
static char gReleaseDate[9];
//extern UINT32 ProjectCode;
//extern UINT32 VersionNumber;
//extern UINT32 ReleaseDate;

//Please modify VersionInfo.s :: ProjectCode
char *Prj_GetModelInfo()
{
	//strncpy(gModelName, (char *)&ProjectCode, 9);
	gModelName[8] = 0;
	return gModelName;
}

//Please modify VersionInfo.s :: VersionNumber
char *Prj_GetVerInfo()
{
	//strncpy(gVersion, (char *)&VersionNumber, 9);
	gVersion[8] = 0;
	return gVersion;
}

//Please modify VersionInfo.s :: ReleaseDate
char *Prj_GetReleaseDate()
{
	//strncpy(gReleaseDate, (char *)&ReleaseDate, 9);
	gReleaseDate[8] = 0;
	return gReleaseDate;
}

//-----------------------------------------------------------------------------
// Compiler-time info
//-----------------------------------------------------------------------------
//#include "ProjectInfo.cfg"

// C standard format: Mmm dd yyyy HH:MM:SS (ex. Nov 06 2007 11:15:11)
static CHAR gPrjBuildDateStd[] = __DATE__ ", " __TIME__;

// User defined format: yyyy/mm/dd HH:MM:SS (ex. 2007/11/06 11:15:11)
static CHAR gPrjBuildDateUser[32];

// Retrieve year info
#define OS_YEAR     ((((__DATE__ [7] - '0') * 10 + (__DATE__ [8] - '0')) * 10 \
					  + (__DATE__ [9] - '0')) * 10 + (__DATE__ [10] - '0'))

// Retrieve month info
#define OS_MONTH    (__DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 1 : 6) \
					 : __DATE__ [2] == 'b' ? 2 \
					 : __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 3 : 4) \
					 : __DATE__ [2] == 'y' ? 5 \
					 : __DATE__ [2] == 'l' ? 7 \
					 : __DATE__ [2] == 'g' ? 8 \
					 : __DATE__ [2] == 'p' ? 9 \
					 : __DATE__ [2] == 't' ? 10 \
					 : __DATE__ [2] == 'v' ? 11 : 12)

// Retrieve day info
#define OS_DAY      ((__DATE__ [4] == ' ' ? 0 : __DATE__ [4] - '0') * 10 \
					 + (__DATE__ [5] - '0'))

// Retrieve hour info
#define OS_HOUR     ((__TIME__ [0] - '0') * 10 + (__TIME__ [1] - '0'))

// Retrieve minute info
#define OS_MINUTE   ((__TIME__ [3] - '0') * 10 + (__TIME__ [4] - '0'))

// Retrieve second info
#define OS_SECOND   ((__TIME__ [6] - '0') * 10 + (__TIME__ [7] - '0'))




//-----------------------------------------------------------------------------
// Project build time info, C standard (US) format
//-----------------------------------------------------------------------------
char *Prj_GetBuildDateStd(void)
{
	return gPrjBuildDateStd;
}

//-----------------------------------------------------------------------------
// Project build time info, user defined format
//-----------------------------------------------------------------------------
char *Prj_GetBuildDateUser(void)
{
	snprintf(gPrjBuildDateUser, sizeof(gPrjBuildDateUser) - 1, "%d/%02d/%02d, %s", OS_YEAR, OS_MONTH, OS_DAY, __TIME__);
	return gPrjBuildDateUser;
}
UINT16 Prj_GetBuildYear(void)
{
    return OS_YEAR;
}
UINT8 Prj_GetBuildMonth(void)
{
    return OS_MONTH;
}
UINT8 Prj_GetBuildDay(void)
{
    return OS_DAY;
}

//-----------------------------------------------------------------------------
// Project version string
//-----------------------------------------------------------------------------
char *Prj_GetCheckinDate(void)
{
#if (FW_VERSION_RELEASE == ENABLE)
	MODELEXT_HEADER *head = NULL;
	BININFO *pBinInfo = (BININFO *)Dx_GetModelExtCfg(MODELEXT_TYPE_BIN_INFO, &head);
	return pBinInfo->fw.FwInfo_1;
#else
	return gPrjCheckInDate;
#endif
}

static char gPrjGitRevision[9]="1";

char *Prj_GetGitRevision(void)
{
	#if defined(_GIT_REVISION_)
	snprintf(gPrjGitRevision, sizeof(gPrjGitRevision), "%s", _GIT_REVISION_);
	#else
	//DBG_DUMP("not defined _GIT_REVISION_\r\n");
	#endif
	return gPrjGitRevision;
}

char *Prj_GetVersionString(void)
{
    snprintf(gFWExternalVersion,sizeof(gFWExternalVersion) - 1, "%s.%s.%04d%02d%02d", FW_CUSTOMER_MODEL, FW_CUSTOMER_VERSION_NUM, Prj_GetBuildYear(), Prj_GetBuildMonth(), Prj_GetBuildDay());
	return gFWExternalVersion;
}

//@}
