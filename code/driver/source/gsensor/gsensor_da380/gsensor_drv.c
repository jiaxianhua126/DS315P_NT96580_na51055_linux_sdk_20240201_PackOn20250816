#include "gsensor_drv.h"
#include "gsensor_main.h"


#include "kwrap/util.h"

#define __MODULE__			gsen_da380
#define __DBGLVL__			1      // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__			"*"    //*=All, [mark]=CustomClass
#include <kwrap/debug.h>