#!/bin/sh

modprobe cfg80211

MODULES=`lsmod | grep bcmdhd`

if [ -z "$MODULES" ]; then
	insmod /lib/modules/5.10.168/extra/net/bcmdhd.101.10.591.x/bcmdhd.ko firmware_path=/lib/firmware/fw_syn43711a0_sdio.bin nvram_path=/lib/firmware/nvram_ap6611s.txt
else
	echo "bcmdhd already exist"
fi

TRY=0
while [ 1 ]
do
	WLAN0=`ifconfig -a | grep wlan0`
	echo "WLAN0=$WLAN0"

	if [ -z "$WLAN0" ]; then
		echo "TRY=$TRY"
		if [ $TRY -gt 5 ]; then
			rmmod bcmdhd
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
