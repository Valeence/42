#!/bin/bash

curl -sfL https://get.k3s.io | \
  INSTALL_K3S_EXEC="server --node-ip=192.168.56.110 --write-kubeconfig-mode=644" sh -

sleep 2

TOKEN=$(sudo cat /var/lib/rancher/k3s/server/node-token)

echo "$TOKEN" | sudo tee /vagrant/token.txt > /dev/null
