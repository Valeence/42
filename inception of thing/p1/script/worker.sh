#!/bin/bash

MASTER_IP="192.168.56.110"
TOKEN=$(cat /vagrant/token.txt)

curl -sfL https://get.k3s.io | \
  K3S_URL="https://$MASTER_IP:6443" \
  K3S_TOKEN="$TOKEN" \
  INSTALL_K3S_EXEC="agent --node-ip=192.168.56.111" \
  sh -
