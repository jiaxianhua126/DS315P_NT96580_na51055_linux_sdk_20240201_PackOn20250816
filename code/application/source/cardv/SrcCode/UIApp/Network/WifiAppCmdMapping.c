#include "WifiAppCmdMapping.h"
#include "UIWnd/UIFlow.h"
#include "DxInput.h"

#define MOVE_SIZE_SUPPORT       ENABLE //DISABLE

WIFIAPPINDEXMAP photoSizeMap[] = {
	{PHOTO_SIZE_12M, "12M"  },
	{PHOTO_SIZE_10M, "10M"  },
	{PHOTO_SIZE_8M, "8M"   },
	{PHOTO_SIZE_5M, "5M"   },
	{PHOTO_SIZE_3M, "3M"   },
	{PHOTO_SIZE_VGA, "VGA"  },
	{INDEX_END, 0}
};
#if MOVE_SIZE_SUPPORT
WIFIAPPINDEXMAP movieSizeMap[] = {
	//{MOVIE_SIZE_FRONT_2880x2160P24, "2880x2160P24"},           //UHD P24
	{MOVIE_SIZE_FRONT_2560x1440P60, "1440P60 2560x1440"},           //QHD P30
	{MOVIE_SIZE_FRONT_2560x1440P30, "1440P30 2560x1440"},           //QHD P30
	{MOVIE_SIZE_FRONT_2304x1296P60, "1296P60 2304x1296"},           //3MHD P30
	{MOVIE_SIZE_FRONT_2304x1296P30, "1296P30 2304x1296"},           //FHD
	{MOVIE_SIZE_FRONT_1920x1080P60, "1080P60 1920x1080"},           //FHD
	{MOVIE_SIZE_FRONT_1920x1080P30, "1080P30 1920x1080"},           //FHD
	/*
	{MOVIE_SIZE_FRONT_1280x720P120, "1280x720P120"},           //HD
	{MOVIE_SIZE_FRONT_1280x720P60, "1280x720P60"},             //HD
	{MOVIE_SIZE_FRONT_1280x720P30, "1280x720P30"},             //HD
	{MOVIE_SIZE_FRONT_848x480P30, "848x480P30"},               //WVGA
	{MOVIE_SIZE_FRONT_640x480P240, "640x480P240"},             //VGA
	{MOVIE_SIZE_FRONT_640x480P30, "640x480P30"},               //VGA
	{MOVIE_SIZE_FRONT_320x240P30, "320x240P30"},               //QVGA
	{MOVIE_SIZE_DUAL_1920x1080P30_1920x1080P30, "1920x1080P30_1920x1080P30"}, //FHD FHD
	{MOVIE_SIZE_DUAL_1920x1080P30_1280x720P30, "1920x1080P30_1280x720P30"}, //FHD HD
	{MOVIE_SIZE_DUAL_1920x1080P30_848x480P30, "1920x1080P30_848x480P30"}, //FHD WVGA
	*/
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP movieSizeMap_EthCam[] = {
	{MOVIE_SIZE_FRONT_2560x1440P60, "1440P60+1080P30"},           //QHD P30
	{MOVIE_SIZE_FRONT_2560x1440P30, "1440P30+1080P30"},           //QHD P30
	{MOVIE_SIZE_FRONT_2304x1296P60, "1296P60+1080P30"},           //QHD P30
	{MOVIE_SIZE_FRONT_2304x1296P30, "1296P30+1080P30"},           //QHD P30
	{MOVIE_SIZE_FRONT_1920x1080P60, "1080P60+1080P30"},           //FHD
	{MOVIE_SIZE_FRONT_1920x1080P30, "1080P30+1080P30"},           //FHD
	{INDEX_END, 0}
};
#endif

WIFIAPPINDEXMAP DualCamMap[] = {
	{DUALCAM_FRONT,  "Front Camera"  },
	{DUALCAM_BEHIND, "Rear Camera"  },
	{DUALCAM_BOTH,   "Dual View" },
	//{DUALCAM_BOTH2,  "Dual View2" },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP cyclicRecMap[] = {
	//{MOVIE_CYCLICREC_OFF,  "OFF"  },
	{MOVIE_CYCLICREC_1MIN, "1MIN"  },
	//{MOVIE_CYCLICREC_2MIN, "2MIN"  },
	{MOVIE_CYCLICREC_3MIN, "3MIN"  },
	{MOVIE_CYCLICREC_5MIN, "5MIN"  },
	//{MOVIE_CYCLICREC_10MIN, "10MIN" },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP WDRMap[] = {
	{MOVIE_WDR_OFF, "OFF"  },
	{MOVIE_WDR_ON, "ON"  },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP HDRMap[] = {
	{MOVIE_HDR_OFF, "OFF"  },
	{MOVIE_HDR_ON, 	"ON"  },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP EVMap[] = {
	//{EV_P20, "+2.0"},
	//{EV_P16, "+5/3"},
	//{EV_P13, "+4/3"},
	{EV_N10, "-1.0"},
	{EV_N06, "-2/3"},	
	{EV_N03, "-1/3"},
	{EV_00,  "+0.0"},	
	{EV_P03, "+1/3"},
	{EV_P06, "+2/3"},	
	{EV_P10, "+1.0"},
	//{EV_N13, "-4/3"},
	//{EV_N16, "-5/3"},
	//{EV_N20, "-2.0"},
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP motionDetMap[] = {
	{MOVIE_MOTIONDET_OFF, "OFF"  },
	{MOVIE_MOTIONDET_ON, "ON"  },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP audioMap[] = {
	{MOVIE_AUDIO_OFF, "OFF"  },
	{MOVIE_AUDIO_ON, "ON"  },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP dateImprintMap[] = {
	{MOVIE_DATEIMPRINT_OFF, "OFF"  },
	{MOVIE_DATEIMPRINT_ON, "ON"  },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP gSensorMap[] = {
    #if 0
	{GSENSOR_OFF, "OFF"  },
	{GSENSOR_LOW, "LOW"  },
	{GSENSOR_MED, "MED"  },
	{GSENSOR_HIGH, "HIGH"  },
	#else
	{GSENSOR_OFF,  "OFF"  },
	{GSENSOR_LOW,  "Low"  },
	{GSENSOR_MED,  "Medium"  },
	{GSENSOR_HIGH, "High"  },
    #endif
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP wifiAutoRecMap[] = {
	{WIFI_AUTO_RECORDING_OFF, "OFF" },
	{WIFI_AUTO_RECORDING_ON, "ON"  },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP powerOffMap[] = {
	{POWER_ON,    "ON"},
	{POWER_1MIN,  "1MIN"},
	{POWER_2MIN,  "2MIN"},
	{POWER_3MIN,  "3MIN"},
	{POWER_5MIN,  "5MIN"},
	{POWER_10MIN, "10MIN"},
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP langMap[] = {
#if (!defined(COUNTRY_JP))
	{LANG_TC,  "TC"},	
	{LANG_SC,  "SC"},	
	{LANG_EN,  "EN"},
#else
	{LANG_JP,  "JP"},
	{LANG_SC,  "SC"},	
	{LANG_EN,  "EN"},
#endif
	//{LANG_RU,  "RU"},
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP TVMap[] = {
	{TV_MODE_NTSC, "NTSC"},
	{TV_MODE_PAL,  "PAL"},
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP RearSensorMirrorMap[] = {
	{REAR_MIRROR_DISPLAY_OFF, "OFF"  },
	{REAR_MIRROR_DISPLAY_ON,  "ON"  },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP GPSSwitchMap[] = {
	{GPS_OFF, "OFF" },
	{GPS_ON,  "ON"  },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP SpeedUnitMap[] = {
	{SPEED_UNIT_MPH, "MPH"  },		
	{SPEED_UNIT_KPH, "KM/H"  },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP gpsStampMap[] = {
	{GPS_STAMP_OFF,  		"OFF"},
	{GPS_STAMP_BOTH,  		"Speed & Coordinates"},
	{GPS_STAMP_SPEED,  		"Speed"},
	{GPS_STAMP_COORDINATES, "Coordinates"},
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP TimeZoneMap[] = {
    {GMT_0,     "GMT 0" },
    {GMT_P1,    "GMT +1" },
    {GMT_P2,    "GMT +2" },
    {GMT_P3,    "GMT +3" },
    {GMT_P3_30, "GMT +3:30" },
    {GMT_P4,    "GMT +4" },
    {GMT_P4_30, "GMT +4:30" },
    {GMT_P5,    "GMT +5" },
    {GMT_P5_30, "GMT +5:30" },
    {GMT_P6,    "GMT +6" },
    //{GMT_P6_30, "GMT +6:30" },
    {GMT_P7,    "GMT +7" },
    {GMT_P8,    "GMT +8" },
    {GMT_P9,    "GMT +9" },
    {GMT_P9_30, "GMT +9:30" },
    {GMT_P10,   "GMT +10" },
    {GMT_P10_30,"GMT +10:30" },
    {GMT_P11,   "GMT +11" },
    {GMT_P12,   "GMT +12" },
    {GMT_P13,   "GMT +13" },
    {GMT_M1,    "GMT -1" },
    {GMT_M2,    "GMT -2" },
    //{GMT_M2_30, "GMT -2:30" },
    {GMT_M3,    "GMT -3" },
    {GMT_M3_30, "GMT -3:30" },
    {GMT_M4,    "GMT -4" },
    {GMT_M5,    "GMT -5" },
    {GMT_M6,    "GMT -6" },
    {GMT_M7,    "GMT -7" },
    {GMT_M8,    "GMT -8" },
    {GMT_M9,    "GMT -9" },
    {GMT_M10,   "GMT -10" },
    {GMT_M11,   "GMT -11" },
    {GMT_M12,   "GMT -12" },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP parkingModeMap[] = {
	{PARKING_MODE_OFF,			"OFF"  },
	//{PARKING_MODE_MOTION_DET, 	"motion" },
	{PARKING_MODE_ON_1FPS,		"1fps"	},
	//{PARKING_MODE_ON_2FPS,		"2fps"	},
	//{PARKING_MODE_ON_5FPS,		"5fps"	},
	//{PARKING_MODE_ON_10FPS,		"10fps"	},
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP BeepMap[] = {
	{BEEP_OFF, "OFF"  },
	{BEEP_ON,  "ON"  },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP VolumeMap[] = {
	{VOLUME20, 		"20%"  },
	{VOLUME40,  	"40%"  },
	{VOLUME60,  	"40%"  },
	{VOLUME80,  	"80%"  },
	{VOLUME100,  	"100%"  },
	{VOLUME_MUTE,  	"MUTE"  },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP FrequencyMap[] = {
	{FREQUENCY_50HZ, "50Hz"  },
	{FREQUENCY_60HZ, "60Hz"  },
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP LedMap[] = {
	{LED_OFF, "OFF"},
	{LED_ON,  "ON"},
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP LCDOffMap[] = {
	{LCDOFF_ON,    "OFF"},
	{LCDOFF_1MIN, "1MIN"},
	{LCDOFF_3MIN,  "3MIN"},
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP FormatWarningMap[] = {
	{FORMAT_WARNING_OFF,     "OFF"},
	{FORMAT_WARNING_15_DAY,  "15 Days"},
	{FORMAT_WARNING_30_DAY,  "30 Days"},
	{FORMAT_WARNING_60_DAY,  "60 Days"},
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP VoiceCtrlMap[] = {
	{ASR_OFF, "OFF"},
	{ASR_STANDARD,  "ON"},
	{INDEX_END, 0}
};

WIFIAPPINDEXMAP VoicePromptMap[] = {
	{MOVIE_VOICE_OFF, "OFF"},
	{MOVIE_VOICE_ON,  "ON"},
	{INDEX_END, 0}
};



WIFIAPPMAP wifiAppFlagMap[] = {
	//{FL_PHOTO_SIZE,         "PHOTO_SIZE",         photoSizeMap},
#if MOVE_SIZE_SUPPORT
	{FL_MOVIE_SIZE,         "MOVIE_SIZE",         movieSizeMap},
#endif
	{FL_MOVIE_CYCLIC_REC,   "MOVIE_CYCLIC_REC",   cyclicRecMap},
	{FL_DUAL_CAM,           "MOVIE_DUALCAM",      DualCamMap},
	{FL_LCD_OFF,            "LCD_OFF",            LCDOffMap},
	{FL_REAR_SENSOR_MIRROR,"REAR_SENSOR_MIRROR", RearSensorMirrorMap},
	{FL_GPS,       			"GPS", 		 		  GPSSwitchMap},
	//{FL_SPEED_SHOW,         "SPEED_SHOW",         SpeedShowMap},
	{FL_SPEED_UNIT,         "SPEED_UNIT",         SpeedUnitMap},
	{FL_TIME_ZONE,          "TIME_ZONE",          TimeZoneMap},
	{FL_GSENSOR,            "GSENSOR",            gSensorMap},
	{FL_PARKING_MODE,   	"PARKING_MODE",       parkingModeMap},	
	{FL_MOVIE_DATEIMPRINT,  "MOVIE_DATEIMPRINT",  dateImprintMap},
	{FL_MOVIE_AUDIO,        "MOVIE_AUDIO",        audioMap},
	{FL_BEEP,               "BEEP",               BeepMap},
	//{FL_SYSTEM_VOLUME,      "SYSTEM_VOLUME",      VolumeMap},
	//{FL_PLAY_VOLUME,     	"PLAY_VOLUME",        VolumeMap},
	//{FL_MOVIE_WDR,          "MOVIE_WDR",          WDRMap},
	{FL_MOVIE_HDR,          "MOVIE_HDR",          HDRMap},
	{FL_EV,                 "EV",                 EVMap},
	{FL_FREQUENCY,          "FREQUENCY",          FrequencyMap},
	{FL_LANGUAGE,           "LANGUAGE",           langMap},
	{FL_FORMAT_WARNING,     "FORMAT_WARNING",     FormatWarningMap},
	{FL_GPS_STAMP,     		"GPS_STAMP",     		gpsStampMap},
	{FL_VOLUME,     		"VOLUME",     			VolumeMap},
	{FL_ASR,     			"VOICE CTRONL",     	VoiceCtrlMap},
	{FL_MOVIE_VOICE,     	"VOICE PROMPT",     	VoicePromptMap},

	//{FL_MOVIE_MOTION_DET,   "MOVIE_MOTION_DET",   motionDetMap},
	//{FL_WIFI_AUTO_RECORDING, "WIFI_AUTO_RECORDING", wifiAutoRecMap},
	//{FL_AUTO_POWER_OFF,     "AUTO_POWER_OFF",     powerOffMap},
	//{FL_TV_MODE,            "TV_MODE",            TVMap},
	{FL_NULL, 0},
};
WIFIAPPMAP wifiAppFlagMap_Dual[] = {
	//{FL_PHOTO_SIZE,         "PHOTO_SIZE",         photoSizeMap},
#if MOVE_SIZE_SUPPORT
	{FL_MOVIE_SIZE,         "MOVIE_SIZE",         movieSizeMap_EthCam},
#endif
	{FL_MOVIE_CYCLIC_REC,   "MOVIE_CYCLIC_REC",   cyclicRecMap},
	{FL_DUAL_CAM,           "MOVIE_DUALCAM",      DualCamMap},
	{FL_LCD_OFF,            "LCD_OFF",            LCDOffMap},
	{FL_REAR_SENSOR_MIRROR,"REAR_SENSOR_MIRROR", RearSensorMirrorMap},
	{FL_GPS,       			"GPS", 		 		  GPSSwitchMap},
	//{FL_SPEED_SHOW,         "SPEED_SHOW",         SpeedShowMap},
	{FL_SPEED_UNIT,         "SPEED_UNIT",         SpeedUnitMap},
	{FL_TIME_ZONE,          "TIME_ZONE",          TimeZoneMap},
	{FL_GSENSOR,            "GSENSOR",            gSensorMap},
	{FL_PARKING_MODE,   	"PARKING_MODE",       parkingModeMap},	
	{FL_MOVIE_DATEIMPRINT,  "MOVIE_DATEIMPRINT",  dateImprintMap},
	{FL_MOVIE_AUDIO,        "MOVIE_AUDIO",        audioMap},
	{FL_BEEP,               "BEEP",               BeepMap},
	//{FL_SYSTEM_VOLUME,      "SYSTEM_VOLUME",      VolumeMap},
	//{FL_PLAY_VOLUME,     	"PLAY_VOLUME",        VolumeMap},
	//{FL_MOVIE_WDR,          "MOVIE_WDR",          WDRMap},
	{FL_MOVIE_HDR,          "MOVIE_HDR",          HDRMap},
	{FL_EV,                 "EV",                 EVMap},
	{FL_FREQUENCY,          "FREQUENCY",          FrequencyMap},
	{FL_LANGUAGE,           "LANGUAGE",           langMap},
	{FL_FORMAT_WARNING,     "FORMAT_WARNING",     FormatWarningMap},
	{FL_GPS_STAMP,     		"GPS_STAMP",     		gpsStampMap},
	{FL_VOLUME,     		"VOLUME",     			VolumeMap},
	{FL_ASR,     			"VOICE CTRONL",     	VoiceCtrlMap},
	{FL_MOVIE_VOICE,     	"VOICE PROMPT",     	VoicePromptMap},

	//{FL_MOVIE_MOTION_DET,   "MOVIE_MOTION_DET",   motionDetMap},
	//{FL_WIFI_AUTO_RECORDING, "WIFI_AUTO_RECORDING", wifiAutoRecMap},
	//{FL_AUTO_POWER_OFF,     "AUTO_POWER_OFF",     powerOffMap},
	//{FL_TV_MODE,            "TV_MODE",            TVMap},
	{FL_NULL, 0},
};	

WIFIAPPMAP *WifiCmd_GetMapTbl(void)
{
	//return wifiAppFlagMap;

	//if (System_GetEnableSensor() == (SENSOR_1|SENSOR_2)) 
	if (GPIOMap_EthCam1Det())
	{
		return wifiAppFlagMap_Dual;
	} else {
		return wifiAppFlagMap;
	}
}
