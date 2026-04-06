#!/bin/bash

find_container() {
    local hostname=$1
    for ID in $(docker ps -q); do
        local CURRENT_HOSTNAME=$(docker exec -it "$ID" hostname 2>/dev/null | tr -d '\r')
        if [ "$CURRENT_HOSTNAME" = "$hostname" ]; then
            echo "$ID"
            return 0
        fi
    done
    return 1
}

echo "ÉTAPE 1/3 : Configuration du Route Reflector (R1)"
R1_ID=$(find_container "vandre-1")
if [ -n "$R1_ID" ]; then
    echo "Conteneur $R1_ID → vandre-1"
    docker exec -i "$R1_ID" sh < router-1.sh
    echo "R1 configuré"
    sleep 5
else
    echo "R1 non trouvé !"
    exit 1
fi

echo ""
echo "ÉTAPE 2/3 : Configuration des Leafs (R2, R3, R4)"

R2_ID=$(find_container "vandre-2")
if [ -n "$R2_ID" ]; then
    echo "➡️  Conteneur $R2_ID → vandre-2"
    docker exec -i "$R2_ID" sh < router-2.sh
    echo "R2 configuré"
fi

R3_ID=$(find_container "vandre-3")
if [ -n "$R3_ID" ]; then
    echo "Conteneur $R3_ID → vandre-3"
    docker exec -i "$R3_ID" sh < router-3.sh
    echo "R3 configuré"
fi

R4_ID=$(find_container "vandre-4")
if [ -n "$R4_ID" ]; then
    echo "Conteneur $R4_ID → vandre-4"
    docker exec -i "$R4_ID" sh < router-4.sh
    echo "R4 configuré"
fi

sleep 10

echo ""
echo "ÉTAPE 3/3 : Configuration des Hosts (H1, H2, H3)"

H1_ID=$(find_container "host-vandre-1")
if [ -n "$H1_ID" ]; then
    echo "Conteneur $H1_ID → host-vandre-1"
    docker exec -i "$H1_ID" sh < host-1.sh
    echo "H1 configuré"
fi

H2_ID=$(find_container "host-vandre-2")
if [ -n "$H2_ID" ]; then
    echo "Conteneur $H2_ID → host-vandre-2"
    docker exec -i "$H2_ID" sh < host-2.sh
    echo "H2 configuré"
fi

H3_ID=$(find_container "host-vandre-3")
if [ -n "$H3_ID" ]; then
    echo "Conteneur $H3_ID → host-vandre-3"
    docker exec -i "$H3_ID" sh < host-3.sh
    echo "H3 configuré"
fi

echo "   docker exec -it $R1_ID vtysh -c 'show bgp l2vpn evpn summary'"
echo "   docker exec -it $H1_ID ping 192.168.10.2"