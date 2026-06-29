#!/bin/bash

set -e

apt-get update -y

echo "checking curl"
if ! command -v curl &> /dev/null; then
    apt-get install -y curl
else
    echo "curl is already installed"
fi


echo "checking kubectl"
if ! command -v kubectl &> /dev/null; then
    KUBECTL_VERSION=$(curl -s https://dl.k8s.io/release/stable.txt)

    curl -LO "https://dl.k8s.io/release/${KUBECTL_VERSION}/bin/linux/amd64/kubectl"
    curl -LO "https://dl.k8s.io/release/${KUBECTL_VERSION}/bin/linux/amd64/kubectl.sha256"

    echo "$(cat kubectl.sha256) kubectl" | sha256sum --check

    install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl

    rm kubectl kubectl.sha256
else
    echo "kubectl is already installed"
fi

echo "installing k3d"
if ! command -v k3d &> /dev/null; then
    curl -fsSL https://raw.githubusercontent.com/k3d-io/k3d/main/install.sh | bash
else
    echo "k3d is already installed"
fi

HOSTS_FILE="/etc/hosts"

add_host() {
    ENTRY=$1
    if ! grep -q "$ENTRY" $HOSTS_FILE; then
        echo "$ENTRY" >> $HOSTS_FILE
        echo "Added $ENTRY"
    else
        echo "$ENTRY already exists"
    fi
}

add_host "127.0.0.1 argocd.local"
add_host "127.0.0.1 app.local"

echo "Installation complete"