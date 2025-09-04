#ifndef _GSENSOR_MAIN_H
#define _GSENSOR_MAIN_H

#ifdef __KERNEL__
#include <linux/delay.h>
#include "kwrap/type.h"
#include "kwrap/flag.h"
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#else
#include "kwrap/type.h"
#include "kwrap/flag.h"
#endif

int8_t gsen_i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t data, uint16_t len);
int8_t gsen_i2c_read(uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint16_t len);

#endif

