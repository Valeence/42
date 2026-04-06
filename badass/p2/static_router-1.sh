ip link add br0 type bridge #switch virtuel qui relie host -> tunnel
ip link set dev br0 up

ip addr add 10.1.1.1/24 dev eth0 #underlay (transporte les paquets vxlan)
# vxlan tunnel entre 10.1.1.1 a 10.1.1.2
ip link add name vxlan10 type vxlan id 10 dev eth0 remote 10.1.1.2 local 10.1.1.1 dstport 4789
ip addr add 20.1.1.1/24 dev vxlan10

# bridgecontrol: add eth1 and vxlan10 to the bridge, to directly connect the VXLAN network to the host on eth1.
brctl addif br0 eth1
brctl addif br0 vxlan10

ip link set dev vxlan10 up