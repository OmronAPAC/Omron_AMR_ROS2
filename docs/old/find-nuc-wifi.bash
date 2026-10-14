#!/bin/bash

drng="192.168.105.0/24"
rng=$1
mac="5c:80:b6:0a:33:f9"

echo "Scanning with Nmap"

if [ -z "$rng" ]
then
    echo "Scanning at default range: $drng"
    nmap -sn $drng
else
    echo "Scanning at given range: $rng"
    nmap -sn $rng
fi

echo ""
echo "Looking for MAC address $mac please wait..."
sleep 8 && 
arp -n | grep $mac
