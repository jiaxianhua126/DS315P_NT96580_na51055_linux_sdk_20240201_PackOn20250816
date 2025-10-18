ifconfig lo up
ifconfig wlan0 up
ifconfig wlan0 192.168.11.1
hostapd /etc/hostapd_80m.conf -dd &
touch /var/lib/misc/udhcp.leases
dnsmasq -i wlan0 -C /etc/dnsmasq.conf &
