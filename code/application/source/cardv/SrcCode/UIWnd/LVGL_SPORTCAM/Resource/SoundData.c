/**
    Copyright   Novatek Microelectronics Corp. 2005.  All rights reserved.

    @file       SoundData.c
    @ingroup    mIPRJAPKey

    @brief      Keypad tone, Startup... sound data
                This file contain the PCM (ADPCM) data of keypad tone, Startup...

    @note       Nothing.

    @date       2005/01/23
*/

/** \addtogroup mIPRJAPKey */
//@{
#include "PrjInc.h"
#include "SoundData.h"
#include "GxSound.h"

#define THIS_DBGLVL         2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          sounddata
#define __DBGLVL__          ((THIS_DBGLVL>=PRJ_DBG_LVL)?THIS_DBGLVL:PRJ_DBG_LVL)
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>
///////////////////////////////////////////////////////////////////////////////

#if ((_BOARD_DRAM_SIZE_ == 0x04000000) || (SENSOR_CAPS_COUNT >= 2) ||  (defined(_NVT_ETHREARCAM_RX_) && (ETH_REARCAM_CAPS_COUNT >= 2)))
#define SOUND_AUDIO_SR		AUDIO_SR_16000
#else
#define SOUND_AUDIO_SR		AUDIO_SR_16000
#endif


#if (AUDIO_FUNC == ENABLE && WAV_PLAY_FUNC == DISABLE) // GxSound_Play conflicts with WavPlay

#if (ENGLISH_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_32K.c"
#include "SoundData_RecordingEn_32K.c"
#include "SoundData_MCarderror_Format_32K.c"
#include "SoundData_MCardFormatFail_32K.c"
#include "SoundData_MCardFormatSuccessful_32K.c"
#include "SoundData_ParRecordStart_32K.c"
#include "SoundData_PInsertCard_32K.c"
#include "SoundData_RecordingStart_32K.c"
#include "SoundData_VideoProtect_32K.c"
#include "SoundData_WifiConnect_32K.c"
#include "SoundData_WifiDisable_32K.c"
#include "SoundData_WifiEnable_32K.c"
#endif

#if (ARBIC_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_Arbic.c"
#include "SoundData_RecordingEn_Arbic.c"
#include "SoundData_MCarderror_Format_Arbic.c"
#include "SoundData_MCardFormatFail_Arbic.c"
#include "SoundData_MCardFormatSuccessful_Arbic.c"
#include "SoundData_ParRecordStart_Arbic.c"
#include "SoundData_PInsertCard_Arbic.c"
#include "SoundData_RecordingStart_Arbic.c"
#include "SoundData_VideoProtect_Arbic.c"
#include "SoundData_WifiConnect_Arbic.c"
#include "SoundData_WifiDisable_Arbic.c"
#include "SoundData_WifiEnable_Arbic.c"
#endif

#if (CHINESE_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_Chinese.c"
#include "SoundData_RecordingEn_Chinese.c"
#include "SoundData_MCarderror_Format_Chinese.c"
#include "SoundData_MCardFormatFail_Chinese.c"
#include "SoundData_MCardFormatSuccessful_Chinese.c"
#include "SoundData_ParRecordStart_Chinese.c"
#include "SoundData_PInsertCard_Chinese.c"
#include "SoundData_RecordingStart_Chinese.c"
#include "SoundData_VideoProtect_Chinese.c"
#include "SoundData_WifiConnect_Chinese.c"
#include "SoundData_WifiDisable_Chinese.c"
#include "SoundData_WifiEnable_Chinese.c"
#endif

#if (RUSSIAN_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_Russian.c"
#include "SoundData_RecordingEn_Russian.c"
#include "SoundData_MCarderror_Format_Russian.c"
#include "SoundData_MCardFormatFail_Russian.c"
#include "SoundData_MCardFormatSuccessful_Russian.c"
#include "SoundData_ParRecordStart_Russian.c"
#include "SoundData_PInsertCard_Russian.c"
#include "SoundData_RecordingStart_Russian.c"
#include "SoundData_VideoProtect_Russian.c"
#include "SoundData_WifiConnect_Russian.c"
#include "SoundData_WifiDisable_Russian.c"
#include "SoundData_WifiEnable_Russian.c"
#endif

#if (SPANISH_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_Spanish.c"
#include "SoundData_RecordingEn_Spanish.c"
#include "SoundData_MCarderror_Format_Spanish.c"
#include "SoundData_MCardFormatFail_Spanish.c"
#include "SoundData_MCardFormatSuccessful_Spanish.c"
#include "SoundData_ParRecordStart_Spanish.c"
#include "SoundData_PInsertCard_Spanish.c"
#include "SoundData_RecordingStart_Spanish.c"
#include "SoundData_VideoProtect_Spanish.c"
#include "SoundData_WifiConnect_Spanish.c"
#include "SoundData_WifiDisable_Spanish.c"
#include "SoundData_WifiEnable_Spanish.c"
#endif

#if (POLISH_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_Polish.c"
#include "SoundData_RecordingEn_Polish.c"
#include "SoundData_MCarderror_Format_Polish.c"
#include "SoundData_MCardFormatFail_Polish.c"
#include "SoundData_MCardFormatSuccessful_Polish.c"
#include "SoundData_ParRecordStart_Polish.c"
#include "SoundData_PInsertCard_Polish.c"
#include "SoundData_RecordingStart_Polish.c"
#include "SoundData_VideoProtect_Polish.c"
#include "SoundData_WifiConnect_Polish.c"
#include "SoundData_WifiDisable_Polish.c"
#include "SoundData_WifiEnable_Polish.c"
#endif

#if (TURKEY_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_Turkey.c"
#include "SoundData_RecordingEn_Turkey.c"
#include "SoundData_MCarderror_Format_Turkey.c"
#include "SoundData_MCardFormatFail_Turkey.c"
#include "SoundData_MCardFormatSuccessful_Turkey.c"
#include "SoundData_ParRecordStart_Turkey.c"
#include "SoundData_PInsertCard_Turkey.c"
#include "SoundData_RecordingStart_Turkey.c"
#include "SoundData_VideoProtect_Turkey.c"
#include "SoundData_WifiConnect_Turkey.c"
#include "SoundData_WifiDisable_Turkey.c"
#include "SoundData_WifiEnable_Turkey.c"
#endif

#if (CESKA_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_Ceska.c"
#include "SoundData_RecordingEn_Ceska.c"
#include "SoundData_MCarderror_Format_Ceska.c"
#include "SoundData_MCardFormatFail_Ceska.c"
#include "SoundData_MCardFormatSuccessful_Ceska.c"
#include "SoundData_ParRecordStart_Ceska.c"
#include "SoundData_PInsertCard_Ceska.c"
#include "SoundData_RecordingStart_Ceska.c"
#include "SoundData_VideoProtect_Ceska.c"
#include "SoundData_WifiConnect_Ceska.c"
#include "SoundData_WifiDisable_Ceska.c"
#include "SoundData_WifiEnable_Ceska.c"
#endif

#if (ROM_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_Rom.c"
#include "SoundData_RecordingEn_Rom.c"
#include "SoundData_MCarderror_Format_Rom.c"
#include "SoundData_MCardFormatFail_Rom.c"
#include "SoundData_MCardFormatSuccessful_Rom.c"
#include "SoundData_ParRecordStart_Rom.c"
#include "SoundData_PInsertCard_Rom.c"
#include "SoundData_RecordingStart_Rom.c"
#include "SoundData_VideoProtect_Rom.c"
#include "SoundData_WifiConnect_Rom.c"
#include "SoundData_WifiDisable_Rom.c"
#include "SoundData_WifiEnable_Rom.c"
#endif

#if (SLOVEN_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_Sloven.c"
#include "SoundData_RecordingEn_Sloven.c"
#include "SoundData_MCarderror_Format_Sloven.c"
#include "SoundData_MCardFormatFail_Sloven.c"
#include "SoundData_MCardFormatSuccessful_Sloven.c"
#include "SoundData_ParRecordStart_Sloven.c"
#include "SoundData_PInsertCard_Sloven.c"
#include "SoundData_RecordingStart_Sloven.c"
#include "SoundData_VideoProtect_Sloven.c"
#include "SoundData_WifiConnect_Sloven.c"
#include "SoundData_WifiDisable_Sloven.c"
#include "SoundData_WifiEnable_Sloven.c"
#endif

#if (DEUTSCH_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_Deutsch.c"
#include "SoundData_RecordingEn_Deutsch.c"
#include "SoundData_MCarderror_Format_Deutsch.c"
#include "SoundData_MCardFormatFail_Deutsch.c"
#include "SoundData_MCardFormatSuccessful_Deutsch.c"
#include "SoundData_ParRecordStart_Deutsch.c"
#include "SoundData_PInsertCard_Deutsch.c"
#include "SoundData_RecordingStart_Deutsch.c"
#include "SoundData_VideoProtect_Deutsch.c"
#include "SoundData_WifiConnect_Deutsch.c"
#include "SoundData_WifiDisable_Deutsch.c"
#include "SoundData_WifiEnable_Deutsch.c"
#endif

#if (JAPANESE_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_Japanese.c"
#include "SoundData_RecordingEn_Japanese.c"
#include "SoundData_MCarderror_Format_Japanese.c"
#include "SoundData_MCardFormatFail_Japanese.c"
#include "SoundData_MCardFormatSuccessful_Japanese.c"
#include "SoundData_ParRecordStart_Japanese.c"
#include "SoundData_PInsertCard_Japanese.c"
#include "SoundData_RecordingStart_Japanese.c"
#include "SoundData_VideoProtect_Japanese.c"
#include "SoundData_WifiConnect_Japanese.c"
#include "SoundData_WifiDisable_Japanese.c"
#include "SoundData_WifiEnable_Japanese.c"
#endif

#if (ITALIAN_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_Italian.c"
#include "SoundData_RecordingEn_Italian.c"
#include "SoundData_MCarderror_Format_Italian.c"
#include "SoundData_MCardFormatFail_Italian.c"
#include "SoundData_MCardFormatSuccessful_Italian.c"
#include "SoundData_ParRecordStart_Italian.c"
#include "SoundData_PInsertCard_Italian.c"
#include "SoundData_RecordingStart_Italian.c"
#include "SoundData_VideoProtect_Italian.c"
#include "SoundData_WifiConnect_Italian.c"
#include "SoundData_WifiDisable_Italian.c"
#include "SoundData_WifiEnable_Italian.c"
#endif

#if (FRANCE_VOICESOUND == ENABLE)
#include "SoundData_RecordingDis_France.c"
#include "SoundData_RecordingEn_France.c"
#include "SoundData_MCarderror_Format_France.c"
#include "SoundData_MCardFormatFail_France.c"
#include "SoundData_MCardFormatSuccessful_France.c"
#include "SoundData_ParRecordStart_France.c"
#include "SoundData_PInsertCard_France.c"
#include "SoundData_RecordingStart_France.c"
#include "SoundData_VideoProtect_France.c"
#include "SoundData_WifiConnect_France.c"
#include "SoundData_WifiDisable_France.c"
#include "SoundData_WifiEnable_France.c"
#endif

#if (SOUND_AUDIO_SR == AUDIO_SR_16000)
#include "SoundData_PowerOn_16K.c"
#if (PHOTO_MODE == ENABLE)
#include "SoundData_Shutter_16K.c"
#endif
#include "SoundData_Key_16K.c"
#if (_ADAS_FUNC_ == ENABLE)
#include "SoundData_LDWS_16K.c"
#include "SoundData_FCW_16K.c"
#include "SoundData_SnG_16K.c"
#include "SoundData_LaneDeparture_16K.c"
#include "SoundData_FrontCarCollision_16K.c"
#include "SoundData_FrontCarGo_16K.c"
#include "SoundData_Pedestrian_16K.c"

#endif
#if (_DDD_FUNC_ == ENABLE)
#include "SoundData_DDD1_16K.c"
#include "SoundData_DDD2_16K.c"
#include "SoundData_DDD3_16K.c"
#endif
#if (_GPS_EDOG_UNIQUE_SKY_==ENABLE)
#include "SoundData_EP_0_16K.c"
#include "SoundData_EP_1_16K.c"
#include "SoundData_EP_2_16K.c"
#include "SoundData_EP_3_16K.c"
#include "SoundData_EP_4_16K.c"
#include "SoundData_EP_5_16K.c"
#include "SoundData_EP_6_16K.c"
#include "SoundData_EP_7_16K.c"
#include "SoundData_EP_8_16K.c"
#include "SoundData_EP_9_16K.c"
#include "SoundData_EP_10_16K.c"
#include "SoundData_EP_11_16K.c"
#include "SoundData_EP_12_16K.c"
#include "SoundData_EP_13_16K.c"
#include "SoundData_EP_14_16K.c"
#include "SoundData_EP_15_16K.c"
#include "SoundData_EP_16_16K.c"
#include "SoundData_EP_17_16K.c"
#include "SoundData_EP_18_16K.c"
#include "SoundData_EP_19_16K.c"
#include "SoundData_EP_20_16K.c"
#include "SoundData_EP_21_16K.c"
#include "SoundData_EP_22_16K.c"
#include "SoundData_EP_23_16K.c"
#include "SoundData_EP_24_16K.c"
#include "SoundData_EP_25_16K.c"
#include "SoundData_EP_26_16K.c"
#include "SoundData_EP_27_16K.c"
#include "SoundData_EP_28_16K.c"
#include "SoundData_EP_29_16K.c"
#include "SoundData_EP_30_16K.c"
#include "SoundData_EP_31_16K.c"
#include "SoundData_EP_32_16K.c"
#include "SoundData_EP_33_16K.c"
#include "SoundData_EP_34_16K.c"
#include "SoundData_EP_35_16K.c"
#include "SoundData_EP_36_16K.c"
#include "SoundData_EP_37_16K.c"
#include "SoundData_EP_38_16K.c"
#include "SoundData_EP_39_16K.c"
#include "SoundData_EP_42_16K.c"
#include "SoundData_EP_43_16K.c"
#include "SoundData_EP_44_16K.c"
#include "SoundData_EP_45_16K.c"
#include "SoundData_EP_46_16K.c"
#include "SoundData_EP_51_16K.c"
#include "SoundData_EP_75_16K.c"
#include "SoundData_EP_76_16K.c"
#include "SoundData_EP_77_16K.c"
#include "SoundData_EP_78_16K.c"
#include "SoundData_EP_79_16K.c"
#include "SoundData_EP_80_16K.c"
#include "SoundData_EP_81_16K.c"
#include "SoundData_EP_82_16K.c"
#include "SoundData_EP_87_16K.c"
#include "SoundData_EP_88_16K.c"
#include "SoundData_EP_89_16K.c"
#include "SoundData_EP_90_16K.c"
#include "SoundData_EP_91_16K.c"
#include "SoundData_EP_92_16K.c"
#include "SoundData_EP_93_16K.c"
#include "SoundData_EP_94_16K.c"
#include "SoundData_EP_95_16K.c"
#include "SoundData_EP_96_16K.c"
#include "SoundData_EP_97_16K.c"
#include "SoundData_EP_kejizhifa_16K.c"
#include "SoundData_EP_xiansu_16K.c"
#endif

#else
//32K
#include "SoundData_PowerOn_32K.c"

#if (PHOTO_MODE == ENABLE)
#include "SoundData_Shutter_32K.c"
#endif
#include "SoundData_Key_32K.c"
#if (_ADAS_FUNC_ == ENABLE)
#include "SoundData_LDWS_32K.c"
#include "SoundData_FCW_32K.c"
#include "SoundData_SnG_32K.c"
#endif
#if (_DDD_FUNC_ == ENABLE)
#include "SoundData_DDD1_32K.c"
#include "SoundData_DDD2_32K.c"
#include "SoundData_DDD3_32K.c"
#endif
#if (_GPS_EDOG_UNIQUE_SKY_==ENABLE)
#include "SoundData_EP_0_32K.c"
#include "SoundData_EP_1_32K.c"
#include "SoundData_EP_2_32K.c"
#include "SoundData_EP_3_32K.c"
#include "SoundData_EP_4_32K.c"
#include "SoundData_EP_5_32K.c"
#include "SoundData_EP_6_32K.c"
#include "SoundData_EP_7_32K.c"
#include "SoundData_EP_8_32K.c"
#include "SoundData_EP_9_32K.c"
#include "SoundData_EP_10_32K.c"
#include "SoundData_EP_11_32K.c"
#include "SoundData_EP_12_32K.c"
#include "SoundData_EP_13_32K.c"
#include "SoundData_EP_14_32K.c"
#include "SoundData_EP_15_32K.c"
#include "SoundData_EP_16_32K.c"
#include "SoundData_EP_17_32K.c"
#include "SoundData_EP_18_32K.c"
#include "SoundData_EP_19_32K.c"
#include "SoundData_EP_20_32K.c"
#include "SoundData_EP_21_32K.c"
#include "SoundData_EP_22_32K.c"
#include "SoundData_EP_23_32K.c"
#include "SoundData_EP_24_32K.c"
#include "SoundData_EP_25_32K.c"
#include "SoundData_EP_26_32K.c"
#include "SoundData_EP_27_32K.c"
#include "SoundData_EP_28_32K.c"
#include "SoundData_EP_29_32K.c"
#include "SoundData_EP_30_32K.c"
#include "SoundData_EP_31_32K.c"
#include "SoundData_EP_32_32K.c"
#include "SoundData_EP_33_32K.c"
#include "SoundData_EP_34_32K.c"
#include "SoundData_EP_35_32K.c"
#include "SoundData_EP_36_32K.c"
#include "SoundData_EP_37_32K.c"
#include "SoundData_EP_38_32K.c"
#include "SoundData_EP_39_32K.c"
#include "SoundData_EP_42_32K.c"
#include "SoundData_EP_43_32K.c"
#include "SoundData_EP_44_32K.c"
#include "SoundData_EP_45_32K.c"
#include "SoundData_EP_46_32K.c"
#include "SoundData_EP_51_32K.c"
#include "SoundData_EP_75_32K.c"
#include "SoundData_EP_76_32K.c"
#include "SoundData_EP_77_32K.c"
#include "SoundData_EP_78_32K.c"
#include "SoundData_EP_79_32K.c"
#include "SoundData_EP_80_32K.c"
#include "SoundData_EP_81_32K.c"
#include "SoundData_EP_82_32K.c"
#include "SoundData_EP_87_32K.c"
#include "SoundData_EP_88_32K.c"
#include "SoundData_EP_89_32K.c"
#include "SoundData_EP_90_32K.c"
#include "SoundData_EP_91_32K.c"
#include "SoundData_EP_92_32K.c"
#include "SoundData_EP_93_32K.c"
#include "SoundData_EP_94_32K.c"
#include "SoundData_EP_95_32K.c"
#include "SoundData_EP_96_32K.c"
#include "SoundData_EP_97_32K.c"
#include "SoundData_EP_kejizhifa_32K.c"
#include "SoundData_EP_xiansu_32K.c"
#endif

#endif

static const SOUND_DATA gDemo_Sound[DEMOSOUND_SOUND_MAX_CNT] = {
	{ 0 },
	{ uiSoundKey,					sizeof(uiSoundKey),				SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_KEY_TONE			},
#if (ENGLISH_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_English,       		sizeof(uiSoundRecordingEn_English),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_ENGLISH_TONE        },
	{ uiSoundRecordingDis_English,				sizeof(uiSoundRecordingDis_English), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_ENGLISH_TONE		},	
	{ uiSoundMCarderrorFormat_English,		sizeof(uiSoundMCarderrorFormat_English), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_ENGLISH_TONE		},
	{ uiSoundMCardFormatFail_English,			sizeof(uiSoundMCardFormatFail_English), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_ENGLISH_TONE		},
	{ uiSoundMCardFormatSuccessful_English,		sizeof(uiSoundMCardFormatSuccessful_English), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_ENGLISH_TONE		},
	{ uiSoundParRecordStart_English,		sizeof(uiSoundParRecordStart_English), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_ENGLISH_TONE		},
	{ uiSoundPInsertCard_English,			sizeof(uiSoundPInsertCard_English), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_ENGLISH_TONE		},
	{ uiSoundRecordingStart_English,		sizeof(uiSoundRecordingStart_English), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_ENGLISH_TONE		},
	{ uiSoundVideoProtect_English,			sizeof(uiSoundVideoProtect_English), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_ENGLISH_TONE		},
	{ uiSoundWifiConnect_English,			sizeof(uiSoundWifiConnect_English), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_ENGLISH_TONE		},
	{ uiSoundWifiDisable_English,			sizeof(uiSoundWifiDisable_English), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_ENGLISH_TONE		},
	{ uiSoundWifiEnable_English,			sizeof(uiSoundWifiEnable_English), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_ENGLISH_TONE		},
#endif

#if (ARBIC_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_Arbic,       		sizeof(uiSoundRecordingEn_Arbic),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_ARBIC_TONE        },
	{ uiSoundRecordingDis_Arbic,				sizeof(uiSoundRecordingDis_Arbic), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_ARBIC_TONE		},	
	{ uiSoundMCarderrorFormat_Arbic,		sizeof(uiSoundMCarderrorFormat_Arbic), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_ARBIC_TONE		},
	{ uiSoundMCardFormatFail_Arbic,			sizeof(uiSoundMCardFormatFail_Arbic), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_ARBIC_TONE		},
	{ uiSoundMCardFormatSuccessful_Arbic,		sizeof(uiSoundMCardFormatSuccessful_Arbic), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_ARBIC_TONE		},
	{ uiSoundParRecordStart_Arbic,		sizeof(uiSoundParRecordStart_Arbic), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_ARBIC_TONE		},
	{ uiSoundPInsertCard_Arbic,			sizeof(uiSoundPInsertCard_Arbic), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_ARBIC_TONE		},
	{ uiSoundRecordingStart_Arbic,		sizeof(uiSoundRecordingStart_Arbic), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_ARBIC_TONE		},
	{ uiSoundVideoProtect_Arbic,			sizeof(uiSoundVideoProtect_Arbic), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_ARBIC_TONE		},
	{ uiSoundWifiConnect_Arbic,			sizeof(uiSoundWifiConnect_Arbic), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_ARBIC_TONE		},
	{ uiSoundWifiDisable_Arbic,			sizeof(uiSoundWifiDisable_Arbic), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_ARBIC_TONE		},
	{ uiSoundWifiEnable_Arbic,			sizeof(uiSoundWifiEnable_Arbic), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_ARBIC_TONE		},
#endif

#if (CHINESE_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_Chinese,       		sizeof(uiSoundRecordingEn_Chinese),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_CHINESE_TONE        },
	{ uiSoundRecordingDis_Chinese,				sizeof(uiSoundRecordingDis_Chinese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_CHINESE_TONE		},	
	{ uiSoundMCarderrorFormat_Chinese,		sizeof(uiSoundMCarderrorFormat_Chinese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_CHINESE_TONE		},
	{ uiSoundMCardFormatFail_Chinese,			sizeof(uiSoundMCardFormatFail_Chinese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_CHINESE_TONE		},
	{ uiSoundMCardFormatSuccessful_Chinese,		sizeof(uiSoundMCardFormatSuccessful_Chinese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_CHINESE_TONE		},
	{ uiSoundParRecordStart_Chinese,		sizeof(uiSoundParRecordStart_Chinese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_CHINESE_TONE		},
	{ uiSoundPInsertCard_Chinese,			sizeof(uiSoundPInsertCard_Chinese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_CHINESE_TONE		},
	{ uiSoundRecordingStart_Chinese,		sizeof(uiSoundRecordingStart_Chinese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_CHINESE_TONE		},
	{ uiSoundVideoProtect_Chinese,			sizeof(uiSoundVideoProtect_Chinese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_CHINESE_TONE		},
	{ uiSoundWifiConnect_Chinese,			sizeof(uiSoundWifiConnect_Chinese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_CHINESE_TONE		},
	{ uiSoundWifiDisable_Chinese,			sizeof(uiSoundWifiDisable_Chinese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_CHINESE_TONE		},
	{ uiSoundWifiEnable_Chinese,			sizeof(uiSoundWifiEnable_Chinese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_CHINESE_TONE		},
#endif

#if (RUSSIAN_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_Russian,       		sizeof(uiSoundRecordingEn_Russian),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_RUSSIAN_TONE        },
	{ uiSoundRecordingDis_Russian,				sizeof(uiSoundRecordingDis_Russian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_RUSSIAN_TONE		},	
	{ uiSoundMCarderrorFormat_Russian,		sizeof(uiSoundMCarderrorFormat_Russian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_RUSSIAN_TONE		},
	{ uiSoundMCardFormatFail_Russian,			sizeof(uiSoundMCardFormatFail_Russian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_RUSSIAN_TONE		},
	{ uiSoundMCardFormatSuccessful_Russian,		sizeof(uiSoundMCardFormatSuccessful_Russian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_RUSSIAN_TONE		},
	{ uiSoundParRecordStart_Russian,		sizeof(uiSoundParRecordStart_Russian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_RUSSIAN_TONE		},
	{ uiSoundPInsertCard_Russian,			sizeof(uiSoundPInsertCard_Russian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_RUSSIAN_TONE		},
	{ uiSoundRecordingStart_Russian,		sizeof(uiSoundRecordingStart_Russian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_RUSSIAN_TONE		},
	{ uiSoundVideoProtect_Russian,			sizeof(uiSoundVideoProtect_Russian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_RUSSIAN_TONE		},
	{ uiSoundWifiConnect_Russian,			sizeof(uiSoundWifiConnect_Russian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_RUSSIAN_TONE		},
	{ uiSoundWifiDisable_Russian,			sizeof(uiSoundWifiDisable_Russian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_RUSSIAN_TONE		},
	{ uiSoundWifiEnable_Russian,			sizeof(uiSoundWifiEnable_Russian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_RUSSIAN_TONE		},
#endif

#if (SPANISH_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_Spanish,       		sizeof(uiSoundRecordingEn_Spanish),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_SPANISH_TONE        },
	{ uiSoundRecordingDis_Spanish,				sizeof(uiSoundRecordingDis_Spanish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_SPANISH_TONE		},	
	{ uiSoundMCarderrorFormat_Spanish,		sizeof(uiSoundMCarderrorFormat_Spanish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_SPANISH_TONE		},
	{ uiSoundMCardFormatFail_Spanish,			sizeof(uiSoundMCardFormatFail_Spanish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_SPANISH_TONE		},
	{ uiSoundMCardFormatSuccessful_Spanish,		sizeof(uiSoundMCardFormatSuccessful_Spanish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_SPANISH_TONE		},
	{ uiSoundParRecordStart_Spanish,		sizeof(uiSoundParRecordStart_Spanish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_SPANISH_TONE		},
	{ uiSoundPInsertCard_Spanish,			sizeof(uiSoundPInsertCard_Spanish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_SPANISH_TONE		},
	{ uiSoundRecordingStart_Spanish,		sizeof(uiSoundRecordingStart_Spanish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_SPANISH_TONE		},
	{ uiSoundVideoProtect_Spanish,			sizeof(uiSoundVideoProtect_Spanish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_SPANISH_TONE		},
	{ uiSoundWifiConnect_Spanish,			sizeof(uiSoundWifiConnect_Spanish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_SPANISH_TONE		},
	{ uiSoundWifiDisable_Spanish,			sizeof(uiSoundWifiDisable_Spanish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_SPANISH_TONE		},
	{ uiSoundWifiEnable_Spanish,			sizeof(uiSoundWifiEnable_Spanish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_SPANISH_TONE		},
#endif

#if (POLISH_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_Polish,       		sizeof(uiSoundRecordingEn_Polish),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_POLISH_TONE        },
	{ uiSoundRecordingDis_Polish,				sizeof(uiSoundRecordingDis_Polish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_POLISH_TONE		},	
	{ uiSoundMCarderrorFormat_Polish,		sizeof(uiSoundMCarderrorFormat_Polish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_POLISH_TONE		},
	{ uiSoundMCardFormatFail_Polish,			sizeof(uiSoundMCardFormatFail_Polish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_POLISH_TONE		},
	{ uiSoundMCardFormatSuccessful_Polish,		sizeof(uiSoundMCardFormatSuccessful_Polish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_POLISH_TONE		},
	{ uiSoundParRecordStart_Polish,		sizeof(uiSoundParRecordStart_Polish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_POLISH_TONE		},
	{ uiSoundPInsertCard_Polish,			sizeof(uiSoundPInsertCard_Polish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_POLISH_TONE		},
	{ uiSoundRecordingStart_Polish,		sizeof(uiSoundRecordingStart_Polish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_POLISH_TONE		},
	{ uiSoundVideoProtect_Polish,			sizeof(uiSoundVideoProtect_Polish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_POLISH_TONE		},
	{ uiSoundWifiConnect_Polish,			sizeof(uiSoundWifiConnect_Polish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_POLISH_TONE		},
	{ uiSoundWifiDisable_Polish,			sizeof(uiSoundWifiDisable_Polish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_POLISH_TONE		},
	{ uiSoundWifiEnable_Polish,			sizeof(uiSoundWifiEnable_Polish), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_POLISH_TONE		},
#endif

#if (TURKEY_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_Turkey,       		sizeof(uiSoundRecordingEn_Turkey),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_TURKEY_TONE        },
	{ uiSoundRecordingDis_Turkey,				sizeof(uiSoundRecordingDis_Turkey), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_TURKEY_TONE		},	
	{ uiSoundMCarderrorFormat_Turkey,		sizeof(uiSoundMCarderrorFormat_Turkey), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_TURKEY_TONE		},
	{ uiSoundMCardFormatFail_Turkey,			sizeof(uiSoundMCardFormatFail_Turkey), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_TURKEY_TONE		},
	{ uiSoundMCardFormatSuccessful_Turkey,		sizeof(uiSoundMCardFormatSuccessful_Turkey), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_TURKEY_TONE		},
	{ uiSoundParRecordStart_Turkey,		sizeof(uiSoundParRecordStart_Turkey), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_TURKEY_TONE		},
	{ uiSoundPInsertCard_Turkey,			sizeof(uiSoundPInsertCard_Turkey), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_TURKEY_TONE		},
	{ uiSoundRecordingStart_Turkey,		sizeof(uiSoundRecordingStart_Turkey), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_TURKEY_TONE		},
	{ uiSoundVideoProtect_Turkey,			sizeof(uiSoundVideoProtect_Turkey), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_TURKEY_TONE		},
	{ uiSoundWifiConnect_Turkey,			sizeof(uiSoundWifiConnect_Turkey), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_TURKEY_TONE		},
	{ uiSoundWifiDisable_Turkey,			sizeof(uiSoundWifiDisable_Turkey), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_TURKEY_TONE		},
	{ uiSoundWifiEnable_Turkey,			sizeof(uiSoundWifiEnable_Turkey), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_TURKEY_TONE		},
#endif

#if (CESKA_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_Ceska,       		sizeof(uiSoundRecordingEn_Ceska),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_CESKA_TONE        },
	{ uiSoundRecordingDis_Ceska,				sizeof(uiSoundRecordingDis_Ceska), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_CESKA_TONE		},	
	{ uiSoundMCarderrorFormat_Ceska,		sizeof(uiSoundMCarderrorFormat_Ceska), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_CESKA_TONE		},
	{ uiSoundMCardFormatFail_Ceska,			sizeof(uiSoundMCardFormatFail_Ceska), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_CESKA_TONE		},
	{ uiSoundMCardFormatSuccessful_Ceska,		sizeof(uiSoundMCardFormatSuccessful_Ceska), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_CESKA_TONE		},
	{ uiSoundParRecordStart_Ceska,		sizeof(uiSoundParRecordStart_Ceska), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_CESKA_TONE		},
	{ uiSoundPInsertCard_Ceska,			sizeof(uiSoundPInsertCard_Ceska), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_CESKA_TONE		},
	{ uiSoundRecordingStart_Ceska,		sizeof(uiSoundRecordingStart_Ceska), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_CESKA_TONE		},
	{ uiSoundVideoProtect_Ceska,			sizeof(uiSoundVideoProtect_Ceska), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_CESKA_TONE		},
	{ uiSoundWifiConnect_Ceska,			sizeof(uiSoundWifiConnect_Ceska), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_CESKA_TONE		},
	{ uiSoundWifiDisable_Ceska,			sizeof(uiSoundWifiDisable_Ceska), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_CESKA_TONE		},
	{ uiSoundWifiEnable_Ceska,			sizeof(uiSoundWifiEnable_Ceska), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_CESKA_TONE		},
#endif

#if (ROM_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_Rom,       		sizeof(uiSoundRecordingEn_Rom),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_ROM_TONE        },
	{ uiSoundRecordingDis_Rom,				sizeof(uiSoundRecordingDis_Rom), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_ROM_TONE		},	
	{ uiSoundMCarderrorFormat_Rom,		sizeof(uiSoundMCarderrorFormat_Rom), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_ROM_TONE		},
	{ uiSoundMCardFormatFail_Rom,			sizeof(uiSoundMCardFormatFail_Rom), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_ROM_TONE		},
	{ uiSoundMCardFormatSuccessful_Rom,		sizeof(uiSoundMCardFormatSuccessful_Rom), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_ROM_TONE		},
	{ uiSoundParRecordStart_Rom,		sizeof(uiSoundParRecordStart_Rom), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_ROM_TONE		},
	{ uiSoundPInsertCard_Rom,			sizeof(uiSoundPInsertCard_Rom), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_ROM_TONE		},
	{ uiSoundRecordingStart_Rom,		sizeof(uiSoundRecordingStart_Rom), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_ROM_TONE		},
	{ uiSoundVideoProtect_Rom,			sizeof(uiSoundVideoProtect_Rom), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_ROM_TONE		},
	{ uiSoundWifiConnect_Rom,			sizeof(uiSoundWifiConnect_Rom), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_ROM_TONE		},
	{ uiSoundWifiDisable_Rom,			sizeof(uiSoundWifiDisable_Rom), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_ROM_TONE		},
	{ uiSoundWifiEnable_Rom,			sizeof(uiSoundWifiEnable_Rom), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_ROM_TONE		},
#endif

#if (SLOVEN_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_Sloven,       		sizeof(uiSoundRecordingEn_Sloven),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_SLOVEN_TONE        },
	{ uiSoundRecordingDis_Sloven,				sizeof(uiSoundRecordingDis_Sloven), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_SLOVEN_TONE		},	
	{ uiSoundMCarderrorFormat_Sloven,		sizeof(uiSoundMCarderrorFormat_Sloven), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_SLOVEN_TONE		},
	{ uiSoundMCardFormatFail_Sloven,			sizeof(uiSoundMCardFormatFail_Sloven), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_SLOVEN_TONE		},
	{ uiSoundMCardFormatSuccessful_Sloven,		sizeof(uiSoundMCardFormatSuccessful_Sloven), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_SLOVEN_TONE		},
	{ uiSoundParRecordStart_Sloven,		sizeof(uiSoundParRecordStart_Sloven), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_SLOVEN_TONE		},
	{ uiSoundPInsertCard_Sloven,			sizeof(uiSoundPInsertCard_Sloven), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_SLOVEN_TONE		},
	{ uiSoundRecordingStart_Sloven,		sizeof(uiSoundRecordingStart_Sloven), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_SLOVEN_TONE		},
	{ uiSoundVideoProtect_Sloven,			sizeof(uiSoundVideoProtect_Sloven), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_SLOVEN_TONE		},
	{ uiSoundWifiConnect_Sloven,			sizeof(uiSoundWifiConnect_Sloven), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_SLOVEN_TONE		},
	{ uiSoundWifiDisable_Sloven,			sizeof(uiSoundWifiDisable_Sloven), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_SLOVEN_TONE		},
	{ uiSoundWifiEnable_Sloven,			sizeof(uiSoundWifiEnable_Sloven), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_SLOVEN_TONE		},
#endif

#if (DEUTSCH_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_Deutsch,       		sizeof(uiSoundRecordingEn_Deutsch),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_DEUTSCH_TONE        },
	{ uiSoundRecordingDis_Deutsch,				sizeof(uiSoundRecordingDis_Deutsch), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_DEUTSCH_TONE		},	
	{ uiSoundMCarderrorFormat_Deutsch,		sizeof(uiSoundMCarderrorFormat_Deutsch), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_DEUTSCH_TONE		},
	{ uiSoundMCardFormatFail_Deutsch,			sizeof(uiSoundMCardFormatFail_Deutsch), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_DEUTSCH_TONE		},
	{ uiSoundMCardFormatSuccessful_Deutsch,		sizeof(uiSoundMCardFormatSuccessful_Deutsch), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_DEUTSCH_TONE		},
	{ uiSoundParRecordStart_Deutsch,		sizeof(uiSoundParRecordStart_Deutsch), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_DEUTSCH_TONE		},
	{ uiSoundPInsertCard_Deutsch,			sizeof(uiSoundPInsertCard_Deutsch), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_DEUTSCH_TONE		},
	{ uiSoundRecordingStart_Deutsch,		sizeof(uiSoundRecordingStart_Deutsch), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_DEUTSCH_TONE		},
	{ uiSoundVideoProtect_Deutsch,			sizeof(uiSoundVideoProtect_Deutsch), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_DEUTSCH_TONE		},
	{ uiSoundWifiConnect_Deutsch,			sizeof(uiSoundWifiConnect_Deutsch), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_DEUTSCH_TONE		},
	{ uiSoundWifiDisable_Deutsch,			sizeof(uiSoundWifiDisable_Deutsch), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_DEUTSCH_TONE		},
	{ uiSoundWifiEnable_Deutsch,			sizeof(uiSoundWifiEnable_Deutsch), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_DEUTSCH_TONE		},
#endif

#if (JAPANESE_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_Japanese,       		sizeof(uiSoundRecordingEn_Japanese),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_JAPANESE_TONE        },
	{ uiSoundRecordingDis_Japanese,				sizeof(uiSoundRecordingDis_Japanese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_JAPANESE_TONE		},	
	{ uiSoundMCarderrorFormat_Japanese,		sizeof(uiSoundMCarderrorFormat_Japanese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_JAPANESE_TONE		},
	{ uiSoundMCardFormatFail_Japanese,			sizeof(uiSoundMCardFormatFail_Japanese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_JAPANESE_TONE		},
	{ uiSoundMCardFormatSuccessful_Japanese,		sizeof(uiSoundMCardFormatSuccessful_Japanese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_JAPANESE_TONE		},
	{ uiSoundParRecordStart_Japanese,		sizeof(uiSoundParRecordStart_Japanese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_JAPANESE_TONE		},
	{ uiSoundPInsertCard_Japanese,			sizeof(uiSoundPInsertCard_Japanese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_JAPANESE_TONE		},
	{ uiSoundRecordingStart_Japanese,		sizeof(uiSoundRecordingStart_Japanese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_JAPANESE_TONE		},
	{ uiSoundVideoProtect_Japanese,			sizeof(uiSoundVideoProtect_Japanese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_JAPANESE_TONE		},
	{ uiSoundWifiConnect_Japanese,			sizeof(uiSoundWifiConnect_Japanese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_JAPANESE_TONE		},
	{ uiSoundWifiDisable_Japanese,			sizeof(uiSoundWifiDisable_Japanese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_JAPANESE_TONE		},
	{ uiSoundWifiEnable_Japanese,			sizeof(uiSoundWifiEnable_Japanese), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_JAPANESE_TONE		},
#endif



#if (ITALIAN_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_Italian,       		sizeof(uiSoundRecordingEn_Italian),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_ITALIAN_TONE        },
	{ uiSoundRecordingDis_Italian,				sizeof(uiSoundRecordingDis_Italian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_ITALIAN_TONE		},	
	{ uiSoundMCarderrorFormat_Italian,		sizeof(uiSoundMCarderrorFormat_Italian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_ITALIAN_TONE		},
	{ uiSoundMCardFormatFail_Italian,			sizeof(uiSoundMCardFormatFail_Italian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_ITALIAN_TONE		},
	{ uiSoundMCardFormatSuccessful_Italian,		sizeof(uiSoundMCardFormatSuccessful_Italian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_ITALIAN_TONE		},
	{ uiSoundParRecordStart_Italian,		sizeof(uiSoundParRecordStart_Italian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_ITALIAN_TONE		},
	{ uiSoundPInsertCard_Italian,			sizeof(uiSoundPInsertCard_Italian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_ITALIAN_TONE		},
	{ uiSoundRecordingStart_Italian,		sizeof(uiSoundRecordingStart_Italian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_ITALIAN_TONE		},
	{ uiSoundVideoProtect_Italian,			sizeof(uiSoundVideoProtect_Italian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_ITALIAN_TONE		},
	{ uiSoundWifiConnect_Italian,			sizeof(uiSoundWifiConnect_Italian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_ITALIAN_TONE		},
	{ uiSoundWifiDisable_Italian,			sizeof(uiSoundWifiDisable_Italian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_ITALIAN_TONE		},
	{ uiSoundWifiEnable_Italian,			sizeof(uiSoundWifiEnable_Italian), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_ITALIAN_TONE		},
#endif

#if (FRANCE_VOICESOUND == ENABLE)
	{ uiSoundRecordingEn_France,       		sizeof(uiSoundRecordingEn_France),     SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICEN_FRANCE_TONE        },
	{ uiSoundRecordingDis_France,				sizeof(uiSoundRecordingDis_France), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MICDIS_FRANCE_TONE		},	
	{ uiSoundMCarderrorFormat_France,		sizeof(uiSoundMCarderrorFormat_France), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDERRORFORMAT_FRANCE_TONE		},
	{ uiSoundMCardFormatFail_France,			sizeof(uiSoundMCardFormatFail_France), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATFAIL_FRANCE_TONE		},
	{ uiSoundMCardFormatSuccessful_France,		sizeof(uiSoundMCardFormatSuccessful_France), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_FRANCE_TONE		},
	{ uiSoundParRecordStart_France,		sizeof(uiSoundParRecordStart_France), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PARRECORDSTART_FRANCE_TONE		},
	{ uiSoundPInsertCard_France,			sizeof(uiSoundPInsertCard_France), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PINSERTCARD_FRANCE_TONE		},
	{ uiSoundRecordingStart_France,		sizeof(uiSoundRecordingStart_France), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RECORDINGSTART_FRANCE_TONE		},
	{ uiSoundVideoProtect_France,			sizeof(uiSoundVideoProtect_France), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIDEOPROTECT_FRANCE_TONE		},
	{ uiSoundWifiConnect_France,			sizeof(uiSoundWifiConnect_France), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFICONNECT_FRANCE_TONE		},
	{ uiSoundWifiDisable_France,			sizeof(uiSoundWifiDisable_France), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIDISABLE_FRANCE_TONE		},
	{ uiSoundWifiEnable_France,			sizeof(uiSoundWifiEnable_France), 	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_WIFIENADLE_FRANCE_TONE		},
#endif



#if (PHOTO_MODE == ENABLE)
	{ uiSoundShutter,			sizeof(uiSoundShutter),			SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_SHUTTER_TONE		},
#endif
	{ uiSoundPowerOn,			sizeof(uiSoundPowerOn),			SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_POWERON_TONE		},
#if (_ADAS_FUNC_ == ENABLE)
	{ uiSoundLaneDeparture,		sizeof(uiSoundLaneDeparture),	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_LDWS_TONE 		},
	{ uiSoundFrontCarCollision,	sizeof(uiSoundFrontCarCollision),SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_FCS_TONE			},
	{ uiSoundFrontCarGo,		sizeof(uiSoundFrontCarGo), 		SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_SNG_TONE			},
	{ uiSoundPedestrian,		sizeof(uiSoundPedestrian),		SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_PCW_TONE			},
	{ uiSoundLdws,				sizeof(uiSoundLdws),			SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_LCAWS_TONE 		},
	{ uiSoundFcw,				sizeof(uiSoundFcw), 			SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_RCW_TONE			},
	{ uiSoundSnG,				sizeof(uiSoundSnG), 			SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_VIRTUAL_BUMPERS_TONE},
#endif  // #if (_ADAS_FUNC_ == ENABLE)
//#NT#2016/07/20#Brain Yen -begin
//#NT#DDD alarm sound
#if (_DDD_FUNC_ == ENABLE)
	{ uiSound_DDDWarning1,		sizeof(uiSound_DDDWarning1),	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_DDDWARNING1_TONE	},
	{ uiSound_DDDWarning2,		sizeof(uiSound_DDDWarning2),	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_DDDWARNING2_TONE	},
	{ uiSound_DDDWarning3,		sizeof(uiSound_DDDWarning3),	SOUND_AUDIO_SR, TRUE, DEMOSOUND_SOUND_DDDWARNING3_TONE	},
#endif  //#if (_DDD_FUNC_ == ENABLE)
//#NT#2016/07/20#Brain Yen -end
#if (_GPS_EDOG_UNIQUE_SKY_==ENABLE)
	{ uiSound_EP_0,				sizeof(uiSound_EP_0),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP0_TONE_WRONGDIRECT	},
	{ uiSound_EP_1,				sizeof(uiSound_EP_1),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP1_TONE_CAMERA_OVERSPEED	},
	{ uiSound_EP_2,				sizeof(uiSound_EP_2),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP2_TONE_CAMERA_FXIED },
	{ uiSound_EP_3,				sizeof(uiSound_EP_3),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP3_TONE_RADAR_SPEED_DETECT },
	{ uiSound_EP_4,				sizeof(uiSound_EP_4),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP4_TONE_CAMERA_BRIDGE_UP },
	{ uiSound_EP_5,				sizeof(uiSound_EP_5),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP5_TONE_GPS_OK },
	{ uiSound_EP_6,				sizeof(uiSound_EP_6),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP6_TONE_HIGHWAY_ENTER },
	{ uiSound_EP_7,				sizeof(uiSound_EP_7),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP7_TONE_OIL_STATION },
	{ uiSound_EP_8,				sizeof(uiSound_EP_8),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP8_TONE_CAMERA_BRIDGE_FIXED },
	{ uiSound_EP_9,				sizeof(uiSound_EP_9),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP9_TONE_CAMERA_HIGHWAY_FIXED },
	{ uiSound_EP_10,			sizeof(uiSound_EP_10),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP10_TONE_CAMERA_HIGHWAY_RADAR },
	{ uiSound_EP_11,			sizeof(uiSound_EP_11),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP11_TONE_BIG_BEND	},
	{ uiSound_EP_12,			sizeof(uiSound_EP_12),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP12_TONE_M	},//no use 172
	{ uiSound_EP_13,			sizeof(uiSound_EP_13),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP13_TONE_DIANZIJIANKONG	},
	{ uiSound_EP_14,			sizeof(uiSound_EP_14),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP14_TONE_CAMERA_BRIDGE_DOWN	},
	{ uiSound_EP_15,			sizeof(uiSound_EP_15),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP15_TONE_SINGLE_ROAD	},
	{ uiSound_EP_16,			sizeof(uiSound_EP_16),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP16_TONE_TIELUKOU	},//no use
	{ uiSound_EP_17,			sizeof(uiSound_EP_17),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP17_TONE_BUS_ROAD	},
	{ uiSound_EP_18,			sizeof(uiSound_EP_18),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP18_TONE_DANGE_ROAD	},
	{ uiSound_EP_19,			sizeof(uiSound_EP_19),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP19_TONE_CAREFULLY_DRIVE	},
	{ uiSound_EP_20,			sizeof(uiSound_EP_20),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP20_TONE_TURNON_LIGHT	},
	{ uiSound_EP_21,			sizeof(uiSound_EP_21),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP21_TONE	},
	{ uiSound_EP_22,			sizeof(uiSound_EP_22),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP22_TONE_REST_STATION	},
	{ uiSound_EP_23,			sizeof(uiSound_EP_23),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP23_TONE_HOLE_ENTER	},
	{ uiSound_EP_24,			sizeof(uiSound_EP_24),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP24_TONE_SELECT_A_ROAD	},
	{ uiSound_EP_25,			sizeof(uiSound_EP_25),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP25_TONE_SPEED_TEST_START	},
	{ uiSound_EP_26,			sizeof(uiSound_EP_26),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP26_TONE_SCHOOL_AREA	},
	{ uiSound_EP_27,			sizeof(uiSound_EP_27),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP27_TONE_CHECK_TRAFFIC_LAW	},
	{ uiSound_EP_28,			sizeof(uiSound_EP_28),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP28_TONE_FORBID_PARKING	},
	{ uiSound_EP_29,			sizeof(uiSound_EP_29),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP29_TONE_DOWNHILL	},
	{ uiSound_EP_30,			sizeof(uiSound_EP_30),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP30_TONE_JIAOLIUDAO	},
	{ uiSound_EP_31,			sizeof(uiSound_EP_31),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP31_TONE_FORBID_TURNLEFT	},

	{ uiSound_EP_32,			sizeof(uiSound_EP_32),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP32_TONE_HIGH_BRIDGE_RED_LIGHT	},
	{ uiSound_EP_33,			sizeof(uiSound_EP_33),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP33_TONE_ON_LINE_PHOTO	},
	{ uiSound_EP_34,			sizeof(uiSound_EP_34),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP34_TONE_TOLL_STATION	},//no use
	{ uiSound_EP_35,			sizeof(uiSound_EP_35),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP35_TONE_END_TESTSPEED_AREA	},
	{ uiSound_EP_36,			sizeof(uiSound_EP_36),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP36_TONE_PLEASE_SLOW_DOWN	},
	{ uiSound_EP_37,			sizeof(uiSound_EP_37),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP37_TONE_DRINK_DRIVE	},
	{ uiSound_EP_38,			sizeof(uiSound_EP_38),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP38_TONE_GAS_STATION	},//no use
	{ uiSound_EP_39,			sizeof(uiSound_EP_39),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP39_TONE_HIGHWAY_EXIT	},
	{ uiSound_EP_42,			sizeof(uiSound_EP_42),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP42_TONE_DIDONG	},
	{ uiSound_EP_43,			sizeof(uiSound_EP_43),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP43_TONE_DONDDD	},
	{ uiSound_EP_44,			sizeof(uiSound_EP_44),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP44_TONE_CARE_FRONT1	},
	{ uiSound_EP_45,			sizeof(uiSound_EP_45),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP45_TONE_FRONT	},
	{ uiSound_EP_46,			sizeof(uiSound_EP_46),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP46_TONE_CARE_FRONT2   },
	{ uiSound_EP_51,			sizeof(uiSound_EP_51),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP51_TONE_OVERSPEED   },
	{ uiSound_EP_75,			sizeof(uiSound_EP_75),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP75_TONE_100   },
	{ uiSound_EP_76,			sizeof(uiSound_EP_76),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP76_TONE_200   },
	{ uiSound_EP_77,			sizeof(uiSound_EP_77),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP77_TONE_300   },
	{ uiSound_EP_78,			sizeof(uiSound_EP_78),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP78_TONE_400   },
	{ uiSound_EP_79,			sizeof(uiSound_EP_79),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP79_TONE_500   },
	{ uiSound_EP_80,			sizeof(uiSound_EP_80),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP80_TONE_600   },
	{ uiSound_EP_81,			sizeof(uiSound_EP_81),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP81_TONE_700   },
	{ uiSound_EP_82,			sizeof(uiSound_EP_82),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP82_TONE_800   },
	{ uiSound_EP_87, 			sizeof(uiSound_EP_87), 			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP87_TONE_20KM	},
	{ uiSound_EP_88,			sizeof(uiSound_EP_88),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP88_TONE_30KM   },
	{ uiSound_EP_89,			sizeof(uiSound_EP_89),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP89_TONE_40KM	},
	{ uiSound_EP_90,			sizeof(uiSound_EP_90),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP90_TONE_50KM	},
	{ uiSound_EP_91,			sizeof(uiSound_EP_91),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP91_TONE_60KM },
	{ uiSound_EP_92,			sizeof(uiSound_EP_92),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP92_TONE_70KM },
	{ uiSound_EP_93,			sizeof(uiSound_EP_93),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP93_TONE_80KM },
	{ uiSound_EP_94,			sizeof(uiSound_EP_94),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP94_TONE_90KM },
	{ uiSound_EP_95,			sizeof(uiSound_EP_95),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP95_TONE_100KM },
	{ uiSound_EP_96,			sizeof(uiSound_EP_96),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP96_TONE_110KM },
	{ uiSound_EP_97,			sizeof(uiSound_EP_97),			SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_EP97_TONE_120KM },
	{ uiSound_EP_kejizhifa,		sizeof(uiSound_EP_kejizhifa),	SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_KEJIZHIFA },
	{ uiSound_EP_xiansu, 		sizeof(uiSound_EP_xiansu), 		SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_XIANSU },
#endif
	{ uiSoundKey,				sizeof(uiSoundKey),				SOUND_AUDIO_SR, TRUE,	DEMOSOUND_SOUND_DDD_TONE },


};
#endif

static volatile BOOL        bKeyToneEn = TRUE;

void UISound_RegTable(void)
{
	#if (AUDIO_FUNC == ENABLE && WAV_PLAY_FUNC == DISABLE) // GxSound_Play conflicts with WavPlay
	ER retV = E_OK;
	retV = GxSound_SetSoundTable
		   ((UINT32)DEMOSOUND_SOUND_MAX_CNT, (PSOUND_DATA)&gDemo_Sound[0]);
	if (retV != E_OK) {
		DBG_ERR("Set SoundData Fail:%d\r\n", retV);
	}
	#endif
}

void UISound_EnableKey(BOOL bEn)
{
	bKeyToneEn = bEn;
}
UINT32 UIVoice_GetVolume(void)
{
    UINT32 vol_value = 95;
	switch(UI_GetData(FL_VOLUME))
	{
	case VOLUME20:
		vol_value = 20;
		break;
	case VOLUME40:
		vol_value = 40;
		break;
	case VOLUME60:
		vol_value = 60;
		break;
	case VOLUME80:
		vol_value = 80;
		break;
	case VOLUME100:
		vol_value = 95;
		break;
	case VOLUME_MUTE:
		vol_value = 0;
		break;
	default:
		vol_value = 95;
		break;
	}
	return vol_value;
}

void UISound_Play(UINT32 index)
{
	if (bKeyToneEn == FALSE) {
		return;
	}
	if(UI_GetData(FL_VOLUME)!= VOLUME_MUTE)
	{
		if((index > DEMOSOUND_SOUND_NONE) && (index < DEMOSOUND_SOUND_POWERON_TONE))//key
		{
			if(UI_GetData(FL_BEEP)== BEEP_ON)
			{
				GxSound_WaitStop();
				GxSound_SetVolume(UIVoice_GetVolume());
				GxSound_Play(index);
			}
		}
		else//other sound
		{
			GxSound_WaitStop();
			GxSound_SetVolume(UIVoice_GetVolume());
			GxSound_Play(index);
		}
	}

	#if 0//(AUDIO_FUNC == ENABLE && WAV_PLAY_FUNC == DISABLE) // GxSound_Play conflicts with WavPlay
	//#NT#2015/10/16#Do not play sound if previous sound is still playing#KCHong
	//if (UI_GetData(FL_BEEP)== BEEP_ON)
	if (UI_GetData(FL_BEEP) != BEEP_OFF /*&& GxSound_IsPlaying() == FALSE*/) {
#if _TODO
		UINT32 AdasDebugMode = 0;
		if ((AdasDebugMode = ADAS_IsAdasDebug()) != 0) {
			// This is a test code for adas debug mode, mute alarm sound
			GxSound_SetVolume((AdasDebugMode & 0x7f));
		}
#endif
#if 0
		if((index == DEMOSOUND_SOUND_MICEN_TONE) ||							\
			(index == DEMOSOUND_SOUND_MICDIS_TONE) || 						\
			(index == DEMOSOUND_SOUND_MCARDERRORFORMAT_TONE) ||			\
			(index == DEMOSOUND_SOUND_MCARDFORMATFAIL_TONE) || 			\
			(index == DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_TONE) || 	\
			(index == DEMOSOUND_SOUND_PARRECORDSTART_TONE) || 				\
			(index == DEMOSOUND_SOUND_PINSERTCARD_TONE) || 					\
			(index == DEMOSOUND_SOUND_RECORDINGSTART_TONE) || 				\
			(index == DEMOSOUND_SOUND_VIDEOPROTECT_TONE) || 				\
			(index == DEMOSOUND_SOUND_WIFICONNECT_TONE) || 					\
			(index == DEMOSOUND_SOUND_WIFIDISABLE_TONE) || 					\
			(index == DEMOSOUND_SOUND_WIFIENADLE_TONE) ) {
			GxSound_SetVolume(75);
		} else {
			GxSound_SetVolume(70);
		}
#endif
		
		//printf("call UISound_Play = %d\r\n",index);
		GxSound_SetVolume(vol_value);
        switch (UI_GetData(FL_BEEP)) {
        case BEEP_OFF:
            break;

        case BUTTON_BEEP:
            if ((index == DEMOSOUND_SOUND_KEY_TONE)
                /*|| (index == DEMOSOUND_SOUND_LDWS_TONE)
                || (index == DEMOSOUND_SOUND_FCS_TONE)*/)
            {
                GxSound_Play(index);
            }
            break;

        case START_SOUND:
            if(/*(index == DEMOSOUND_SOUND_KEY_TONE)
                ||*/ (index == DEMOSOUND_SOUND_POWERON_TONE)
                /*|| (index == DEMOSOUND_SOUND_LDWS_TONE)
                || (index == DEMOSOUND_SOUND_FCS_TONE)*/)
            {
                GxSound_Play(index);
            }
            break;

        case BEEP_ON:
            GxSound_Play(index);
            break;
        }
	}
	#endif
}
//@}

UINT32 UIVoice_GetIndex(UINT32 index)
{

	switch(index) {
	case DEMOSOUND_SOUND_MICEN_TONE:
		switch(SysGetFlag(FL_LANGUAGE)) {
#if 1
		case LANG_TC:
		case LANG_SC:
			index = DEMOSOUND_SOUND_MICEN_CHINESE_TONE;
		break;
		
		case LANG_RU:
			index = DEMOSOUND_SOUND_MICEN_RUSSIAN_TONE;
		break;

		case LANG_TR:
			index = DEMOSOUND_SOUND_MICEN_TURKEY_TONE;
		break;

		case LANG_RO:
			index = DEMOSOUND_SOUND_MICEN_ROM_TONE;
		break;
		
		case LANG_PL:
			index = DEMOSOUND_SOUND_MICEN_POLISH_TONE;
		break;

		case LANG_CZ:
			index = DEMOSOUND_SOUND_MICEN_CESKA_TONE;
		break;

		case LANG_SK:
			index = DEMOSOUND_SOUND_MICEN_SLOVEN_TONE;
		break;

		case LANG_ES:
			index = DEMOSOUND_SOUND_MICEN_SPANISH_TONE;
		break;

		case LANG_DE:
			index = DEMOSOUND_SOUND_MICEN_DEUTSCH_TONE;
		break;

		case LANG_IT:
			index = DEMOSOUND_SOUND_MICEN_ITALIAN_TONE;
		break;

		case LANG_JP:
			index = DEMOSOUND_SOUND_MICEN_JAPANESE_TONE;
		break;

		case LANG_FR:
			index = DEMOSOUND_SOUND_MICEN_FRANCE_TONE;
		break;
#endif		
		default:
			index = DEMOSOUND_SOUND_MICEN_ENGLISH_TONE;
		}
	break;

	case DEMOSOUND_SOUND_MICDIS_TONE:
		switch(SysGetFlag(FL_LANGUAGE)) {
#if 1
		case LANG_TC:
		case LANG_SC:
			index = DEMOSOUND_SOUND_MICDIS_CHINESE_TONE;
		break;

		case LANG_RU:
			index = DEMOSOUND_SOUND_MICDIS_RUSSIAN_TONE;
		break;

		case LANG_TR:
			index = DEMOSOUND_SOUND_MICDIS_TURKEY_TONE;
		break;
		
		case LANG_RO:
			index = DEMOSOUND_SOUND_MICEN_ROM_TONE;
		break;

		case LANG_PL:
			index = DEMOSOUND_SOUND_MICDIS_POLISH_TONE;
		break;
		
		case LANG_CZ:
			index = DEMOSOUND_SOUND_MICDIS_CESKA_TONE;
		break;

		case LANG_SK:
			index = DEMOSOUND_SOUND_MICDIS_SLOVEN_TONE;
		break;

		case LANG_ES:
			index = DEMOSOUND_SOUND_MICDIS_SPANISH_TONE;
		break;

		case LANG_DE:
			index = DEMOSOUND_SOUND_MICDIS_DEUTSCH_TONE;
		break;

		case LANG_IT:
			index = DEMOSOUND_SOUND_MICDIS_ITALIAN_TONE;
		break;
		
		case LANG_JP:
			index = DEMOSOUND_SOUND_MICDIS_JAPANESE_TONE;
		break;

		case LANG_FR:
			index = DEMOSOUND_SOUND_MICDIS_FRANCE_TONE;
		break;
#endif
		default:
			index = DEMOSOUND_SOUND_MICDIS_ENGLISH_TONE;
		}
	break;

	case DEMOSOUND_SOUND_MCARDERRORFORMAT_TONE:
		switch(SysGetFlag(FL_LANGUAGE)) {
#if 1
		case LANG_TC:
		case LANG_SC:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_CHINESE_TONE;
		break;

		case LANG_RU:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_RUSSIAN_TONE;
		break;

		case LANG_TR:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_TURKEY_TONE;
		break;
		
		case LANG_RO:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_ROM_TONE;
		break;

		case LANG_PL:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_POLISH_TONE;
		break;
		
		case LANG_CZ:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_CESKA_TONE;
		break;

		case LANG_SK:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_SLOVEN_TONE;
		break;

		case LANG_ES:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_SPANISH_TONE;
		break;
		
		case LANG_DE:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_DEUTSCH_TONE;
		break;

		case LANG_IT:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_ITALIAN_TONE;
		break;

		case LANG_JP:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_JAPANESE_TONE;
		break;

		case LANG_FR:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_FRANCE_TONE;
		break;
#endif
		default:
			index = DEMOSOUND_SOUND_MCARDERRORFORMAT_ENGLISH_TONE;
		}
	break;	

	case DEMOSOUND_SOUND_MCARDFORMATFAIL_TONE:
		switch(SysGetFlag(FL_LANGUAGE)) {
#if 1
		case LANG_TC:
		case LANG_SC:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_CHINESE_TONE;
		break;
		
		case LANG_RU:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_RUSSIAN_TONE;
		break;

		case LANG_TR:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_TURKEY_TONE;
		break;

		case LANG_RO:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_ROM_TONE;
		break;

		case LANG_PL:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_POLISH_TONE;
		break;

		case LANG_CZ:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_CESKA_TONE;
		break;

		case LANG_SK:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_SLOVEN_TONE;
		break;

		case LANG_ES:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_SPANISH_TONE;
		break;

		case LANG_DE:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_DEUTSCH_TONE;
		break;

		case LANG_IT:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_ITALIAN_TONE;
		break;

		case LANG_JP:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_JAPANESE_TONE;
		break;

		case LANG_FR:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_FRANCE_TONE;
		break;
#endif
		default:
			index = DEMOSOUND_SOUND_MCARDFORMATFAIL_ENGLISH_TONE;
		}
	break;

	case DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_TONE:
		switch(SysGetFlag(FL_LANGUAGE)) {
#if 1
		case LANG_TC:
		case LANG_SC:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_CHINESE_TONE;
		break;

		case LANG_RU:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_RUSSIAN_TONE;
		break;

		case LANG_TR:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_TURKEY_TONE;
		break;

		case LANG_RO:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_ROM_TONE;
		break;

		case LANG_PL:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_POLISH_TONE;
		break;

		case LANG_CZ:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_CESKA_TONE;
		break;

		case LANG_SK:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_SLOVEN_TONE;
		break;

		case LANG_ES:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_SPANISH_TONE;
		break;

		case LANG_DE:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_DEUTSCH_TONE;
		break;

		case LANG_IT:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_ITALIAN_TONE;
		break;

		case LANG_JP:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_JAPANESE_TONE;
		break;

		case LANG_FR:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_FRANCE_TONE;
		break;
#endif
		default:
			index = DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_ENGLISH_TONE;
		}
	break;

	case DEMOSOUND_SOUND_PARRECORDSTART_TONE:
		switch(SysGetFlag(FL_LANGUAGE)) {
#if 1
		case LANG_TC:
		case LANG_SC:
			index = DEMOSOUND_SOUND_PARRECORDSTART_CHINESE_TONE;
		break;
		
		case LANG_RU:
			index = DEMOSOUND_SOUND_PARRECORDSTART_RUSSIAN_TONE;
		break;

		case LANG_TR:
			index = DEMOSOUND_SOUND_PARRECORDSTART_TURKEY_TONE;
		break;

		case LANG_RO:
			index = DEMOSOUND_SOUND_PARRECORDSTART_ROM_TONE;
		break;
		
		case LANG_PL:
			index = DEMOSOUND_SOUND_PARRECORDSTART_POLISH_TONE;
		break;

		case LANG_CZ:
			index = DEMOSOUND_SOUND_PARRECORDSTART_CESKA_TONE;
		break;

		case LANG_SK:
			index = DEMOSOUND_SOUND_PARRECORDSTART_SLOVEN_TONE;
		break;

		case LANG_ES:
			index = DEMOSOUND_SOUND_PARRECORDSTART_SPANISH_TONE;
		break;

		case LANG_DE:
			index = DEMOSOUND_SOUND_PARRECORDSTART_DEUTSCH_TONE;
		break;

		case LANG_IT:
			index = DEMOSOUND_SOUND_PARRECORDSTART_ITALIAN_TONE;
		break;

		case LANG_JP:
			index = DEMOSOUND_SOUND_PARRECORDSTART_JAPANESE_TONE;
		break;

		case LANG_FR:
			index = DEMOSOUND_SOUND_PARRECORDSTART_FRANCE_TONE;
		break;
#endif
		default:
			index = DEMOSOUND_SOUND_PARRECORDSTART_ENGLISH_TONE;
		}
	break;

	case DEMOSOUND_SOUND_PINSERTCARD_TONE:
		switch(SysGetFlag(FL_LANGUAGE)) {
#if 1
		case LANG_TC:
		case LANG_SC:
			index = DEMOSOUND_SOUND_PINSERTCARD_CHINESE_TONE;
		break;

		case LANG_RU:
			index = DEMOSOUND_SOUND_PINSERTCARD_RUSSIAN_TONE;
		break;

		case LANG_TR:
			index = DEMOSOUND_SOUND_PINSERTCARD_TURKEY_TONE;
		break;

		case LANG_RO:
			index = DEMOSOUND_SOUND_PINSERTCARD_ROM_TONE;
		break;

		case LANG_PL:
			index = DEMOSOUND_SOUND_PINSERTCARD_POLISH_TONE;
		break;

		case LANG_CZ:
			index = DEMOSOUND_SOUND_PINSERTCARD_CESKA_TONE;
		break;

		case LANG_SK:
			index = DEMOSOUND_SOUND_PINSERTCARD_SLOVEN_TONE;
		break;

		case LANG_ES:
			index = DEMOSOUND_SOUND_PINSERTCARD_SPANISH_TONE;
		break;

		case LANG_DE:
			index = DEMOSOUND_SOUND_PINSERTCARD_DEUTSCH_TONE;
		break;

		case LANG_IT:
			index = DEMOSOUND_SOUND_PINSERTCARD_ITALIAN_TONE;
		break;

		case LANG_JP:
			index = DEMOSOUND_SOUND_PINSERTCARD_JAPANESE_TONE;
		break;

		case LANG_FR:
			index = DEMOSOUND_SOUND_PINSERTCARD_FRANCE_TONE;
		break;
#endif
		default:
			index = DEMOSOUND_SOUND_PINSERTCARD_ENGLISH_TONE;
		}
	break;
	
	case DEMOSOUND_SOUND_RECORDINGSTART_TONE:
		switch(SysGetFlag(FL_LANGUAGE)) {
#if 1
		case LANG_TC:
		case LANG_SC:
			index = DEMOSOUND_SOUND_RECORDINGSTART_CHINESE_TONE;
		break;

		case LANG_RU:
			index = DEMOSOUND_SOUND_RECORDINGSTART_RUSSIAN_TONE;
		break;

		case LANG_TR:
			index = DEMOSOUND_SOUND_RECORDINGSTART_TURKEY_TONE;
		break;

		case LANG_RO:
			index = DEMOSOUND_SOUND_RECORDINGSTART_ROM_TONE;
		break;

		case LANG_PL:
			index = DEMOSOUND_SOUND_RECORDINGSTART_POLISH_TONE;
		break;

		case LANG_CZ:
			index = DEMOSOUND_SOUND_RECORDINGSTART_CESKA_TONE;
		break;

		case LANG_SK:
			index = DEMOSOUND_SOUND_RECORDINGSTART_SLOVEN_TONE;
		break;

		case LANG_ES:
			index = DEMOSOUND_SOUND_RECORDINGSTART_SPANISH_TONE;
		break;

		case LANG_DE:
			index = DEMOSOUND_SOUND_RECORDINGSTART_DEUTSCH_TONE;
		break;

		case LANG_IT:
			index = DEMOSOUND_SOUND_RECORDINGSTART_ITALIAN_TONE;
		break;

		case LANG_JP:
			index = DEMOSOUND_SOUND_RECORDINGSTART_JAPANESE_TONE;
		break;

		case LANG_FR:
			index = DEMOSOUND_SOUND_RECORDINGSTART_FRANCE_TONE;
		break;
#endif
		default:
			index = DEMOSOUND_SOUND_RECORDINGSTART_ENGLISH_TONE;
		}
	break;

	case DEMOSOUND_SOUND_VIDEOPROTECT_TONE:
		switch(SysGetFlag(FL_LANGUAGE)) {
#if 1
		case LANG_TC:
		case LANG_SC:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_CHINESE_TONE;
		break;

		case LANG_RU:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_RUSSIAN_TONE;
		break;

		case LANG_TR:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_TURKEY_TONE;
		break;

		case LANG_RO:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_ROM_TONE;
		break;

		case LANG_PL:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_POLISH_TONE;
		break;

		case LANG_CZ:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_CESKA_TONE;
		break;

		case LANG_SK:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_SLOVEN_TONE;
		break;

		case LANG_ES:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_SPANISH_TONE;
		break;

		case LANG_DE:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_DEUTSCH_TONE;
		break;

		case LANG_IT:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_ITALIAN_TONE;
		break;

		case LANG_JP:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_JAPANESE_TONE;
		break;

		case LANG_FR:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_FRANCE_TONE;
		break;
#endif
		default:
			index = DEMOSOUND_SOUND_VIDEOPROTECT_ENGLISH_TONE;
		}
	break;

	case DEMOSOUND_SOUND_WIFICONNECT_TONE:
		switch(SysGetFlag(FL_LANGUAGE)) {
#if 1
		case LANG_TC:
		case LANG_SC:
			index = DEMOSOUND_SOUND_WIFICONNECT_CHINESE_TONE;
		break;

		case LANG_RU:
			index = DEMOSOUND_SOUND_WIFICONNECT_RUSSIAN_TONE;
		break;

		case LANG_TR:
			index = DEMOSOUND_SOUND_WIFICONNECT_TURKEY_TONE;
		break;

		case LANG_RO:
			index = DEMOSOUND_SOUND_WIFICONNECT_ROM_TONE;
		break;

		case LANG_PL:
			index = DEMOSOUND_SOUND_WIFICONNECT_POLISH_TONE;
		break;

		case LANG_CZ:
			index = DEMOSOUND_SOUND_WIFICONNECT_CESKA_TONE;
		break;

		case LANG_SK:
			index = DEMOSOUND_SOUND_WIFICONNECT_SLOVEN_TONE;
		break;

		case LANG_ES:
			index = DEMOSOUND_SOUND_WIFICONNECT_SPANISH_TONE;
		break;			

		case LANG_DE:
			index = DEMOSOUND_SOUND_WIFICONNECT_DEUTSCH_TONE;
		break;

		case LANG_IT:
			index = DEMOSOUND_SOUND_WIFICONNECT_ITALIAN_TONE;
		break;

		case LANG_JP:
			index = DEMOSOUND_SOUND_WIFICONNECT_JAPANESE_TONE;
		break;

		case LANG_FR:
			index = DEMOSOUND_SOUND_WIFICONNECT_FRANCE_TONE;
		break;
#endif
		default:
			index = DEMOSOUND_SOUND_WIFICONNECT_ENGLISH_TONE;
		}
	break;

	case DEMOSOUND_SOUND_WIFIDISABLE_TONE:
		switch(SysGetFlag(FL_LANGUAGE)) {
#if 1
		case LANG_TC:
		case LANG_SC:
			index = DEMOSOUND_SOUND_WIFIDISABLE_CHINESE_TONE;
		break;

		case LANG_RU:
			index = DEMOSOUND_SOUND_WIFIDISABLE_RUSSIAN_TONE;
		break;

		case LANG_TR:
			index = DEMOSOUND_SOUND_WIFIDISABLE_TURKEY_TONE;
		break;

		case LANG_RO:
			index = DEMOSOUND_SOUND_WIFIDISABLE_ROM_TONE;
		break;

		case LANG_PL:
			index = DEMOSOUND_SOUND_WIFIDISABLE_POLISH_TONE;
		break;

		case LANG_CZ:
			index = DEMOSOUND_SOUND_WIFIDISABLE_CESKA_TONE;
		break;

		case LANG_SK:
			index = DEMOSOUND_SOUND_WIFIDISABLE_SLOVEN_TONE;
		break;

		case LANG_ES:
			index = DEMOSOUND_SOUND_WIFIDISABLE_SPANISH_TONE;
		break;

		case LANG_DE:
			index = DEMOSOUND_SOUND_WIFIDISABLE_DEUTSCH_TONE;
		break;

		case LANG_IT:
			index = DEMOSOUND_SOUND_WIFIDISABLE_ITALIAN_TONE;
		break;

		case LANG_JP:
			index = DEMOSOUND_SOUND_WIFIDISABLE_JAPANESE_TONE;
		break;

		case LANG_FR:
			index = DEMOSOUND_SOUND_WIFIDISABLE_FRANCE_TONE;
		break;
#endif
		default:
			index = DEMOSOUND_SOUND_WIFIDISABLE_ENGLISH_TONE;
		}
	break;

	case DEMOSOUND_SOUND_WIFIENADLE_TONE:
		switch(SysGetFlag(FL_LANGUAGE)) {
#if 1
		case LANG_TC:
		case LANG_SC:
			index = DEMOSOUND_SOUND_WIFIENADLE_CHINESE_TONE;
		break;

		case LANG_RU:
			index = DEMOSOUND_SOUND_WIFIENADLE_RUSSIAN_TONE;
		break;

		case LANG_TR:
			index = DEMOSOUND_SOUND_WIFIENADLE_TURKEY_TONE;
		break;

		case LANG_RO:
			index = DEMOSOUND_SOUND_WIFIENADLE_ROM_TONE;
		break;

		case LANG_PL:
			index = DEMOSOUND_SOUND_WIFIENADLE_POLISH_TONE;
		break;

		case LANG_CZ:
			index = DEMOSOUND_SOUND_WIFIENADLE_CESKA_TONE;
		break;

		case LANG_SK:
			index =  DEMOSOUND_SOUND_WIFIENADLE_SLOVEN_TONE;
		break;

		case LANG_ES:
			index = DEMOSOUND_SOUND_WIFIENADLE_SPANISH_TONE;
		break;

		case LANG_DE:
			index = DEMOSOUND_SOUND_WIFIENADLE_DEUTSCH_TONE;
		break;

		case LANG_IT:
			index = DEMOSOUND_SOUND_WIFIENADLE_ITALIAN_TONE;
		break;

		case LANG_JP:
			index = DEMOSOUND_SOUND_WIFIENADLE_JAPANESE_TONE;
		break;

		case LANG_FR:
			index = DEMOSOUND_SOUND_WIFIENADLE_FRANCE_TONE;
		break;
#endif
		default:
			index = DEMOSOUND_SOUND_WIFIENADLE_ENGLISH_TONE;
		}
	break;
	
	}

	return index;


}
void UIVoice_Play(UINT32 index)
{
#if 1
	UINT32 Voice_Index = 0;
	if (bKeyToneEn == FALSE) {
		return;
	}
	
	#if (AUDIO_FUNC == ENABLE && WAV_PLAY_FUNC == DISABLE) // GxSound_Play conflicts with WavPlay
	//#NT#2015/10/16#Do not play sound if previous sound is still playing#KCHong
	//if (UI_GetData(FL_BEEP)== BEEP_ON)
	if (GxSound_IsPlaying() == FALSE) {
#if _TODO
		UINT32 AdasDebugMode = 0;
		if ((AdasDebugMode = ADAS_IsAdasDebug()) != 0) {
			// This is a test code for adas debug mode, mute alarm sound
			GxSound_SetVolume((AdasDebugMode & 0x7f));
		}
#endif

#if 0
		if((index == DEMOSOUND_SOUND_MICEN_TONE) ||							\
			(index == DEMOSOUND_SOUND_MICDIS_TONE) || 						\
			(index == DEMOSOUND_SOUND_MCARDERRORFORMAT_TONE) ||			\
			(index == DEMOSOUND_SOUND_MCARDFORMATFAIL_TONE) || 			\
			(index == DEMOSOUND_SOUND_MCARDFORMATSUCCESSFUL_TONE) || 	\
			(index == DEMOSOUND_SOUND_PARRECORDSTART_TONE) || 				\
			(index == DEMOSOUND_SOUND_PINSERTCARD_TONE) || 					\
			(index == DEMOSOUND_SOUND_RECORDINGSTART_TONE) || 				\
			(index == DEMOSOUND_SOUND_VIDEOPROTECT_TONE) || 				\
			(index == DEMOSOUND_SOUND_WIFICONNECT_TONE) || 					\
			(index == DEMOSOUND_SOUND_WIFIDISABLE_TONE) || 					\
			(index == DEMOSOUND_SOUND_WIFIENADLE_TONE) ) {
			GxSound_SetVolume(80);
		} else {
			GxSound_SetVolume(75);
		}
#endif
        Voice_Index = UIVoice_GetIndex(index);
        GxSound_SetVolume(UIVoice_GetVolume());	
        switch (UI_GetData(FL_MOVIE_VOICE)) {
        case MOVIE_VOICE_OFF:
            break;
        case MOVIE_VOICE_ON:
		GxSound_Play(Voice_Index);
            break;
        }
        }
	#endif
#endif
}

#if 1//(E_DOG_FUNCTION == ENABLE)
//#YND#2019/03/28  #@LHB
static volatile BOOL        bdogToneEn = TRUE;
UINT32 SoundSelectstatic[50]={0};

void UIDogSound_Enable(BOOL bEn)
{
    bdogToneEn = bEn;
}


void UIDogSound_Play(UINT32 index)
{
	//debug_msg("=========SoID= %d ==========\r\n",index);
	GxSound_SetVolume(UIVoice_GetVolume());	
	GxSound_WaitStop();
    GxSound_Play(index);	
	GxSound_WaitStop();
}

void DogSoundPlayID(UINT32 SoID)
{
   UINT32 i;
   for(i=0;i<=50;i++)
   {
     //debug_msg("24161.GPSoundPlayID.FileSelectstatic[%d] = %d SoID= %d \r\n",i,SoundSelectstatic[i],SoID);  
      if(SoundSelectstatic[i]==0)
      	{
          SoundSelectstatic[i]=SoID;
	   	  //debug_msg("24154.GPSoundPlayID.FileSelectstatic[%d] = %d SoID= %d \r\n",i,SoundSelectstatic[i],SoID);
	  	  break;
		}
   }
}

//static UINT32 soundID = 0;
void DogSoundPlayFun(void)
{
	//debug_msg("GPSSoundPlayFun.GxSound_IsPlaying= %d \r\n",GxSound_IsPlaying());
	if (bdogToneEn == FALSE)
	{
	  return;
	}

	for(UINT32 i = 0; i < 50; i++)
	{
	    if(SoundSelectstatic[i] != 0)
	    {
	        UIDogSound_Play(SoundSelectstatic[i]);
	        SoundSelectstatic[i] = 0;  // ²¥·ÅºóÇå³ý
	    }
	}
}

void DogSoundCycPlay(void)
{
   DogSoundPlayFun();
}
#endif


