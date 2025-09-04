#ifndef WIFICMDMOVIE_H
#define WIFICMDMOVIE_H

#include "UIFramework.h"

typedef enum {
	WIFI_MOV_ST_IDLE = 0,
	WIFI_MOV_ST_LVIEW,
	WIFI_MOV_ST_RECORD,
	WIFI_MOV_ST_MAX
} WIFI_MOV_ST_SETTING;
//extern UINT32 FlowWiFiMovie_GetRecCurrTime(void);
extern UINT32 FlowMovie_GetRecCurrTime(void);


extern void FlowWiFiMovie_StartRec(void);
extern void FlowWiFiMovie_StopRec(void);
extern void FlowWiFiMovie_AutoHDR(void);

extern INT32 WiFiCmd_GetStatus(void);
extern UINT32  UIFlowWiFiMovie_GetMaxRecTime(void);

extern INT32 WiFiCmd_OnExeMovieRec(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetMovieRecSize(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeCyclicRec(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeMovieWDR(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeMovieHDR(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeSetHDRTime(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);

extern INT32 WiFiCmd_OnExeSetMovieEV(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeSetMovieEV2(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
//#NT#2016/06/03#Charlie Chang -begin
//#NT#add contrast, audioIn, flip_mirror , quality set
extern INT32 WiFiCmd_OnExeSetMovieContrast(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeSetMovieAudioIn(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeSetMovieAudioInSR(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeSetMovieFlipMirror(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeSetMovieQualitySet(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
//#NT#2016/06/03#Charlie Chang -end
extern INT32 WiFiCmd_OnExeSetMotionDet(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeSetParkingMotionDet(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeSetMovieAudio(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeSetMovieDateImprint(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeSetMovieLiveviewSize(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetMovieGSesnorSensitivity(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetParkingGSensor(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetAutoRecording(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetMovieRecBitRate(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetMovieLiveviewBitRate(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeMovieLiveviewStart(VControl *pCtrl, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeTriggerMovieRawEnc(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);

//#NT#2017/01/03#Isiah Chang -begin
//#NT#Add WiFiCmd Bitrate control.
extern INT32 WiFiCmd_OnExeMovieBRCAdjust(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern BOOL WiFiCmd_BRC_AutoRunStateGet(void);
extern INT32 WiFiCmd_BRCAdjust(INT32 iLevel);
//#NT#2017/01/03#Isiah Chang -end
extern INT32 WiFiCmd_OnMovieFull(VControl *pCtrl, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnMovieWrError(VControl *pCtrl, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnStorageSlow(VControl *pCtrl, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnMovieOneSec(VControl *pCtrl, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnMovieRawEncJpgOKCB(VControl *pCtrl, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnMovieRawEncErr(VControl *pCtrl, UINT32, UINT32 *);
extern void WiFiCmd_MotionDetectStart(void);
extern void WiFiCmd_MotionDetectStop(void);
extern void WiFiCmd_OnMotionDetect(void);
extern void WiFiCmd_HBStart(void);
extern void WiFiCmd_HBStop(void);
extern void WiFiCmd_HBOneSec(void);
extern INT32 WiFiCmd_OnExeMovieVedioReady(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
extern INT32 WiFiCmd_OnExeSetMovieTimeLapseRec(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetMovieMetering(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetMovieBitRate(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetMovieGPSStamp(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetMovieModelStamp(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeBeep(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeScreenSaver(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeFrequency(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeGPS(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeTimeZone(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSpeedUnit(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetCarNo(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSensorRotate(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSensor2Rotate(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetCustomStamp(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeFormatWarning(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeParkingMode(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetCarNo(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSysReboot(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSysBootDelay(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeIRRearColor(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeRearSensorMirror(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetMovieVoice(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetMenuComingSound(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetParkingOffGPS(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetDateFormat(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetAsrControl(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetAsrContent(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeVideoFormat(VControl *, UINT32 , UINT32 *);
extern INT32 WiFiCmd_OnExeMovieCodec(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeVolume(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeShutdownTimer(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeWaterLogo(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetStorageType(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeSetEnterParkingTime(VControl *, UINT32 , UINT32 *);
extern INT32 WiFiCmd_OnExeSensorRotate(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeRearSensorMirror(VControl *, UINT32, UINT32 *);
extern INT32 WiFiCmd_OnExeCustomFWUpdate(VControl *, UINT32 , UINT32 *);
extern INT32 WiFiCmd_OnExeSendFWMD5(VControl *, UINT32 , UINT32 *);
extern INT32 WiFiCmd_OnExeEdogDataUpdate(VControl *, UINT32 , UINT32 *);
extern INT32 WiFiCmd_OnExeSetBand(VControl *, UINT32, UINT32 *);

#endif
