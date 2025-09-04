#include "PrjInc.h"
#include "PrjCfg.h"
#include "UIResource.h"
//#NT#2010/10/15#Niven Cho -begin
//#NT#CMP_LANG
static STRING_TABLE g_LangCurrTbl = 0;
//#NT#2010/10/15#Niven Cho -end
//MOVIE_SIZE_TAG
#if  (!defined(COUNTRY_JP))
char *gUserStr[STRID_USER_END - STRID_USER_START] = {
	"MCTF",
	"Edge",
	"NR",
	"WiFi/ETH",
	"6400",
	"12800",
	//single
	"4K P50",//"UHD P50",
	"3840x2160P 30fps",//"UHD P30",
	"4K P24",//"UHD P24",
	"2.7K P60",
	"2592x1944P 30fps",
    "2560x1600P 30fps",
	"2560x1440P 80fps",//"QHD P80",
	"2560x1440P 60fps",//"QHD P60",
	"2560x1440P 30fps",//"QHD P30",
	"2560x1080P 60fps",
	"2560x1080P 30fps",
	"2304x1296P 60fps",//"3MHD P60",
	"2304x1296P 30fps",//"3MHD P30",
	"1920x1080P 120fps",//"FHD P120",
	"1920x1080P 96fps",//"FHD P96",
	"1920x1080P 60fps",//"FHD P60",
	"1920x1080P 30fps",//"FHD P30",
	"1280x720P 240fps",//"HD P240",
	"1280x720P 120fps",//"HD P120",
	"1280x720P 60fps",//"HD P60",
	"1280x720P 30fps",//"HD P30",
	"WVGA P30",
	"VGA P240",
	"VGA P30",
	"QVGA P30",
	//dual
	"UHD P30+FHD P30",
	"QHD P30+HD P30",
	"1440P30+1080P30",
	"3MHD P30+HD P30",
	"1080P30+1080P30",
	"1080P60+1080P60",
	"FHD P30+HD P30",
	"FHD P30+WVGA P30",
	//multi
	"FHD P30 x3",
	"QHD P30+FHD P30 x2",
	"FHD P30 x4",
	//clone
	"FHD P30+FHD P30",
	"FHD P30+HD P30",
	"QHD P30+WVGA P30",
	"3MHD P30+WVGA P30",
	"FHD P60+WVGA P30",
	"FHD P60+VGA P30", //640x360
	"FHD P30+WVGA P30",
	"2048x2048 P30 + 480x480 P30",
	"Both2",
	"SideBySide",
	"Burst 30",
	"5M 2992x1696",
	//"Codec",
	"MJPG",
	//"H264",
	//"H265",
	"Livestream",
	"QR Code Scan",
	"Connect to hotspot...",
	"Not Find Hotspot",
	"Hotspot is broken",
	"RSC effect",
	"SUPER HIGH",
	//"2.4GHz",
	//"5.2GHz",
	//"5.8GHz",
	//"EIS"
};
#else
char *gUserStr[STRID_USER_END - STRID_USER_START] = {
	"MCTF",
	"Edge",
	"NR",
	"WiFi/ETH",
	"6400",
	"12800",
	//single
	"4K P50",//"UHD P50",
	"3840x2160P 27.5fps",//"UHD P30",
	"4K P24",//"UHD P24",
	"2.7K P55",
	"2592x1944P 27.5fps",
    "2560x1600P 27.5fps",
	"2560x1440P 80fps",//"QHD P80",
	"2560x1440P 55fps",//"QHD P60",
	"2560x1440P 27.5fps",//"QHD P30",
	"2560x1080P 55fps",
	"2560x1080P 27.5fps",
	"2304x1296P 55fps",//"3MHD P60",
	"2304x1296P 27.5fps",//"3MHD P30",
	"1920x1080P 110fps",//"FHD P120",
	"1920x1080P 96fps",//"FHD P96",
	"1920x1080P 55fps",//"FHD P60",
	"1920x1080P 27.5fps",//"FHD P30",
	"1280x720P 240fps",//"HD P240",
	"1280x720P 110fps",//"HD P120",
	"1280x720P 55fps",//"HD P60",
	"1280x720P 27.5fps",//"HD P30",
	"WVGA P30",
	"VGA P240",
	"VGA P30",
	"QVGA P30",
	//dual
	"UHD P30+FHD P30",
	"QHD P30+HD P30",
	"1440P30+1080P30",
	"3MHD P30+HD P30",
	"1080P30+1080P30",
	"1080P60+1080P60",
	"FHD P30+HD P30",
	"FHD P30+WVGA P30",
	//multi
	"FHD P30 x3",
	"QHD P30+FHD P30 x2",
	"FHD P30 x4",
	//clone
	"FHD P30+FHD P30",
	"FHD P30+HD P30",
	"QHD P30+WVGA P30",
	"3MHD P30+WVGA P30",
	"FHD P60+WVGA P30",
	"FHD P60+VGA P30", //640x360
	"FHD P30+WVGA P30",
	"2048x2048 P30 + 480x480 P30",
	"Both2",
	"SideBySide",
	"Burst 30",
	"5M 2992x1696",
	//"Codec",
	"MJPG",
	//"H264",
	//"H265",
	"Livestream",
	"QR Code Scan",
	"Connect to hotspot...",
	"Not Find Hotspot",
	"Hotspot is broken",
	"RSC effect",
	"SUPER HIGH",
	//"2.4GHz",
	//"5.2GHz",
	//"5.8GHz",
	//"EIS"
};

#endif
char *UIRes_GetUserString(UINT32 TxtId)
{
	return gUserStr[TxtId - STRID_USER_START];
}

///////////////////////////////////////////////////////////////////////////////
//
//  String (LANG)

//!!!POOL_ID_LANG need to sync current_lang_id for load language correct
#if(_LANG_STORE_ == _INSIDECODE_)
//#NT#2010/10/15#Niven Cho -begin
//#NT#CMP_LANG
UINT32 Get_LanguageValue(UINT32 uhIndex)
{
#if (DRAM_SIZE_64MB_DISP_OFF==DISABLE)

	switch (uhIndex) {
	case LANG_EN:
		g_LangCurrTbl = (STRING_TABLE)&gDemoKit_String_EN;
		break;
#if (_BOARD_DRAM_SIZE_ > 0x04000000)

	case LANG_DE:
		g_LangCurrTbl = (STRING_TABLE)&gDemoKit_String_DE;
		break;
	case LANG_FR:
		g_LangCurrTbl = (STRING_TABLE)&gDemoKit_String_FR;
		break;
	case LANG_ES:
		g_LangCurrTbl = (STRING_TABLE)&gDemoKit_String_ES;
		break;
	case LANG_IT:
		g_LangCurrTbl = (STRING_TABLE)&gDemoKit_String_IT;
		break;
	case LANG_PO:
		g_LangCurrTbl = (STRING_TABLE)&gDemoKit_String_PO;
		break;
	case LANG_TC:
		g_LangCurrTbl = (STRING_TABLE)&gDemoKit_String_TC;
		break;
	case LANG_SC:
		g_LangCurrTbl = (STRING_TABLE)&gDemoKit_String_SC;
		break;
	case LANG_RU:
		g_LangCurrTbl = (STRING_TABLE)&gDemoKit_String_RU;
		break;
	case LANG_JP:
		g_LangCurrTbl = (STRING_TABLE)&gDemoKit_String_JP;
		break;
#endif
	}
#endif
	return g_LangCurrTbl;
}
//#NT#2010/10/15#Niven Cho -end
#endif
UINT32 Get_LanguageTable(void)
{
//#NT#2010/10/15#Niven Cho -begin
//#NT#CMP_LANG
	if (g_LangCurrTbl == 0) {
		g_LangCurrTbl = (STRING_TABLE)&gDemoKit_String_EN;
	}
	return g_LangCurrTbl;
//#NT#2010/10/15#Niven Cho -end
}
