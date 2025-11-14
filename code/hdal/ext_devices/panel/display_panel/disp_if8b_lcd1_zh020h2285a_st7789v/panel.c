/*
    Display object object panel configuration parameters for PSD300

    @file       PSD300.c
    @ingroup
    @note       Nothing

    Copyright   Novatek Microelectronics Corp. 2021.  All rights reserved.
*/
#include "dispdev_if8bits.h"


/*
    panel Parameters for PSD300
*/
//@{
#define IFCMD_CMD   0x01
#define IFCMD_DATA  0x02

const T_PANEL_CMD t_cmd_standby[] = {
	//{0x2B, 0x00}
};

const T_PANEL_CMD t_cmd_mode_rgb320[] = {
    	{IFCMD_CMD,0x11},	
	{CMDDELAY_MS,130},	

	{IFCMD_CMD,0x36},
	{IFCMD_DATA,0x08}, 	//RGB565

	{IFCMD_CMD,0x3A},
	{IFCMD_DATA,0x66}, 	//RGB565


	{IFCMD_CMD,0xB0},  //Interface Control
	{IFCMD_DATA,0x11},	//RGB interface
	{IFCMD_DATA,0X04}, 	//0XF4	/RIM=1:6 BIT BUS WIDTH

	{IFCMD_CMD,0x21},
	{IFCMD_DATA,0x2A},
	
	{IFCMD_CMD,0xB1},  //RGB Interface Control
	{IFCMD_DATA,0xE0},  // without RAM=C0 , With RAM = 40h , HV mode=60h
	{IFCMD_DATA,0x04},  // V Bproch by HV mode= MCU porch
	{IFCMD_DATA,0x14},  // H Bproch by HV mode= MCU porch

	#if 1
	{IFCMD_CMD,0xB2},
	{IFCMD_DATA,0x05},
	{IFCMD_DATA,0x05},
	{IFCMD_DATA,0x00},
	{IFCMD_DATA,0x33},
	{IFCMD_DATA,0x33},
	#else
	{IFCMD_CMD,0xb2},
	{IFCMD_DATA,0x0c},
	{IFCMD_DATA,0x0c},
	{IFCMD_DATA,0x00},
	{IFCMD_DATA,0x33},
	{IFCMD_DATA,0x33},
	#endif
	
	{IFCMD_CMD,0xB7},
	{IFCMD_DATA,0x75},
					
	{IFCMD_CMD,0xF6},  //Interface Control
	{IFCMD_DATA,0x01},
	{IFCMD_DATA,0x13},
	{IFCMD_DATA,0x07},  //RIM: Specify the RGB interface mode when the RGB interface is used. 

	#if 1
	{IFCMD_CMD,0xBB},
	{IFCMD_DATA,0x22},  //1C
	
	{IFCMD_CMD,0xC0},
	{IFCMD_DATA,0x2C},
	
	{IFCMD_CMD,0xC2},
	{IFCMD_DATA,0x01},
	
	{IFCMD_CMD,0xC3},
	{IFCMD_DATA,0x13},  //0B
	
	{IFCMD_CMD,0xC4},
	{IFCMD_DATA,0x20},
	
	{IFCMD_CMD,0xC6},
	{IFCMD_DATA,0x11},
	
	{IFCMD_CMD,0xD0},
	{IFCMD_DATA,0xA4},
	{IFCMD_DATA,0xA1},
	#else
	{IFCMD_CMD,0xBB},
	{IFCMD_DATA,0x1C},
	
	{IFCMD_CMD,0xC0},     
	{IFCMD_DATA,0x2C},   

	{IFCMD_CMD,0xC2},     
	{IFCMD_DATA,0x01},   

	{IFCMD_CMD,0xC3},   //GVDD  
	{IFCMD_DATA,0x0B}, //   

	{IFCMD_CMD,0xC4},     
	{IFCMD_DATA,0x20},   

	{IFCMD_CMD,0xC6},     
	{IFCMD_DATA,0x0F},   

	{IFCMD_CMD,0xD0},     
	{IFCMD_DATA,0xA4},   
	{IFCMD_DATA,0xA1},  
	#endif

	{IFCMD_CMD,0xD6},
	{IFCMD_DATA,0xA1},

	#if 1
	{IFCMD_CMD,0xE0},
	{IFCMD_DATA,0xd0},
	{IFCMD_DATA,0x05}, //00
	{IFCMD_DATA,0x0a},  //03
	{IFCMD_DATA,0x09},  //09
	{IFCMD_DATA,0x08},  //13
	{IFCMD_DATA,0x05},//  //1C
	{IFCMD_DATA,0x2e},//  //3A
	{IFCMD_DATA,0x44},  //55
	{IFCMD_DATA,0x45},  //48
	{IFCMD_DATA,0x0f},   //18
	{IFCMD_DATA,0x17},   //12
	{IFCMD_DATA,0x16},  //0E
	{IFCMD_DATA,0x2b},   //19
	{IFCMD_DATA,0x33},//   //1E
	
	{IFCMD_CMD,0xE1},
	{IFCMD_DATA,0xd0},
	{IFCMD_DATA,0x05}, //00
	{IFCMD_DATA,0x0a},  //03
	{IFCMD_DATA,0x09},  //09
	{IFCMD_DATA,0x08},  //13
	{IFCMD_DATA,0x05},//  //1C
	{IFCMD_DATA,0x2e},//  //3A
	{IFCMD_DATA,0x43},  //55
	{IFCMD_DATA,0x45},  //48
	{IFCMD_DATA,0x0f},   //18
	{IFCMD_DATA,0x16},   //12
	{IFCMD_DATA,0x16},  //0E
	{IFCMD_DATA,0x2b},   //19
	{IFCMD_DATA,0x33},//   //1E
	#else
	{IFCMD_CMD,0xE0},     
	{IFCMD_DATA,0xD0},   
	{IFCMD_DATA,0x06},   
	{IFCMD_DATA,0x0B},   
	{IFCMD_DATA,0x0A},   
	{IFCMD_DATA,0x09},   
	{IFCMD_DATA,0x06},   
	{IFCMD_DATA,0x2F},   
	{IFCMD_DATA,0x44},   
	{IFCMD_DATA,0x45},   
	{IFCMD_DATA,0x18},   
	{IFCMD_DATA,0x14},   
	{IFCMD_DATA,0x14},   
	{IFCMD_DATA,0x27},   
	{IFCMD_DATA,0x2D},   

	{IFCMD_CMD,0xE1},     
	{IFCMD_DATA,0xD0},   
	{IFCMD_DATA,0x06},   
	{IFCMD_DATA,0x0B},   
	{IFCMD_DATA,0x0A},   
	{IFCMD_DATA,0x09},   
	{IFCMD_DATA,0x05},   
	{IFCMD_DATA,0x2E},   
	{IFCMD_DATA,0x43},   
	{IFCMD_DATA,0x45},   
	{IFCMD_DATA,0x18},   
	{IFCMD_DATA,0x14},   
	{IFCMD_DATA,0x14},   
	{IFCMD_DATA,0x27},   
	{IFCMD_DATA,0x2D},
	#endif
	
	{IFCMD_CMD,0x29},
	{CMDDELAY_MS,50},	
	
	{IFCMD_CMD,0x2C}, 
	{CMDDELAY_MS,20},
};

const T_LCD_PARAM t_mode[] = {
	/***********       RGB 320 mode         *************/
	{
		// T_PANEL_PARAM
		{
			/* Old prototype */
            PINMUX_LCDMODE_RGB_THROUGH,      //!< LCDMode
            5000000,//15960000 / 3,                           //!< fDCLK
                (41+240),              //0x3C       //!< uiHSyncTotalPeriod
                240,//960,                            //!< uiHSyncActivePeriod
                19,              // 0x3b             //!< uiHSyncBackPorch
                0x08+320,                        //!< uiVSyncTotalPeriod
                320,                            //!< uiVSyncActivePeriod
                0x04,                           //!< uiVSyncBackPorchOdd
                0x04,                           //!< uiVSyncBackPorchEven
                240,                            //!< uiBufferWidth
                320,                            //!< uiBufferHeight
                240,                            //!< uiWindowWidth
                320,                            //!< uiWindowHeight
			FALSE,                          //!< b_ycbcr_format

			/* New added parameters */
            0x0A,                           //!< uiHSyncSYNCwidth  
            0x02                             //!< uiVSyncSYNCwidth
		},

		// T_IDE_PARAM
		{
			/* Old prototype */
            PINMUX_LCD_SEL_SERIAL_RGB_6BITS,// PINMUX_LCD_SEL_SERIAL_RGB_8BITS,//!< pinmux_select_lcd;
			ICST_CCIR601,                   //!< icst;
            {TRUE,TRUE},                  //!< dithering[2];
            DISPLAY_DEVICE_AU,         //!< **DONT-CARE**
			IDE_PDIR_RBG,                   //!< pdir;
			IDE_LCD_G,                      //!< odd;
            IDE_LCD_G,                      //!< even;
			TRUE,                           //!< hsinv;
			TRUE,                           //!< vsinv;
			FALSE,                          //!< hvldinv;
			FALSE,                          //!< vvldinv;
			FALSE,                           //!< clkinv;
			FALSE,                          //!< fieldinv;
			FALSE,                          //!< **DONT-CARE**
			FALSE,                          //!< interlace;
			FALSE,                          //!< **DONT-CARE**
            0x50,                           //!< ctrst;
			0x00,                           //!< brt;
            0x50,                           //!< cmults;
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
	//{0x04,0x18}
};
const T_PANEL_CMD t_cmd_rotate_180[] = {
	//{0x04,0x1b}
};
const T_LCD_ROT t_rotate[] = {
	//{DISPDEV_LCD_ROTATE_NONE, (T_PANEL_CMD *)t_cmd_rotate_none, 1},
	//{DISPDEV_LCD_ROTATE_180, (T_PANEL_CMD *)t_cmd_rotate_180, 1}
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

#define SETTING_PANEL_REG_BIT_SHIFT_ADDRESS 8               //D[?] is Address LSB
#define SETTING_PANEL_REG_BIT_SHIFT_VALUE   0               //D[?] is Content LSB
#define SETTING_PANEL_REG_BIT_WRITE         14              //D[?] is Bit of Write Command
#define SETTING_PANEL_REG_MODE_WRITE        0               //BIT High(1) or LOW(0) is Write Mode
#define SETTING_PANEL_REG_MODE_READ         1               //BIT High(1) or LOW(0) is Read  Mode

#if 1
void dispdev_write_to_lcd_sif(DISPDEV_IOCTRL p_disp_dev_control, UINT32 addr, UINT32 value)
{
	UINT32                  ui_sif_data;
	DISPDEV_IOCTRL_PARAM    dev_io_ctrl;

	//Pack Data
	ui_sif_data = ((UINT32)addr << SETTING_PANEL_REG_BIT_SHIFT_ADDRESS)
				| ((UINT32)value << SETTING_PANEL_REG_BIT_SHIFT_VALUE);

	//Arrange Address
	ui_sif_data = ((ui_sif_data & (1 << SETTING_PANEL_REG_BIT_WRITE)) << 1)
				| (ui_sif_data & (~(1 << SETTING_PANEL_REG_BIT_WRITE)));

	ui_sif_data = (ui_sif_data << 16);
	//RW Mode
	//or 0 => skip
	//uiSIFData |= (SETTING_PANEL_REG_MODE_WRITE<<SETTING_PANEL_REG_BIT_WRITE);


	p_disp_dev_control(DISPDEV_IOCTRL_GET_REG_IF, &dev_io_ctrl);
	sif_send(dev_io_ctrl.SEL.GET_REG_IF.ui_sif_ch, ui_sif_data, 0, 0);
}


static void dispdev_writeToLcdGpio_Cmd(DISPDEV_IOCTRL p_disp_dev_control, UINT32 addr, UINT32 value)
{
	UINT32                  ui_sif_data, j;
	UINT32                  sif_clk, sif_sen, sif_data;
	DISPDEV_IOCTRL_PARAM    dev_io_ctrl;

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
	dispdev_platform_set_gpio_ouput(sif_clk, 1);
	dispdev_platform_set_gpio_ouput(sif_data, 1);

    ui_sif_data = (UINT32)value;
   // vk_pr_warn("ui_sif_data : 0x%08lx\r\n", ui_sif_data);

	dispdev_platform_delay_us(500);

	dispdev_platform_set_gpio_ouput(sif_sen, 0);


    for(j=9; j>0; j--)
    {
		if (((ui_sif_data >> (j - 1)) & 0x01)) {
			dispdev_platform_set_gpio_ouput(sif_data, 1);
		} else {
			dispdev_platform_set_gpio_ouput(sif_data, 0);
		}

		dispdev_platform_delay_us(100);
		dispdev_platform_set_gpio_ouput(sif_clk, 0);
		dispdev_platform_delay_us(200);
		dispdev_platform_set_gpio_ouput(sif_clk, 1);
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
 	UINT32                  ui_sif_data, j;
	UINT32                  sif_clk, sif_sen, sif_data;
	DISPDEV_IOCTRL_PARAM    dev_io_ctrl;

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
	dispdev_platform_set_gpio_ouput(sif_clk, 1);
	dispdev_platform_set_gpio_ouput(sif_data, 1);

    ui_sif_data = (UINT32)value;
    ui_sif_data |= 0x100;
    //vk_pr_warn("ui_sif_data : 0x%04lx\r\n", ui_sif_data);

	dispdev_platform_delay_us(500);

	dispdev_platform_set_gpio_ouput(sif_sen, 0);


    for(j=9; j>0; j--)
    {
		if (((ui_sif_data >> (j - 1)) & 0x01)) {
			dispdev_platform_set_gpio_ouput(sif_data, 1);
		} else {
			dispdev_platform_set_gpio_ouput(sif_data, 0);
		}

		dispdev_platform_delay_us(100);
		dispdev_platform_set_gpio_ouput(sif_clk, 0);
		dispdev_platform_delay_us(200);
		dispdev_platform_set_gpio_ouput(sif_clk, 1);
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
					DBG_WRN("panel dtsi gpio_cs is not set!\r\n");
				}

				cell = (uint32_t*)fdt_getprop((const void*)fdt_addr, nodeoffset, "gpio_clk", NULL);
				if (cell > 0) {
					disp_dev.SEL.SET_REG_IF.ui_gpio_clk = be32_to_cpu(cell[0]);
				} else {
					DBG_WRN("panel dtsi gpio_clk is not set!\r\n");
				}

				cell = (uint32_t*)fdt_getprop((const void*)fdt_addr, nodeoffset, "gpio_data", NULL);
				if (cell > 0) {
					disp_dev.SEL.SET_REG_IF.ui_gpio_data = be32_to_cpu(cell[0]);
				} else {
					DBG_WRN("panel dtsi gpio_data is not set!\r\n");
				}

				p_disp_obj->dev_ctrl(DISPDEV_SET_REG_IF, &disp_dev);

			}
		} else {
			DBG_WRN("panel dtsi lcd_ctrl is not set!\r\n");
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
    DBG_DUMP("Hello, panel: JD9852\r\n");
    return 0;
}

void panel_exit(void)
{
    DBG_DUMP("PW35P00, Goodbye\r\n");
}
#elif defined __KERNEL__
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
    pr_info("Hello, panel: PW35P00\n");
    return 0;
}

static void __exit panel_exit(void)
{
	PDISP_OBJ p_disp_obj;
	p_disp_obj = disp_get_display_object(DISP_1);

	p_disp_obj->dev_callback = NULL;
    printk(KERN_INFO "Goodbye\n");
}

module_init(panel_init);
module_exit(panel_exit);

MODULE_DESCRIPTION("PW35P00 Panel");
MODULE_AUTHOR("Novatek Corp.");
MODULE_LICENSE("GPL");
#endif
#endif
