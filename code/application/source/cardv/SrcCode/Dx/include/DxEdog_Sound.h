#ifndef __DXEDOGSOUND_H
#define __DXEDOGSOUND_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>
#include "kwrap/nvt_type.h"
#include "kwrap/error_no.h"
#include <errno.h>
#include <pthread.h>
#include "kwrap/task.h"
#include "kwrap/type.h"
#include "kwrap/error_no.h"
#include "kwrap/flag.h"


void EdogSound_Handle_Init(void);
				

// Flag
#define FLGEDOGSOUND_IDLE          FLGPTN_BIT(0)
#define FLGEDOGSOUND_UPDATE        FLGPTN_BIT(1)
#define FLGEDOGSOUND_ALL           0xFFFFFFFF

extern ID FLG_ID_EDOGSOUND;

extern void EdogSoundTsk_TrigUpdate(void);
extern ER EdogSoundTsk_Close(void);


#endif
