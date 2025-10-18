#!/bin/sh

modprobe cfg80211

MODULES=`lsmod | grep aic8800`

if [ -z "$MODULES" ]; then
	insmod /lib/modules/4.19.91/extra/net/aic8800/aic8800_bsp/aic8800_bsp.ko
	insmod /lib/modules/4.19.91/extra/net/aic8800/aic8800_fdrv/aic8800_fdrv.ko
	#insmod /lib/modules/4.19.91/kernel/drivers/net/wireless/aic8800/aic8800_bsp/aic8800_bsp.ko
	#insmod /lib/modules/4.19.91/kernel/drivers/net/wireless/aic8800/aic8800_fdrv/aic8800_fdrv.ko
	#insmod /lib/modules/4.19.91/hdal/aic8800/aic8800_bsp/aic8800_bsp.ko
	#insmod /lib/modules/4.19.91/hdal/aic8800/aic8800_fdrv/aic8800_fdrv.ko
else
	echo "aic8800 already exist"
fi

TRY=0
while [ 1 ]
do
	WLAN0=`ifconfig -a | grep wlan0`
	echo "WLAN0=$WLAN0"

	if [ -z "$WLAN0" ]; then
		echo "TRY=$TRY"
		if [ $TRY -gt 5 ]; then
			rmmod aic8800
			exit 255
		else
			TRY=$((${TRY}+1))
			sleep 1
		fi
	else
		echo "$WLAN0 found"
		exit 0
	fi
done
