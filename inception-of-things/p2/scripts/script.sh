#!/usr/bin/env bash
set -euo pipefail

curl -sfL https://get.k3s.io | INSTALL_K3S_EXEC="server --node-ip=${node_ip} --write-kubeconfig-mode=644" sh -

echo "${node_ip} app1.com" >> /etc/hosts
echo "${node_ip} app2.com" >> /etc/hosts
echo "${node_ip} app3.com" >> /etc/hosts
