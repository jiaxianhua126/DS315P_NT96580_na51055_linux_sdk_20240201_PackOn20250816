/*
    Display object object panel configuration parameters for T15P

    @file       panel.c
    @ingroup
    @note       Nothing

    Copyright   Novatek Microelectronics Corp. 2011.  All rights reserved.
*/

#include "dispdev_if8bits.h"
#include <linux/cdev.h>
#include <linux/uaccess.h>
#define LCD_ROTATE_FUN_EN	1

#if LCD_ROTATE_FUN_EN
#define LCD_NAME "t15p11"
#define LCDDEV_CNT 1
#define LCD_ROTATE_180  (_IO(0xEE,0x01))
#define LCD_ROTATE_NONE (_IO(0xEE,0x02))
extern DISPDEV_IOCTRL  p_if8bits_io_control1;
typedef struct __t15p_dev {
	dev_t devid;
	struct cdev cdev;
	struct class *class;
	struct device *device;
	int major;
	int minor;
}_t15p_dev;

_t15p_dev t15p_dev;
#endif

const T_PANEL_CMD *tCmdStandby = NULL;

const T_PANEL_CMD tCmdModeRGBSerial[] =
{
    {0x00, 0x00},

    {0x06, 0x00},
    {0x00, 0x0f},
    {0x04, 0x03},//0x03
    {0x03, 0x08},//0x08
    {0x05, 0x20},
    {0x07, 0x40},
    {0x0C, 0x05},
    {0x0E, 0x01}

};

const T_PANEL_CMD t_cmd_standby[] = {
	//{0x00, 0x08}
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
	0,
	// 24 bits per transmission
	24,
	// MSb shift out first
	SIF_DIR_MSB,
	}
};

const T_LCD_PARAM t_mode_n[] = {
    {
        {
            /* Old prototype */
            PINMUX_LCDMODE_RGB_SERIAL,      //!< LCDMode
            10000000,                       //!< fDCLK
            620,                           //!< uiHSyncTotalPeriod
            485,                           //!< uiHSyncActivePeriod
            94,                            //!< uiHSyncBackPorch
            262.5,                         //!< uiVSyncTotalPeriod
            242,                            //!< uiVSyncActivePeriod
            12,                             //!< uiVSyncBackPorchOdd
            12,                           //!< uiVSyncBackPorchEven
            480,                            //!< uiBufferWidth
            240,                            //!< uiBufferHeight
            480,                            //!< uiWindowWidth
            240,                            //!< uiWindowHeight
            FALSE,                          //!< bYCbCrFormat

            /* New added parameters */
            0x01,                           //!< uiHSyncSYNCwidth
            0x01                            //!< uiVSyncSYNCwidth
        },

        // tIDE_PARAM
        {
            /* Old prototype */
            PINMUX_LCD_SEL_SERIAL_RGB_8BITS,//!< pinmux_select_lcd;
            ICST_CCIR601,                   //!< icst;
            {FALSE,FALSE},                  //!< dithering[2];
            DISPLAY_DEVICE_TOPPOLY,         //!< **DONT-CARE**
            IDE_PDIR_RGB,                   //!< pdir;
            IDE_LCD_R,                      //!< odd;
            IDE_LCD_G,                      //!< even;
            TRUE,                           //!< hsinv;
            TRUE,                           //!< vsinv;
            FALSE,                          //!< hvldinv;
            FALSE,                          //!< vvldinv;
            TRUE,                           //!< clkinv;
            FALSE,                          //!< fieldinv;
            TRUE,                           //!< rgbdummy
            FALSE,                          //!< interlace;
            FALSE,                          //!< **DONT-CARE**
            0x40,                           //!< ctrst;
            0x00,                           //!< brt;
            0x40,                           //!< cmults;
            FALSE,                          //!< cex;
            FALSE,                          //!< **DONT-CARE**
            TRUE,                           //!< **DONT-CARE**
            TRUE,                           //!< tv_powerdown;
            {0x00,0x00},                    //!< **DONT-CARE**

            /* New added parameters */
            FALSE,                          //!< YCex
            FALSE,                          //!< HLPF
            {FALSE,FALSE,FALSE},            //!< subpixOdd[3]
            {FALSE,FALSE,FALSE},            //!< subpixEven[3]
            {IDE_DITHER_6BITS,IDE_DITHER_6BITS,IDE_DITHER_6BITS}, //!< DitherBits[3]
            FALSE,                          //!< clk1/2
        },

        (T_PANEL_CMD*)tCmdModeRGBSerial,                  //!< pCmdQueue
        sizeof(tCmdModeRGBSerial)/sizeof(T_PANEL_CMD),    //!< nCmd
    }
};



const T_PANEL_CMD tCmdRotateNone[] =
{
    {0x04, 0x03}
};

const T_PANEL_CMD tCmdRotate180[] =
{
    {0x04, 0x00}
};

const T_LCD_ROT t_rotate[] =
{
    {DISPDEV_LCD_ROTATE_NONE,   (T_PANEL_CMD*)tCmdRotateNone,    1},
    {DISPDEV_LCD_ROTATE_180,    (T_PANEL_CMD*)tCmdRotate180,     1}
};


//@}

T_LCD_ROT *dispdev_get_lcd_rotate_cmd(UINT32 *mode_number)
{
	if (t_rotate != NULL) {
		*mode_number = sizeof(t_rotate) / sizeof(T_LCD_ROT);
	} else {
		*mode_number = 0;
	}
	return (T_LCD_ROT *)t_rotate;
}

T_LCD_PARAM *dispdev_get_config_mode(UINT32 *mode_number)
{
	*mode_number = sizeof(t_mode_n) / sizeof(T_LCD_PARAM);
	return (T_LCD_PARAM *)t_mode_n;
}

T_PANEL_CMD *dispdev_get_standby_cmd(UINT32 *cmd_number)
{
	*cmd_number = sizeof(t_cmd_standby) / sizeof(T_PANEL_CMD);
	return (T_PANEL_CMD *)t_cmd_standby;
}

#if 1
void dispdev_write_to_lcd_sif(DISPDEV_IOCTRL p_disp_dev_control, UINT32 addr, UINT32 value)
{
	UINT32                  ui_sif_data;
	DISPDEV_IOCTRL_PARAM    dev_io_ctrl;

	ui_sif_data = (UINT32)addr << 24 | (UINT32)value << 8;

	p_disp_dev_control(DISPDEV_IOCTRL_GET_REG_IF, &dev_io_ctrl);
	sif_send(dev_io_ctrl.SEL.GET_REG_IF.ui_sif_ch, ui_sif_data, 0, 0);
}


void dispdev_write_to_lcd_gpio(DISPDEV_IOCTRL p_disp_dev_control, UINT32 addr, UINT32 value)
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

	ui_sif_data = (UINT32)addr << 12 | (UINT32)value;

	dispdev_platform_delay_us(500);

	dispdev_platform_set_gpio_ouput(sif_sen, 0);

	for (j = 16; j > 0; j--) {
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

T_LCD_SIF_PARAM *dispdev_get_lcd_sif_param(void)
{
	return (T_LCD_SIF_PARAM *)t_sif_param;
}

void dispdev_read_from_lcd_gpio(DISPDEV_IOCTRL p_disp_dev_control, UINT32 addr, UINT32 *p_value)
{
	DBG_ERR("Has not implement dispdev_read_from_lcd_gpio \r\n");
}

void dispdev_change_mode(UINT32 mode)
{
	DBG_DUMP("ntsc %d\r\n", (unsigned int)mode);
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
    DBG_DUMP("Hello, panel: T15P\r\n");
    return 0;
}

void panel_exit(void)
{
    DBG_DUMP("T15P, Goodbye\r\n");
}
#elif defined __KERNEL__

#if LCD_ROTATE_FUN_EN
	static int lcd_open(struct inode *inode,struct file *filp)
	{
		filp->private_data = &t15p_dev;
		printk("t15p lcd open success!\r\n");
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

	static long lcd_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
	{
		DISPDEV_PARAM   disp_dev;
		PDISP_OBJ p_disp_obj;
		DISPDEV_IOCTRL_PARAM    dev_io_ctrl;
		DISPDEV_IOCTRL p_disp_dev_control;
		p_disp_obj = disp_get_display_object(DISP_1);
		p_disp_obj->open();
		p_disp_obj->dev_callback = &dispdev_get_lcd1_dev_obj;
		p_disp_dev_control = p_if8bits_io_control1;
		if (p_disp_dev_control == NULL) {
			printk("p_disp_dev_control == NULL\r\n");
		}
		switch(cmd) {
			case LCD_ROTATE_180:
				printk("LCD ROTATE 180\r\n");
				dev_io_ctrl.SEL.SET_SRGB_OUTORDER.pix_order     = IDE_PDIR_RBG;
				dev_io_ctrl.SEL.SET_SRGB_OUTORDER.odd_start     = IDE_LCD_R;
				dev_io_ctrl.SEL.SET_SRGB_OUTORDER.even_start    = IDE_LCD_B;
				p_disp_dev_control(DISPDEV_IOCTRL_SET_SRGB_OUTORDER, &dev_io_ctrl);
				disp_dev.SEL.SET_ROTATE.rot = DISPDEV_LCD_ROTATE_180;
        		p_disp_obj->dev_ctrl(DISPDEV_SET_ROTATE, &disp_dev);
				break;
			case LCD_ROTATE_NONE:
				printk("LCD ROTATE NONE\r\n");
				dev_io_ctrl.SEL.SET_SRGB_OUTORDER.pix_order     = IDE_PDIR_RGB;
				dev_io_ctrl.SEL.SET_SRGB_OUTORDER.odd_start     = IDE_LCD_R;
				dev_io_ctrl.SEL.SET_SRGB_OUTORDER.even_start    = IDE_LCD_G;
				p_disp_dev_control(DISPDEV_IOCTRL_SET_SRGB_OUTORDER, &dev_io_ctrl);
				disp_dev.SEL.SET_ROTATE.rot = DISPDEV_LCD_ROTATE_NONE;
        		p_disp_obj->dev_ctrl(DISPDEV_SET_ROTATE, &disp_dev);
				break;
			default:
				break;
		}

		p_disp_obj->dev_callback = &dispdev_get_lcd1_dev_obj;
		p_disp_obj->close();
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

    printk(KERN_INFO "Hello, panel: T15P\n");
	DBG_WRN("Hello, panel: T15P\n");
	panel = of_find_node_by_name(NULL, "display");
	if (panel) {
		DBG_WRN("panel\n");
		if (!of_property_read_u32(panel, "lcd_ctrl", &value)) {
			DBG_WRN("value = %d\n", value);
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
			DBG_WRN("gpio_cs = %d, gpio_ck = %d, gpio_dat = %d\n", gpio_cs, gpio_ck, gpio_dat);
		} else {
			DBG_WRN("panel dtsi lcd_ctrl is not set!\r\n");
		}
	} else {
		DBG_WRN("can not find display node!\r\n");
	}

#if 0
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
#endif	
	p_disp_obj->dev_callback = &dispdev_get_lcd1_dev_obj;
	p_disp_obj->close();
	DBG_WRN("panel_init T15P end\r\n");

#if LCD_ROTATE_FUN_EN
	//1
	if (t15p_dev.major) {
		t15p_dev.devid = MKDEV(t15p_dev.major,0);
		register_chrdev_region(t15p_dev.devid,LCDDEV_CNT,LCD_NAME);
	} else {
		alloc_chrdev_region(&t15p_dev.devid,0,LCDDEV_CNT,LCD_NAME);
		t15p_dev.major = MAJOR(t15p_dev.devid);
		t15p_dev.minor = MINOR(t15p_dev.devid);
	}
	printk("t15p_dev major = %d,minor = %d\r\n",t15p_dev.major,t15p_dev.minor);
	//2
	t15p_dev.cdev.owner = THIS_MODULE;
	cdev_init(&t15p_dev.cdev,&devlcd_fops);
	cdev_add(&t15p_dev.cdev,t15p_dev.devid,LCDDEV_CNT);
	//3
	t15p_dev.class = class_create(THIS_MODULE,LCD_NAME);
	if (IS_ERR(t15p_dev.class)) {
		return PTR_ERR(t15p_dev.class);
	}
	//4
	t15p_dev.device = device_create(t15p_dev.class,NULL,t15p_dev.devid,NULL,LCD_NAME);
	if (IS_ERR(t15p_dev.device)) {
		return PTR_ERR(t15p_dev.device);
	}
#endif
    return 0;
}

static void __exit panel_exit(void)
{
	PDISP_OBJ p_disp_obj;
	p_disp_obj = disp_get_display_object(DISP_1);

	p_disp_obj->dev_callback = NULL;
	cdev_del(&t15p_dev.cdev);
	unregister_chrdev_region(t15p_dev.devid,LCDDEV_CNT);

	device_destroy(t15p_dev.class,t15p_dev.devid);
	class_destroy(t15p_dev.class);
    printk(KERN_INFO "Goodbye\n");
}

module_init(panel_init);
module_exit(panel_exit);

MODULE_DESCRIPTION("AUCN01 Panel");
MODULE_AUTHOR("Novatek Corp.");
MODULE_LICENSE("GPL");
#endif
#endif
