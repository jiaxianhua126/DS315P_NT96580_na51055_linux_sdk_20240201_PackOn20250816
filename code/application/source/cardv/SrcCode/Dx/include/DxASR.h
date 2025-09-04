#ifndef _DXASR_H
#define _DXASR_H

#include "kwrap/nvt_type.h"

typedef enum {
    ASR_PHOTO = 1,
    ASR_STARTVIDEO,
    ASR_CLOSEVIDEO,
    ASR_ENRECODING,
    ASR_DISRECODING,
    ASR_OPENLCD,
    ASR_CLOSELCD,
    ASR_OPENWIFI,
    ASR_CLOSEWIFI,
    ASR_OPENAHEAD,
    ASR_OPENBACK,
    ASR_OPENAP,
    ASR_CLOSEAP,
    ASR_SHOWALL,
    ASR_VLOCKING,
    ASR_INSIDE_VIDEO,
    ASR_BACK_TOHOMEPAGE,
} ASR_FLAG_LIST;

typedef struct _pAsr_SerialNumber{
    UINT8 Asr_SerialNumber_Flag;
    char SerialNumber[32];
}pAsr_SerialNumber;

extern void ASR_Uninstall(void);
extern UINT8 Dx_GetASR_Flag(void);
extern void Dx_SetASR_Flag(UINT8 arg);
extern void ASR_SetMode(UINT32 mode_arg);
extern int ASR_Open(void);
#endif
