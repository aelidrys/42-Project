#!/bin/bash

set -e

echo "Creating k3d cluster"


k3d cluster create --servers 1 --agents 1 || true

echo "Creating namespaces"
kubectl delete namespace argocd --ignore-not-found
kubectl delete namespace dev --ignore-not-found
kubectl create namespace argocd || true
kubectl create namespace dev || true

echo "Installing ArgoCD"

kubectl apply --server-side -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml
kubectl wait --for=condition=available --timeout=300s deployment -n argocd --all



echo "Disabling TLS for ArgoCD (use HTTP)"
kubectl patch deployment argocd-server -n argocd \
  --type='json' \
  -p='[
    {
      "op": "replace",
      "path": "/spec/template/spec/containers/0/args",
      "value": ["/usr/local/bin/argocd-server","--insecure"]
    }
  ]'

kubectl rollout restart deployment argocd-server -n argocd
kubectl rollout status deployment argocd-server -n argocd

echo "ArgoCD admin password:"

kubectl get secret argocd-initial-admin-secret -n argocd \
  -o jsonpath="{.data.password}" | base64 -d
echo ""
echo "Applying application configuration"
sleep 5
kubectl apply -f confs/

echo ""
echo "✅ Setup complete"
echo ""
echo "👉 Access ArgoCD:"
echo "kubectl port-forward svc/argocd-server -n argocd 8080:80"
echo "Open: http://localhost:8080"
echo ""
echo "👉 Access App:"
echo "kubectl port-forward svc/my-app -n dev 8888:8888"
echo "Open: http://localhost:8888"
