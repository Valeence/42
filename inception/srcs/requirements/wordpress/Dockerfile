FROM debian:bullseye-slim

# Installation de PHP 8.2
RUN apt-get update && apt-get upgrade -y && apt-get install -y \
    ca-certificates \
    apt-transport-https \
    curl \
    lsb-release \
    && curl -sS https://packages.sury.org/php/README.txt | bash - \
    && apt-get update \
    && apt-get install -y php8.2-fpm \
    && apt-get install -y php8.2-mysqli \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /run/php

COPY conf/www.conf /etc/php/8.2/fpm/pool.d/www.conf
COPY tools/script.sh .
RUN chmod +x script.sh

CMD ["./script.sh"]