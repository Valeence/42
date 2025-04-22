FROM debian:bullseye-slim

# Install nginx
RUN apt-get update && apt-get upgrade -y && apt-get install -y nginx openssl
RUN mkdir -p /etc/nginx/ssl
RUN openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key -subj "/C=FR/ST=IDF/L=Paris/O=42/OU=42/CN=vandre.42.fr/UID=vandre"

# root directory
RUN chmod 755 /var/www/html 
RUN chown -R www-data:www-data /var/www/html

# Copy the configuration file
COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY tools/default /etc/nginx/sites-available/default

# Start the service
CMD ["nginx", "-g", "daemon off;"]