/**
    Copyright   Novatek Microelectronics Corp. 2009.  All rights reserved.

    @file       DetKey.c
    @ingroup    mIPRJAPKeyIO

    @brief      Scan key, modedial
                Scan key, modedial

    @note       Nothing.

    @date       2017/05/02
*/

/** \addtogroup mIPRJAPKeyIO */
//@{

#include "DxCfg.h"
#include "IOCfg.h"
#include "DxInput.h"
#include "KeyDef.h"
#include "comm/hwclock.h"
#include "comm/hwpower.h"
#include "PrjCfg.h"//ETH_REARCAM_CAPS_COUNT
#if 0
#include "rtc.h"
#include "Delay.h"
#endif
///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          DxKey
#define __DBGLVL__          2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ADC related
////////////////////////////////////////////////////////////////////////////////
#if (ADC_KEY == ENABLE)
#define VOLDET_KEY_ADC_RANGE            (110)
#define VOLDET_KEY_ADC_LVL0             (100)
#define VOLDET_KEY_ADC_LVL1             (400)
#define VOLDET_KEY_ADC_TH               (400)//(512)

#define VOLDET_KEY_LVL_UNKNOWN           0xFFFFFFFF
#define VOLDET_KEY_LVL_0                 0
#define VOLDET_KEY_LVL_1                 1
#define VOLDET_KEY_LVL_2                 2
#define VOLDET_KEY_LVL_3                 3
#define VOLDET_KEY_LVL_4                 4
#define VOLDET_KEY_LVL_5                 5
#endif
#if (ADC_KEY == ENABLE)
static UINT32 VolDet_GetKey1ADC(void)
{
#if (VOLDET_ADC_CONT_MODE == DISABLE)
	UINT32 uiADCValue;

	uiADCValue = adc_readData(ADC_CH_VOLDET_KEY1);
	// One-Shot Mode, trigger one-shot
	adc_triggerOneShot(ADC_CH_VOLDET_KEY1);

	return uiADCValue;
#else
	//printf("call ADC_CH_VOLDET_KEY1 = %d\r\n",adc_readData(ADC_CH_VOLDET_KEY1));
	return adc_readData(ADC_CH_VOLDET_KEY1);
#endif
}
static UINT32 VolDet_GetKey2ADC(void)
{
#if (VOLDET_ADC_CONT_MODE == DISABLE)
    UINT32 uiADCValue;

    uiADCValue = adc_readData(ADC_CH_VOLDET_KEY2);
    // One-Shot Mode, trigger one-shot
    adc_triggerOneShot(ADC_CH_VOLDET_KEY2);

    return uiADCValue;
#else
	//printf("call ADC_CH_VOLDET_KEY2 = %d\r\n",adc_readData(ADC_CH_VOLDET_KEY2));
    	return adc_readData(ADC_CH_VOLDET_KEY2);
#endif
}

/**
  Get ADC key voltage level

  Get  ADC key  2 voltage level.

  @param void
  @return UINT32 key level, refer to VoltageDet.h -> VOLDET_MS_LVL_XXXX
*/
static UINT32 VolDet_GetKey1Level(void)
{
	static UINT32	uiRetKey1Lvl = VOLDET_KEY_LVL_UNKNOWN;
	UINT32			uiKey1ADC = 0, uiCurKey1Lvl = VOLDET_KEY_LVL_UNKNOWN;

	uiKey1ADC = VolDet_GetKey1ADC();
	//DBG_IND("uiKey1ADC %d \r\n", uiKey1ADC);
	if (uiKey1ADC < VOLDET_KEY_ADC_TH) {
		if (uiKey1ADC < VOLDET_KEY_ADC_LVL0) {
			uiCurKey1Lvl = VOLDET_KEY_LVL_0;
		} else if (uiKey1ADC < VOLDET_KEY_ADC_LVL1) {
			uiCurKey1Lvl = VOLDET_KEY_LVL_1;
		}
	} else {
		uiCurKey1Lvl = VOLDET_KEY_LVL_UNKNOWN;
	}

	uiRetKey1Lvl = uiCurKey1Lvl;

	return uiRetKey1Lvl;
}


static UINT32 VolDet_GetKey2Level(void)
{
	static UINT32   uiRetKey2Lvl = VOLDET_KEY_LVL_UNKNOWN;
	UINT32          uiKey2ADC = 0, uiCurKey2Lvl = VOLDET_KEY_LVL_UNKNOWN;

	uiKey2ADC = VolDet_GetKey2ADC();
	//DBG_IND("uiKey2ADC %d \r\n", uiKey2ADC);
	if (uiKey2ADC < VOLDET_KEY_ADC_TH) {
		if (uiKey2ADC < VOLDET_KEY_ADC_LVL0) {
			uiCurKey2Lvl = VOLDET_KEY_LVL_0;
		} else if (uiKey2ADC < VOLDET_KEY_ADC_LVL1) {
			uiCurKey2Lvl = VOLDET_KEY_LVL_1;
		}
	} else {
		uiCurKey2Lvl = VOLDET_KEY_LVL_UNKNOWN;
	}

	uiRetKey2Lvl = uiCurKey2Lvl;

	return uiRetKey2Lvl;
}


/**
  Detect Mode Switch state.

  Detect Mode Switch state.

  @param void
  @return UINT32 Mode Switch state (DSC Mode)
*/
#endif

////////////////////////////////////////////////////////////////////////////////
// GPIO related

//static BOOL g_bIsShutter2Pressed = FALSE;

/**
  Delay between toggle GPIO pin of input/output

  Delay between toggle GPIO pin of input/output

  @param void
  @return void
*/
static void DrvKey_DetKeyDelay(void)
{
	gpio_readData(0);
	gpio_readData(0);
	gpio_readData(0);
	gpio_readData(0);
}

void DrvKey_Init(void)
{
}

#if 1
static UINT32 uiEnterParkingTimer = 150;//3sec
void EnterParkingTimer_Set(UINT32 value)
{
    uiEnterParkingTimer = value;
}

BOOL GPIOMap_DetACCPlugIn(void)
{
    //DBG_DUMP("^G *** gpio_getPin(GPIO_ACC_PLUG)= %d ***\r\n", gpio_getPin(GPIO_ACC_PLUG));
    if (!gpio_getPin(GPIO_ACC_PLUG)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*extern */BOOL   isACCTrigPowerOn;
static UINT32 ACC_OnTimerCount = 0;
static UINT32 ACC_OffTimerCount = 0;
static BOOL   bACC_On = FALSE;
static BOOL   bACC_Off = FALSE;

static UINT32 DrvKey_DetACCPower(void)
{
    UINT32 uiKeyCode = 0;

    if (GPIOMap_DetACCPlugIn())
    {
        ACC_OffTimerCount = 0;
        bACC_Off = FALSE;
        isACCTrigPowerOn = TRUE;

        if (!bACC_On)
        {
            ++ACC_OnTimerCount;
        }

        if (ACC_OnTimerCount > 150)
        {
            uiKeyCode |= FLGKEY_MODE;
			//DBG_DUMP("call DrvKey_DetACCPower FLGKEY_MODE\n");
            if (ACC_OnTimerCount > 153)
            {
                ACC_OnTimerCount = 0;
                bACC_On = TRUE;
            }
        }
    }
    else
    {
        ACC_OnTimerCount = 0;
        bACC_On = FALSE;

        if (!bACC_Off)
        {
            ++ACC_OffTimerCount;
        }

        if (ACC_OffTimerCount > uiEnterParkingTimer)
        {
            if (isACCTrigPowerOn)
            {
            	//DBG_DUMP("DrvKey_DetACCPower success!\n");
                uiKeyCode |= FLGKEY_KEY_POWER_ACC;//FLGKEY_KEY_POWER;
            }
            if (ACC_OffTimerCount > (uiEnterParkingTimer + 3))
            {
                ACC_OffTimerCount = 0;
                bACC_Off = TRUE;
            }
        }
    }

    return uiKeyCode;
}
#endif
/**
  Detect normal key is pressed or not.

  Detect normal key is pressed or not.
  Return key pressed status (refer to KeyDef.h)

  @param void
  @return UINT32
*/
UINT32 DrvKey_DetNormalKey(void)
{
	UINT32 uiKeyCode = 0;
	UINT32 temp = 0;
/*
#if (ADC_KEY == ENABLE)
	UINT32 uiKey1Lvl = VolDet_GetKey1Level();
	switch (uiKey1Lvl) {
	case VOLDET_KEY_LVL_UNKNOWN:
	default:
		break;
	case VOLDET_KEY_LVL_0:
		uiKeyCode |= FLGKEY_RIGHT;
		break;
	case VOLDET_KEY_LVL_1:
		uiKeyCode |= FLGKEY_DOWN;
		break;
	case VOLDET_KEY_LVL_2:
		uiKeyCode |= FLGKEY_SHUTTER2;
		break;
	case VOLDET_KEY_LVL_3:
		uiKeyCode |= FLGKEY_UP;
		break;
	case VOLDET_KEY_LVL_4:
		uiKeyCode |= FLGKEY_ENTER;
		break;
	}
#endif
*/
#if (ADC_KEY == ENABLE)
	UINT32 uiKey1Lvl = VolDet_GetKey1Level();
	UINT32 uiKey2Lvl = VolDet_GetKey2Level();
	switch (uiKey1Lvl) {
	case VOLDET_KEY_LVL_UNKNOWN:
	default:
		break;
	case VOLDET_KEY_LVL_0:
		uiKeyCode |= FLGKEY_UP;
		//DBG_IND("CAll FLGKEY_UP\r\n");
		break;
	case VOLDET_KEY_LVL_1:
		uiKeyCode |= FLGKEY_DOWN;
		//DBG_IND("CAll FLGKEY_DOWN\r\n");
		break;
	}

	switch (uiKey2Lvl) {
	case VOLDET_KEY_LVL_UNKNOWN:
	default:
		break;
	case VOLDET_KEY_LVL_0:
		uiKeyCode |= FLGKEY_ENTER;
		//DBG_IND("CAll FLGKEY_ENTER\r\n");
		break;
	//case VOLDET_KEY_LVL_1:
	//	uiKeyCode |= FLGKEY_RIGHT;
	//	break;
	}
#endif

#if (GPIO_KEY == ENABLE)
	/*
	if (gpio_getPin(GPIO_KEY_LEFT)) {
		uiKeyCode |= FLGKEY_LEFT;
	}
	if (gpio_getPin(GPIO_KEY_SHUTTER1)) {
		uiKeyCode |= FLGKEY_SHUTTER1;
	}
	if (gpio_getPin(GPIO_KEY_SHUTTER2)) {
		uiKeyCode |= FLGKEY_SHUTTER2;
	}
	if (gpio_getPin(GPIO_KEY_ZOOMIN)) {
		uiKeyCode |= FLGKEY_ZOOMIN;
	}
	if (gpio_getPin(GPIO_KEY_ZOOMOUT)) {
		uiKeyCode |= FLGKEY_ZOOMOUT;
	}
	*/
	if (!gpio_getPin(GPIO_KEY_RIGHT)) {
		uiKeyCode |= FLGKEY_RIGHT;
		//DBG_IND("CAll GPIO_KEY_RIGHT\r\n");
		//DBG_IND("FLGKEY_ENTER!\n");
	}
#endif
    //detect if power-on by press playback key
    if (hwpower_get_power_key(POWER_ID_PSW1))
    {
        uiKeyCode |= FLGKEY_LEFT;
		//DBG_IND("CAll FLGKEY_LEFT\r\n");
    }
	
	temp = DrvKey_DetACCPower();
    uiKeyCode |= temp;
	//DBG_IND("KEY=%08x\r\n", uiKeyCode);

	DrvKey_DetKeyDelay();
	return uiKeyCode;
}
/**
  Detect power key is pressed or not.

  Detect power key is pressed or not.
  Return key pressed status (refer to KeyDef.h)

  @param void
  @return UINT32
*/
UINT32 DrvKey_DetPowerKey(void)
{
    static UINT32 ShutDownCount = 0;
	UINT32 uiKeyCode = 0;

	if (hwpower_get_power_key(POWER_ID_PSW1)) {
        ShutDownCount++;
		// Reset shutdown timer
		hwpower_set_power_key(POWER_ID_PSW1, 0xf0);
		if(ShutDownCount > 20) {
            uiKeyCode = FLGKEY_KEY_POWER;
	        }
	    } else {
	        ShutDownCount = 0;
		}
	return uiKeyCode;
}

UINT32 DrvKey_DetStatusKey(DX_STATUS_KEY_GROUP KeyGroup)
{
	UINT32 uiReturn = STATUS_KEY_LVL_UNKNOWN;
	switch (KeyGroup) {
	case DX_STATUS_KEY_GROUP1:
		break;

	case DX_STATUS_KEY_GROUP2:
		break;

	case DX_STATUS_KEY_GROUP3:
		break;

	case DX_STATUS_KEY_GROUP4:
		break;

	case DX_STATUS_KEY_GROUP5:
		break;

	default:
		DBG_ERR("[StatusKey]no this attribute");
		break;
	}
	return uiReturn;
}
void GPIOMap_SensorPowerOn(BOOL en)//no useless,gpio.dtsi pull up
{
#if 0//(defined(_NVT_ETHREARCAM_RX_))
    if (en) {
        gpio_setPin(GPIO_EHT_CAM_1_PWR);
    } else {
        gpio_clearPin(GPIO_EHT_CAM_1_PWR);
    }
#endif
}

void GPIOMap_Sensor2PowerOn(BOOL en)//no useless,gpio.dtsi pull up
{
#if (defined(_NVT_ETHREARCAM_RX_))    
    if (en) {
        gpio_setPin(GPIO_EHT_CAM_2_PWR);
    } else {
        gpio_clearPin(GPIO_EHT_CAM_2_PWR);
    }
 #endif   
}
BOOL GPIOMap_EthCam1Det(void)
{
#if (defined(_NVT_ETHREARCAM_RX_)&&(ETH_REARCAM_CAPS_COUNT>=1))
    if(gpio_getPin(GPIO_ETH1_DET)){
        return FALSE;
    }else {
        return TRUE;
    }
#else
	return FALSE;
#endif
}
BOOL GPIOMap_EthCam2Det(void)
{
#if (defined(_NVT_ETHREARCAM_RX_)&&(ETH_REARCAM_CAPS_COUNT>=2))
     if(gpio_getPin(GPIO_ETH2_DET)){
         return FALSE;
     }else {
         return TRUE;
     }
#else
	return FALSE;
#endif
}

