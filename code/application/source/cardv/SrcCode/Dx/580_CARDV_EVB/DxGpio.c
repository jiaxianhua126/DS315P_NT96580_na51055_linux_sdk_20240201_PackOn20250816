#include "DxGpio.h"
#include "kwrap/type.h"
#include "Dx.h"
#include "DxCommon.h"
#include "IOCfg.h"
#include "hdal.h"
#include "UIWnd/UIFlow.h"

void Check_LEDStatus(void)
{
	if (SysGetFlag(FL_LED) == LED_ON) {
		if (SysGetFlag(FL_MOVIE_AUDIO) == MOVIE_AUDIO_OFF) { 
			Control_LedTurn(MIC_LED,0); 
		} else {
			Control_LedTurn(MIC_LED,1);
		}
	} else {
		GPIOMap_TurnOffLED();
	}
}

void GPIO_PowerLED_Turn(UINT32 status)
{
    if (status) 
        gpio_setPin(GPIO_RED_LED);
    else
        gpio_clearPin(GPIO_RED_LED);
}

void GPIO_RECLED_Turn(UINT32 status)
{
    if (status) 
        gpio_setPin(GPIO_REC_LED);
    else
        gpio_clearPin(GPIO_REC_LED);
}

void GPIO_MICLED_Turn(UINT32 status)
{
    if (status) 
        gpio_setPin(GPIO_MIC_LED);
    else
        gpio_clearPin(GPIO_MIC_LED);
}

void GPIO_WIFILED_Turn(UINT32 status)
{
    if (status) 
        gpio_setPin(GPIO_WIFI_LED);
    else
        gpio_clearPin(GPIO_WIFI_LED);
}

//turn off all LED
void GPIOMap_TurnOffLED(void)
{
    GPIO_PowerLED_Turn(0);
    GPIO_RECLED_Turn(0);
    GPIO_MICLED_Turn(0);
    GPIO_WIFILED_Turn(0);
}

//turn on LED
void GPIOMap_TurnOnLED(void)
{	
		Check_LEDStatus();
		gpio_setPin(GPIO_RED_LED);
		gpio_setPin(GPIO_REC_LED);
}

UINT32 LED_Get_Status(void)
{
	return gpio_getPin(GPIO_REC_LED);
}

void Control_LedTurn(UINT32 Select_LED,UINT32 status)
{
	if (SysGetFlag(FL_LED) == LED_ON) {
        switch(Select_LED) {
        case POWER_LED:
            GPIO_PowerLED_Turn(status);
        	break;

        case REC_LED:
            GPIO_RECLED_Turn(status);
        	break;

        case MIC_LED:
            GPIO_MICLED_Turn(status);
        	break;

        case WIFI_LED:
            GPIO_WIFILED_Turn(status);
        	break;
        }
	} else {
		GPIOMap_TurnOffLED();
	}

}