#!/bin/bash

curl -sfL https://get.k3s.io | \
  INSTALL_K3S_EXEC="server --node-ip=192.168.56.110 --write-kubeconfig-mode=644" \
  sh -

echo '<h1>Hello from app 1!</h1>' > index1.html
echo '<h1>Hello from app 2!</h1>' > index2.html
echo '<h1>Hello from app 3!</h1>' > index3.html

kubectl apply -f ../../vagrant/app1/app-one.yaml

kubectl apply -f ../../vagrant/app2/app-two.yaml

kubectl apply -f ../../vagrant/app3/app-three.yaml