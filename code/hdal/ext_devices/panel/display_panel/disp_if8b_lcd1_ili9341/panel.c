/*
    Display object object panel configuration parameters for ili9341

    @file       ili9341.c
    @ingroup
    @note       Nothing

    Copyright   Novatek Microelectronics Corp. 2021.  All rights reserved.
*/
#include "dispdev_if8bits.h"
#include <linux/cdev.h>
#include <linux/uaccess.h>
#define IFCMD_CMD   0x01000000
#define IFCMD_DATA  0x02000000
#define LCD_ROTATE_FUN_EN	1
#define PANEL_WIDTH 	720
#define PANEL_HEIGHT	320

#if LCD_ROTATE_FUN_EN
#define LCD_NAME "ili9341"
#define LCDDEV_CNT 1
#define LCD_ROTATE_180  (_IO(0xEE,0x01))
#define LCD_ROTATE_NONE (_IO(0xEE,0x02))
extern DISPDEV_IOCTRL  p_if8bits_io_control1;
typedef struct __ili9341_dev {
	dev_t devid;
	struct cdev cdev;
	struct class *class;
	struct device *device;
	int major;
	int minor;
}_ili9341_dev;

_ili9341_dev ili9341_dev;
#endif

/*
    panel Parameters for ili9341c
*/
//@{
const T_PANEL_CMD t_cmd_standby[] = {
//  {MICMD_CMD,0x28}, //Display off
  {CMDDELAY_US, 1},
//  {MICMD_CMD,0x10}, //enter sleep mode
//  {MICMD_CMD,0x2c}, //memory write
};

const T_PANEL_CMD t_cmd_mode_rgb320[] = {

#if 1
	{CMDDELAY_MS, 120},
	{IFCMD_CMD, 0x11},	//Sleep out
	{CMDDELAY_MS, 120}, //Delay 120ms

	{IFCMD_CMD, 0x36}, //Memory Data Access Control
	{IFCMD_DATA,0x1C}, //0x00 // MY MX MV ML RGB MH XX XX

	{IFCMD_CMD, 0x21},

	{IFCMD_CMD, 0xB2},
	{IFCMD_DATA,0x05},
	{IFCMD_DATA,0x05},
	{IFCMD_DATA,0x00},
	{IFCMD_DATA,0x33},
	{IFCMD_DATA,0x33},

	{IFCMD_CMD, 0xB7},
	{IFCMD_DATA,0x64},

	{IFCMD_CMD, 0xBB},
	{IFCMD_DATA,0x2A},

	{IFCMD_CMD, 0xC0},
	{IFCMD_DATA,0x2C},

	{IFCMD_CMD, 0xC2},
	{IFCMD_DATA,0x01},

	{IFCMD_CMD, 0xC3}, //VRH--->值越小越暗,反之越白
	{IFCMD_DATA,0x13},

	{IFCMD_CMD, 0xC4},
	{IFCMD_DATA,0x20},

	{IFCMD_CMD, 0xC6},
	{IFCMD_DATA,0x11},

	{IFCMD_CMD, 0xD0},
	{IFCMD_DATA,0xA4},
	{IFCMD_DATA,0xA1},

	{IFCMD_CMD, 0xD6},
	{IFCMD_DATA,0xA1},

	{IFCMD_CMD, 0xB0}, //影响RGB显示
	{IFCMD_DATA,0x11}, //11
	{IFCMD_DATA,0xF4}, //CC

	{IFCMD_CMD, 0xB1}, //影响RGB显示,如果显示方向不对,请调整这里
	{IFCMD_DATA,0xEE}, //0xE0//Mode Selection HV Mode//0xEE
	{IFCMD_DATA,0x04}, //04
	{IFCMD_DATA,0x14}, //14//15

	{IFCMD_CMD, 0xE0},
	{IFCMD_DATA,0xD0},
	{IFCMD_DATA,0x06},
	{IFCMD_DATA,0x06},
	{IFCMD_DATA,0x0E},
	{IFCMD_DATA,0x0D},
	{IFCMD_DATA,0x06},
	{IFCMD_DATA,0x2F},
	{IFCMD_DATA,0x3A},
	{IFCMD_DATA,0x47},
	{IFCMD_DATA,0x08},
	{IFCMD_DATA,0x15},
	{IFCMD_DATA,0x14},
	{IFCMD_DATA,0x2C},
	{IFCMD_DATA,0x33},

	{IFCMD_CMD, 0xE1},
	{IFCMD_DATA,0xD0},
	{IFCMD_DATA,0x06},
	{IFCMD_DATA,0x06},
	{IFCMD_DATA,0x0E},
	{IFCMD_DATA,0x0D},
	{IFCMD_DATA,0x06},
	{IFCMD_DATA,0x2F},
	{IFCMD_DATA,0x3B},
	{IFCMD_DATA,0x47},
	{IFCMD_DATA,0x08},
	{IFCMD_DATA,0x15},
	{IFCMD_DATA,0x14},
	{IFCMD_DATA,0x2C},
	{IFCMD_DATA,0x33},

	{IFCMD_CMD, 0x3A},
	{IFCMD_DATA,0x06}, //06--->262K(RGB666);05--->65K

	{IFCMD_CMD, 0x29}, //Display ON

	/*
	{IFCMD_CMD, 0x2a},
	{IFCMD_DATA,0x00},
	{IFCMD_DATA,0x00},
	{IFCMD_DATA,0x00},
	{IFCMD_DATA,0xdf},

	{IFCMD_CMD, 0x2b},
	{IFCMD_DATA,0x00},
	{IFCMD_DATA,0x00},
	{IFCMD_DATA,0x01},
	{IFCMD_DATA,0x3f},

	{IFCMD_CMD, 0x2c},
	*/

#elif 0 //ZH020H2278A - STT7789V
	{IFCMD_CMD,0x11},	
	{CMDDELAY_MS,130},	

	{IFCMD_CMD,0x36},
	{IFCMD_DATA,0x1C},	//RGB565

	{IFCMD_CMD,0x3A},
	{IFCMD_DATA,0x06},	//RGB565

	{IFCMD_CMD,0x21},

	{IFCMD_CMD,0xB2},
	{IFCMD_DATA,0x05},
	{IFCMD_DATA,0x05},
	{IFCMD_DATA,0x00},
	{IFCMD_DATA,0x33},
	{IFCMD_DATA,0x33},

	{IFCMD_CMD,0xB7},
	{IFCMD_DATA,0x75},
					
	{IFCMD_CMD,0xF6},  //Interface Control
	{IFCMD_DATA,0x01},
	{IFCMD_DATA,0x13},
	{IFCMD_DATA,0x07},	//RIM: Specify the RGB interface mode when the RGB interface is used. 

	{IFCMD_CMD,0xBB},
	{IFCMD_DATA,0x22},	//1C

	{IFCMD_CMD,0xC0},
	{IFCMD_DATA,0x2C},

	{IFCMD_CMD,0xC2},
	{IFCMD_DATA,0x01},

	{IFCMD_CMD,0xC3},
	{IFCMD_DATA,0x1E}, //0B //VRH--->值越小越暗,反之越白

	{IFCMD_CMD,0xC4},
	{IFCMD_DATA,0x20},

	{IFCMD_CMD,0xC6},
	{IFCMD_DATA,0x11},

	{IFCMD_CMD,0xD0},
	{IFCMD_DATA,0xA4},
	{IFCMD_DATA,0xA1},

	{IFCMD_CMD,0xD6},
	{IFCMD_DATA,0xA1},

	{IFCMD_CMD, 0xB0}, //影响RGB显示
	{IFCMD_DATA,0x11}, //11
	{IFCMD_DATA,0xF4}, //CC

	{IFCMD_CMD, 0xB1}, //影响RGB显示,如果显示方向不对,请调整这里
	{IFCMD_DATA,0xEE}, //0xE0//Mode Selection HV Mode//0xEE
	{IFCMD_DATA,0x04}, //04
	{IFCMD_DATA,0x14}, //14//15

	{IFCMD_CMD,0xE0},
	{IFCMD_DATA,0xd0},
	{IFCMD_DATA,0x05}, //00
	{IFCMD_DATA,0x0a},	//03
	{IFCMD_DATA,0x09},	//09
	{IFCMD_DATA,0x08},	//13
	{IFCMD_DATA,0x05},	//1C
	{IFCMD_DATA,0x2e},	//3A
	{IFCMD_DATA,0x44},	//55
	{IFCMD_DATA,0x45},	//48
	{IFCMD_DATA,0x0f},	 //18
	{IFCMD_DATA,0x17},	 //12
	{IFCMD_DATA,0x16},	//0E
	{IFCMD_DATA,0x2b},	 //19
	{IFCMD_DATA,0x33},	 //1E

	{IFCMD_CMD,0xE1},
	{IFCMD_DATA,0xd0},
	{IFCMD_DATA,0x05}, //00
	{IFCMD_DATA,0x0a},	//03
	{IFCMD_DATA,0x09},	//09
	{IFCMD_DATA,0x08},	//13
	{IFCMD_DATA,0x05},	//1C
	{IFCMD_DATA,0x2e},	//3A
	{IFCMD_DATA,0x43},	//55
	{IFCMD_DATA,0x45},	//48
	{IFCMD_DATA,0x0f},	 //18
	{IFCMD_DATA,0x16},	 //12
	{IFCMD_DATA,0x16},	//0E
	{IFCMD_DATA,0x2b},	 //19
	{IFCMD_DATA,0x33},	 //1E

	{IFCMD_CMD,0x29},
	{CMDDELAY_MS,50},	

	{IFCMD_CMD,0x2C}, 
	{CMDDELAY_MS,20},	

#elif 0 //FTD020H2278A - STT7789V
	{CMDDELAY_MS,120},	 //ms
	{IFCMD_CMD , 0x11},  //Sleep out
	{CMDDELAY_MS,120},	 //Delay 120ms

	{IFCMD_CMD , 0x36}, 	
	{IFCMD_DATA , 0x1C},   

	{IFCMD_CMD , 0x21}, 	

	{IFCMD_CMD , 0xB2}, 	
	{IFCMD_DATA , 0x05},   
	{IFCMD_DATA , 0x05},   
	{IFCMD_DATA , 0x00},   
	{IFCMD_DATA , 0x33},   
	{IFCMD_DATA , 0x33},   

	{IFCMD_CMD , 0xB7}, 	
	{IFCMD_DATA , 0x75},   

	{IFCMD_CMD , 0xBB}, 	
	{IFCMD_DATA , 0x22},   

	{IFCMD_CMD , 0xC0}, 	
	{IFCMD_DATA , 0x2C},   

	{IFCMD_CMD , 0xC2}, 	
	{IFCMD_DATA , 0x01},   

	{IFCMD_CMD , 0xC3}, 	
	{IFCMD_DATA , 0x13},   

	{IFCMD_CMD , 0xC4}, 	
	{IFCMD_DATA , 0x20},   

	{IFCMD_CMD , 0xC6}, 	
	{IFCMD_DATA , 0x11},   

	{IFCMD_CMD , 0xD0}, 	
	{IFCMD_DATA , 0xA4},   
	{IFCMD_DATA , 0xA1},   

	{IFCMD_CMD , 0xD6}, 	
	{IFCMD_DATA , 0xA1},   

	{IFCMD_CMD, 0xB0}, //影响RGB显示
	{IFCMD_DATA,0x11}, //11
	{IFCMD_DATA,0xF4}, //CC

	{IFCMD_CMD, 0xB1}, //影响RGB显示,如果显示方向不对,请调整这里
	{IFCMD_DATA,0xEE}, //0xE0//Mode Selection HV Mode//0xEE
	{IFCMD_DATA,0x04}, //04
	{IFCMD_DATA,0x14}, //14//15

	{IFCMD_CMD , 0xE0}, 	
	{IFCMD_DATA , 0xD0},   
	{IFCMD_DATA , 0x05},   
	{IFCMD_DATA , 0x0A},   
	{IFCMD_DATA , 0x09},   
	{IFCMD_DATA , 0x08},   
	{IFCMD_DATA , 0x05},   
	{IFCMD_DATA , 0x2E},   
	{IFCMD_DATA , 0x44},   
	{IFCMD_DATA , 0x45},   
	{IFCMD_DATA , 0x0F},   
	{IFCMD_DATA , 0x17},   
	{IFCMD_DATA , 0x16},   
	{IFCMD_DATA , 0x2B},   
	{IFCMD_DATA , 0x33},   

	{IFCMD_CMD , 0xE1}, 	
	{IFCMD_DATA , 0xD0},   
	{IFCMD_DATA , 0x05},   
	{IFCMD_DATA , 0x0A},   
	{IFCMD_DATA , 0x09},   
	{IFCMD_DATA , 0x08},   
	{IFCMD_DATA , 0x05},   
	{IFCMD_DATA , 0x2E},   
	{IFCMD_DATA , 0x43},   
	{IFCMD_DATA , 0x45},   
	{IFCMD_DATA , 0x0F},   
	{IFCMD_DATA , 0x16},   
	{IFCMD_DATA , 0x16},   
	{IFCMD_DATA , 0x2B},   
	{IFCMD_DATA , 0x33},   

	{IFCMD_CMD, 0x3A},
	{IFCMD_DATA,0x06}, //06--->262K(RGB666);05--->65K

	{IFCMD_CMD , 0x29}, 	//Display on

#else
	//ZH020B2232E - STST7789V (TN)
	{IFCMD_CMD,0x11},	
	{CMDDELAY_MS,130},	

	{IFCMD_CMD,0x36},
	{IFCMD_DATA,0x1C},

	{IFCMD_CMD,0x3A},
	{IFCMD_DATA,0x06},	//RGB565
	/*
	{IFCMD_CMD,0xB0},	 //Interface Control
	{IFCMD_DATA,0x11},	//RGB interface
	{IFCMD_DATA,0X04},	//0XF4	/RIM=1:6 BIT BUS WIDTH

	{IFCMD_CMD,0xB1},  //RGB Interface Control
	{IFCMD_DATA,0xe0},	// without RAM=C0 , With RAM = 40h , HV mode=60h	  //E0
	{IFCMD_DATA,0x03},	// V Bproch by HV mode= MCU porch
	{IFCMD_DATA,0x14},	// H Bproch by HV mode= MCU porch
	*/
	{IFCMD_CMD,0xB2},
	{IFCMD_DATA,0x0C},
	{IFCMD_DATA,0x0C},
	{IFCMD_DATA,0x00},
	{IFCMD_DATA,0x33},
	{IFCMD_DATA,0x33},

	//{IFCMD_CMD,0xB7},
	//{IFCMD_DATA,0x35},  //VGH,VGL 			

	{IFCMD_CMD,0xBB},
	{IFCMD_DATA,0x35},	//VCOM

	{IFCMD_CMD,0xC0},
	{IFCMD_DATA,0x2C},	

	{IFCMD_CMD,0xC2},
	{IFCMD_DATA,0x01},

	{IFCMD_CMD,0xC3},
	{IFCMD_DATA,0x0B},

	{IFCMD_CMD,0xC4},
	{IFCMD_DATA,0x20},

	{IFCMD_CMD,0xC5},
	{IFCMD_DATA,0x0D},

	{IFCMD_CMD,0xC6},
	{IFCMD_DATA,0x09},	// dot inversion

	{IFCMD_CMD,0xD0},
	{IFCMD_DATA,0xA4},
	{IFCMD_DATA,0xA1},


	{IFCMD_CMD, 0xD6},
	{IFCMD_DATA,0xA1},

	{IFCMD_CMD, 0xB0}, //影响RGB显示
	{IFCMD_DATA,0x11}, //11
	{IFCMD_DATA,0xF4}, //CC

	{IFCMD_CMD, 0xB1}, //影响RGB显示,如果显示方向不对,请调整这里
	{IFCMD_DATA,0xEE}, //0xE0//Mode Selection HV Mode//0xEE
	{IFCMD_DATA,0x04}, //04
	{IFCMD_DATA,0x14}, //14//15


	{IFCMD_CMD,0xE0},
	{IFCMD_DATA,0xd0},
	{IFCMD_DATA,0x00},
	{IFCMD_DATA,0x03},
	{IFCMD_DATA,0x09},
	{IFCMD_DATA,0x13},
	{IFCMD_DATA,0x1c},
	{IFCMD_DATA,0x3a},
	{IFCMD_DATA,0x55},
	{IFCMD_DATA,0x48},
	{IFCMD_DATA,0x18},
	{IFCMD_DATA,0x12},
	{IFCMD_DATA,0x0e},
	{IFCMD_DATA,0x19},
	{IFCMD_DATA,0x1e},

	{IFCMD_CMD,0xE1},
	{IFCMD_DATA,0xd0},
	{IFCMD_DATA,0x00},
	{IFCMD_DATA,0x03},
	{IFCMD_DATA,0x09},
	{IFCMD_DATA,0x05},
	{IFCMD_DATA,0x25},
	{IFCMD_DATA,0x3a},
	{IFCMD_DATA,0x55},
	{IFCMD_DATA,0x50},
	{IFCMD_DATA,0x3d},
	{IFCMD_DATA,0x1c},
	{IFCMD_DATA,0x1d},
	{IFCMD_DATA,0x1d},
	{IFCMD_DATA,0x1e}, 

	{IFCMD_CMD,0x29},
	{CMDDELAY_MS,50},	

	//{IFCMD_CMD,0x2C}, 
	//{CMDDELAY_MS,20}, 

#endif
};

const T_LCD_PARAM t_mode[] = {
	/***********       RGB 320 mode         *************/
	{
		// T_PANEL_PARAM
		{
			/* Old prototype */
		    PINMUX_LCDMODE_RGB_SERIAL,         //!< lcd_mode
            18000000,
            1024,                           //!< uiHSyncTotalPeriod
			729,                            //!< ui_hsync_active_period
            69,                             //!< uiHSyncBackPorch  26 32
            380,                            //!< uiVSyncTotalPeriod
			350,                            //!< ui_vsync_active_period
            8,                              //!< uiVSyncBackPorchOdd
            8,                              //!< uiVSyncBackPorchEven
			PANEL_WIDTH,                    //!< ui_buffer_width
			PANEL_HEIGHT,                   //!< ui_buffer_height
			PANEL_WIDTH,                    //!< ui_window_width
			PANEL_HEIGHT,                   //!< ui_window_height
			FALSE,                          //!< b_ycbcr_format

			/* New added parameters */
			0x0A,                           //!< ui_hsync_sync_width
            0x04                            //!< uiVSyncSYNCwidth
		},

		// T_IDE_PARAM
		{
			/* Old prototype */
			PINMUX_LCD_SEL_SERIAL_RGB_6BITS,//!< pinmux_select_lcd;
			ICST_CCIR601,                   //!< icst;
			{FALSE, FALSE},                 //!< dithering[2];
            DISPLAY_DEVICE_TOPPOLY,         //!< **DONT-CARE**
            IDE_PDIR_RBG,                   //!< pdir;
			IDE_LCD_R,                      //!< odd;
            IDE_LCD_R,                      //!< even;
			TRUE,                           //!< hsinv;
			TRUE,                           //!< vsinv;
			FALSE,                          //!< hvldinv;
			FALSE,                          //!< vvldinv;
			TRUE,                           //!< clkinv;
			FALSE,                          //!< fieldinv;
			FALSE,                          //!< **DONT-CARE**
			FALSE,                          //!< interlace;
			FALSE,                          //!< **DONT-CARE**
			0x40,                           //!< ctrst;
			0x00,                           //!< brt;
            0x40,                           //!< cmults;
			FALSE,                          //!< cex;
			FALSE,                          //!< **DONT-CARE**
			TRUE,                           //!< **DONT-CARE**
			TRUE,                           //!< tv_powerdown;
			{0x00, 0x00},                   //!< **DONT-CARE**

			/* New added parameters */
			FALSE,                          //!< yc_ex
			FALSE,                          //!< hlpf
            {TRUE,TRUE,TRUE},               //!< subpixOdd[3]
			{FALSE, FALSE, FALSE},          //!< subpix_even[3]
			{IDE_DITHER_6BITS, IDE_DITHER_6BITS, IDE_DITHER_6BITS} //!< dither_bits[3]
		},

		(T_PANEL_CMD *)t_cmd_mode_rgb320,                 //!< p_cmd_queue
		sizeof(t_cmd_mode_rgb320) / sizeof(T_PANEL_CMD),  //!< n_cmd
	}

};
const T_PANEL_CMD t_cmd_rotate_none[] = {
    {0x36,0x1C},
};
const T_PANEL_CMD t_cmd_rotate_180[] = {
    {0x36,0x08},
};
const T_LCD_ROT t_rotate[] = {
	{DISPDEV_LCD_ROTATE_NONE, (T_PANEL_CMD *)t_cmd_rotate_none, 1},
	{DISPDEV_LCD_ROTATE_180, (T_PANEL_CMD *)t_cmd_rotate_180, 1}
};

const T_LCD_SIF_PARAM t_sif_param[] = {
	{
	// SIF mode 00
	0,
	//SIF_MODE_00,
	// Bus clock maximun = 20 MHz
	18000000,
	// SENS = 0
	30,
	// SENH = 30
	50,
	// 24 bits per transmission
	16,
	// MSb shift out first
	SIF_DIR_MSB,
	}
};
//@}

T_LCD_ROT *dispdev_get_lcd_rotate_cmd(UINT32 *mode_number)
{

	*mode_number = sizeof(t_rotate) / sizeof(T_LCD_ROT);

	return (T_LCD_ROT *)t_rotate;
}

T_LCD_PARAM *dispdev_get_config_mode(UINT32 *mode_number)
{
	*mode_number = sizeof(t_mode) / sizeof(T_LCD_PARAM);
	return (T_LCD_PARAM *)t_mode;
}

T_PANEL_CMD *dispdev_get_standby_cmd(UINT32 *cmd_number)
{
	*cmd_number = sizeof(t_cmd_standby) / sizeof(T_PANEL_CMD);
	return (T_PANEL_CMD *)t_cmd_standby;
}
void dispdev_write_to_lcd_sif(DISPDEV_IOCTRL p_disp_dev_control, UINT32 addr, UINT32 value)
{
    UINT32                  ui_sif_data;
    DISPDEV_IOCTRL_PARAM    dev_io_ctrl;

    ui_sif_data = ((((UINT32)addr << 8)|((UINT32)value)) << 16);

	p_disp_dev_control(DISPDEV_IOCTRL_GET_REG_IF, &dev_io_ctrl);
	sif_send(dev_io_ctrl.SEL.GET_REG_IF.ui_sif_ch, ui_sif_data, 0, 0);
}

static void dispdev_writeToLcdGpio_Cmd(DISPDEV_IOCTRL p_disp_dev_control, UINT32 addr, UINT32 value)
{
	UINT32					ui_sif_data, j;
	UINT32					sif_clk, sif_sen, sif_data;
	DISPDEV_IOCTRL_PARAM	dev_io_ctrl;


    p_disp_dev_control(DISPDEV_IOCTRL_GET_REG_IF, &dev_io_ctrl);
	sif_clk  = dev_io_ctrl.SEL.GET_REG_IF.ui_gpio_clk;
	sif_sen  = dev_io_ctrl.SEL.GET_REG_IF.ui_gpio_sen;
	sif_data = dev_io_ctrl.SEL.GET_REG_IF.ui_gpio_data;

	
	if (dispdev_platform_request_gpio(sif_clk, "clk")) {
		DBG_ERR("gpio%d requset err\r\n", (int)sif_clk);
	}
	if (dispdev_platform_request_gpio(sif_sen, "sen")) {
		DBG_ERR("gpio%d requset err\r\n", (int)sif_sen);
	}
	if (dispdev_platform_request_gpio(sif_data, "data")) {
		DBG_ERR("gpio%d requset err\r\n", (int)sif_data);
	}

	dispdev_platform_set_gpio_ouput(sif_sen, 1);
	dispdev_platform_set_gpio_ouput(sif_data, 1);
	dispdev_platform_set_gpio_ouput(sif_clk, 0);


    ui_sif_data = (UINT32)value;

    dispdev_platform_delay_us(500);

	dispdev_platform_set_gpio_ouput(sif_sen, 0);
    for(j=9; j>0; j--)
    {
        if(((ui_sif_data >> (j - 1)) & 0x01))
        {
			dispdev_platform_set_gpio_ouput(sif_data, 1);
        }
        else
        {
			dispdev_platform_set_gpio_ouput(sif_data, 0);
        }

        dispdev_platform_delay_us(100);
		dispdev_platform_set_gpio_ouput(sif_clk, 1);
        dispdev_platform_delay_us(200);
		dispdev_platform_set_gpio_ouput(sif_clk, 0);
        dispdev_platform_delay_us(100);
    }
    dispdev_platform_delay_us(500);
	dispdev_platform_set_gpio_ouput(sif_sen, 1);
	
	dispdev_platform_free_gpio(sif_clk);
	dispdev_platform_free_gpio(sif_sen);
	dispdev_platform_free_gpio(sif_data);

}


static void dispdev_writeToLcdGpio_data(DISPDEV_IOCTRL p_disp_dev_control, UINT32 addr, UINT32 value)
{
	UINT32					ui_sif_data, j;
	UINT32					sif_clk, sif_sen, sif_data;
	DISPDEV_IOCTRL_PARAM	dev_io_ctrl;



    p_disp_dev_control(DISPDEV_IOCTRL_GET_REG_IF, &dev_io_ctrl);
	sif_clk  = dev_io_ctrl.SEL.GET_REG_IF.ui_gpio_clk;
	sif_sen  = dev_io_ctrl.SEL.GET_REG_IF.ui_gpio_sen;
	sif_data = dev_io_ctrl.SEL.GET_REG_IF.ui_gpio_data;

	if (dispdev_platform_request_gpio(sif_clk, "clk")) {
		DBG_ERR("gpio%d requset err\r\n", (int)sif_clk);
	}
	if (dispdev_platform_request_gpio(sif_sen, "sen")) {
		DBG_ERR("gpio%d requset err\r\n", (int)sif_sen);
	}
	if (dispdev_platform_request_gpio(sif_data, "data")) {
		DBG_ERR("gpio%d requset err\r\n", (int)sif_data);
	}

	dispdev_platform_set_gpio_ouput(sif_sen, 1);
	dispdev_platform_set_gpio_ouput(sif_data, 1);
	dispdev_platform_set_gpio_ouput(sif_clk, 0);


    ui_sif_data = (UINT32)value;
    ui_sif_data |= 0x100;

    dispdev_platform_delay_us(500);

	dispdev_platform_set_gpio_ouput(sif_sen, 0);

    for(j=9; j>0; j--)
    {
        if(((ui_sif_data >> (j - 1)) & 0x01))
        {
			dispdev_platform_set_gpio_ouput(sif_data, 1);
        }
        else
        {
			dispdev_platform_set_gpio_ouput(sif_data, 0);
        }

        dispdev_platform_delay_us(100);
		dispdev_platform_set_gpio_ouput(sif_clk, 1);
        dispdev_platform_delay_us(200);
		dispdev_platform_set_gpio_ouput(sif_clk, 0);
        dispdev_platform_delay_us(100);
    }
    dispdev_platform_delay_us(500);
	dispdev_platform_set_gpio_ouput(sif_sen, 1);
	dispdev_platform_free_gpio(sif_clk);
	dispdev_platform_free_gpio(sif_sen);
	dispdev_platform_free_gpio(sif_data);
	
}
void dispdev_write_to_lcd_gpio(DISPDEV_IOCTRL p_disp_dev_control, UINT32 addr, UINT32 value)
{
    if(addr & IFCMD_DATA)
        dispdev_writeToLcdGpio_data(p_disp_dev_control,addr,value);
    else
        dispdev_writeToLcdGpio_Cmd(p_disp_dev_control,addr,value);
}
void dispdev_read_from_lcd_gpio(DISPDEV_IOCTRL p_disp_dev_control, UINT32 addr, UINT32 *p_value)
{
	DBG_ERR("Has not implement dispdev_read_from_lcd_gpio \r\n");
}

T_LCD_SIF_PARAM *dispdev_get_lcd_sif_param(void)
{
	return (T_LCD_SIF_PARAM *)t_sif_param;
}

#if defined __FREERTOS
int panel_init(void)
{
	unsigned char *fdt_addr = (unsigned char *)fdt_get_base();
	int nodeoffset;
	uint32_t *cell = NULL;
	DISPDEV_PARAM   disp_dev;
	PDISP_OBJ p_disp_obj;
	p_disp_obj = disp_get_display_object(DISP_1);
	p_disp_obj->open();

    if(fdt_addr == NULL)
		return -1;


	nodeoffset = fdt_path_offset((const void*)fdt_addr, "/display");
	if (nodeoffset >= 0) {

		cell = (uint32_t*)fdt_getprop((const void*)fdt_addr, nodeoffset, "lcd_ctrl", NULL);
		if (cell > 0) {
			if (be32_to_cpu(cell[0]) == 0) {
				disp_dev.SEL.SET_REG_IF.lcd_ctrl = DISPDEV_LCDCTRL_SIF;
				disp_dev.SEL.SET_REG_IF.ui_gpio_sen = 0;
				disp_dev.SEL.SET_REG_IF.ui_gpio_clk = 0;
				disp_dev.SEL.SET_REG_IF.ui_gpio_data = 0;

				cell = (uint32_t*)fdt_getprop((const void*)fdt_addr, nodeoffset, "sif_channel", NULL);
				if (cell > 0) {
					disp_dev.SEL.SET_REG_IF.ui_sif_ch = (SIF_CH)(be32_to_cpu(cell[0]));
					p_disp_obj->dev_ctrl(DISPDEV_SET_REG_IF, &disp_dev);
				} else {
					DBG_WRN("panel dtsi sif_channel is not set!\r\n");
				}
			} else {
				disp_dev.SEL.SET_REG_IF.lcd_ctrl = DISPDEV_LCDCTRL_GPIO;
				disp_dev.SEL.SET_REG_IF.ui_sif_ch = 0;

				cell = (uint32_t*)fdt_getprop((const void*)fdt_addr, nodeoffset, "gpio_cs", NULL);
				if (cell > 0) {
					disp_dev.SEL.SET_REG_IF.ui_gpio_sen = be32_to_cpu(cell[0]);
				} else {
					DBG_ERR("panel dtsi gpio_cs is not set!\r\n");
				}

				cell = (uint32_t*)fdt_getprop((const void*)fdt_addr, nodeoffset, "gpio_clk", NULL);
				if (cell > 0) {
					disp_dev.SEL.SET_REG_IF.ui_gpio_clk = be32_to_cpu(cell[0]);
				} else {
					DBG_ERR("panel dtsi gpio_clk is not set!\r\n");
				}

				cell = (uint32_t*)fdt_getprop((const void*)fdt_addr, nodeoffset, "gpio_data", NULL);
				if (cell > 0) {
					disp_dev.SEL.SET_REG_IF.ui_gpio_data = be32_to_cpu(cell[0]);
				} else {
					DBG_ERR("panel dtsi gpio_data is not set!\r\n");
				}
				DBG_DUMP("LCD_SEN=%d LCD_CLK=%d LCD_DATA=%d\r\n",(int)(disp_dev.SEL.SET_REG_IF.ui_gpio_sen),(int)(disp_dev.SEL.SET_REG_IF.ui_gpio_clk),(int)(disp_dev.SEL.SET_REG_IF.ui_gpio_data));

				p_disp_obj->dev_ctrl(DISPDEV_SET_REG_IF, &disp_dev);
				

			}
		} else {
			DBG_ERR("panel dtsi lcd_ctrl is not set!\r\n");
		}
	} else {
		DBG_WRN("can not find display node!\r\n");
	}


	nodeoffset = fdt_path_offset((const void*)fdt_addr, "/logo");
	if (nodeoffset >= 0) {
		cell = (uint32_t*)fdt_getprop((const void*)fdt_addr, nodeoffset, "enable", NULL);
		if (cell > 0) {
			disp_dev.SEL.SET_LOGOMODE.b_en_logo = be32_to_cpu(cell[0]);
			p_disp_obj->dev_ctrl(DISPDEV_SET_LOGOMODE, &disp_dev);
		} else {
			DBG_WRN("panel dtsi logo mode enable is not set!\r\n");
		}
	} else {
		DBG_WRN("can not find logo node!\r\n");
	}	

	p_disp_obj->dev_callback = &dispdev_get_lcd1_dev_obj;
	p_disp_obj->close();
    DBG_DUMP("Hello, panel: ILI9341\r\n");
    return 0;
}

void panel_exit(void)
{
    DBG_DUMP("ili9341, Goodbye\r\n");
}
#elif defined __KERNEL__

#if LCD_ROTATE_FUN_EN
	static int lcd_open(struct inode *inode,struct file *filp)
	{
		filp->private_data = &ili9341_dev;
		printk("ili9341 lcd open success!\r\n");
		return 0;
	}

	static ssize_t lcd_read(struct file *filp,char __user *buf,size_t cnt,loff_t *offt) 
	{
		return 0;
	}

	static ssize_t lcd_write(struct file *filp,const char __user *buf,size_t cnt,loff_t *offt)
	{
		int retvalue;
		unsigned char databuf[1];
		unsigned char lcd_rotate_status;

		retvalue = copy_from_user(databuf,buf,cnt);
		if(retvalue < 0) {
			printk("kernel write failed!\r\n");
			return -EFAULT;
		}

		lcd_rotate_status = databuf[0];
		if (lcd_rotate_status) {
			printk("lcd rotate 180\r\n");
		} else {
			printk("lcd normal mode\r\n");
		}

		return cnt;
	}


	static void dispdev_write_lcd_reg(UINT32 ui_addr, UINT32 ui_value)
	{
		DISPDEV_IOCTRL_PARAM    dev_io_ctrl;
	#if (DISPLCDSEL_IF8BITS_TYPE == DISPLCDSEL_IF8BITS_LCD1)
		DISPDEV_IOCTRL          p_disp_dev_control = p_if8bits_io_control1;
	#elif (DISPLCDSEL_IF8BITS_TYPE == DISPLCDSEL_IF8BITS_LCD2)
		DISPDEV_IOCTRL          p_disp_dev_control = p_if8bits_io_control2;
	#endif

		p_disp_dev_control(DISPDEV_IOCTRL_GET_REG_IF, &dev_io_ctrl);
	#if (DISPLCDSEL_IF8BITS_TYPE == DISPLCDSEL_IF8BITS_LCD1)
		if (dev_io_ctrl.SEL.GET_REG_IF.lcd_ctrl == DISPDEV_LCDCTRL_GPIO) {
			dispdev_write_to_lcd_gpio(p_disp_dev_control, ui_addr, ui_value);
		} else if (dev_io_ctrl.SEL.GET_REG_IF.lcd_ctrl == DISPDEV_LCDCTRL_SIF) {
			dispdev_write_to_lcd_sif(p_disp_dev_control, ui_addr, ui_value);
		}
	#elif (DISPLCDSEL_IF8BITS_TYPE == DISPLCDSEL_IF8BITS_LCD2)
		if (dev_io_ctrl.SEL.GET_REG_IF.lcd_ctrl == DISPDEV_LCDCTRL_GPIO) {
			dispdev_write_to_lcd_gpio2(p_disp_dev_control, ui_addr, ui_value);
		} else if (dev_io_ctrl.SEL.GET_REG_IF.lcd_ctrl == DISPDEV_LCDCTRL_SIF) {
			dispdev_write_to_lcd_sif2(p_disp_dev_control, ui_addr, ui_value);
		}
	#endif
		//return E_OK;
	}


	static long lcd_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
	{
		DISPDEV_LCD_ROTATE lcd_rot;
		switch(cmd) {
			case LCD_ROTATE_180:
				lcd_rot = DISPDEV_LCD_ROTATE_180;
				dispdev_write_lcd_reg(IFCMD_CMD,0x36);
				dispdev_write_lcd_reg(IFCMD_DATA,0x08);
				printk("LCD ROTATE 180\r\n");
				break;
			case LCD_ROTATE_NONE:
				lcd_rot = DISPDEV_LCD_ROTATE_NONE;			
				dispdev_write_lcd_reg(IFCMD_CMD,0x36);
				dispdev_write_lcd_reg(IFCMD_DATA,0xC8);
				printk("LCD ROTATE NONE\r\n");
				break;
			default:
				break;
		}
		return 0;
	}

	static int lcd_release(struct inode *inode,struct file *filp)
	{
		return 0;
	}
	static struct file_operations devlcd_fops = {
		.owner = THIS_MODULE,
		.open = lcd_open,
		.read = lcd_read,
		.write = lcd_write,
		.unlocked_ioctl = lcd_ioctl,
		.release = lcd_release,
	};
	

#endif


static int __init panel_init(void)
{
	DISPDEV_PARAM   disp_dev;
	u32 gpio_cs = 0;
	u32 gpio_ck = 0;
	u32 gpio_dat = 0;
	struct device_node *panel;
	u32 value = 0;
	PDISP_OBJ p_disp_obj;
	p_disp_obj = disp_get_display_object(DISP_1);
	p_disp_obj->open();

	panel = of_find_node_by_name(NULL, "display");
	if (panel) {
		if (!of_property_read_u32(panel, "lcd_ctrl", &value)) {
			if (value == 0) {
				disp_dev.SEL.SET_REG_IF.lcd_ctrl = DISPDEV_LCDCTRL_SIF;
				disp_dev.SEL.SET_REG_IF.ui_gpio_sen = 0;
				disp_dev.SEL.SET_REG_IF.ui_gpio_clk = 0;
				disp_dev.SEL.SET_REG_IF.ui_gpio_data = 0;
				if (!of_property_read_u32(panel, "sif_channel", &value)) {
					disp_dev.SEL.SET_REG_IF.ui_sif_ch = (SIF_CH)value;
					p_disp_obj->dev_ctrl(DISPDEV_SET_REG_IF, &disp_dev);
				} else {
					DBG_WRN("panel dtsi sif_channel is not set!\r\n");
				}
			} else {
				disp_dev.SEL.SET_REG_IF.lcd_ctrl = DISPDEV_LCDCTRL_GPIO;
				if (!of_property_read_u32(panel, "gpio_cs", &gpio_cs)) {
				} else {
					DBG_WRN("panel dtsi gpio_cs is not set!\r\n");
				}
				if (!of_property_read_u32(panel, "gpio_clk", &gpio_ck)) {
				} else {
					DBG_WRN("panel dtsi gpio_clk is not set!\r\n");
				}
				if (!of_property_read_u32(panel, "gpio_data", &gpio_dat)) {
				} else {
					DBG_WRN("panel dtsi gpio_data is not set!\r\n");
				}

				disp_dev.SEL.SET_REG_IF.ui_sif_ch = 0;
				disp_dev.SEL.SET_REG_IF.ui_gpio_sen = gpio_cs;
				disp_dev.SEL.SET_REG_IF.ui_gpio_clk = gpio_ck;
				disp_dev.SEL.SET_REG_IF.ui_gpio_data = gpio_dat;
				p_disp_obj->dev_ctrl(DISPDEV_SET_REG_IF, &disp_dev);

			}
		} else {
			DBG_WRN("panel dtsi lcd_ctrl is not set!\r\n");
		}
	} else {
		DBG_WRN("can not find display node!\r\n");
	}

	panel = of_find_node_by_name(NULL, "logo");
	if (panel) {
		if (!of_property_read_u32(panel, "enable", &value)) {
			disp_dev.SEL.SET_LOGOMODE.b_en_logo = value;
			p_disp_obj->dev_ctrl(DISPDEV_SET_LOGOMODE, &disp_dev);
		} else {
			DBG_WRN("panel dtsi logo mode enable is not set!\r\n");
		}
	} else {
		DBG_WRN("can not find logo node!\r\n");
	}	
	
	p_disp_obj->dev_callback = &dispdev_get_lcd1_dev_obj;
	p_disp_obj->close();
    pr_info("Hello, panel: ILI9341\n");

#if LCD_ROTATE_FUN_EN
	//1
	if (ili9341_dev.major) {
		ili9341_dev.devid = MKDEV(ili9341_dev.major,0);
		register_chrdev_region(ili9341_dev.devid,LCDDEV_CNT,LCD_NAME);
	} else {
		alloc_chrdev_region(&ili9341_dev.devid,0,LCDDEV_CNT,LCD_NAME);
		ili9341_dev.major = MAJOR(ili9341_dev.devid);
		ili9341_dev.minor = MINOR(ili9341_dev.devid);
	}
	printk("ili9341_dev major = %d,minor = %d\r\n",ili9341_dev.major,ili9341_dev.minor);
	//2
	ili9341_dev.cdev.owner = THIS_MODULE;
	cdev_init(&ili9341_dev.cdev,&devlcd_fops);
	cdev_add(&ili9341_dev.cdev,ili9341_dev.devid,LCDDEV_CNT);
	//3
	ili9341_dev.class = class_create(THIS_MODULE,LCD_NAME);
	if (IS_ERR(ili9341_dev.class)) {
		return PTR_ERR(ili9341_dev.class);
	}
	//4
	ili9341_dev.device = device_create(ili9341_dev.class,NULL,ili9341_dev.devid,NULL,LCD_NAME);
	if (IS_ERR(ili9341_dev.device)) {
		return PTR_ERR(ili9341_dev.device);
	}
#endif
    return 0;
}

static void __exit panel_exit(void)
{
	PDISP_OBJ p_disp_obj;
	p_disp_obj = disp_get_display_object(DISP_1);

	p_disp_obj->dev_callback = NULL;
#if LCD_ROTATE_FUN_EN
    cdev_del(&ili9341_dev.cdev);
	unregister_chrdev_region(ili9341_dev.devid,LCDDEV_CNT);

	device_destroy(ili9341_dev.class,ili9341_dev.devid);
	class_destroy(ili9341_dev.class);
#endif
    printk(KERN_INFO "Goodbye\n");
}

module_init(panel_init);
module_exit(panel_exit);

MODULE_DESCRIPTION("ILI9341 Panel");
MODULE_AUTHOR("Novatek Corp.");
MODULE_LICENSE("GPL");
#endif
