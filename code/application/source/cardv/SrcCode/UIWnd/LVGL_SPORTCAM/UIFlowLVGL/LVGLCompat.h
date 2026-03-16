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
void FlowWiFiMovie_IconDrawTimelapse(BOOL show);
void FlowWiFiMovie_IconDrawMotionDet(BOOL show);
void FlowWiFiMovie_IconDrawAudio(BOOL show);
void FlowWiFiMovie_IconDrawWiFiConnected(BOOL show);
void UIFlowWndWiFiMovie_UpdateWiFiData(BOOL bShow);
void FlowMovie_USBRemovePowerOff(void);
INT32 UIFlowWndWiFiMovie_OnCustom2(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);
void UIFlowWndWiFiMovie_StopTimer(void);

#endif
