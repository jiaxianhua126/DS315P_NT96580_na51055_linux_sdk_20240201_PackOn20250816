#include "DxCfg.h"
#include "IOCfg.h"

#include "DxWiFi.h"
#include "Utility/SwTimer.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          DxWiFi
#define __DBGLVL__          2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass

///////////////////////////////////////////////////////////////////////////////
void DrvWiFi_PowerOn(void)
{
    UINT32 GPIO_WIFI_PWREN = 43;
    UINT32 GPIO_WL_REG_ON = 37;
    printf("[API]\r\n");
    gpio_setPin(GPIO_WIFI_PWREN);
    SwTimer_DelayMs(100);
    gpio_setPin(GPIO_WL_REG_ON);
    SwTimer_DelayMs(100);
    printf("[API]\r\n");
}

void DrvWiFi_PowerOff(void)
{
    printf("[API]\r\n");
    //gpio_clearPin(GPIO_WL_REG_ON);
    //SwTimer_DelayMs(100);
    //gpio_clearPin(GPIO_WIFI_PWREN);
    //SwTimer_DelayMs(100);
    printf("[API]\r\n");
}

