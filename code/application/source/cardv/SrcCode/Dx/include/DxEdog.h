#ifndef __DXEDOG_H
#define __DXEDOG_H

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
//#include <linux/watchdog.h>
//#define DXWATCHDOG_PATH  "/dev/watchdog0"

//#define WATCHDOG_EN    _IOWR('w',1,unsigned int)
//#define FEED_DOG       _IOWR('w',2,unsigned int)
//void *Edog_CreateTask(void);
void Edog_EnableTask(void);
void Edog_DisableTask(void);
void Edog_Handle_Init(void);

#endif
