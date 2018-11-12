# $1 is drop probability
sudo iptables -A OUTPUT -p udp -m statistic --mode random --probability $1 -j DROP
