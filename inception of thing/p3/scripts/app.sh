PASS=$(kubectl -n argocd get secret argocd-initial-admin-secret -o jsonpath="{.data.password}" | base64 -d)

argocd login argocd.127.0.0.1.nip.io:8085 --username admin --password $PASS --plaintext --insecure

argocd app create will-app \
 --repo https://github.com/CarsonJo/cjozefzo-iot \
 --path . \
 --dest-server https://kubernetes.default.svc \
 --dest-namespace dev 

argocd app set will-app --sync-policy automated 

#kubectl -n argocd get secret argocd-initial-admin-secret -o jsonpath="{.data.password}" | base64 -d
