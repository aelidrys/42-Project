#!/bin/bash
echo "================================================================="
echo "Installing GitLab..."
set -euo pipefail

if [ -z "${HOST_IP:-}" ]; then
  echo "HOST_IP environment variable is not set. Please set it to the IP address of the host machine."
  exit 1
fi

curl https://packages.gitlab.com/install/repositories/gitlab/gitlab-ee/script.deb.sh | bash

EXTERNAL_URL="http://${HOST_IP}" apt install -y gitlab-ee


# Ensure GitLab is configured and services are running
# sudo gitlab-ctl reconfigure


# get root password
# sudo cat /etc/gitlab/initial_root_password
# get  argocd password
# kubectl get secret argocd-initial-admin-secret -n argocd -o jsonpath="{.data.password}" | base64 -d