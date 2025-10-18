#!/bin/sh

echo $#
echo $*
mkfifo /var/run/wifi_events.pipe
TRY=0
HOSTAPD=`ps`
AMPK_AP=0
HOSTAPD=`echo $HOSTAPD | grep hostapd`
if [ -n "$HOSTAPD" ]; then
        echo "hostapd is running. Try to stop it"
	killall -9 hostapd
	while [ 1 ]
	do
		HOSTAPD=`ps`
		HOSTAPD=`echo $HOSTAPD | grep hostapd`
		if [ -n "$HOSTAPD" ]; then
			if [ $TRY -gt 5 ]; then
				echo "can't stop hostapd"
				exit 255
			else
				echo "TRY=$TRY"
				TRY=$((${TRY}+1))
	                        sleep 1
			fi
		else
			echo "hostapd is stopped"
			break
		fi
	done
	ifconfig wlan0 down
fi

TRY=0
WPA=`ps`
WPA=`echo $WPA | grep wpa_supplicant`
if [ -n "$WPA" ]; then
        echo "wpa_supplicant is running. Try to stop it"
        killall -9 wpa_supplicant
        while [ 1 ]
        do
		WPA=`ps`
		WPA=`echo $WPA | grep wpa_supplicant`
                if [ -n "$WPA" ]; then
                        if [ $TRY -gt 5 ]; then
                                echo "can't stop wpa_supplicant"
                                exit 255
                        else
                                echo "TRY=$TRY"
                                TRY=$((${TRY}+1))
                                sleep 1
                        fi
                else
                        echo "wpa_supplicant is stopped"
                        break
                fi
        done
        ifconfig wlan0 down
fi



if [ "$1" == "ap" ]; then
	ifconfig lo up
	ifconfig wlan0 up


	if [ "$2" == "5G" ]; then
                echo preamble=1 >> /var/run/hostapd.conf
                echo utf8_ssid=1 >> /var/run/hostapd.conf
                echo hw_mode=a >> /var/run/hostapd.conf
                echo ieee80211n=1 >> /var/run/hostapd.conf
                echo ieee80211ac=1 >> /var/run/hostapd.conf
                echo ieee80211ax=1 >> /var/run/hostapd.conf
                echo country_code=CN >> /var/run/hostapd.conf
                echo channel=36 >> /var/run/hostapd.conf
                echo vht_oper_chwidth=1 >> /var/run/hostapd.conf
                echo ht_capab=[HT20][HT40+][SHORT-GI-40][SHORT-GI-20] >> /var/run/hostapd.conf
                echo vht_capab=[SHORT-GI-80][MAX-A-MPDU-LEN-EXP7] >> /var/run/hostapd.conf
                echo vht_oper_centr_freq_seg0_idx=42 >> /var/run/hostapd.conf
                echo he_oper_centr_freq_seg0_idx=42 >> /var/run/hostapd.conf
                echo he_oper_chwidth=1 >> /var/run/hostapd.conf
                echo obss_interval=0 >> /var/run/hostapd.conf
		echo "5G mode successful"
                echo wmm_enabled=1 >> /var/run/hostapd.conf
	elif [ "$2" == "5.8G" ]; then
		echo preamble=1 >> /var/run/hostapd.conf
                echo utf8_ssid=1 >> /var/run/hostapd.conf
                echo logger_syslog=-1 >> /var/run/hostapd.conf
                echo logger_syslog_level=2 >> /var/run/hostapd.conf
                echo logger_stdout=-1 >> /var/run/hostapd.conf
                echo logger_stdout_level=2 >> /var/run/hostapd.conf
                echo hw_mode=a >> /var/run/hostapd.conf
                echo ieee80211n=1 >> /var/run/hostapd.conf
                echo ieee80211ac=1 >> /var/run/hostapd.conf
                echo ieee80211ax=1 >> /var/run/hostapd.conf
                echo country_code=CN >> /var/run/hostapd.conf
                echo channel=149 >> /var/run/hostapd.conf
                echo vht_oper_chwidth=1 >> /var/run/hostapd.conf
                echo ht_capab=[HT20][HT40+][SHORT-GI-40][SHORT-GI-20] >> /var/run/hostapd.conf
                echo vht_capab=[SHORT-GI-80][MAX-A-MPDU-LEN-EXP7] >> /var/run/hostapd.conf
                echo vht_oper_centr_freq_seg0_idx=155 >> /var/run/hostapd.conf
                echo he_oper_centr_freq_seg0_idx=155 >> /var/run/hostapd.conf
                echo he_oper_chwidth=1 >> /var/run/hostapd.conf
                echo obss_interval=0 >> /var/run/hostapd.conf
		echo "5G mode successful"
	elif [ "$2" == "2.4G" ]; then
                echo logger_syslog=-1 >> /var/run/hostapd.conf
                echo logger_syslog_level=2 >> /var/run/hostapd.conf
                echo logger_stdout=-1 >> /var/run/hostapd.conf
                echo logger_stdout_level=2 >> /var/run/hostapd.conf
                echo preamble=1 >> /var/run/hostapd.conf
                echo utf8_ssid=1 >> /var/run/hostapd.conf
                echo ieee80211n=1 >> /var/run/hostapd.conf
                echo ieee80211ac=0 >> /var/run/hostapd.conf
                echo ieee80211ax=1 >> /var/run/hostapd.conf
                echo country_code=CN >> /var/run/hostapd.conf
                echo channel=6 >> /var/run/hostapd.conf
                echo hw_mode=g >> /var/run/hostapd.conf
                echo "2.4G mode successful"
                echo ht_capab=[HT20][SHORT-GI-20][SHORT-GI-40] >> /var/run/hostapd.conf
                echo obss_interval=0 >> /var/run/hostapd.conf
                echo wmm_enabled=1 >> /var/run/hostapd.conf
	else
		echo preamble=1 >> /var/run/hostapd.conf
                echo utf8_ssid=1 >> /var/run/hostapd.conf
                echo hw_mode=a >> /var/run/hostapd.conf
                echo ieee80211n=1 >> /var/run/hostapd.conf
                echo ieee80211ac=1 >> /var/run/hostapd.conf
                echo ieee80211ax=1 >> /var/run/hostapd.conf
                echo country_code=CN >> /var/run/hostapd.conf
                echo channel=149 >> /var/run/hostapd.conf
                echo vht_oper_chwidth=1 >> /var/run/hostapd.conf
                echo ht_capab=[HT20][HT40+][SHORT-GI-40][SHORT-GI-20] >> /var/run/hostapd.conf
                echo vht_capab=[SHORT-GI-80][MAX-A-MPDU-LEN-EXP7] >> /var/run/hostapd.conf
                echo vht_oper_centr_freq_seg0_idx=155 >> /var/run/hostapd.conf
                echo he_oper_centr_freq_seg0_idx=155 >> /var/run/hostapd.conf
                echo he_oper_chwidth=1 >> /var/run/hostapd.conf
                echo obss_interval=0 >> /var/run/hostapd.conf
		echo "5G mode successful"
	fi

	echo driver=nl80211 >> /var/run/hostapd.conf
	echo ctrl_interface=/var/run/hostapd >> /var/run/hostapd.conf

	hostapd  /var/run/hostapd.conf &

	TRY=0
	while [ 1 ]
	do
	        UP=`ifconfig wlan0 | grep UP`
	        echo "UP=$UP"
	
	        if [ -z "$UP" ]; then
	                echo "TRY=$TRY"
	                if [ $TRY -gt 5 ]; then
	                        hostapd stop
	                        exit 255
	                else
	                        TRY=$((${TRY}+1))
	                        sleep 1
	                fi
	        else
	                echo "UP ok"
	                ifconfig wlan0 192.168.1.254
			break
	        fi
	done

	udhcpd /etc/udhcpdw.conf
	TRY=0
	while [ 1 ]
	do
	        DHCP=`ps`
	        DHCP=`echo $DHCP | grep udhcpd`
	        echo "DHCP=$DHCP"
	
	        if [ -z "$DHCP" ]; then
	                echo "TRY=$TRY"
	                if [ $TRY -gt 5 ]; then
	                        echo "Can't run udhcpd"
	                        exit 255
	                else
	                        TRY=$((${TRY}+1))
	                        sleep 1
	                fi
	        else
	                echo "udhcpd ok"
	                exit 0
	        fi
	done
elif [ "$1" == "sta" ]; then
		wpa_supplicant -Dnl80211 -i wlan0 -c /var/run/wpa_supplicant.conf &
        TRY=0
        while [ 1 ]
        do
                UP=`ifconfig wlan0 | grep UP`
                echo "UP=$UP"

                if [ -z "$UP" ]; then
                        echo "TRY=$TRY"
                        if [ $TRY -gt 5 ]; then
                                hostapd stop
                                exit 255
                        else
                                TRY=$((${TRY}+1))
                                sleep 1
                        fi
                else
                        echo "UP ok"
                        ifconfig wlan0 192.168.1.1
                        break
                fi
        done

        udhcpc -i wlan0
        TRY=0
        while [ 1 ]
        do
                DHCP=`ps`
                DHCP=`echo $DHCP | grep udhcpc`
                echo "DHCP=$DHCP"

                if [ -z "$DHCP" ]; then
                        echo "TRY=$TRY"
                        if [ $TRY -gt 5 ]; then
                                echo "Can't run udhcpc"
                                exit 255
                        else
                                TRY=$((${TRY}+1))
                                sleep 1
                        fi
                else
                        echo "udhcpd ok"
                        exit 0
                fi
        done
fi

echo "exit up.sh"
exit 255
