
vtysh << EOF
configure terminal

interface lo
 ip address 1.1.1.1/32

interface eth0
 ip address 10.1.1.1/30

interface eth1
 ip address 10.1.1.5/30

interface eth2
 ip address 10.1.1.9/30

router ospf
 network 1.1.1.1/32 area 0
 network 10.1.1.0/30 area 0
 network 10.1.1.4/30 area 0
 network 10.1.1.8/30 area 0

router bgp 65000
 bgp router-id 1.1.1.1
 no bgp ebgp-requires-policy
 bgp cluster-id 1.1.1.1
 neighbor leafs peer-group
 neighbor leafs remote-as 65000
 neighbor leafs update-source lo
 neighbor leafs route-reflector-client
 neighbor 1.1.1.2 peer-group leafs
 neighbor 1.1.1.3 peer-group leafs
 neighbor 1.1.1.4 peer-group leafs
 address-family l2vpn evpn
  neighbor leafs activate
  neighbor leafs route-reflector-client
 exit-address-family

exit
exit
write memory
exit
EOF