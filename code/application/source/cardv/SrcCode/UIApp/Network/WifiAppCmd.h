#ifndef _WIFIAPPCMD_H_
#define _WIFIAPPCMD_H_

#include "kwrap/type.h"
#include "UIApp/WifiCmdParser/WifiCmdParser.h"
/**
    @name EXT_CMD_ITEM command from APP.
*/
//@{
//photo mode command
#define WIFIAPP_CMD_CAPTURE              1001
#define WIFIAPP_CMD_CAPTURESIZE          1002
#define WIFIAPP_CMD_FREE_PIC_NUM         1003

//movie mode command
#define WIFIAPP_CMD_RECORD                    2001
#define WIFIAPP_CMD_MOVIE_REC_SIZE            2002
#define WIFIAPP_CMD_CYCLIC_REC                2003
#define WIFIAPP_CMD_MOVIE_WDR                 2004
#define WIFIAPP_CMD_MOVIE_EV                  2005
#define WIFIAPP_CMD_MOTION_DET                2006
#define WIFIAPP_CMD_MOVIE_AUDIO               2007
#define WIFIAPP_CMD_DATEIMPRINT               2008
#define WIFIAPP_CMD_MAX_RECORD_TIME           2009
#define WIFIAPP_CMD_MOVIE_LIVEVIEW_SIZE       2010
#define WIFIAPP_CMD_MOVIE_GSENSOR_SENS        2011
#define WIFIAPP_CMD_SET_AUTO_RECORDING        2012
#define WIFIAPP_CMD_MOVIE_REC_BITRATE         2013
#define WIFIAPP_CMD_MOVIE_LIVEVIEW_BITRATE    2014
#define WIFIAPP_CMD_MOVIE_LIVEVIEW_START      2015
#define WIFIAPP_CMD_MOVIE_RECORDING_TIME      2016
#define WIFIAPP_CMD_MOVIE_REC_TRIGGER_RAWENC  2017
#define WIFIAPP_CMD_MOVIE_GET_RAWENC_JPG      2018
#define WIFIAPP_CMD_MOVIE_GET_LIVEVIEW_FMT    2019
//#NT#2016/06/03#Charlie Chang -begin
//#NT# add contrast, two-way audio , flip_mirror. quality sets
#define WIFIAPP_CMD_MOVIE_CONTRAST            2020
#define WIFIAPP_CMD_TWOWAY_AUDIO              2021
#define WIFIAPP_CMD_TWOWAY_AUDIO_SAMPLERATE   2022
#define WIFIAPP_CMD_FLIP_MIRROR               2023
#define WIFIAPP_CMD_QUALITYSET                2024
//#NT#2016/06/03#Charlie Chang -end
//#NT#2016/12/02#Isiah Chang -begin
//#NT#Add WiFiCmd Bitrate control.
#define WIFIAPP_CMD_MOVIE_BRC_ADJUST          2025
//#NT#2016/12/02#Isiah Chang -end
//HDR Set
#define WIFIAPP_CMD_MOVIE_HDR                 2026
#define WIFIAPP_CMD_SET_HDRDET_TIME       	  2027
#define WIFIAPP_CMD_GET_HDRDET_TIME       	  2028

//setup command
#define WIFIAPP_CMD_MODECHANGE                3001
#define WIFIAPP_CMD_QUERY                     3002
#define WIFIAPP_CMD_SET_SSID                  3003
#define WIFIAPP_CMD_SET_PASSPHRASE            3004
#define WIFIAPP_CMD_SET_DATE                  3005
#define WIFIAPP_CMD_SET_TIME                  3006
#define WIFIAPP_CMD_POWEROFF                  3007
#define WIFIAPP_CMD_LANGUAGE                  3008
#define WIFIAPP_CMD_TVFORMAT                  3009
#define WIFIAPP_CMD_FORMAT                    3010
#define WIFIAPP_CMD_SYSRESET                  3011
#define WIFIAPP_CMD_VERSION                   3012
#define WIFIAPP_CMD_FWUPDATE                  3013
#define WIFIAPP_CMD_QUERY_CUR_STATUS          3014
#define WIFIAPP_CMD_FILELIST                  3015
#define WIFIAPP_CMD_HEARTBEAT                 3016
#define WIFIAPP_CMD_DISK_FREE_SPACE           3017
#define WIFIAPP_CMD_RECONNECT_WIFI            3018
#define WIFIAPP_CMD_GET_BATTERY               3019
#define WIFIAPP_CMD_NOTIFY_STATUS             3020
#define WIFIAPP_CMD_SAVE_MENUINFO             3021
#define WIFIAPP_CMD_GET_HW_CAP                3022
#define WIFIAPP_CMD_REMOVE_USER               3023
#define WIFIAPP_CMD_GET_CARD_STATUS           3024
#define WIFIAPP_CMD_GET_DOWNLOAD_URL          3025
#define WIFIAPP_CMD_GET_UPDATEFW_PATH         3026
#define WIFIAPP_CMD_UPLOAD_FILE               3027
#define WIFIAPP_CMD_SET_PIP_STYLE             3028
#define WIFIAPP_CMD_GET_SSID_PASSPHRASE       3029
#define WIFIAPP_CMD_QUERY_MOVIE_SIZE          3030
#define WIFIAPP_CMD_QUERY_MENUITEM            3031
#define WIFIAPP_CMD_SEND_SSID_PASSPHRASE      3032
#define WIFIAPP_CMD_SET_WIFI_CONNECT_MODE     3033
#define WIFIAPP_CMD_AUTO_TEST_CMD_DONE        3034
//#NT#2016/03/23#Isiah Chang -begin
//#NT#add new Wi-Fi UI flow.
#define WIFIAPP_CMD_APP_STARTUP               3035
#define WIFIAPP_CMD_APP_SESSION_CLOSE         3036
//#NT#2016/03/23#Isiah Chang -end
//#NT#2016/06/01#Isiah Chang -begin
//#NT#add a Wi-Fi command to get current mode status.
#define WIFIAPP_CMD_GET_MODE_STAUTS           3037
//#NT#2016/06/01#Isiah Chang -end
//#NT#2016/06/06#Charlie Chang -begin
//#NT#
#define WIFIAPP_CMD_WIFIAP_SEARCH             3038
//#NT#2016/06/06#Charlie Chang -end

//playback command
#define WIFIAPP_CMD_THUMB                4001
#define WIFIAPP_CMD_SCREEN               4002
#define WIFIAPP_CMD_DELETE_ONE           4003
#define WIFIAPP_CMD_DELETE_ALL           4004
#define WIFIAPP_CMD_MOVIE_FILE_INFO      4005
//@}
//upload command
#define WIFIAPP_CMD_UPLOAD               5001
#define WIFIAPP_CMD_UPLOAD_AUDIO         5002

//user define command
#define WIFIAPP_CMD_USER_START           8001

//photo 9001~9200
#define WIFIAPP_CMD_PHOTO_SHUTTER_SPEED  9001
#define WIFIAPP_CMD_PHOTO_DATE_STAMP     9002
#define WIFIAPP_CMD_PHOTO_INTERVAL       9003
#define WIFIAPP_CMD_PHOTO_SELFTIMER      9004
#define WIFIAPP_CMD_PHOTO_CONTSHOT       9005
#define WIFIAPP_CMD_PHOTO_RAW            9006
#define WIFIAPP_CMD_GET_SELFTIMER_CNT    9007
#define WIFIAPP_CMD_GET_TIMELAPSE_STATE  9008
#define WIFIAPP_CMD_PHOTO_EV             9009
#define WIFIAPP_CMD_PHOTO_WB             9010
#define WIFIAPP_CMD_PHOTO_ISO            9011
#define WIFIAPP_CMD_PHOTO_COLOR          9012
#define WIFIAPP_CMD_PHOTO_SHARPNESS      9013
#define WIFIAPP_CMD_PHOTO_METERING       9014
#define WIFIAPP_CMD_PHOTO_CONTRAST       9015
#define WIFIAPP_CMD_PHOTO_DZOOM          9016
#define WIFIAPP_CMD_PHOTO_GPS_STAMP      9017

//movie 9201~9400
#define WIFIAPP_CMD_LOCK_UNLCOK_VIDEO    9200
#define WIFIAPP_CMD_MOVIE_TIMELAPSE_REC  9201
#define WIFIAPP_CMD_MOVIE_AUDIO_VOL      9202
#define WIFIAPP_CMD_MOVIE_WB             9203
#define WIFIAPP_CMD_MOVIE_ISO            9204
#define WIFIAPP_CMD_MOVIE_COLOR          9205
#define WIFIAPP_CMD_MOVIE_SHARPNESS      9206
#define WIFIAPP_CMD_MOVIE_METERING       9207
#define WIFIAPP_CMD_MOVIE_SHUTTER_SPEED  9208
#define WIFIAPP_CMD_MOVIE_INTERVAL       9209
#define WIFIAPP_CMD_MOVIE_RSC            9210
#define WIFIAPP_CMD_MOVIE_LOWLIGHT       9211
#define WIFIAPP_CMD_MOVIE_BITRATE        9212
#define WIFIAPP_CMD_MOVIE_DZOOM          9213
#define WIFIAPP_CMD_MOVIE_GPS_STAMP      9214
#define WIFIAPP_CMD_MOVIE_SLOW_MOTION    9215
#define WIFIAPP_CMD_MOVIE_MODEL_STAMP    9216
#define WIFIAPP_CMD_MOVIE_EV2            9217
#define WIFIAPP_CMD_IR_REAR_COLOR        9218
#define WIFIAPP_CMD_REAR_SENSOR_MIRROR   9219
#define WIFIAPP_CMD_PARKING_GSENSOR      9220
#define WIFIAPP_CMD_PARKING_MOTION_DET   9221
#define WIFIAPP_CMD_MOVIE_CODEC          9222
#define WIFIAPP_CMD_FRONT_SENSOR_MIRROR  9223
#define WIFIAPP_CMD_CARNO_STAMP			 9224
#define WIFIAPP_CMD_MOVIE_EV3            9225
#define WIFIAPP_CMD_INSIDE_CAMERA		 9226

//setup 9401~9600
#define WIFIAPP_CMD_GET_DATE_TIME        9401
#define WIFIAPP_CMD_START_RF_PAIRING     9402
#define WIFIAPP_CMD_BEEP                 9403
#define WIFIAPP_CMD_OSD                  9404
#define WIFIAPP_CMD_SCREEN_SAVER         9405
#define WIFIAPP_CMD_FREQUENCY            9406
#define WIFIAPP_CMD_GET_MODEL_NAME       9407
#define WIFIAPP_CMD_GET_CURRENT_MODE     9408
#define WIFIAPP_CMD_QUICK_CAPTURE        9409
#define WIFIAPP_CMD_GPS                  9410
#define WIFIAPP_CMD_TIMEZONE             9411
#define WIFIAPP_CMD_SPEEDUNIT            9412
#define WIFIAPP_CMD_SENSOR_ROTATE        9413
#define WIFIAPP_CMD_LED                  9414
#define WIFIAPP_CMD_EXTPOWER             9415
#define WIFIAPP_CMD_DATEFORMAT           9416
#define WIFIAPP_CMD_CUSTOM_STAMP         9417
#define WIFIAPP_CMD_USBMODE              9418
#define WIFIAPP_CMD_WIFI_AUTO            9419
#define WIFIAPP_CMD_FORMAT_WARNING       9420
#define WIFIAPP_CMD_PARKING_MODE         9421
#define WIFIAPP_CMD_SET_CARNO            9422
#define WIFIAPP_CMD_SYSREBOOT            9423
#define WIFIAPP_CMD_BOOTDELAY            9424
#define WIFIAPP_CMD_SENSOR2_ROTATE       9425
#define WIFIAPP_CMD_GET_CARNO            9426
#define WIFIAPP_CMD_GET_CUSTOM_STAMP     9427
#define WIFIAPP_CMD_SHUTDOWNTIMER        9428
#define WIFIAPP_CMD_WATER_LOGO           9429
#define WIFIAPP_CMD_GET_GPS_STATUS       9430
#define WIFIAPP_CMD_GET_SOS_STATUS       9431
#define WIFIAPP_CMD_GET_SENSOR_STATUS    9432
#define WIFIAPP_CMD_LCD_ROTATE           9433
#define WIFIAPP_CMD_SET_STORAGE_TYPE     9434
#define WIFIAPP_CMD_ENTER_PARK_TIMER     9435
#define WIFIAPP_CMD_PHOTO_FILELIST       9436
#define WIFIAPP_CMD_RO_FILELIST          9437
#define WIFIAPP_CMD_GET_GPS_DB           9438
#define WIFIAPP_CMD_SETUP_AMBIANCE_LED   9439 //breath led
#define WIFIAPP_CMD_VIDEO_FORMAT         9440
#define WIFIAPP_CMD_SET_MOVIE_RO         9441
#define WIFIAPP_CMD_TSR                  9442
#define WIFIAPP_CMD_SNG                  9443
#define WIFIAPP_CMD_FATIGUEDRIVING       9444
#define WIFIAPP_CMD_REMINDLIGHT          9445
#define WIFIAPP_CMD_SEND_MD5             9446
#define WIFIAPP_CMD_VOLUME               9447
#define WIFIAPP_CMD_WIFI_BAND            9448
#define WIFIAPP_CMD_MOVIE_VOICE          9449
#define WIFIAPP_CMD_APP_MENU_COMING      9450
#define WIFIAPP_CMD_PARKING_GPS          9451
#define WIFIAPP_CMD_LED_BRIGHTNESS       9452
#define WIFIAPP_CMD_ASR_CONTROL          9453 //ASR
#define WIFIAPP_CMD_ASR_CONTENT          9454
#define WIFIAPP_CMD_SPEEDSHOW            9455
#define WIFIAPP_CMD_PLAY_VOLUME          9456
#define WIFIAPP_CMD_GPS_MODULE			 9457
#define WIFIAPP_CMD_EIS			 		 9458
#define WIFIAPP_CMD_GET_MAC_ADDR     	 9459
#define WIFIAPP_CMD_WIFI_PWD_SHOW     	 9460 //Viofo

#define WIFIAPP_CMD_SET_SCENE_MODE       9460 //Polaroid
#define WIFIAPP_CMD_GSENSOR_CALIBRATION  9461
#define WIFIAPP_CMD_GSENSOR_SLOPE_LOCK   9462
#define WIFIAPP_CMD_TIME_FORMAT			 9463//24H 12H
#define WIFIAPP_CMD_LOCK_AND_PIM		 9464
#define WIFIAPP_CMD_MIC_BUTTON_FUNC      9465
#define WIFIAPP_CMD_ACTION_BUTTON_FUNC   9466
#define WIFIAPP_CMD_PRIVATE_MODE 	     9467
#define WIFIAPP_CMD_LOCK_VIDEO		 	 9468
#define WIFIAPP_CMD_LDWS         		 9469
#define WIFIAPP_CMD_FCW         		 9470
#define WIFIAPP_CMD_PCW         		 9471
#define WIFIAPP_CMD_RCW         		 9472
#define WIFIAPP_CMD_DV_MODE         	 9473
#define WIFIAPP_CMD_EDOG_OVERSPEED_ALARM 9474
#define WIFIAPP_CMD_BUZZER_VOLUME		 9475
#define WIFIAPP_CMD_SPEED_ALERT_SOUND    9476
#define WIFIAPP_CMD_ADAS_ALL    	 	 9477
#define WIFIAPP_CMD_ADAS_SOUND    	 	 9478
#define WIFIAPP_CMD_LCD_SHOW_TIME        9479
#define WIFIAPP_CMD_SENSOR3_ROTATE       9480
#define WIFIAPP_CMD_REAR2_SENSOR_MIRROR  9481
#define WIFIAPP_CMD_REVERSE_ALERT_SOUND  9482
#define WIFIAPP_CMD_SHUTDOWN_VOLTAGE     9483
#define WIFIAPP_CMD_HYBRID_PARKING       9484
#define WIFIAPP_CMD_MACHINE_POS       	 9485
#define WIFIAPP_CMD_VOLTAGE_STAMP        9486
#define WIFIAPP_CMD_LONG_PRESS_ALARM     9487
#define WIFIAPP_CMD_GET_CAR_VOLTAGE      9488
#define WIFIAPP_CMD_STAMP_COLOR          9489
#define WIFIAPP_CMD_GET_HARDWIRE_MAC     9490


//add for PAPAGO
#define WIFIAPP_CMD_GET_PRODUCT_INFO     9090
//#define WIFIAPP_CMD_GET_MAC_ADDR         9091
//#define WIFIAPP_CMD_LOCK_UNLCOK_VIDEO    9133
#define WIFIAPP_CMD_GET_DEVICE_FUNC      9143

/**
    @name WIFIAPP_RET return value for app command.
*/
//@{
#define WIFIAPP_RET_OK                   0
#define WIFIAPP_RET_RECORD_STARTED       1
#define WIFIAPP_RET_RECORD_STOPPED       2
#define WIFIAPP_RET_DISCONNECT           3
#define WIFIAPP_RET_MIC_ON               4
#define WIFIAPP_RET_MIC_OFF              5
#define WIFIAPP_RET_POWER_OFF            6
#define WIFIAPP_RET_REMOVE_BY_USER       7
//#NT#2016/06/23#Isiah Chang -begin
//#NT#Notify APP to restart RTSP live view becaues of sensor plug/unplug event.
#define WIFIAPP_RET_SENSOR_NUM_CHANGED   8
//#NT#2016/06/23#Isiah Chang -end
#define WIFIAPP_RET_CARD_INSERT          9
#define WIFIAPP_RET_CARD_REMOVE          10
#define WIFIAPP_RET_GSENSOR_STARTED      11
#define WIFIAPP_RET_GSENSOR_STOPPED      12
#define WIFIAPP_RET_GPS_PLUGOUT          13
#define WIFIAPP_RET_GPS_VOID             14
#define WIFIAPP_RET_GPS_ACTIVE           15
#define WIFIAPP_RET_SENSOR2_INSERT       16
#define WIFIAPP_RET_SENSOR2_REMOVE       17
#define WIFIAPP_RET_DISPLAY_FRONT        18
#define WIFIAPP_RET_DISPLAY_BEHIND       19
#define WIFIAPP_RET_DISPLAY_BOTH         20
#define WIFIAPP_RET_WIFI_OFF			 21
#define WIFIAPP_RET_NOFILE              (-1)
#define WIFIAPP_RET_EXIF_ERR            (-2)
#define WIFIAPP_RET_NOBUF               (-3)
#define WIFIAPP_RET_FILE_LOCKED         (-4)
#define WIFIAPP_RET_FILE_ERROR          (-5)
#define WIFIAPP_RET_DELETE_FAILED       (-6)
#define WIFIAPP_RET_MOVIE_FULL          (-7)
#define WIFIAPP_RET_MOVIE_WR_ERROR      (-8)
#define WIFIAPP_RET_MOVIE_SLOW          (-9)
#define WIFIAPP_RET_BATTERY_LOW         (-10)
#define WIFIAPP_RET_STORAGE_FULL        (-11)
#define WIFIAPP_RET_FOLDER_FULL         (-12)
#define WIFIAPP_RET_FAIL                (-13)
#define WIFIAPP_RET_FW_WRITE_CHK_ERR    (-14)   // (UPDNAND_STS_FW_WRITE_CHK_ERR+WIFIAPP_RET_FW_OFFSET)
#define WIFIAPP_RET_FW_READ2_ERR        (-15)   // (UPDNAND_STS_FW_READ2_ERR+WIFIAPP_RET_FW_OFFSET)
#define WIFIAPP_RET_FW_WRITE_ERR        (-16)   // (UPDNAND_STS_FW_WRITE_ERR+WIFIAPP_RET_FW_OFFSET)
#define WIFIAPP_RET_FW_READ_CHK_ERR     (-17)   // (UPDNAND_STS_FW_READ_CHK_ERR+WIFIAPP_RET_FW_OFFSET)
#define WIFIAPP_RET_FW_READ_ERR         (-18)   // (UPDNAND_STS_FW_READ_ERR+WIFIAPP_RET_FW_OFFSET)
#define WIFIAPP_RET_FW_INVALID_STG      (-19)   // (UPDNAND_STS_FW_INVALID_STG+WIFIAPP_RET_FW_OFFSET)
#define WIFIAPP_RET_FW_OFFSET           (-20)   // FW update offset
#define WIFIAPP_RET_PAR_ERR             (-21)
#define WIFIAPP_RET_STATE_ERR           (-22)
#define WIFIAPP_RET_CMD_NOTFOUND        WIFI_CMD_NOT_FOUND //(-256)

#define WIFIAPP_RET_USER_DEF             1000

//@}

/* WIFIAPP_RET_FW_xxx refere to
#define UPDNAND_STS_FW_OK               0   // Update FW to NAND OK
#define UPDNAND_STS_FW_INVALID_STG      1   // Invalid source storage
#define UPDNAND_STS_FW_READ_ERR         2   // FW doesn't exist or read error
#define UPDNAND_STS_FW_READ_CHK_ERR     3   // Read FW checksum failed, might be error
#define UPDNAND_STS_FW_WRITE_ERR        4   // Write FW to NAND error
#define UPDNAND_STS_FW_READ2_ERR        5   // Read FW from NAND failed (for write checking)
#define UPDNAND_STS_FW_WRITE_CHK_ERR    6   // Write FW checksum failed
*/



#define WIFIFLAG_MODE_DONE                   FLGPTN_BIT(0) //0x00000001
#define WIFIFLAG_CAPTURE_DONE                FLGPTN_BIT(1) //0x00000002
#define WIFIFLAG_RECORD_DONE                 FLGPTN_BIT(2) //0x00000004
#define WIFIFLAG_PREVIEW_DONE                FLGPTN_BIT(3) //0x00000008
#define WIFIFLAG_FORMAT_DONE                 FLGPTN_BIT(4) //0x00000010
#define WIFIFLAG_UPDATE_DONE                 FLGPTN_BIT(5) //0x00000020
#define WIFIFLAG_MOVIE_REC_RAWENC_DONE       FLGPTN_BIT(6) //0x00000040

//#define POOL_SIZE_XML_TEMP_BUF         		 ALIGN_CEIL_64(0x40100)

/**
     app mode change command
     command WIFIAPP_CMD_MODECHANGE
*/
typedef enum {
	WIFI_APP_MODE_PHOTO = 0,
	WIFI_APP_MODE_MOVIE,
	WIFI_APP_MODE_PLAYBACK,
	ENUM_DUMMY4WORD(WIFI_APP_MODE_CMD)
} WIFI_APP_MODE_CMD;

#define SysCmdWifi_CmdSend(a,b)  //temp define


#define DEF_XML_HEAD    "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
#define DEF_XML_RET     "<Function>\n<Cmd>%d</Cmd>\n<Status>%d</Status>\n</Function>"
#define DEF_XML_STR     "<Function>\n<Cmd>%d</Cmd>\n<Status>%d</Status>\n<String>%s</String>\n</Function>"
#define DEF_XML_VALUE   "<Function>\n<Cmd>%d</Cmd>\n<Status>%d</Status>\n<Value>%lld</Value>\n</Function>"
#define DEF_XML_CMD_CUR_STS    "<Cmd>%d</Cmd>\n<Status>%d</Status>\n"

UINT32 WifiApp_SendCmd(UINT32 cmd, UINT32 status);
UINT32 WifiApp_SendAutoTestCmd(UINT32 par1, UINT32 par2);
void WifiAppCmd_init(void);
void WifiAppCmd_UnInit(void);


int UserSocket_Send(char *addr, int *size);
int UserSocket_Recv(char *addr, int size);
int UserUdpSocket_Recv(char *addr, int size);
void UserSocket_Open(void);
void UserSocket_Close(void);

#endif //_WIFIAPPCMD_H_



