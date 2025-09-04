#ifndef __UART_H
#define __UART_H

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

extern ER uart2_open(void);
extern void uart2_init(void);
extern ER uart2_getString(CHAR *pcString, UINT32 *pcBufferLen);
extern ER uart2_close(void);

#endif

