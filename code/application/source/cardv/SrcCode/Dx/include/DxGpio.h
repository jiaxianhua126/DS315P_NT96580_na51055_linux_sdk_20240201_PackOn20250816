#ifndef _DX_GPIO_H
#define _DX_GPIO_H

#include "kwrap/nvt_type.h"

#define POWER_LED  0
#define REC_LED    1
#define MIC_LED    2
#define WIFI_LED   3

extern void GPIOMap_TurnOffLED(void);
extern void GPIOMap_TurnOnLED(void);
extern void Control_LedTurn(UINT32 Select_LED,UINT32 status);
extern void Check_LEDStatus(void);
extern UINT32 LED_Get_Status(void);
extern void 	Dx_InitWifi_PWEREN(void);

#endif
