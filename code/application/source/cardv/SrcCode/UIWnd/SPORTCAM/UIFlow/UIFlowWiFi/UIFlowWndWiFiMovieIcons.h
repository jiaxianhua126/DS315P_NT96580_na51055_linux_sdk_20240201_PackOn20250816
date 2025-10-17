
#ifndef __UIFlowWndWiFiMovieIcons_H
#define __UIFlowWndWiFiMovieIcons_H
#include "UIWnd/UIFlow.h"
#include "kwrap/type.h"


extern void FlowWiFiMovie_IconDrawDscMode(BOOL bShow);
extern void FlowWiFiMovie_IconDrawMaxRecTime(BOOL bShow);
extern void FlowWiFiMovie_IconDrawRecTime(BOOL bShow);
extern void FlowWiFiMovie_IconDrawDateTime(BOOL bShow);
extern void FlowWiFiMovie_IconDrawRec(BOOL bShow);
extern void FlowWiFiMovie_IconDrawSize(BOOL bShow);
extern void FlowWiFiMovie_IconDrawEV(BOOL bShow);
extern void FlowWiFiMovie_IconDrawStorage(BOOL bShow);
extern void FlowWiFiMovie_IconDrawCyclicRec(BOOL bShow);
extern void FlowWiFiMovie_IconDrawHDR(BOOL bShow);
extern void FlowWiFiMovie_IconDrawMotionDet(BOOL bShow);
extern void FlowWiFiMovie_IconDrawBattery(BOOL bShow);
extern void FlowWiFiMovie_IconDrawDZoom(BOOL bShow);
extern void FlowWiFiMovie_DrawPIM(BOOL bShow);
extern void FlowWiFiMovie_IconDrawSOS(BOOL bShow);
extern void FlowWiFiMovie_IconDrawAudio(BOOL bShow);
extern void FlowWiFiMovie_IconDrawTimelapse(BOOL bShow);
extern void FlowWiFiMovie_DrawFolderCheck(BOOL bShow);
extern void FlowWiFiMovie_DrawCustomerType(BOOL bShow);
extern void FlowWiFiMovie_IconDrawGPSSignal(BOOL bShow);
extern void FlowWiFiMovie_IconDrawWiFiConnected(BOOL bShow);
extern void FlowWiFiMovie_IconDrawWiFiDisConnected(BOOL bShow);
extern void FlowWiFiMovie_OnTimer1SecIndex(void);

extern void FlowWiFiMovie_IconDrawSNG(BOOL bShow);
extern void FlowWiFiMovie_IconDrawTSR(BOOL bShow);
extern  void FlowWiFiMovie_IconDrawRL(BOOL bShow);
extern void FlowWiFiMovie_initIcon(void);

extern void FlowWiFiMovie_UpdateIcons(BOOL bShow);

extern void   FlowWiFiMovie_SetRecMaxTime(UINT32 RecMaxTime);
extern UINT32 FlowWiFiMovie_GetRecMaxTime(void);
extern void   FlowWiFiMovie_SetRecCurrTime(UINT32 RecCurrTime);
extern UINT32 FlowWiFiMovie_GetRecCurrTime(void);

#endif //__UIFlowWndWiFiMovieIcons_H
