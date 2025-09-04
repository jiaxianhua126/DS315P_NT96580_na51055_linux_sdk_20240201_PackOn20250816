#ifndef __UIFlowWndMovieIcons_H
#define __UIFlowWndMovieIcons_H

extern void FlowMovie_IconDrawDscMode(VControl *pCtrl);
extern void FlowMovie_IconHideDscMode(VControl *pCtrl);
extern void FlowMovie_IconDrawMaxRecTime(VControl *pCtrl);
extern void FlowMovie_IconHideMaxRecTime(VControl *pCtrl);
extern void FlowMovie_IconDrawRecTime(VControl *pCtrl);
extern void FlowMovie_IconHideRecTime(VControl *pCtrl);
extern void FlowMovie_IconDrawRec(VControl *pCtrl);
extern void FlowMovie_IconHideRec(VControl *pCtrl);
extern void FlowMovie_IconDrawSize(VControl *pCtrl);
extern void FlowMovie_IconHideSize(VControl *pCtrl);
extern void FlowMovie_IconDrawStorage(VControl *pCtrl);
extern void FlowMovie_IconHideStorage(VControl *pCtrl);
extern void FlowMovie_IconDrawEV(VControl *pCtrl);
extern void FlowMovie_IconHideEV(VControl *pCtrl);
extern void FlowMovie_IconDrawBattery(VControl *pCtrl);
extern void FlowMovie_IconHideBattery(VControl *pCtrl);
extern void FlowMovie_DrawPIM(BOOL bDraw);
extern void FlowMovie_IconDrawDZoom(VControl *pCtrl);
extern void FlowMovie_IconHideDZoom(VControl *pCtrl);
extern void FlowMovie_IconDrawDateTime(void);
extern void FlowMovie_IconHideDateTime(void);
extern void FlowMovie_IconDrawHDR(VControl *pCtrl);
extern void FlowMovie_IconHideHDR(VControl *pCtrl);
extern void FlowMovie_IconDrawMotionDet(VControl *pCtrl);
extern void FlowMovie_IconHideMotionDet(VControl *pCtrl);
extern void FlowMovie_IconDrawSOS(VControl *pCtrl);
extern void FlowMovie_IconHideSOS(VControl *pCtrl);
extern void FlowMovie_IconDrawAudio(VControl *pCtrl);
extern void FlowMovie_IconHideAudio(VControl *pCtrl);
extern void FlowMovie_IconDrawTimelapse(VControl *pCtrl);
extern void FlowMovie_IconHideTimelapse(VControl *pCtrl);
extern void FlowMovie_DrawFolderCheck(BOOL bShow);
extern void FlowMovie_HideFolderCheck(void);
extern void FlowMovie_DrawCustomerType(void);
extern void FlowMovie_HideCustomerType(void);
extern void FlowMovie_IconDrawGPSSignal(void);
extern void FlowMovie_IconHideGPSSignal(void);
extern void FlowMovie_IconDrawTPMS(void);
extern void FlowMovie_IconHideTPMS(void);
extern void FlowMovie_IconDrawCompass(void);
extern void FlowMovie_IconHideCompass(void);
#if 0//(GPS_PANEL_FUNC==ENABLE)
extern void FlowMovie_IconDrawTimeDate(void);
extern void FlowMovie_IconHideTimeDate(void);
extern void FlowMovie_IconDrawSpeed(void);
extern void FlowMovie_IconHideSpeed(void);
extern void FlowMovie_IconDrawPanelSpeed(UINT32 Count);
#endif
extern void FlowMovie_IconDrawEIS(void);
extern void FlowMovie_IconHideEIS(void);

extern void FlowMovie_UpdateIcons(BOOL bShow);

#endif //__UIFlowWndMovieIcons_H
