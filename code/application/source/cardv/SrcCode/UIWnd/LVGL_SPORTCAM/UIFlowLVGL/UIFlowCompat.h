#ifndef _UIFLOWLVGL_COMPAT_H_
#define _UIFLOWLVGL_COMPAT_H_

extern BOOL ParkingM_PreRecord_EMR;
extern BOOL bWndWiFiMovieOpenFirst;
extern BOOL isACCTrigParkMode;
extern BOOL isACCTrigLowBitrate;
extern BOOL isACCTrigPreRecordDet;
extern BOOL WifiStarting;
extern BOOL bWiFiModeChanged;
extern VControl UIMenuWndWiFiMobileLinkOKCtrl;

extern void FlowMovie_BaseDaySet(int year, int month, int day);
extern BOOL FlowMovie_WakeUpLCDBacklight(void);
extern UINT32 FlowWiFiMovie_GetRecCurrTime(void);
extern UINT32 Get_ParkingModeTimeLapseValue(UINT32 uiIndex);
extern BOOL FlowMovie_IsEthCamConnectOK(void);
extern void FlowMovie_USBRemovePowerOff(void);
extern INT32 UIFlowWndWiFiMovie_OnCustom2(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);

#endif
