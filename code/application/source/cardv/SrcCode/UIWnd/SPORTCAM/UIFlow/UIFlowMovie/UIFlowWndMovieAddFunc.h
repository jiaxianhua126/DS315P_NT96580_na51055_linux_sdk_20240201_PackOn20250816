#ifndef _UIFLOWMOVIEADDFUNCS_H
#define _UIFLOWMOVIEADDFUNCS_H

#define WAIT_SECONDS 1
void Set_IsRearOK(UINT8 value);
UINT8 Get_IsRearOK(void);
void Set_PreviewStable_Record(BOOL value);
BOOL Get_PreviewStable_Record(void);
void UIFlowWndMovie_OnTXStatusDet(void);
void UIFlowWndMovie_OnAutoStartRec(void);
extern void UIFlowMoive_AutoStartWiFi(void);

#if (defined(_NVT_ETHREARCAM_RX_))
extern BOOL   SysInit_GetEthTxFW_Update_getstd(void);
extern BOOL   SysInit_GetEthBootFW_Update_getstd(void);
extern BOOL Cmd_ethcam_tx_fwupdate(unsigned char argc, char **argv);
extern BOOL Cmd_ethcam_ethboot(unsigned char argc, char **argv);
extern BOOL SysInit_getintoGPS_mode_getstd(void);

#endif
extern UINT32 Movie_GetCyclicRecTime(void);
extern void FlowMovie_BaseDaySet(int year,int month,int day);

extern UINT32 g_uiPreTimelapse;

extern void FlowMovie_SyncEthCamMneu(UINT8 id,BOOL bReopen);
extern void FlowMovie_UpdateLED(void);
extern void FlowMovie_DetTxDisconnected(void);
extern void FlowMovie_LCDIconDimDsiable(UINT8 uCount);
extern void FlowMovie_DetLCDIconHide(void);
extern void FlowMovie_LEDToggle(UINT8 uState);
extern void FlowMovie_UpdateLED(void);
extern void FlowMovie_SetCapPicture(BOOL flag);
extern BOOL FlowMovie_GetCapPicture(void);
extern void FlowMovie_SetCapPictureCount(UINT8 cnt);
extern UINT8 FlowMovie_GetCapPictureCount(void);
extern BOOL FlowMovie_IsEthCamConnectOK(void);
extern void FlowMovie_SyncTimeToRear(void);
extern void FlowMovie_SetCrash(void);
#if (_GPS_EDOG_UNIQUE_SKY_==ENABLE)
extern void  FlowMovie_EdogAlarmVoice(UINT8 type);
extern BOOL  FlowMovie_isEdogTypeValid(UINT8 type);
extern BOOL g_bManualCloseEdogWnd;
#endif
extern void UIFlowWndMovie_OnDeleteOld(void);
extern BOOL UIFlowWndMovie_CheckFileFolder(void);



extern BOOL g_uiWiFiRecordIngMotionDet;
extern BOOL g_uiWiFiParkingModeMotionDet;
extern BOOL bWiFiConnected;
extern BOOL bWndWiFiMovieOpenFirst;
extern BOOL bWiFiRec_AutoStart;
extern BOOL bWiFiRec_AutoStop;
extern BOOL bWiFiModeChanged;
//extern BOOL bWiFiRec_GSensorEvent;

extern INT32 UIFlowWndWiFiMovie_OnCustom2(VControl *pCtrl, UINT32 paramNum, UINT32 *paramArray);

#endif//

