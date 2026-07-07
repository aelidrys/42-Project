# base image of ff_nginx
FROM debian:11


# install nginx
RUN apt-get update -y && apt-get install nginx -y 

# Copy configeration files to the container
COPY config.conf /etc/nginx/sites-enabled

# generate ssl certaficate
RUN mkdir /etc/nginx/ssl
RUN apt-get update -y && apt-get install openssl -y
RUN openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key \
    -subj "/C=MR/ST=IDF/L=benguerir/O=1337/OU=1337/CN=aelidrys.42.fr/UID=aelidrys" 

# start nginx when the container is run
CMD ["nginx" ,"-g","daemon off;"]