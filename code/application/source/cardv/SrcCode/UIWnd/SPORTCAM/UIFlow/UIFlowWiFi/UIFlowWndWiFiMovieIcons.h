
#ifndef __UIFlowWndWiFiMovieIcons_H
#define __UIFlowWndWiFiMovieIcons_H
#include "UIWnd/UIFlow.h"
#include "kwrap/type.h"


extern void FlowWiFiMovie_IconDrawDscMode(BOOL bShow);
extern void FlowWiFiMovie_IconDrawMaxRecTime(BOOL bShow);
extern void FlowWiFiMovie_IconDrawRecTime(BOOL bShow);
extern void FlowWiFiMovie_IconDrawDateTime(BOOL bShow);
//extern void FlowWiFiMovie_IconDrawRec(BOOL bShow);
extern void FlowWiFiMovie_IconDrawSize(BOOL bShow);
//extern void FlowWiFiMovie_IconDrawEV(BOOL bShow);
extern void FlowWiFiMovie_IconDrawStorage(BOOL bShow);
//extern void FlowWiFiMovie_IconDrawCyclicRec(BOOL bShow);
extern void FlowWiFiMovie_IconDrawMotionDet(BOOL bShow);
extern void FlowWiFiMovie_IconDrawBattery(BOOL bShow);
extern void FlowWiFiMovie_IconDrawDZoom(BOOL bShow);
extern void FlowWiFiMovie_DrawPIM(BOOL bShow);
extern void FlowWiFiMovie_IconDrawSOS(BOOL bShow);
extern void FlowWiFiMovie_IconDrawAudio(BOOL bShow);
extern void FlowWiFiMovie_IconDrawTimelapse(BOOL bShow);
//extern void FlowWiFiMovie_IconDrawLDWS(BOOL bShow);
//extern void FlowWiFiMovie_IconDrawFCW(BOOL bShow);
//extern void FlowWiFiMovie_IconDrawParkingMode(BOOL bShow);
//extern void FlowWiFiMovie_IconDrawPM_TLR(BOOL bShow);
//extern void FlowWiFiMovie_IconDrawParkingMode_Status(BOOL bShow);
extern void FlowWiFiMovie_IconDrawGPSSignal(BOOL bShow);
//extern void FlowWiFiMovie_IconDrawCustomerTxt(BOOL bShow);
//extern void FlowWiFiMovie_IconDrawMovieCodec(BOOL bShow);
extern void FlowWiFiMovie_IconDrawWiFiConnected(BOOL bShow);
extern void FlowWiFiMovie_IconDrawWiFiDisConnected(BOOL bShow);
extern void FlowWiFiMovie_OnTimer1SecIndex(void);

extern void FlowWiFiMovie_UpdateIcons(BOOL bShow);

extern void   FlowWiFiMovie_SetRecMaxTime(UINT32 RecMaxTime);
extern UINT32 FlowWiFiMovie_GetRecMaxTime(void);
extern void   FlowWiFiMovie_SetRecCurrTime(UINT32 RecCurrTime);
extern UINT32 FlowWiFiMovie_GetRecCurrTime(void);

extern void FlowWiFiMovie_IconDrawTPMS(BOOL bShow);
extern void FlowWiFiMovie_IconDrawCompass(void);
extern void FlowWiFiMovie_IconHideCompass(void);
#if 0//(GPS_PANEL_FUNC==ENABLE)
extern void FlowWiFiMovie_IconDrawTimeDate(void);
extern void FlowWiFiMovie_IconHideTimeDate(void);
extern void FlowWiFiMovie_IconDrawSpeed(void);
extern void FlowWiFiMovie_IconHideSpeed(void);
extern void FlowWiFiMovie_IconDrawPanelSpeed(UINT32 Count);
#endif
extern void FlowWiFiMovie_IconDrawHDR(BOOL bShow);
extern void FlowWiFiMovie_IconDrawEIS(BOOL bShow);
extern void FlowWiFiMovie_DrawFolderCheck(BOOL bShow);

#endif //__UIFlowWndWiFiMovieIcons_H
