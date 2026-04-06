#!/bin/bash

for ID in $(docker ps -q); do

    HOSTNAME=$(docker exec -it "$ID" hostname 2>/dev/null | tr -d '\r')

    echo "➡️  $ID → $HOSTNAME"

    if [ "$HOSTNAME" = "host-vandre-1" ]; then
        docker exec -i "$ID" sh < host-1.sh
    fi

    if [ "$HOSTNAME" = "host-vandre-2" ]; then
        docker exec -i "$ID" sh < host-2.sh
    fi

    if [ "$HOSTNAME" = "router-vandre-1" ]; then
        docker exec -i "$ID" sh < static_router-1.sh
    fi

    if [ "$HOSTNAME" = "router-vandre-2" ]; then
        docker exec -i "$ID" sh < static_router-2.sh
    fi

done
