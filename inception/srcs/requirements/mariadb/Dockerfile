FROM debian:bullseye-slim

RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y mariadb-client mariadb-server && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/lib/mysql /run/mysqld && \
    chown -R mysql:mysql /var/lib/mysql /run/mysqld && \
    chmod 777 /tmp

COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/
COPY tools/init.sql /etc/mysql/init.sql
COPY tools/script.sh /script.sh
RUN chmod +x /script.sh

CMD ["./script.sh"]
