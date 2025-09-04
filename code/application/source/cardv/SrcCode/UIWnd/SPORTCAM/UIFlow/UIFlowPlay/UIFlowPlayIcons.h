
#ifndef __UIFlowWndPlayIcons_H
#define __UIFlowWndPlayIcons_H

#include <kwrap/nvt_type.h>

extern void FlowPB_UpdateIcons(BOOL bShow);
extern void FlowPB_IconDrawMovPlay(BOOL bShow);
extern void FlowPB_IconDrawMovStop(BOOL bShow);
extern void FlowPB_IconDrawMovPlayTime(BOOL bShow);
extern void FlowPB_ClearAllThumbIcon(void);
extern void FlowPB_ShowAllThumbIcon(void);

extern void FlowPB_IconDrawMovSpeed(void);
extern void FlowPB_IconHideMovSpeed(VControl *pCtrl);

extern void FlowPB_IconDrawMovPlay_HideShowIcon(BOOL bShow);
extern void FlowPB_IconDrawMovBwd(BOOL bShow,UINT32 iconID);
extern void FlowPB_IconDrawMovFwd(BOOL bShow,UINT32 iconID);
extern void FlowPB_IconDrawVideoTotalTime(BOOL bShow);



#endif //__UIFlowWndPlayIcons_H
