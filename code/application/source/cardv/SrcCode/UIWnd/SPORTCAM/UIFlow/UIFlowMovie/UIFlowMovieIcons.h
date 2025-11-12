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
extern void FlowMovie_IconDrawMotionDet(void);
extern void FlowMovie_IconHideMotionDet(void);
extern void FlowMovie_IconDrawSOS(void);
extern void FlowMovie_IconHideSOS(void);
extern void FlowMovie_IconDrawAudio(VControl *pCtrl);
extern void FlowMovie_IconHideAudio(VControl *pCtrl);
extern void FlowMovie_IconDrawTimelapse(void);
extern void FlowMovie_IconHideTimelapse(void);
extern void FlowMovie_DrawFolderCheck(BOOL bShow);
extern void FlowMovie_DrawCustomerType(void);
extern void FlowMovie_HideCustomerType(void);
extern void FlowMovie_IconDrawGPSSignal(void);
extern void FlowMovie_IconHideGPSSignal(void);
extern void FlowMovie_IconDrawSNG(void);
extern void FlowMovie_IconHideSNG(void);
extern void FlowMovie_IconDrawTSR(void);
extern void FlowMovie_IconHideTSR(void);
extern void FlowMovie_IconDrawRL(void);
extern void FlowMovie_IconHideRL(void);
extern void FlowMovie_initIcon(void);
extern void FlowMovie_IconDrawADASAnimation(void);
extern void FlowMovie_IconDrawADASUpdateCar(void);


extern void FlowMovie_UpdateIcons(BOOL bShow);

#endif //__UIFlowWndMovieIcons_H
