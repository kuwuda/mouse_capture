#!/bin/sh
# A very hack-ish mouse capture script
# Must use flat acceleration profile

if [[ $(pgrep mon_lock) ]];
then
	pkill mon_lock
	exit 0
fi

DEVNODE=/dev/input/by-id/usb-Kingsis_Peripherals_ZOWIE_Gaming_mouse-event-mouse

DISPLAY=$(swaymsg -t get_outputs | jq -r '.. | select(.focused? == true) | (.rect.width, .rect.height, .rect.x, .rect.y)' | tr "\n" " ")

ARGS=$DISPLAY+$(slurp -p | cut -f1 -d" " | tr "," " ")

intercept -g $DEVNODE | /home/kusu/scripts/mon_lock $ARGS | uinput -d $DEVNODE
