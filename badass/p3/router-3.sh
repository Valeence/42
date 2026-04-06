#!/bin/bash

# === PARTIE FRR ===
vtysh << EOF
configure terminal

interface lo
 ip address 1.1.1.3/32

interface eth1
 ip address 10.1.1.6/30

router ospf
 network 1.1.1.3/32 area 0
 network 10.1.1.4/30 area 0

router bgp 65000
 bgp router-id 1.1.1.3
 no bgp ebgp-requires-policy
 neighbor 1.1.1.1 remote-as 65000
 neighbor 1.1.1.1 update-source lo
 address-family l2vpn evpn
  neighbor 1.1.1.1 activate
  advertise-all-vni
 exit-address-family

exit
exit
write memory
exit
EOF

# === PARTIE VXLAN + BRIDGE ===
ip link add vxlan10 type vxlan id 10 dstport 4789 local 1.1.1.3 nolearning
ip link set vxlan10 up

brctl addbr br10
brctl addif br10 vxlan10
brctl addif br10 eth0
ip link set br10 up