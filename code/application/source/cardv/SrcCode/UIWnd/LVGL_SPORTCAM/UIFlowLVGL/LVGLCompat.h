#ifndef _LVGL_COMPAT_H
#define _LVGL_COMPAT_H

#include "PrjInc.h"

extern BOOL ParkingM_PreRecord_EMR;
extern BOOL isACCTrigParkMode;
extern BOOL isACCTrigLowBitrate;
extern BOOL isACCTrigPreRecordDet;
extern BOOL WifiStarting;
extern BOOL bWiFiConnected;
extern BOOL bWndWiFiMovieOpenFirst;
extern BOOL bWiFiModeChanged;
extern BOOL g_NotRecordWrn;
extern BOOL g_uiWiFiRecordIngMotionDet;
extern BOOL g_uiWiFiParkingModeMotionDet;
extern BOOL bWiFiRec_AutoStart;
extern BOOL bWiFiRec_AutoStop;
extern BOOL WiFiManualSetSOS;
extern BOOL g_WiFiAutoRec;
extern BOOL GPIOMap_IsLCDBacklightOn(void);
extern void GPIOMap_TurnOnLCDBacklight(void);

void FlowMovie_BaseDaySet(int year, int month, int day);
BOOL FlowMovie_WakeUpLCDBacklight(void);
BOOL FlowMovie_IsEthCamConnectOK(void);
void FlowMovie_SetSOSStatusNow(BOOL En);
BOOL FlowMovie_GetSOSStatusNow(void);
void FlowMovie_SetLedFlash_BeepWrn(BOOL std);
UINT32 FlowWiFiMovie_GetRecCurrTime(void);
void FlowWiFiMovie_SetRecCurrTime(UINT32 time);
void FlowWiFiMovie_UpdateIcons(BOOL force);
void FlowWiFiMovie_IconDrawMaxRecTime(BOOL show);
void FlowWiFiMovie_IconDrawRecTime(BOOL show);
void FlowWiFiMovie_IconDrawDateTime(BOOL show);
void FlowWiFiMovie_IconDrawRec(BOOL show);
void FlowWiFiMovie_IconDrawTimelapse(BOOL show);
void FlowWiFiMovie_IconDrawMotionDet(BOOL show);
void FlowWiFiMovie_DrawPIM(BOOL show);
void FlowWiFiMovie_IconDrawAudio(BOOL show);
void FlowWiFiMovie_IconDrawSOS(BOOL show);
void FlowWiFiMovie_IconDrawGPSSignal(BOOL show);
void FlowWiFiMovie_IconDrawWiFiConnected(BOOL show);
void FlowWiFiMovie_IconDrawWiFiDisConnected(BOOL show);
void FlowWiFiMovie_IconDrawSNG(BOOL show);
void FlowWiFiMovie_IconDrawTSR(BOOL show);
void FlowWiFiMovie_IconDrawADASAnimation(void);
void FlowWiFiMovie_IconDrawADASUpdateCar(void);
void FlowWiFiMovie_IconDrawADASHideCar(void);
void FlowWiFiMovie_IconDrawADASDistance(UINT32 distance);
void FlowWiFiMovie_IconHideADASDistance(void);
void FlowWiFiMovie_IconDrawADASDisplayType(UINT32 id);
void FlowWiFiMovie_IconHideADASDisplayType(void);
void FlowWiFiMovie_IconDrawDDDAlarm(UINT32 id);
void FlowWiFiMovie_IconHideDDDAlarm(void);
void UIFlowWndWiFiMovie_UpdateWiFiData(BOOL bShow);
void FlowMovie_USBRemovePowerOff(void);
INT32 UIFlowWndWiFiMovie_OnCustom2(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
void UIFlowWndWiFiMovie_StopTimer(void);

#endif
