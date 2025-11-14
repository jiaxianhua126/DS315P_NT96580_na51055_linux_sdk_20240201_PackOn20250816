/*
    Display object for driving DSI device

    @file       LX318FWB1201.c
    @ingroup
    @note       This panel MUST select ide clock to PLL1 ( 480 ). Once change to \n
				another frequence, the _IDE_FDCLK should be re calculated

    Copyright   Novatek Microelectronics Corp. 2011.  All rights reserved.
*/
#include "dispdev_ifdsi.h"

#define FW_ROTATE       DISABLE//ENABLE

#define _LX318FWB1201_ 1
#define _JL_0316IVO_   2

#define DSI_LCD_OPT          _JL_0316IVO_

#if (FW_ROTATE == ENABLE)
#define PANEL_WIDTH     480
#define PANEL_HEIGHT    320
#else
#define PANEL_WIDTH     320//376
#define PANEL_HEIGHT    816//960
#endif

//_disp_ifdsi_lcd1_LX318FWB1201_
/*
    RGB888 = 1 pixel = 3bytes packet
    If DSI src = 240MHz, internal clock = 30MHz, data rate = 30MHz x 1bytes = 30MB / sec per lane
    2 lane = 60MB = 20Mpixel ' ide need > 20MHz
*/


#define DSI_FORMAT_RGB565          0    //N/A in LX318FWB1201
#define DSI_FORMAT_RGB666P         1    //N/A in LX318FWB1201
#define DSI_FORMAT_RGB666L         2    //N/A in LX318FWB1201
#define DSI_FORMAT_RGB888          3    //IDE use 480 & DSI use 480

#define DSI_OP_MODE_CMD_MODE       1
#define DSI_OP_MODE_VDO_MODE       0

#define DSI_PACKET_FORMAT          DSI_FORMAT_RGB888

#if (DSI_LCD_OPT == _LX318FWB1201_)
#define DSI_TARGET_CLK             480    //real chip use 480Mhz
#else
#define DSI_TARGET_CLK             300    //real chip use 240Mhz
#endif
//#define DSI_TARGET_CLK             160  //FPGA use 160MHz
//#define DSI_TARGET_CLK             120
#define DSI_OP_MODE                DSI_OP_MODE_VDO_MODE //DSI_OP_MODE_CMD_MODE

#if (DSI_PACKET_FORMAT == DSI_FORMAT_RGB666P) && (DSI_OP_MODE == DSI_OP_MODE_CMD_MODE)
#error "Command mode not support RGB666P"
#endif


#if (DSI_LCD_OPT == _LX318FWB1201_)
#define _IDE_fDCLK     	27500000
#else
#define _IDE_fDCLK      30000000 ///21500000
#endif


/*
    Panel Parameters for TCON  LX318FWB1201
*/
//@{
/*Used in DSI*/
const T_PANEL_CMD t_cmd_mode_dsi[] = {
	//{CMDDELAY_MS,  120},				//ms
#if (DSI_LCD_OPT == _LX318FWB1201_) 
	{DSICMD_CMD,  0xFF},
	{DSICMD_DATA,  0x77},
	{DSICMD_DATA,  0x01},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x13},
	
	{DSICMD_CMD,  0xEF},
	{DSICMD_DATA,  0x08},
	
	{DSICMD_CMD,  0xFF},
	{DSICMD_DATA,  0x77},
	{DSICMD_DATA,  0x01},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x10},
	
	{DSICMD_CMD,  0xC0},
	{DSICMD_DATA,  0x77},//63
	{DSICMD_DATA,  0x00},
	
	{DSICMD_CMD,  0xC1}, 
	{DSICMD_DATA,  0x0C},  //12
	{DSICMD_DATA,  0x0C},  //0A	
	 
	{DSICMD_CMD,  0xC2}, 
	{DSICMD_DATA,  0x07},
	{DSICMD_DATA,  0x02},  //

	//{DSICMD_CMD,  0x07}, //rotate
	//{DSICMD_DATA,  0x04},

	{DSICMD_CMD,  0xCC},
	{DSICMD_DATA,  0x10},
	
	{DSICMD_CMD,  0xB0},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x0C},
	{DSICMD_DATA,  0x19},
	{DSICMD_DATA,  0x0B},
	{DSICMD_DATA,  0x0F},
	{DSICMD_DATA,  0x06},
	{DSICMD_DATA,  0x05},
	{DSICMD_DATA,  0x08},
	{DSICMD_DATA,  0x08},
	{DSICMD_DATA,  0x1F},
	{DSICMD_DATA,  0x04},
	{DSICMD_DATA,  0x11},
	{DSICMD_DATA,  0x0F},
	{DSICMD_DATA,  0x26},
	{DSICMD_DATA,  0x2F},
	{DSICMD_DATA,  0x1D},
	
	{DSICMD_CMD,  0xB1},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x17},
	{DSICMD_DATA,  0x19},
	{DSICMD_DATA,  0x0F},
	{DSICMD_DATA,  0x12},
	{DSICMD_DATA,  0x05},
	{DSICMD_DATA,  0x05},
	{DSICMD_DATA,  0x08},
	{DSICMD_DATA,  0x07},
	{DSICMD_DATA,  0x1F},
	{DSICMD_DATA,  0x03},
	{DSICMD_DATA,  0x10},
	{DSICMD_DATA,  0x10},
	{DSICMD_DATA,  0x27},
	{DSICMD_DATA,  0x2F},
	{DSICMD_DATA,  0x1D},
	
	{DSICMD_CMD,  0xFF},
	{DSICMD_DATA,  0x77},
	{DSICMD_DATA,  0x01},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x11},
	
	{DSICMD_CMD,  0xB0},
	{DSICMD_DATA,  0x45},
	
	{DSICMD_CMD,  0xB1},
	{DSICMD_DATA,  0x76},
	
	{DSICMD_CMD,  0xB2},
	{DSICMD_DATA,  0x81},
	
	{DSICMD_CMD,  0xB3},
	{DSICMD_DATA,  0x80},
	
	{DSICMD_CMD,  0xB5},
	{DSICMD_DATA,  0x4e},
	
	{DSICMD_CMD,  0xB7},
	{DSICMD_DATA,  0x85},
	
	{DSICMD_CMD,  0xB8},
	{DSICMD_DATA,  0x20},
	
	{DSICMD_CMD,  0xC1},
	{DSICMD_DATA,  0x78},
	
	{DSICMD_CMD,  0xC2},
	{DSICMD_DATA,  0x78},
	
	{DSICMD_CMD,  0xD0},
	{DSICMD_DATA,  0x88},
	
	//{CMDDELAY_MS,  100},
	{DSICMD_CMD,  0xE0},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x02},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x0C},

	{DSICMD_CMD,  0xE1}, 
	{DSICMD_DATA,  0x02},	
	{DSICMD_DATA,  0x8C},
	{DSICMD_DATA,  0x04}, 
	{DSICMD_DATA,  0x8C},
	{DSICMD_DATA,  0x01},	
	{DSICMD_DATA,  0x8C},
	{DSICMD_DATA,  0x03}, 
	{DSICMD_DATA,  0x8C},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x44}, 
	{DSICMD_DATA,  0x44}, 
	
	{DSICMD_CMD,  0xE2}, 
	{DSICMD_DATA,  0x03},
	{DSICMD_DATA,  0x03},
	{DSICMD_DATA,  0x03},
	{DSICMD_DATA,  0x03}, 
	{DSICMD_DATA,  0x00}, 
	{DSICMD_DATA,  0x00},	
	{DSICMD_DATA,  0xD4}, 
	{DSICMD_DATA,  0x00}, 
	{DSICMD_DATA,  0x00}, 
	{DSICMD_DATA,  0x00},	
	{DSICMD_DATA,  0xD4},		  
	{DSICMD_DATA,  0x00},			
	
	{DSICMD_CMD,  0xE3},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x33},
	{DSICMD_DATA,  0x33},
	
	{DSICMD_CMD,  0xE4},
	{DSICMD_DATA,  0x44},
	{DSICMD_DATA,  0x44},
	
	{DSICMD_CMD,  0xE5}, 
	{DSICMD_DATA,  0x09},
	{DSICMD_DATA,  0xD2},
	{DSICMD_DATA,  0x35},
	{DSICMD_DATA,  0x8C},
	{DSICMD_DATA,  0x0B},
	{DSICMD_DATA,  0xD4},
	{DSICMD_DATA,  0x35},
	{DSICMD_DATA,  0x8C},
	{DSICMD_DATA,  0x05},
	{DSICMD_DATA,  0xCE},
	{DSICMD_DATA,  0x35},
	{DSICMD_DATA,  0x8C},
	{DSICMD_DATA,  0x07},
	{DSICMD_DATA,  0xD0},
	{DSICMD_DATA,  0x35},
	{DSICMD_DATA,  0x8C},
	
	{DSICMD_CMD,  0xE6},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x33},
	{DSICMD_DATA,  0x33},
	
	{DSICMD_CMD,  0xE7},
	{DSICMD_DATA,  0x44},
	{DSICMD_DATA,  0x44},
	
	{DSICMD_CMD,  0xE8}, 
	{DSICMD_DATA,  0x08},
	{DSICMD_DATA,  0xD1},
	{DSICMD_DATA,  0x35},
	{DSICMD_DATA,  0x8C},
	{DSICMD_DATA,  0x0A},
	{DSICMD_DATA,  0xD3},
	{DSICMD_DATA,  0x35},
	{DSICMD_DATA,  0x8C},
	{DSICMD_DATA,  0x04},
	{DSICMD_DATA,  0xCD},
	{DSICMD_DATA,  0x35},
	{DSICMD_DATA,  0x8C},
	{DSICMD_DATA,  0x06},
	{DSICMD_DATA,  0xCF},
	{DSICMD_DATA,  0x35},
	{DSICMD_DATA,  0x8C},
	
	{DSICMD_CMD,  0xEB},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x01},
	{DSICMD_DATA,  0xE4},
	{DSICMD_DATA,  0xE4},
	{DSICMD_DATA,  0x44},
	{DSICMD_DATA,  0x00},
	
	{DSICMD_CMD,  0xED},		 
	{DSICMD_DATA,  0x77},		  
	{DSICMD_DATA,  0x66},		  
	{DSICMD_DATA,  0x55},		  
	{DSICMD_DATA,  0x44},		  
	{DSICMD_DATA,  0xCA},		  
	{DSICMD_DATA,  0xF1},		  
	{DSICMD_DATA,  0x03},		  
	{DSICMD_DATA,  0xBF},		  
	{DSICMD_DATA,  0xFB},		  
	{DSICMD_DATA,  0x30},		  
	{DSICMD_DATA,  0x1F},		  
	{DSICMD_DATA,  0xAC},		  
	{DSICMD_DATA,  0x44},		  
	{DSICMD_DATA,  0x55},		  
	{DSICMD_DATA,  0x66},		  
	{DSICMD_DATA,  0x77},		  
	
	{DSICMD_CMD,  0xEF},
	{DSICMD_DATA,  0x10}, 
	{DSICMD_DATA,  0x0D}, 
	{DSICMD_DATA,  0x04}, 
	{DSICMD_DATA,  0x08}, 
	{DSICMD_DATA,  0x3F}, 
	{DSICMD_DATA,  0x1F},
	
	{DSICMD_CMD,  0xFF},
	{DSICMD_DATA,  0x77},
	{DSICMD_DATA,  0x01},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x13},
	
	{DSICMD_CMD,  0xE8},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x0E},
	
	
	{DSICMD_CMD,  0x11},//sleepout
	{DSICMD_DATA,  0x00},
	{CMDDELAY_MS,  120},
	

	{DSICMD_CMD,  0xE8},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x0C},
	{CMDDELAY_MS,  20},
	
	{DSICMD_CMD,  0xE8},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x00},
	
	{DSICMD_CMD,  0xFF},
	{DSICMD_DATA,  0x77},
	{DSICMD_DATA,  0x01},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x00},
	{DSICMD_DATA,  0x00},
	
	//{DSICMD_CMD,  0x36},
	//{DSICMD_DATA,  0x00},
	//{DSICMD_CMD,  0x35},
	//{DSICMD_DATA,  0x00},
	
	{DSICMD_CMD,  0x29},//displayout
	{DSICMD_DATA,  0x00},
	{CMDDELAY_MS,  120},
#else
	{DSICMD_CMD,  0xFF},
	{DSICMD_DATA,0x77},
	{DSICMD_DATA,0x01},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x13},
	{DSICMD_CMD,  0xEF},
	{DSICMD_DATA,0x08},
	{DSICMD_CMD,  0xFF},
	{DSICMD_DATA,0x77},
	{DSICMD_DATA,0x01},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x10},
	{DSICMD_CMD,  0xC0},
	{DSICMD_DATA,0xE5},
	{DSICMD_DATA,0x02},
	{DSICMD_CMD,  0xC1},
	{DSICMD_DATA,0x15},
	{DSICMD_DATA,0x0A},
	{DSICMD_CMD,  0xC2},
	{DSICMD_DATA,0x07},
	{DSICMD_DATA,0x02},
	{DSICMD_CMD,  0xCC},
	{DSICMD_DATA,0x10},
	{DSICMD_CMD,  0xB0},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x08},
	{DSICMD_DATA,0x51},
	{DSICMD_DATA,0x0D},
	{DSICMD_DATA,0xCE},
	{DSICMD_DATA,0x06},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x08},
	{DSICMD_DATA,0x08},
	{DSICMD_DATA,0x24},
	{DSICMD_DATA,0x05},
	{DSICMD_DATA,0xD0},
	{DSICMD_DATA,0x0F},
	{DSICMD_DATA,0x6F},
	{DSICMD_DATA,0x36},
	{DSICMD_DATA,0x1F},
	{DSICMD_CMD,  0xB1},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x10},
	{DSICMD_DATA,0x4F},
	{DSICMD_DATA,0x0C},
	{DSICMD_DATA,0x11},
	{DSICMD_DATA,0x05},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x07},
	{DSICMD_DATA,0x07},
	{DSICMD_DATA,0x18},
	{DSICMD_DATA,0x02},
	{DSICMD_DATA,0xD3},
	{DSICMD_DATA,0x11},
	{DSICMD_DATA,0x6E},
	{DSICMD_DATA,0x34},
	{DSICMD_DATA,0x1F},
	{DSICMD_CMD,  0xFF},
	{DSICMD_DATA,0x77},
	{DSICMD_DATA,0x01},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x11},
	{DSICMD_CMD,  0xB0},
	{DSICMD_DATA,0x4D},
	{DSICMD_CMD,  0xB1},
	{DSICMD_DATA,0x37},
	{DSICMD_CMD,  0xB2},
	{DSICMD_DATA,0x87},
	{DSICMD_CMD,  0xB3},
	{DSICMD_DATA,0x80},
	{DSICMD_CMD,  0xB5},
	{DSICMD_DATA,0x4A},
	{DSICMD_CMD,  0xB7},
	{DSICMD_DATA,0x85},
	{DSICMD_CMD,  0xB8},
	{DSICMD_DATA,0x21},
	{DSICMD_CMD,  0xB9},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x13},
	{DSICMD_CMD,  0xC0},
	{DSICMD_DATA,0x09},
	{DSICMD_CMD,  0xC1},
	{DSICMD_DATA,0x78},
	{DSICMD_CMD,  0xC2},
	{DSICMD_DATA,0x78},
	{DSICMD_CMD,  0xD0},
	{DSICMD_DATA,0x88},
	{CMDDELAY_MS,100},
	{DSICMD_CMD,  0xE0},
	{DSICMD_DATA,0x80},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x02},
	{DSICMD_CMD,  0xE1},
	{DSICMD_DATA,0x0F},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x10},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x60},
	{DSICMD_DATA,0x60},
	{DSICMD_CMD,  0xE2},
	{DSICMD_DATA,0x30},
	{DSICMD_DATA,0x30},
	{DSICMD_DATA,0x60},
	{DSICMD_DATA,0x60},
	{DSICMD_DATA,0x45},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x46},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_CMD,  0xE3},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x33},
	{DSICMD_DATA,0x33},
	{DSICMD_CMD,  0xE4},
	{DSICMD_DATA,0x44},
	{DSICMD_DATA,0x44},
	{DSICMD_CMD,  0xE5},
	{DSICMD_DATA,0x0F},
	{DSICMD_DATA,0x4A},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0x11},
	{DSICMD_DATA,0x4A},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0x13},
	{DSICMD_DATA,0x4A},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0x15},
	{DSICMD_DATA,0x4A},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0xA0},
	{DSICMD_CMD,  0xE6},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x33},
	{DSICMD_DATA,0x33},
	{DSICMD_CMD,  0xE7},
	{DSICMD_DATA,0x44},
	{DSICMD_DATA,0x44},
	{DSICMD_CMD,  0xE8},
	{DSICMD_DATA,0x10},
	{DSICMD_DATA,0x4A},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0x12},
	{DSICMD_DATA,0x4A},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0x14},
	{DSICMD_DATA,0x4A},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0x16},
	{DSICMD_DATA,0x4A},
	{DSICMD_DATA,0xA0},
	{DSICMD_DATA,0xA0},
	{DSICMD_CMD,  0xEB},
	{DSICMD_DATA,0x02},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x4E},
	{DSICMD_DATA,0x4E},
	{DSICMD_DATA,0xEE},
	{DSICMD_DATA,0x44},
	{DSICMD_DATA,0x00},
	{DSICMD_CMD,  0xED},
	{DSICMD_DATA,0xFF},
	{DSICMD_DATA,0xFF},
	{DSICMD_DATA,0x04},
	{DSICMD_DATA,0x56},
	{DSICMD_DATA,0x72},
	{DSICMD_DATA,0xFF},
	{DSICMD_DATA,0xFF},
	{DSICMD_DATA,0xFF},
	{DSICMD_DATA,0xFF},
	{DSICMD_DATA,0xFF},
	{DSICMD_DATA,0xFF},
	{DSICMD_DATA,0x27},
	{DSICMD_DATA,0x65},
	{DSICMD_DATA,0x40},
	{DSICMD_DATA,0xFF},
	{DSICMD_DATA,0xFF},
	{DSICMD_CMD,  0xEF},
	{DSICMD_DATA,0x08},
	{DSICMD_DATA,0x08},
	{DSICMD_DATA,0x08},
	{DSICMD_DATA,0x40},
	{DSICMD_DATA,0x3F},
	{DSICMD_DATA,0x64},
	{DSICMD_CMD,  0xFF},
	{DSICMD_DATA,0x77},
	{DSICMD_DATA,0x01},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x13},
	{DSICMD_CMD,  0xE8},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x0E},
	{DSICMD_CMD,  0xFF},
	{DSICMD_DATA,0x77},
	{DSICMD_DATA,0x01},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_CMD,  0x11},
	{CMDDELAY_MS,120},
	{DSICMD_CMD,  0xFF},
	{DSICMD_DATA,0x77},
	{DSICMD_DATA,0x01},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x13},
	{DSICMD_CMD,  0xE8},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x0C},
	{CMDDELAY_MS,10},
	{DSICMD_CMD,  0xE8},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_CMD,  0xFF},
	{DSICMD_DATA,0x77},
	{DSICMD_DATA,0x01},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_DATA,0x00},
	{DSICMD_CMD,  0x36},
	{DSICMD_DATA,0x00},
	{DSICMD_CMD,  0x35},
	{DSICMD_DATA,0x00},
	{DSICMD_CMD,  0x29},
	{CMDDELAY_MS,20 },

#endif

};


const T_PANEL_CMD t_cmd_standby_dsi[] = {
    {DSICMD_CMD,     0x28},     // Display OFF
    {DSICMD_CMD,     0x10}      // Sleep in
};

const T_LCD_PARAM t_mode_dsi[] = {
    /***********       MI Serial Format 1      *************/
    {
        // tPANEL_PARAM
        {
            /* Old prototype */
            //PINMUX_DSI_1_LANE_VDO_SYNC_EVENT_RGB666P,   //!< LCDMode
            //PINMUX_DSI_1_LANE_VDO_SYNC_PULSE_RGB666P,   //!< LCDMode
            //PINMUX_DSI_1_LANE_VDO_SYNC_EVENT_RGB666L,
            //PINMUX_DSI_1_LANE_VDO_SYNC_PULSE_RGB666L,   //!< LCDMode
            //PINMUX_DSI_1_LANE_VDO_SYNC_PULSE_RGB565,
#if (DSI_OP_MODE == DSI_OP_MODE_VDO_MODE)
#if (DSI_PACKET_FORMAT == DSI_FORMAT_RGB565)
            //PINMUX_DSI_1_LANE_VDO_SYNC_PULSE_RGB565,
            PINMUX_DSI_1_LANE_VDO_SYNC_EVENT_RGB565,
#elif (DSI_PACKET_FORMAT == DSI_FORMAT_RGB666P)
            //PINMUX_DSI_1_LANE_VDO_SYNC_EVENT_RGB666P,
            PINMUX_DSI_1_LANE_VDO_SYNC_PULSE_RGB666P,
#elif (DSI_PACKET_FORMAT == DSI_FORMAT_RGB666L)
            PINMUX_DSI_1_LANE_VDO_SYNC_EVENT_RGB666L,
            //PINMUX_DSI_1_LANE_VDO_SYNC_PULSE_RGB666L,
#elif (DSI_PACKET_FORMAT == DSI_FORMAT_RGB888)
            PINMUX_DSI_1_LANE_VDO_SYNC_EVENT_RGB888,
            //PINMUX_DSI_1_LANE_VDO_SYNC_PULSE_RGB888,
#endif

#else
#if (DSI_PACKET_FORMAT == DSI_FORMAT_RGB565)
            PINMUX_DSI_1_LANE_CMD_MODE_RGB565,
#elif (DSI_PACKET_FORMAT == DSI_FORMAT_RGB666L)
            PINMUX_DSI_1_LANE_CMD_MODE_RGB666L,
#elif (DSI_PACKET_FORMAT == DSI_FORMAT_RGB888)
            PINMUX_DSI_1_LANE_CMD_MODE_RGB888,
#endif
#endif
			_IDE_fDCLK,                             //!< fd_clk
#if (FW_ROTATE == ENABLE)
            (0x68+PANEL_HEIGHT),                         //!< uiHSyncTotalPeriod
            PANEL_HEIGHT,                                //!< uiHSyncActivePeriod
            0x34,                                       //!< uiHSyncBackPorch
            0x04+PANEL_WIDTH,                           //!< uiVSyncTotalPeriod
            PANEL_WIDTH,                               //!< uiVSyncActivePeriod
            0x02,                                       //!< uiVSyncBackPorchOdd
            0x02,                                       //!< uiVSyncBackPorchEven
#elif (DSI_LCD_OPT == _LX318FWB1201_)
			442,//(HVALIDST+HVALIDST+HSYNCT+PANEL_WIDTH), //!< uiHSyncTotalPeriod
            PANEL_WIDTH,                                //!< uiHSyncActivePeriod
			50,//HVALIDST,                               //!< uiHSyncBackPorch
			1006,//(VVALIDST+VVALIDST + VSYNCT+ PANEL_HEIGHT),//!< ui_vsync_total_period
            PANEL_HEIGHT,                               //!< uiVSyncActivePeriod
			20,//VVALIDST,                               //!< ui_vsync_back_porch_odd
			20,//VVALIDST,                               //!< ui_vsync_back_porch_even
#else////3.16
			PANEL_WIDTH+30+30+10,//(HVALIDST+HVALIDST+HSYNCT+PANEL_WIDTH), //!< uiHSyncTotalPeriod
            PANEL_WIDTH,                                //!< uiHSyncActivePeriod
			30,//HVALIDST, 58,4                              //!< uiHSyncBackPorch
			PANEL_HEIGHT+20+20+8,//(VVALIDST+VVALIDST + VSYNCT+ PANEL_HEIGHT),//!< ui_vsync_total_period
            PANEL_HEIGHT,                               //!< uiVSyncActivePeriod
			20,//VVALIDST,                               //!< ui_vsync_back_porch_odd
			20,//VVALIDST,                               //!< ui_vsync_back_porch_even			
#endif
			PANEL_WIDTH,                            //!< ui_buffer_width
			PANEL_HEIGHT,                           //!< ui_buffer_height
			PANEL_WIDTH,                            //!< ui_window_width
			PANEL_HEIGHT,                           //!< ui_window_height
			FALSE,                                  //!< b_ycbcr_format

			/* New added parameters */
#if (DSI_LCD_OPT == _LX318FWB1201_)
			0x06,                                   //!< ui_hsync_sync_width
			0x06                                    //!< ui_vsync_sync_width
#else ///3.16
			10,//0x04,									//!< ui_hsync_sync_width
			8,//0x04,									//!< ui_vsync_sync_width
#endif
		},


		// T_IDE_PARAM
		{
			/* Old prototype */
			PINMUX_LCD_SEL_GPIO,            //!< pinmux_select_lcd;
			ICST_CCIR601,                   //!< icst;
            {FALSE, FALSE},                  //!< dithering[2];
			DISPLAY_DEVICE_MIPIDSI,         //!< **DONT-CARE**
			IDE_PDIR_RGB,                   //!< pdir;
			IDE_LCD_R,                      //!< odd;
			IDE_LCD_G,                      //!< even;
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
			{FALSE, FALSE, FALSE},          //!< subpix_odd[3]
			{FALSE, FALSE, FALSE},          //!< subpix_even[3]
			{IDE_DITHER_5BITS, IDE_DITHER_6BITS, IDE_DITHER_5BITS}, //!< dither_bits[3]
			FALSE                           //!< clk1/2
		},

		(T_PANEL_CMD *)t_cmd_mode_dsi,                 //!< p_cmd_queue
		sizeof(t_cmd_mode_dsi) / sizeof(T_PANEL_CMD),  //!< n_cmd
	}
};

const T_LCD_ROT *t_rot_dsi = NULL;

//@}

T_LCD_ROT *dispdev_get_lcd_rotate_dsi_cmd(UINT32 *mode_number)
{
#if 0
	if (t_rot_dsi != NULL) {
		*mode_number = sizeof(t_rot_dsi) / sizeof(T_LCD_ROT);
	} else
#endif
	{
		*mode_number = 0;
	}
	return (T_LCD_ROT *)t_rot_dsi;
}

T_LCD_PARAM *dispdev_get_config_mode_dsi(UINT32 *mode_number)
{
	*mode_number = sizeof(t_mode_dsi) / sizeof(T_LCD_PARAM);
	return (T_LCD_PARAM *)t_mode_dsi;
}

T_PANEL_CMD *dispdev_get_standby_cmd_dsi(UINT32 *cmd_number)
{
	*cmd_number = sizeof(t_cmd_standby_dsi) / sizeof(T_PANEL_CMD);
	return (T_PANEL_CMD *)t_cmd_standby_dsi;
}

void dispdev_set_dsi_drv_config(DSI_CONFIG_ID id, UINT32 value)
{
	if (dsi_set_config(id, value) != E_OK)	{
		DBG_DUMP("dsi_set_config not support, id = 0x%x, value = 0x%x\r\n", (unsigned int)id, (unsigned int)value);
	}
}

void dispdev_set_dsi_config(DSI_CONFIG *p_dsi_config)
{
#if 0
	// DSI input source clock = 480
	// Target can be 480 / 240 / 160 / 120
	FLOAT   dsi_target_clk = DSI_TARGET_CLK;
	UINT32  div;


	div = (UINT32)(p_dsi_config->f_dsi_src_clk / dsi_target_clk);

	if (div == 0) {
        UT35067A0_WRN_MSG("Div = 0 force ++\r\n");
		div++;
	}
	pll_setClockRate(PLL_CLKSEL_DSI_CLKDIV, PLL_DSI_CLKDIV(div - 1));
#else
	dispdev_set_dsi_drv_config(DSI_CONFIG_ID_FREQ, DSI_TARGET_CLK * 1000000);
#endif
#if (DSI_TARGET_CLK == 160) //real is 150MHz
	dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TLPX, 3);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_BTA_TA_GO, 7);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_THS_PREPARE, 1);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_THS_ZERO, 4);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_THS_TRAIL, 2);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_THS_EXIT, 3);

    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_PREPARE, 1);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_ZERO, 7);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_POST, 8);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_PRE, 1);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_TRAIL, 1);
#elif(DSI_TARGET_CLK == 240)
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TLPX, 2);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_BTA_TA_GO, 7);
	dsi_set_config(DSI_CONFIG_ID_BTA_TA_SURE, 0);
	dsi_set_config(DSI_CONFIG_ID_BTA_TA_GET, 20);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_THS_PREPARE, 1);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_THS_ZERO, 4);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_THS_TRAIL, 3);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_THS_EXIT, 4);

    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_PREPARE, 2);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_ZERO, 9);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_POST, 9);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_PRE, 1);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_TRAIL, 2);
	dsi_set_config(DSI_CONFIG_ID_BTA_HANDSK_TMOUT_VAL, 0x40);
#elif(DSI_TARGET_CLK == 120)
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TLPX, 1);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_BTA_TA_GO, 4);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_THS_PREPARE, 1);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_THS_ZERO, 1);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_THS_TRAIL, 1);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_THS_EXIT, 1);

    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_PREPARE, 0);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_ZERO, 4);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_POST, 7);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_PRE, 1);
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TCLK_TRAIL, 1);

#endif
    dispdev_set_dsi_drv_config(DSI_CONFIG_ID_DATALANE_NO, DSI_DATA_LANE_0);
	dispdev_set_dsi_drv_config(DSI_CONFIG_ID_TE_BTA_INTERVAL, 0x1F);
	dispdev_set_dsi_drv_config(DSI_CONFIG_ID_CLK_PHASE_OFS, 0x3);
	//dispdev_set_dsi_drv_config(DSI_CONFIG_ID_PHASE_DELAY_ENABLE_OFS, 0x1);

	#if 0
	dispdev_set_dsi_drv_config(DSI_CONFIG_ID_CLK_LP_CTRL, 0x1);
	#else
	dispdev_set_dsi_drv_config(DSI_CONFIG_ID_CLK_LP_CTRL, 0x0);
	#endif
	dispdev_set_dsi_drv_config(DSI_CONFIG_ID_SYNC_DLY_CNT, 0xF);
	dsi_set_config(DSI_CONFIG_ID_EOT_PKT_EN, TRUE);//mask check
}

#if defined __FREERTOS
int panel_init(void)
{
	unsigned char *fdt_addr = (unsigned char *)fdt_get_base();
	int nodeoffset;
	uint32_t *cell = NULL;
	DISPDEV_PARAM   disp_dev;
	PDISP_OBJ p_disp_obj;
	uint32_t value = 0;
	p_disp_obj = disp_get_display_object(DISP_1);

    if(fdt_addr == NULL)
		return -1;

	nodeoffset = fdt_path_offset((const void*)fdt_addr, "/logo");
	if (nodeoffset >= 0) {
		cell = (uint32_t*)fdt_getprop((const void*)fdt_addr, nodeoffset, "enable", NULL);
		if (cell > 0) {
			 value = be32_to_cpu(cell[0]);
			 disp_dev.SEL.SET_LOGOMODE.b_en_logo = value;
			p_disp_obj->dev_ctrl(DISPDEV_SET_LOGOMODE, &disp_dev);
			if(value == 0){
				dsi_reset();
			}
		} else {
			dsi_reset();
			DBG_WRN("panel dtsi logo mode enable is not set!\r\n");
		}
	} else {
		dsi_reset();
		DBG_WRN("can not find logo node!\r\n");
	}
	
	p_disp_obj->dev_callback = &dispdev_get_lcd1_dev_obj;
    DBG_DUMP("Hello, panel: LX318FWB1201\n");
    return 0;
}

void panel_exit(void)
{
    DBG_DUMP("LX318FWB1201, Goodbye\r\n");
}

#elif defined __KERNEL__
static int __init panel_init(void)
{
	DISPDEV_PARAM   disp_dev;
	struct device_node *panel;
	u32 value = 0;
	PDISP_OBJ p_disp_obj;
	p_disp_obj = disp_get_display_object(DISP_1);

	panel = of_find_node_by_name(NULL, "logo");
	if (panel) {
		if (!of_property_read_u32(panel, "enable", &value)) {
			disp_dev.SEL.SET_LOGOMODE.b_en_logo = value;
			p_disp_obj->dev_ctrl(DISPDEV_SET_LOGOMODE, &disp_dev);
			if(value == 0){
				dsi_reset();
			}
		} else {
			dsi_reset();
			DBG_WRN("panel dtsi logo mode enable is not set!\r\n");

		}
	} else {
		dsi_reset();
		DBG_WRN("can not find logo node!\r\n");
	}
	
	p_disp_obj->dev_callback = &dispdev_get_lcd1_dev_obj;
    pr_info("Hello, panel: LX318FWB1201\n");
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

MODULE_DESCRIPTION("LX318FWB1201 Panel");
MODULE_AUTHOR("Novatek Corp.");
MODULE_LICENSE("GPL");
#endif


