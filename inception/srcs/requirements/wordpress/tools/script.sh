#!/bin/bash

cd /var/www/html
curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar # gérer WordPress sans passer par l'interface graphique.
chmod +x wp-cli.phar
./wp-cli.phar core download --allow-root
./wp-cli.phar config create --dbname="$MYSQL_DATABASE" --dbuser="$MYSQL_USER" --dbpass="$MYSQL_PASSWORD" --dbhost="$MYSQL_HOST" --allow-root
./wp-cli.phar core install --url="$WP_URL" --title="$WP_TITLE" --admin_user="$WP_ADMIN" --admin_password="$WP_ADMIN_PASSWORD" --admin_email="$WP_ADMIN_MAIL" --allow-root

# Créer l'utilisateur admin s'il n'existe pas
if ! ./wp-cli.phar user get "$WP_ADMIN_USER" --allow-root > /dev/null 2>&1; then
    echo "Création de l'utilisateur admin..."
    ./wp-cli.phar user create "$WP_ADMIN" "$WP_ADMIN_MAIL" --role=administrator --user_pass="$WP_ADMIN_PASSWORD" --allow-root
fi

# Créer l'utilisateur normal s'il n'existe pas
if ! ./wp-cli.phar user list --allow-root | grep -q "$WP_USER"; then
    ./wp-cli.phar user create "$WP_USER" "$WP_MAIL" --role=subscriber --user_pass="$WP_USER_PASSWORD" --allow-root
fi

# Lancer PHP-FPM
php-fpm8.2 -F