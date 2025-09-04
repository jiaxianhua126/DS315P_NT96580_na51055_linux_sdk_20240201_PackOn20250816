#ifdef __KERNEL__
#include <linux/delay.h>
#include <linux/module.h>
#include "gsensor_main.h"
#include "gsensor_drv.h"
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/vmalloc.h>
#include <linux/moduleparam.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/io.h>
#include <linux/of_device.h>
#include <linux/kdev_t.h>
#include <linux/clk.h>
#include <linux/mm.h>
#include <kwrap/dev.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#else
#include "gsensor_main.h"
#include "gsensor_drv.h"
#endif

#include "kwrap/util.h"

#define __MODULE__			gsen_da380
#define __DBGLVL__			1      // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__			"*"    //*=All, [mark]=CustomClass
#include <kwrap/debug.h>

#define MALLOC(x) kzalloc((x), GFP_KERNEL)
#define FREE(x) kfree((x))

//=============================================================================
// function declaration
//=============================================================================
static long gsen_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
static ER gsen_i2c_init_driver(UINT32 i2c_id);
static int gsen_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int gsen_i2c_remove(struct i2c_client *client);
static void gsen_i2c_remove_driver(UINT32 id);
static INT32 gsen_i2c_transfer(struct i2c_msg *msgs, INT32 num);
int8_t gsen_i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t data, uint16_t len);
int8_t gsen_i2c_read(uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint16_t len);
static int __init gsen_module_init(void);
static void __exit gsen_module_exit(void);

//=============================================================================
// Global variable
//=============================================================================
static int LEVEL = 1;

struct gsensor_ioctl_data {
	int cmd;
	int data;
};

static GSEN_I2C gsen_i2c = {
	GSEN_I2C_ID_3, GSEN_I2C_ADDR
};

static struct i2c_board_info gsen_i2c_device = {
	.type = GSEN_I2C_NAME,
	.addr = GSEN_I2C_ADDR,
};

static GSEN_I2C_INFO *gsen_i2c_info;

static const struct i2c_device_id gsen_i2c_id[] = {
	{ GSEN_I2C_NAME, 0 },
	{ }
};

static struct i2c_driver gsen_i2c_driver = {
	.driver = {
		.name  = GSEN_I2C_NAME,
        .owner = THIS_MODULE,
	},
	.probe    = gsen_i2c_probe,
	.remove   = gsen_i2c_remove,
	.id_table = gsen_i2c_id,
};

//=============================================================================
// function define
//=============================================================================
static ER gsen_i2c_init_driver(UINT32 i2c_id)
{
	ER ret = E_OK;
	printk(KERN_ERR "gsen_i2c_init_driver %X \n", gsen_i2c_device.addr);
	if (i2c_new_device(i2c_get_adapter(i2c_id), &gsen_i2c_device) == NULL) {
		DBG_ERR("%s fail: i2c_new_device not OK.\n", __FUNCTION__);
		printk(KERN_ERR "%s fail: i2c_new_device not OK.\n", __FUNCTION__);
	}
	if (i2c_add_driver(&gsen_i2c_driver) != 0) {
		DBG_ERR("%s fail: i2c_add_driver not OK.\n", __FUNCTION__);
		printk(KERN_ERR "%s fail: i2c_add_driver not OK.\n", __FUNCTION__);
	}

	return ret;
}

static INT32 gsen_i2c_transfer(struct i2c_msg *msgs, INT32 num)
{
	int ret;

	if (unlikely(gsen_i2c_info->iic_adapter == NULL)) {
		DBG_ERR("%s fail: gsen_i2c_info->ii2c_adapter not OK\n", __FUNCTION__);
		printk(KERN_ERR "%s fail: pmu_i2c_info->ii2c_adapter not OK\n", __FUNCTION__);
		return -1;
	}

#if 0
	if (unlikely(i2c_transfer(gsen_i2c_info->iic_adapter, msgs, num) != num)) {
		DBG_ERR("%s fail: i2c_transfer not OK \n", __FUNCTION__);
		return -1;
	}
#else
	ret = i2c_transfer(gsen_i2c_info->iic_adapter, msgs, num);
	if (ret != num) {
		printk(KERN_ERR "%s fail: i2c_transfer not OK, ret %d\n", __FUNCTION__, ret);
	}
#endif

	return 0;
}

int8_t gsen_i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t data, uint16_t len)
{
	struct i2c_msg  msgs;

    char *pBuf = NULL;

    pBuf = (char *)kzalloc((len+1), GFP_KERNEL);

    if (pBuf == NULL) {
        printk("gsen_i2c_write: pBuf is NULL");
        return -1;
    }

	pBuf[0]    = reg_addr & 0xFF;
    memcpy(&pBuf[1], &data, len);
	msgs.addr  = gsen_i2c.addr; //must equal to dev_addr
	msgs.flags = 0;//w
	msgs.len   = len + 1;
	msgs.buf   = pBuf;

	gsen_i2c_transfer(&msgs, 1);

    kfree(pBuf);

    return 0;
}

int8_t gsen_i2c_read(uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint16_t len)
{
	struct i2c_msg  msgs[2];
	unsigned char   buf[1], buf2[1];

	buf[0]        = reg_addr & 0xFF;
	msgs[0].addr  = gsen_i2c.addr; //must equal to dev_addr
	msgs[0].flags = 0;//w
	msgs[0].len   = 1;
	msgs[0].buf   = buf;

	buf2[0]       = 0;
	msgs[1].addr  = gsen_i2c.addr;
	msgs[1].flags = 1;//r

	msgs[1].len   = len;
	msgs[1].buf   = (UINT8 *)data;

	gsen_i2c_transfer(msgs, 2);
	// printk(KERN_ERR "gsen_i2c_read %X \n", msgs[0].addr);
	return (UINT32)buf2[0];
}

static int gsen_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	printk("DA380 gsen probe success!!\n");
	gsen_i2c_info = NULL;
	gsen_i2c_info = MALLOC(sizeof(GSEN_I2C_INFO));
	if (gsen_i2c_info == NULL) {
		DBG_ERR("%s fail: MALLOC not OK.\n", __FUNCTION__);
		return E_SYS;
	}

	gsen_i2c_info->iic_client  = client;
	gsen_i2c_info->iic_adapter = client->adapter;

	i2c_set_clientdata(client, gsen_i2c_info);
	printk(KERN_ERR "gsen_i2c_probe!\r\n");

	return 0;
}

static int gsen_i2c_remove(struct i2c_client *client)
{
	FREE(gsen_i2c_info);
	gsen_i2c_info = NULL;
	printk(KERN_ERR "gsen_i2c_remove!\r\n");
	return 0;
}

void gsen_i2c_remove_driver(UINT32 id)
{
	i2c_unregister_device(gsen_i2c_info->iic_client);
	i2c_del_driver(&gsen_i2c_driver);
}

static ER gsen_init(void)
{
	ER rt;
	uint8_t chip_id = 0;
	rt = gsen_i2c_init_driver(gsen_i2c.id);
	gsen_i2c_read(GSEN_I2C_ADDR,0x01,&chip_id,1);
	if(chip_id != 0x13){
		gsen_i2c_read(GSEN_I2C_ADDR,0x01,&chip_id,1);
		if(chip_id != 0x13){
			gsen_i2c_read(GSEN_I2C_ADDR,0x01,&chip_id,1);
			if(chip_id != 0x13){
				printk(KERN_EMERG "------da380 read chip id  error= %x-----\r\n", chip_id);
				return -1;
			}
		}
	}
	printk("da380 read chip id = 0x%x\r\n", chip_id);
    //start soft rest
    gsen_i2c_write(GSEN_I2C_ADDR, 0x0F,0x06, 1);  //12bit   +-8g range

    gsen_i2c_write(GSEN_I2C_ADDR, 0x10,0x06, 1);  //0x06 62.5Hz     //0x07  125 Hz
    gsen_i2c_write(GSEN_I2C_ADDR, 0x11,0x5E, 1);  //0x1E//0x5E low power mode  //500Hz        //

    gsen_i2c_write(GSEN_I2C_ADDR, 0x16,0x00, 1);  /**INT_SET*/
    gsen_i2c_write(GSEN_I2C_ADDR, 0x17,0x00, 1);  /**INT_SET*/

    gsen_i2c_write(GSEN_I2C_ADDR, 0x19,0x00, 1);  /**INT_MAP*/
	gsen_i2c_write(GSEN_I2C_ADDR, 0x1A,0x00, 1);  /**INT_MAP*/
	
    gsen_i2c_write(GSEN_I2C_ADDR, 0x20,0x02, 1);  //0:selects active level low for pin INT        1: selects active level high for pin INT
    gsen_i2c_write(GSEN_I2C_ADDR, 0x21,0x80, 1);  /**temporary latched*/

	gsen_i2c_write(GSEN_I2C_ADDR, 0x27,0x03, 1);  /**Active duration time*/
	gsen_i2c_write(GSEN_I2C_ADDR, 0x28,0xFF, 1);  /**Threshold of active interrupt*/
	printk(KERN_EMERG "------da380 init successful -----\r\n");
	return rt;
}

static long gsen_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    unsigned int value = 0;
    HI_COLLISION_SHIFT_VALUE_S  Collision;
    int ret = 0;
	uint8_t chip_id = 0;
    da380_data_t raw_data = { {0} };
    uint8_t _baData[DA380_SENSOR_DATA_SIZE_RES_HIGH] = { 0, 0, 0, 0, 0, 0 };

    switch (_IOC_NR(cmd))
    {
	case _IOC_NR(IOC_GSENSORGET_CHIP_ID):
		gsen_i2c_read(GSEN_I2C_ADDR,0x18,&chip_id,1);
		ret = copy_to_user((void *)arg, &chip_id, sizeof(chip_id));
		if (0 != ret)
		{
			return -1;
		}
		break;
    case _IOC_NR(IOC_GSENSOR_PARKING_SENSITIVITY):
        //ret = copy_from_user(&value, &arg, sizeof(unsigned int));
		value = (unsigned int)arg;
		//printk("call kernel IOC_GSENSOR_PARKING_SENSITIVITY value=%d arg=%ld\r\n",value,arg);
        if(0 == value)
        {
	        //gsen_i2c_write(GSEN_I2C_ADDR, 0x11, 0x9E, 1);  /**standby mode*/
	        //gsen_i2c_write(GSEN_I2C_ADDR, 0x17,0x00, 1);   /**disable all inturupt*/
	        //gsen_i2c_write(GSEN_I2C_ADDR, 0x07,0x0, 1);    /**sleep mode*/
			//gsen_i2c_write(GSEN_I2C_ADDR, 0x19,0x00, 1);  /**INT_MAP*/
			//gsen_i2c_write(GSEN_I2C_ADDR, 0x1A,0x00, 1);  /**INT_MAP*/
            gsen_i2c_write(GSEN_I2C_ADDR, 0x16,0x00, 1);  /**INT_SET*/
            gsen_i2c_write(GSEN_I2C_ADDR, 0x17,0x00, 1);  /**INT_SET*/
			gsen_i2c_write(GSEN_I2C_ADDR, 0x28,0xFF, 1);  /**Threshold of active interrupt*/
			printk("call senstivity off\r\n");
        }
        else
        {
            gsen_i2c_write(GSEN_I2C_ADDR, 0x11, 0x9E, 1);  /**standby mode*/
            if(1 == value)/**senstivity low*/
            {
				printk("call senstivity low\r\n");
                //gsen_i2c_write(GSEN_I2C_ADDR, 0x04, SENSOR_PARKING_SENSITIVITY_LOW_VAL_L, 1);  /**Shake Threshold LSB*/
                //gsen_i2c_write(GSEN_I2C_ADDR, 0x05, SENSOR_PARKING_SENSITIVITY_LOW_VAL_H, 1);  /**Shake Threshold MSB*/
                gsen_i2c_write(GSEN_I2C_ADDR, 0x16,0x00, 1);  /**INT_SET*/
                gsen_i2c_write(GSEN_I2C_ADDR, 0x17,0x00, 1);  /**INT_SET*/
                gsen_i2c_write(GSEN_I2C_ADDR, 0x27,0x03, 1);  /**Active duration time*/
				gsen_i2c_write(GSEN_I2C_ADDR, 0x28,0x0F, 1);  /**Threshold of active interrupt*/
            }
            else if(2 == value)/**senstivity middle*/
            {
				printk("call senstivity middle\r\n");
                //gsen_i2c_write(GSEN_I2C_ADDR, 0x04, SENSOR_PARKING_SENSITIVITY_MID_VAL_L, 1);  /**Shake Threshold LSB*/
                //gsen_i2c_write(GSEN_I2C_ADDR, 0x05, SENSOR_PARKING_SENSITIVITY_MID_VAL_H, 1);  /**Shake Threshold MSB*/
                gsen_i2c_write(GSEN_I2C_ADDR, 0x16,0x00, 1);  /**INT_SET*/
                gsen_i2c_write(GSEN_I2C_ADDR, 0x17,0x00, 1);  /**INT_SET*/	
                gsen_i2c_write(GSEN_I2C_ADDR, 0x27,0x03, 1);  /**Active duration time*/			
				gsen_i2c_write(GSEN_I2C_ADDR, 0x28,0x08, 1);  /**Threshold of active interrupt*/
            }
            else/**senstivity heigh*/
            {
				printk("call senstivity heigh\r\n");
                //gsen_i2c_write(GSEN_I2C_ADDR, 0x04, SENSOR_PARKING_SENSITIVITY_HIGH_VAL_L, 1);  /**Shake Threshold LSB*/
                //gsen_i2c_write(GSEN_I2C_ADDR, 0x05, SENSOR_PARKING_SENSITIVITY_HIGH_VAL_H, 1);  /**Shake Threshold MSB*/
                gsen_i2c_write(GSEN_I2C_ADDR, 0x16,0x00, 1);  /**INT_SET*/
                gsen_i2c_write(GSEN_I2C_ADDR, 0x17,0x00, 1);  /**INT_SET*/
                gsen_i2c_write(GSEN_I2C_ADDR, 0x27,0x03, 1);  /**Active duration time*/				
				gsen_i2c_write(GSEN_I2C_ADDR, 0x28,0x02, 1);  /**Threshold of active interrupt*/
            }

            gsen_i2c_write(GSEN_I2C_ADDR, 0x16, 0x00, 1);  /**Shake inturupt enable*/
            gsen_i2c_write(GSEN_I2C_ADDR, 0x11, 0x5E, 1);  /**Shake and anymotion feature enable*/

            if(0 != LEVEL)
            {
                gsen_i2c_write(GSEN_I2C_ADDR, 0x07,0xC1, 1);  /**high level */
            }
            else
            {
                gsen_i2c_write(GSEN_I2C_ADDR, 0x07,0x41, 1);  /***low level*/
            }
        }
        break;

	case _IOC_NR(IOC_GSENSOR_COLLISION_SENSITIVITY):
		ret = copy_from_user(&value, (void *)arg, sizeof(unsigned int));
		if(0 == value)
		{
			gsen_i2c_write(GSEN_I2C_ADDR, 0x11, 0x9E, 1);		/**standby mode*/
			gsen_i2c_write(GSEN_I2C_ADDR, 0x17, 0x00, 1);		/**disable all inturupt*/
			//gsen_i2c_write(GSEN_I2C_ADDR, 0x07, 0xC1, 1);		/**wakeup mode*/
		}
		else
		{
			gsen_i2c_write(GSEN_I2C_ADDR, 0x11, 0x9E, 1);		/**standby mode*/
			if(1 == value)/**senstivity low*/
 			{
				gsen_i2c_write(GSEN_I2C_ADDR, 0x04,SENSOR_COLLISION_SENSITIVITY_LOW_VAL_L, 1);	/**Shake Threshold LSB*/
				gsen_i2c_write(GSEN_I2C_ADDR, 0x05,SENSOR_COLLISION_SENSITIVITY_LOW_VAL_H, 1);	/**Shake Threshold MSB*/
			}
			else if(2 == value)/**senstivity middle*/
			{
				gsen_i2c_write(GSEN_I2C_ADDR, 0x04,SENSOR_COLLISION_SENSITIVITY_MID_VAL_L, 1);	/**Shake Threshold LSB*/
				gsen_i2c_write(GSEN_I2C_ADDR, 0x05,SENSOR_COLLISION_SENSITIVITY_MID_VAL_H, 1);	/**Shake Threshold MSB*/

			}
			else/**senstivity heigh*/
                	{
				gsen_i2c_write(GSEN_I2C_ADDR, 0x04,SENSOR_COLLISION_SENSITIVITY_HIGH_VAL_L, 1);	/**Shake Threshold LSB*/
				gsen_i2c_write(GSEN_I2C_ADDR, 0x05,SENSOR_COLLISION_SENSITIVITY_HIGH_VAL_H, 1);	/**Shake Threshold MSB*/
			}
			
			gsen_i2c_write(GSEN_I2C_ADDR, 0x16, 0x07, 1);	/**shake inturupt enable*/
			gsen_i2c_write(GSEN_I2C_ADDR, 0x11, 0x5E, 1);	/**anymotion and shake feature enable*/


			if(0 != LEVEL)
			{
				//gsen_i2c_write(GSEN_I2C_ADDR, 0x07, 0xE1, 1);  /**high level */
			}
			else
			{
				//gsen_i2c_write(GSEN_I2C_ADDR, 0x07, 0x61, 1);  /***low level*/
			}

		}
        break;

	case _IOC_NR(IOC_GSENSOR_GET_CUR_VALUE):
            if (copy_from_user(&raw_data, (void *)arg, sizeof(da380_data_t)))
            	return -1;

            gsen_i2c_read(GSEN_I2C_ADDR, DA380_REG_XOUT_EX_L, (unsigned char*)&_baData[0], 1);
            gsen_i2c_read(GSEN_I2C_ADDR, DA380_REG_XOUT_EX_H, (unsigned char*)&_baData[1], 1);

            gsen_i2c_read(GSEN_I2C_ADDR, DA380_REG_YOUT_EX_L, (unsigned char*)&_baData[2], 1);
            gsen_i2c_read(GSEN_I2C_ADDR, DA380_REG_YOUT_EX_H, (unsigned char*)&_baData[3], 1);

            gsen_i2c_read(GSEN_I2C_ADDR, DA380_REG_ZOUT_EX_L, (unsigned char*)&_baData[4], 1);
            gsen_i2c_read(GSEN_I2C_ADDR, DA380_REG_ZOUT_EX_H, (unsigned char*)&_baData[5], 1);


            raw_data.fData[DA380_AXIS_X] = (_baData[0] | (_baData[1] << 8));
            raw_data.fData[DA380_AXIS_Y] = (_baData[2] | (_baData[3] << 8));
            raw_data.fData[DA380_AXIS_Z] = (_baData[4] | (_baData[5] << 8));

            if(copy_to_user((void *)arg, &raw_data, sizeof(da380_data_t)))
            	printk("IOC_GSENSOR_GET_CUR_VALUE error\n");
            break;
        case _IOC_NR(EXCEED_THRESHOLD_FLAG):
            gsen_i2c_read(GSEN_I2C_ADDR, 0x14,(unsigned char*)&value, 1);
	        //printk(KERN_EMERG "value = %d\n",value);
            if((value & 0x08) != 0)
            {
                Collision.COLLISION_HAPPEN = 0x1;
            }
            else
            {
                Collision.COLLISION_HAPPEN = 0x0;
            }
            if((value & 0x04) != 0)
            {
                Collision.SHIFT_HAPPEN = 0x1;
            }
            else
            {
                Collision.SHIFT_HAPPEN = 0x0;
            }
            ret = copy_to_user((void *)arg, &Collision, sizeof(HI_COLLISION_SHIFT_VALUE_S));
            if (0 != ret)
            {
                 return -1;
            }

        break;
    }
    return 0;
}

static int gsen_open(struct inode *inode, struct file *filp)
{
	printk("gsen open successful!\r\n");
	return 0;
}



static const struct file_operations gsen_fops = {
	.owner          = THIS_MODULE,
	.unlocked_ioctl	= gsen_ioctl,
	.open = gsen_open,
};

static struct miscdevice gsen_miscdev = {
	.minor          = MISC_DYNAMIC_MINOR,
	.name           = "gsensor",
	.fops           = &gsen_fops,
};

static int __init gsen_module_init(void)
{
	int rt;
	printk("----------------gsen_module_init-----------------------\r\n");
	DBG_IND("\n");

    rt = gsen_init();
	if (rt == -1)
	{
		gsen_i2c_remove_driver(gsen_i2c.id);
		printk(KERN_EMERG "------da380 not adapt-----\r\n");  
		return rt;
	}
	rt = misc_register(&gsen_miscdev);
    if (rt) {
        DBG_ERR("misc_register fail, ret = %d\n", rt);
        return rt;
    }

    return 0;
}

static void __exit gsen_module_exit(void)
{
	DBG_IND("\n");
	printk("----------------gsen_module_exit-----------------------\r\n");
    gsen_i2c_remove_driver(gsen_i2c.id);
}

module_init(gsen_module_init);
module_exit(gsen_module_exit);

MODULE_DESCRIPTION("da380 gsensor");
MODULE_AUTHOR("Novatek Corp.");
MODULE_LICENSE("GPL");

