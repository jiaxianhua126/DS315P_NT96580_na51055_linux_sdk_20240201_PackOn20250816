#ifndef __DXWATCHDOG_H
#define __DXWATCHDOG_H

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
#include <linux/watchdog.h>
#define DXWATCHDOG_PATH  "/dev/watchdog0"

#define WATCHDOG_EN    _IOWR('w',1,unsigned int)
#define FEED_DOG       _IOWR('w',2,unsigned int)
//void *Watchdog_CreateTask(void);
void Watchdog_CancelTask(void);
void Watchdog_Enable(void);
void Watchdog_Disable(void);
void Watchdog_Init(void);

#endif
