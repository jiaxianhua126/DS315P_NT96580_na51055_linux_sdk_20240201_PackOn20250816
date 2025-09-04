#ifndef __DXLED_H
#define __DXLED_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
typedef struct led_config {
	unsigned int led_num;
	unsigned int led_time;
}led_cfg;

void select_sleep(unsigned int mSectime);
void Led_Install(unsigned int Led_Num,unsigned int Led_time);
void Led_Uninstall(void);
#endif
